/*
  SD card read/write

 This example shows how to read and write data to and from an SD card file
 The circuit:

 created   Nov 2010
 by David A. Mellis
 modified 9 Apr 2012
 by Tom Igoe

 port to LinkIt ONE
 by Loovee
 2014-10-12


 This example code is in the public domain.

 */

#include <LFlash.h>
#include <LSD.h>
#include <LStorage.h>

#define Drv LFlash          // use Internal 10M Flash
// #define Drv LSD           // use SD card

LFile myFile;

void setup()
{
    // Open serial communications and wait for port to open:
    Serial.begin(9600);
    
    while(!Serial.available());         // input any thing to start

    Serial.print("Initializing Storage card...");

    pinMode(10, OUTPUT);

    Drv.begin();

    // open the file. note that only one file can be open at a time,
    // so you have to close this one before opening another.
    Drv.remove("test.txt");
    myFile = Drv.open("test.txt", FILE_WRITE);

    // if the file opened okay, write to it:
    if (myFile) {
        Serial.print("Writing to test.txt...");
       // while (myFile.size()!=0)
        {
        myFile.seek(myFile.size());
        myFile.print("hi\bf");
        }
        // close the file:
        myFile.print("DONE");
        myFile.close();
        Serial.println("done.");
    } else {
        // if the file didn't open, print an error:
        Serial.println("error opening test.txt");
    }

    // re-open the file for reading:
    myFile = Drv.open("test.txt");
    if (myFile) {
        Serial.println("test.txt:");
        myFile.seek(0);
        String payload;
        char buf;
        buf = char(myFile.read());
        payload = String(buf);
        // read from the file until there's nothing else in it:
        while (myFile.available()) {
            buf = char(myFile.read());
            payload += String(buf);
        }
        // close the file:
        Serial.println(payload);
        Serial.println(payload);
        myFile.close();
    } else {
        // if the file didn't open, print an error:
        Serial.println("error opening test.txt");
    }
}

void loop()
{
    // nothing happens after setup
}
