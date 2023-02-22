#include "LittleFS.h"

#include <ESP8266WiFi.h>
#include <Hash.h>
//#include <FirebaseESP8266.h>
#include <SoftwareSerial.h>
#include <SPI.h>
#include <RF24.h>
#include <nRF24l01.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <Arduino_JSON.h>
#include <LiquidCrystal_I2C.h>

IPAddress local_IP  (192, 168, 4, 22);
IPAddress gateway  (192, 168, 4, 9);
IPAddress subnet    (255, 255, 255, 0);

/*
IPAddress local_IP  (192, 168, 1, 184);
IPAddress gateaway  (192, 168, 1, 1);
IPAddress subnet    (255, 255, 0, 0);
*/

//SCK D5
//MISO D6
//MOSI D7
#define CE_nRF D4
#define CSN_nRF D8

#define RX_BT D3
#define TX_BT D0

#define FIREBASE_HOST "https://biodegester-default-rtdb.firebaseio.com/"
#define FIREBASE_AUTH "16o2iUiCAQj2DLpfm4YtaNg0vjXKcyL1kqPFLENf"
#define WIFI_SSID "UGTECHNOPARK"
#define WIFI_PASSWORD "ugtp2021"
#define HOTSPOT_SSID "Biodigester"
#define HOTSPOT_PASSWORD "Digesterbio"

const byte address [6] = "00001";
float sensor [6];

float press1, finalphValue, press2;
int liquidLevel, temperature, lperMinute;
String kondisiTangki;

AsyncWebServer server (80);
AsyncEventSource events ("/events");

//FirebaseData firebaseData;
JSONVar readings;
RF24 radioRx (CE_nRF, CSN_nRF);
SoftwareSerial BT (RX_BT, TX_BT); //RX-D3, TX-D0
LiquidCrystal_I2C lcd = LiquidCrystal_I2C (0x25, 16, 2);

unsigned long lastTime = 0;
unsigned long timerDelay = 5000;

void initFS()
{
    if (!LittleFS.begin())
    {
        Serial.println ("Gagal Saat Mounting LittleFS");    
    }

    Serial.println ("Mounting LittleFS Sukses");
}

void initWiFi()
{
    if (!WiFi.config (local_IP, gateway, subnet))
    {
        Serial.println ("Gagal Saat Konfigurasi STA WiFi");
    }

    WiFi.begin (WIFI_SSID, WIFI_PASSWORD);
    
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print (".");
        delay (1000);   
    }
    
    Serial.println ("\n");
    Serial.print ("Tersambung pada...");
    Serial.println (WIFI_SSID);
    Serial.print ("Alamat IP : ");
    Serial.println (WiFi.localIP());

    lcd.setCursor (0, 0);
    lcd.print ("Alamat IP :");
    lcd.setCursor (0, 1);
    lcd.print (" " + local_IP);
    
}

/*
void initAP()
{
    if (!WiFi.softAPConfig (local_IP, gateway, subnet))
    {
        Serial.println ("Gagal Saat Konfigurasi STA Hotspot");
    }

    WiFi.softAP (HOTSPOT_SSID, HOTSPOT_PASSWORD);
    
    Serial.print ("\n");
    Serial.print ("Alamat IP Access Point    : ");
    Serial.println (WiFi.softAPIP());
    Serial.print ("Alamat IP Lokal           : ");
    Serial.println (WiFi.localIP());
}
*/

String getSensorReadings()
{
    readings ["temperature"]    = String (temperature);
    readings ["pressure"]       = String (press1);
    readings ["ph"]             = String (finalphValue);
    readings ["level"]          = String (liquidLevel);
    readings ["pressure2"]      = String (press2);
    readings ["flow"]           = String (lperMinute);
    String jsonString = JSON.stringify (readings);
    return jsonString;
}

void setup() 
{
    Serial.begin(9600); 
    BT.begin(9600);
    
    lcd.init();
    lcd.backlight();
    
    //initAP();
    initFS();

    radioRx.begin ();
    radioRx.openReadingPipe (0, address);
    radioRx.setPALevel (RF24_PA_MAX);
    radioRx.startListening ();
    
    //Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
    //Firebase.reconnectWiFi(true);

    
    server.on ("/", HTTP_GET, [] (AsyncWebServerRequest *request)
    {
        request -> send (LittleFS, "/index.html", "text/html");
    });

    server.serveStatic ("/", LittleFS, "/");

    server.on ("/readings", HTTP_GET, [] (AsyncWebServerRequest *request)
    {
        String json = getSensorReadings();
        request -> send (200, "application/json", json);
        json = String();   
    });

    events.onConnect ([] (AsyncEventSourceClient *client)
    {
        if (client -> lastId())
        {
            Serial.printf ("Client Terhubung Kembali, ID Terakhir Pesan : %u\n", 
            client -> lastId());           
        }

        client -> send ("Hello", NULL, millis(), 5000);
    });

    server.addHandler (&events);

    server.begin();

    IPAddress IP = WiFi.softAPIP();
    lcd.setCursor (0, 0);
    lcd.print ("Alamat IP :");
    lcd.setCursor (0, 1);
    lcd.print ("  ");
    lcd.print (IP);
    
    
    delay(1000);
}

void loop() 
{
    if (radioRx.available())
    {
        radioRx.read (sensor, sizeof (sensor));
        Serial.println ("============= DATA FROM NANO =============");
        Serial.print ("Temperatur Tangki 1      = ");
        Serial.println (sensor[0]);         //Temperatur
        Serial.print ("Tekanan Tangki 1         = ");
        Serial.println (sensor[1]);         //Tekanan 1
        Serial.print ("pH Limbah Tangki 1       = ");
        Serial.println (sensor[2]);         //PH
        Serial.print ("Level Limbah Tangki 1    = ");
        Serial.println (sensor[3]);         //Level
        Serial.print ("Tekanan Tangki 2         = ");
        Serial.println (sensor[4]);         //Tekanan 2
        Serial.print ("Laju Gas Tangki 1        = ");
        Serial.println (sensor[5]);         //Laju Gas
        lcd.setCursor (0, 0);
        lcd.print ("SINYAL TERHUBUNG");
        Serial.println ("Connected");        
        delay (1000);
    }
    else
    {
        lcd.setCursor (0, 0);
        lcd.print ("SINYAL  TERPUTUS");
        Serial.println ("Disconnected");
        delay (1000);
    }

    temperature     = int (sensor [0]);
    press1          = sensor [1];   
    finalphValue    = sensor [2];
    liquidLevel     = int (sensor [3]);
    press2          = sensor [4];
    lperMinute      = int (sensor [5]);

    if (liquidLevel == 1)
    {
        kondisiTangki = "Penuh";
    }
    else
    {
        kondisiTangki = "Kosong";
    }

    
    if ((millis() - lastTime) > timerDelay)
    {
        events.send ("Ping", NULL, millis());
        events.send (getSensorReadings().c_str(), "new_readings", millis());
        lastTime = millis();
    }
    
    
    /*
    Serial.println ("=============DATA FINAL=============");
    Serial.println (temperature);       //Temperatur
    Serial.println (press1);            //Tekanan 1
    Serial.println (finalphValue);      //PH
    Serial.println (kondisiTangki);     //Tangki
    Serial.println (press2);            //Tekanan 2
    Serial.println (lperMinute);        //Laju Gas
    */

    
    //=============Bluetooth data=============
    BT.print (kondisiTangki);       //Tangki
    BT.print("#");
    BT.print (temperature);         //Temperatur
    BT.print("#");
    BT.print (press1);              //Tekanan 1
    BT.print("#");
    BT.print (press2);              //Tekanan 2
    BT.print("#");
    BT.print (finalphValue);        //PH
    BT.print("#");
    BT.println (lperMinute);        //Laju Gas
    delay(1000);
    

    /*
    if (BT.available())
    {
        char data_received;
        data_received = BT.read();
        if (data_received == '1')
        {
            Serial.println ("KONEKSI OK");
        }
    }
    */
    
/* NOTE:
 *  To upload value, command is ===> Firebase.setInt(firebaseData, "path", variable);
 *  Example                     ===>  Firebase.setInt(firebaseData, "/data", val);
 */
/* 
    //=========================SEND FLOW=========================
    if (Firebase.setInt(firebaseData, "/Nilai/Aliran gas", lperMinute)) 
    {    
        // On successful Write operation, function returns 1  
        Serial.println("Value Uploaded Successfully");
        delay(1000);
    }
    else 
    {        
        Serial.println(firebaseData.errorReason());
    }

    //=========================SEND TEMPERATURE=========================
    if (Firebase.setInt(firebaseData, "/Nilai/Temperatur", temperature)) 
    {   
        // On successful Write operation, function returns 1  
        Serial.println("Value Uploaded Successfully");
        delay(1000);
    }
    else 
    {        
        Serial.println(firebaseData.errorReason());
    }

    //=========================SEND PH=========================
    if (Firebase.setFloat(firebaseData, "/Nilai/Ph", finalphValue)) 
    {    
        // On successful Write operation, function returns 1  
        Serial.println("Value Uploaded Successfully");
        delay(1000);
    }
    else 
    {        
        Serial.println(firebaseData.errorReason());
    }

    //=========================SEND PRESSURE 1=========================
    if (Firebase.setFloat(firebaseData, "/Nilai/Tekanan gas tangki", press1)) 
    {    
        // On successful Write operation, function returns 1  
        Serial.println("Value Uploaded Successfully");
        delay(1000);
    }
    else 
    {        
        Serial.println(firebaseData.errorReason());
    }

    //=========================SEND WASTE LEVEL=========================
    if (Firebase.setString(firebaseData, "/Nilai/Kondisi isi tangki", kondisiTangki)) 
    {    
        // On successful Write operation, function returns 1  
        Serial.println("Value Uploaded Successfully");
        delay(1000);
    }
    else 
    {        
        Serial.println(firebaseData.errorReason());
    }

    //=========================SEND PRESSURE 2=========================
    if (Firebase.setFloat(firebaseData, "/Nilai/Tekanan gas tabung", press2)) 
    {    
        // On successful Write operation, function returns 1  
        Serial.println("Value Uploaded Successfully");
        delay(1000);
    }
    else 
    {        
        Serial.println(firebaseData.errorReason());
    }
*/
    delay(1000);
}
