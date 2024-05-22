#include <ESP8266WiFi.h>

const char* ssid = "Ma"; //需要更改为要连接的WiFi名称
const char* password = "74d8}Z78"; //WiFi密码

const int ledPin = 2;

WiFiServer server(80);

void setup() {
 pinMode(ledPin, OUTPUT);
 digitalWrite(ledPin, LOW);

 Serial.begin(115200);

 WiFi.begin(ssid, password);
 while (WiFi.status() != WL_CONNECTED) {
  delay(1000);
  Serial.println("Connecting to WiFi...");
 }

 server.begin();
 Serial.println("Server started");
}

void loop() {
 WiFiClient client = server.available();
 if (!client) {
  return;
 }

 while (!client.available()) {
  delay(1);
 }

 String request = client.readStringUntil('\r');
 client.flush();

 if (request.indexOf("/on") != -1) {
  digitalWrite(ledPin, HIGH);
 } else if (request.indexOf("/off") != -1) {
  digitalWrite(ledPin, LOW);
 }

 client.println("HTTP/1.1 200 OK");
 client.println("Content-Type: text/html");
 client.println();
 client.println("<!DOCTYPE HTML>");
 client.println("<html>");
 client.println("LED is now " + String(digitalRead(ledPin) == HIGH ? "on" : "off"));
 client.println("<br>< a href=' '>Turn On</ a>");
 client.println("<br>< a href='/off'>Turn Off</ a>");
 client.println("</html>");

 delay(1);
}