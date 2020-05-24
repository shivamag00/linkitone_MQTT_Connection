// LinkIt One sketch for MQTT Demo

#include <LWiFi.h>
#include <LWiFiClient.h>

#include <PubSubClient.h>

/* 
	Modify to your WIFI Access Credentials. 
*/
#define WIFI_AP "moto e5 plus 8607"
#define WIFI_PASSWORD "12345678"
#define WIFI_AUTH LWIFI_WPA  // choose from LWIFI_OPEN, LWIFI_WPA, or LWIFI_WEP.

/*
	Modify to your MQTT broker - Select only one
*/
//char mqttBroker[] = "iot.eclipse.org";
 byte mqttBroker[] = {192,168,43,2}; // modify to your local broker
char tp = '0';
char gp = '0';
LWiFiClient wifiClient;

PubSubClient client( wifiClient );

unsigned long lastSend;




void setup()
{
   delay(10000);
   Serial.begin(115200);
   Serial.print("HI");
   InitLWiFi();

   client.setServer( mqttBroker, 1883 );
   client.setCallback( callback );

   lastSend = 0;
}

void loop()
{
  
  if( !client.connected() ) {
    reconnect();
  }

  if( millis()-lastSend > 5000 ) {	// Send an update only after 5 seconds
    sendAnalogData();
    lastSend = millis();
  }
  
  client.loop();
}

void callback( char* topic, byte* payload, unsigned int length ) {
  Serial.print( "Recived message on Topic:" );
  Serial.print( topic );
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
  Serial.print( "    Message:");
  for (int i=0;i<length;i++) {
    Serial.print( (char)payload[i] );
  }
  Serial.println();
  Serial.println(tp);
  Serial.println(gp);
  Serial.println();
}

void sendAnalogData() {
  // Read data to send
  String data_A0;
  String data_A1;
  String data_A2;
  if (tp=='1')
  {
    data_A0 = (String)analogRead( A0 );
  }
  else
   data_A0 = "off";

   if (gp=='1') 
   {
    data_A1 = (String)analogRead( A1 );
    data_A2 = (String)analogRead( A2 );
   }
   else
   {
     data_A1 = "off";
    data_A2 = "off";
   }

  // Just debug messages
  Serial.print( "Sending analog data : [" );
  Serial.print( data_A0 ); Serial.print( data_A1 ); Serial.print( data_A2 );
  Serial.print( "]   -> " );

  // Prepare a JSON payload string
  String payload = "{";
  payload += "\"Temperature\":\""; payload += data_A0; payload += "\", ";
  payload += "\"Latitude\":\""; payload += data_A1; payload += "\", ";
  payload += "\"Longitude\":\""; payload += data_A2; payload += "\"";
  payload += "}";
  
  // Send payload
  char analogData[100];
  payload.toCharArray( analogData, 100 );
  client.publish( "sidsat", analogData );
  Serial.println( analogData );
}

void InitLWiFi()
{
  LWiFi.begin();
  // Keep retrying until connected to AP
  Serial.println("Connecting to AP");
  while (0 == LWiFi.connect(WIFI_AP, LWiFiLoginInfo(WIFI_AUTH, WIFI_PASSWORD))) {
    delay(1000);
  }
  Serial.println("Connected to AP");
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Connecting to MQTT broker ...");
    // Attempt to connect
    if ( client.connect("LinkIt One Client") ) {  // Better use some random name
      Serial.println( "[DONE]" );
      // Publish a message on topic "outTopic"
      client.publish( "sidsat","Hello, This is LinkIt One" );
    // Subscribe to topic "inTopic"
      client.subscribe( "temp" );
      client.subscribe( "gps" );
    } else {
      Serial.print( "[FAILED] [ rc = " );
      Serial.print( client.state() );
      Serial.println( " : retrying in 5 seconds]" );
      // Wait 5 seconds before retrying
      delay( 5000 );
    }
  }
}
