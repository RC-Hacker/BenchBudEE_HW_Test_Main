// BenchBudEE HW Checkout Program
//
// menuUtility.ino --
//  This provides a framework for a menu-driven test suit.  The framework 
//  provides all menu output text formatting and implements the user selection
//  function to simplify test code develoment and provide a uniform look/feel
//  to all menus.
//

#include "menuUtility.h"

#define ARDUINO_SERIAL_MONITOR                      // Optimize code for use with the IDE built-in serial monitor 
#define MENU_INPUT_TO_INDEX(input) ((input) - '1')  // Subtract ASCII 1 to get to menu index

// -- Privite function declarations --
//
static void menuClear(void);
static void menuHeaderPrint(const String  aHeader);
static void menuPrint(const String        header,
                      const menuLine      aMenu[],
                      int                 size);
static bool menuSelectoinExecute(const menuLine aMenu[],
                                 int            size);


// -- Public function definitions --
//

// menuLoop --
//  Displays a formatted menu and handles user selection.
//
void 
menuLoop(const String    header,
         const menuLine  aMenu[],
         int             size)
{
  menuClear();
  do
  {
    menuPrint(header, aMenu, size);
  } while (menuSelectionExecute(aMenu, size) == false);
  menuClear();
}


// -- Privite function definitions --
//

// menuClear --
//  Clears the terminal screen
//
static void 
menuClear(void)
{
#ifdef ARDUINO_SERIAL_MONITOR
  // Brain-dead implementation for built-in serial monitor
  for (int i = 0; i <= 15; i++)
    Serial.println("");
    
#else //!ARDUINO_SERIAL_MONITOR
  // Better implementation for real serial moniitor e.g., Putty
  // Note this has not yet been tested
  Serial.write(27);    // ESC
  Serial.print("[2J"); // clear screen
  Serial.write(27);    // ESC
  Serial.print("[H");  // cursor to home
#endif //ARDUINO_SERIAL_MONITOR
}


// menuHeaderPrint --
//  Print the header with a pretty banner
//
static void 
menuHeaderPrint(const String aHeader)
{
  Serial.println("");
  Serial.print("--++ ");
  Serial.print(aHeader);
  Serial.println(" ++--");
}


// menuPrint --
//  Print the menu header followed by the menu items
//  identified in the menu array.
//
static void 
menuPrint(const String    header,
          const menuLine  aMenu[] ,
          int             size)
{
  menuHeaderPrint(header);
  for (int i = 0; i < size; i++)
  {
    Serial.print(aMenu[i].lineId);
    Serial.print(". ");
    Serial.println(aMenu[i].lineText);
  }  
  Serial.println("Please select or E to exit");
  Serial.println("");
}


// menuSelectionExecute --
//  Get the user input and invoke the associated
//  function.
//
static bool
menuSelectionExecute(const menuLine aMenu[],
                     int            size)
{
  bool isExit = false;
 
  // Wait for input
  while (Serial.available() == 0);
  
  // Get input and call selected test sub-menu
  int selection      = Serial.read();
  int selectionIndex = MENU_INPUT_TO_INDEX(selection);
  
  if ((selection == 'e') || (selection == 'E'))
    isExit = true;
  else if (selectionIndex < size)
    aMenu[selectionIndex].menuFunction();
  else
     Serial.println("Invalid Selection. Try again.");
     
  return(isExit);
}
