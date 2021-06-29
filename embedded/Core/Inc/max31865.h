
#ifndef _MAX31865_H
#define _MAX31865_H

#include <stdint.h>
#include "stm32f7xx_hal.h"

#define WRITE_FLAG 0x80

#define MAX31865_REG_CONFIG           0x00
#define MAX31865_CONFIG_VBIAS         (1 << 7)
#define MAX31865_CONFIG_AUTO          (1 << 6)
#define MAX31865_CONFIG_1SHOT         (1 << 5)
#define MAX31865_CONFIG_3WIRE         (1 << 4)
#define MAX31865_CONFIG_FAULT_DETECTION_NONE      ( 0x00 << 2 )
#define MAX31865_CONFIG_FAULT_DETECTION_AUTO      ( 0x01 << 2 )
#define MAX31865_CONFIG_FAULT_DETECTION_MANUAL_1  ( 0x02 << 2 )
#define MAX31865_CONFIG_FAULT_DETECTION_MANUAL_2  ( 0x03 << 2 )
#define MAX31865_CONFIG_FAULT_CLEAR   (1 << 1)
#define MAX31865_CONFIG_50HZ          (1 << 0)



#define MAX31865_REG_RTD_MSB          0x01
#define MAX31865_REG_RTD_LSB          0x02
#define MAX31865_REG_HIGH_FLT_MSB     0x03
#define MAX31865_REG_HIGH_FLT_LSB     0x04
#define MAX31865_REG_LOW_FLT_MSB      0x05
#define MAX31865_REG_LOW_FLT_LSB      0x06
#define MAX31865_REG_FAULT_STATUS       0x07
#define MAX31865_FAULT_HIGH_THRESHOLD  ( 1 << 7 )
#define MAX31865_FAULT_LOW_THRESHOLD   ( 1 << 6 )
#define MAX31865_FAULT_REFIN           ( 1 << 5 )
#define MAX31865_FAULT_REFIN_FORCE     ( 1 << 4 )
#define MAX31865_FAULT_RTDIN_FORCE     ( 1 << 3 )
#define MAX31865_FAULT_VOLTAGE         ( 1 << 2 )




/* RTD data, RTD current, and measurement reference
   voltage. The ITS-90 standard is used; other RTDs
   may have coefficients defined by the DIN 43760 or
   the U.S. Industrial (American) standard. */
#define RTD_A_ITS90         3.9080e-3
#define RTD_A_USINDUSTRIAL  3.9692e-3
#define RTD_A_DIN43760      3.9848e-3
#define RTD_B_ITS90         -5.870e-7
#define RTD_B_USINDUSTRIAL  -5.8495e-7
#define RTD_B_DIN43760      -5.8019e-7
/* RTD coefficient C is required only for temperatures
   below 0 deg. C.  The selected RTD coefficient set
   is specified below. */
#define SELECT_RTD_HELPER(x) x
#define SELECT_RTD(x) SELECT_RTD_HELPER(x)
#define RTD_A         SELECT_RTD(RTD_A_ITS90)
#define RTD_B         SELECT_RTD(RTD_B_ITS90)
/*
 * The reference resistor on the hardware; see the MAX31865 datasheet
 * for details.  The values 400 and 4000 Ohm are recommended values for
 * the PT100 and PT1000.
 */
#define RTD_RREF_PT100     400 /* Ohm */

/*
 * The RTD resistance at 0 degrees Celcius.  For the PT100, this is 100 Ohm;
 * for the PT1000, it is 1000 Ohm.
 */
#define RTD_RESISTANCE_PT100   100 /* Ohm */

#define RTD_ADC_RESOLUTION  ( 1u << 15 ) /* 15 bits */

void max31865_init();

uint8_t max31865_get_temperature();

#endif /* _MAX31865_H */
