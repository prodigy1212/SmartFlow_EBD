// Include RadioHead Amplitude Shift Keying Library
#include <RH_ASK.h>
// Include dependant SPI Library 
#include <SPI.h> 
 
// Define output strings
 
// Create Amplitude Shift Keying Object
//Note: pin13=relay signal, pin11=receiver signal 
RH_ASK rf_driver;
 
void setup()
{
  Serial.begin(9600 );
  // Initialize ASK Object
  if (!rf_driver.init()){
    Serial.println("init failed");  
     pinMode(13,OUTPUT);
  }
    
}
 
void loop()
{
    // Set buffer to size of expected message
    
    uint8_t buf[20];
    uint8_t buflen = sizeof(buf);
    
    // Check if received packet is correct size
    Serial.println("hello ");
    if (rf_driver.recv(buf, &buflen)){
      Serial.println("Received: ");
      Serial.println((char *)buf);
    }
    else {
      Serial.println ("not working ");
    }
     digitalWrite(13,HIGH);    
 
     delay(2000);
     
     analogWrite(13,LOW);
     delay(2000);
}
   
