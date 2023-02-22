/*
    Written by Aqilla Rahman Musyaffa
*/

#include <SPI.h>
#include <LoRa.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

String message = "";

String
type, IP,
level, pressure1, pressure2, volume, pH, CH4, CO2, temp,  
B1level, B2level, B3level, B4level, B5level, 
B1pressure1, B2pressure1, B3pressure1, B4pressure1, B5pressure1,
B1pressure2, B2pressure2, B3pressure2, B4pressure2, B5pressure2,
B1volume, B2volume, B3volume, B4volume, B5volume,
B1pH, B2pH, B3pH, B4pH, B5pH,
B1CH4, B2CH4, B3CH4, B4CH4, B5CH4,
B1CO2, B2CO2, B3CO2, B4CO2, B5CO2,
B1temp, B2temp, B3temp, B4temp, B5temp;

LiquidCrystal_I2C lcd = LiquidCrystal_I2C (0x27, 20, 4);

void setup() 
{
    //Serial.println ("C1");
    
    Serial.begin(9600); 
    Serial3.begin (115200);

    lcd.init();
    lcd.backlight();

    lcd.setCursor (0, 0);
    lcd.print ("B-1");
    lcd.setCursor (4, 0);
    lcd.print ("B-2");
    lcd.setCursor (9, 0);
    lcd.print ("B-3");
    lcd.setCursor (14, 0);
    lcd.print ("B-4");
    lcd.setCursor (18, 0);
    lcd.print ("B-5");
    lcd.setCursor (0, 2);
    lcd.print ("  UGTP BIO NETWORK  ");
    lcd.setCursor (0, 3);
    lcd.print ("    192.168.4.20    ");
        
    //Serial.println ("C2");
    
    if (!LoRa.begin (915E6))
    {
        Serial.println ("LoRa Gagal Dimulai");
        while (1);
        lcd.setCursor (2, 1);
        lcd.print ("!LoRa  Terputus!");
    }
    
    else
    {
        Serial.println ("LoRa Mulai");
        lcd.setCursor (2, 1);
        lcd.print ("!LoRa Terhubung!");
    }

    //Serial.println ("C3");
    
    LoRa.receive();
}

void loop() 
{   
    //Serial.println ("C4");
    
    int packetSize = LoRa.parsePacket();
    if (packetSize)
    {
        while (LoRa.available())
        {
            type = LoRa.readStringUntil ('#');
            Serial3.print (type);
            Serial3.print ('#');
            CH4 = LoRa.readStringUntil ('#');
            Serial3.print (CH4);
            Serial3.print ('#');
            pressure1 = LoRa.readStringUntil ('#');
            Serial3.print (pressure1);
            Serial3.print ('#');
            pressure2 = LoRa.readStringUntil ('#');
            Serial3.print (pressure2);
            Serial3.print ('#');
            pH = LoRa.readStringUntil ('#');
            Serial3.print (pH);
            Serial3.print ('#');
            CO2 = LoRa.readStringUntil ('#');
            Serial3.print (CO2);
            Serial3.print ('#');
            volume = LoRa.readStringUntil ('#');
            Serial3.print (volume);
            Serial3.print ('#');
            temp = LoRa.readStringUntil ('#');
            Serial3.print (temp);
            Serial3.print ('#');
            level = LoRa.readStringUntil ('#');
            Serial3.print (level);
            Serial3.print ('#');
        }

    delay (1000);

    //Serial.println ("C5");
    }
}
