// BenchBudEE HW Checkout Program
//
// BenchBudEE_HW_Test_Main.ino --
//  This is the top-level source file for the 
//  BenchBudEE HW Checkout and Test program.
//

#include "menuUtility.h"
#include "fanModuleTest.h"
#include "thermoModuleTest.h"
#include "ledModuleTest.h"
#include "adjPowerModuleTest.h"
#include "relayModuleTest.h"

void ledModuleTestMain(void);

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  // The Main Menu --
  //  The main menu selections and the corresponding function called
  //  upon selectoin are defined in the array below.  More options/sub-menus
  //  can be added to this array as needed.  See menuUtility.h for details.
  //
  const menuLine mainMenu[] = {
  {1, "Fan Test", fanModuleTestMain},
  {2, "Thermocouple Test", thermoModuleTestMain},
  {3, "LED Test", ledModuleTestMain},
  {4, "Adjustable Power Test", adjPowerModuleTestMain},
  {5, "Relay Test", relayModuleTestMain},
  };
  
  // No need to change anything else in this function --
  menuLoop("Main Menu", mainMenu, MENU_SIZE(mainMenu));
}

