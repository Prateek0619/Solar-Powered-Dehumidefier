
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <dht11.h>
#include <SoftwareSerial.h>
SoftwareSerial mySerial(D6, D7); //Rx, Tx

dht11 DHT11;
BlynkTimer timer;
char auth[] = "99BsKs1_JGPHXivZrO_DfsLQ3QsgELND";
char ssid[] = "POCO F1";
char pass[] = "123456789";

volatile int pinValue;

BLYNK_WRITE(V1)
{
  pinValue = param.asInt();
}

void setup()
{
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  pinMode(D2, INPUT);
  DHT11.attach(D2);
  pinMode(D5, OUTPUT);
  digitalWrite(D5, HIGH);
  mySerial.begin(9600);
}

void loop()
{
  delay(1000);
  sendSerialData(pinValue);
  Blynk.run();
  timer.run();
}


void sendSerialData(int pin) {
  int chk = DHT11.read();
  int temp = DHT11.temperature;
  int hum = DHT11.humidity;
  Blynk.virtualWrite(V0, temp);
  Blynk.virtualWrite(V2, hum);
  Serial.print(pin);
  Serial.print(":");
  Serial.print(temp);
  Serial.print(":");
  Serial.println(hum);
  mySerial.print(pin);
  mySerial.print(':');
  mySerial.print(temp);
  mySerial.print(':');
  mySerial.print(hum);
  mySerial.println(':');
}
