/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Sweep
*/

#include <Bridge.h>
#include <YunServer.h>
#include <YunClient.h>
#include <Servo.h>

Servo turnOn;
Servo turnOff;
YunServer server;


int pos = 0;

void setup() {
  // Start our connection
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);; // turn on Led while connecting
  Bridge.begin();
  turnOn.attach(9);
  turnOff.attach(10);  

  // Show a fancy flash pattern once connected
  digitalWrite(LED_BUILTIN, LOW); 
  delay(150);
  digitalWrite(LED_BUILTIN,HIGH); 
  delay(150);
  digitalWrite(LED_BUILTIN,LOW); 
  delay(150);
  digitalWrite(LED_BUILTIN,HIGH); 
  delay(150);
  digitalWrite(LED_BUILTIN,LOW); 
  delay(150);
  
  // Disable for some connections:
  // Start listening for connections  
  
  server.listenOnLocalhost();
  server.begin();
 
}

void loop() {
  // Listen for clients
  YunClient client = server.accept();
  // Client exists?
  if (client) {
    // Lets process the request!
    process(client);
    client.stop();
  }
  delay(50);
}

void process(YunClient client) {
  // Collect user commands
  String command = client.readStringUntil('\\'); // load whole string
  
  // Enable HTML
  client.println("Status: 200");
  client.println("Content-type: text/html");
  client.println();
  
  // Show UI
  client.println("<B><Center>");
  client.println("<a href='http://yun.local/arduino/on\\'>Turn ON LED</a><br>");
  client.println("<a href='http://yun.local/arduino/off\\'>Turn OFF LED</a><br>");
  client.print("Command: ");
  client.println(command);
  client.println("</B></Center>");
  
  // Check what the user entered ...
  
  // Turn on
  if (command == "on") {
    for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
      turnOn.write(pos);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15ms for the servo to reach the position
    }
    for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
      turnOn.write(pos);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15ms for the servo to reach the position
    }
   }
  
  // Turn off
  if (command == "off") {
    for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
      turnOff.write(pos);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15ms for the servo to reach the position
    }
    for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
      turnOff.write(pos);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15ms for the servo to reach the position
    }
  }
}



// twelve servo objects can be created on most boards

    // variable to store the servo position


   // attaches the servo on pin 9 to the servo object




