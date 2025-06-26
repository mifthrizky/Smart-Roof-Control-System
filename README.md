# Smart Roof Control System (Weather Guard)
Prototipe sistem atap cerdas yang dirancang untuk membuka dan menutup secara otomatis maupun manual. Proyek ini bertujuan untuk memberikan solusi praktis dalam melindungi area seperti jemuran, kanopi, atau teras dari perubahan cuaca yang tiba-tiba, terutama hujan.

Kelompok 7 : 
- Miftah Rizky Alamsyah (223443062)
- Fadhlurrofiq Nurrohmat (223443054)
- Muhammad Rafi Alghifari (223443063)

Kunjungi [Demonstrasi Alat]([https://www.google.com](https://drive.google.com/file/d/1WKvHODm6A_32iK1DwhoApPgoQzdo7A9f/view))

__📖 Latar Belakang__
Seringkali kita meninggalkan jemuran atau barang-barang penting di area terbuka, dan khawatir saat hujan turun tiba-tiba. Sistem ini lahir dari kebutuhan akan otomasi sederhana untuk mengatasi masalah tersebut. Dengan adanya mode otomatis dan manual, pengguna mendapatkan perlindungan sekaligus fleksibilitas penuh atas atap pelindung mereka.

__✨ Fitur Utama__
Kontrol Ganda: Dapat dioperasikan dalam dua mode:
Otomatis: Atap akan menutup sendiri saat sensor mendeteksi hujan.
Manual: Pengguna dapat membuka atau menutup atap kapan saja menggunakan tombol.
Deteksi Hujan Akurat: Menggunakan Rain Sensor Module untuk pemicu mode otomatis yang andal.
Pergerakan Presisi: Digerakkan oleh Motor Stepper melalui mekanisme roda gigi, memastikan pergerakan yang mulus dan terkontrol.
Berbasis ESP8266: Menggunakan mikrokontroler populer yang memiliki kapabilitas Wi-Fi untuk potensi pengembangan IoT di masa depan.

__🛠️ Komponen yang Dibutuhkan__

![Screenshot 2025-06-26 150928](https://github.com/user-attachments/assets/bf3cb691-89c2-4a60-be95-105068f51c8a)



__🔌 Wiring Diagram__

![image](https://github.com/user-attachments/assets/4e174480-78c7-4961-84a8-6e8c2eaaf632)

__📱Tampilan Aplikasi__

![Screenshot 2025-06-26 151540](https://github.com/user-attachments/assets/793f9d09-53b1-4311-a1b8-1aed948e4e20)



__⚙️ Cara Kerja Sistem__
Inisialisasi: Saat sistem dinyalakan, atap berada dalam posisi default (terbuka) dan sistem siaga.
Mode Otomatis:
Sistem terus memantau output dari Rain Sensor Module.
Jika sensor mendeteksi air, ESP8266 akan mengirim perintah ke driver ULN2003 untuk menggerakkan motor stepper dan menutup atap.
Mode Manual:
Jika tombol "Tutup" ditekan, ESP8266 akan menggerakkan motor untuk menutup atap, mengabaikan kondisi sensor untuk sementara.
Jika tombol "Buka" ditekan, ESP8266 akan menggerakkan motor untuk membuka atap.

__🚀 Instalasi & Penyiapan__
Rakit Sirkuit: Susun semua komponen pada breadboard atau PCB sesuai dengan diagram koneksi di atas.
Siapkan Arduino IDE:
Install Arduino IDE di komputer Anda.
Tambahkan ESP8266 Board Manager ke Arduino IDE melalui menu File > Preferences. URL: http://arduino.esp8266.com/stable/package_esp8266com_index.json
Buka Tools > Board > Boards Manager, cari "esp8266" dan install.
Install Library: Jika kode Anda memerlukan library khusus untuk motor stepper, install melalui Sketch > Include Library > Manage Libraries....
Upload Kode:
Buka file kode .ino proyek ini.
Pilih board yang sesuai (misalnya: "NodeMCU 1.0 (ESP-12E Module)").
Pilih Port COM yang benar.
Klik tombol Upload.

__🔧 Cara Penggunaan__
Setelah instalasi selesai dan sistem menyala:

Biarkan sistem berjalan untuk perlindungan otomatis. Saat hujan terdeteksi, atap akan menutup sendiri.
Tekan tombol "Buka" untuk membuka atap secara manual.
Tekan tombol "Tutup" untuk menutup atap secara manual kapan pun Anda mau.
