// BenchBudEE HW Checkout Program
//
// BenchBudEePins --
//  This header defines the Arduion pins usage for the BenchBudEE 
//

#ifndef BENCH_BUDEE_PINS_H
#define BENCH_BUDEE_PINS_H

// --++ Relay Module Pins ++--
// Relay Digitla channels --
const int RELAY_CONTROL_PIN  = 6;

// --++ Fan Module Pins ++--
// Fan Analog channels --
//
const int  FAN_CURRENT_MEAS_PIN   = 2;
const int  FAN_TACH_MEAS_PIN      = 3;

// Fan Digital channels --
//
const int  FAN_DAC_SELECT_PIN  =  7;
const int  FAN_LDAC_PIN        =  3;
const int  FAN_MODE_PIN        =  0;
const int  FAN_PWM_PIN         =  10;
const int  FAN_SHDN_PIN        =  2;


#endif // BENCH_BUDEE_PINS_H
