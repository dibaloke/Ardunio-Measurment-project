#include <Keypad.h>

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//Basic Initialization

int keypad_security_state=0;
//Define the number of attempt is accepted before security system is activiated
int accepted_no_of_attempt=2;
const int buzzer_pin = 11;

int attempt=0;
bool password_matched=true;
//password array contains the hard-coded value of real password
char password[]={'5','5','5','5','5','5'};
const int password_length=6;
//password_array will contain the password entered by the user
char password_array[password_length];


//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// Keypad Number Definition
const byte ROWS = 4; //four rows
const byte COLS = 4; //three columns
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//Define pin
byte rowPins[ROWS] = {2, 3, 4, 5}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {6,7,8,9}; //connect to the column pinouts of the keypad



// Instance Creation of Keypad Class
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );


//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


void setup(){
  Serial.begin(9600);
   pinMode(buzzer_pin, OUTPUT); 
 
}
  
void loop(){//void loop starts

  if(keypad_security_state==1){
    Serial.println("Hello Intruder, Caught");
    buzzer();
    
    
    }

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 // Here we take the input to the keypad
 if(keypad_security_state==0){
   for(int i=0;i<password_length;i++){//for loop starts

           while(1){ //while loop starts

               char key = keypad.getKey();  
                       if (key){  // if starts
                               Serial.println(key);
                               password_array[i]=key;
                               break;
                               } //if ends

          }//while loop ends

   }//for loop ends

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


// Serial print to check if the number pressed is the same length as the password_length
//Serial.println("Password_length number of key is pressed");





//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// Here we match the enterd keypad  number to password and count the number of attempts
for(int i=0;i<password_length;i++){// second for loop starts
 
//       Serial.println(password_array[i]);
           if(password[i]!=password_array[i]){//if  starts
               password_matched=false;
         
      }//if ends
            if(password[i]==password_array[i]){//if  starts
               
               if(i==(password_length-1)&& password_matched==false ){
                password_matched=false;
                Serial.println("Inside Bug");
               }

               else{
               password_matched=true;
               Serial.println("Bug");
               }
               //Bug
               
         
      }//if ends

    
      if(i==(password_length-1) && password_matched==false){//if starts
                  attempt++;
                  Serial.print("Number of attempt: ");
                  Serial.print(attempt);
                  Serial.println();
           
        
        
      }//if ends




      
  
}// second for loop ends

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//Take Decision based on number of attempts and password matching

if(password_matched==true && attempt<=accepted_no_of_attempt){
  
   Serial.println("Welcome Home");
  
  }
 
     

else if(password_matched==false && attempt >accepted_no_of_attempt ){

  Serial.println("Intruder Alert");
  keypad_security_state=1;
  
  
  }  


 }//base if ends
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

 
}//void loop ends



void buzzer(){

  
  tone(buzzer_pin, 1000); // Send 1KHz sound signal...
  delay(1000);        // ...for 1 sec
  noTone(buzzer_pin);     // Stop sound...
  delay(1000);        // ...for 1sec

}        
