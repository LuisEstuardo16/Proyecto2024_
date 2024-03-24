#include <WiFi.h>
#include <Wire.h> //conexion I2C 
#include <ESP32Servo.h>

const char *ssid = "";
const char *password = "";

WiFiServer server(80);
String header;

unsigned long currentTime = millis();
unsigned long previousTime = 0;
const long timeoutTime = 2000;

int state = 0; 
int state2 = 0; 
int state3 = 0;
int servoPin1=23;//puerta 1
int servoPin2=18;//puerta 2
int servoPin3=19;//puerta 3
Servo myservo;
Servo myservo2;
Servo myservo3;

int pos= 0;
int pos2=0;
int pos3=0;


void setup() {
   Wire.begin(21, 22);
   Serial.begin(115200);
   //*******PARA PRIMER SERVO *****
  ESP32PWM::allocateTimer(0);
	ESP32PWM::allocateTimer(1);
	ESP32PWM::allocateTimer(2);
	ESP32PWM::allocateTimer(3);
	myservo.setPeriodHertz(50);   
	myservo.attach(servoPin1, 1000, 2000);
  //*******PARA SEGUNDO SERVO *****
  ESP32PWM::allocateTimer(0);
	ESP32PWM::allocateTimer(1);
	ESP32PWM::allocateTimer(2);
	ESP32PWM::allocateTimer(3);
	myservo2.setPeriodHertz(50);    
	myservo2.attach(servoPin2, 1000, 2000);
  //*******PARA TERCER SERVO *****
  ESP32PWM::allocateTimer(0);
	ESP32PWM::allocateTimer(1);
	ESP32PWM::allocateTimer(2);
	ESP32PWM::allocateTimer(3);
	myservo3.setPeriodHertz(50);    
	myservo3.attach(servoPin3, 1000, 2000);

  // conectar a wifi con la ssid y contraseña
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  // imprimir la IP y start el web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop() {
   WiFiClient client = server.available(); 
  if (client)
  { // si un nuevo cliente se conecta,
    currentTime = millis();
    previousTime = currentTime;
    Serial.println("New Client."); 
    String currentLine = "";      
    while (client.connected() && currentTime - previousTime <= timeoutTime)
    { 
      currentTime = millis();
      if (client.available())
      {                         
        char c = client.read(); 
        Serial.write(c);        
        header += c;
        if (c == '\n')
        { 
          if (currentLine.length() == 0)
          {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();

            // cambiar el GPIOs on y off
            if (header.indexOf("GET /servo1/on") >= 0)
            {
              state = 1;
              Serial.println("puerta abierta");
              SERVO_1_on();
                       
            }
            else if (header.indexOf("GET /servo1/off") >= 0)
            {
              state = 0;
              Serial.println("puerta cerrada");
              SERVO_1_off();
                       }
            if (header.indexOf("GET /servo2/on") >= 0)
            {
              state2 = 1;
              Serial.println("puerta abierta");
              SERVO_2_on();
                       
            }
            else if (header.indexOf("GET /servo2/off") >= 0)
            {
              state2 = 0;
              Serial.println("puerta cerrada");
              SERVO_2_off();
                       }

             if (header.indexOf("GET /servo3/on") >= 0)
            {
              state3 = 1;
              Serial.println("puerta abierta");
              SERVO_3_on();
                       
            }
            else if (header.indexOf("GET /servo3/off") >= 0)
            {
              state3 = 0;
              Serial.println("puerta cerrada");
              SERVO_3_off();
                       }
                       
           
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
           

            // CSS to style the on/off buttons
            // Feel free to change the background-color and font-size attributes to fit your preferences
            
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #DCCD1C ; border-color: black; color: black; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color:#D5CE81 ;}</style></head>");

            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button3 { background-color: #C36110 ; border-color: black; color: black; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button4 {background-color: #C49B78;}</style></head>");

           client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button5 { background-color:  #5944DF ; border-color: black; color: black; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button6 {background-color: #857CC4 ;}</style></head>");
            
           
            // Web Page Heading
            client.println("<body><h1>Control de Puertas</h1>");
            //control de cerrado ya abierto de puertas
            if (state == 1)
            {
              client.println("<p>Puerta 1</p>");
              client.println("<p><a href=\"/servo1/off\"><button class=\"button\">cerrar</button></a></p>");
              
              
            
            }
            else
            {
              client.println("<p>Puerta 1</p>");
              client.println("<p><a href=\"/servo1/on\"><button class=\"button button2\">abrir</button></a></p>");
            
           
            
            }
            if (state2 == 1)
            {
              client.println("<p>Puerta 2</p>");
              client.println("<p><a href=\"/servo2/off\"><button class=\"button3 \">cerrar</button></a></p>");
              
              
            
            }
            else
            {
              client.println("<p>Puerta 2</p>");
              client.println("<p><a href=\"/servo2/on\"><button class=\" button3 button4\">abrir</button></a></p>");
            
           
            }
           if (state3 == 1)
            {
              client.println("<p>Puerta 3</p>");
              client.println("<p><a href=\"/servo3/off\"><button class=\"button5\">cerrar</button></a></p>");
              
              
            
            }
            else
            {
              client.println("<p>Puerta 3</p>");
              client.println("<p><a href=\"/servo3/on\"><button class=\"button5 button6\">abrir</button></a></p>");
            
           
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

void SERVO_1_on(){
 	for (pos = 0; pos <= 180; pos += 1) { 
		myservo.write(pos);   
		delay(15);          
	}
}

void SERVO_1_off(){
 
  for (pos = 120; pos >= 0; pos -= 1) { 
		myservo.write(pos); 
		delay(15);             
	}
}
void SERVO_2_on(){
  for (pos2 = 0; pos2 <= 120; pos2 += 1) { 
		myservo2.write(pos2);    
		delay(15);             
	}

}
void SERVO_2_off(){
   for (pos2 = 119; pos2 >= 0; pos2 -= 1) { 
		myservo2.write(pos2);    
		delay(15);             
	}
}
void SERVO_3_on(){
   for (pos3 = 0; pos3 <= 120; pos3 += 1) { 
		myservo3.write(pos3);    
		delay(15);             
	}
}   void SERVO_3_off(){
   for (pos3 = 119; pos3 >= 0; pos3 -= 1) { 
		myservo3.write(pos3);    
		delay(15);             
	}
}
