#include <LiquidCrystal.h>

LiquidCrystal lcd(8,9,4,5,6,7);
void setup() {
lcd.begin(16,2);
lcd.setCursor(0,0);
}

void loop() {
lcd.setCursor(4,0);
lcd.print("Benjamin");
}
