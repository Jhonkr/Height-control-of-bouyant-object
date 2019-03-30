
const int pingPin = 7; // Trigger Pin of Ultrasonic Sensor; Pino do Trigger do Sensor
const int echoPin = 6; // Echo Pin of Ultrasonic Sensor; Pino de Echo do Sensor
const int LED = 13; //Test internal LED
const double interval = 2; //Value for delay

int Ts = 50; //time sampling

void setup() {
   Serial.begin(9600); // Starting Serial Terminal
   delay(1000);

}
void loop() {
   
   float duration, mm, time_total;
   time_total = millis();

   pinMode(LED, OUTPUT);
   pinMode(pingPin, OUTPUT);
   
   digitalWrite(pingPin, LOW);
   digitalWrite(LED, LOW);
   delayMicroseconds(2);
   
   digitalWrite(pingPin, HIGH);
   delayMicroseconds(2);
   
   digitalWrite(pingPin, LOW);
   pinMode(echoPin, INPUT);
   
   duration = pulseIn(echoPin, HIGH);
   mm = microsecondsToMilimeters(duration);

   Serial.print(mm);
   Serial.print("mm");

   Serial.println();

   if (duration){
    digitalWrite(LED, HIGH); 
   }
   
   // Serial.println(millis()-time_total); //execution time
   
  while ((time_total+Ts) > millis()){
 }
}

long microsecondsToMilimeters(long microseconds) {
   return 10.0 * microseconds / 29.0 / 2.0;
}
