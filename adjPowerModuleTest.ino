// BenchBudEE HW Checkout Program
//
// adjPowerModuleTest.ino --
//  Power Module Test suit
//

#include "BenchBudEePins.h"
#include "adjPowerModuleTest.h"
#include "menuUtility.h"

// Declare prototypes for tests here --
//
static void adjPowerModuleVPlusMonitor(void);


// adjPowerModuleTestMain --
//  This is the main entry point for the Power Module Test menu
//
void adjPowerModuleTestMain(void)
{
  // Replace the menu entries in the array with the real tests.
  // See menuUtility.h for details.
  const menuLine adjPowerMenu[] = {
  {1, "V+ Monitor Test", adjPowerModuleVPlusMonitor},
  };

  // No need to change anything else in this function --
  menuLoop("Adjustable Power Module Test Menu", adjPowerMenu, MENU_SIZE(adjPowerMenu));
}

// Define the test implementations below --
//  These are dummy examples and should be replaced.
//
static void adjPowerModuleVPlusMonitor(void)
{
  int adcRaw;
  int adcVoltage;
  int voltageAdjOutput;

  pinMode(V_POS_ADJ_MON_PIN, INPUT);
  Serial.println("Monitoring Positive Voltage. Enter any key to stop.");
  
  do
  {
    // Get the raw ADC reading --
    //
    adcRaw  = analogRead(V_POS_ADJ_MON_PIN);
    
    // Convert to voltage at the Arduino pin --
    //  Use the map function to convert the raw ADC read to the millivolts
    // present at the analog input pin.  This assumes that the analoge reference is +5 V.
    //
    adcVoltage = map(adcRaw, 0, 1023, 0, 5000);
    
    // Calculate the voltage at the positive V+_ADJ output
    //
    voltageAdjOutput = adcVoltage * 4;
    
    Serial.print("ADC Input = ");
    Serial.print(adcRaw);
    Serial.print(", ADC Voltage = ");
    Serial.print(adcVoltage);
    Serial.print("mV, V+_ADJ Output = ");
    Serial.print(voltageAdjOutput);
    Serial.println("mV");
    
    delay(500); 
 
  } while (Serial.available() == 0);
  
  // Get input and discard it --
  Serial.read();
}
