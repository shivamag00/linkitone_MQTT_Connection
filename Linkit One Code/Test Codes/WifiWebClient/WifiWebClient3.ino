/*
  Web client

 This sketch connects to a website 
 using Wi-Fi functionality on MediaTek LinkIt platform.

 Change the macro WIFI_AP, WIFI_PASSWORD, WIFI_AUTH and SITE_URL accordingly.

 created 13 July 2010
 by dlf (Metodo2 srl)
 modified 31 May 2012
 by Tom Igoe
 modified 20 Aug 2014
 by MediaTek Inc.
 */

#include <LWiFi.h>
#include <LWiFiClient.h>

#define WIFI_AP "_____________"
#define WIFI_PASSWORD "_____________"
#define WIFI_AUTH LWIFI_WPA  // choose from LWIFI_OPEN, LWIFI_WPA, or LWIFI_WEP.
#define SITE_URL "192.168.137.2"
#define tempPin A0

int tempValue = 0;

LWiFiClient c;

void setup()
{
  delay(10000);
  
  LWiFi.begin();
  Serial.begin(115200);

  // keep retrying until connected to AP
  Serial.println("Connecting to AP");
  while (0 == LWiFi.connect(WIFI_AP, LWiFiLoginInfo(WIFI_AUTH, WIFI_PASSWORD)))
  {
    
    delay(1000);
  }
}
  
  
void loop()
{
 delay(10000);
 tempValue = analogRead(tempPin);
 float temp = tempValue * 0.48828125;
 String tmp = String(temp);
 Serial.println("Temperature :");
 Serial.print(temp);
 Serial.print("*C");
 //delay(10000);

// keep retrying until connected to website
  Serial.println("Connecting to WebSite");
  while (0 == c.connect(SITE_URL, 80))
  {
    Serial.println("Re-Connecting to WebSite");
    delay(1000);
  }




  // send HTTP request, ends with 2 CR/LF
 char d1[]="firstname=Temperature&lastname=";
 char d2[] = "&email=141";
 String thisData = d1 + tmp +d2;
 //create a char array for sending data 
//send the header
c.println("POST /stack/database_connection.php HTTP/1.1");           //define POST path
 
c.println("Host: " SITE_URL);           //define hostname  
c.println("Connection: close");
 
c.println("Content-Type: application/x-www-form-urlencoded");     //define Content-Type 
c.print("Content-Length: ");                     //define Content-Length 
c.println(43);
c.println();
 
// send the body (variables)
c.print(thisData);
  // waiting for server response
  Serial.println("waiting HTTP response:");
//  while (!c.available())
 // {
   // delay(100);
 // }


/*boolean disconnectedMsg = false;


  // Make sure we are connected, and dump the response content to Serial
  while (c)
  {
    
    int v = c.read();
    if (v != -1)
    {
      Serial.print((char)v);
    }
    else
    {
      Serial.println("no more content, disconnect");
      c.stop();
      while (1)
      {
        delay(1);
      }
    }
  }

  if (!disconnectedMsg)
  {
    Serial.println("disconnected by server");
    disconnectedMsg = true;
  }
  delay(500);*/
}
