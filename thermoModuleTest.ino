// BenchBudEE HW Checkout Program
//
// thermoModuleTest.ino --
//  Thermocoupler Module Test suit
//

#include "thermoModuleTest.h"
#include "menuUtility.h"

// Declare prototypes for tests here --
//  These are dummy examples and should be replaced.
//
static void thermoModuleTestA(void);
static void thermoModuleTestB(void);
static void thermoModuleTestC(void);

// thermoModuleTestMain --
//  This is the main entry point for the Thermocoupler Module Test menu
//
void thermoModuleTestMain(void)
{
  // Replace the menu entries in the array with the real tests.
  // See menuUtility.h for details.
  const menuLine thermoMenu[] = {
  {1, "Thermocouple Test A", thermoModuleTestA},
  {2, "Thermocouple Test B", thermoModuleTestB},
  {3, "Thermocouple Test C", thermoModuleTestC},
  };

  // No need to change anything else in this function --
  menuLoop("Thermocouple Module Test Menu", thermoMenu, MENU_SIZE(thermoMenu));
}

// Define the test implementations below --
//  These are dummy examples and should be replaced.
//
static void thermoModuleTestA(void)
{
  Serial.println("Thermocouple Module Test A in progress...");
  delay(1000);
  Serial.println("Success!");
}

static void thermoModuleTestB(void)
{
  Serial.println("Thermocouple Module Test B in progress...");
  delay(1000);
  Serial.println("Success!");
}

static void thermoModuleTestC(void)
{
  Serial.println("Thermocouple Module Test C in progress...");
  delay(1000);
  Serial.println("Success!");
}
