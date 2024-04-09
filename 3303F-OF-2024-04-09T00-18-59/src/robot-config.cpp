#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors

// VEXcode generated functions
digital_out Hang = digital_out(Brain.ThreeWirePort.H);

void CTier();



void Ctier() 
  { 
    if(Hang.value())
    {
      Hang.set(false); 
      wait(200,msec); 
    }
    else 
    {
      Hang.set(true); 
      wait(200,msec);
    }
  }





























/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}