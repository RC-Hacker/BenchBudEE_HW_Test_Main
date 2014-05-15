// BenchBudEE HW Checkout Program
//
// ledModuleTest.ino --
//  LED Module Test suit
//

#include "ledModuleTest.h"
#include "menuUtility.h"

// Declare prototypes for tests here --
//  These are dummy examples and should be replaced.
//
static void ledModuleTestA(void);
static void ledModuleTestB(void);
static void ledModuleTestC(void);

// ledModuleTestMain --
//  This is the main entry point for the LED Module Test menu
//
void ledModuleTestMain(void)
{
  // Replace the menu entries in the array with the real tests.
  // See menuUtility.h for details.
  const menuLine ledMenu[] = {
  {1, "LED Test A", ledModuleTestA},
  {2, "LED Test B", ledModuleTestB},
  {3, "LED Test C", ledModuleTestC},
  };

  // No need to change anything else in this function --
  menuLoop("LED Module Test Menu", ledMenu, MENU_SIZE(ledMenu));
  
  return;
}

// Define the test implementations below --
//  These are dummy examples and should be replaced.
//
static void ledModuleTestA(void)
{
  Serial.println("LED Module Test A in progress...");
  delay(1000);
  Serial.println("Success!");
  
  return;
}

static void ledModuleTestB(void)
{
  Serial.println("LED Module Test B in progress...");
  delay(1000);
  Serial.println("Success!");
  
  return;
}

static void ledModuleTestC(void)
{
  Serial.println("LED Module Test C in progress...");
  delay(1000);
  Serial.println("Success!");
  
  return;
}



  
