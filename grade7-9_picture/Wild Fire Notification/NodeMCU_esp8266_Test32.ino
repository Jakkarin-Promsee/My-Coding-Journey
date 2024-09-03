// DS18B20 สายสีแดง = VCC,สายสีดำ = GND,สายสีเหลือง - DAT
// DS18B20x1 VCC-5V , GND-GND , DAT-6 ระหว่างVCCกับDATมีตัวต้านทาน1k
// DS18B20x2 VCC-5V , GND-GND , DAT-7 ระหว่างVCCกับDATมีตัวต้านทาน1k
//----------------------------------------

#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <DallasTemperature.h>
#include <OneWire.h>
#include <TridentTD_LineNotify.h>
#include "SoftwareSerial.h"
//----------------------------------------

//----------------------------------------
#define ONE_WIRE_BUS1 D1 // กำหนดว่าขาของเซนเซอร์ 18B20 ต่อกับขา 1
#define ONE_WIRE_BUS2 D2 // กำหนดว่าขาของเซนเซอร์ 18B20 ต่อกับขา 2
#define ON_Board_LED 2   //--> Defining an On Board LED, used for indicators when the process of connecting to a wifi router
#define LINE_TOKEN "lpZUuYCoo8fx8px1P1v7X34OZSIGxPzpp9lMyKTtRgp"
//----------------------------------------

//----------------------------------------
OneWire oneWire1(ONE_WIRE_BUS1);       // ตัวที่1 ตั้งตัวแปร
OneWire oneWire2(ONE_WIRE_BUS2);       // ตัวที่2 ตั้งตัวแปร
DallasTemperature sensors1(&oneWire1); // ตัวที่1 ใช้ตัวแปร
DallasTemperature sensors2(&oneWire2); // ตัวที่2 ใช้ตัวแปร
SoftwareSerial GPSModule(D7, D6);      // TX, RX
//----------------------------------------

//----------------------------------------SSID dan Password wifi mu gan.
const char *ssid = "HUAWEI MatePad T";   //--> Nama Wifi / SSID.
const char *password = "pimjai15082520"; //-->  Password wifi .
// const char* ssid = "JBL X"; //--> Nama Wifi / SSID.
// const char* password = "may080918"; //-->  Password wifi .
//----------------------------------------

//----------------------------------------Host & httpsPort
const char *host = "script.google.com";
const int httpsPort = 443;
//----------------------------------------

//----------------------------------------
WiFiClientSecure client; //--> Create a WiFiClientSecure object.
//----------------------------------------

//---------------------------------------- Timers auxiliar variables
long now = millis();
long lastMeasure = 0;
String GAS_ID = "AKfycby_2HvSJuu9osVayv1z6e2jSDPhkim-ZeqFOd0Qvo8L9ZPj7HI"; //--> spreadsheet script ID
int updates;
int failedUpdates;
int pos;
int stringplace = 0;
String timeUp;
String nmea[15];
String labels[12]{"Time: ", "Status: ", "Latitude: ", "Hemisphere: ", "Longitude: ", "Hemisphere: ", "Speed: ", "Track Angle: ", "Date: "};
//----------------------------------------

//============================================ void setup
void setup()
{

  Serial.begin(115200);
  delay(500);
  sensors1.begin(); // ตัวที่1 เริ่มการทำงาน
  sensors2.begin(); // ตัวที่2 เริ่มการทำงาน
  GPSModule.begin(9600);
  Serial.println();
  Serial.println(LINE.getVersion());
  WiFi.begin(ssid, password); //--> Connect to your WiFi router
  Serial.println("");
  pinMode(ON_Board_LED, OUTPUT);    //--> On Board LED port Direction output
  digitalWrite(ON_Board_LED, HIGH); //-->
  //----------------------------------------Wait for connection
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    //----------------------------------------Make the On Board Flashing LED on the process of connecting to the wifi router.
    digitalWrite(ON_Board_LED, LOW);
    delay(250);
    digitalWrite(ON_Board_LED, HIGH);
    delay(250);
  }
  //----------------------------------------
  digitalWrite(ON_Board_LED, HIGH); //--> Turn off the On Board LED when it is connected to the wifi router.
  //----------------------------------------If successfully connected to the wifi router, the IP Address that will be visited is displayed in the serial monitor
  Serial.println("");
  Serial.print("Successfully connected to : ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println();
  //----------------------------------------
  LINE.setToken(LINE_TOKEN);
  client.setInsecure();

  for (int D = 0; D <= 4; D++)
  {
    sensors1.requestTemperatures();        // ตัวที่1 อ่านอุณหภูมิ
    sensors2.requestTemperatures();        // ตัวที่2 อ่านอุณหภูมิ
    float x = sensors1.getTempCByIndex(0); // ตัวที่1 เก็บไว้ตัวเเปรg
    float y = sensors2.getTempCByIndex(0); // ตัวที่2 เก็บไว้ในตัวเเปีh

    if (x >= 30)
    {
      break;
    }
    else if (y >= 30)
    {
      break;
    }
    else if (x <= -127)
    {
      break;
    }
    else if (y <= -127)
    {
      break;
    }
    delay(4560);
  }
  now = millis();
  // Publishes new temperature and humidity every 3 seconds
  if (now - lastMeasure > 50)
  {
    lastMeasure = now;

    sensors1.requestTemperatures();        // ตัวที่1 อ่านอุณหภูมิ
    sensors2.requestTemperatures();        // ตัวที่2 อ่านอุณหภูมิ
    float h = sensors1.getTempCByIndex(0); // ตัวที่1 เก็บไว้ตัวเเปรg
    float t = sensors2.getTempCByIndex(0); // ตัวที่2 เก็บไว้ในตัวเเปีh
    // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)

    Serial.print("Temp1: ");
    Serial.print(h);
    Serial.print(" *c ");
    Serial.print("Temp2: ");
    Serial.print(t);
    Serial.println(" *C ");
    GPSModule.flush();
    while (GPSModule.available() > 0)
    {
      GPSModule.read();
    }
    if (GPSModule.find("$GPRMC,"))
    {
      String tempMsg = GPSModule.readStringUntil('\n');
      for (int i = 0; i < tempMsg.length(); i++)
      {
        if (tempMsg.substring(i, i + 1) == ",")
        {
          nmea[pos] = tempMsg.substring(stringplace, i);
          stringplace = i + 1;
          pos++;
        }
        if (i == tempMsg.length() - 1)
        {
          nmea[pos] = tempMsg.substring(stringplace, i);
        }
      }
      updates++;
      nmea[2] = ConvertLat();
      nmea[4] = ConvertLng();
    }

    stringplace = 0;
    pos = 0;

    String f = nmea[2];
    String g = nmea[4];

    Serial.print(nmea[2]);
    Serial.print(",");
    Serial.print(nmea[4]);
    Serial.println("");
    if (t >= 30)
    {
      String LineText;
      String string1 = "อุณหภูมิที่วัดได้สูงเกินกว่าค่าที่กำหนด";
      String string2 = "เซนเซอร์วัดอุณหภูมิ1=";
      String string3 = "เซนเซอร์วัดอุณหภูมิ2=";
      String string4 = "พิกัดตำแหน่ง ";
      String string5 = " ํc ";

      LineText = string1 + "[" + string2 + t + string5 + "]" + "[" + string3 + h + string5 + "]" + "[" + string4 + f + "," + g + "]";
      Serial.print("Line ");
      Serial.println(LineText);
      LINE.notify(LineText);
    }
    else if (h >= 30)
    {
      String LineText;
      String string1 = "อุณหภูมิที่วัดได้สูงเกินกว่าค่าที่กำหนด";
      String string2 = "เซนเซอร์วัดอุณหภูมิ1=";
      String string3 = "เซนเซอร์วัดอุณหภูมิ2=";
      String string4 = "พิกัดตำแหน่ง ";
      String string5 = " ํc ";

      LineText = string1 + "[" + string2 + t + string5 + "]" + "[" + string3 + h + string5 + "]" + "[" + string4 + f + "," + g + "]";
      Serial.print("Line ");
      Serial.println(LineText);
      LINE.notify(LineText);
    }
    sendData(t, h, f, g);
  }
}
//==============================================================================

//============================================================================== void loop
void loop()
{
  // เวลาที่ต้อการ/2 -6  นาทีละ-1
  for (int S = 0; S <= 4318; S++)
  {
    sensors1.requestTemperatures();        // ตัวที่1 อ่านอุณหภูมิ
    sensors2.requestTemperatures();        // ตัวที่2 อ่านอุณหภูมิ
    float x = sensors1.getTempCByIndex(0); // ตัวที่1 เก็บไว้ตัวเเปรg
    float y = sensors2.getTempCByIndex(0); // ตัวที่2 เก็บไว้ในตัวเเปีh

    Serial.print(x);
    Serial.print(y);

    if (x >= 30)
    {
      break;
    }
    else if (y >= 30)
    {
      break;
    }
    else if (x <= -127)
    {
      break;
    }
    else if (y <= -127)
    {
      break;
    }
    delay(4560);
  }

  now = millis();
  // Publishes new temperature and humidity every 3 seconds
  if (now - lastMeasure > 50)
  {
    lastMeasure = now;

    sensors1.requestTemperatures();        // ตัวที่1 อ่านอุณหภูมิ
    sensors2.requestTemperatures();        // ตัวที่2 อ่านอุณหภูมิ
    float h = sensors1.getTempCByIndex(0); // ตัวที่1 เก็บไว้ตัวเเปรg
    float t = sensors2.getTempCByIndex(0); // ตัวที่2 เก็บไว้ในตัวเเปีh
    // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)

    Serial.print("Temp1: ");
    Serial.print(h);
    Serial.print(" *c ");
    Serial.print("Temp2: ");
    Serial.print(t);
    Serial.println(" *C ");
    GPSModule.flush();
    while (GPSModule.available() > 0)
    {
      GPSModule.read();
    }
    if (GPSModule.find("$GPRMC,"))
    {
      String tempMsg = GPSModule.readStringUntil('\n');
      for (int i = 0; i < tempMsg.length(); i++)
      {
        if (tempMsg.substring(i, i + 1) == ",")
        {
          nmea[pos] = tempMsg.substring(stringplace, i);
          stringplace = i + 1;
          pos++;
        }
        if (i == tempMsg.length() - 1)
        {
          nmea[pos] = tempMsg.substring(stringplace, i);
        }
      }
      updates++;
      nmea[2] = ConvertLat();
      nmea[4] = ConvertLng();
    }

    stringplace = 0;
    pos = 0;

    String f = nmea[2];
    String g = nmea[4];

    Serial.print(nmea[2]);
    Serial.print(",");
    Serial.print(nmea[4]);
    Serial.println("");
    if (t >= 30)
    {
      String LineText;
      String string1 = "อุณหภูมิที่วัดได้สูงเกินกว่าค่าที่กำหนด";
      String string2 = "เซนเซอร์วัดอุณหภูมิ1=";
      String string3 = "เซนเซอร์วัดอุณหภูมิ2=";
      String string4 = "พิกัดตำแหน่ง ";
      String string5 = " ํc ";

      LineText = string1 + "[" + string2 + t + string5 + "]" + "[" + string3 + h + string5 + "]" + "[" + string4 + f + "," + g + "]";
      Serial.print("Line ");
      Serial.println(LineText);
      LINE.notify(LineText);
    }
    else if (h >= 30)
    {
      String LineText;
      String string1 = "อุณหภูมิที่วัดได้สูงเกินกว่าค่าที่กำหนด";
      String string2 = "เซนเซอร์วัดอุณหภูมิ1=";
      String string3 = "เซนเซอร์วัดอุณหภูมิ2=";
      String string4 = "พิกัดตำแหน่ง ";
      String string5 = " ํc ";

      LineText = string1 + "[" + string2 + t + string5 + "]" + "[" + string3 + h + string5 + "]" + "[" + string4 + f + "," + g + "]";
      Serial.print("Line ");
      Serial.println(LineText);
      LINE.notify(LineText);
    }
    sendData(t, h, f, g);
  }
}
//==============================================================================GPS module
String ConvertLat()
{
  String posneg = "";
  if (nmea[3] == "S")
  {
    posneg = "-";
  }
  String latfirst;
  float latsecond;
  for (int i = 0; i < nmea[2].length(); i++)
  {
    if (nmea[2].substring(i, i + 1) == ".")
    {
      latfirst = nmea[2].substring(0, i - 2);
      latsecond = nmea[2].substring(i - 2).toFloat();
    }
  }
  latsecond = latsecond / 60;
  String CalcLat = "";

  char charVal[9];
  dtostrf(latsecond, 4, 6, charVal);
  for (int i = 0; i < sizeof(charVal); i++)
  {
    CalcLat += charVal[i];
  }
  latfirst += CalcLat.substring(1);
  latfirst = posneg += latfirst;
  return latfirst;
}

String ConvertLng()
{
  String posneg = "";
  if (nmea[5] == "W")
  {
    posneg = "-";
  }

  String lngfirst;
  float lngsecond;
  for (int i = 0; i < nmea[4].length(); i++)
  {
    if (nmea[4].substring(i, i + 1) == ".")
    {
      lngfirst = nmea[4].substring(0, i - 2);
      // Serial.println(lngfirst);
      lngsecond = nmea[4].substring(i - 2).toFloat();
      // Serial.println(lngsecond);
    }
  }
  lngsecond = lngsecond / 60;
  String CalcLng = "";
  char charVal[9];
  dtostrf(lngsecond, 4, 6, charVal);
  for (int i = 0; i < sizeof(charVal); i++)
  {
    CalcLng += charVal[i];
  }
  lngfirst += CalcLng.substring(1);
  lngfirst = posneg += lngfirst;
  return lngfirst;
}

//----------------------------------------void sendData
void sendData(float value1, float value2, String value3, String value4)
{
  Serial.println("==========");
  Serial.print("connecting to ");
  Serial.println(host);

  //----------------------------------------Connect to Google host
  if (!client.connect(host, httpsPort))
  {
    Serial.println("connection failed");
    return;
  }
  //----------------------------------------

  //----------------------------------------Proses dan kirim data

  float string_temp1 = value1;
  float string_temp2 = value2;
  String string_where1 = value3;
  String string_where2 = value4;

  String url = "/macros/s/" + GAS_ID + "/exec?temp1=" + string_temp1 + "&temp2=" + string_temp2 + "&where=" + string_where1 + "," + string_where2; //  2 variables
  Serial.print("requesting URL: ");
  Serial.println(url);

  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "User-Agent: BuildFailureDetectorESP8266\r\n" +
               "Connection: close\r\n\r\n");

  Serial.println("request sent");

  //----------------------------------------

  //---------------------------------------
  while (client.connected())
  {
    String line = client.readStringUntil('\n');
    if (line == "\r")
    {
      Serial.println("headers received");
      break;
    }
  }
  String line = client.readStringUntil('\n');
  if (line.startsWith("{\"state\":\"success\""))
  {
    Serial.println("esp8266/Arduino CI successfull!");
  }
  else
  {
    Serial.println("esp8266/Arduino CI has failed");
  }
  Serial.print("reply was : ");
  Serial.println(line);
  Serial.println("closing connection");
  Serial.println("==========");
  Serial.println();
  //----------------------------------------
}
//===============================================
