/*
    Written by Aqilla Rahman Musyaffa
*/

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <max6675.h>
#include <DS3231.h>
#include <SPI.h>
#include <LoRa.h>
#include <MQ135.h>

/* LoRa to MEGA 2560 interface (By Shield)
 * NSS/CS   D10
 * RESET    D9
 */

/*
 * ANALOG
 * Methane              A8
 * Pressure 1           A9
 * Pressure 2           A10
 * pH                   A11
 * CO2                  A12
 */

 /* DIGITAL
  * Volume (Flow)       D22
  * Temperature (SCK)   D24
  * Temperature (CS)    D26
  * Temperature (SO)    D28
  * Level               D30
  */

  /*
   * SDA                D20
   * SCL                D21
   * GND                GND
   */

#define methaneMQ2          A8
#define pressureSensor1     A9
#define pressureSensor2     A10
#define phSensor            A11
#define carbonMQ135         A12

const byte volumeSensor     = 22;
const byte tempSCK          = 24;
const byte tempCS           = 26;
const byte tempSO           = 28;
const byte levelSensor      = 30;

const byte strobeRelay      = 31;
const byte valveRelay       = 33;
const byte motorRelay       = 35;
const byte pumpRelay        = 37;

String flag                 = "B4";

int methaneGas              = 0;

int liquidLevel             = 0;        //LEVEL LIMBAH TANGKI 1
String kondisiTangki;                   //LEVEL LIMBAH TANGKI 1

int pressureAnalog1;
int pressureAnalog2;
float pressure1;                        //TEKANAN TANGKI 1
float pressure2;                        //TEKANAN TANGKI 2

int temperatureValue;                   //TEMPERATUR TANGKI 1

float phAnalog;
float finalphValue          = 0.0;      //PH TANGKI 1

volatile int flowFrequency;
int lperMinute, vol         = 0;        //LAJU DAN VOLUME GAS TANGKI 2
unsigned long currentTime;
unsigned long cloopTime;

const byte onHour   = 16;
const byte onMin    = 0;
const byte offHour  = 16;
const byte offMin   = 30;

String loraMessage = "";

MAX6675 thermocouple(tempSCK, tempCS, tempSO);

LiquidCrystal_I2C lcd1 = LiquidCrystal_I2C (0x27, 20, 4);
LiquidCrystal_I2C lcd2 = LiquidCrystal_I2C (0x25, 20, 4);

DS3231 rtc (SDA, SCL);
Time t;

MQ135 CO2Sensor (carbonMQ135);

void flow()
{
    flowFrequency++;
}

void setup() 
{
    Serial.begin (9600);

    
    if (!LoRa.begin (915E6))
    {
        Serial.println ("LoRa Gagal Dimulai");
        while (1);
    }
    
    //rtc.begin();
    
    Serial.println ("C0");
    
    lcd1.init();
    lcd2.init();
    lcd1.backlight();
    lcd2.backlight();

    lcd1.setCursor (0, 0);
    lcd1.print ("Tangki    : ");
    lcd1.setCursor (0, 1);
    lcd1.print ("Tekanan   : ");
    lcd1.setCursor (17, 1);
    lcd1.print ("Bar");
    lcd1.setCursor (0, 2);
    lcd1.print ("Temperatur:   ");
    lcd1.setCursor (18, 2);
    lcd1.print ((char)223);
    lcd1.print ("C");
    lcd1.setCursor (0, 3);
    lcd1.print ("pH Limbah : ");
    
    lcd2.setCursor (0, 0);
    lcd2.print ("Metana : ");
    lcd2.setCursor (17, 0);
    lcd2.print ("PPM");
    lcd2.setCursor (0, 2);
    lcd2.print ("Tekanan: ");
    lcd2.setCursor (17, 2);
    lcd2.print ("Bar");
    lcd2.setCursor (0, 1);
    lcd2.print ("CO2    : ");
    lcd2.setCursor (17, 1);
    lcd2.print ("PPM"); 
    lcd2.setCursor (0, 3);
    lcd2.print ("Volume : ");
    lcd2.setCursor (15, 3);
    lcd2.print ("Liter");

    Serial.println ("C1");

    pinMode (methaneMQ2, INPUT);        //MQ2 Sensor
    pinMode (pressureSensor1, INPUT);   //Pressure Sensor 1
    pinMode (pressureSensor2, INPUT);   //Pressure Sensor 2
    pinMode (phSensor, INPUT);          //pH Sensor
    pinMode (carbonMQ135, INPUT);       //MQ135 Sensor

    pinMode (volumeSensor, INPUT);      //Flow Sensor
    pinMode (levelSensor, INPUT);       //Level Sensor
    
    pinMode (strobeRelay, OUTPUT);      //Strobe Lamp Relay
    pinMode (valveRelay, OUTPUT);       //Valve Relay
    pinMode (motorRelay, OUTPUT);       //AC Motor Relay 
    
    digitalWrite (volumeSensor, HIGH);
    attachInterrupt (0, flow, RISING);
    sei();
    currentTime = millis();
    cloopTime = currentTime;
    delay (1000);
    
    Serial.println ("C2");
}

void loop() 
{
    //t = rtc.getTime();
    
    Serial.println ("C3");  

    currentTime = millis();
    if (currentTime >= (cloopTime + 1000))
    {
        cloopTime = currentTime;
        //Pulse Frequency (Hz) = 11Q, Q is flow rate in L/Min.
        //L/Minute  = Pulse Frequency / 11
        //L/Hour    = Pulse Frequency / 11 * 60
        //Volume    = L/Minute / 60;
        lperMinute = (flowFrequency/11);
        vol = vol + (lperMinute/11);
        lcd2.setCursor (9, 3);
        lcd2.print (vol);
        flowFrequency = 0;
    }
    else
    {
        lcd2.setCursor (9, 3);
        lcd2.print (vol);
    }
    
    Serial.println ("C4");
    
    liquidLevel = digitalRead (levelSensor);
    if (liquidLevel == 1)
    {
        digitalWrite (motorRelay, LOW);
        lcd1.setCursor (12, 0);
        lcd1.print ("Kosong");
        kondisiTangki = "Penuh";
        Serial.println (liquidLevel);
    }
    else
    {
        digitalWrite (motorRelay, HIGH);
        lcd1.setCursor (12, 0);
        lcd1.print ("Penuh ");
        kondisiTangki = "Kosong";
        Serial.println (liquidLevel);
    }

    Serial.println ("C5");

    if (t.hour == onHour && t.min == onMin)
    {
        digitalWrite (motorRelay, LOW);
    }
    else if (t.hour == offHour && t.min == offMin)
    {
        digitalWrite (motorRelay, HIGH);
    }
    
    methaneGas = analogRead (methaneMQ2);
    float CH4Voltage = methaneGas * (5.0 / 1023.0);
    int methanePPM = (15000 / 1024) * ((CH4Voltage / 5) * 1024);
    
    int carbonPPM = CO2Sensor.getPPM();
    
    pressureAnalog1     = analogRead (pressureSensor1);
    pressureAnalog2     = analogRead (pressureSensor2);
    pressure1           = pressure (pressureAnalog1);
    pressure2           = pressure (pressureAnalog2);
    
    temperatureValue = thermocouple.readCelsius();

    phAnalog = analogRead (phSensor);
    finalphValue = (-0.0693 * phAnalog) + 7.3855;

    if ((finalphValue >= 6.5 && finalphValue <= 7.5)  || (temperatureValue >= 20 && temperatureValue <= 30))
    {
        digitalWrite (valveRelay, LOW);
    }
    else
    {
        digitalWrite (valveRelay, HIGH);
    }

    if (pressure1 >= 0.4)
    {
        digitalWrite (strobeRelay, LOW);
    }
    else
    {
        digitalWrite (strobeRelay, HIGH);
    }

    Serial.println ("C6");
    
    lcd1.setCursor (12, 1);
    lcd1.print (pressure1);
    //Serial.println (press1);

    lcd1.setCursor (14, 2);
    lcd1.print (int (temperatureValue));
    //Serial.println (temperatureValue);

    lcd1.setCursor (12, 3);
    lcd1.print (finalphValue);
    //Serial.println (finalphValue);
    
    lcd2.setCursor (9, 0);
    lcd2.print ("       ");
    lcd2.setCursor (9, 0);
    lcd2.print (methanePPM);    
    //Serial.println (methanePPM);
    
    lcd2.setCursor (9, 2);
    lcd2.print (pressure2);
    //Serial.print (press2);

    lcd2.setCursor (9, 1);
    lcd2.print ("       ");
    lcd2.setCursor (9, 1);
    lcd2.print (carbonPPM);
    //Serial.println (carbonPPM);

    LoRa.beginPacket();
    LoRa.print(flag);
    LoRa.print("#");
    LoRa.print(String (methanePPM));
    LoRa.print("#");
    LoRa.print(String (pressure1));
    LoRa.print("#");
    LoRa.print(String (pressure2));
    LoRa.print("#");
    LoRa.print(String (finalphValue));
    LoRa.print("#");
    LoRa.print(String (carbonPPM));
    LoRa.print("#");
    LoRa.print(String (vol));
    LoRa.print("#");
    LoRa.print(String (temperatureValue));
    LoRa.print("#");
    LoRa.print(String (liquidLevel));
    LoRa.print("#");
    LoRa.endPacket();
    
    delay (1750);
    
    Serial.println ("C7");
}

float pressure (int pressureValue)
{
    float voltage = (pressureValue*5.0)/1024.0;
    float pressurePascal = (3.0*((float)voltage-0.47))*1000000.0;
    float pressureBar = pressurePascal/10e5;
    return pressureBar; 
}
