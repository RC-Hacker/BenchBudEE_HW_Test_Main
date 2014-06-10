// BenchBudEE HW Checkout Program
//
// Mcp48xx.h --
//  Driver for the Microchip MCP48xx series DAC.  This driver is compatible
//  with the 12-bit MCP4821, 10-bit MCP4811, and 8-bit MCP4801.  To use this
//  driver a 12-bit DAC settins is provided for all three devices.  However,
//  the LSb's of the control word are ignored for the MCP4811 and MCP4821.
//  Precision can be limited specifically to 8 or 10 bits.  When limited 
//  the control value or millivolte value provied are rounded to the nearest
//  sigificant value for the selected precision.
//  
//
//

#ifndef MCP48XX_H
#define MCP48XX_H

#include <Arduino.h>

const  int  MCP48XX_DAC_RAW_MAX            = 0xFFF;
const  int  MCP48XX_DAC_1X_MILLIVOLT_MAX   = 2048;
const  int  MCP48XX_DAC_2X_MILLIVOLT_MAX   = 4096;

class Mcp48xx
{
  
   public: // Class scope typedefs --
  typedef enum {
    DAC_OK,								            // No error
    DAC_OVER_RANGE,		            // Provided control value is out of range of the DAC
    DAC_LDAC_NOT_CONNECTED,     // LDAC pin not connected. DAC preload & commit not supported.
    DAC_DAC_ALREADY_COMMITTED,  // DAC control was already committed to output
    DAC_ALREDY_OFF,             // DAC output was already off
    DAC_ALREADY_ON              // DAC output was already on
  } DacStatus;

  typedef enum {
   GAIN_MODE_ONE_X,		// Configures DAC for 0 - 2.038 Volts output
   GAIN_MODE_TWO_X		// Configures DAC for 0 - 4.096 volts output
  } GainMode;
  
  typedef enum {
  		PRECISION_8,  			//  8 bits of percision for MCP4801
  		PRECISION_10,				// 10 bits of precision for MCP4811
  		PRECISION_12,				// 12 bits of precision for MCP4821
  		PRECISION_NA				// Default is NA or undefined. Works for all devices but does not round control values
  	} Precision;
  
   public: // Functions --
     // Creators & destructors --
     //
     explicit Mcp48xx(int        dacSelectPin,	 // Arduino pin connected to the Chip Select. Must be connected.
                      GainMode   gainMode,				 // Gain select 1X or 2X
                      int        ldacPin,      // Arduion pin connected to the LDAC pin. Use -1 if not conected.
                      Precision  precision,	   // Defines the number of sigificant bits.
                      int        shdnPin);     // Arduino pin connected to the SHDN pin. Use -1 if not connnected.
     ~Mcp48xx(void);
     
     // Behaviors --
     //
     uint16_t   rawGet(void)                           const; // Returns the DAC control value.
                                                              //    Note if perecision was limited then the rounded value is returned.
     MDacStatus rawSet(uint16_t         controlValue);	       // Sets the DAC to the control value provided.
                                                              //    Note the setting is rounded if precision is limited.
     GainMode   gainModeGet(void)                      const; // Returns the DAC gain mode.
     void       gainModeSet(GainMode    gainMode);										// Sets the DAC gain mode. WARNING, new Gain Mode does not take effect
                                                              //    until DAC control value or voltage is set.
     bool       isOn(void)                             const; // Indicates if the DAC output is on.
     bool       isOff(void)                            const; // Indicates if the DAC output is off.
     DacStatus  ldacPreload(void);                            // Allows DAC control value to be set but not committed. WARNING requires LDAC Pin.
     DacStatus  ldacCommit(void);                             // Commits last DAC output setting to the DAC output. WARNING  requires LDAC Pin.
     DacStatus  off(void);                                    // Turns off the DAC output
     DacStatus  on(void);                                     // Turns on the DAC output. WARNING the output value will be as last set.
     uint16_t	   millivoltsGet(void)                           // Returns the DAC output setting in millivolts.
                                                              //    Note if precision was set then the rounded value is returned.   
     DacStatus  millivoltsSet(uint16_t  millivolts)    const; // Sets the DAC output to the millivolts provided.
                                                              //    Note the settng is rounded if precision is limited. 


   private:  // Data --
     GainMode   i_gainMode;
     int        i_dacSelectPin;
     bool       i_isOn;
     int        i_ldacPin;
     int        i_shdnPin;
     uint16_t   i_dacControlValue;
     uint16_t   i_dacMillivolts;
     Precision  i_precision;
     
   private:  // Private methods --
     bool    isLdacPinConnected(void)   const;
     bool    isShdnPinConnected(void)   const;
 
     // Declare but do not define the copy and assignment methods to prevent class copying --
     //
     // Since the DAC is a physical device the class representing
     // it should not be copied or the state of either copy can become
     // unsynchronized with the physical state of the dac.
     //
     Mcp48xx(Mcp48xx const&  Mcp48xx);
     Mcp48xx&  operator=(Mcp48xx const& rhs);
};

// Inline functions
//

// DAC Get --
//  Return the current DAC control word setting.
//
inline uint16_t
Mcp48xx::rawGet(void) const
{
  return(i_dacControlValue);
}

// Gain Mode Get --
//  Return the current gain mode setting.
//
inline GainMode
Mcp48xx::gainModeGet(void) const
{
  return(i_gainMode);
}

// Gain Mode Set --
//  Set the gain mode as requested.
//
inline void
Mcp48xx::gainModeSet(GainMode   gainMode)
{
  i_gainMode  = gainMode;
}

// Is LDAC Pin Connected --
//   Returns ture if LDAC Pin is connected
//
inline bool
Mcp48xx::isLdacPinConnected(void)
{
  return(i_ldacPin >= 0);
}

// Is SHDN Pin Connected --
//   Returns true if SHDN Pin is connected
//
inline bool
Mcp48xx::isShdnPinConnected(void)
{
  return(i_shdnPin >= 0);
}

// DAC millivolte Get --
//  Return the current DAC output setting in millivoltes.
//
inline uint16_t
Mcp48xx::millivoltsGet(void) const
{
  return(i_dacMillivolts);
}

#endif //MCP48XX_H