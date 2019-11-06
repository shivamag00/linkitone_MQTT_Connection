// LinkIt One sketch for MQTT Demo

#include <LWiFi.h>
#include <LWiFiClient.h>
#include <PubSubClient.h>
#include <LSD.h> 
#include<LFlash.h>


/* 
  Modify to your WIFI Access Credentials. 
*/
#define WIFI_AP "Red"
#define WIFI_PASSWORD "12345678"
#define WIFI_AUTH LWIFI_WPA  // choose from LWIFI_OPEN, LWIFI_WPA, or LWIFI_WEP.
#define DRV LFlash
/*
  Modify to your MQTT broker - Select only one
*/
//char mqttBroker[] = "iot.eclipse.org";
byte mqttBroker[] = {192,168,43,2}; // modify to your local broker
char tp = '0'; //Temperature Control
char gp = '0'; //GPS Control
LWiFiClient wifiClient;
PubSubClient client( wifiClient );
unsigned long lastSend;
bool AP_Connect = false;
bool server_Connect = false;

//--------------------------------------------------------------------------
void setup()
{
   delay(10000);//10s delay
   Serial.begin(115200);
   Serial.print("HI");
  

   

   client.setServer( mqttBroker, 1883 ); //Setting the mqtt server
   client.setCallback( callback ); //Sets the callback function which will be called when a message is received

   lastSend = 0; //Denotes the time elapsed from the start of the program to the point when the data was sent via publish command    
}

//--------------------------------------------------------------------------
void loop()
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
  {
    if ((char)payload[0]=='0')
      tp = '0';
    else 
      tp ='1'; 

  
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
    data_A0 = (String)analogRead( A0 );  //temperature code here
  }
  else
   data_A0 = "f";

   if (gp=='1') 
   {
    data_A1 = (String)analogRead( A1 ); //gps code here
    data_A2 = (String)analogRead( A2 );
   }
   else
   {
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
      while (i<=51)
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
