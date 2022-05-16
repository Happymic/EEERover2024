/*
  EEERover starter code
  For Metro M0 Express with WINC1500 WiFi module
  Based on https://docs.arduino.cc/library-examples/wifi-library/WiFiWebServer
 */

#include <SPI.h>
#include <WiFi101.h>

const char ssid[] = "EEERover";     //  your network SSID (name)
const char pass[] = "exhibition";   // your network password
const bool APMode = false;          // Option to host a WiFi network
const int led =  LED_BUILTIN;
const int groupNumber = 99;         // Set your group number and IP address

void printWiFiStatus();
void printMacAddress(byte mac[]);

int status = WL_IDLE_STATUS;
WiFiServer server(80);

void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  Serial.println("EEERover Web Server");

  pinMode(led, OUTPUT);      // set the LED pin mode

  // check for the presence of the shield:
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    // don't continue
    while (true);
  }

  //Configure the static IP address
  WiFi.config(IPAddress(192,168,0,groupNumber));
  
  if (APMode) { //Host a WiFi network
    Serial.print("Creating access point named: ");
    Serial.println(ssid);

    // Create open network.
    status = WiFi.beginAP(ssid);
    if (status != WL_AP_LISTENING) {
      Serial.println("Creating access point failed");
      while (true);
    }

  } else {  //Connect to exisiting network
    status = WiFi.begin(ssid, pass);
    while ( status != WL_CONNECTED) {
      Serial.print("Attempting to connect to Network named: ");
      Serial.println(ssid);                   // print the network name (SSID);
      delay(1000);
    }

  }

  // you're connected now, so print out the status
  printWiFiStatus();

  // start the web server on port 80
  server.begin();

}


void loop() {
  
  //Check for status change
  if (status != WiFi.status()) {
    status = WiFi.status();

    //Check for new AP connection
    if (status == WL_AP_CONNECTED) {
      byte remoteMac[6];
      Serial.print("Device connected to AP, MAC address: ");
      WiFi.APClientMacAddress(remoteMac);
      printMacAddress(remoteMac);
    } else if (status == WL_AP_LISTENING) {
      Serial.println("Waiting for connection to AP");
    }
  }
  

  WiFiClient client = server.available();   // listen for incoming clients

  if (client) {                             // if you get a client,
    Serial.println("new client");           // print a message out the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor


        if (c == '\n') {                    // Is the line complete?

          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();

            // the content of the HTTP response follows the header:
            client.print("Click <a href=\"/H\">here</a> turn the LED on<br>");
            client.print("Click <a href=\"/L\">here</a> turn the LED off<br>");

            // The HTTP response ends with another blank line:
            client.println();
            Serial.println("Sent page");
            // break out of the while loop:
            break;
          }

          // Other lines have information that might be useful
          else {
            // Check to see if the client request was "GET /H" or "GET /L":
            if (currentLine.startsWith("GET /H")) {
              digitalWrite(led, HIGH);               // GET /H turns the LED on
            }
            if (currentLine.startsWith("GET /L")) {
              digitalWrite(led, LOW);                // GET /L turns the LED off
            }
          }

          currentLine = ""; //Clear the string ready for the next line
        }
        else if (c != '\r') {    // if you got anything else but a line end,
          currentLine += c;      // add it to the end of the currentLine
        }

      }
    }
    // close the connection:
    client.stop();
    Serial.println("client disconnected");
  }
}

void printWiFiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
  // print where to go in a browser:
  Serial.print("To see this page in action, open a browser to http://");
  Serial.println(ip);

}

void printMacAddress(byte mac[]) {
  for (int i = 5; i >= 0; i--) {
    if (mac[i] < 16) {
      Serial.print("0");
    }
    Serial.print(mac[i], HEX);
    if (i > 0) {
      Serial.print(":");
    }
  }
  Serial.println();
}