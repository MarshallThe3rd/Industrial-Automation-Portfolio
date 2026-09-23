<img width="807" height="516" alt="image" src="https://github.com/user-attachments/assets/1efdd19f-6ea1-46f3-abdc-9a6d488a9e95" /># Project 03: Conveyor Timer

## 1. Project Overview

Pada Project 03 atau **Conveyor Timer**, saya ingin membuat sebuah sistem conveyor yang dapat berjalan selama waktu tertentu.

Sistem dimulai dengan menekan tombol **START**. Setelah cycle aktif, conveyor akan tetap berjalan meskipun tombol START sudah dilepas. Setelah timer mencapai waktu yang telah ditentukan, cycle akan otomatis berhenti sehingga conveyor ikut berhenti.

Project ini dibuat menggunakan **TIA Portal dan S7-PLCSIM** sebagai tahap awal sebelum nantinya diterapkan pada sistem conveyor secara fisik.

---

## 2. Control Logic

Pada project ini saya mempelajari beberapa konsep dasar **Ladder Logic** pada PLC, yaitu:

- Normally Open (NO)
- Normally Closed (NC)
- Coil
- Self-Holding / Latching
- TON Timer
- Input, Memory, dan Output

### Normally Open (NO)

NO digunakan sebagai kondisi logika yang akan meneruskan jalur ketika kondisi input atau memory bernilai **TRUE**.

### Normally Closed (NC)

NC memiliki logika yang berlawanan dengan NO. Jalur akan diteruskan ketika kondisi input atau memory bernilai **FALSE**.

Dengan demikian, NO dan NC sama-sama digunakan sebagai kondisi logika, tetapi memiliki kondisi aktif yang berlawanan.

### Coil

Coil digunakan sebagai hasil dari suatu rangkaian logika. Nilai Coil ditentukan berdasarkan kondisi logika yang berada sebelumnya.

Pada project ini, Coil digunakan untuk mengatur `Cycle_Active` dan `Conveyor_Motor`.

---

## 3. Self-Holding

Salah satu konsep penting yang saya pelajari pada project ini adalah **Self-Holding** atau **Latching**.

Self-Holding digunakan agar suatu kondisi tetap aktif setelah tombol START dilepas.

Pada penggunaan nyata, tombol START hanya perlu ditekan sesaat. Ketika tombol dilepas, input START akan kembali FALSE secara otomatis karena tombol kembali ke posisi awal.

Namun, `Cycle_Active` tetap TRUE karena menggunakan rangkaian Self-Holding.

### Alur Self-Holding

```text
START ditekan
      ↓
START = TRUE
      ↓
Cycle_Active = TRUE
      ↓
START dilepas
      ↓
START = FALSE
      ↓
Cycle_Active tetap TRUE
```

Dengan konsep ini, tombol START hanya digunakan untuk memberikan perintah awal, sedangkan `Cycle_Active` menunjukkan bahwa proses sedang berjalan.

---

## 4. System State

Pada project ini terdapat dua kondisi utama:

### READY

Sistem berada dalam kondisi siap untuk memulai cycle.

```text
Cycle_Active = FALSE
Conveyor_Motor = FALSE
```

### RUNNING

Sistem sedang menjalankan cycle.

```text
Cycle_Active = TRUE
Conveyor_Motor = TRUE
```

**Timer bukan merupakan state.** Timer hanya digunakan untuk menentukan berapa lama sistem berada dalam kondisi RUNNING.

Dengan kata lain:

- **State** menunjukkan kondisi sistem.
- **Timer** menentukan durasi suatu kondisi.

---

## 5. Ladder Program

Program PLC dibagi menjadi beberapa **Network** agar setiap bagian logic memiliki fungsi yang lebih jelas.

### Network 1 - Cycle Control

Network pertama digunakan untuk mengatur `Cycle_Active`.

Secara sederhana, logic yang digunakan adalah:

```text
START OR Cycle_Active
        AND
    NOT STOP
        AND
    NOT Timer.Q
        ↓
   Cycle_Active
```

Network ini menangani:

- Perintah START
- Self-Holding
- STOP
- Penghentian cycle ketika timer selesai

<img width="698" height="297" alt="image" src="https://github.com/user-attachments/assets/a6b21b8b-51de-4581-b350-2cada7b47b71" />

### Network 2 - Conveyor Timer

Network kedua menggunakan **TON (Timer On-Delay)**.

`Cycle_Active` digunakan sebagai input timer.

Timer yang digunakan memiliki nilai:

```text
PT = T#5s
```

Artinya, ketika `Cycle_Active` TRUE, timer akan menghitung selama **5 detik**.

Setelah 5 detik tercapai, `Timer.Q` menjadi TRUE.

<img width="692" height="275" alt="image" src="https://github.com/user-attachments/assets/dac6b613-97b3-459d-a884-469e6826751c" />

### Network 3 - Conveyor Motor

Network ketiga digunakan untuk menghubungkan `Cycle_Active` dengan output conveyor.

Ketika:

```text
Cycle_Active = TRUE
```

maka:

```text
Conveyor_Motor = TRUE
```

Ketika:

```text
Cycle_Active = FALSE
```

maka:

```text
Conveyor_Motor = FALSE
```

<img width="702" height="207" alt="image" src="https://github.com/user-attachments/assets/55bd3fdd-8464-43cf-b2b8-6bb490a5e399" />

---

## 6. System Flow

Secara keseluruhan, sistem bekerja dengan alur:

```text
READY
  ↓
START
  ↓
RUNNING
  ↓
Timer 5 detik
  ↓
Cycle OFF
  ↓
Motor OFF
  ↓
READY
```

Selain penghentian otomatis melalui timer, sistem juga dapat dihentikan menggunakan tombol STOP sebelum timer selesai.

Alurnya:

```text
RUNNING
  ↓
STOP
  ↓
READY
```

---

## 7. Input and Output

| Tag | Address | Type | Function |
|---|---|---|---|
| `Start_Button` | `%I0.0` | Bool | Memulai cycle |
| `Stop_Button` | `%I0.1` | Bool | Menghentikan cycle |
| `Cycle_Active` | `%M0.0` | Bool | Menyimpan status cycle |
| `Conveyor_Motor` | `%Q0.0` | Bool | Mengontrol output conveyor |
| `Timer_Conveyor` | - | TON | Mengatur durasi cycle |

---

## 8. Simulation

Project ini diuji menggunakan **S7-PLCSIM** sebelum diterapkan pada hardware fisik.

### Initial State

Pada kondisi awal:

```text
Start_Button = FALSE
Stop_Button = FALSE
Cycle_Active = FALSE
Conveyor_Motor = FALSE
```

Sistem berada pada kondisi **READY**.

> **Screenshot:** akan ditambahkan.

### Start Cycle

Ketika tombol START ditekan:

```text
Start_Button = TRUE
Cycle_Active = TRUE
Conveyor_Motor = TRUE
Timer mulai menghitung
```

> **Screenshot:** akan ditambahkan.

### Start Button Released

Setelah tombol START dilepas:

```text
Start_Button = FALSE
Cycle_Active = TRUE
Conveyor_Motor = TRUE
```

Cycle tetap berjalan karena menggunakan **Self-Holding**.

> **Screenshot:** akan ditambahkan.

### Timer Completed

Setelah timer mencapai 5 detik:

```text
Timer.Q = TRUE
Cycle_Active = FALSE
Conveyor_Motor = FALSE
```

Sistem kembali ke kondisi **READY**.

> **Screenshot:** akan ditambahkan.

### Manual Stop

Jika tombol STOP ditekan sebelum timer selesai:

```text
RUNNING
  ↓
STOP
  ↓
READY
```

`Cycle_Active` dan `Conveyor_Motor` akan menjadi FALSE.

> **Screenshot:** akan ditambahkan.

---

## 9. Learning Outcomes

Melalui Project 03 ini, saya mempelajari bagaimana sebuah sistem PLC dapat menggabungkan input, Ladder Logic, memory, timer, dan output untuk membentuk suatu proses otomatis.

Beberapa konsep yang saya pelajari:

- Memahami fungsi dasar NO, NC, dan Coil.
- Memahami hubungan antara input dan output pada PLC.
- Memahami konsep Self-Holding atau Latching.
- Memahami perbedaan antara `Start_Button` dan `Cycle_Active`.
- Memahami penggunaan TON Timer.
- Memahami konsep state sederhana seperti READY dan RUNNING.
- Memahami bagaimana PLC menjalankan program melalui scan cycle.
- Memahami bagaimana logic sederhana START/STOP dapat dikembangkan menjadi proses otomatis menggunakan timer.

---

## 10. Development Plan

Project ini akan dikembangkan secara bertahap:

1. Membuat Ladder Logic.
2. Melakukan simulasi menggunakan S7-PLCSIM.
3. Menguji seluruh kondisi sistem.
4. Menentukan hardware yang diperlukan.
5. Membuat physical conveyor.
6. Menghubungkan controller dengan hardware.
7. Melakukan pengujian pada physical system.
8. Membuat dokumentasi dan demonstration video.

Tahap simulasi dilakukan terlebih dahulu untuk memastikan logic PLC telah berjalan sesuai dengan rancangan sebelum diterapkan pada perangkat keras.

---

## 11. Documentation

### Ladder Logic

Screenshot Ladder Logic akan ditambahkan.

### PLCSIM

Screenshot simulasi akan ditambahkan.

### Physical Conveyor

Foto physical conveyor akan ditambahkan setelah tahap hardware selesai.

### Demonstration Video

Video demonstration akan ditambahkan setelah sistem selesai dibuat.

---

## 12. Project Status

### Completed

- [x] Membuat project S7-1200 pada TIA Portal
- [x] Membuat Ladder Logic
- [x] Membuat Self-Holding
- [x] Menggunakan TON Timer
- [x] Melakukan simulasi menggunakan S7-PLCSIM
- [x] Menguji START dan STOP
- [x] Menguji automatic stop setelah timer selesai
- [x] Menguji cycle secara berulang

### Next Development

- [ ] Menambahkan dokumentasi screenshot
- [ ] Menentukan hardware conveyor
- [ ] Membuat physical conveyor
- [ ] Menghubungkan controller dengan hardware
- [ ] Melakukan pengujian physical system
- [ ] Membuat video demonstration

---

## 13. Project Goal

Tujuan dari project ini adalah memahami bagaimana PLC dapat digunakan untuk mengontrol suatu proses secara otomatis menggunakan **Ladder Logic, Self-Holding, Timer, dan State sederhana**.

Project ini menjadi salah satu tahap pembelajaran untuk memahami dasar:

- PLC Programming
- Control Logic
- Industrial Automation
- Automatic Sequence Control

Setelah logic berhasil diuji melalui simulasi, project akan dikembangkan menjadi **physical conveyor system** untuk menguji penerapan logic pada perangkat keras secara langsung.
