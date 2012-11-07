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
            break;
        case DHT_ERROR_START_FAILED_1:
            Serial.println("Error: start failed (stage 1)");
            break;
        case DHT_ERROR_START_FAILED_2:
            Serial.println("Error: start failed (stage 2)");
            break;
        case DHT_ERROR_READ_TIMEOUT:
            Serial.println("Error: read timeout");
            break;
        case DHT_ERROR_CHECKSUM_FAILURE:
            Serial.println("Error: checksum error");
            break;
    }
 
    delay(500);
}
