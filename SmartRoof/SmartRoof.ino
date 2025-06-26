#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>
#include <Stepper.h>

// ==================== Firebase Setup ====================
#define FIREBASE_HOST "https://rain-monitoring-ac319-default-rtdb.asia-southeast1.firebasedatabase.app/"
#define FIREBASE_AUTH "EioMxjO6CpFu9gonBnCdL3jzn0rTYMMVZKhRh75H"
FirebaseData firebaseData;

// ==================== WiFi ====================
const char* ssid = "test";         // Ganti dengan SSID WiFi Anda
const char* password = "pqr9865p"; // Ganti dengan password WiFi

// ==================== Motor Stepper ====================
const int stepsPerRevolution = 200;
Stepper myStepper(stepsPerRevolution, D1, D3, D2, D4);

// ==================== Tombol Manual ====================
#define button1 digitalRead(D5) == LOW //tutup
#define button2 digitalRead(D6) == LOW //buka

// ==================== Sensor Hujan ====================
const int hujanPin = A0;

// ==================== Variabel Status ====================
int hujan = 0;
int cerah = 1;
int aman = 2;
int kondisi = cerah;

int rotasi = 7000;
String statusPintu = "Tertutup"; // default awal

void setup() {
  Serial.begin(9600);

  pinMode(D5, INPUT_PULLUP);
  pinMode(D6, INPUT_PULLUP);
  pinMode(hujanPin, INPUT);

  myStepper.setSpeed(100);

  // Koneksi WiFi
  WiFi.begin(ssid, password);
  Serial.print("Menghubungkan ke WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nTerhubung ke WiFi");

  // Koneksi ke Firebase
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
}

void putarStepper(int totalStep) {
  int langkahKecil = 200;
  int arah = (totalStep > 0) ? 1 : -1;
  int total = abs(totalStep);

  for (int i = 0; i < total; i += langkahKecil) {
    myStepper.step(langkahKecil * arah);
    delay(50);
  }

  // Update status pintu ke Firebase
  statusPintu = (totalStep > 0) ? "Tertutup" : "Terbuka";
  Firebase.setString(firebaseData, "/WeatherGuard/statusPintu", statusPintu);
}

void loop() {
  int hujanValue = analogRead(hujanPin);
  Serial.print("RainHumidity: ");
  Serial.println(hujanValue);

  Serial.print("Cuaca: ");
  if (kondisi == cerah) {
    Serial.println("Cerah");
  } else if (kondisi == hujan) {
    Serial.println("Hujan");
  } else {
    Serial.println("Aman");
  }

  // Kirim nilai hujan ke Firebase
  Firebase.setInt(firebaseData, "/WeatherGuard/hujanValue", hujanValue);

  // Otomatisasi buka/tutup berdasarkan sensor hujan
  if (hujanValue <= 600 && kondisi == cerah) {
    kondisi = hujan;
    Serial.println("Hari Hujan - Menutup Atap");
    putarStepper(rotasi);
    
  } else if (hujanValue >= 600 && kondisi == hujan) {
    kondisi = cerah;
    Serial.println("Hari Cerah - Membuka Atap");
    putarStepper(-rotasi);
  }

  // Tombol manual buka
  if (button1) {
    putarStepper(rotasi);
    delay(300); // debounce sederhana
  }
  // Tombol manual tutup
  if (button2) {
    putarStepper(-rotasi);
    delay(300); // debounce sederhana
  }



  // Baca perintah dari Firebase (kontrol dari aplikasi)
  if (Firebase.getString(firebaseData, "/WeatherGuard/perintah")) {
    String perintah = firebaseData.stringData();
    perintah.replace("\"", "");
    perintah.replace("\\", "");
    perintah.trim(); 
    Serial.println("Data perintah dari Firebase: " + perintah);
    
    if (perintah == "Buka") {
      Serial.println("Perintah Buka diterima, memutar stepper...");
      putarStepper(-rotasi);
      // Reset perintah setelah diproses
      if (Firebase.setString(firebaseData, "/WeatherGuard/perintah", "kosong")) {
        Serial.println("Perintah reset berhasil.");
      } else {
        Serial.print("Gagal reset perintah: ");
        Serial.println(firebaseData.errorReason());
      }
    } else if (perintah == "Tutup") {
      Serial.println("Perintah Tutup diterima, memutar stepper...");
      putarStepper(rotasi);
      // Reset perintah setelah diproses
      if (Firebase.setString(firebaseData, "/WeatherGuard/perintah", "kosong")) {
        Serial.println("Perintah reset berhasil.");
      } else {
        Serial.print("Gagal reset perintah: ");
        Serial.println(firebaseData.errorReason());
      }
    }
  }

  // Update kondisi ke Firebase
  String kondisiText = (kondisi == cerah) ? "Cerah" : (kondisi == hujan) ? "Hujan" : "Aman";
  Firebase.setString(firebaseData, "/WeatherGuard/cuaca", kondisiText);

  delay(500);
}
