#include <SPI.h>
#include <MFRC522.h>
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <LiquidCrystal_I2C.h>
#include <elapsedMillis.h>
#include <Keypad_I2C.h>
#include <Keypad.h>   
#include <Wire.h>

#define I2CADDR 0x20
#define RFIDSDA D8
#define RFIDRST D0

const char* host = "script.google.com";
const int httpsPort = 443;

const char* ssid = "-";
const char* password = "-";
String GOOGLE_SCRIPT_ID = "-";

const byte ROWS = 4; 
const byte COLS = 4; 
char hexaKeys[ROWS][COLS] = 
{
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {4, 5, 6, 7}; 
byte colPins[COLS] = {0, 1, 2, 3}; 

byte readCard [4];

byte modeCounter = 0;
bool rfidMode = true;

unsigned int lcdInterval = 1000;
unsigned int serialInterval = 2000;

char key;
char shift1, shift2, shift3, shift4, shift5, location;

String UID, SHIFT1, SHIFT2, SHIFT3, SHIFT4, SHIFT5, LOCATION;
String dataAbsen, dataRespond;
String nameResponse, accessResponse, statusResponse;

elapsedMillis lcdMillis;
elapsedMillis serialMillis;
MFRC522 mfrc522(RFIDSDA, RFIDRST);
LiquidCrystal_I2C lcd (0x27, 20, 4);
Keypad_I2C keypad4x4(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS, I2CADDR); 
WiFiClientSecure client;

void setup()
{
  Serial.begin(115200);
  Wire.begin();                
  keypad4x4.begin();
  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("   INITIATION....   ");

  delay (1000);

  WiFi.mode (WIFI_STA);
  WiFi.begin (ssid, password);
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

  delay (1000);

  lcd.setCursor(0, 3);
  lcd.print("                    ");
  lcd.setCursor(0, 3);
  lcd.print("     ALL CLEAR!     ");

  delay(2000);

  lcd.clear();
}
  
void loop()
{
  if (serialMillis >= serialInterval)
  {
    Serial.print ("Mode : ");
    Serial.println (modeCounter);  
    serialMillis = 0;
  }

  if (lcdMillis >= lcdInterval)
  {
    lcdOutput();
    lcdMillis = 0;
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

    modeCounter = 1;
    rfidMode = false;

    mfrc522.PICC_HaltA();
    mfrc522.PCD_StopCrypto1();
  }

  else
  {  
    key = keypad4x4.getKey();
    if (key)
    {
      if (modeCounter == 1)
      {
        shift1 = key;
        SHIFT1 = String (shift1);
        modeCounter ++;
      }
      else if (modeCounter == 2)
      {
        shift2 = key;
        SHIFT2 = String (shift2);
        modeCounter ++;
      }
      else if (modeCounter == 3)
      {
        shift3 = key;
        SHIFT3 = String (shift3);
        modeCounter ++;
      }
      else if (modeCounter == 4)
      {
        shift4 = key;
        SHIFT4 = String (shift4);
        modeCounter ++;
      }
      else if (modeCounter == 5)
      {
        shift5 = key;
        SHIFT5 = String (shift5);
        modeCounter ++;
      }
      else if (modeCounter == 6)
      {
        location = key;
        switch (location)
        {
          case 'A':
            LOCATION = "LAB_D";
            break;
          case 'B':
            LOCATION = "LAB_J";
            break;
          case 'C':
            LOCATION = "LAB_K";
            break;
          case '#':
            sendData();
            break;
        }
      } 
      switch (key)
      {
        case 'D':
          SHIFT1 = "";
          SHIFT2 = "";
          SHIFT3 = "";
          SHIFT4 = "";
          SHIFT5 = "";
          LOCATION = "";
          modeCounter = 1;          
          break;
      }
    }    
  }
}

void lcdOutput()
{
  if (modeCounter == 0)
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("   SYSTEM STARTED   ");
    lcd.setCursor(0, 2);
    lcd.print("  *SCANNING  CARD*  ");
  }

  else
  {
    lcd.setCursor(0, 0);
    lcd.print("                    ");
    lcd.setCursor(0,0);
    lcd.print("A:" + SHIFT1); 
    lcd.setCursor(4,0);
    lcd.print("B:" + SHIFT2);
    lcd.setCursor(8,0);
    lcd.print("C:" + SHIFT3);
    lcd.setCursor(12,0);
    lcd.print("D:" + SHIFT4);
    lcd.setCursor(16,0);
    lcd.print("E:" + SHIFT5);

    lcd.setCursor(0, 1);
    lcd.print("                    ");
    lcd.setCursor(0, 1);
    lcd.print("LOCATION: " + LOCATION);   

    lcd.setCursor(0, 2);
    lcd.print("                    ");
    lcd.setCursor(0, 2);
    lcd.print("    *UID LOCKED*    ");
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
}

void concatData()
{
  dataAbsen = "uid=" + UID +
              "&shift1=" + SHIFT1 + 
              "&shift2=" + SHIFT2 +
              "&shift3=" + SHIFT3 +
              "&shift4=" + SHIFT4 +
              "&shift5=" + SHIFT5 +
              "&domain=" + LOCATION;
  
  //"API : uid=7c4a1930&shift1=2&shift2=6&shift3=8&shift4=4&shift5=5&location=LAB_K"
}

void sendData()
{
  concatData();

  Serial.print ("API : ");
  Serial.println (dataAbsen);

  lcd.setCursor(0, 3);
  lcd.print("                    ");
  lcd.setCursor(0, 3);
  lcd.print("   *SENDING DATA*   ");

  dataRespond = sendData(dataAbsen, NULL);
  HandleDataFromGoogle (dataRespond);

  Serial.print ("Response : ");
  Serial.println (dataRespond);
  
  dataAbsen = "";
  UID = "";
  SHIFT1 = "";
  SHIFT2 = "";
  SHIFT3 = "";
  SHIFT4 = "";
  SHIFT5 = "";
  LOCATION = "";

  rfidMode = true;
  modeCounter = 0;

  delay (1000);
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
  accessResponse = data.substring(0, ind);
  int nextInd = data.indexOf(":", ind + 1);
  nameResponse = data.substring(ind + 1, nextInd);
  statusResponse = data.substring(nextInd + 1, data.length());

  if (accessResponse == "0")
  {
    //Unregistered UID
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print (nameResponse);
    lcd.setCursor(0, 2);
    lcd.print ("  UID " + statusResponse);
    lcd.setCursor(18, 2);
    lcd.print ("  ");
  }

  else if (accessResponse == "1")
  {
    //Registered UID (Assistant)
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print (nameResponse);
    lcd.setCursor(0, 1);
    lcd.print ("   ASISTEN UGMURO   ");
    lcd.setCursor(0, 3);
    lcd.print ("   UID " + statusResponse);
    lcd.setCursor(17, 3);
    lcd.print ("   ");
  }

  else if (accessResponse == "2")
  {
    //Registered UID (Staff)
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print (nameResponse);
    lcd.setCursor(0, 1);
    lcd.print ("    STAFF UGMURO    ");
    lcd.setCursor(0, 3);
    lcd.print ("   UID " + statusResponse);
    lcd.setCursor(17, 3);
    lcd.print ("   ");
  }

  delay (3000);
}

/*
var timeZone = "Asia/Jakarta";
var dateTimeFormat = "dd/MM/yyyy HH:mm:ss";
var logSpreadSheetId = "-";

function doGet(e) 
{
  var access = "0";
  var name = 'Unknown';
  var status = 'Unregistered';
  Logger.log(JSON.stringify(e));   // view parameters
  var result = 'OK';      // assume success
  
  if (e.parameter == 'undefined') 
  {
    result = 'No Parameters';
  }
  else 
  {
    var uid = '';

    var shift1Status = '';
    var shift2Status = '';
    var shift3Status = '';
    var shift4Status = '';
    var shift5Status = '';
    var shift1Value = '';
    var shift2Value = '';
    var shift3Value = '';
    var shift4Value = '';
    var shift5Value = '';

    var domain = '';

    for (var param in e.parameter) 
    {
      var value = stripQuotes(e.parameter[param]);
      switch (param) 
      {
        case 'uid':
          uid = value;
          break;
        case 'shift1':
          shift1Status = value;
          shift1Value = shiftMap (value); 
          break;
        case 'shift2':
          shift2Status = value;
          shift2Value = shiftMap (value);
          break;
        case 'shift3':
          shift3Status = value;
          shift3Value = shiftMap (value);
          break;
        case 'shift4':
          shift4Status = value;
          shift4Value = shiftMap (value);
          break;
        case 'shift5':
          shift5Status = value;
          shift5Value = shiftMap (value);
          break;
        case 'domain':
          domain = value;
          break;
        default:
          result = "unsupported parameter";
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
        status = data[i][3];
        break;
      } 
    }

    if (domain == 'LAB_D')
    {
      addLog (0, uid, name, shift1Status, shift1Value, shift2Status, shift2Value, shift3Status, shift3Value, shift4Status, shift4Value, shift5Status, shift5Value, domain, status, access);
    }
    else if (domain == 'LAB_J')
    {
      addLog (1, uid, name, shift1Status, shift1Value, shift2Status, shift2Value, shift3Status, shift3Value, shift4Status, shift4Value, shift5Status, shift5Value, domain, status, access);
    }
    else if (domain == 'LAB_K')
    {
      addLog (2, uid, name, shift1Status, shift1Value, shift2Status, shift2Value, shift3Status, shift3Value, shift4Status, shift4Value, shift5Status, shift5Value, domain, status, access);
    }
  }
  
  result = (access + ":" + name + ":" + status );
  return ContentService.createTextOutput(result);
}

function shiftMap (shiftValue)
{
  if (shiftValue == '0')
  {
    return 0;
  }
  else if (shiftValue == '1')
  {
    return 5;
  }
  else if (shiftValue == '2')
  {
    return 10;
  }
  else if (shiftValue == '3')
  {
    return 15;
  }
  else if (shiftValue == '4')
  {
    return 20;
  }
  else if (shiftValue == '5')
  {
    return 25;
  }
  else if (shiftValue == '6')
  {
    return 30;
  }
  else if (shiftValue == '7')
  {
    return 35;
  }
  else if (shiftValue == '8')
  {
    return 40;
  }
  else if (shiftValue == '9')
  {
    return 45;
  }
  else 
  {
    return 100;
  }
}

function addLog (sheetDomain, logUid, logName, logShift1Status, logShift1Value, logShift2Status, logShift2Value, logShift3Status, logShift3Value, logShift4Status, logShift4Value, logShift5Status, logShift5Value, logDomain, logStatus, logAccess) 
{   
  var spr = SpreadsheetApp.openById (logSpreadSheetId);
  var sheet = spr.getSheets()[sheetDomain];
  var data = sheet.getDataRange().getValues();
  var pos = sheet.getLastRow() + 1;
  var rowData = [];
    
  rowData[0] = Utilities.formatDate (new Date(), timeZone, dateTimeFormat);
  rowData[1] = logUid;
  rowData[2] = logName;
  rowData[3] = logShift1Status;
  rowData[4] = logShift1Value;
  rowData[5] = logShift2Status;
  rowData[6] = logShift2Value;
  rowData[7] = logShift3Status;
  rowData[8] = logShift3Value;
  rowData[9] = logShift4Status;
  rowData[10] = logShift4Value;
  rowData[11] = logShift5Status;
  rowData[12] = logShift5Value;
  rowData[13] = logDomain;
  rowData[14] = logStatus;
  rowData[15] = logAccess;
  
  var newRange = sheet.getRange(pos, 1, 1, rowData.length);
  newRange.setValues([rowData]);
}

function stripQuotes(value) 
{
  return value.replace(/^["']|['"]$/g, "");
}
*/