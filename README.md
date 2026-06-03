# Final Project - Sistem Mikroprosesor dan Mikrokontroller

Repository ini berisi implementasi kode dan laporan untuk tugas Final Project mata kuliah **Sistem Mikroprosesor dan Mikrokontroller**.

**Mahasiswa:** Yuke Brilliant Hestiavin (5024241016)  
**Dosen Pengampu:** Eko Pramunanto, S.T., M.T.  
**Departemen:** Teknik Komputer, ITS Surabaya

---

## Struktur Repository

```
FP/
├── Clock 4 Digit/          # Kode dan rangkaian jam digital 4-digit dengan dimming
├── Knight Rider Led/       # Kode dan rangkaian lampu berjalan dengan kontrol LDR
├── Wifi Scan/              # Kode pemindaian jaringan WiFi asinkron
└── Laporan/                # Laporan LaTeX (2 file laporan)
    ├── laporan_1_clock.tex
    ├── laporan_2_lampu_berjalan.tex
    └── assets/
        ├── code/           # Source code (di-include dari laporan)
        └── img/            # Gambar (wiring diagram, screenshot, dll)
```

---

## Proyek yang Diimplementasikan

### 1. Jam Digital 4-Digit dengan Fitur Dimming
- **Komponen:** ESP32, RTC DS1307, TM1637, Potensiometer
- **Fitur:**
  - Menampilkan waktu real-time dari RTC DS1307
  - Kontrol kecerahan (dimming) menggunakan potensiometer
  - Komunikasi I2C untuk RTC dan TM1637
  - ADC 12-bit untuk membaca nilai analog potensiometer

### 2. Lampu Berjalan (Knight Rider) dengan Kontrol Cerdas
- **Komponen:** ESP32, 3 LED, 2 Potensiometer, Sensor LDR
- **Fitur:**
  - Efek lampu berjalan (Knight Rider) dengan PWM
  - Kontrol kecepatan dan kecerahan menggunakan 2 potensiometer
  - Sensor LDR untuk aktivasi otomatis berdasarkan kondisi cahaya
  - Pemindaian WiFi asinkron (non-blocking) setiap 10 detik

### 3. WiFi Network Scanner
- **Komponen:** ESP32 dengan modul WiFi
- **Fitur:**
  - Pemindaian jaringan WiFi secara asinkron
  - Menampilkan SSID, RSSI, Channel, dan status enkripsi
  - Tidak memblokir eksekusi tugas lain (non-blocking)

---

## Kompilasi Laporan LaTeX

Laporan ditulis dalam format LaTeX dengan spesifikasi:
- **Ukuran kertas:** A4
- **Margin:** Atas 3cm, Bawah 3cm, Kanan 3cm, Kiri 4cm
- **Line spacing:** 1.15
- **Format cover:** Judul → Logo → Mata Kuliah → Dosen → Nama/NRP → Departemen

### Cara Kompilasi

**Menggunakan Overleaf:**
1. Upload seluruh folder `Laporan/` ke Overleaf
2. Pastikan struktur folder `assets/` juga ter-upload
3. Compile file `.tex` menggunakan engine `pdflatex`

**Menggunakan LaTeX Lokal:**
```bash
cd Laporan
pdflatex laporan_1_clock.tex
pdflatex laporan_2_lampu_berjalan.tex
```

### Dependencies LaTeX
- `graphicx` - untuk gambar
- `listings` - untuk syntax highlighting kode
- `xcolor` - untuk warna
- `hyperref` - untuk hyperlink
- `setspace` - untuk line spacing
- `float` - untuk posisi gambar/tabel
- `multirow` - untuk tabel dengan baris yang di-merge

---

## Komponen yang Digunakan

| Komponen | Fungsi |
|----------|--------|
| ESP32 | Mikrokontroler utama |
| RTC DS1307 | Modul waktu real-time (I2C) |
| TM1637 | Driver display 7-segment 4-digit |
| Potensiometer 10kΩ | Input analog untuk kontrol kecerahan/kecepatan |
| LED (Merah/Kuning/Hijau) | Output lampu |
| Resistor 220Ω | Pembatas arus LED |
| Sensor LDR | Detektor intensitas cahaya |
| Resistor 10kΩ | Pembagi tegangan untuk LDR |

---

## Konsep yang Dipelajari

- **Pulse Width Modulation (PWM):** Kontrol kecerahan LED dan kecepatan animasi
- **Analog to Digital Converter (ADC):** Membaca nilai analog dari potensiometer dan sensor
- **Komunikasi I2C:** Interface dengan modul RTC DS1307
- **Sensor LDR:** Kontrol otomatis berbasis intensitas cahaya
- **WiFi Connectivity:** Pemindaian jaringan asinkron pada ESP32
- **Multiple ADC Channels:** Membaca beberapa input analog secara bersamaan

---

## Lisensi

Proyek ini dibuat untuk keperluan akademik mata kuliah Sistem Mikroprosesor dan Mikrokontroller, Departemen Teknik Komputer, ITS Surabaya.
