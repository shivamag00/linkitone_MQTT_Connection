#include <LFlash.h>
#include <LSD.h>
#include <LStorage.h>
#include <LGPS.h>
#include <LWiFi.h>
#include <LWiFiClient.h>

//Modify to your wifi connection details
#define WIFI_AP "moto e5 plus 8607"
#define WIFI_PASSWORD "12345678"
#define WIFI_AUTH LWIFI_WPA  // choose from LWIFI_OPEN, LWIFI_WPA, or LWIFI_WEP.
#define SITE_URL "192.168.43.2" //Site URL to which we have to connect to.
#define tempPin A0 //Pin for measuring temperature

int tempValue = 0;
LWiFiClient c;

//uncomment the storage you want to use
#define Drv LFlash          // use Internal 10M Flash
// #define Drv LSD           // use SD card

//-----------------------------------------------------------------------------------------------------------------
//Definitions for GPS Data
gpsSentenceInfoStruct info; //needed to get GPS data

double latitude = 0.00;
double longitude = 0.00;
float altitude = 0.00;
float dop = 100.00; //dilution of precision
float geoid = 0.00;
float k_speed = 0.00, m_speed = 0.00; //speed in knots and speed in m/s
float track_angle = 0.00;
int fix = 0;
int hour = 0, minute = 0, second = 0;
int sat_num = 0; //number of visible satellites
int day = 0, month = 0, year = 0;
String time_format = "00:00:00", date_format = "00:00:0000";
String lat_format = "0.00000", lon_format = "0.00000";
char file[15] = "";
int pause = 3000; //time in milliseconds between two logs

//-----------------------------------------------------------------------------------------------------------------
void setup()
{
	delay(5000); //Delay given to give time to open serial monitor before the program runs
	LWiFi.begin();
	Serial.begin(115200);
}


//-----------------------------------------------------------------------------------------------------------------
void loop()
{
	delay(10000);
  
	// keep retrying until connected to AP
	Serial.println("Connecting to AP");
	while (0 == LWiFi.connect(WIFI_AP, LWiFiLoginInfo(WIFI_AUTH, WIFI_PASSWORD)))
	{
    	delay(1000); //Retry after every 1s
	}
  
  	// keep retrying until connected to website
  	Serial.println("Connecting to WebSite");
  	while (0 == c.connect(SITE_URL, 80))
  	{
    	Serial.println("Re-Connecting to WebSite");
    	delay(1000); //Retry after every 1s
  	}

  	// send HTTP request, ends with 2 CR/LF
  	Serial.println("Sending HTTP GET request");
  	c.println("GET /medfin/linkit_rqtgps.php HTTP/1.1");
  	c.println("Host: " SITE_URL);
  	c.println("Connection: close");
  	c.println();

  	// waiting for server response
  	Serial.println("waiting HTTP response:");
  	while (!c.available()) //if incoming data is not available, wait for .1s for the server to respond 
  	{
    	delay(100);
  	}
  
  	boolean disconnectedMsg = false;  
  	delay(10000);
  
  	// Make sure we are connected, and dump the response content to Serial
	char query[1000];
  	int g=0;
  	while (c)
  	{
    	//read the bytes obtained from server
    	int v = c.read();
    	if (v != -1)
    	{
      		Serial.print((char)v);
      		query[g]=(char)v;
      		g++;
    	}
    	else
    	{
      		Serial.println("no more content, disconnect");
      		c.stop();
      
      ///<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<INFINITE LOOP>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>  ??????????
      		while (1)
      		{
        		delay(1);
      		}
      ///<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<INFINITE LOOP>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>  ??????????
    	}
  	}
  
 
  	//Searching for a particular keyword in the response obtained from the sever.
  	char keyword[]="Sidsat";
    
  	// We search for the keyword in the query and copy the data after it in another array 'main_query'
  	char main_query[300];
  	int i = 0 , j = 0;
  	//i traverses through the query while j traverses through the keyword.
  	for(i = 0 ; query[i] != '\0' ; i++)
  	{
    	if (query[i]=='\n')
    	continue;
    	if(keyword[j] == query[i])
    	{
      		j++;
    	}
        else
    	{
      		j = 0;
    	}
    
    	if(j == strlen(keyword))
      		break;
    
  	}
  
  	i = i + 1;
    if(j == strlen(keyword))
  	{
    	for( j = i; query[j] != '\0' ; j++)
    	{
       		main_query[j-i] = query[j]; 
       	}
        main_query[j - i] = '\0'; 
    }
  
  	//If GPS Control 1, switch on the gps
  	if(main_query[0]=='1')
  	{
 		LGPS.powerOn();
    	Serial.println("GPS started.");
    	Serial.print("\nGPS ON\n");
    	getData(&info);
  	}
  	else
  	{
    	Serial.print("\nGPS OFF\n");
    	LGPS.powerOff();
  	} 
    
  	if (!disconnectedMsg)
  	{
    	Serial.println("disconnected by server");
    	disconnectedMsg = true;
  	}
  	delay(500);
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

	//Controlling Temperature
	delay(10000);

  	// keep retrying until connected to website
  	Serial.println("Connecting to WebSite");
  	while (0 == c.connect(SITE_URL, 80))
  	{
    	Serial.println("Re-Connecting to WebSite");
    	delay(1000);
  	}

  	// send HTTP request, ends with 2 CR/LF
  	Serial.println("send HTTP GET request");
  	c.println("GET /medfin/linkit_rqt.php HTTP/1.1");
  	c.println("Host: " SITE_URL);
  	c.println("Connection: close");
  	c.println();

  	// waiting for server response
  	Serial.println("waiting HTTP response:");
  	while (!c.available())
  	{
   		delay(100);
  	}
  
	disconnectedMsg = false;  
  
  
	delay(10000);
	// Make sure we are connected, and dump the response content to Serial
	char query1[1000];
	g=0;
	while (c)
	{
    	int v = c.read();
    	if (v != -1)
    	{
      		Serial.print((char)v);
      		query1[g]=(char)v;
      		g++;
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
  
  	//keyword[]="Sidsat";
    // We search for the keyword in the query and copy the data after it in another array.
  	char main_query1[300];
   	i = 0 , j = 0;
  	//i traverses through the query while j traverses through the keyword.
  	for(i = 0 ; query[i] != '\0' ; i++)
  	{
    	if (query1[i]=='\n')
    		continue;
    	if(keyword[j] == query1[i])
    	{
      		j++;
    	}
    	else
    	{
      		j = 0;
   	 	}
        if(j == strlen(keyword))
      		break;
    
  	}
  
  	i = i + 1;
    if(j == strlen(keyword))
  	{
      	for( j = i; query1[j] != '\0' ; j++)
    	{
       		main_query1[j-i] = query1[j]; 
    	}
    	main_query1[j - i] = '\0'; 
   	}
  
  	if(main_query1[0]=='1')
  	{
    	Serial.print("\nTemp ON\n");
    	getTemp();
  	}
  	else
  	{
    	Serial.print("\nTemp OFF\n");
    } 
    
  	if (!disconnectedMsg)
  	{
    	Serial.println("disconnected by server");
   		disconnectedMsg = true;
  	}
  	delay(500);
}




//---------------------------------------------------------------------------------------------------------------------------------------------
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




//---------------------------------------------------------------------------------------------------------------------------------------------
/**
*Gets gps informations
*@param info gpsSentenceInfoStruct is a struct containing NMEA sentence infomation
*@return the number of hooked satellites, or 0 if there was an error getting informations
*/
int getData(gpsSentenceInfoStruct* info)
{
  	Serial.println("Collecting GPS data.");
  	LGPS.getData(info); //Collects GPS Data in two ways - GPGGA and RMC using NMEA 0183 protocol.
  	Serial.println((char*)info->GPGGA); //defining the type of format (in this case GPGGA) of which we require data
  	if (info->GPGGA[0] == '$')
  	{
    	Serial.print("Parsing GGA data....");
    	String str = (char*)(info->GPGGA);
    	str = str.substring(str.indexOf(',') + 1);

    	//Extracting Time Information from the Data
    	hour = str.substring(0, 2).toInt();
    	minute = str.substring(2, 4).toInt();
    	second = str.substring(4, 6).toInt();
    	time_format = "";
    	time_format += hour;
    	time_format += ":";
    	time_format += minute;
    	time_format += ":";
    	time_format += second;

    	//Extracting Latitude Information from data
    	str = str.substring(str.indexOf(',') + 1);
    	latitude = convert(str.substring(0, str.indexOf(',')), str.charAt(str.indexOf(',') + 1) == 'S');
    	
    	//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<USELESS LINES>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    	int val = latitude * 1000000;
    	//Converting float value to String
    	String s = String(val);
    	lat_format = s.substring(0, (abs(latitude) < 100) ? 2 : 3);
    	lat_format += '.';
    	lat_format += s.substring((abs(latitude) < 100) ? 2 : 3);
    	//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<USELESS LINES end>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

    	//Extracting Latitude Information from data
    	str = str.substring(str.indexOf(',') + 3);
    	longitude = convert(str.substring(0, str.indexOf(',')), str.charAt(str.indexOf(',') + 1) == 'W');
    	val = longitude * 1000000;

    	//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<USELESS LINES>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    	s = String(val);
    	//Converting Float to String
    	lon_format = s.substring(0, (abs(longitude) < 100) ? 2 : 3);
    	lon_format += '.';
    	lon_format += s.substring((abs(longitude) < 100) ? 2 : 3);

    	//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<USELESS LINES end>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    	//Converting latitude and longitude to string
    	String latPlot = String(latitude);
    	String longPlot = String(longitude);
     	Serial.println("*******************************************");
    	Serial.println(latPlot) ;
    	Serial.println("*******************************************");
   		Serial.println("*******************************************");
    	Serial.println(longPlot) ;
    	Serial.println("*******************************************");


 		// keep retrying until connected to website
  		Serial.println("Connecting to WebSite");
  		while (0 == c.connect(SITE_URL, 80))
 	 	{
    		Serial.println("Re-Connecting to WebSite");
    		delay(1000);
 	 	}
  		// send HTTP request, ends with 2 CR/LF
 		//char d1[]="temp=";
 		char d3[]="lat=";
 		char d2[] = "&long=";
 		String thisData = d3 +  latPlot +d2+longPlot;
 		//create a char array for sending data 
		//send the header
		c.println("POST /medfin/gps.php HTTP/1.1");           //define POST path
 		c.println("Host: " SITE_URL);           //define hostname  
		c.println("Connection: close");
 		c.println("Content-Type: application/x-www-form-urlencoded");     //define Content-Type 
		c.print("Content-Length: ");                     //define Content-Length 
		c.println(20);
		c.println();
 
		// send the body (variables)
		c.print(thisData);

	    
		//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<USELESS LINES>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
	    str = str.substring(str.indexOf(',') + 3);
	    fix = str.charAt(0) - 48;
	    str = str.substring(2);
	    sat_num = str.substring(0, 2).toInt();
	    str = str.substring(3);
	    dop = str.substring(0, str.indexOf(',')).toFloat();
	    str = str.substring(str.indexOf(',') + 1);
	    altitude = str.substring(0, str.indexOf(',')).toFloat();
	    str = str.substring(str.indexOf(',') + 3);
	    geoid = str.substring(0, str.indexOf(',')).toFloat();
	    Serial.println("done.");
    
	    if (info->GPRMC[0] == '$')
	    {
	      	Serial.print("Parsing RMC data....");
	      	str = (char*)(info->GPRMC);
	      	int comma = 0;
	      	for (int i = 0; i < 60; ++i)
	      	{
	        	if (info->GPRMC[i] == ',')
	        	{
	          		comma++;
	          		if (comma == 7)
	          		{
	            		comma = i + 1;
	            		break;
	          		}
        		}
      		}

			str = str.substring(comma);
			k_speed = str.substring(0, str.indexOf(',')).toFloat();
			m_speed = k_speed * 0.514;
			str = str.substring(str.indexOf(',') + 1);
			track_angle = str.substring(0, str.indexOf(',')).toFloat();
			str = str.substring(str.indexOf(',') + 1);
			day = str.substring(0, 2).toInt();
			month = str.substring(2, 4).toInt();
			year = str.substring(4, 6).toInt();
			date_format = "20";
			date_format += year;
			date_format += "-";
			date_format += month;
			date_format += "-";
			date_format += day;
			Serial.println("done.");
			return sat_num;
   		}
   		//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<USELESS LINES>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
   	}
  	else
  	{
    	Serial.println("No GGA data");
  	}
  	return 0;
}


//---------------------------------------------------------------------------------------------------------------------------------------------

int getTemp()
{
  	tempValue = analogRead(tempPin);
 	float temp = tempValue * 0.48828125;
 	String tmp = String(temp);
 	Serial.println("Temperature :");
 	Serial.print(temp);
 	Serial.print("*C");

 	// keep retrying until connected to website
  	Serial.println("Connecting to WebSite");
  	while (0 == c.connect(SITE_URL, 80))
  	{
    	Serial.println("Re-Connecting to WebSite");
    	delay(1000);
  	}
  	// send HTTP request, ends with 2 CR/LF
 	char d1[]="temp=";
  	String thisData = d1 + tmp;
 	//create a char array for sending data 
	//send the header
	c.println("POST /medfin/temperature.php HTTP/1.1");           //define POST path
	c.println("Host: " SITE_URL);           //define hostname  
	c.println("Connection: close");
	c.println("Content-Type: application/x-www-form-urlencoded");     //define Content-Type 
	c.print("Content-Length: ");                     //define Content-Length 
	c.println(10);
	c.println();
	// send the body (variables)
	c.print(thisData);
    return 0;
}