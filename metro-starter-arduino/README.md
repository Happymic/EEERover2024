# EEERover starter code

This project is an example of setting up WiFi communication with the Metro M0 Express module using HTTP.
The microcontroller connects to a WiFi network and acts as a simple web server, returning a very basic web page when it receives an HTTP request.
It also acts on certain path strings in the HTTP request to switch an LED on and off when the client clicks buttons on the webpage.

## Building the project

Additional libraries are needed to use Arduino IDE with the Metro M0 board and WiFi module. [Follow the instructions from Adafruit](https://learn.adafruit.com/adafruit-metro-m0-express/arduino-ide-setup) to add support for the Metro M0 board in Arduino IDE.
			
The WiFi communication functions are provided by the WiFi101 library, which also must be installed with the Library Manager. The library installs its own set of example sketches and has an [API reference](https://www.arduino.cc/en/Reference/WiFi101). The demonstration code in this repository is based on these examples.

## Network configuration

The code is configured to connect to the EEERover network in the lab. You can give a different WiFi network and password, such as a mobile hotspot, by changing the appropriate lines in the code. You won't be able to connect to the College WiFi network, which uses a login. When the code starts it reports its IP Address on the serial monitor. You can connect to the microcontroller from a computer on the same WiFi network by typing this address into a web browser.

You may need to connect to the microcontroller when it is not connected to a host computer, so you won't see the message reporting the IP address. You can fix the IP address to a certain value by setting `groupNumber` to your group number. You can only do this on the EEERover network because it has been configured to allow a certain range of static IPs.

## HTTP server

The `WiFiWebServer` class is used to handle HTTP requests from WiFi clients.
HTTP is the protocol used to access websites and it is used here because it allows the creation of a simple user interface using a web browser.

The server is configured in the `setup()` function using calls to `server.on()` to define what happens when requests are received.
Each HTTP request has a path, which is the part of the url after the domain name or IP address. The server responds to three different paths:
 - `\` The root address, e.g. `http://192/168/0/10`
 - `\on` A request to turn the LED on
 -`\off` A request to turn the LED off

A different function is called when each request is received, but all respond by sending back the same default webpage.

## Next steps

The code gives an example of sending information in both directions between the microcontroller and the remote client.
It can be extended to include all the data you need to control your rover and get data back.

### Improving the UI

The basic webpage gives a poor quality UI. A better UI could be written using more complex HTML, but storing that on the microcontroller would slow down communication if it is transmitted on every request.
A better approach could be to return the webpage only when the root path is requested. Some simple Javascript could allow the webpage to send requests for other paths like `/on` without refreshing the webpage.
You could also create an app that sends these requests.

### Alternatives to HTTP

Using HTTP creates quite a lot of overhead in the headers that are transmitted in every transaction.
You can use the WiFi101 library to send and receive raw data byte-by-byte.
However, a web browser will not let you control the internet traffic at such a low level so you would need to write a user interface with an appropriate programming language and socket library to achieve this functionality.
