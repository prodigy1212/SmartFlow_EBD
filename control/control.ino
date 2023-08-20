// Include RadioHead Amplitude Shift Keying Library
#include <RH_ASK.h>
// Include dependant SPI Library 
#include <SPI.h> 
 
// Define output strings
 
// Create Amplitude Shift Keying Object
//Note: pin13=relay signal, pin11=receiver signal 
RH_ASK rf_driver;
uint8_t buf[20];
    uint8_t buflen = sizeof(buf);
    unsigned long previousMillis = 0; // Store the last time an action was performed
    const unsigned long interval = 10000; // Interval in milliseconds (10 second)
      
 
void setup()
{
  Serial.begin(9600 );
  // Initialize ASK Object
pinMode(13,OUTPUT);  
/* from here we check whether environment substation is attached and work, and we also check for GSM module*/
  if (!rf_driver.init()){
    Serial.println("init failed"); 
         
     exit (1);     
  }
  int i=0;
  while( i<=10){
 if (rf_driver.recv(buf, &buflen)){
      Serial.println("Received:  ");
      Serial.println((char *)buf);
      break;
    }
    else {
      i++;    }
      delay(2000);
  }      
        
    if (i==11){
      Serial.println ("Can't from environment ");
      exit (1);               
    }  
    // after checking environment,we check for a connection to the GSM for the first time. if all is well then we enter the loop 
}
 
void loop()
{
    
 unsigned long currentMillis = millis(); // Get the current time   
  if (currentMillis - previousMillis >= interval) {
        // check sensors to see where it is time to irrigate 
    previousMillis = currentMillis;
  } 
    
    /*
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
   */
}
   
