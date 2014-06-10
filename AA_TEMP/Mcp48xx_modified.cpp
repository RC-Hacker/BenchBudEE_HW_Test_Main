// BenchBudEE HW Checkout Program
//
// Mcp48xx.cpp --
//  Library for MCP48xx series driver.
//

#include "Mcp48xx.h"
#include <SPI.h>


// Defines and Macros for MCP48xx command --
//  The MCP48XX accepts one command in the form:
//
// BIT    15  14  13    12     11 - 0
//      +---+---+----+------+----------+
//      | 0 | x | GA | SHDN | D11 - D0 |
//      +---+---+----+------+----------+
//
// Where:  Bit 15 is the header (always set to 0)
//         Bit 14 is a don't care
//         Bit 13 is Gain Select  1 = 1x (Vout = Vref * (D/4096))
//                                0 = 2x (Vout = Vref * (D/4096))
//         Bit 12 is Shutdown  1 = Active mode, Vout is on
//                             0 = Shutdown mode, Vout is off
//         Bits 11 to 0 is the DAC input data.  The lower 2 bits are ignored
//                                              for the MCP4811 and the lower 4
//                                              bits are ignored for the MCP4801.
//
//
static const int  HEADER              = 0;
static const int  SHUTDOWN            = 0;
static const int  ACTIVE              = 1;
static const int  GAIN_1X             = 1;
static const int  GAIN_2X             = 0;
static const int  HEADER_POSITION     = 15;
static const int  HEADER_MASK         = 0x8000;
static const int  GAIN_POSITION       = 13;
static const int  GAIN_MASK           = 0x2000;
static const int  SHUTDOWN_POSITION   = 12;
static const int  SHUTDOWN_MASK       = 0x1000;
static const int  DAC_INPUT_POSITION  = 0;
static const int  DAC_INPUT_MASK      = 0x0FFF;
#define MCP48XX_COMMAND_FIELD_SET(value, position, mask)  (((value) << (position)) & (mask))
#define MCP48XX_COMMAND_HEADER_FIELD_SET                (((HEADER) << (HEADER_POSITION))    & (HEADER_MASK))
#define MCP48XX_COMMAND_GAIN_FIELD_SET(gain)            (((gain)   << (GAIN_POSITION))      & (GAIN_MASK))
#define MCP48XX_COMMAND_SHUTDOWN_FIELD_SET(shdn)        (((shdn)   << (SHUTDOWN_POSITION))  & (SHUTDOWN_MASK))
#define MCP48XX_COMMAND_DAC_INPUT_FIELD_SET(input)      (((input)  << (DAC_INPUT_POSITION)) & (DAC_INPUT_MASK))



// Mcp48xx constructor --
//
Mcp48xx::Mcp48xx(int       dacSelectPin,  
                 GainMode  gainMode,
                 int       ldacPin,
                 Precision precision,
                 int       shdnPin)
: i_dacSelectPin(dacSelectPin),
  i_gainMode(gainMode),
  i_ldacPin(ldacPin),
  i_precision(precision),
  i_shdnPin(shdnPin),
  i_dacControlValue(0),
  i_dacMillivolts(0),
  i_isOn(0)
{

  // Initialize pins and initial settings --
  //
  if (isShdnPinConnected())
  {
      pinMode(i_shdnPin, OUTPUT);
  }
  
  if (isLdacPinConneted())
  {
      pinMode(i_ldacPin, OUTPUT);
  }

  pinMode(i_dacSelectPin, OUTPUT);
  digitalWrite(i_dacSelectPin, HIGH);
  
  // Initilize the SPI interface --
  //
  SPI.setDataMode(SPI_MODE0);
  SPI.setBitOrder(MSBFIRST); 
  SPI.begin();
  
  // Initialize the DAC to a resonable state --
  //
  off();
  set(0);
  ldacCommit();
}

// Mcp48xx destructor --
//
Mcp48xx::~Mcp48xx(void)
{
  // Leave the DAC in a default state --
  //
   off();
   set(0);
   ldacCommit();
   
   SPI.end();
}

// Dac Set --
//  Set the DAC output to the value provided.
//
Mcp48xx::DacStatus
Mcp48xx::rawSet(unsigned int controlValue)
{
  DacStatus  status   = DAC_OK;
  
  // Verify that the provided value is within range --
  //  The max resolution for the MCP48XX series is 12 bits or 0x0FFF.
  //
  if (controlValue > MCP48XX_DAC_MAX)
  {
    status  = DAC_OVER_RANGE;
  }
  else
  {
  
  // TODO: Round per precision
  // TODO: save the contol value
  //
    unsigned int command =  MCP48XX_COMMAND_HEADER_FIELD_SET
                          | MCP48XX_COMMAND_GAIN_FIELD_SET((i_gainMode == GAIN_MODE_ONE_X) ? GAIN_1X : GAIN_2X)
                          | MCP48XX_COMMAND_SHUTDOWN_FIELD_SET(i_isOn ? ACTIVE : SHUTDOWN)
                          | MCP48XX_COMMAND_DAC_INPUT_FIELD_SET(controlValue);
 
    // Start of critical section --
    {
      //  Mask interrupts
      noInterrupts();
    
      digitalWrite(i_dacSelectPin, LOW);  // DAC select is active-low
      SPI.transfer(command >> 8);         // Send the command MSB
      SPI.transfer(command);              // Send the command LSB
      digitalWrite(i_dacSelectPin, HIGH); // Commit the change
      // TODO: Add LDAC commit
      
      interrupts();  // End of critical section
    }  
  }    
     
  return(status);
}

// DAC output off --
//  Turn off the DAC output.
//
void
Mcp48xx::off(void)
{
  i_isOn  = false;
  
  if (i_shdnPin >= 0)
  {
      // Assert the active-low DAC shutdown pin --
      //
      digitalWrite(i_shdnPin, LOW);
  }
  else // If the LDAC control is not connected then must send command to DAC to shutdown the output
  {
      rawSet(i_controlValue);
  }
}

// Dac output on --
//  Turn on the DAC output.
//
void
Mcp48xx::on(void)
{
  // De-assert the active-low DAC shutdown pin --
  //
  digitalWrite(i_shdnPin, HIGH);
  i_isOn  = true;
}