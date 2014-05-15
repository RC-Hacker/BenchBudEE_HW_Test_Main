// BenchBudEE HW Checkout Program
//
// Relay.h --
//  Header file for the Relay library
//

#ifndef RELAY_H
#define RELAY_H

#include "Arduino.h"

class Relay
{
   public:  // Functions --
     // Creators & destructors --
     //
     explicit Relay(int pin);  // Prevent implicit conversions
     ~Relay(void);
     
     // Behaviors --
     //
     bool  isOff(void)  const;
     bool  isOn(void)   const;
     void  off(void);
     void  on(void);
     void  toggle(void);

   private:  // Data --
     bool   i_isOn;
     int    i_pin;

     // Declare but do not define the copy and assignment methods to prevent class copying --
     //
     // Since releays are physical objects the class representing
     // them should not be copied or the state of either copy can become
     // unsynchronized with the physical state of the relay.
     //
     Relay(Relay const&  Relay);
     Relay&  operator=(Relay const& rhs);
};

#endif //RELAY_H
