
# Project 02 - Emergency Stop Station

LINK VIDEO : https://youtu.be/ms8RlsjGRMo

## 1. System Overview

**Emergency Stop Station** adalah sistem kontrol sederhana berbasis ESP32 yang mensimulasikan mekanisme **START/STOP dan Emergency Stop** pada panel kontrol industri.

Push button **START** digunakan untuk mengaktifkan sistem, sedangkan push button **STOP** digunakan untuk mengembalikan sistem ke kondisi READY. Push button **E-STOP** digunakan untuk mengaktifkan kondisi darurat, dan push button **RESET** digunakan untuk mengembalikan sistem dari kondisi darurat ke kondisi READY.

LED hijau digunakan sebagai indikator sistem sedang RUNNING, sedangkan LED merah digunakan sebagai indikator kondisi EMERGENCY.

Project ini dibuat menggunakan ESP32 dengan konsep dasar **Digital Input, Digital Output, State Machine, dan Emergency Stop Logic**.

---

## 2. Control Logic

Sistem menggunakan variabel `state` sebagai **state** untuk menyimpan kondisi sistem.

### READY State

```text
Initial State
     ↓
state = 0
     ↓
Green LED OFF
     ↓
Red LED OFF
```

### START Sequence

```text
START Button
     ↓
digitalRead()
     ↓
state = 1
     ↓
Green LED ON
     ↓
System RUNNING
```

### STOP Sequence

```text
STOP Button
     ↓
digitalRead()
     ↓
state = 0
     ↓
Green LED OFF
     ↓
Red LED OFF
     ↓
System READY
```

### E-STOP Sequence

```text
E-STOP Button
     ↓
digitalRead()
     ↓
state = 2
     ↓
Green LED OFF
     ↓
Red LED ON
     ↓
System EMERGENCY
```

### RESET Sequence

```text
RESET Button
     ↓
digitalRead()
     ↓
state = 0
     ↓
Green LED OFF
     ↓
Red LED OFF
     ↓
System READY
```

Variabel `state` digunakan untuk menyimpan kondisi sistem:

- `state = 0` → READY
- `state = 1` → RUNNING
- `state = 2` → EMERGENCY

Ketika tombol **START** ditekan saat sistem berada pada kondisi READY, ESP32 mengubah nilai `state` menjadi `1`. LED hijau akan menyala sebagai indikator bahwa sistem sedang RUNNING.

Ketika tombol **STOP** ditekan saat sistem sedang RUNNING, ESP32 mengubah nilai `state` menjadi `0`. Kedua LED akan mati dan sistem kembali ke kondisi READY.

Ketika tombol **E-STOP** ditekan, ESP32 mengubah nilai `state` menjadi `2`. LED hijau akan mati dan LED merah akan menyala sebagai indikator kondisi EMERGENCY.

Kondisi EMERGENCY tetap tersimpan meskipun tombol E-STOP dilepas. Sistem hanya dapat kembali ke kondisi READY setelah tombol **RESET** ditekan.

Konsep ini mensimulasikan **state machine control**, yaitu sistem yang memiliki beberapa kondisi dan berpindah dari satu kondisi ke kondisi lainnya berdasarkan input yang diterima.

---

## 3. Hardware & Pin Configuration

| Component | GPIO | Function |
|---|---:|---|
| Green LED | GPIO 23 | Output / RUNNING Indicator |
| Red LED | GPIO 22 | Output / EMERGENCY Indicator |
| START Button | GPIO 18 | Input / START Command |
| STOP Button | GPIO 19 | Input / STOP Command |
| E-STOP Button | GPIO 21 | Input / Emergency Command |
| RESET Button | GPIO 4 | Input / RESET Command |

### Input Configuration

Push button menggunakan konfigurasi:

```cpp
INPUT_PULLDOWN
```

Dengan konfigurasi ini, kondisi input secara default berada pada `LOW`. Ketika push button ditekan, input menerima tegangan `3.3V` sehingga terbaca sebagai `HIGH`.

### LED Configuration

LED digunakan sebagai indikator kondisi sistem.

Rangkaian LED menggunakan resistor sebagai pembatas arus:

```text
GPIO
   │
Resistor 1kΩ
   │
LED (+)
LED (-)
   │
  GND
```

LED hijau digunakan sebagai indikator RUNNING, sedangkan LED merah digunakan sebagai indikator EMERGENCY.

---

## 4. Operation

| Action | Result |
|---|---|
| Initial State | Both LEDs OFF |
| Press START | Green LED turns ON |
| Press STOP | Both LEDs turn OFF |
| Press E-STOP | Red LED turns ON, green LED turns OFF |
| Release E-STOP | System remains in EMERGENCY |
| Press RESET | Both LEDs turn OFF, system returns to READY |

### Operating Sequence

```text
Initial State
     ↓
System READY
     ↓
Press START
     ↓
System RUNNING
     ↓
Press E-STOP
     ↓
System EMERGENCY
     ↓
Release E-STOP
     ↓
System remains in EMERGENCY
     ↓
Press RESET
     ↓
System READY
```

---

## 5. Learning Outcomes

Through this project, the following concepts were learned:

- Digital Input
- Digital Output
- Push Button
- LED Control
- `digitalRead()`
- `digitalWrite()`
- Integer Variable (`int`)
- State Management
- State Machine
- `INPUT_PULLDOWN`
- START/STOP Control Logic
- Emergency Stop Logic
- Basic Industrial Control Logic

---
