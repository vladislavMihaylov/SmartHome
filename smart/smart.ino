#include <LiquidCrystal.h>

LiquidCrystal lcd(4, 5, 10, 11, 12, 13);

void setup()
{
    lcd.begin(16, 2);
    lcd.print("Hello world!");
}

void loop()
{
}
