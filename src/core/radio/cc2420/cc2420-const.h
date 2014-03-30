/*
 * Spec for cc2420
 */

#ifndef SWITCH_MODE_DELAY
#define SWITCH_MODE_DELAY                  0           // second
#define SYMBOL                             0.000016    // second
#define SWITCH_MODE_DELAY_IDLE_TO_TRANS    SYMBOL*12   // symbol
#define SWITCH_MODE_DELAY_IDLE_TO_LISTEN   SYMBOL*12   // symbol
#define SWITCH_MODE_DELAY_TRANS_TO_LISTEN  SYMBOL*12   // symbol
#define SWITCH_MODE_DELAY_TRANS_TO_IDLE    SYMBOL*0    // symbol
#define SWITCH_MODE_DELAY_LISTEN_TO_TRANS  SYMBOL*12   // symbol
#define SWITCH_MODE_DELAY_LISTEN_TO_IDLE   SYMBOL*0    // symbol
#endif

#ifndef DATA_RATE
#define DATA_RATE 250000.0  // bps
#endif

#define FREQUENCY 2400.0      // MHz

#define TXPOWER_LEVEL_MAX 31.0  // level max
#define TXPOWER_LEVEL_MIN  0.0  // level min

#define TXPOWER_MAX        0.0  // dBm
#define TXPOWER_MIN      -90.0  // dBm

#define TXPOWER_CURRENT 17.4 // mA

#define RXPOWER_CURRENT 18.8 // mA

#define SUPPLY_VOLTAGE   1.8 // V

#define SLPOWER
