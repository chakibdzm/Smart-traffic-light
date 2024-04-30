const int RED_1 = D0; // side 1 road 1
const int YELLOW_1 = D1;
const int GREEN_1 = D2;

const int RED_2 = D3; // side 1 road 1
const int YELLOW_2 = D4;
const int GREEN_2 = D5;

const int pirSensor1Road1 = D6; // Sensor 1 for Road 1 connected to pin D6
const int pirSensor2Road1 = D7; // Sensor 2 for Road 1 connected to pin D7
const int pirSensor1Road2 = D8; // Sensor 1 for Road 2 connected to pin D8
//const int pirSensor2Road2 = D9; // Sensor 2 for Road 2 connected to pin D9

int countRoad1 = 0; // Initialize variables to store motion counts for each road
int countRoad2 = 0;

unsigned long previousMillis = 0; // Variable to store the last time counts were printed
const long interval = 5000; // Interval for checking counts and adjusting lights (5 seconds)

void setup() {
  Serial.begin(9600); // Initialize serial communication
  pinMode(RED_1, OUTPUT);
  pinMode(YELLOW_1, OUTPUT); //road 1
  pinMode(GREEN_1, OUTPUT);
  pinMode(RED_2, OUTPUT);
  pinMode(YELLOW_2, OUTPUT); //road 1
  pinMode(GREEN_2, OUTPUT);
  
  pinMode(pirSensor1Road1, INPUT); // Set the PIR sensor pins as input
  pinMode(pirSensor2Road1, INPUT);
  pinMode(pirSensor1Road2, INPUT);
  //pinMode(pirSensor2Road2, INPUT);
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

  // Check for motion on Road 2, Sensor 2
  // if (digitalRead(pirSensor2Road2) == HIGH) {
  //   countRoad2++; // Increment count for Road 2
  //   Serial.println("Motion detected on Road 2, Sensor 2");
  // }


  // Calculate the ratio of counts between the two roads
  float ratio = float(countRoad1) / 5;

  // Adjust traffic light timings based on the ratio
  if (ratio > 1.0) { // Road 1 has more motion, so give it more green time
    // Traffic light timings for Road 1
    digitalWrite(RED_1, HIGH);
    digitalWrite(YELLOW_1, LOW);
    digitalWrite(GREEN_1, LOW);
    
    // Traffic light timings for Road 2
    digitalWrite(RED_2, LOW);
    digitalWrite(YELLOW_2, LOW);
    digitalWrite(GREEN_2, HIGH);

    // Adjust delays for Road 2
    delay(2000); // Green light for Road 2 (8 seconds)
    digitalWrite(GREEN_2, LOW);
    digitalWrite(YELLOW_2, HIGH); // Yellow light for Road 2
    delay(1000); // Yellow light for Road 2 (2 seconds)
    digitalWrite(YELLOW_2, LOW);
    digitalWrite(RED_2,HIGH);
    digitalWrite(RED_1,LOW);
    digitalWrite(GREEN_1,HIGH);
    delay(8000);
     digitalWrite(GREEN_1,LOW);
    digitalWrite(YELLOW_1,HIGH);
    delay(1000);
    digitalWrite(YELLOW_1,LOW);
    

  } else if (ratio < 1.0) { // Road 2 has more motion, so give it more green time
    // Traffic light timings for Road 1
    digitalWrite(RED_1, HIGH);
    digitalWrite(YELLOW_1, LOW);
    digitalWrite(GREEN_1, LOW);
    
    // Traffic light timings for Road 2
    digitalWrite(RED_2, LOW);
    digitalWrite(YELLOW_2, LOW);
    digitalWrite(GREEN_2, HIGH);

    // Adjust delays for Road 2
    delay(8000); // Green light for Road 2 (8 seconds)
    digitalWrite(GREEN_2, LOW);
    digitalWrite(YELLOW_2, HIGH); // Yellow light for Road 2
    delay(1000); // Yellow light for Road 2 (2 seconds)
    digitalWrite(YELLOW_2, LOW);
    digitalWrite(RED_2,HIGH);
    digitalWrite(RED_1,LOW);
    digitalWrite(GREEN_1,HIGH);
    delay(2000);
     digitalWrite(GREEN_1,LOW);
    digitalWrite(YELLOW_1,HIGH);
    delay(1000);
    digitalWrite(RED_2,LOW);
    digitalWrite(YELLOW_1,LOW);
  } else { // Equal motion counts on both roads
    //Default traffic light timings for both roads
   digitalWrite(RED_1, HIGH);
 digitalWrite(RED_2,LOW);
 digitalWrite(GREEN_2,HIGH);
  digitalWrite(GREEN_1,LOW);
 delay(5000);
 digitalWrite(GREEN_2,LOW);
  digitalWrite(YELLOW_2,HIGH);
  delay(3000);
 digitalWrite(YELLOW_2,LOW);
  digitalWrite(GREEN_1,HIGH);
  digitalWrite(RED_1,LOW);
  digitalWrite(RED_2,HIGH);

  delay(5000);
  digitalWrite(GREEN_1,LOW);
  digitalWrite(YELLOW_1,HIGH);
  delay(3000);
  digitalWrite(YELLOW_1,LOW);
  }

  // Reset counts for the next cycle
  

  // Delay to avoid reading the sensors too quickly
  delay(100); 
}
