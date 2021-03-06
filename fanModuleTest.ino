// BenchBudEE HW Checkout Program
//
// fanModuleTest.ino --
// Fan Module Test suit
//

#include "BenchBudEePins.h"
#include "fanModuleTest.h"
#include "menuUtility.h"

// Declare prototypes for tests here --
//
static void fanModuleDacStairstep(void);
static void fanModulePwmLevels(void);
static void fanModuleQ3Test(void);
static void fanModuleFanPwmTest(void);

// fanModuleTestMain --
// This is the main entry point for the Fan Module Test menu
//
void fanModuleTestMain(void)
{
  // Replace the menu entries in the array with the real tests.
  // See menuUtility.h for details.
  const menuLine fanMenu[] = {
  {1, "Start DAC Stairstep Test", fanModuleDacStairstep},
  {2, "PWM Levels Test", fanModulePwmLevels},
  {3, "Q3 Test", fanModuleQ3Test},
  {4, "FAN PWM Test", fanModuleFanPwmTest},
  };

  // No need to change anything else in this function --
  menuLoop("Fan Module Test Menu", fanMenu, MENU_SIZE(fanMenu));
}

static void fanModuleDacStairstep(void)
{
  Mcp48xx dac(FAN_DAC_SELECT_PIN,
               Mcp48xx::GAIN_MODE_TWO_X,
               FAN_LDAC_PIN,
               FAN_SHDN_PIN);
  int dacControl = 0;
  
  // TODO: Replace this after FAN class is created --
  // Configure the FAN module for constant current.
  //pinMode(FAN_MODE_PIN, OUTPUT);
  //digitalWrite(FAN_MODE_PIN, LOW);
  // Set FAN PWM low initally so PWM MOSFET is off.
  pinMode(FAN_PWM_PIN, OUTPUT);
  digitalWrite(FAN_PWM_PIN, LOW);
  // End TODO: --
  
  Serial.println("DAC Stairstep Test in progress. Enter any key to stop.");
  
  dac.on();

  do
  {
    if (dacControl > MCP48XX_DAC_MAX)
      dacControl = 0;
    
    if (dac.set(dacControl) != Mcp48xx::DAC_OK)
    {
      Serial.println("Error setting DAC control value. Exiting test");
      break;
    }
    
    dacControl += 64;
    delay (100);
    
  } while (Serial.available() == 0);
  
  // Get input and discard it --
  Serial.read();
  
  dac.off();
  
}

// TODO: Rework this test after FAN class is created --
//
static void fanModulePwmLevels(void)
{
  Mcp48xx dac(FAN_DAC_SELECT_PIN,
               Mcp48xx::GAIN_MODE_TWO_X,
               FAN_LDAC_PIN,
               FAN_SHDN_PIN);
  
  // Configure the FAN module for PWM Mode.
  //pinMode(FAN_MODE_PIN, OUTPUT);
  //digitalWrite(FAN_MODE_PIN, HIGH);
  // Set FAN PWM low initally so PWM MOSFET is off.
  pinMode(FAN_PWM_PIN, OUTPUT);
  digitalWrite(FAN_PWM_PIN, LOW);
  
  // Setup the DAC ouput --
  //
  dac.on();
  if (dac.set(64) != Mcp48xx::DAC_OK)
  {
    Serial.println("Error setting DAC control value. Exiting test");
  }
  
  else
  {
    int pwmLevel = 0;
    int pwmValue = 0;
    
    Serial.println("PWM 3 Level Test in progress. Enter any key to stop.");

    do
    {
      pwmValue = map(pwmLevel, 0, 4, 0, 255); // Map values 0-4 to 0-255
      analogWrite(FAN_PWM_PIN, pwmValue);
      
      if (++pwmLevel > 4)
        pwmLevel = 0;
      
      Serial.print("PWM Value = ");
      Serial.println(pwmValue);
      Serial.println("");
      
      delay(2000);
    } while (Serial.available() == 0);
    
    // Get input and discard it --
    Serial.read();
  }
  
  // Turn off the PWM MOSFET and DAC output before exiting --
  //
  digitalWrite(FAN_PWM_PIN, LOW);
  dac.off();
}

static void fanModuleQ3Test(void)
{
  Mcp48xx  dac(FAN_DAC_SELECT_PIN,
               Mcp48xx::GAIN_MODE_ONE_X,
               FAN_LDAC_PIN,
               FAN_SHDN_PIN);
  uint8_t  fanMode  = LOW;
  
  // Set FAN PWM low to disable PWM MOSFET --
  //
  pinMode(FAN_PWM_PIN, OUTPUT);
  digitalWrite(FAN_PWM_PIN, fanMode);
  
  // Configure the Fan Mode pin --
  //
  pinMode(FAN_MODE_PIN, OUTPUT);
  digitalWrite(FAN_MODE_PIN, LOW);
  
  // Setup the DAC ouput --
  //  Set the DAC to output to 80 mV
  dac.on();
  if (dac.set(160) != Mcp48xx::DAC_OK)
  {
    Serial.println("Error setting DAC control value. Exiting test");
  }
  
  else
  {
    Serial.println("Q3 Test in progress. Enter any key to stop.");
    
    do
    {
      // Toggle fan mode and delay --
      fanMode  = ((fanMode == HIGH) ? LOW : HIGH);
      digitalWrite(FAN_MODE_PIN, fanMode);
      delay(5000);

    } while (Serial.available() == 0);
    
    // Get input and discard it --
    Serial.read();
  }
  
  // Turn off the PWM MOSFET and DAC output before exiting --
  //
  dac.off();
}

static void fanModuleFanPwmTest(void)
{
  Mcp48xx  dac(FAN_DAC_SELECT_PIN,
               Mcp48xx::GAIN_MODE_ONE_X,
               FAN_LDAC_PIN,
               FAN_SHDN_PIN);
  
  // Set FAN PWM low to disable PWM MOSFET --
  //
  pinMode(FAN_PWM_PIN, OUTPUT);
  digitalWrite(FAN_PWM_PIN, LOW);
  
  // Configure the Fan Mode pin --
  //
  pinMode(FAN_MODE_PIN, OUTPUT);
  digitalWrite(FAN_MODE_PIN, LOW);
  
  // Setup the DAC ouput --
  //  Set the DAC to output to 80 mV
  dac.on();
  if (dac.set(160) != Mcp48xx::DAC_OK)
  {
    Serial.println("Error setting DAC control value. Exiting test");
  } 
  
  else
  {
    int pwmLevel = 4;
    int pwmValue = 0;
    
    Serial.println("PWM 3 Level Test in progress. Enter any key to stop.");
    digitalWrite(FAN_MODE_PIN, HIGH);
    do
    {
      pwmValue = map(pwmLevel, 0, 4, 0, 255); // Map values 0-3 to 0-255
      analogWrite(FAN_PWM_PIN, pwmValue);
      
      Serial.print("PWM Value = ");
      Serial.println(pwmValue);
      Serial.println("");
 
      delay(5000);     

      // At end of PWM levels, turn off PWM fan mode for 5 seconds --
      //
      if (--pwmLevel < 0)
      {
        pwmLevel = 4;
        digitalWrite(FAN_MODE_PIN, LOW);
        Serial.println("Fan PWM Mode off");
        delay(5000);
        digitalWrite(FAN_MODE_PIN, HIGH);
        Serial.println("Fan PWM Mode on");
      }
    } while (Serial.available() == 0);
    
    // Get input and discard it --
    Serial.read();
  }
  
  // Turn off the PWM MOSFET and DAC output before exiting --
  //
  digitalWrite(FAN_PWM_PIN, LOW);
  dac.off();
}
