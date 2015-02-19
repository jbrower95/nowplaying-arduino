// This sketch is for Arduino versions 1.0 and later
#include <SoftwareSerial.h>

//Attach the display's transmit line to digital pin 5.
SoftwareSerial mySerial(3,5); // pin 5 = TX, pin 3 = RX (unused)

void setup()
{
  Serial.begin(9600);   // set up serial connection for communication over USB
  mySerial.begin(9600); // set up Display serial port for 9600 baud
  delay(500);           // wait for display to boot up
  clearDisplay();
  moveToBeginning();
}

void clearDisplay()
{
//this is enough characters to clear off two columns of the display.
 mySerial.write("                "); // clear display
 mySerial.write("                "); 
}

void moveToBeginning()
{
  //write these characters to move to the beginning (from display docs)
  mySerial.write(254);
  mySerial.write(128); 
}
void loop()
{
  
  while(true) {
   
    //wait for data to become available
    while (Serial.available()==0);
    
    unsigned int availableBytes = Serial.available();
    char output[availableBytes+1];
    //declare one more byte than necessary for a null terminator

    int bytesRead = 0;
    while (bytesRead < availableBytes){
      //continue to read bytes until we've read all of them
      output[bytesRead] = Serial.read();
      bytesRead++;
    }    

    //null terminate the output string
    output[bytesRead] = 0;
      
    moveToBeginning();
    clearDisplay();
    moveToBeginning();
    mySerial.write(output);
  } 
  
}

