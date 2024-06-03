
#include <ESP8266WiFi.h>

#ifndef STASSID
#define STASSID "iPhone ch"
#define STAPSK "ronaldo9"
#endif
const int RED_1 = D0; // side 1 road 1
const int YELLOW_1 = D1;
const int GREEN_1 = D2;

const int RED_2 = D3; // side 1 road 1
const int YELLOW_2 = D4;
const int GREEN_2 = D5;

const int pirSensor1Road1 = D6; // Sensor 1 for Road 1 connected to pin D6
const int pirSensor2Road1 = D7; // Sensor 2 for Road 1 connected to pin D7
const int pirSensor1Road2 = D8; // Sensor 1 for Road 2 connected to pin D8
const int pirSensor2Road2 = 3; // Sensor 2 for Road 2 connected to pin D9


const char* ssid = STASSID;
const char* password = STAPSK;

const char* host = "djxmmx.net";
const uint16_t port = 17;

int countRoad1 = 0; // Initialize variables to store motion counts for each road
int countRoad2 = 0;

unsigned long previousMillis = 0; // Variable to store the last time counts were printed
const long interval = 5000; // Interval for checking counts and adjusting lights (5 seconds)

void setup() {
  Serial.begin(115200);
  pinMode(RED_1, OUTPUT);
  pinMode(YELLOW_1, OUTPUT); //road 1
  pinMode(GREEN_1, OUTPUT);
  pinMode(RED_2, OUTPUT);
  pinMode(YELLOW_2, OUTPUT); //road 1
  pinMode(GREEN_2, OUTPUT);
  
  pinMode(pirSensor1Road1, INPUT); // Set the PIR sensor pins as input
  pinMode(pirSensor2Road1, INPUT);
  pinMode(pirSensor1Road2, INPUT);
  pinMode(pirSensor2Road2, INPUT);
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  /* Explicitly set the ESP8266 to be a WiFi-client, otherwise, it by default,
     would try to act as both a client and an access-point and could cause
     network-issues with your other WiFi-devices on your WiFi-network. */
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

}

void loop() {
 
  // Check for motion on Road 1, Sensor 1
  if (digitalRead(pirSensor1Road1) == HIGH) {
    countRoad1++; // Increment count for Road 1
    Serial.println("Motion detected on Road 1, Sensor 1");
  }

  // Check for motion on Road 1, Sensor 2
  if (digitalRead(pirSensor2Road1) == HIGH) {
    countRoad1++; // Increment count for Road 1
    Serial.println("Motion detected on Road 1, Sensor 2");
  }

  // Check for motion on Road 2, Sensor 1
  if (digitalRead(pirSensor1Road2) == HIGH) {
    countRoad2++; // Increment count for Road 2
    Serial.println("Motion detected on Road 2, Sensor 1");
  }

  // // Check for motion on Road 2, Sensor 2
  if (digitalRead(pirSensor2Road2) == HIGH) {
     countRoad2++; // Increment count for Road 2
     Serial.println("Motion detected on Road 2, Sensor 2");
  }



  // Calculate the ratio of counts between the two roads
  float ratio = float(countRoad1) /float(countRoad2) ;
  // float ratio = float(countRoad1) / 5;

  ratio = constrain(ratio, 0.0, 1.0);

  // Adjust traffic light timings for Road 1 and Road 2 based on the ratio
  adjustTrafficLights(RED_1, YELLOW_1, GREEN_1, RED_2, YELLOW_2, GREEN_2, ratio);




  // Adjust traffic light timings based on the ratio
//   if (ratio > 1.0) { // Road 1 has more motion, so give it more green time
//     // Traffic light timings for Road 1
//     digitalWrite(RED_1, HIGH);
//     digitalWrite(YELLOW_1, LOW);
//     digitalWrite(GREEN_1, LOW);
    
//     // Traffic light timings for Road 2
//     digitalWrite(RED_2, LOW);
//     digitalWrite(YELLOW_2, LOW);
//     digitalWrite(GREEN_2, HIGH);

//     // Adjust delays for Road 2
//     delay(2000); // Green light for Road 2 (8 seconds)
//     digitalWrite(GREEN_2, LOW);
//     digitalWrite(YELLOW_2, HIGH); // Yellow light for Road 2
//     delay(1000); // Yellow light for Road 2 (2 seconds)
//     digitalWrite(YELLOW_2, LOW);
//     digitalWrite(RED_2,HIGH);
//     digitalWrite(RED_1,LOW);
//     digitalWrite(GREEN_1,HIGH);
//     delay(8000);
//      digitalWrite(GREEN_1,LOW);
//     digitalWrite(YELLOW_1,HIGH);
//     delay(1000);
//     digitalWrite(YELLOW_1,LOW);
    

//   } else if (ratio < 1.0) { // Road 2 has more motion, so give it more green time
//     // Traffic light timings for Road 1
//     digitalWrite(RED_1, HIGH);
//     digitalWrite(YELLOW_1, LOW);
//     digitalWrite(GREEN_1, LOW);
    
//     // Traffic light timings for Road 2
//     digitalWrite(RED_2, LOW);
//     digitalWrite(YELLOW_2, LOW);
//     digitalWrite(GREEN_2, HIGH);

//     // Adjust delays for Road 2
//     delay(8000); // Green light for Road 2 (8 seconds)
//     digitalWrite(GREEN_2, LOW);
//     digitalWrite(YELLOW_2, HIGH); // Yellow light for Road 2
//     delay(1000); // Yellow light for Road 2 (2 seconds)
//     digitalWrite(YELLOW_2, LOW);
//     digitalWrite(RED_2,HIGH);
//     digitalWrite(RED_1,LOW);
//     digitalWrite(GREEN_1,HIGH);
//     delay(2000);
//      digitalWrite(GREEN_1,LOW);
//     digitalWrite(YELLOW_1,HIGH);
//     delay(1000);
//     digitalWrite(RED_2,LOW);
//     digitalWrite(YELLOW_1,LOW);
//   } else { // Equal motion counts on both roads
//     //Default traffic light timings for both roads
//    digitalWrite(RED_1, HIGH);
//  digitalWrite(RED_2,LOW);
//  digitalWrite(GREEN_2,HIGH);
//   digitalWrite(GREEN_1,LOW);
//  delay(5000);
//  digitalWrite(GREEN_2,LOW);
//   digitalWrite(YELLOW_2,HIGH);
//   delay(3000);
//  digitalWrite(YELLOW_2,LOW);
//   digitalWrite(GREEN_1,HIGH);
//   digitalWrite(RED_1,LOW);
//   digitalWrite(RED_2,HIGH);

//   delay(5000);
//   digitalWrite(GREEN_1,LOW);
//   digitalWrite(YELLOW_1,HIGH);
//   delay(3000);
//   digitalWrite(YELLOW_1,LOW);
//   }

  // Reset counts for the next cycle
  // countRoad1 = 0;
  // countRoad2 = 0;

  // Delay to avoid reading the sensors too quickly
  delay(100); 
}

void adjustTrafficLights(int redPin1, int yellowPin1, int greenPin1, int redPin2, int yellowPin2, int greenPin2, float ratio) {
  int totalCycleTime = 20; // total cycle time for the lights in seconds
  int yellowTime = 2; // fixed yellow light time in seconds

  // Calculate green and red light durations based on the ratio
  int greenTime1 = round((totalCycleTime - yellowTime) * ratio);
  greenTime1 = max(greenTime1, 6);
  int redTime1 = totalCycleTime - yellowTime - greenTime1;
  redTime1 = max(redTime1, 6);
  int greenTime2 = totalCycleTime - yellowTime - greenTime1;
  greenTime2 = max(greenTime2, 6);
int redTime2 = totalCycleTime - yellowTime - greenTime2;
  redTime2 = max(redTime2, 6);
  

  // Road 2 times are opposite of Road 1
  
  
 


  // Traffic light sequence for Road 1
  

 digitalWrite(greenPin2, LOW);
 digitalWrite(yellowPin2, HIGH);
  delay(yellowTime * 1000);
  digitalWrite(yellowPin2, LOW);
    digitalWrite(redPin1, LOW);
  digitalWrite(greenPin1, HIGH);
  digitalWrite(redPin2, HIGH);
 
  delay(greenTime1 * 1000);

  digitalWrite(greenPin1, LOW);
  digitalWrite(yellowPin1, HIGH);
  digitalWrite(greenPin2, LOW);
  digitalWrite(yellowPin2, LOW);
  delay(yellowTime * 1000);

  digitalWrite(yellowPin1, LOW);
  digitalWrite(redPin1, HIGH);
  digitalWrite(yellowPin2, LOW);
  digitalWrite(redPin2, LOW);
  digitalWrite(greenPin2, HIGH);
  delay(redTime1 * 1000);

  // Traffic light sequence for Road 2 (this part is handled within the combined sequence)
  // No need to handle separately as it's part of the combined logic

  // Ensure the total time sums up to 20 seconds
  Serial.print("Road 1 Green Time: ");
  Serial.println(greenTime1);
  Serial.print("Road 1 Yellow Time: ");
  Serial.println(yellowTime);
  Serial.print("Road 1 Red Time: ");
  Serial.println(redTime1);

  Serial.print("Road 2 Green Time: ");
  Serial.println(greenTime2);
  Serial.print("Road 2 Yellow Time: ");
  Serial.println(yellowTime);
  Serial.print("Road 2 Red Time: ");
  Serial.println(redTime2);

  Serial.print("Total Time: ");
  Serial.println(greenTime1 + yellowTime + redTime1);
}