/*
    Written by Aqilla Rahman Musyaffa
*/

#include "LittleFS.h"

#include <ESP8266WiFi.h>
#include <Hash.h>
#include <SPI.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <Arduino_JSON.h>

#define HOTSPOT_SSID "UGTP BIO NETWORK"
#define HOTSPOT_PASSWORD "renewableenergy" 

IPAddress local_IP  (192, 168, 4, 20);
IPAddress gateaway  (192, 168, 4, 9);
IPAddress subnet    (255, 255, 255, 0);

String
sData[8],
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

AsyncWebServer server (80);
AsyncEventSource events ("/events");

JSONVar readings;

unsigned long lastTime = 0;
unsigned long timerDelay = 5000;

String message = "";

void initFS()
{
    if (!LittleFS.begin())
    {
        Serial.println ("Gagal Saat Mounting LittleFS");    
    }

    Serial.println ("Mounting LittleFS Sukses");
}

void initAP()
{
    if (!WiFi.softAPConfig (local_IP, gateaway, subnet))
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

String getSensorReadings()
{
    readings ["B1level"]        = B1level;
    readings ["B1pressure1"]    = B1pressure1;
    readings ["B1pressure2"]    = B1pressure2;
    readings ["B1volume"]       = B1volume;
    readings ["B1ph"]           = B1pH;
    readings ["B1CH4"]          = B1CH4;
    readings ["B1CO2"]          = B1CO2;           
    readings ["B1temperature"]  = B1temp;

    readings ["B2level"]        = B2level;
    readings ["B2pressure1"]    = B2pressure1;
    readings ["B2pressure2"]    = B2pressure2;
    readings ["B2volume"]       = B2volume;
    readings ["B2ph"]           = B2pH;
    readings ["B2CH4"]          = B2CH4;
    readings ["B2CO2"]          = B2CO2;           
    readings ["B2temperature"]  = B2temp;

    readings ["B3level"]        = B3level;
    readings ["B3pressure1"]    = B3pressure1;
    readings ["B3pressure2"]    = B3pressure2;
    readings ["B3volume"]       = B3volume;
    readings ["B3ph"]           = B3pH;
    readings ["B3CH4"]          = B3CH4;
    readings ["B3CO2"]          = B3CO2;           
    readings ["B3temperature"]  = B3temp;

    readings ["B4level"]        = B4level;
    readings ["B4pressure1"]    = B4pressure1;
    readings ["B4pressure2"]    = B4pressure2;
    readings ["B4volume"]       = B4volume;
    readings ["B4ph"]           = B4pH;
    readings ["B4CH4"]          = B4CH4;
    readings ["B4CO2"]          = B4CO2;           
    readings ["B4temperature"]  = B4temp;

    readings ["B5level"]        = B5level;
    readings ["B5pressure1"]    = B5pressure1;
    readings ["B5pressure2"]    = B5pressure2;
    readings ["B5volume"]       = B5volume;
    readings ["B5ph"]           = B5pH;
    readings ["B5CH4"]          = B5CH4;
    readings ["B5CO2"]          = B5CO2;           
    readings ["B5temperature"]  = B5temp;
    
    String jsonString = JSON.stringify (readings);
    return jsonString;
}

void setup() 
{
    Serial.begin(115200); 
       
    initAP();
    initFS();

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
}

void loop() 
{   
    if (Serial.available())
    {
        while (Serial.available() > 0)
        {
            type = Serial.readStringUntil('#');
            CH4 = Serial.readStringUntil('#');
            pressure1 = Serial.readStringUntil('#');
            pressure2 = Serial.readStringUntil('#');
            pH = Serial.readStringUntil('#');
            CO2 = Serial.readStringUntil('#');
            volume = Serial.readStringUntil('#');
            temp = Serial.readStringUntil('#');
            level = Serial.readStringUntil('#');
            //Serial.println ("C1");
        }

        if (type == "B1")
        {
            B1CH4 = CH4;
            B1pressure1 = pressure1;
            B1pressure2 = pressure2;
            B1pH = pH;
            B1CO2 = CO2;
            B1volume = volume;
            B1temp = temp;
            B1level = level;
        }

        if (type == "B2")
        {
            B2CH4 = CH4;
            B2pressure1 = pressure1;
            B2pressure2 = pressure2;
            B2pH = pH;
            B2CO2 = CO2;
            B2volume = volume;
            B2temp = temp;
            B2level = level;
        }

        if (type == "B3")
        {
            B3CH4 = CH4;
            B3pressure1 = pressure1;
            B3pressure2 = pressure2;
            B3pH = pH;
            B3CO2 = CO2;
            B3volume = volume;
            B3temp = temp;
            B3level = level;
        }

        if (type == "B4")
        {
            B4CH4 = CH4;
            B4pressure1 = pressure1;
            B4pressure2 = pressure2;
            B4pH = pH;
            B4CO2 = CO2;
            B4volume = volume;
            B4temp = temp;
            B4level = level;
        }

        if (type == "B5")
        {
            B5CH4 = CH4;
            B5pressure1 = pressure1;
            B5pressure2 = pressure2;
            B5pH = pH;
            B5CO2 = CO2;
            B5volume = volume;
            B5temp = temp;
            B5level = level;
        }

        //message.trim();
        
        /*
        if (message != "")
        {
            if (message.indexOf("B1") >= 0)
            {
                message = message.substring (3);
                int index = 0;
                for (int i=0; i<=message.length();i++)
                {
                    char delimiter = '#';
                    if (message [i] != delimiter)
                    {
                        sData [index] += message [i];
                        //Serial.println (data[i]);
                    }
                    else
                    {
                        index++;
                    }
                }
                
                B1CH4 = sData [0];
                B1pressure1 = sData [1];
                B1pressure2 = sData [2];
                B1pH = sData [3];
                B1CO2 = sData [4];
                B1volume = sData [5];
                B1temp = sData [6];
                B1level = sData [7];
            }

            if (message.indexOf("B2") >= 0)
            {
                message = message.substring (3);
                int index = 0;
                for (int i=0; i<=message.length();i++)
                {
                    char delimiter = '#';
                    if (message [i] != delimiter)
                    {
                        sData [index] += message [i];
                        //Serial.println (data[i]);
                    }
                    else
                    {
                        index++;
                    }
                }
                
                B2CH4 = sData [0];
                B2pressure1 = sData [1];
                B2pressure2 = sData [2];
                B2pH = sData [3];
                B2CO2 = sData [4];
                B2volume = sData [5];
                B2temp = sData [6];
                B2level = sData [7];
            }

            if (message.indexOf("B3") >= 0)
            {
                message = message.substring (3);
                int index = 0;
                for (int i=0; i<=message.length();i++)
                {
                    char delimiter = '#';
                    if (message [i] != delimiter)
                    {
                        sData [index] += message [i];
                        //Serial.println (data[i]);
                    }
                    else
                    {
                        index++;
                    }
                }
                
                B3CH4 = sData [0];
                B3pressure1 = sData [1];
                B3pressure2 = sData [2];
                B3pH = sData [3];
                B3CO2 = sData [4];
                B3volume = sData [5];
                B3temp = sData [6];
                B3level = sData [7];
            }

            if (message.indexOf("B4") >= 0)
            {
                message = message.substring (3);
                int index = 0;
                for (int i=0; i<=message.length();i++)
                {
                    char delimiter = '#';
                    if (message [i] != delimiter)
                    {
                        sData [index] += message [i];
                        //Serial.println (data[i]);
                    }
                    else
                    {
                        index++;
                    }
                }
                
                B4CH4 = sData [0];
                B4pressure1 = sData [1];
                B4pressure2 = sData [2];
                B4pH = sData [3];
                B4CO2 = sData [4];
                B4volume = sData [5];
                B4temp = sData [6];
                B4level = sData [7];
            }

            if (message.indexOf("B5") >= 0)
            {
                message = message.substring (3);
                int index = 0;
                for (int i=0; i<=message.length();i++)
                {
                    char delimiter = '#';
                    if (message [i] != delimiter)
                    {
                        sData [index] += message [i];
                        //Serial.println (data[i]);
                    }
                    else
                    {
                        index++;
                    }
                }
                
                B5CH4 = sData [0];
                B5pressure1 = sData [1];
                B5pressure2 = sData [2];
                B5pH = sData [3];
                B5CO2 = sData [4];
                B5volume = sData [5];
                B5temp = sData [6];
                B5level = sData [7];
            }
        }
        */
    }

    if ((millis() - lastTime) > timerDelay)
    {
        events.send ("Ping", NULL, millis());
        events.send (getSensorReadings().c_str(), "new_readings", millis());
        lastTime = millis();
    }
    
    Serial.println ("C2");
    
    delay (1000); 
}
