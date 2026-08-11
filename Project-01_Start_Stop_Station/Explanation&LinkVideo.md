# Project 01 - Start Stop Station

LINK VIDEO : https://youtube.com/shorts/9BZFkrv-fqc?si=ajguD65vyTBAovfh

## 1. System Overview

**Start Stop Station** adalah sistem kontrol sederhana yang mensimulasikan mekanisme **START/STOP** pada panel kontrol industri.

Push button **START** digunakan untuk mengaktifkan output, sedangkan push button **STOP** digunakan untuk menonaktifkannya. LED digunakan sebagai indikator status motor.

Project ini dibuat menggunakan ESP32 dengan konsep dasar **Digital Input, Digital Output, State, dan Latching Control**.

---

## 2. Control Logic

Sistem menggunakan variabel `motorON` sebagai **state** untuk menyimpan kondisi output motor.

### START Sequence

```text
START Button
     ↓
digitalRead()
     ↓
motorON = TRUE
     ↓
digitalWrite(MOTOR, HIGH)
     ↓
LED ON
```

### STOP Sequence

```text
STOP Button
     ↓
digitalRead()
     ↓
motorON = FALSE
     ↓
digitalWrite(MOTOR, LOW)
     ↓
LED OFF
```

Variabel `motorON` digunakan untuk menyimpan status motor.

Ketika tombol **START** ditekan, ESP32 membaca input sebagai `HIGH`, kemudian mengubah nilai `motorON` menjadi `TRUE`. Status tersebut tetap tersimpan meskipun tombol START sudah dilepas.

Ketika tombol **STOP** ditekan, ESP32 membaca input sebagai `HIGH`, kemudian mengubah nilai `motorON` menjadi `FALSE`.

Setelah status `motorON` ditentukan, ESP32 menggunakan `digitalWrite()` untuk mengatur output LED:

- `motorON = TRUE` → LED menyala
- `motorON = FALSE` → LED mati

Konsep ini mensimulasikan **latching control**, yaitu kondisi output tetap aktif setelah perintah START diberikan dan baru berhenti ketika perintah STOP diberikan.

---

## 3. Hardware & Pin Configuration

| Component | GPIO | Function |
|---|---:|---|
| Green LED | GPIO 5 | Output / Motor Indicator |
| START Button | GPIO 22 | Input / START Command |
| STOP Button | GPIO 23 | Input / STOP Command |

### Input Configuration

Push button menggunakan konfigurasi:

```cpp
INPUT_PULLDOWN
```

Dengan konfigurasi ini, kondisi input secara default berada pada `LOW`. Ketika push button ditekan, input menerima tegangan `3.3V` sehingga terbaca sebagai `HIGH`.

### LED Configuration

LED digunakan sebagai simulasi indikator motor.

Rangkaian LED menggunakan resistor sebagai pembatas arus:

```text
GPIO 5
   │
Resistor 1kΩ
   │
LED (+)
LED (-)
   │
  GND
```

---

## 4. Operation

| Action | Result |
|---|---|
| Press START | LED turns ON |
| Release START | LED remains ON |
| Press STOP | LED turns OFF |
| Release STOP | LED remains OFF |

### Operating Sequence

```text
Initial State
     ↓
Motor OFF
     ↓
Press START
     ↓
Motor ON
     ↓
Release START
     ↓
Motor remains ON
     ↓
Press STOP
     ↓
Motor OFF
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
- Boolean Variable (`bool`)
- State Management
- `INPUT_PULLDOWN`
- Basic Latching Control
- Basic Industrial Control Logic

---
