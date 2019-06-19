/* 
 *  Created by J, KOBYLARZ - https://github.com/Jhonkr/Height-control-of-bouyant-object
   
   
 *  Height control of bouyant object;
   
  
    Ultrasonic sensor Pins:
        VCC: +5VDC
        Trig : Trigger (INPUT) - Pin 7
        Echo: Echo (OUTPUT) - Pin 6
        GND: GND
 
*/
#include <Ultrasonic.h>
#define trigPin 7
#define echoPin 6
#define pwmPin 3
#define Ts 30
int PWM = 110;
int serial = 0;
char inBuffer[4];
float setpoint = 150;

// Control
float pv, dif_pv;
float  pv_ant = 0;
float erro = 0;
float cv_0 = 137;

// float kp = 0.30002; 
// float kd = 3.0003;


float kp = 3;//41; 
float kd = 30;//174; //173;


Ultrasonic ultrasonic(trigPin, echoPin);

void setup() {

             // CA02 | CA01  | CS00 
             //   0  |   1   |   0
             
   TCCR0B = 2 ; // TC0 Control Register B setting value CLK/8 from prescaler 

   pinMode(pwmPin, OUTPUT); // Setting as output pwm pin

   Serial.begin(9600); // Starting Serial Terminal
   delay(1000);

}

void loop() {

   long time_total = millis()/8; // Multiply by 8 to adjust according to PreScaler
   float sound_vel, distance;

   
   sound_vel = 342620; // Sound Vel value from calculator: http://www.audioacustica.com.br/calculadoras_audio/velocidade_som.html 
   float microsec = ultrasonic.timing(); // Return time
   distance = sound_vel*microsec*0.000001/2; //Distance in mm
   
   
   // Control
   erro = setpoint - distance;
   dif_pv = distance - pv_ant;
   PWM = kp * erro - kd*dif_pv + cv_0;
   pv_ant = distance;
   
   if (PWM > 255) PWM = 255;
   if (PWM < 0) PWM = 0;
   
   analogWrite(pwmPin, PWM); // Write PWM value 
   Serial.print(distance);
   //Serial.print(",");
   //Serial.print(PWM);
   Serial.print(",");
   Serial.println(setpoint);
   //Serial.println(millis());    // Execution time
   
    
   if (Serial.available() > 0){
   Serial.readBytes(inBuffer, 4); // Read 4 caracteres in ASCII
   setpoint = atoi(inBuffer); // ASCII to int
   }
   
   while ((time_total+Ts) > millis()/8){}   // Wait for time sampling
}  
