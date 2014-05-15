// BenchBudEE HW Checkout Program
//
// fanModuleTest.ino --
//  Fan Module Test suit
//

#include "fanModuleTest.h"
#include "menuUtility.h"

// Declare prototypes for tests here --
//  These are dummy examples and should be replaced.
//
static void fanModuleTestA(void);
static void fanModuleTestB(void);
static void fanModuleTestC(void);

// fanModuleTestMain --
//  This is the main entry point for the Fan Module Test menu
//
void fanModuleTestMain(void)
{
  // Replace the menu entries in the array with the real tests.
  // See menuUtility.h for details.
  const menuLine fanMenu[] = {
  {1, "Fan Test A", fanModuleTestA},
  {2, "Fan Test B", fanModuleTestB},
  {3, "Fan Test C", fanModuleTestC},
  };

  // No need to change anything else in this function --
  menuLoop("Fan Module Test Menu", fanMenu, MENU_SIZE(fanMenu));
}

// Define the test implementations below --
//  These are dummy examples and should be replaced.
//
static void fanModuleTestA(void)
{
  Serial.println("Fan Module Test A in progress...");
  delay(1000);
  Serial.println("Success!");
}

static void fanModuleTestB(void)
{
  Serial.println("Fan Module Test B in progress...");
  delay(1000);
  Serial.println("Success!");
}

static void fanModuleTestC(void)
{
  Serial.println("Fan Module Test C in progress...");
  delay(1000);
  Serial.println("Success!");
}



  
