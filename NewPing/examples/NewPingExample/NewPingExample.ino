//HC RS04 Sensore ultrasuoni
//Giuseppe Caccavale

#include <LiquidCrystal.h>
#include <NewPing.h>
#define TRIGGER_PIN  9  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     10  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 300 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
const int Pulsante = 8;
unsigned long previousMillis = 0; 
const long interval = 500;

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

int value_SetDist = 0;
int SetDistance = 0;
int ValueDist = 0;

void setup() {
  pinMode(Pulsante, INPUT);
  //Serial.begin(115200); 
  lcd.begin(16, 2);
}

void loop() {
  delay(50);                      // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  unsigned int uS = sonar.ping(); // Send ping, get ping time in microseconds (uS).
  ValueDist = uS / US_ROUNDTRIP_CM;
  value_SetDist = digitalRead(Pulsante);
  unsigned long currentMillis = millis();
  
  if(value_SetDist == HIGH){
  delay(2000);
  SetDistance = ValueDist;}
  
  ValueDist = ValueDist - SetDistance;
 /* Serial.print("Ping: ");
  Serial.print(ValueDist); // Convert ping time to distance in cm and print result (0 = outside set distance range)
  Serial.println("cm");*/
  
if(currentMillis - previousMillis >= interval) { 
    previousMillis = currentMillis;   
    lcd.setCursor(0,0);
    lcd.print("Set Dist: ");
    lcd.print(SetDistance);
    lcd.print(" cm        ");
    
    lcd.setCursor(0,1);
    lcd.print("Distanza: ");
    lcd.print(ValueDist);
    lcd.print(" cm        ");}
}
