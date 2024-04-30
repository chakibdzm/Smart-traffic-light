#define RED_1 D1 // side 1 road 1
#define YELLOW_1 D2
#define GREEN_1 D3

//#define RED_2 D4 //side 2 road 2
//#define YELLOW_2 D5
//#define GREEN_2 D6
#define cpt1 D5
#define cpt2 D6

#define cpt3 D7
#define cpt4 D8

               // choose the input pin (for PIR sensor)
int val = 0; 
int road1=0;
int road2=0;
void setup() {
  // Initialize GPIO pins for traffic lights as outputs
  //pinMode(RED_1, OUTPUT);
  //pinMode(YELLOW_1, OUTPUT); //road 1
  //pinMode(GREEN_1, OUTPUT);


  pinMode(cpt1, INPUT);  
  pinMode(cpt2, INPUT); 
  pinMode(cpt3, INPUT); 
  pinMode(cpt4, INPUT);    // declare sensor as input
 
  Serial.begin(9600);
}

void loop() {


   // read input value
  if ((digitalRead(cpt1) || digitalRead(cpt2))==HIGH) {            // check if the input is HIGH 
   
      // we have just turned on
      
      road1++;

      Serial.println("Motion detected road 1" + road1);
  
      // We only want to print on the output change, not state
      
    
  } 
  
  
   if ((digitalRead(cpt3) || digitalRead(cpt4)) == HIGH) {
      road2++;
   
      // we have just turned of
      Serial.println("Motion detected road 2" + road2);
      // We only want to print on the output change, not state
     
  };

  delay(1000);
  


  // Implement traffic light sequence for Road 1
 // digitalWrite(RED_1, HIGH);
 // digitalWrite(RED_2,LOW);
 // digitalWrite(GREEN_2,HIGH);
  //digitalWrite(GREEN_1,LOW);
//  delay(5000);
 // digitalWrite(GREEN_2,LOW);
  //digitalWrite(YELLOW_2,HIGH);
  //delay(3000);
 // digitalWrite(YELLOW_2,LOW);
  //digitalWrite(GREEN_1,HIGH);
  //digitalWrite(RED_1,LOW);
  //digitalWrite(RED_2,HIGH);

  //delay(5000);
  //digitalWrite(GREEN_1,LOW);
  //digitalWrite(YELLOW_1,HIGH);
  //delay(3000);
  //digitalWrite(YELLOW_1,LOW);
    
}
