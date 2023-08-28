// Include RadioHead Amplitude Shift Keying Library

#include <RH_ASK.h>
// Include dependant SPI Library 
#include <SPI.h> 
#include "SoftwareSerial.h"
SoftwareSerial mySerial(2, 3);
#define rxPin 2
#define txPin 3
const String APN  = "internet";
const String USER = "";
const String PASS = "";

const String FIREBASE_HOST  = "https://smartflow-36cce-default-rtdb.europe-west1.firebasedatabase.app/";
const String FIREBASE_SECRET  = "fyQlG8FBOJgFHOFb6RxUVGtet8zoGgN0PB38xaYP";
 
// Define output strings
 
// Create Amplitude Shift Keying Object
//Note: pin13=relay signal, pin11=receiver signal 
RH_ASK rf_driver;
uint8_t buf[14];
    uint8_t buflen = sizeof(buf);
    unsigned long previousMillis_Read = 0; // Store the last time an action was performed
    const unsigned long interval_Read = 4000; // Interval in milliseconds (10  second)
    unsigned long previousMillis_Trans = 0; //
    const unsigned long interval_Trans = 1000;
     char Crop_Type='T', Crop_Stage='V'; 
     int D_moisture=0; float D_temp=0.00; float D_hum=0.00 ; // this variable holds values from environment after they are decoded     
     int bufsize=16;
    void  Read_Sensor(){
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
        
          if (i==10){
             Serial.println ("Can't from environment ");
           exit (1);               
          }  
    }                 
      void decode (int &moisture, float &temp, float &hum,uint8_t buff[14]){
            String holder;
             String sub_hum;
             String sub_mois;
              String sub_temp;
            for (int i = 0; i < sizeof(buf); i++) {
                            
              holder += char(buf[i]);
              Serial.println(holder) ;
            }
            Serial.println(holder);
            
            if(holder.substring(1,2) == "," ){
               sub_mois= holder.substring(0,1);
               sub_hum= holder.substring(2,7);
              sub_temp= holder.substring(8,13);
            } 
            else{
               sub_mois= holder.substring(0,2);
              sub_hum= holder.substring(3,8);
              sub_temp= holder.substring(9,14);
            }
      
            
            moisture=  sub_mois.toInt();  
             temp= sub_temp.toFloat();
              hum= sub_hum.toFloat();             
               
        
      } 
       
      void Irrigate(/*char Crop_T,char Crop_S,int Temp,int hum,*/ int Soil_M){
       // if conditions are met, irrigate.
           decode( D_moisture, D_temp, D_hum,buf);
          if(!(D_moisture>=50)){
               digitalWrite(8,HIGH );  
                Serial.println("pump is UP");      
                               delay(2000);
                    digitalWrite(8,LOW);  
                                                                                      
                         
          }  
          else{
           Serial.println("Not time to irrigate");            
          }                   
                                   
                                        
        
      }
 
void setup()
{
  Serial.begin(9600 );
  // Initialize ASK Object
  pinMode(8,OUTPUT);  
 //from here we check whether environment substation is attached and work, and we also check for GSM module
  if (!rf_driver.init()){
    Serial.println("init failed"); 
         
     exit (1);     
    }
  
    //Begin serial communication with SIM800
 /*   
   SIM800.begin(9600);
  
   Serial.println("Initializing SIM800...");
   init_gsm();
    // after checking environment,we check for a connection to the GSM for the first time. if all is well then we enter the loop 
*/    
 }
 
void loop()
 {
    
 unsigned long currentMillis_Read = millis(); // Get the current time   
  if (currentMillis_Read - previousMillis_Read >= interval_Read) {
        // check sensors to see where it is time to irrigate 
        Read_Sensor(); 
        Irrigate(D_moisture);  
       
          Serial.println("moistur:");
           Serial.println(D_moisture);          
          Serial.println ("tempeture:");
          Serial.println (D_temp);
          Serial.println("humity:");   
          Serial.println(D_hum);   
             
    previousMillis_Read = currentMillis_Read; 
     delay(5000);     
   
  } 
  /*
unsigned long currentMillis_Trans = millis(); // Get the current time   
  if (currentMillis_Trans - previousMillis_Trans >= interval_Trans) {
        // check sensors to see where it is time to irrigate 
    previousMillis_Trans = currentMillis_Trans;
  }
*/  
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
   
}
*/


