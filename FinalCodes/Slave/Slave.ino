const int fan1 = 9;
const int fan2 = 10;

#include <LiquidCrystal.h>
#include <SoftwareSerial.h>
SoftwareSerial mySerial(6, 7);
int controlPwm = 0;
int temperatureValue = 0;
int humidityValue = 0;
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {

  lcd.begin(16, 2);
  TCCR1A = 0; // undo the configuration done by...
  TCCR1B = 0; // ...the Arduino core library
  TCNT1 = 0; // reset timer
  TCCR1A = _BV(COM1A1) | _BV(COM1B1) | _BV(WGM11); //Undo default timers
  TCCR1B = _BV(WGM13) | _BV(CS10); //for pins 9 & 10
  ICR1 = 320;
  pinMode(fan1, OUTPUT);
  pinMode(fan2, OUTPUT);
  OCR1A = 0; //set pwm to 0 out of 320 on pin 9
  OCR1B = 0; //set pwm to 0 out of 320 on pin 10
  mySerial.begin(9600);
  Serial.begin(9600);

}

void loop() {
  if (mySerial.available() < 0)
    return;
  String R = mySerial.readString();
  controlPwm = splitString(R, ':', 0).toInt();
  temperatureValue = splitString(R, ':', 1).toInt();
  humidityValue = splitString(R, ':', 2).toInt();
  Serial.print(controlPwm);
  Serial.print(":");
  Serial.print(temperatureValue);
  Serial.print(":");
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp = ");
  lcd.print(temperatureValue);
  Serial.println(humidityValue);
  controlFan(controlPwm);
}



void controlFan(int controlPwm) {
  switch (controlPwm) {
    case 0:
      OCR1A = 0;
      OCR1B = 0;
      break;
    case 1:
      OCR1A = 64;
      OCR1B = 64;
      break;
    case 2:
      OCR1A = 128;
      OCR1B = 128;
      break;
    case 3:
      OCR1A = 192;
      OCR1B = 192;
      break;
    case 4:
      OCR1A = 256;
      OCR1B = 256;
      break;
    case 5:
      OCR1A = 320;
      OCR1B = 320;
      break;
    default:
      OCR1A = 0;
      break;
  }
}


String splitString(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length() - 1;

  for (int i = 0; i <= maxIndex && found <= index; i++)
  {
    if (data.charAt(i) == separator || i == maxIndex)
    {
      found++;
      strIndex[0] = strIndex[1] + 1;
      strIndex[1] = (i == maxIndex) ? i + 1 : i;
    }
  }
  return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}
