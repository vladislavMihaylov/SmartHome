#include <LiquidCrystal.h>
#include <dht.h>

LiquidCrystal lcd(4, 5, 10, 11, 12, 13);
DHT sensor = DHT();
int lightSignalPin = 8;
int buttonPin = 9;
int globalTemperature = 0;

char *info[] = {"   Very cold   ", "cold" , "norm", "Poloneck", " \x4D\x61\xB9\xBa\x79 \xB8 \xBF\x70\xB8\xBA\x6F", " \x4D\x61\xB9\xBa\x79 \xB8 \xC1\x6F\x70\xBF\xC3"};


void showInfo()
{
    lcd.print(info[globalTemperature / 5]);
}

void setup()
{
    Serial.begin(9600);
    lcd.begin(16, 2);
    sensor.attach(A5);
    pinMode(lightSignalPin, OUTPUT);
    pinMode(buttonPin, INPUT);
    digitalWrite(buttonPin, HIGH);
    delay(1000);
}

void loop()
{   
    int but = digitalRead(buttonPin);
    if(but == 1)
    {
      lcd.clear();
      lcd.print("     O""\xE3""e""\xBD\xC4"":   ");
      lcd.setCursor(0, 1);
      showInfo();
      //delay(1000);
    }
    

    // метод update заставляет сенсор выдать текущие измерения
    sensor.update();
 
    switch (sensor.getLastError())
    {
        case DHT_ERROR_OK:
            char msg[128];
            
            globalTemperature = sensor.getTemperatureInt();
            int humidity = sensor.getHumidityInt();
            sprintf(msg, "T = %dC, H = %d%%", globalTemperature, humidity);
            if(but == 0)
            {
               lcd.clear();
               lcd.print(msg);
            }
            lcd.setCursor(0, 1);
            
            break;
    }
    
    int lightLevel = analogRead(A4);
    int waterLevel = analogRead(A3);
    
    if(lightLevel >= 1000)
    {
        lightLevel = 999;
    }
    if(lightLevel >= 700)
    {
        digitalWrite(lightSignalPin, HIGH);
    }
    if(lightLevel < 700)
    {
        digitalWrite(lightSignalPin, LOW);
    }
    
    char msg2[128];
    
    sprintf(msg2, "L = %d  W = %d  ", lightLevel, waterLevel);
    if(but == 0)
    {
        lcd.print(msg2);
    }
    delay(500);
}
