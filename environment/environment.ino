 // Include the radio head library for RF communication
#include <RH_ASK.h>
#include <Adafruit_Sensor.h>
#include "DHT.h";

// instantiate a driver for the RF module
RH_ASK driver;

// the analog input pin for the soil moisture sensor
int sensorPin = A0;

// variable to store the sensor value in analog form
int sensorValue = 0;

// variable to store the moisture percentage
int moisturePercent = 0;
#define DHTPIN 7 // DHT.22 output Pin connection
#define DHTTYPE DHT11 // DHT type is DHT 22 (AM2303)

float hum; // stores humidity value   

float temp; // stores temperature values
String Str_humid;
String Str_temp;
String Str_out;   // String to store final formatted output 
DHT dht(DHTPIN,DHTTYPE); 

void setup()
{
    // initializes the serial communication at 9600 baud rate
    Serial.begin(9600);

    // sets the digital pin 13 as output
    pinMode(13, OUTPUT);

    //  check if RadioHead rf driver is initialized
    if (!driver.init())
    {
        Serial.println("init failed");
    }
    dht.begin();
    delay (2000);
}

void loop()
{
    // reads the analog value from the sensor
    sensorValue = analogRead(sensorPin); // read soil value 
     delay(2000);
    hum=dht.readHumidity();
    delay(3000);  // get Humidity value 
    temp =dht.readTemperature (); // get temperature 
  
     Str_humid =String(hum,2);
     Str_temp =String (temp,2);
      Str_out=Str_humid +","+Str_temp; 
      Serial.println(hum);
      Serial.println(Str_out +"  "+"DHT value");// concate temperature string value and humidity string value   
    moisturePercent = map(sensorValue, 0, 1023, 0, 100); // maps the sensor value to a range of 0-100

    // prints the moisture percentage to the serial monitor
    Serial.print("Moisture Level: ");
    Serial.print(moisturePercent);
    Serial.println("%");

    // buffer to hold the moisture percentage
    char msg[15];

    // converts the moisture percentage to a string
    sprintf(msg, "%d", moisturePercent);
    String Total = String(msg) + "," +Str_out;   // add  moisture, humidity and temp figure
    const char *final =Total.c_str();  //final figure ready to be transmitted 
    // sends the moisture percentage
    driver.send((uint8_t *)final, strlen(final));

    // waits for the data to be sent
    
    if (driver.waitPacketSent()){
      Serial.println("Data sent\n");
      Serial.println(msg);
    } 

    else {
      Serial.println( "not sent ");
    }

    // prints confirmation message sent to the serial monitor
    

    // waits for 2 second before re-running the loop
    delay(2000);
}

