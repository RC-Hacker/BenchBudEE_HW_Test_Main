// BenchBudEE HW Checkout Program
//
// Relay.cpp --
//  Library for controlling the BenchBudEE relay.
//

#include "Relay.h"

// Relay constructor --
//
Relay::Relay(int pin)
: i_pin(pin),
  i_isOn(false)
{
  pinMode(i_pin, OUTPUT);
  // Initialize the relay to the off state
  digitalWrite(i_pin, LOW);
}

// Relay destructor --
//
Relay::~Relay(void)
{
  // Set the pinMode back to input
  // to turn off the Arduino driver
  pinMode(i_pin, INPUT);
}

// Relay isOff --
//  Returns ture if the relay is de-enervized.  Returns false otherwise.
//
bool
Relay::isOff(void) const
{
  return(!i_isOn);
}

// Relay isOn --
//  Returns true if the relay is energized. Returns false otherwise.
//
bool
Relay::isOn(void) const
{
  return(i_isOn);
}

// Relay off --
//  De-energizes the relay.
//
void
Relay::off()
{
  digitalWrite(i_pin, LOW);
  i_isOn  = false;
}

// Relay on --
//  Energizes the relay.
//
void
Relay::on()
{
  digitalWrite(i_pin, HIGH);
  i_isOn  = true;
}

// Relay toggle --
//  Toggles the relays on/off state
//
void
Relay::toggle(void)
{
  i_isOn ? off() : on();
}
