// BenchBudEE HW Checkout Program
//
// menuUtility.h --
//  Public interface for the Menu Utility
//
// A menu is created by defining an array of menuLine structs.
// For example:
//   const menuLine myMenu[] = {
//  {1, "My menu text one", myFunctionOne},
//  {2, "My menu text two", myFunctionTwo},
//  {3, "My menu text three", myFunctionThree},
//  };
// 
// The array is passed to the menuLoop() function along with a menu header and the menu array size.
// For example:
//   menuLoop("Here Is My Menu", myMenu, MENU_SIZE(myMenu));
//
// The menuLoop() funciton will display the menu, call the appropriate function base on user selection,
// print an error meesage upon invalid entries, and exit when the user selects "e" or "E".
//
// For example, the code above produces the following output to the serial monitor:
// 
// --++ Here Is My Menu ++--
// 1. My menu text one
// 2. My menu text two
// 3. My menu text three
// Please select or E to exit
//
// If the user selects "1" then myFunctionOne is invoked by the menuLoop.  When the user is done
// and select "e" or "E" the menuLoop() function exits.
//

#ifndef MENU_UTILITY_H
#define MENU_UTILITY_H

#include "Arduino.h"

#define MENU_SIZE(aMenu) (sizeof(aMenu)/sizeof(menuLine))   // Calculate the numebr of menu entries

typedef struct menuLine {
  int     lineId;                // Defines the user selection to invoke this menu item
  String  lineText;              // Defines the test displayed for the menu item
  void    (*menuFunction)(void); // Define the function called when the user selected the menu item
} menuLine;

// menuLoop --
//  Displays a formatted menu consisint of the header string followed by the menu itemsdefined in the
//  aMenu array of menuLine structures. Handles user selection and invokes the associated 
//  function for the menu item.  The function exits when the user selects "e" or "E".
//  
//  Cautions: This function does not verify that each entry
//            in the aMenu array has a unique lineId.
//
void 
menuLoop(const String    header,
         const menuLine  aMenu[],
         int             size);
   
#endif //MENU_UTILITY_H
