//---------------------------------------------------------------------
//  FOR NEXT IMPLEMENTATIONS:
// - METODO SIMPLE MOVING AVERAGE -V.0.5 
// - METODO PER CODIFICARE IN UNA SOLA FUNZIONE LE INFORMAZIONI IN USCITA SUL MONITOR SERIALE: void fastPrint(String, int)
// 
//
//
//
//
//
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// INIZIO FILE
//
// PROJECT NAME: SENSORE DISTANZA ARDUINO UNO 
//----------------------
// VERSIONING: What's new?
// -- 28/11/2018 V.0.4 - Metodo per plottare i dati. Risolto bug unsigned int sui timer. 
// -- 20/11/2018 V.0.3 - METODO PER LASCIARE ACCESI I LED tot SECONDI SENZA BLOCCARE L'ESECUZIONE DEL PROGRAMMA. (Conteneneva un bug)
// -- 19/11/2018 V.0.2 - riorganizzazione e parametrizzazione del codice --> conseguente ottimizzazione. 
//----------------------
// CREDITS: 
//
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------
//                           LIBRARIES                                
//---------------------------------------------------------------------
// include the library code:
#include <LiquidCrystal.h>
#include <NewPing.h>

//---------------------------------------------------------------------
//                       GLOBAL DECLARATIONS
//---------------------------------------------------------------------

#define CLOCK 200   // delay in ms for Loop refresh rate. 
#define LED_TIMER 1000   //led activation in milliseconds

//ULTRASONIC SENSOR
#define TRIGGER_PIN 5     // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN 4   // Arduino pin tied to echo pin on the ultrasonic sensor.
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
unsigned int timeCounter;
unsigned int lightTimer = 0;
unsigned int distanceTimer = 0;

LiquidCrystal LCD(8, 7, 12, 11, 10, 9);
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);   // Creates a sonar object for controlling the ultrasonic

void lcdprint(int );
void fastPrint(String , int );   //prototipo metodo compatto stampa stringa;

//end
//------------------------------------------------------------------

//@@@@@     WARNING: NOTHING SHOULD BE EDITED BELOW THIS LINE !!! 

// ------------------------------------------------------------------------
//                               SETUP 
//-------------------------------------------------------------------------
void setup() {

  Serial.begin(9600);   //START SERIAL MONITOR.
  LCD.begin(16, 2);    // set up the number of columns and rows on the LCD object

  

  //AREA TEST LCD
 
  LCD.print("test riga 1"); // Print a message to the LCD.

  // set the cursor to column 0, line 1
  // line 1 is the second row, since counting begins with 0
  LCD.setCursor(0, 1);
  LCD.print("test riga 2");  // print to the second line

  delay(1500);

  
  // SETUP ULTRASONIC SENSOR
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
 /* pinMode(DISTANCE_LED, OUTPUT);

  // SETUP LIGHT SENSOR
  pinMode(PHOTORESISTOR_PIN, INPUT);
  pinMode(PHOTORESISTOR_LED, OUTPUT);
*/

// clean up the screen before printing a new reply
  LCD.clear();
  LCD.print("*AVVIO SONAR*");
  delay(2000);
  LCD.setCursor(0,0);
  LCD.print("Distance(cm):");
 

//end setup  
  }  
  
//---------------------------------------------------------------------------
//                               LOOP
//---------------------------------------------------------------------------


void loop() {

  timeCounter = millis();
 /*
  //LIGHT READING
  
  lightValue = analogRead(PHOTORESISTOR_PIN);  
  delayMicroseconds(100); // delay for reading
  
  //Serial.print("Light sensor = " );
  //Serial.println(lightValue);

 // fastPrint("Light sensor = ",lightValue);   //FASTPRINT 

  if (lightValue > LIGHT_THRESHOLD) {
    digitalWrite(PHOTORESISTOR_LED, HIGH);
    lightTimer = millis();
  }
  else if (millis()- lightTimer > LED_TIMER) {
    digitalWrite(PHOTORESISTOR_LED, LOW);
  }
*/
//-----------------------------------------------

  //DISTANCE READING

  distanceValue = calculateDistance();  // Calls a function for measure distance
  
    /*Serial.print("Distanza: ");
    Serial.print(distanceValue);
    Serial.println(" cm");   */    //print distance
 
 
   // fastPrint("Distanza (cm) = ",distanceValue);
  /*
  if ( distanceValue > 0 && distanceValue < DISTANCE_THRESHOLD) {   //check for transits in working range              
    digitalWrite(DISTANCE_LED, HIGH);                                 //active led
    transitCounter++;                                                  //increments by 1 the counter of transits.
    distanceTimer = millis();
  }
  else if (millis()- distanceTimer > LED_TIMER) {
    digitalWrite(DISTANCE_LED, LOW);
  }
  */
  //------------------------------------------------------------------------------

  Serial.println(distanceValue);  //for matlab readings
  lcdprint(distanceValue);
  //------------------------------------------------------------------------------

  while (millis()-timeCounter < CLOCK){
        delayMicroseconds(10);   //WAIT UNTIL CLOCK DURATION
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

//Function for printing distance on display
void lcdprint(int distanceValue){
  LCD.setCursor(13, 1);
  LCD.print(distanceValue); // Convert ping time to distance in cm and print result (0 = outside set distance range)
  LCD.print("     ");
}

