// BenchBudEE HW Checkout Program
//
// relayModuleTest.ino --
//  Relay Module Test suit
//

#include "relayModuleTest.h"
#include "menuUtility.h"
#include "Relay.h"

// Declare prototypes for tests here --
//  These are dummy examples and should be replaced.
//
static void relayModuleOff(void);
static void relayModuleOn(void);
static void relayModuleStatus(void);
static void relayModuleToggle(void);

static Relay relay(relayPin);

// relayModuleTestMain --
//  This is the main entry point for the Relay Module Test menu
//
void relayModuleTestMain(void)
{
  // Replace the menu entries in the array with the real tests.
  // See menuUtility.h for details.
  const menuLine relayMenu[] = {
  {1, "Turn on the relay", relayModuleOn},
  {2, "Turn off the relay", relayModuleOff},
  {3, "Toggle the relay", relayModuleToggle},
  {4, "Get relay status", relayModuleStatus},
  };

  // No need to change anything else in this function --
  menuLoop("Relay Module Test Menu", relayMenu, MENU_SIZE(relayMenu));
}

// relayModuleOff --
// Turn off the relay
//
static void relayModuleOff(void)
{
  relay.off();
  Serial.println("The relay is now off");
  delay(1000);
}

// relayModuleOn --
// Turn off the relay
//
static void relayModuleOn(void)
{
  relay.on();
  Serial.println("The relay is now on");
  delay(1000);
}

// relayModuleToggle --
// Toggle the state of the relay
//
static void relayModuleToggle(void)
{
  bool savedState = relay.isOn();
  relay.toggle();
  Serial.print("Changed the relay state from ");
  if (savedState)
    Serial.println("on to off");
  else
    Serial.println("off to on");
    
  delay(1000);
}

// relayModuleStatus --
// Toggle the state of the relay
//
static void relayModuleStatus(void)
{
  Serial.print("The relay is ");
  if (relay.isOn())
    Serial.println("on");
  else
    Serial.println("off");
    
  delay(1000);
}


  
