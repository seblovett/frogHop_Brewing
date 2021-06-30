/*
 * max31865.c
 *
 *  Created on: 28 Jun 2021
 *      Author: seblo
 */

#include "max31865.h"
#include <stdio.h>
#include "main.h"
#include <math.h>

#define RREF 430  // reference resistor in Ohms
#define RTD_NOM 100

void spi_write(uint8_t reg, uint8_t val)
{
  uint8_t tx[2] = {0};
  uint8_t rx[2] = {0};
  tx[0] = reg | WRITE_FLAG; 
  tx[1] = val;
  HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, GPIO_PIN_RESET);
  HAL_SPI_TransmitReceive(&hspi2, tx, rx, 2, 100);
  HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, GPIO_PIN_SET);
}

uint8_t spi_read8(uint8_t reg)
{
  uint8_t tx[2] = {0};
  uint8_t rx[2] = {0};
  tx[0] = reg; 
  HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, GPIO_PIN_RESET);
  HAL_SPI_TransmitReceive(&hspi2, tx, rx, 2, 100);
  HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, GPIO_PIN_SET);
  return rx[1];
}

uint16_t spi_read16(uint8_t reg)
{
  uint8_t tx[3] = {0};
  uint8_t rx[3] = {0};
  tx[0] = reg; 
  HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, GPIO_PIN_RESET);
  HAL_SPI_TransmitReceive(&hspi2, tx, rx, 3, 100);
  HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, GPIO_PIN_SET);
  uint16_t val = (rx[1] << 8) | rx[2];
  return val;
}

void max31865_init()
{
  uint8_t val;
  val = spi_read8(MAX31865_REG_CONFIG);
  // printf("Config = 0x%02x\r\n", val);
  val = MAX31865_CONFIG_VBIAS | MAX31865_CONFIG_AUTO |
            MAX31865_CONFIG_3WIRE | MAX31865_CONFIG_50HZ;
  // printf("write Config = 0x%02x\r\n", val);
  spi_write(MAX31865_REG_CONFIG, val);
  
  val = spi_read8(MAX31865_REG_CONFIG);
  // printf("Config = 0x%02x\r\n", val);

}

double get_resistance()
{
    uint16_t rtdval = spi_read16(MAX31865_REG_RTD_MSB);
    
    if ((rtdval & 0x01)) // lowest bit is a fault flag
    {
        uint8_t fault = spi_read8(MAX31865_REG_FAULT_STATUS);
        printf("Error 0x%02x detected\r\n", fault);
    }
    printf("raw val = 0x%04x\r\n", rtdval);
    rtdval >>= 1;  // remove the Fault bit
    double R = (double)rtdval * (double)RREF / 32768.0;
    // rtdval /= 32768;
    // rtdval *= RREF;
    return R;
}
/**
 * Apply the Callendar-Van Dusen equation to convert the RTD resistance
 * to temperature:
 *
 *   \f[
 *   t=\frac{-A\pm \sqrt{A^2-4B\left(1-\frac{R_t}{R_0}\right)}}{2B}
 *   \f],
 *
 * where
 *
 * \f$A\f$ and \f$B\f$ are the RTD coefficients, \f$R_t\f$ is the current
 * resistance of the RTD, and \f$R_0\f$ is the resistance of the RTD at 0
 * degrees Celcius.
 *
 * For more information on measuring with an RTD, see:
 * <http://newton.ex.ac.uk/teaching/CDHW/Sensors/an046.pdf>.
 *
 * @param [in] resistance The measured RTD resistance.
 * @return Temperature in degrees Celcius.
 */
uint8_t max31865_get_temperature() 
{
  static const double a2   = 2.0 * RTD_B;
  static const double b_sq = RTD_A * RTD_A;

  const double rtd_resistance = RTD_RESISTANCE_PT100;

  double c = 1.0 - get_resistance() / rtd_resistance;
  double D = b_sq - 2.0 * a2 * c;
  double temperature_deg_C = ( -RTD_A + sqrt( D ) ) / a2;

  return( (uint8_t)temperature_deg_C );
}

/**
 * Read all settings and measurements from the MAX31865 and store them
 * internally in the class.
 *
 * @return Fault status byte
 */
uint8_t read_all()
{
  // uint16_t combined_bytes;

  // /* Start the read operation. */
  // digitalWrite( this->cs_pin, LOW );
  // /* Tell the MAX31865 that we want to read, starting at register 0. */
  // SPI.transfer( 0x00 );

  // /* Read the MAX31865 registers in the following order:
  //      Configuration
  //      RTD
  //      High Fault Threshold
  //      Low Fault Threshold
  //      Fault Status */

  // this->measured_configuration = SPI.transfer( 0x00 );

  // combined_bytes  = SPI.transfer( 0x00 ) << 8;
  // combined_bytes |= SPI.transfer( 0x00 );
  // this->measured_resistance = combined_bytes >> 1;

  // combined_bytes  = SPI.transfer( 0x00 ) << 8;
  // combined_bytes |= SPI.transfer( 0x00 );
  // this->measured_high_threshold = combined_bytes ;

  // combined_bytes  = SPI.transfer( 0x00 ) << 8;
  // combined_bytes |= SPI.transfer( 0x00 );
  // this->measured_low_threshold = combined_bytes ;

  // this->measured_status = SPI.transfer( 0x00 );

  // digitalWrite( this->cs_pin, HIGH );

  // /* Reset the configuration if the measured resistance is
  //    zero or a fault occurred. */
  // if(   this->measured_resistance == 0 || this->measured_status != 0  )
  //   reconfigure( true );

  // return( status() );
  return 0;
}

/**
 * Read fault status
 * internally in the class.
 *
 * @return Fault status byte
 */
uint8_t fault_status()
{
  // uint8_t fault_status ;

  // /* Start the read operation. */
  // digitalWrite( this->cs_pin, LOW );
  // /* Tell the MAX31865 that we want to read, starting at register 7. */
  // SPI.transfer( 0x07 );
  // fault_status = this->measured_status = SPI.transfer( 0x00 );
  // digitalWrite( this->cs_pin, HIGH );
  // return( fault_status );
  return 0;
}

/**
 * Read configuration register
 * internally in the class.
 *
 * @return config register byte
 */
uint8_t config_register()
{
  // uint8_t config_register ;

  // /* Start the read operation. */
  // digitalWrite( this->cs_pin, LOW );
  // /* Tell the MAX31865 that we want to read, starting at register 0. */
  // SPI.transfer( 0x00 );
  // config_register = this->measured_status = SPI.transfer( 0x00 );
  // digitalWrite( this->cs_pin, HIGH );
  // return( config_register );
  return 0;
}
