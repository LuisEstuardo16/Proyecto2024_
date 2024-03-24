#include <WiFi.h>
#include <Wire.h> //I2C connection

// Replace with your network credentials
const char *ssid = "";
const char *password = "";

// Set web server port number to 80
WiFiServer server(80);

// Variable to store the HTTP request
String header;

// Current time
unsigned long currentTime = millis();
// Previous time
unsigned long previousTime = 0; 
// Define timeout time in milliseconds (example: 2000ms = 2s)
const long timeoutTime = 2000;

int state1 = 0; // 0 off, 1 on
int state2 = 0;
int state3 = 0;
int state4 = 0;
int state5 = 0;
int state6 = 0;



int led1=23;//pin led
int led2=21;//pin led
int led3=19;//pin led
int led4=5;//pin led
int led5=16;//pin led
int led6=15;//pin led

void setup() {
   pinMode(led1,OUTPUT);
   pinMode(led2,OUTPUT);
   pinMode(led3,OUTPUT);
   pinMode(led4,OUTPUT);
   pinMode(led5,OUTPUT);
   pinMode(led6,OUTPUT);

   
   Wire.begin(18, 22);
   Serial.begin(115200);

     // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop() {
   WiFiClient client = server.available(); // Listen for incoming clients

  if (client)
  { // If a new client connects,
    currentTime = millis();
    previousTime = currentTime;
    Serial.println("New Client."); // print a message out in the serial port
    String currentLine = "";       // make a String to hold incoming data from the client
    while (client.connected() && currentTime - previousTime <= timeoutTime)
    { // loop while the client's connected
      currentTime = millis();
      if (client.available())
      {                         // if there's bytes to read from the client,
        char c = client.read(); // read a byte, then
        Serial.write(c);        // print it out the serial monitor
        header += c;
        if (c == '\n')
        { // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0)
          {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();

            // turns the GPIOs on and off
            if (header.indexOf("GET /led1/on") >= 0)
            {
              state1 = 1;
              Serial.println("Led ON");
              LED();
                       
            }
            else if (header.indexOf("GET /led1/off") >= 0)
            {
              state1 = 0;
              Serial.println("Led OFF");
              LED_Apagada();
                       }
                        // turns the GPIOs on and off
            if (header.indexOf("GET /led2/on") >= 0)
            {
              state2 = 1;
              Serial.println("Led ON");
              LED_2();
                       
            }
            else if (header.indexOf("GET /led2/off") >= 0)
            {
              state2 = 0;
              Serial.println("Led OFF");
              LED_Apagada2();
                       }
                        // turns the GPIOs on and off
            if (header.indexOf("GET /led3/on") >= 0)
            {
              state3 = 1;
              Serial.println("Led ON");
              LED_3();
                       
            }
            else if (header.indexOf("GET /led3/off") >= 0)
            {
              state3 = 0;
              Serial.println("Led OFF");
              LED_Apagada3();
                       }
                        // turns the GPIOs on and off
            if (header.indexOf("GET /led4/on") >= 0)
            {
              state4 = 1;
              Serial.println("Led ON");
              LED_4();
                       
            }
            else if (header.indexOf("GET /led4/off") >= 0)
            {
              state4 = 0;
              Serial.println("Led OFF");
              LED_Apagada4();
                       }
                        // turns the GPIOs on and off
            if (header.indexOf("GET /led5/on") >= 0)
            {
              state5 = 1;
              Serial.println("Led ON");
              LED_5();
                       
            }
            else if (header.indexOf("GET /led5/off") >= 0)
            {
              state5 = 0;
              Serial.println("Led OFF");
              LED_Apagada5();
                       }
                        // turns the GPIOs on and off
            if (header.indexOf("GET /led6/on") >= 0)
            {
              state6 = 1;
              Serial.println("Led ON");
              LED_6();
                       
            }
            else if (header.indexOf("GET /led6/off") >= 0)
            {
              state6 = 0;
              Serial.println("Led OFF");
              LED_Apagada6();
                       }


            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS to style the on/off buttons
            // Feel free to change the background-color and font-size attributes to fit your preferences
            //led 1
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #2F32F3; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #FF4D8E;}</style></head>");
           //led 2
           client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button3 { background-color: #2F32F3; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button4 {background-color: #FF4D8E;}</style></head>");
            //led 3
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button5 { background-color: #2F32F3; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button6 {background-color: #FF4D8E;}</style></head>");
            //led 4
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button7 { background-color: #2F32F3; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button8 {background-color: #FF4D8E;}</style></head>");
            //led 5
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button9 { background-color: #2F32F3; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button10 {background-color: #FF4D8E;}</style></head>");
            //led 6 
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button11 { background-color: #2F32F3; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button12 {background-color: #FF4D8E;}</style></head>");
                     
            client.println("<body><h1>Mi ESP32 Web Server</h1>");

            if (state1 == 1)
            {
              client.println("<p>Led 1 Encendida</p>");
              client.println("<p><a href=\"/led1/off\"><button class=\"button\">OFF </button></a></p>");
              
              
            
            }
            else
            {
              client.println("<p>Led 1 Apagada</p>");
              client.println("<p><a href=\"/led1/on\"><button class=\"button  button2\">ON</button></a></p>");
            
           
            
            }
            if (state2 == 1)
            {
              client.println("<p>Led 2 Encendida</p>");
              client.println("<p><a href=\"/led2/off\"><button class=\"button3\">OFF</button></a></p>");
              
              
            
            }
            else
            {
              client.println("<p>Led 2 Apagada</p>");
              client.println("<p><a href=\"/led2/on\"><button class=\"button3 button4\">ON</button></a></p>");
            
           
            
            }
            if (state3 == 1)
            {
              client.println("<p>Led 3 Encendida</p>");
              client.println("<p><a href=\"/led3/off\"><button class=\"button5 \">OFF</button></a></p>");
              
              
            
            }
            else
            {
              client.println("<p>Led 3 Apagada</p>");
              client.println("<p><a href=\"/led3/on\"><button class=\"button5 button6\">ON</button></a></p>");
            
           
            
            }
            if (state4 == 1)
            {
              client.println("<p>Led 4 Encendida</p>");
              client.println("<p><a href=\"/led4/off\"><button class=\"button7 \">OFF</button></a></p>");
              
              
            
            }
            else
            {
              client.println("<p>Led 4 Apagada</p>");
              client.println("<p><a href=\"/led4/on\"><button class=\"button7 button8\">ON</button></a></p>");
            
           
            
            }
            if (state5 == 1)
            {
              client.println("<p>Led 5 Encendida</p>");
              client.println("<p><a href=\"/led5/off\"><button class=\"button9 \">OFF</button></a></p>");
              
              
            
            }
            else
            {
              client.println("<p>Led 5 Apagada</p>");
              client.println("<p><a href=\"/led5/on\"><button class=\"button9 button10\">ON</button></a></p>");
            
           
            
            }
            if (state6 == 1)
            {
              client.println("<p>Led 6 Encendida</p>");
              client.println("<p><a href=\"/led6/off\"><button class=\"button11\">OFF</button></a></p>");
              
              
            
            }
            else
            {
              client.println("<p>Led 6 Apagada</p>");
              client.println("<p><a href=\"/led6/on\"><button class=\"button11 button12\">ON</button></a></p>");
            
           
            
            }

            client.println("</body></html>");

            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          }
          else
          { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        }
        else if (c != '\r')
        {                   // if you got anything else but a carriage return character,
          currentLine += c; // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }

}

void LED(){
 digitalWrite(led1,HIGH);
}

void LED_Apagada(){
  digitalWrite(led1,LOW);
}
void LED_2(){
 digitalWrite(led2,HIGH);
}

void LED_Apagada2(){
  digitalWrite(led2,LOW);
}
void LED_3(){
 digitalWrite(led3,HIGH);
}

void LED_Apagada3(){
  digitalWrite(led3,LOW);
}
void LED_4(){
 digitalWrite(led4,HIGH);
}

void LED_Apagada4(){
  digitalWrite(led4,LOW);
}
void LED_5(){
 digitalWrite(led5,HIGH);
}

void LED_Apagada5(){
  digitalWrite(led5,LOW);
}
void LED_6(){
 digitalWrite(led6,HIGH);
}

void LED_Apagada6(){
  digitalWrite(led6,LOW);
}
