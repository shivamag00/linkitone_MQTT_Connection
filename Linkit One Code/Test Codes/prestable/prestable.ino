/* 
 *  LinkIt One sketch for MQTT Prototype  *
Functions:
  callback        -
  sendMemCard     -
  InitLWiFi       - 
  reconnect       -
  sendAnalogdata  -
  GPS Functions   - 
  reportdata      -
  sendreportdata  -
*/
//-------HARDWARE REPORTING INFORM SIR-----------------
#include <LWiFi.h>
#include <LWiFiClient.h>
#include <PubSubClient.h>
#include <LSD.h> 
#include <LFlash.h>
#include <LGPS.h>
#include "LDHT.h" // LDHT Library
#include <Wire.h>
#include <math.h>


//<<<<<----- Delay Variables ----->>>>>//
int reportingDelay = 5000;
int sensingDelay = 60000;
int pause = 3000;   //time delay in milliseconds for every sensor
//<<<<<----- ./Delay Variables ----->>>>>//

float locallat, locallong, localtemp;
String slocallat, slocallong, slocaltemp;
//---------- DHT Configurations ----------//
#define DHTPIN 8          // what pin we're connected to
#define DHTTYPE DHT11     // using DHT11 sensor

LDHT dht(DHTPIN,DHTTYPE);

float tempC=0.0,Humi=0.0;
//---------- ./DHT Configurations ----------//


//---------- GPS Configurations ----------//
gpsSentenceInfoStruct info; //needed to get GPS data

double latitude = 0.00;
double longitude = 0.00;
double latT = 0.00, lonT = 0.00;
int hour = 0, minute = 0, second = 0;
int sat_num = 0;    //number of visible satellites
int day = 0, month = 0, year = 0;
String time_format = "00:00:00", date_format = "00:00:0000";
String lat_format = "0.00000", lon_format = "0.00000";
//---------- ./GPS Configurations ----------//

//<<<<<----- Server Variables ----->>>>>//
char tp = '0'; //DHT Switch
char gp = '0'; //GPS Switch
float tUT = 70; // Temperature Upper Threshold
float tLT = -150; // Temperature Lower Threshold
//<<<<<----- ./Server Variables ----->>>>>//

/* 
  Modify to your WIFI Access Credentials. 
*/
#define WIFI_AP "moto e5 plus 8607"
#define WIFI_PASSWORD "12345678"
#define WIFI_AUTH LWIFI_WPA  // choose from LWIFI_OPEN, LWIFI_WPA, or LWIFI_WEP.
#define DRV LFlash
/*
  Modify to your MQTT broker - Select only one
*/
//char mqttBroker[] = "iot.eclipse.org";
byte mqttBroker[] = {192,168,43,2}; // modify to your local broker
          //char tp = '0'; //Temperature Control 
          //char gp = '0'; //GPS Control
LWiFiClient wifiClient;
PubSubClient client( wifiClient );
unsigned long lastSend, lastreportsend;

bool AP_Connect = false;
bool server_Connect = false;

//--------------------------------------------------------------------------
void setup()
{
   delay(10000);  //10s fixed delay
   
   Serial.begin(115200);
   Serial.print("HI, LinkIt is now beginning its work\n\n\n\n");
   
  //---------- DHT Setup ----------//
   dht.begin();
   Serial.println(" DHT11 Sensor :\n");
   Serial.print(DHTTYPE);
  //---------- ./DHT Setup ----------//

  //---------- GPS Setup ----------//
    LGPS.powerOn();
    Serial.println("GPS started.");
  //---------- ./GPS Setup ----------//

   
   client.setServer( mqttBroker, 1883 ); //Setting the mqtt server
   client.setCallback( callback ); //Sets the callback function which will be called when a message is received

   lastreportsend = 0;
   lastSend = 0; //Denotes the time elapsed from the start of the program to the point when the data was sent via publish command    
}

//--------------------------------------------------------------------------
void loop()
{
//----------Initial connect----------//
 if (LWiFi.status() != LWIFI_STATUS_CONNECTED)
   InitLWiFi();

 if (client.state()!=0)
   reconnect();  
//----------./Initial connect----------//  
  if((millis()-lastreportsend) > reportingDelay)
  {
    reportdata();
    if ((localtemp < tLT) || localtemp >tUT)
    {
      if (LWiFi.status() != LWIFI_STATUS_CONNECTED)
      InitLWiFi();

      if (client.state()!=0)
      reconnect();

      if ( AP_Connect && server_Connect)
      sendreportdata();
    }
    lastreportsend = millis();
  }
  
  if((millis()- lastSend) >  sensingDelay)
  {
    if (LWiFi.status() != LWIFI_STATUS_CONNECTED)
    InitLWiFi();  //Function to connect to the Wifi
    Serial.println(AP_Connect);
    Serial.println(server_Connect);
  
    if (client.state()!=0)
    reconnect();
    //if( !client.connected() ) 
    
    delay(5000);
    //if( millis()-lastSend > 5000 ) // millis() returns the time elapsed from the start of the program. Subtracting millis and lastsend gives the time elapsed between sending successive messages
                                 // Here we are Sending an update only after 5 seconds
    { 
      //sendAnalogData();
      sendMemCard();
      if ( AP_Connect && server_Connect)
      sendAnalogdata();
      lastSend = millis();
    }
  }
    

  
  client.loop();
}

//--------------------------------------------------------------------------
void callback( char* topic, byte* payload, unsigned int length ) 
{
  Serial.print( "Recived message on Topic:" );
  Serial.print( topic );
  //Setiing The temperature and gps control values according to the values received from the server
  if (topic[0]=='g')
  {
    if ((char)payload[0]=='0')
      gp = '0';
    else 
      gp ='1'; 
  }
  else
  if (topic[0]=='t')
  {
    if ((char)payload[0]=='0')
      tp = '0';
    else 
      tp ='1'; 
  }
  else
  if (topic[0]=='u')
  {
    tUT=atof((char*)payload);
    Serial.println("Upper Threshold");
    Serial.println(tUT);
  }
  else
  if (topic[0]=='l')
  {
    tLT=atof((char*)payload);
    Serial.println("Lower Threshold");
    Serial.println(tLT);
  }
  else
  if (topic[0]=='r')
  {
    reportingDelay=atoi((char*)payload);
    Serial.println("Reporting Delay");
    Serial.println(reportingDelay);
  }
  else
  if (topic[0]=='s')
  {
    sensingDelay=atoi((char*)payload);
    Serial.println("Sensing Delay");
    Serial.println(sensingDelay);
  }
  
  Serial.print( "Message:");
  for (int i=0;i<length;i++) 
  {
    Serial.print( (char)payload[i] );
  }

  //Printing the final values
  Serial.println();
  Serial.println(tp);
  Serial.println(gp);
  Serial.println();
}

//--------------------------------------------------------------------------
void sendMemCard() 
{
   DRV.begin();
  // Read data to send
  Serial.println("Memory Card Entered");
  String data_A0;
  String data_A1;
  String data_A2;
  if (tp=='1')
  {
   //---------- DHT Loop ----------//
      if(dht.read())
      {   
        Serial.println("Statring to read temperature");
        tempC = dht.readTemperature();
        //Humi = dht.readHumidity();

//##### For testing purposes of DHT #####//
/*        Serial.println("*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*");
        Serial.print("Temperature Celsius = ");
        Serial.print(dht.readTemperature());
        Serial.println("C");
*/
//##### Readings to be added later #####//
/* 
        Serial.print("Temperature Fahrenheit = ");
        Serial.print(dht.readTemperature(false));
        Serial.println("F");

        Serial.print("Humidity = ");
        Serial.print(dht.readHumidity());
        Serial.println("%");

        Serial.print("HeatIndex = ");
        Serial.print(dht.readHeatIndex(tempC,Humi));
        Serial.println("C");

        Serial.print("DewPoint = ");
        Serial.print(dht.readDewPoint(tempC,Humi));
        Serial.println("C");
*/   }
    delay(2000);
  //---------- ./DHT Loop ----------//


    data_A0 = (String)tempC;
    //data_A0 = "0.00";
  }
  else
   data_A0 = "f";

   if (gp=='1') 
   {
     

  //---------- GPS Loop ----------//
//  Serial.println("*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*");
    if (getData(&info) > 3)   //Start retriving data if no of satellites being tracked are greater than 3
    {
      String str = "|";
      str += date_format;
      str += ",";
      str += time_format;
      str += ",";
      str += lat_format;
      str += ",";
      str += lon_format;
      str += ",";
      str += sat_num;
      str += "|";
  //    Serial.println(str);
    }
    else{
      Serial.println("Less then 4 satelites.");
    }
    delay(pause);
  //---------- ./GPS Loop ----------//
    
    data_A1 = (String)latitude;
      data_A2 = (String)longitude;
    
    //data_A1 = "0.00";
    //data_A2 = "0.00";
   }
   else
   {
     LGPS.powerOff();
     data_A1 = "f";
    data_A2 = "f";
   }

  // Just debug messages
  Serial.print( "Sending analog data : [" );
  Serial.print( data_A0 ); 
  Serial.print( data_A1 ); 
  Serial.print( data_A2 );
  Serial.print( "]   -> " );

  // Prepare a JSON payload string
  String payload = "{";
  payload += "\"Temperature\":\""; payload += data_A0; payload += "\", ";
  payload += "\"Latitude\":\""; payload += data_A1; payload += "\", ";
  payload += "\"Longitude\":\""; payload += data_A2; payload += "\"";
  payload += "}";

  //Store Payload
  LFile dataFile = DRV.open("datalog.txt", FILE_WRITE);

  // if the file is available, write to it:
  if (dataFile) 
  {
    Serial.println("Memory Data Entered");
    dataFile.print(payload);
    dataFile.close();
    Serial.println(payload);
  }
  
  //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  
  //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
}


//--------------------------------------------------------------------------
void InitLWiFi()
{
  LWiFi.begin();

  // Keep retrying until connected to AP
  Serial.println("Connecting to AP");
  int i=1, j=0;
  while (i <= 1) 
  {
    LWiFi.connect(WIFI_AP, LWiFiLoginInfo(WIFI_AUTH, WIFI_PASSWORD));
    if (LWiFi.status() == LWIFI_STATUS_CONNECTED)
    {
      j=1;
      Serial.println("Connected");
      AP_Connect = true;
      break; 
    }
    delay(1000); //Reconnect after 1 second
    i=i+1;
    AP_Connect = false;
    Serial.println("Disconnected");
  }
  if (j==1)
  Serial.println("Connected to AP");
  else
  Serial.println("Could not Connect To AP");

  
}


//--------------------------------------------------------------------------
void reconnect() 
{
  // Loop until we're reconnected
  int i=1;
  while (i<=1) 
  {
    Serial.print("Connecting to MQTT broker ...");

    // Attempt to connect
    if ( client.connect("LinkIt One Client") ) // Connects to the server with the Client ID "Linkit One Client"
    {  
      Serial.println( "[DONE]" );

      // Publish a message on topic "outTopic"
      client.publish( "sidsat","Hello, This is LinkIt One" );
      // Subscribe to topic "inTopic"
      client.subscribe( "temp" );
      client.subscribe( "gps" );
      client.subscribe( "up" );
      client.subscribe( "low" );
      client.subscribe( "report" );
      client.subscribe( "sense" );
      
      server_Connect = true;
      break;
    } 
    else 
    {
      Serial.print( "[FAILED] [ rc = " );
      Serial.print( client.state() ); //Gives the reason for not being able to connect
      Serial.println( " : retrying in 5 seconds]" );
      // Wait 5 seconds before retrying
      delay( 5000 );
      server_Connect = false;
      i=i+1;
    }
    //!client.connected() can also be used
  }
}

//--------------------------------------------------------------------------
void sendAnalogdata()
{
  LFile dataFile = DRV.open("datalog.txt");
  // if the file is available, read from it:
  
  if (dataFile) 
  {
    while(dataFile.available())
    {
      Serial.println("Send Entered");
      int i=1;
      String payload;
      char buf;
      buf = char(dataFile.read());
      payload = String(buf);
      while (buf!='}')
      {
        buf = char(dataFile.read());
        payload += String(buf);
        i=i+1; 
      }
      // Send payload
      char analogData[100];
      Serial.println(payload);
      payload.toCharArray( analogData, 100 ); //copies the contents of the payload to the buffer 'analogData'
      client.publish( "sidsat", analogData ); //publishes to the topic sidsat
      Serial.println( analogData );
      delay(500);
    }
    dataFile.close();
    DRV.remove("datalog.txt");
    dataFile.close();

  }
}



 //'''''''''' GPS Functions ''''''''''//
/**
*Converts degrees from (d)ddmm.mmmm to (d)dd.mmmmmm
*@param str the string rappresentation of the angle in (d)ddmm.mmmm format
*@param dir if true the direction is south, and the angle is negative.
*@return the given angle in dd.mmmmmm format.
*/
float convert(String str, boolean dir)
{
  double mm, dd;
  int point = str.indexOf('.');
  dd = str.substring(0, (point - 2)).toFloat();
  mm = str.substring(point - 2).toFloat() / 60.00;
  return (dir ? -1 : 1) * (dd + mm);
}

/**
*Gets gps informations
*@param info gpsSentenceInfoStruct is a struct containing NMEA sentence infomation
*@return the number of hooked satellites, or 0 if there was an error getting informations
*/
int getData(gpsSentenceInfoStruct* info)
{
  Serial.println("Collecting GPS data.");
  LGPS.getData(info);
//  Serial.println((char*)info->GPGGA);
  if (info->GPGGA[0] == '$')
  {
    Serial.println("Parsing GGA data....");
    String str = (char*)(info->GPGGA);
    str = str.substring(str.indexOf(',') + 1);
    hour = str.substring(0, 2).toInt();
    minute = str.substring(2, 4).toInt();
    second = str.substring(4, 6).toInt();
    time_format = "";
    time_format += hour;
    time_format += ":";
    time_format += minute;
    time_format += ":";
    time_format += second;
    str = str.substring(str.indexOf(',') + 1);
    latitude = convert(str.substring(0, str.indexOf(',')), str.charAt(str.indexOf(',') + 1) == 'S');
    int val = latitude * 1000000;
    String s = String(val);
    lat_format = s.substring(0, (abs(latitude) < 100) ? 2 : 3);
    lat_format += '.';
    lat_format += s.substring((abs(latitude) < 100) ? 2 : 3);
    str = str.substring(str.indexOf(',') + 3);
    longitude = convert(str.substring(0, str.indexOf(',')), str.charAt(str.indexOf(',') + 1) == 'W');
    val = longitude * 1000000;
    s = String(val);
    lon_format = s.substring(0, (abs(longitude) < 100) ? 2 : 3);
    lon_format += '.';
    lon_format += s.substring((abs(longitude) < 100) ? 2 : 3);

    sat_num = str.substring(0, 2).toInt();

    String Latitude = String(latitude, 5);
    String Longitude = String(longitude, 5);
    String Sat_num = String(sat_num);
    
//    Serial.println("Data comming in......");
//    Serial.print("Latitude :");
//    Serial.println(Latitude);
//    Serial.print("Longitude :");
//    Serial.println(longitude);
//    Serial.print("No of satellites being tracked :");
//    Serial.println(Sat_num);
//    Serial.println("done.");
  
    
//    if (info->GPRMC[0] == '$')
//    {
//      Serial.print("Parsing RMC data....");
//      str = (char*)(info->GPRMC);
//      int comma = 0;
//      for (int i = 0; i < 60; ++i)
//      {
//        if (info->GPRMC[i] == ',')
//        {
//          comma++;
//          if (comma == 7)
//          {

//            comma = i + 1;
//            break;
//          }
//        }
//      }
//
//      day = str.substring(0, 2).toInt();
//      month = str.substring(2, 4).toInt();
//      year = str.substring(4, 6).toInt();
//      date_format = "20";
//      date_format += year;
//      date_format += "-";
//      date_format += month;
//      date_format += "-";
//      date_format += day;
//      Serial.println("done.");
//      return sat_num;
//    }
//  }
//  else
//  {
//    Serial.println("No GGA data");
//  }
//  return 0;
}
}
//'''''''''' ./GPS Functions ''''''''''//





//--------------------------------------------------------------------------
void reportdata() 
{
  Serial.println("Sensing data for threshold \n\n");
  if(dht.read())
  {   
        Serial.println("Starting to read temperature");
        tempC = dht.readTemperature();
        localtemp = tempC;
        //Humi = dht.readHumidity();

//##### For testing purposes of DHT #####//
/*      Serial.println("*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*");
        Serial.print("Temperature Celsius = ");
        Serial.print(dht.readTemperature());
        Serial.println("C");
*/
//##### Readings to be added later #####//
/* 
        Serial.print("Temperature Fahrenheit = ");
        Serial.print(dht.readTemperature(false));
        Serial.println("F");

        Serial.print("Humidity = ");
        Serial.print(dht.readHumidity());
        Serial.println("%");

        Serial.print("HeatIndex = ");
        Serial.print(dht.readHeatIndex(tempC,Humi));
        Serial.println("C");

        Serial.print("DewPoint = ");
        Serial.print(dht.readDewPoint(tempC,Humi));
        Serial.println("C");
*/   }
    delay(2000);
  //---------- ./DHT Loop ----------//

  //---------- GPS Loop ----------//
//  Serial.println("*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*");
    if (getData(&info) > 3)   //Start retriving data if no of satellites being tracked are greater than 3
    {
      String str = "|";
      str += date_format;
      str += ",";
      str += time_format;
      str += ",";
      str += lat_format;
      str += ",";
      str += lon_format;
      str += ",";
      str += sat_num;
      str += "|";
  //    Serial.println(str);
    }
    else
    Serial.println("Less then 4 satelites.");
    delay(pause);
  //---------- ./GPS Loop ----------//
    
    locallat = latitude;
    locallong = longitude;  
}


//--------------------------------------------------------------------------
void sendreportdata() 
{
  Serial.println( "Sensing data for threshold \n\n");
  if(dht.read())
  {   
        Serial.println("Starting to read temperature");
        tempC = dht.readTemperature();
        slocaltemp = (String)tempC;
        //Humi = dht.readHumidity();

//##### For testing purposes of DHT #####//
/*      Serial.println("*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*");
        Serial.print("Temperature Celsius = ");
        Serial.print(dht.readTemperature());
        Serial.println("C");
*/
//##### Readings to be added later #####//
/* 
        Serial.print("Temperature Fahrenheit = ");
        Serial.print(dht.readTemperature(false));
        Serial.println("F");

        Serial.print("Humidity = ");
        Serial.print(dht.readHumidity());
        Serial.println("%");

        Serial.print("HeatIndex = ");
        Serial.print(dht.readHeatIndex(tempC,Humi));
        Serial.println("C");

        Serial.print("DewPoint = ");
        Serial.print(dht.readDewPoint(tempC,Humi));
        Serial.println("C");
*/   }
    delay(2000);
  //---------- ./DHT Loop ----------//

  //---------- GPS Loop ----------//
//  Serial.println("*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*");
    if (getData(&info) > 3)   //Start retriving data if no of satellites being tracked are greater than 3
    {
      String str = "|";
      str += date_format;
      str += ",";
      str += time_format;
      str += ",";
      str += lat_format;
      str += ",";
      str += lon_format;
      str += ",";
      str += sat_num;
      str += "|";
  //    Serial.println(str);
    }
    else
    Serial.println("Less then 4 satelites.");
    delay(pause);
  //---------- ./GPS Loop ----------//
    
    slocallat = (String)latitude;
    slocallong = (String)longitude;

    String payload = "{";
  payload += "\"Temperature\":\""; payload += slocaltemp; payload += "\", ";
  payload += "\"Latitude\":\""; payload += slocallat; payload += "\", ";
  payload += "\"Longitude\":\""; payload += slocallong; payload += "\"";
  payload += "}";

      char analogData[100];
      Serial.println(payload);
      payload.toCharArray( analogData, 100 ); //copies the contents of the payload to the buffer 'analogData'
      client.publish( "sidsat", analogData ); //publishes to the topic sidsat
      Serial.println( analogData );
      Serial.println("Sending alert data");
      delay(500);
}
