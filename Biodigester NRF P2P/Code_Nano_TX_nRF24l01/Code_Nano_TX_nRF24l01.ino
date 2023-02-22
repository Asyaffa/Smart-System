
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <max6675.h>
//#include <SoftwareSerial.h>
#include <DS3231.h>
#include <SPI.h>
#include <RF24.h>
#include <nRF24l01.h>

#define pressureSensor1 A0
#define pressureSensor2 A7
#define phSensor A6

#define strobeRelay A1
#define waterRelay A2
const byte motorRelay = 7;
const byte valveRelay = 8;

//SCK = D13
//MISO = D12
//MOSI = D11
const byte CE_nRF = 9;
const byte CSN_nRF = 10;
const byte address [6] = "00001";
float sensor [6];

const byte levelSensor  = 3;
float liquidLevel         = 0;            //LEVEL LIMBAH TANGKI 1
String kondisiTangki;                   //LEVEL LIMBAH TANGKI 1

int pressureValue1;
int pressureValue2;
float press1;                           //TEKANAN TANGKI 1
float press2;                           //TEKANAN TANGKI 2

const byte thermoSO  = 4;
const byte thermoCS  = 5;
const byte thermoSCK = 6;
float temperatureValue;                 //TEMPERATUR TANGKI 1

int adcValue            = 0;
float finalphValue      = 0.0;          //PH TANGKI 1

const byte flowSensor           = 2;
volatile int flowFrequency;
float lperHour, lperMinute, vol = 0.0;  //LAJU DAN VOLUME GAS TANGKI 2
unsigned long currentTime;
unsigned long cloopTime;

const byte onHour   = 16;
const byte onMin    = 0;
const byte offHour  = 16;
const byte offMin   = 30;

RF24 radioTx (CE_nRF, CSN_nRF);

MAX6675 thermocouple(thermoSCK, thermoCS, thermoSO);

//SoftwareSerial toNodeMCU (9, 8); //RX-D9, TX-D8

LiquidCrystal_I2C lcd1 = LiquidCrystal_I2C (0x27, 20, 4);
LiquidCrystal_I2C lcd2 = LiquidCrystal_I2C (0x25, 20, 4);

DS3231 rtc (SDA, SCL);
Time t;

void flow()
{
    flowFrequency++;
}

void setup() 
{
    Serial.begin (9600);

    rtc.begin();
  
    lcd1.init();
    lcd2.init();
    lcd1.backlight();
    lcd2.backlight();

    lcd1.setCursor (0, 0);
    lcd1.print ("Tangki     : ");
    lcd1.setCursor (0, 1);
    lcd1.print ("Tekanan    : ");
    lcd1.setCursor (17, 1);
    lcd1.print ("Bar");
    lcd1.setCursor (0, 2);
    lcd1.print ("Temperatur :   ");
    lcd1.setCursor (18, 2);
    lcd1.print ((char)223);
    lcd1.print ("C");
    lcd1.setCursor (0, 3);
    lcd1.print ("pH Limbah  : ");
    
    lcd2.setCursor (0, 0);
    lcd2.print ("Waktu  :");
    lcd2.setCursor (0, 1);
    lcd2.print ("Tekanan: ");
    lcd2.setCursor (17, 1);
    lcd2.print ("Bar");
    lcd2.setCursor (0, 2);
    lcd2.print ("Laju   : ");
    lcd2.setCursor (15, 2);
    lcd2.print ("L/Min");   
    lcd2.setCursor (0, 3);
    lcd2.print ("Volume : ");
    lcd2.setCursor (15, 3);
    lcd2.print ("Liter");
    
    radioTx.begin();
    radioTx.openWritingPipe(address);
    radioTx.setPALevel (RF24_PA_MIN);
    radioTx.stopListening();

    //Serial.println ("C1");
    
    pinMode (levelSensor,INPUT);        //Level Sensor
    pinMode (pressureSensor1, INPUT);   //Pressure Sensor 1
    pinMode (pressureSensor2, INPUT);   //Pressure Sensor 2
    pinMode (phSensor, INPUT);          //pH Sensor
    pinMode (motorRelay, OUTPUT);       //Relay Motor AC
    pinMode (valveRelay, OUTPUT);       //Relay Valve Gas
    pinMode (strobeRelay, OUTPUT);      //Relay Lampu 
    pinMode (waterRelay, OUTPUT);       //Relay 2

    /*
    digitalWrite (motorRelay, HIGH);    //Berputar
    digitalWrite (valveRelay, LOW);     //Tertutup
    digitalWrite (waterRelay, HIGH);    //Air Mengalir
    digitalWrite (blitzRelay, LOW);     //Lampu Mati
    //Serial.println ("C1");
    */
    
    pinMode (flowSensor, INPUT);        //Flow Sensor
    digitalWrite (flowSensor, HIGH);
    attachInterrupt (0, flow, RISING);
    sei();
    currentTime = millis();
    cloopTime = currentTime;
    delay (1000);
    
    //Serial.println ("C2");
}

void loop() 
{
    t = rtc.getTime();
    
    //Serial.println ("C3");

    lcd2.setCursor (8, 0);
    lcd2.print (rtc.getTimeStr());
    lcd2.print (" WIB");  
    
    //Serial.println ("C4");

    currentTime = millis();
    if (currentTime >= (cloopTime + 1000))
    {
        cloopTime = currentTime;
        //Pulse Frequency (Hz) = 7.5Q, Q is flow rate in L/Min.
        //L/Minute  = Pulse Frequency / 7.5Q
        //L/Hour    = Pulse Frequency x 60 / 7.5Q
        //Volume    = L/Minute / 60;
        lperMinute = (flowFrequency/7.5);
        lcd2.setCursor (9, 2);
        lcd2.print (lperMinute);
        vol = vol + (lperMinute/60);
        lcd2.setCursor (9, 3);
        lcd2.print (vol);
        flowFrequency = 0;
    }
    else
    {
        lcd2.setCursor (9, 2);
        lcd2.print (flowFrequency);
        lcd2.setCursor (9, 3);
        lcd2.print (vol);
    }
    
    //Serial.println ("C5");
    
    liquidLevel = digitalRead (levelSensor);
    if (liquidLevel == 1)
    {
        digitalWrite (motorRelay, HIGH);
        lcd1.setCursor (13, 0);
        lcd1.print ("Penuh ");
        kondisiTangki = "Penuh";
    }
    else
    {
        digitalWrite (motorRelay, LOW);
        lcd1.setCursor (13, 0);
        lcd1.print ("Kosong");
        kondisiTangki = "Kosong";
    }

    //Serial.println ("C4");
    
    if (t.hour == onHour && t.min == onMin)
    {
        digitalWrite (motorRelay, LOW);
    }
    else if (t.hour == offHour && t.min == offMin)
    {
        digitalWrite (motorRelay, HIGH);
    }
    
    pressureValue1 = analogRead (pressureSensor1);
    pressureValue2 = analogRead (pressureSensor2);
    float press1 = pressure (pressureValue1);
    float press2 = pressure (pressureValue2);
    
    temperatureValue = thermocouple.readCelsius();
    
    adcValue = analogRead (phSensor);
    finalphValue = -(-0.0139*adcValue) + 7.7851;

    if ((finalphValue >= 6.5 && finalphValue <= 7.5)  || (temperatureValue >= 20 && temperatureValue <= 30))
    {
        digitalWrite (valveRelay, LOW);
    }
    else
    {
        digitalWrite (valveRelay, HIGH);
    }

    if (press1 >= 0.4)
    {
        analogWrite (strobeRelay, 255);
    }
    else
    {
        analogWrite (strobeRelay, 0);
    }

    sensor [0] = temperatureValue;
    sensor [1] = press1;    
    sensor [2] = finalphValue;    
    sensor [3] = liquidLevel;
    sensor [4] = press2;
    sensor [5] = lperMinute;
    
    radioTx.write (sensor, sizeof (sensor));

    Serial.println ("Data Transmitted");

        
    Serial.println ("====================DATA TRANSMITTED====================");
    //Serial.println (sensor[0]);
    Serial.println (sensor[1]);
    //Serial.println (sensor[2]);
    //Serial.println (sensor[3]);
    Serial.println (sensor[4]);
    //Serial.println (sensor[5]);
    Serial.println ("========================================================");

    //Serial.println ("C5");
    
    lcd1.setCursor (13, 1);
    lcd1.print (press1);
    //Serial.println (press1);

    lcd1.setCursor (15, 2);
    lcd1.print (int (temperatureValue));
    //Serial.println (temperatureValue);

    lcd1.setCursor (13, 3);
    lcd1.print (finalphValue);
    //Serial.println (finalphValue);
    
    lcd2.setCursor (9, 1);
    lcd2.print (press2);
    //Serial.println (press2);

    /*
    String message = "";
    while (toNodeMCU.available() > 0)
    {
        message += char(toNodeMCU.read());
    }
    message.trim();
    if (message == "Ya")
    {
        kirim();
    }
    message = "";
    */
    
    delay(1000);
}

float pressure (int pressureValue)
{
    float voltage = (pressureValue*5.0)/1024.0;
    float pressurePascal = (3.0*((float)voltage-0.47))*1000000.0;
    float pressureBar = pressurePascal/10e5;
    return pressureBar; 
}

/*
void kirim()
{
    // Tangki#Temperatur#Tekanan1#Tekanan2#pH#Aliran
    String data = tangki + "#" + String(temperatureValue) + "#" + String(press1) + "#" + String(press2) + "#" + String(finalphValue) + "#" + String(lperMinute); 
    Serial.println (data);
    toNodeMCU.println (data);
}
*/

/*
void TXdataSensor()
{
    sensor [0] = temperatureValue;
    sensor [1] = press1;    
    sensor [2] = finalphValue;    
    sensor [3] = liquidLevel;
    sensor [4] = press2;
    sensor [5] = lperMinute;
    
    radioTx.write (sensor, sizeof (sensor));

    Serial.println ("Data Transmitted");

        
    Serial.println ("====================DATA TRANSMITTED====================");
    //Serial.println (sensor[0]);
    Serial.println (sensor[1]);
    //Serial.println (sensor[2]);
    //Serial.println (sensor[3]);
    Serial.println (sensor[4]);
    //Serial.println (sensor[5]);
    Serial.println ("========================================================");
    
}
*/
