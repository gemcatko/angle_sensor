#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <WiFiAP.h>
#include <Wire.h>

#include "index.h"  //Web page header file
 
// Set these to your desired credentials.
const char* ssid = "AP@ESP32";
const char* password = "password";

WebServer server(80);

// A1332 I2C address is 0x0C(12)
byte Addr = 12;

//===============================================================
// Functions
//===============================================================
void whatPorts () { //print out SDA and SCL ports
  Serial.print("SDA Port is: ");
  Serial.println(SDA); 
  Serial.print("SCL Port is: ");
  Serial.println(SCL);   
}
void handleRoot() {
 String s = MAIN_page; //Read HTML contents
 server.send(200, "text/html", s); //Send web page
}
 
void handleValue() {
 float a = getAngle();
 String angleValue = String(a);
 server.send(200, "text/plane", angleValue); //Send value only to client ajax request
}


//function to get magnetic angle
float getAngle() {
  unsigned int data[2];
  byte error;
      
  // Start I2C Transmission 
  Wire.beginTransmission(Addr);
      
  // Stop I2C Transmission 
  //error = Wire.endTransmission();
  //Serial.println(error);
  if (error == 0)
  {
    //Serial.print("I2C device found at address 12");
    // Request 2 byte of data
    Wire.requestFrom(Addr, 2);
      
    // Read 2 bytes of data
    // raw_adc msb, raw_adc lsb 
    if(Wire.available() == 2)
    {
      data[0] = Wire.read();
      data[1] = Wire.read();
    }
    
    // Checking valid data
    while((data[0] == 0) && (data[1] == 0))
    {
      // Request 2 byte of data
      Wire.requestFrom(Addr, 2);
      
      // Read 2 bytes of data
      // raw_adc msb, raw_adc lsb 
      if(Wire.available() == 2)
      {
        data[0] = Wire.read();
        data[1] = Wire.read();
      }
    }
      
    // Convert the data to 12-bits
    int raw_adc = ((data[0] & 0x0F) * 256) + (data[1] & 0xFF);
    float angle = (raw_adc * 360.0) / 4096.0;
      
    //Serial.print("Magnetic Angle : ");
    Serial.println(angle);
    // Output data to serial monitor and return also as function result
    return angle;
  }
  else if (error == 4)
  {
    Serial.print("Unknown error at address 0x");
    return 0;
  }
  else
  {
    Serial.println("No I2C devices found");
    return 0;
  }

}

//===============================================================
// Setup
//===============================================================

void setup() {
  Wire.begin();
  
  Serial.begin(115200);
  Serial.println();
  Serial.println("Stating measurement");
  /*
  //Serial.println("Configuring access point...");
  
  // You can remove the password parameter if you want the AP to be open.
  //WiFi.softAP(ssid, password);
  //IPAddress myIP = WiFi.softAPIP();
  //Serial.print("AP IP address: ");
  //Serial.println(myIP);
  
  //Serial.println("AP started");
  delay(300);

  server.on("/", handleRoot);
  server.on("/readValue", handleValue);//To get update of Value only
  server.begin(); 

  Serial.println("Server started");
  //whatPorts ();
  */
}





void loop() {
  getAngle();
  delay(10);
}
