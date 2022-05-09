#define BLYNK_TEMPLATE_ID           "TMPL4i-ILXAr"                      // Blynk authentification setings
#define BLYNK_DEVICE_NAME           "FIRE"
#define BLYNK_AUTH_TOKEN            "nmLlrS0HjdKN30G8GlU4etBtaWQvkUvV"
#define BLYNK_PRINT Serial                                               // Sending data to Blynk Serial Debug (pir sensor (9600))
#define BLYNK_PRINT SerialUSB                                            // Seding data to the temp sensor (115200)
#include <SPI.h>                                                          //mkr setings for wifi
#include <WiFi101.h>
#include <BlynkSimpleWiFiShield101.h>                                     //blynk settings
#include <DHT.h>                                                          // temp sensor data

char auth[] = BLYNK_AUTH_TOKEN;                                            // authentification information for blynk and wifi
char ssid[] = "VM1635798";
char pass[] = "Jn6vmszkbvvp";

#define DHTPIN 2                                                           // dht to pin 2
#define DHTTYPE DHT11                                                       // seting the type of DHT (11)

DHT dht(DHTPIN, DHTTYPE);                                                 // starting the sensor
BlynkTimer timer;                                                         // upddate timer on blynk
int sensor = 5;                                                           // pin on pin 5
int state = LOW;                                                          // state of the sensor in LOW (HIGH for trigger)
int val =0 ;                                                              // default value is 0
 
void sendSensor()                                                         // reading data from DHT for t and h
{
  float h = dht.readHumidity();                                           // receiving data from the sensor under t and h
  float t = dht.readTemperature(); 

  Blynk.virtualWrite(V5, h);                                               // assigning virtual pins to the t an h
  Blynk.virtualWrite(V6, t);
}
void notifiaction()                                                         // pin starting
 {  
  val = digitalRead(5);                                                     // reading pin 5                                         
  if (val == HIGH)                                                          // if value is high
  {  
   if (state == LOW)                                                        // sensor turned on
   {  
    Serial.println("Movement Detected!!");                                  // alarm!
   }  
   else if (val == HIGH)                                                   // after the val is High then
   {  
   }  
  }   
  else if (state == LOW)                                                    // switch off the sensor
  {  
  }  
 Blynk.virtualWrite(V7, val);                                               // send val data to V7
 }  
void setup()
{
  SerialUSB.begin(115200);                                                  // accessing Blynk
  Blynk.begin(auth, ssid, pass);
  
  dht.begin();                                                              // starting DHT
 
  timer.setInterval(1000L, sendSensor);                                     // Make a fucntion to read every second
  
  Serial.begin(9600);  
  pinMode(5, INPUT);                                                         // pin on pin 5 
  Blynk.begin(auth, ssid, pass);  
  timer.setInterval(1000L, notifiaction);                                     // function to be called every second
 }  
void loop()
{
  Blynk.run();                                                                // running blynk settings
  timer.run();                                                                // following the times on the code
}