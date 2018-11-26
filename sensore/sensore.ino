//---------------------------------------------------------------------
// TODO FOR NEXT VERSIONS:
// - METODO PER TARARE IL SENSORE DI LUMINOSITà (da fare nel setup) -V.0.4
// - METODO PER CODIFICARE IN UNA SOLA FUNZIONE LE INFORMAZIONI IN USCITA SUL MONITOR SERIALE: void fastPrint(char string[], int digit)
// 

//
//
//
//
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// INIZIO FILE
//
//
// NAME: 
// VERSIONING: // -- v.0.4
// -- 20/11/2018 V.0.3 - METODO PER LASCIARE ACCESI I LED tot SECONDI SENZA BLOCCARE L'ESECUZIONE DEL PROGRAMMA.
// -- 19/11/2018 V.0.2 - riorganizzazione e parametrizzazione del codice --> conseguente ottimizzazione. 
// CREDITS: 
//
//---------------------------------------------------------------------
//                           LIBRARIES
//---------------------------------------------------------------------

#include <NewPing.h>

//---------------------------------------------------------------------
//                       GLOBAL DECLARATIONS
//---------------------------------------------------------------------

#define CLOCK 20   // delay in ms for Loop refresh rate. 
#define LED_TIMER 1000   //led activation in milliseconds

//ULTRASONIC SENSOR
#define TRIGGER_PIN 33     // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN 35    // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 399   // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400cm.
#define DISTANCE_THRESHOLD 50 // Distance we want to check for transits (in centimeters). Better add a 5% tolerance.
#define DISTANCE_LED 34  // Led activated when distance changes.


//LIGHT DEPENDING RESISTOR
#define PHOTORESISTOR_PIN A0  // Arduino pin tied to light resistor.
#define PHOTORESISTOR_LED 32  // Led activated when ambient light changes.
#define LIGHT_THRESHOLD 600   // Light amount we want to check for chan
#define MAX_LIGHT 1000        //Maximum light intensity.


// variables and objects
int transitCounter = 0;
int lightValue, distanceValue; 
int timeCounter;
int lightTimer = 0;
int distanceTimer = 0;

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);   // Creates a sonar object for controlling the ultrasonic
void fastPrint(String string, int digit);   //prototipo metodo compatto stampa stringa;

//end
//------------------------------------------------------------------

//@@@@@     WARNING: NOTHING SHOULD BE EDITED BELOW THIS LINE !!! 

// ------------------------------------------------------------------------
//                               SETUP 
//-------------------------------------------------------------------------
void setup() {

  Serial.begin(9600);   //START SERIAL MONITOR.

  
  // SETUP ULTRASONIC SENSOR
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(DISTANCE_LED, OUTPUT);

  // SETUP LIGHT SENSOR
  pinMode(PHOTORESISTOR_PIN, INPUT);
  pinMode(PHOTORESISTOR_LED, OUTPUT);

 

//end setup  
  }  
  
//---------------------------------------------------------------------------
//                               LOOP
//---------------------------------------------------------------------------


void loop() {
  timeCounter = millis();
  //LIGHT READING
  
  lightValue = analogRead(PHOTORESISTOR_PIN);  
  delayMicroseconds(100); // delay for reading
  
  //Serial.print("Light sensor = " );
  //Serial.println(lightValue);

  
<<<<<<< HEAD
 // fastPrint("Light sensor = ",lightValue);   //FASTPRINT 
=======
  fastPrint("Light sensor = ",lightValue);   //FASTPRINT 
>>>>>>> 9dd7e8dbf83fa69c508d84631b6116d92b4999e4
  if (lightValue > LIGHT_THRESHOLD) {
    digitalWrite(PHOTORESISTOR_LED, HIGH);
    lightTimer = millis();
  }
  else if (millis()- lightTimer > LED_TIMER) {
    digitalWrite(PHOTORESISTOR_LED, LOW);
  }

//-----------------------------------------------

  //DISTANCE READING

  distanceValue = calculateDistance();  // Calls a function for measure distance
    /*Serial.print("Distanza: ");
    Serial.print(distanceValue);
    Serial.println(" cm");   */    //print distance
<<<<<<< HEAD
  // fastPrint("Distanza (cm) = ",distanceValue);
=======
    fastPrint("Distanza (cm) = ",distanceValue);
>>>>>>> 9dd7e8dbf83fa69c508d84631b6116d92b4999e4
   // DEBUG  Serial.println(distanceValue);
  if ( distanceValue > 0 && distanceValue < DISTANCE_THRESHOLD) {   //check for transits in working range              
    digitalWrite(DISTANCE_LED, HIGH);                                 //active led
    transitCounter++;                                                  //increments by 1 the counter of transits.
    distanceTimer = millis();
  }
  else if (millis()- distanceTimer > LED_TIMER) {
    digitalWrite(DISTANCE_LED, LOW);
  }
  
  Serial.println(distanceValue);
  //---------------------------------------

  while (millis()-timeCounter < CLOCK){
        delayMicroseconds(10);   //LOOP REFRESH RATE
  }
//fine loop
 }





////////////////////////////////////////////////
////////////////// FUNZIONI //////////////////////   
/////////////////////////////////////////////// 

// Function for calculating the distance measured by the Ultrasonic sensor
int calculateDistance(){ 
  // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  return sonar.ping_cm(); //  Send ping, get distance in cm and print result (0 = outside set distance range)
}

// EXPERIMENTAL
void fastPrint(String string, int digit){
  Serial.print(string); 
  Serial.println(digit);
  Serial.println();
}








