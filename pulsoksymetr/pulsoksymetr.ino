#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include "MAX30100_PulseOximeter.h"
#define OKRES_WYSWIETLANIA 200
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  
uint8_t saturacja;
float tetno;
PulseOximeter max30100;
uint32_t poprzedniOdczyt = 0;

void setup() {
  lcd.begin(16,2);
  lcd.setCursor(0,0);
  lcd.print("Pulsoksymetr");
  //Serial.begin(115200);
  //Serial.print("inicjalizacja pulsoksymetru");
  max30100.begin();
  max30100.setIRLedCurrent(MAX30100_LED_CURR_50MA); //ustawienie pradu diody podczerwonej
  delay(2000);
}

void loop() {
  max30100.update();
  if (millis() - poprzedniOdczyt > OKRES_WYSWIETLANIA) {
    saturacja = max30100.getSpO2();
    tetno = max30100.getHeartRate();
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Tetno: ");
    lcd.print(tetno);
    lcd.print(" bpm");
    lcd.setCursor(0,1);
    lcd.print("Saturacja: ");
    lcd.print(saturacja);
    lcd.print("%");
    
    poprzedniOdczyt = millis();
  }
}
