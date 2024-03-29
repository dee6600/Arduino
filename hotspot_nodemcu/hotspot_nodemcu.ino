#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

// Replace with your network credentials
const char* ssid = "Gochi";
const char* password = "jksab12345";

ESP8266WebServer server(80);   //instantiate server at port 80 (http port)

String page = "";
int LEDPin = 161;
void setup(void){
  //the HTML of the web page
  page = "<h1>Simple NodeMCU Web Server</h1>
          <p>
          <a href=\"LEDOn\"><button>ON</button></a>&nbsp;<a href=\"LEDOff\"><button>OFF</button></a>
          <form action="/submit">
          myssid: <input type="text" name="ssid" value=""><br>
          mypassword: <input type="text" name="passowrd" value=""><br>
          <input type="submit" value="Submit">
          </form>
          </p>";
  //make the LED pin output and initially turned off
  pinMode(LEDPin, OUTPUT);
  digitalWrite(LEDPin, LOW);
   
  delay(1000);
  Serial.begin(115200);
  WiFi.softAP(ssid, password); //begin WiFi access point
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.softAPIP()); 
   
  server.on("/", [](){
    server.send(200, "text/html", page);
  });
  server.on("/LEDOn", [](){
    server.send(200, "text/html", page);
    digitalWrite(LEDPin, HIGH);
    delay(1000);
  });
  server.on("/LEDOff", [](){
    server.send(200, "text/html", page);
    digitalWrite(LEDPin, LOW);
    delay(1000); 
  });
  server.on("/submit",[](){
    String myssid = server.arg(“myssid”);
    String mypassword = server.arg(“mypassword”);
    Serial.println("SSID=",myssid);
    Serial.println("password=",mypassword);
  });
  }
  server.begin();
  Serial.println("Web server started!");
}
 
void loop(void){
  server.handleClient();
}
