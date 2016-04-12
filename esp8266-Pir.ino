#include <DHT.h>
#include <ESP8266WiFi.h>

// replace with your channel’s thingspeak API key,
String apiKey = "8SM299R6WUJ323YY";
const char* ssid = "Forthnet-24F230";
const char* password = "C4294B4C9A";

const char* server = "api.thingspeak.com";
const int buttonPin = 0;
int buttonState = 0;
int pir=0;

WiFiClient client;

void setup() {
Serial.begin(9600);
delay(10);


WiFi.begin(ssid, password);

Serial.println();
Serial.println();
Serial.print("Connecting to ");
Serial.println(ssid);

WiFi.begin(ssid, password);

while (WiFi.status() != WL_CONNECTED) {
delay(500);
Serial.print(".");
}
Serial.println("");
Serial.println("WiFi connected");

 pinMode(LED_BUILTIN, OUTPUT); 
 pinMode(buttonPin, INPUT);

}

void loop() {

buttonState = digitalRead(buttonPin);
 if (buttonState == HIGH) {
    // turn LED on:
  //  digitalWrite(ledPin, HIGH);
  } else {
    // turn LED off:
   // digitalWrite(ledPin, LOW);
  }

if (client.connect(server,80)) { // "184.106.153.149" or api.thingspeak.com
   digitalWrite(LED_BUILTIN, LOW);
String postStr = apiKey;
postStr +="&field1=";
postStr += String(10);
postStr +="&field2=";
postStr += String(10);
postStr +="&field3=";
postStr += String(pir);
postStr += "\r\n\r\n";

client.print("POST /update HTTP/1.1\n");
client.print("Host: api.thingspeak.com\n");
client.print("Connection: close\n");
client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
client.print("Content-Type: application/x-www-form-urlencoded\n");
client.print("Content-Length: ");
client.print(postStr.length());
client.print("\n\n");
client.print(postStr);
digitalWrite(LED_BUILTIN, HIGH);
delay(500);

Serial.print("Temperature: ");
Serial.print(10);
Serial.print(" degrees Celcius Humidity: ");
Serial.print(10);
Serial.println("% send to Thingspeak");

}
client.stop();
pir=0;
for (int thisPin = 1; thisPin < 200; thisPin++) {
    buttonState = digitalRead(buttonPin);
     if (buttonState == HIGH) {
    // turn LED on:
    pir=1;
  digitalWrite(LED_BUILTIN, LOW);
     }
  delay(50);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(50);
  
   
  }


Serial.println("Waiting…");
// thingspeak needs minimum 15 sec delay between updates

}
