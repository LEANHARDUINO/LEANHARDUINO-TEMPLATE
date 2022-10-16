/*
pin lcd_I2C GND --> pin arduino GND.
pin lcd_I2C VCC --> pin arduino OUT 5V.
pin lcd_I2C SDA --> pin arduino A4.
pin lcd_I2C SCL --> pin arduino A5.
*/
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SimpleKalmanFilter.h>   //thu vien ham loc nhieu.
SimpleKalmanFilter filter(0.001, 0.01, 0.001);    //khoi tao gia tri loc.
LiquidCrystal_I2C lcd(0x3F, 20, 4);  //ping lcd 0x3F.
int offset = 0;
float dataRough = A0;
float dataFilter;
// int dennen = 13;  // bat den nen lcd va den chan so D13.
// int nutnhan = 12;
// int thoigian = 0;
void setup() {
  lcd.init();       // khoi tao lcd.
  lcd.backlight();  //bat den nen.
  pinMode(dataRough, INPUT);
  // pinMode(dennen, OUTPUT);
  // pinMode(nutnhan, INPUT);
}

void loop() {
  dataRough = analogRead(A0);
  double voltage = map(dataRough, 0, 1023, 0, 500) + offset;  // offset bu vao phan thap phan
  voltage /= 100;                                        // chia cho 100 de nhan duoc phan thap phan
  dataFilter = filter.updateEstimate(dataRough);    // loc nhieu cho tin hieu dau vao tu chan A0.
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Voltage: ");
  lcd.setCursor(8, 0);
  lcd.print(voltage);
  lcd.setCursor(12, 0);
  lcd.println("V");
  delay(100);
  // khoi tao che do tu tat den nen.
  /*
  thoigian++;
  if (thoigian >= 100) {    //thoi gian tat den nen.
    digitalWrite(dennen, LOW);
  } else digitalWrite(dennen, HIGH);
  int trangthainut = digitalRead(nutnhan);
  if (trangthainut == HIGH) { thoigian = 0; }
  */
}