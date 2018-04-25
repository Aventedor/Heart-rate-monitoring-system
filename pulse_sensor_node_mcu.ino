#include <ESP8266WiFi.h>
//  Variables
#define PSPin D4    // Pulse Sensor ORANGE WIRE connected to ANALOG PIN 0
WiFiClient client;
String apiKey = "DAQJ1KPH7V0LJ0DQ";     //add thinkspeak api key
const char *ssid =  "Alcatel LinkZone_671B";           //wifi ssid
const char *pass =  "70907854";        //wifi password
const char* server = "api.thingspeak.com";    

int c=0,r=0;          //counter and rate variable
int flag=0;
int Signal;                // holds the incoming raw data. Signal value can range from 0-1024
int Threshold = 515;            // Determine which Signal to "count as a beat", and which to ignore
// The SetUp Function:
void setup() {
  pinMode(PSPin,INPUT); 

   Serial.begin(115200);
      WiFi.begin(ssid, pass);
 
      while (WiFi.status() != WL_CONNECTED) 
     {
            delay(500);
            Serial.print(".");
     }
      Serial.println("");
      Serial.println("WiFi connected");// Set's up Serial Communication at certain speed. 
   
}
// The Main Loop Function
void loop()
{

  Signal = analogRead(PSPin);  // Read the PulseSensor's value. 
                                              // Assign this value to the "Signal" variable.

  //Serial.println(Signal);  // Send the Signal value to Serial Plotter.
//if(Signal > Threshold){                          // If the signal is above "515", then "turn-on" Arduino's on-Board LED.  
//     digitalWrite(LED13,HIGH);          
 //  } 
//else {
  //   digitalWrite(LED13,LOW);                //  Else, the sigal must be below "515", so "turn-off" this LED.
  // }

   
   
if(flag==1)
 { c=0;
   //Serial.println("flag=1 block entered");
  Serial.println("High values per 2000 count");
  Serial.print(r);
  // check the network connection once every 10 seconds
  
   if (client.connect(server,80))        //"184.106.153.149" and port no.
                      {  
                            
                             String postStr = apiKey;
                             postStr +="&field1=";
                             postStr += String(r);
                            // postStr +="&field2=";
                            // postStr += String(h);
                             postStr +="\r\n";
 
                            client.print("POST /update HTTP/1.1\n");
                             client.print("Host: api.thingspeak.com\n");
                             client.print("Connection: close\n");
                             client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
                             client.print("Content-Type: application/x-www-form-urlencoded\n");
                             client.print("Content-Length: ");
                             client.print(postStr.length());
                             client.print("\n\n");
                             client.print(postStr);
 
                             Serial.println("pulse: ");
                             Serial.print(r);
                             Serial.println("%. Send to Thingspeak.");
                        }
          client.stop(); 
   r=0;
   flag=0;}
   else
   {
    //Serial.println("flag=0 block entered");
    c=c+1;}
 if(Signal>Threshold)
     {r=r+1;
     //Serial.println("heart beat detected, r incremented");
     }
  else
     {r=r;
     //Serial.println("no heartbeat r remains same");
     }//just for debugging purpose
  if(c==2000)
     {flag=1;
     //Serial.println("2000 counts over, flag becomes 1");
     }
  else
     {flag=0;
     //Serial.println("2000 counts isnt over yet flag remains 0");}
     
   }
delay(1);
   
   
   }


