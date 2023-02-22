/*
    Written by Aqilla Rahman Musyaffa
    
    Based on:
    > https://github.com/unreeeal/ESP/tree/master/ESP-RFID-GOOGLE
*/

#include <SPI.h>
#include <MFRC522.h>
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <LiquidCrystal_I2C.h>
#include <elapsedMillis.h>

#define SS_PIN D10
#define RST_PIN D2  

#define keypadInput A0

elapsedMillis keypadReadMillis;
elapsedMillis lcdOutputMillis;
LiquidCrystal_I2C lcd (0x27, 20, 4);
MFRC522 mfrc522(SS_PIN, RST_PIN);     

const char* host = "script.google.com";
const int httpsPort = 443;

const char* ssid = "(Put Your SSID)";
const char* password = "(Put Your Password)";
String GOOGLE_SCRIPT_ID = "(Put Your GAS Key ID)";

unsigned int keypadReadInterval = 500;
unsigned int lcdOutputInterval = 1000;

byte readCard [4];

String button;
String data;

String UID = "";
String SHIFT1 = "";
String SHIFT2 = "";
String SHIFT3 = "";
String SHIFT4 = "";
String SHIFT5 = "";
String DESC = "";
String LOCATION = "";

String dataAbsen = "";

String lcdShift1 = "";
String lcdShift2 = "";
String lcdShift3 = "";
String lcdShift4 = "";
String lcdShift5 = "";
String lcdName = "";
String lcdRFIDStatus = "";

bool rfidMode = true;

WiFiClientSecure client;

void setup()
{
  Serial.begin (115200);

  pinMode (keypadInput, INPUT_PULLUP);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("   INITIATION....   ");

  delay (1000);

  //WiFI INITIATION
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
    lcd.setCursor(0, 1);
    lcd.print("   Connecting....   ");
  }
  lcd.setCursor(0, 2);
  lcd.print("                    ");
  lcd.setCursor(0, 2);
  lcd.print("   WiFi: " + String (ssid));

  delay(1000);

  while (!Serial);
  SPI.begin();
  mfrc522.PCD_Init();
  delay(4);
  mfrc522.PCD_DumpVersionToSerial();

  delay(1000);

  lcd.setCursor(0, 3);
  lcd.print("                    ");
  lcd.setCursor(0, 3);
  lcd.print("     ALL CLEAR!     ");

  delay(2000);

  lcd.clear();
}

void loop()
{
  if (lcdOutputMillis >= lcdOutputInterval) //1000
  {
    lcdOutput();
    lcdOutputMillis = 0;
  }

  if (keypadReadMillis >= keypadReadInterval) //1000
  {
    if (rfidMode == false)
    {
      keypadRead();
    }
    keypadReadMillis = 0;
  }

  if (rfidMode == true)
  {
    if (!mfrc522.PICC_IsNewCardPresent())
    {
      return;
    }
    if (!mfrc522.PICC_ReadCardSerial())
    {
      return;
    }

    rfidRead();

    mfrc522.PICC_HaltA();
    mfrc522.PCD_StopCrypto1();
  }
}

void rfidRead()
{
  Serial.print(F("\n\nIdentitas Kartu RFID : "));

  for (uint8_t i = 0; i < 4; i++)
  {
    readCard[i] = mfrc522.uid.uidByte[i];
    Serial.print(readCard[i], HEX);
    UID += String(readCard[i], HEX);
  }

  Serial.print("\n");
  rfidMode = false;

  lcdName = "";
  lcdRFIDStatus = "";
}

void lcdOutput()
{
  if (rfidMode == true)
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("   SYSTEM STARTED   ");
    lcd.setCursor(0, 2);
    lcd.print("  *SCANNING  CARD*  ");
  }

  else
  {
    concatData();
    Serial.print ("\nUID          : ");
    Serial.println (UID);
    Serial.print ("Shift        : ");
    Serial.println (lcdShift1 + lcdShift2 + lcdShift3 + lcdShift4 + lcdShift5);
    Serial.print ("Keterangan   : ");
    Serial.println (DESC);
    Serial.print ("Lokasi       : ");
    Serial.println (LOCATION);
    Serial.print ("Data SS      : ");
    Serial.println (dataAbsen);
    Serial.print ("LCD          : ");
    Serial.print (lcdName + " - " + lcdRFIDStatus + "\n");
    Serial.print ("Mode RFID    : ");
    Serial.println (rfidMode);
    Serial.print ("Data : ");
    Serial.println (dataAbsen);

    lcd.setCursor(0, 0);
    lcd.print("                    ");
    lcd.setCursor(0, 0);
    lcd.print("SHIFT   : " + lcdShift1 + " " + lcdShift2 + " " + lcdShift3 + " " + lcdShift4 + " " + lcdShift5);

    lcd.setCursor(0, 1);
    lcd.print("                    ");
    lcd.setCursor(0, 1);
    lcd.print("JOB DESC:     " + DESC);

    lcd.setCursor(0, 2);
    lcd.print("                    ");
    lcd.setCursor(0, 2);
    lcd.print("LOCATION: " + LOCATION);

    lcd.setCursor(0, 3);
    lcd.print("                    ");
    lcd.setCursor(0, 3);
    lcd.print("    *UID LOCKED*    ");
  }
}

void keypadRead()
{
  int buttonValue = analogRead (keypadInput);
  //Serial.print (buttonValue);
  if (buttonValue >= 300)
  {
    if (buttonValue > 1000 && buttonValue <= 1024)
    {
      //Number 1
      button = "1";
      SHIFT1 = "Shift_1";
      lcdShift1 = "1";
      //Serial.println ("\tButton " + button);
    }
    if (buttonValue > 950 && buttonValue <= 985)
    {
      //Number 2
      button = "2";
      SHIFT2 = "Shift_2";
      lcdShift2 = "2";
      //Serial.println ("\tButton " + button);
    }
    if (buttonValue > 850 && buttonValue <= 920)
    {
      //Number 3
      button = "3";
      SHIFT3 = "Shift_3";
      lcdShift3 = "3";
      //Serial.println ("\tButton " + button);
    }
    if (buttonValue > 690 && buttonValue <= 720)
    {
      //Number 4
      button = "4";
      SHIFT4 = "Shift_4";
      lcdShift4 = "4";
      //Serial.println ("\tButton " + button);
    }
    if (buttonValue > 640 && buttonValue <= 675)
    {
      //Number 5
      button = "5";
      SHIFT5 = "Shift_5";
      lcdShift5 = "5";
      //Serial.println ("\tButton " + button);
    }
    if (buttonValue > 610 && buttonValue <= 635)
    {
      //Number 6
      button = "6";
      //Serial.println ("\tButton " + button);
    }
    if (buttonValue > 515 && buttonValue <= 540)
    {
      //Number 7
      button = "7";
      LOCATION = "LAB_D";
      //Serial.println ("\tButton " + button);
    }
    if (buttonValue > 495 && buttonValue <= 515)
    {
      //Number 8
      button = "8";
      LOCATION = "LAB_J";
      //Serial.println ("\tButton " + button);
    }
    if (buttonValue > 475 && buttonValue <= 490)
    {
      //Number 9
      button = "9";
      LOCATION = "LAB_K";
      //Serial.println ("\tButton " + button);
    }
    if (buttonValue > 400 && buttonValue <= 420)
    {
      //Number 0
      button = "0";
      //Serial.println ("\tButton " + button);
    }
    if (buttonValue > 810 && buttonValue <= 835)
    {
      //Desc A
      button = "A";
      DESC = "A";
      //Serial.println ("\tButton " + button);
    }
    if (buttonValue > 580 && buttonValue <= 600)
    {
      //Desc B
      button = "B";
      DESC = "B";
      //Serial.println ("\tButton " + button);
    }
    if (buttonValue > 450 && buttonValue <= 475)
    {
      //Desc C
      button = "C";
      DESC = "C";
      //Serial.println ("\tButton " + button);
    }
    if (buttonValue > 370 && buttonValue <= 395)
    {
      //Button D
      button = "D";
      DESC = "D";
      //Serial.println ("\tButton " + button);
    }
    if (buttonValue > 420 && buttonValue <= 440)
    {
      //Symbol * (CLEAR DATA BUTTON)
      button = "*";
      SHIFT1 = "";
      SHIFT2 = "";
      SHIFT3 = "";
      SHIFT4 = "";
      SHIFT5 = "";
      lcdShift1 = "";
      lcdShift2 = "";
      lcdShift3 = "";
      lcdShift4 = "";
      lcdShift5 = "";
      DESC = "";
      LOCATION = "";
      //Serial.println ("\tButton " + button);
    }
    if (buttonValue > 390 && buttonValue <= 405)
    {
      //Symbol # (SEND DATA BUTTON)
      button = "#";
      concatData();
      data = sendData (dataAbsen, NULL);
      HandleDataFromGoogle (data);
      Serial.println ("Absen Disimpan\n");
      Serial.println (data);
      dataAbsen = "";
      UID = "";
      SHIFT1 = "";
      SHIFT2 = "";
      SHIFT3 = "";
      SHIFT4 = "";
      SHIFT5 = "";
      lcdShift1 = "";
      lcdShift2 = "";
      lcdShift3 = "";
      lcdShift4 = "";
      lcdShift5 = "";
      DESC = "";
      LOCATION = "";
      rfidMode = true;
      delay(3000);
      //Serial.println ("\tButton " + button);
    }
  }
  else
  {
    //Serial.println ("\tNo Button Pressed");
  }
}

void concatData()
{
  dataAbsen = "location=" + LOCATION +
              "&uid=" + UID +
              "&shift=" + SHIFT1 + "," + SHIFT2 + "," + SHIFT3 + "," + SHIFT4 + "," + SHIFT5 +
              "&desc=" + DESC;
}

String sendData(String params, char* domain)
{
  //google scripts requires two get requests
  bool needRedir = false;
  if (domain == NULL)
  {
    domain = (char*)host;
    needRedir = true;
    params = "/macros/s/" + GOOGLE_SCRIPT_ID + "/exec?" + params;
  }

  //Serial.println(*domain);
  String result = "";
  client.setInsecure();

  //Serial.print("connecting to ");
  //Serial.println(host);
  if (!client.connect(host, httpsPort))
  {
    //Serial.println("Connection Failed");
    return "";
  }

  //Serial.print("requesting URL: ");
  //Serial.println(params);
  client.print(String("GET ") + params + " HTTP/1.1\r\n" +
               "Host: " + domain + "\r\n" +
               "Connection: close\r\n\r\n");

  //Serial.println("request sent");
  while (client.connected())
  {
    String line = client.readStringUntil('\n');
    //Serial.println(line);
    if (needRedir)
    {
      int ind = line.indexOf("/macros/echo?user");
      if (ind > 0)
      {
        //Serial.println(line);
        line = line.substring(ind);
        ind = line.lastIndexOf("\r");
        line = line.substring(0, ind);
        //Serial.println(line);
        result = line;
      }
    }

    if (line == "\r")
    {
      //Serial.println("headers received");
      break;
    }
  }

  while (client.available())
  {
    String line = client.readStringUntil('\n');
    if (!needRedir)
      if (line.length() > 5)
        result = line;
    //Serial.println(line);
  }

  if (needRedir)
    return sendData(result, "script.googleusercontent.com");

  else
    return result;
}

void HandleDataFromGoogle(String data)
{
  int ind = data.indexOf(":");
  String access = data.substring(0, ind);
  int nextInd = data.indexOf(":", ind + 1);
  lcdName = data.substring(ind + 1, nextInd);
  lcdRFIDStatus = data.substring(nextInd + 1, data.length());

  if (access == "0")
  {
    //Unregistered UID
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print (lcdName);
    lcd.setCursor(0, 2);
    lcd.print ("  UID " + lcdRFIDStatus);
    lcd.setCursor(18, 2);
    lcd.print ("  ");
  }

  else if (access == "1")
  {
    //Registered UID (Assistant)
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print (lcdName);
    lcd.setCursor(0, 1);
    lcd.print ("   ASISTEN UGMURO   ");
    lcd.setCursor(0, 3);
    lcd.print ("   UID " + lcdRFIDStatus);
    lcd.setCursor(17, 3);
    lcd.print ("   ");
  }

  else if (access == "2")
  {
    //Registered UID (Staff)
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print (lcdName);
    lcd.setCursor(0, 1);
    lcd.print ("    STAFF UGMURO    ");
    lcd.setCursor(0, 3);
    lcd.print ("   UID " + lcdRFIDStatus);
    lcd.setCursor(17, 3);
    lcd.print ("   ");
  }

  delay (3000);
}

/*
================== UID Spreadsheet Google App Script Code ==================
var timeZone = "Asia/Jakarta";
var dateTimeFormat = "dd/MM/yyyy HH:mm:ss";
var logSpreadSheetId = "(Your Log Spreadsheet ID)";

//Function for RFID REGISTRY
function doGet(e) 
{
  var access = "0";
  var name = 'Unknown';
  var text = 'Unregistered';
  var json;
  var error = "ERROR";
  Logger.log(JSON.stringify(e));   // view parameters
  var result = 'OK';      // assume success
  
  if (e.parameter == 'undefined') 
  {
    result = 'No Parameters';
  }
  else 
  {
    var location = 'UGMURO';
    var uid = '';
    var shift = '';
    var desc = '';
    var jobDesc = '';
    var onlyPing = false;
    var error = '';
    for (var param in e.parameter) 
    {
      var value = stripQuotes(e.parameter[param]);
      switch (param) 
      {
        case 'location':
          location = value;
          break;
        case 'uid':
          uid = value;
          break;
        case 'shift':
          shift = value;
          break;
        case 'desc':
          desc = value;
          break;
        default:
          result = "unsupported parameter";
      }
      if (desc == 'A')
      {
        jobDesc = 'Praktikum';
      }
      else if (desc == 'B')
      {
        jobDesc = 'Riset';
      }
      else if (desc == 'C')
      {
        jobDesc = 'Piket';
      }
      else
      {
        jobDesc = 'GABUT';
      }
    }
    var sheet = SpreadsheetApp.getActive().getActiveSheet();
    var data = sheet.getDataRange().getValues();
    if (data.length == 0)
      return;
    for (var i = 0; i < data.length; i++) 
    {
      if (data[i][0] == uid)
      {
        name = data[i][1];
        access = data[i][2];
        text = data[i][3];
        break;
      } 
    }  
    addLog (uid, name, shift, jobDesc, access, location);      
  }
  
  json = 
  {
    'name': name, 
    'access': access,
    'text': text,     
    'error': error
  }
  
  result = (access + ":" + name + ":" + text );
  return ContentService.createTextOutput(result);
  //return ContentService.createTextOutput(JSON.stringify(json) ).setMimeType(ContentService.MimeType.JSON); 
}

//Function for RFID ATTENDANCE LOGGER
function addLog (logUid, logName, logShift, logJobDesc, logAccess, logLocation) 
{   
  var spr = SpreadsheetApp.openById (logSpreadSheetId);
  var sheet = spr.getSheets()[0];
  var data = sheet.getDataRange().getValues();
  var pos = sheet.getLastRow() + 1;
  var rowData = [];
  
  rowData[0] = Utilities.formatDate (new Date(), timeZone, dateTimeFormat);
  rowData[1] = logUid;
  rowData[2] = logName;
  rowData[3] = logShift;
  rowData[4] = logJobDesc;
  rowData[5] = logAccess;
  rowData[6] = logLocation;
  
  var newRange = sheet.getRange(pos, 1, 1, rowData.length);
  newRange.setValues([rowData]);
}

//Remove leading and trailing single or double quotes
function stripQuotes(value) 
{
  return value.replace(/^["']|['"]$/g, "");
}
*/
