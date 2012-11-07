#include <LiquidCrystal.h>
#include <dht.h>

LiquidCrystal lcd(4, 5, 10, 11, 12, 13);
DHT sensor = DHT();

void setup()
{
    lcd.begin(16, 2);
    sensor.attach(A5);
    delay(1000);
}

void loop()
{
    // метод update заставляет сенсор выдать текущие измерения
    sensor.update();
 
    switch (sensor.getLastError())
    {
        case DHT_ERROR_OK:
            char msg[128];
            lcd.clear();
            sprintf(msg, "T = %dC, H = %d%%", 
                    sensor.getTemperatureInt(), sensor.getHumidityInt());
            lcd.print(msg);
            lcd.setCursor(0, 1);
            break;
    }
    
    int lightLevel = analogRead(A4);
    int waterLevel = analogRead(A3);
    
    if(lightLevel >= 1000)
    {
        lightLevel = 999;
    }
    
    char msg2[128];
    
    sprintf(msg2, "L = %d  W = %d  ", lightLevel, waterLevel);
    lcd.print(msg2);
 
    delay(500);
}
