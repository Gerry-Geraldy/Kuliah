// Studi kasus yang saya buat adalah sebuah pendeteksi suhu suatu kamar
// Jika kamar tersebut berada pada suhu 25 sampai 30 celcius maka akan menampilkan led lampu berwarna kuning
// Jika kamar tersebut berada pada  24 celcius kebawah maka akan menampilkan led lampu berwarna biru
// jika kamar tersebut berada pada suhu 30 celcius keatas maka akan menampilkan led lampu berwarna merah
// Dan saya juga memakai fungsi analog write dalam melakukan set pada led lampu yang menyala pada suhu tertentu
// untuk fungsi digital write saya memakai nya untuk mematikan lampu pada kondisi2 yang sudah saya set

#include <OneWire.h>
#include <DallasTemperature.h>

// Hubungkan sensor DS18B20 ke pin A1
OneWire oneWire(4);
DallasTemperature sensors(&oneWire);

// Hubungkan lampu LED ke pin 11 (Merah), 10 (Kuning), dan 9 (Biru)
int redLedPin = 11;
int yellowLedPin = 10;
int blueLedPin = 9;

void setup()
{
  sensors.begin();
  pinMode(redLedPin, OUTPUT);
  pinMode(yellowLedPin, OUTPUT);
  pinMode(blueLedPin, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  sensors.requestTemperatures(); // Baca suhu dari sensor DS18B20

  // Baca suhu dalam derajat Celsius
  float temperatureC = sensors.getTempCByIndex(0);

  // Konversi suhu ke Fahrenheit, Reamur, dan Kelvin
  float temperatureF = (temperatureC * 9.0 / 5.0) + 32;
  float temperatureR = temperatureC * 4.0 / 5.0;
  float temperatureK = temperatureC + 273.15;

  // Cek jika suhu di luar batas
  if (temperatureC > 25.0 && temperatureC < 30.0)
  {
    digitalWrite(redLedPin, LOW);
    analogWrite(yellowLedPin, map(temperatureC, 25, 30, 0, 255));
    digitalWrite(blueLedPin, LOW);
  }
  else if (temperatureC < 24.0)
  {
    digitalWrite(redLedPin, LOW);
    digitalWrite(yellowLedPin, LOW);
    analogWrite(blueLedPin, map(temperatureC, 20, 25, 0, 255));
  }
  else
  {
    digitalWrite(redLedPin, 255);
    digitalWrite(yellowLedPin, LOW);
    analogWrite(blueLedPin, LOW);
  }

  // Tampilkan suhu dalam berbagai skala pada Serial Monitor
  Serial.print("Suhu (Celsius): ");
  Serial.print(temperatureC);
  Serial.println(" °C");

  Serial.print("Suhu (Fahrenheit): ");
  Serial.print(temperatureF);
  Serial.println(" °F");

  Serial.print("Suhu (Reamur): ");
  Serial.print(temperatureR);
  Serial.println(" °Re");

  Serial.print("Suhu (Kelvin): ");
  Serial.print(temperatureK);
  Serial.println(" K");

  delay(2000);
}
