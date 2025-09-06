#define BLYNK_TEMPLATE_ID "TMPL2zwnUm09s"
#define BLYNK_TEMPLATE_NAME "Siddharth's Weather Sensor"
#define BLYNK_AUTH_TOKEN "5ca-KS2RpCeI9pER22G_Y5BnQ6TPc9Rm"

// including the required libraries
#include <WiFi.h> // for the ESP8266 module
#include <BlynkSimpleEsp32.h> // for blynk cloud stream
#include "DHT.h" // for the DHT11 temperature and humidity sensor

#define DHTPIN 4 // GPIO4 on NodeMCU - data pin
#define DHTTYPE DHT11 // defines the kind of sensor


char ssid[] = "ATTSAK";
char pass[] = "angrypear322";

// creates DHT11 and Blynk object instances
DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;

void sendSensorData() {
  float hum = dht.readHumidity();
  float tempF = dht.readTemperature(true); // Fahrenheit
  if (isnan(hum) || isnan(tempF)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  Blynk.virtualWrite(V5, tempF); // Temperature
  Blynk.virtualWrite(V6, hum);   // Humidity
  Serial.print("Humidity: ");
  Serial.print(hum);
  Serial.print("%  Temp: ");
  Serial.print(tempF);
  Serial.println("°F");
}


void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  dht.begin();
  timer.setInterval(2000L, sendSensorData); // Every 2 seconds

}

void loop() {
  // put your main code here, to run repeatedly:

  Blynk.run();
  timer.run();

}
