#include <ESP8266Webhook.h>
#include <ESP8266WiFi.h>
#include "ThingSpeak.h"
#include "HX711.h"
#include <Wire.h>
#define BLYNK_PRINT Serial
#define BLYNK_PRINT Serial
#include <Blynk.h>
#include <BlynkSimpleEsp8266.h>
#include <ESP8266WiFi.h>
#include <Servo.h> // servo library 
#include "NewPing.h"/ /mesafe sensörü kütüphanesi
int servoPin = 0; 
int weightBly;
#define _SSID "Galaxy A51063D"      // Your WiFi SSID
#define _PASSWORD "yjba7177"  // Your WiFi Password
#define KEY "nMnxgnv7TIMgHHPl9I9bnqthPIPmExOnULQSg_q8P7A"        // Webhooks Key
#define EVENT "mama54"      // Webhooks Event Name
unsigned long channelID =1995689;             // Thingspeak channel ID 
unsigned int field_no1=1; 
unsigned int field_no2=2; 
const char* writeAPIKey ="HQXWAFUKEOSU52JQ";   // Thingspeak write API Key 
const char* readAPIKey = "69A1EUFSOXO938BV";   // Thingspeak read API Key 


///////////////////////////////mesafe/////////////////////////////////////
// Hook up HC-SR04 with Trig to Arduino Pin 9, Echo to Arduino pin 10
#define TRIGGER_PIN 5   //D1 D2'ye bağlanır
#define ECHO_PIN 4
// Maximum distance we want to ping for (in centimeters).
#define MAX_DISTANCE 400  


Webhook webhook(KEY, EVENT);    // Create an object.
  NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
  char auth[] = "s6fsycO27eeHXaF6F5QJBERv-MYM7nUP"; //blynk
  HX711 scale(D6, D7);
  float calibration_factor = 205; //-7050 worked for my 440lb max scale setup
  // NewPing setup of pins and maximum distance.
  float duration, distance;
  int mamaMiktari;  
  int kediSayisi;
  int weight;
  Servo s1; 
   WiFiClient client;  

void setup() {
  kediSayisi=0;
  mamaMiktari=0;
  
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  // Connect to WiFi
  Serial.println();
  Serial.println();
  Serial.print("Connecting to: ");
  Serial.println(_SSID);
  WiFi.begin(_SSID, _PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print("-");

  // Print the IP address
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
  digitalWrite(LED_BUILTIN, HIGH);
//================================================================//
   ThingSpeak.begin(client);         // ThingSpeak client sınıfı başlatılıyor


//================================================================//

 Serial.println("HX711 calibration sketch");
  Serial.println("Remove all weight from scale");
  Serial.println("After readings begin, place known weight on scale");
  //Serial.println("Press + or a to increase calibration factor");
  //Serial.println("Press - or z to decrease calibration factor");
  Blynk.begin(auth, _SSID, _PASSWORD);
  delay(2000);

  scale.set_scale();
  scale.tare(); //Reset the scale to 0

  long zero_factor = scale.read_average(); //Get a baseline reading
  Serial.print("Zero factor: "); //This can be used to remove the need to tare the scale. Useful in permanent scale projects.
  Serial.println(zero_factor);

  Serial.println("");
  Serial.println("WiFi Connected");

  /////////servo/////////////////////////////////
  s1.attach(servoPin);  // servo attach D3 pin of arduino  


}

}
void loop() {

     /* ThingSpeak Field Yazma İşlemi */
   // ThingSpeak.writeField (channelID, field_no2, kediSayisi, writeAPIKey);
   // ThingSpeak.writeField (channelID, field_no1, mamaMiktari, writeAPIKey);       // mamaMiktari değerini gönder 

   ThingSpeak.setField (1, mamaMiktari);       // 1 nolu field ı kur 
   ThingSpeak.setField (2, kediSayisi);       // 2 nolu field ı kur 
   ThingSpeak.writeFields(channelID, writeAPIKey);       // kurulu field lere yaz (çoklu yazma) 

//////////////////////mesafe/////////////////
  // Send ping, get distance in cm
  distance = sonar.ping_cm();
  Serial.print("distance : ");
  Serial.print(distance);
  // Send results to Serial Monitor
  if (distance <= 5) 
  {
    kediSayisi++;
  }
  Serial.print("kedi : ");
  Serial.print(kediSayisi);

/////////////////////////////////////ağırlık sensörü/////////////////////////
 scale.set_scale(calibration_factor); //Adjust to this calibration factor
  
  Serial.print("Reading: ");
  Serial.print(scale.get_units(), 1);
  Serial.print(" gr"); //Change this to kg and re-adjust the calibration factor if you follow SI units like a sane person
  Serial.print(" calibration_factor: ");
  Serial.print(calibration_factor);
  Serial.println();
  Blynk.run();
  scale.set_scale(calibration_factor); //Adjust to this calibration factor
 
  weight = scale.get_units(1); 
  weightBly= scale.get_units(1)+500; 

  
  Blynk.virtualWrite(V3, weightBly);

    mamaMiktari = weight;
  ///////////////////birleştirilen kısım//////////////
  if(mamaMiktari<-200){
     /////////////////////////////////////////////////////////ifttt////////////////////////////////////////////////////
     // Trigger with 3 values.
     webhook.trigger(String(weightBly), String(kediSayisi));
     // Trigger without any value and get response.
     int response = webhook.trigger();

     Serial.print("resp:");
     Serial.print(response);
     
     //////////////////////////servo/////////////////////
     s1.write(0);  
     delay(1000);
   s1.write(180);
      
  }

   

    delay(5000);
}


BLYNK_WRITE(V1){
    s1.write(param.asInt()*180);
}
   
   
