


// include the library code:
#include <LiquidCrystal.h>
#include <math.h> 
#include <AccelStepper.h>
#include <MultiStepper.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);


int lazer = 13;
int bPin = A0;
int bPin2 = A1;
int bPin3 = A2;
int slow = 6;
int ls = A3;
int m = 0;
double t = 0.000000;
double tsec = 0.000000;



int angle1 = 0;

int angle2 = 0;

int overallangle = 0;
int dist1 = 0;
int dist2 = 0;
int bob = 0;
double d = 0.000000;
double dd = 0.000000;

double s = 0.000000;
double as = 0.000000;

long gotoposition[2];

int h1 = 0;

AccelStepper stepper1(1, 9, 8); // (Type:driver, STEP, DIR)
AccelStepper stepper2(1, 10, 7);

MultiStepper StepperControl; 


float setspeed=200;
float motorspeed;



void setup() {

 
  pinMode(bPin, INPUT);
  pinMode(bPin2, INPUT);
  pinMode(bPin3, INPUT);
  pinMode(ls, INPUT);
 
  pinMode(lazer, OUTPUT);
  pinMode(slow, OUTPUT);
  
  
  
  lcd.begin(16, 2);
  // Print a message to the LCD.
   lcd.setCursor(0, 0);
  lcd.print("Welcome to ");
  lcd.setCursor(0, 1);
  lcd.print("chillis");

  Serial.begin(9600);
  stepper1.setMaxSpeed(1000);
  stepper1.setSpeed(300);
  stepper2.setMaxSpeed(1000);
  stepper2.setSpeed(300);
  

  

  // Create instances for MultiStepper - Adding the 2 steppers to the StepperControl instance for multi control
  StepperControl.addStepper(stepper1);
  StepperControl.addStepper(stepper2);
  

 
}


void home() {
  while(digitalRead(ls)== 1){
   
           //digitalWrite(slow, HIGH);
           stepper1.setSpeed(400);
           stepper1.runSpeed();
           stepper2.setSpeed(300); 
              //stepper2.runSpeed();             
              stepper2.moveTo(angle1); 
                           
              stepper2.runSpeedToPosition();
           
      }
       stepper1.setCurrentPosition(0);
       stepper2.setCurrentPosition(0);


}


void loop() {

  home();


    while(m == 0){
                 
                  lcd.setCursor(0, 0);
                  lcd.print("angle 1      ");
                  lcd.setCursor(0, 1);
                  lcd.print("                ");
                  lcd.setCursor(0, 1);
                  lcd.print(angle1);
        
         digitalWrite(lazer, HIGH);
            while(digitalRead(bPin) == HIGH){       
                stepper2.setSpeed(-150);
                stepper2.runSpeed();
                angle1=stepper2.currentPosition();               
                      }
    
     
             while(digitalRead(bPin2) == HIGH){      
                stepper2.setSpeed(150);
                stepper2.runSpeed();
                angle1=stepper2.currentPosition();
                      }
             if(digitalRead(bPin3) == HIGH){   
                digitalWrite(lazer, LOW);
                //angle1=angle1*4;
                m++; 
                delay(300);
                }
              }

              while(m == 1){
   
                  lcd.setCursor(0, 0);
                  lcd.print("set end distance");
                  lcd.setCursor(0, 1);
                  lcd.print("                ");
                  lcd.setCursor(0, 1);
                  lcd.print(dist1);
               
 
      
              while(digitalRead(bPin) == HIGH){       
              
                 stepper1.setSpeed(400);
                 stepper1.runSpeed();
                 dist1=stepper1.currentPosition();
                      }

              while(digitalRead(bPin2) == HIGH){      
       
                 stepper1.setSpeed(-400);
                 stepper1.runSpeed();
                 dist1 = stepper1.currentPosition();
                      }
                      
               if(digitalRead(bPin3) == HIGH){
                 m++;  
                  delay(300); 
                }

      
               }

                while(m == 2){
                 
                 lcd.setCursor(0, 0);
                 lcd.print("angle 2         ");
                 lcd.setCursor(0, 1);
                 lcd.print("                ");
                 lcd.setCursor(0, 1);
                 lcd.print(angle2);
        
                digitalWrite(lazer, HIGH);
                   while(digitalRead(bPin) == HIGH){       
                      stepper2.setSpeed(-150);
                      stepper2.runSpeed();
                      angle2=stepper2.currentPosition();
                      }
    
     
                   while(digitalRead(bPin2) == HIGH){      
                      stepper2.setSpeed(150);
                      stepper2.runSpeed();
                      angle2=stepper2.currentPosition();
                      }
             if(digitalRead(bPin3) == HIGH){   
                digitalWrite(lazer, LOW);
                //angle2=angle2*4;
                m++; 
                delay(300);
                }
              }
          while(m == 3){
               //bob = 1;
               lcd.setCursor(0, 0);
               lcd.print(" Time set       ");
               lcd.setCursor(0, 1);
               lcd.print(" Speed Run      ");
               overallangle=angle1-angle2;
               if(overallangle>1){
                  overallangle=-1*overallangle;
                    }

                  while(digitalRead(bPin2) == HIGH){
                   bob = 2;
                    lcd.setCursor(0, 1);
                    lcd.print(">");
                    lcd.setCursor(0, 0);
                    lcd.print(" ");
                    delay(300);

                                
                    }
                  while(digitalRead(bPin) == HIGH){
                   bob = 1;  
                    lcd.setCursor(0, 0);
                    lcd.print(">");
                    lcd.setCursor(0, 1);
                    lcd.print(" "); 
                    delay(300);          
                    }

               
              
               if(digitalRead(bPin3) == HIGH){

                m++;
                delay(300);

                
               }
             
               
          }
          while(m == 4){

              home();
              digitalWrite(slow, HIGH);
              lcd.setCursor(0, 1);
              lcd.print("               ");

             
            

            

            dd=dist1*4;

            if(bob == 1){
  
              lcd.setCursor(0, 0);
              lcd.print("Set time in min");
              lcd.setCursor(0, 1);
              //lcd.print("               ");
              lcd.print(t);

                while(digitalRead(bPin2) == HIGH){                           
                  t++;
                  delay(200);
                    }
                while(digitalRead(bPin) == HIGH){                       
                  t=t-1;
                  delay(200);
                    }
                    

                    if(digitalRead(bPin3) == HIGH){
                      m = 5;
                      delay(300);
                    }
                  
            }
            if(bob == 2){
              m = 6;
              delay(300);
            }

                
          }
          while(m == 5){
            digitalWrite(slow, HIGH);
            dd=dist1*4;
            tsec = t*60;
            
            s = dd/tsec;
            as = angle2*8/tsec;

            stepper1.setSpeed(s);
            stepper2.setSpeed(as);

            stepper1.moveTo(dd);
            stepper2.moveTo(angle2*8);

            stepper1.runSpeedToPosition();
            stepper2.runSpeedToPosition();

            
          }
          while(m == 6){
            digitalWrite(slow, HIGH);
            dd=dist1*4;
            tsec = 10;
            
            s = dd/tsec;
            as = angle2*8/tsec;

            stepper1.setSpeed(s);
            stepper2.setSpeed(as);

            stepper1.moveTo(dd);
            stepper2.moveTo(angle2*8);

            stepper1.runSpeedToPosition();
            stepper2.runSpeedToPosition();
            
          }

            
}

                 
  
             
  
