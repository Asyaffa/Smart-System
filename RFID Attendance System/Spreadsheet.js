/*
	Written by Aqilla Rahman Musyaffa
	
	Based on:
	> https://github.com/unreeeal/ESP/tree/master/ESP-RFID-GOOGLE
*/

var timeZone = "(Your Location Timezone)";
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
    var location = '(Default_Location)';	//NO SPACE
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
  
/*
  json = 
  {
    'name': name, 
    'access': access,
    'text': text,     
    'error': error
  }
*/
  
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
