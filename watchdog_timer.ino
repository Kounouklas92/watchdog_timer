/* O συγκεκριμένος κώδικας χρησιμοποιεί την λογική του watchdog 
 * προκειμένου να θέσει το arduino σε κατάσταση αυτόματου reboot.  
 * Χρησιμοποίησα έναν αισθητήρα απόστασης ο οποίος παίρνει διαφορετικές 
 * μετρήσεις.Θέτω τον timer του watchdog στα 4s.Αν δεν επιστραφεί reset(απάντηση
 * από το watchdog) μέσα σε αυτό το χρονικό περιθώριο από την αρχή της εκτέλεσης του 
 * κώδικα τότε το arduino μεταβαίνεi σε κατάσταση reboot. Με την εντολή While(1) εγκλωβίζω
 * την εκτελέση του προγραμμάτος σε μιά ατέρμονη λούπα επίτηδες προκειμένου να δουλέψει το 
 * watchdog και να πάμε σε αυτόματο reboot μετά τις 50 μετρήσεις του αισθητήρα.
 */
#include <avr/wdt.h>

#define echoPin 6 // echo Pin at pin 6
#define trigPin 7 // trigger Pin at 7

void buzzer1();
void readUltrasonicDistance();

long duration;
int distance;
int i;
const int buzzer = 8;
 
void setup(){
  Serial.begin(9600);
  
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); 
  pinMode(buzzer, OUTPUT);
  

 wdt_disable();  //Disable watchdog 
 delay(2000); 
  
  
  
  // delay a bit more so it is clear we are done with setup
 delay(2000);
 Serial.println("reboot is done");
 buzzer1(); // warning sound
 wdt_enable(WDTO_4S); // watchdog timer with 4 Seconds time out

  
  
  
}
 
void loop() {
  
 

  
 for (int i=0; i<50; i++){
     readUltrasonicDistance();
     delay(1000);
     wdt_reset();   
}
while(1){}
}
  
void buzzer1(){
    tone(buzzer, 1000); // Send 1KHz sound signal
    delay(1000);        
    noTone(buzzer);     // Stop sound
    delay(1000);
}

void readUltrasonicDistance(){
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
// Sets the trigPin HIGH (ACTIVE) for 10 microseconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);
// Calculating the distance
distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
// Displays the distance on the Serial Monitor
Serial.print("Distance: ");
Serial.print(distance);
Serial.println(" cm");
}
