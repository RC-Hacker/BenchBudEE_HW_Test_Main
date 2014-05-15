// BenchBudEE HW Checkout Program
//
// relayModuleTest.ino --
//  Relay Module Test suit
//

#include "relayModuleTest.h"
#include "menuUtility.h"

// Declare prototypes for tests here --
//  These are dummy examples and should be replaced.
//
static void relayModuleTestA(void);
static void relayModuleTestB(void);
static void relayModuleTestC(void);

// relayModuleTestMain --
//  This is the main entry point for the Relay Module Test menu
//
void relayModuleTestMain(void)
{
  // Replace the menu entries in the array with the real tests.
  // See menuUtility.h for details.
  const menuLine relayMenu[] = {
  {1, "Relay Test A", relayModuleTestA},
  {2, "Relay Test B", relayModuleTestB},
  {3, "Relay Test C", relayModuleTestC},
  };

  // No need to change anything else in this function --
  menuLoop("Relay Module Test Menu", relayMenu, MENU_SIZE(relayMenu));
  
  return;
}

// Define the test implementations below --
//  These are dummy examples and should be replaced.
//
static void relayModuleTestA(void)
{
  Serial.println("Relay Module Test A in progress...");
  delay(1000);
  Serial.println("Success!");
  
  return;
}

static void relayModuleTestB(void)
{
  Serial.println("Relay Module Test B in progress...");
  delay(1000);
  Serial.println("Success!");
  
  return;
}

static void relayModuleTestC(void)
{
  Serial.println("Relay Module Test C in progress...");
  delay(1000);
  Serial.println("Success!");
  
  return;
}



  
