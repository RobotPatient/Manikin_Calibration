#ifndef SENSORHUB_DEFINITIONS_HPP
#define SENSORHUB_DEFINITIONS_HPP

#ifdef __SAMD21G18A__

#define ADS7138_ADDR 0x10

#define BAUDRATE 115200
#define ledHb 14
#define SEPERATION_CHAR " "
#define MAX_SAMPLE 255

// i2c system bus
#define W0_SCL 27 // PA22
#define W0_SDA 26 // PA23

#define W1_SCL 39 // PA13
#define W1_SDA 28 // PA12

#define W2_SCL 13 // PA17
#define W2_SDA 11 // PA16
#endif

// Movement Pattern
//      0
//      1
//  2       7
//      3
//  4       6
//      5
// Channel Numbers
//      5
//      4
//  7       2
//      3
//  0       1
//      6
const int positieToChannel[8] = {5, 4, 7, 3, 0, 6, 1, 2};

#endif