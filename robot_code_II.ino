#include <Servo.h>
#define IR_RECEIVE_PIN 9
#include <IRremote.hpp>
 unsigned long res;
unsigned long fres;

int latch = 10; 
int clock = 12; 
int data= 13; 

int D1 = A0;
int D2 = A5;
int D3 = A1;
int D4 = A4;
Servo myservo; 
int delta;
int modul = 0;
int a;
int x;
int y;
int z;
int servo = 90;
bool s = 0;
bool r = 0;  // Declaring Bool variable named r set to 0
bool l = 0;  // Declaring Bool variable named l set to 0
bool u = 0;  // Declaring Bool variable named u set to 0
bool d = 0;
bool ri = 0;
bool le = 0;



const byte table[10]=
{
    B11111100,  // 0
  B01100000,  // 1
  B11011010,  // 2
  B11110010,  // 3
  B01100110,  // 4
  B10110110,  // 5
  B10111110,  // 6
  B11100000,  // 7
  B11111110,  // 8
  B11100110,  // 9
};

void Base(int x, int y, int z, int a) {  //Defining a function named base with int inputs x, y, z, a.
  analogWrite(5, x);                     // analog write pin 5 the value of parameter x (LEFT SPEED)
  analogWrite(6, y);                     // analog write pin 6 the value of parameter y (RIGHT SPEED)
  digitalWrite(7, z);                    // digital write to pin 7 the value of parameter z(LEFT FORWARD/REVERSE)
  digitalWrite(8, a);                    // digital write to pin 8 the value of parameter a(RIGHT FORWARD/REVERSE)
  digitalWrite(3, 1);                    // digital write to pin 3 5V (STANDBY PIN)
}

// --------------------ALL MVMNT FUNCTION DECLARATIONS
void STOP() {          // Function to stop mouvment of car
  analogWrite(5, 0);   // LEFT SPEED 0
  analogWrite(6, 0);   // RIGHT SPEED 0
  digitalWrite(7, 0);  // LEFT MOTORS REVERSE
  digitalWrite(8, 0);  // RIGHT MOTOR REVERSE
  digitalWrite(3, 0);  // ACTIVATE STANDBY
}

void Forward(int x) {  //Declaring the forward function with the int parameter x

  Base(x, x, 1, 1);  // that calls the function base and passes the value of parameter x to the parameters x and y of base and the value 1 to z ands a
}


void Backward(int x) {  //Declaring the backward function with the int parameter x

  Base(x, x, 0, 0);  // that calls the function base and passes the value of parameter x to the parameters x and y of base and the value 0 to z ands a
}

void Right_F(int x) {    //Declaring the Right_F function with the int parameter x
  Base(x / 2, x, 1, 1);  // that calls the function base and passes the value of parameter x/2 and x to the parameters x and y of base and the value 1 to z ands a
}
void Right_B(int x) {    //Declaring the Right_B function with the int parameter x
  Base(x / 2, x, 0, 0);  // that calls the function base and passes the value of parameter x/2 and x to the parameters x and y of base and the value 0 to z ands a
}

void Right(int x) {  //Declaring the Right function with the int parameter x
  Base(x, x, 0, 1);  // that calls the function base and passes the value of parameter x to the parameters x and y of base and the value 0 and 1 to z ands a
}

void Left(int x) {   //Declaring the Left function with the int parameter x
  Base(x, x, 1, 0);  // that calls the function base and passes the value of parameter x to the parameters x and y of base and the value 1 and 0 to z ands a
}
void Left_F(int x) {     //Declaring the Right_B function with the int parameter x
  Base(x, x / 2, 1, 1);  // that calls the function base and passes the value of parameter x and x/2 to the parameters x and y of base and the value 0 to z ands a
}
void Left_B(int x) {     //Declaring the Right_B function with the int parameter x
  Base(x, x / 2, 0, 0);  // that calls the function base and passes the value of parameter x and x/2 to the parameters x and y of base and the value 0 to z ands a
}


void Display4(int num, int num1, int num2, int num3){   
 
delay(5);

    digitalWrite(D2, 1);
    digitalWrite(D3, 1);
    digitalWrite(D4, 1);
    digitalWrite(D1, 0);
      digitalWrite(latch, 0);
    shiftOut(data, clock, LSBFIRST, table[num3]);
           digitalWrite(latch, 1);



digitalWrite(D1, 1);
    digitalWrite(D3, 1);
    digitalWrite(D4, 1);
    digitalWrite(D2, 0);
      digitalWrite(latch, 0);
    shiftOut(data, clock, LSBFIRST, table[num2]);
           digitalWrite(latch, 1);


digitalWrite(D1, 1);
    digitalWrite(D2, 1);
    digitalWrite(D4, 1);
    digitalWrite(D3, 0);
      digitalWrite(latch, 0);
    shiftOut(data, clock, LSBFIRST, table[num1]);
           digitalWrite(latch, 1);
  

digitalWrite(D1, 1);
    digitalWrite(D2, 1);
    digitalWrite(D3, 1);
    digitalWrite(D4, 0);
      digitalWrite(latch, 0);
    shiftOut(data, clock, LSBFIRST, table[num]);
           digitalWrite(latch, 1);



    digitalWrite(D4, 1);
       digitalWrite(D3, 1);
           digitalWrite(D2, 1);
                       digitalWrite(D1, 1);
    
}

void setup()
{
Serial.begin(9600);
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK); // Start the receiver
   myservo.attach(11);
   pinMode(latch, OUTPUT);
    pinMode(clock, OUTPUT);
    pinMode(data, OUTPUT);
     pinMode(D1, OUTPUT);
    pinMode(D2, OUTPUT);
    pinMode(D3, OUTPUT);
     pinMode(D4, OUTPUT);
}

void loop() {
  Display4 (x, y, z, a);
  if (IrReceiver.decode()) {
    res = IrReceiver.decodedIRData.decodedRawData; // Print "old" raw data
      IrReceiver.resume(); // Enable receiving of the next value
  }

  


if(res!= 0 && res!=fres){

fres= res;
Serial.println(fres);
switch (fres) {       // if results.value is equal to....
      case 3125149440:               // the On/off button then...
        Serial.println("ON/OFF");  // serial print on/ off
        s =1 ; 
        u = 0;                   // bool u is equal to 1
        d = 0;                   // bool d is equal to 0
        l = 0;                   // bool l is equal to 0
        r = 0;         
       le= 0;
       ri = 0;
        break;
      case 4061003520:             // the rept button
        Serial.println("REPT");  // serial print rept             // stop moving
           // delay 1 second
         // set toggle equal to 1
        break;
      case 3860463360:           // the EQ button
        Serial.println("EQ");  // serial print EQ
        // set toggle equal to 3
        break;
      case 3910598400:
        Serial.println("0");
        delta = 0;
        modul++;
        break;
      case 4077715200:
        Serial.println("1");
        delta = 1;
        modul++;
        break;
      case 3877175040:
        Serial.println("2");
        delta = 2;
        modul++;
        break;
      case 2707357440:
        Serial.println("3");
        delta = 3;
        modul++;
        break;
      case 4144561920:
        Serial.println("4");
        delta = 4;
        modul++;
        break;
      case 3810328320:
        Serial.println("5");
        delta = 5;
        modul++;
        break;
      case 2774204160:
        Serial.println("6");
        delta = 6;
        modul++;
        break;
      case 3175284480:
        Serial.println("7");
        delta = 7;
        modul++;
        break;
      case 2907897600:
        Serial.println("8");
        delta = 8;
        modul++;
        break;
      case 3041591040:
        Serial.println("9");
        delta = 9;
        modul++;
        break;
         case 3208707840:
        Serial.println("play");
        modul++;
        fres = 0;
        res = 0;
        break;   // if results.value is equal to....
      case 3108437760:             //the VOL + button then...
        Serial.println("VOL+");  // Serial print Vol +
        u = 1;                   // bool u is equal to 1
        d = 0;                   // bool d is equal to 0
        l = 0;                   // bool l is equal to 0
        r = 0;         
        s = 0;          // bool r is equal to 0
        break;

      case 3141861120:            //the |<< button then...
        Serial.println("|<<");  // Serial print |<<
        u = 0;                  // bool u is equal to 0
        d = 0;                  // bool d is equal to 0
        l = 1;                  // bool l is equal to l
        r = 0; 
        s = 0;                  // bool r is equal to 0
        break;

      case 3158572800:            //the >>| button then...
        Serial.println(">>|");  // Serial print >>|
        u = 0;                  // bool u is equal to 0
        d = 0;                  // bool d is equal to 0
        l = 0;                  // bool l is equal to 0
        r = 1;
        s = 0;                   // bool r is equal to 1
        break;

      case 3927310080:             //the VOL + button then...
        Serial.println("VOL-");  // Serial print Vol -
        u = 0;                   // bool u is equal to 0
        d = 1;                   // bool d is equal to 1
        l = 0;                   // bool l is equal to 0
        r = 0;
        s = 0;                    // bool r is equal to 0
        break;

      case 4127850240:
        Serial.println("^^");
        ri = 1;
        le = 0;
        s= 0;
        break;  
    case 4161273600:
        Serial.println("vv");
        ri = 0;
        le = 1;
        s= 0;
        break; 
}}
if (s == 0){
  if (r == 1) {  //if r is equal to 1
      Right(100);  //Move right at speed 100
    }
    if (u == 1) {    //if u is equal to 1
      Forward(100);  //Move forward at speed 100
    }
    if (l == 1) {  //if l is equal to 1
      Left(100);   //Move left at speed 100
    }
    if (d == 1) {     //if d is equal to 1
      Backward(100);  //Move backward at speed 100
    } 
    if(ri == 1 &&le == 0){
    Serial.println("ri");
    servo = 180;
     }
     if(le == 1 && ri ==0){
    Serial.println("le");
    servo = 0;
     }
}
    else if (s ==1){
      STOP();
      servo = 90;
Serial.println("stop");
    }

  myservo.write(servo);

  if (modul != 0) {
    if (modul % 4 == 0) {
      x = delta;
    }
    if (modul % 4 == 1) {
      y = delta;
    }
    if (modul % 4 == 2) {
      z = delta;
    }
    if (modul % 4 == 3) {
      a = delta;
    }
  }
}

 

