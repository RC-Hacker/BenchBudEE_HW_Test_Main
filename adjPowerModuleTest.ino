// BenchBudEE HW Checkout Program
//
// adjPowerModuleTest.ino --
//  Power Module Test suit
//

#include "adjPowerModuleTest.h"
#include "menuUtility.h"

// Declare prototypes for tests here --
//  These are dummy examples and should be replaced.
//
static void adjPowerModuleTestA(void);
static void adjPowerModuleTestB(void);
static void adjPowerModuleTestC(void);

// adjPowerModuleTestMain --
//  This is the main entry point for the Power Module Test menu
//
void adjPowerModuleTestMain(void)
{
  // Replace the menu entries in the array with the real tests.
  // See menuUtility.h for details.
  const menuLine adjPowerMenu[] = {
  {1, "Adjustable Power Test A", adjPowerModuleTestA},
  {2, "Adjustable Power Test B", adjPowerModuleTestB},
  {3, "Adjustable Power Test C", adjPowerModuleTestC},
  };

  // No need to change anything else in this function --
  menuLoop("Adjustable Power Module Test Menu", adjPowerMenu, MENU_SIZE(adjPowerMenu));
}

// Define the test implementations below --
//  These are dummy examples and should be replaced.
//
static void adjPowerModuleTestA(void)
{
  Serial.println("Adjustable Power Module Test A in progress...");
  delay(1000);
  Serial.println("Success!");
}

static void adjPowerModuleTestB(void)
{
  Serial.println("Adjustable Power Module Test B in progress...");
  delay(1000);
  Serial.println("Success!");
}

static void adjPowerModuleTestC(void)
{
  Serial.println("Adjustable Power Module Test C in progress...");
  delay(1000);
  Serial.println("Success!");
}



  
