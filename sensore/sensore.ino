//----------------------
// CREDITS:
//
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------
//                           LIBRARIES
//---------------------------------------------------------------------

#include <NewPing.h>

//---------------------------------------------------------------------
//                       GLOBAL DECLARATIONS
//---------------------------------------------------------------------

#define CLOCK 50      // delay in ms for Loop refresh rate.


//ULTRASONIC SENSOR
#define TRIGGER_PIN 33        // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN 35           // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 400      // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400cm.
#define DISTANCE_THRESHOLD 50 // Distance we want to check for transits (in centimeters). Better add a 5% tolerance.


// variables and objects
int transitCounter = 0;
int distanceValue;
unsigned int tempo;
unsigned long int timeCounter;

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // Creates a sonar object for controlling the ultrasonic

//end
//------------------------------------------------------------------

//@@@@@     WARNING: NOTHING SHOULD BE EDITED BELOW THIS LINE !!!

// ------------------------------------------------------------------------
//                               SETUP
//-------------------------------------------------------------------------
void setup()
{

  Serial.begin(9600); //START SERIAL MONITOR.

  // SETUP ULTRASONIC SENSOR
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);


  //end setup
}

//---------------------------------------------------------------------------
//                               LOOP
//---------------------------------------------------------------------------

void loop()
{ //-----------------------------------------------

  //DISTANCE READING
  tempo = sonar.ping();
  distanceValue = tempo/US_ROUNDTRIP_CM;

  if(distanceValue>0 && distanceValue<=DISTANCE_THRESHOLD){
   transitCounter++;
  }



  Serial.println(distanceValue);
  if(transitCounter>0){
    Serial.println("Conteggio Auto = %d",transitCounter);
  }
  delay(CLOCK);
  //fine loop
}

////////////////////////////////////////////////
////////////////// FUNZIONI //////////////////////
///////////////////////////////////////////////





