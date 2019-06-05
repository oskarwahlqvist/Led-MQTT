#include <WiFiClient.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = "Your SSID! *********************************************";
const char* password =  "***Your PassWord! **************************";
const char* mqttServer = "Your IP! ******************************";
const int mqttPort =1883;
const char* mqttUser = "sUsername";
const char* mqttPassword = "sPassword";

int yellow = D2;

const int delayMillis = 300;
String mqtt_string;

WiFiClient espClient;
PubSubClient client(espClient);

void setup(){
//Kopplar upp sig till WIFI
 Serial.begin(115200);
 WiFi.begin(ssid, password);
 while (WiFi.status() != WL_CONNECTED){
   delay(500);
   Serial.println("Connecting to WiFi..");
 }
 Serial.println("Connected to the WiFi network");
 Serial.println(WiFi.localIP());
 client.setServer(mqttServer, mqttPort);
 client.setCallback(callback);
 while (!client.connected()) {
	 //Kopplar upp sig till MQTT
   Serial.println("Connecting to MQTT...");
   if(client.connect("ESP8266Client", mqttUser, mqttPassword )){
    Serial.println("connected");
   }
		else{
			Serial.print("failed with state ");
			Serial.print(client.state());
			delay(2000);
   }
 }

//Subscribar till mqtt-topic:en "raspsend" 
client.subscribe("raspsend");

}
 
void loop() 
{
  client.loop();
  
  //Loop som sätter av eller på led:en beroende på vad som kommer via MQTT.
    if( mqtt_string == "ledon"){   
      analogWrite(yellow, 1023);
    }
  
    if (mqtt_string == "ledoff" ){
        analogWrite(yellow, 0);
    }
    delay(500);
 }

//Tar emot det som skickas på MQTT topic:en
 void callback(char *topic, byte *payload, unsigned int length) 
{
      if (!strncmp((char *)payload, "ledon", length)){
       // MQTT Payload
           payload[length] = '\0';
           String strPayload = String((char*)payload);
           mqtt_string = strPayload;
      }
       
	  // MQTT Payload
      if (!strncmp((char *)payload, "ledoff", length)){
           payload[length] = '\0';
           String strPayload = String((char*)payload);
           mqtt_string = strPayload;
      }
      
	  //MQTT Topic
      if(!strncmp((char *)topic, "raspsend", length)){
           payload[length] = '\0';
           String tempPayload = String((char*)payload);
           mqtt_string = tempPayload;
           Serial.println("payload = "+ mqtt_string);
      }
      
}
