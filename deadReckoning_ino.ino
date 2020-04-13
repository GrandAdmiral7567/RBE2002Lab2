#include <Zumo32U4Motors.h>
#include <Zumo32U4Encoders.h>

#include <button.h>       //include your button class from last week
#include <eventTimer.h>  //include your shiny, new event timer class

Button buttonA(14); //button A is pin 14 on the Zumo
eventTimer timer;   //assumes you named your class EventTimer

//use the Pololu libraries for motors and encoders
Zumo32U4Motors motors;
Zumo32U4Encoders encoders; //(we're not acutally using this in this code, but we will soon)

//declare the robot states here
enum robotStates {IDLE_STATE, DRIVING_STATE};
robotStates robotState;


struct segment {
  int leftEffort;
  int rightEffort;
  int interval;
};

const int numberOfSegments = 3;
segment segments[numberOfSegments];
eventTimer zumoTimer;
int iSeg;


void setup()
{
  Serial.begin(9600);
  Serial.println("Hello.");
  iSeg = 0;
  robotState = IDLE_STATE;
  buttonA.Init(); //don't forget to call Init()!
  segments[0] = {115,100, 4500};
  segments[1] = {-100,100,1000};
  segments[2] = {130,100,2300};
}

void loop(){
 
  if(robotState == IDLE_STATE){
    if(buttonA.CheckButtonPress()) {
      robotState = DRIVING_STATE;
      Serial.println("Entering Driving State");
      zumoTimer.start(segments[iSeg].interval);
    }
  }

  
  else if(robotState == DRIVING_STATE){
     Drive(iSeg);
     if(zumoTimer.checkExpired()){
      if(iSeg <= 2){
        Serial.println(iSeg);
        iSeg++;
        zumoTimer.start(segments[iSeg].interval);
      }
      else{
        iSeg = 0;
        robotState = IDLE_STATE;
      }
      }
  }
  
    /*
    Drive(iSeg);
    if(zumoTimer.checkExpired()){
      if(iSeg == 2){
        robotState =IDLE_STATE;
      }
      
      iSeg++;
      zumoTimer.cancel();
      zumoTimer.start(segments[iSeg].interval);
    }
  }
  */

}


//add you handlers here:
//handle the button press
//handle the timer expiring

//you'll want a function called Drive() to actually implement the motor commands and start the timer
void Drive(int iSeg) //pass it the number of the Segment you wish to execute
{
 motors.setSpeeds(segments[iSeg].leftEffort, segments[iSeg].rightEffort);
}



