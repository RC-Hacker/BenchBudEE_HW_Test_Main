// BenchBudEE HW Checkout Program
//
// Mcp48xx.h --
//  Driver for the Microchip MCP48xx series DAC.  This driver is compatible
//  with the 12-bit MCP4821, 10-bit MCP4811, and 8-bit MCP4801.  To use this
//  driver a 12-bit DAC settins is provided for all three devices.  However,
//  the LSb's of the control word are ignored for the MCP4811 and MCP4801.
//  
//  Cautions: This class assumes that int is 16 bits or larger.
//

#ifndef MCP48XX_H
#define MCP48XX_H

#include <Arduino.h>

const  int  MCP48XX_DAC_MAX  = 0xFFF;

class Mcp48xx
{
  
   public: // Class scope typedefs --
  typedef enum {
    DAC_OK,
    DAC_OVER_RANGE
  } DacStatus;

  typedef enum {
   GAIN_MODE_ONE_X,
   GAIN_MODE_TWO_X
  } GainMode;
  
   public: // Functions --
     // Creators & destructors --
     //
     explicit Mcp48xx(int                dacSelectPin,  // Arduino pin connected to the Chip Select
                      Mcp48xx::GainMode  gainMode,      // Gain select 1X or 2X
                      int                ldacPin,       // Arduion pin connected to the LDAC pin
                      int                shdnPin);      // Arduino pin connected to the SHDN pin
     ~Mcp48xx(void);
     
     // Behaviors --
     //
     unsigned int       get(void)                            const;
     Mcp48xx::DacStatus set(unsigned int     controlValue);
     Mcp48xx::GainMode  gainModeGet(void)                    const;
     void               gainModeSet(GainMode gainMode);     
     bool               isOn(void)                           const;
     bool               isOff(void)                          const;
     void               off(void);
     void               on(void);


   private:  // Data --
     Mcp48xx::GainMode  i_gainMode;
     int                i_dacSelectPin;
     bool               i_isOn;
     int                i_ldacPin;
     int                i_shdnPin;
     unsigned int       i_dacControlValue;
     
 
     // Declare but do not define the copy and assignment methods to prevent class copying --
     //
     // Since the DAC is a physical device the class representing
     // it should not be copied or the state of either copy can become
     // unsynchronized with the physical state of the dac.
     //
     Mcp48xx(Mcp48xx const&  Mcp48xx);
     Mcp48xx&  operator=(Mcp48xx const& rhs);
};

#endif //MCP48XX_H
