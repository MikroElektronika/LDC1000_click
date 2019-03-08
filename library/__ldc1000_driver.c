/*
    __ldc1000_driver.c

-----------------------------------------------------------------------------

  This file is part of mikroSDK.

  Copyright (c) 2017, MikroElektonika - http://www.mikroe.com

  All rights reserved.

----------------------------------------------------------------------------- */

#include "__ldc1000_driver.h"
#include "__ldc1000_hal.c"

/* ------------------------------------------------------------------- MACROS */



/* ---------------------------------------------------------------- VARIABLES */

#ifdef   __LDC1000_DRV_I2C__
static uint8_t _slaveAddress;
#endif

/* Register Map */
const uint8_t _LDC1000_CMD_ID                    = 0x00;
const uint8_t _LDC1000_CMD_RPMAX                 = 0x01;
const uint8_t _LDC1000_CMD_RPMIN                 = 0x02;
const uint8_t _LDC1000_CMD_SENSORFREQ            = 0x03;
const uint8_t _LDC1000_CMD_LDCCONFIG             = 0x04;
const uint8_t _LDC1000_CMD_CLKCONFIG             = 0x05;
const uint8_t _LDC1000_CMD_THRESHILSB            = 0x06;
const uint8_t _LDC1000_CMD_THRESHIMSB            = 0x07;
const uint8_t _LDC1000_CMD_THRESLOLSB            = 0x08;
const uint8_t _LDC1000_CMD_THRESLOMSB            = 0x09;
const uint8_t _LDC1000_CMD_INTCONFIG             = 0x0A;
const uint8_t _LDC1000_CMD_PWRCONFIG             = 0x0B;
const uint8_t _LDC1000_CMD_STATUS                = 0x20;
const uint8_t _LDC1000_CMD_PROXLSB               = 0x21;
const uint8_t _LDC1000_CMD_PROXMSB               = 0x22;
const uint8_t _LDC1000_CMD_FREQCTRLSB            = 0x23;
const uint8_t _LDC1000_CMD_FREQCTRMID            = 0x24;
const uint8_t _LDC1000_CMD_FREQCTRMSB            = 0x25;

/* Command to write */
// Rp_Max = 38.785K
const uint8_t _LDC1000_RPMAX_38_785K             = 0x11;
// Rp_Min = 2.39K
const uint8_t _LDC1000_RPMIN_2_39K               = 0x3B;
// Sensor Frequency - N = 217; F = 20% * Rf
const uint8_t _LDC1000_SENSORFREQ_N217_F20       = 0xD9;
// LDC Configuration - Amplitude = 2V, Response Time = 6144;
const uint8_t _LDC1000_LDCCONFIG_A2V_T6144       = 0x0F;
// Clock Configuration - External Crystal used for Frequency Counter; Enable External time base clock;
const uint8_t _LDC1000_CLKCONFIG_EC_ET_ENABLE    = 0x02;
// Power Configuration - Active Mode, Conversion is Enabled
const uint8_t _LDC1000_PWRCONFIG_ACTIVE_MODE     = 0x01;

/* Command SPI read */
const uint8_t _LDC1000_CMD_SPI_READ              = 0x80;


/* -------------------------------------------- PRIVATE FUNCTION DECLARATIONS */




/* --------------------------------------------- PRIVATE FUNCTION DEFINITIONS */



/* --------------------------------------------------------- PUBLIC FUNCTIONS */

#ifdef   __LDC1000_DRV_SPI__

void ldc1000_spiDriverInit(T_LDC1000_P gpioObj, T_LDC1000_P spiObj)
{
    hal_spiMap( (T_HAL_P)spiObj );
    hal_gpioMap( (T_HAL_P)gpioObj );

    hal_gpio_csSet( 0 );
}

#endif
#ifdef   __LDC1000_DRV_I2C__

void ldc1000_i2cDriverInit(T_LDC1000_P gpioObj, T_LDC1000_P i2cObj, uint8_t slave)
{
    _slaveAddress = slave;
    hal_i2cMap( (T_HAL_P)i2cObj );
    hal_gpioMap( (T_HAL_P)gpioObj );

    // ... power ON
    // ... configure CHIP
}

#endif
#ifdef   __LDC1000_DRV_UART__

void ldc1000_uartDriverInit(T_LDC1000_P gpioObj, T_LDC1000_P uartObj)
{
    hal_uartMap( (T_HAL_P)uartObj );
    hal_gpioMap( (T_HAL_P)gpioObj );

    // ... power ON
    // ... configure CHIP
}

#endif



/* ----------------------------------------------------------- IMPLEMENTATION */


/* Generic write 8-bit data function */
void ldc1000_writeData( uint8_t addressCommand, uint8_t writeData )
{
    uint8_t buffer[ 2 ];
    
    buffer[ 0 ] = addressCommand;
    buffer[ 1 ] = writeData;

    hal_gpio_csSet( 0 );
    hal_spiWrite( buffer, 2 );
    hal_gpio_csSet( 1 );
}

/* Generic read 8-bit data function */
uint8_t ldc1000_readData( uint8_t address )
{
    uint8_t writeReg[ 1 ];
    uint8_t readReg[ 1 ];

    writeReg[ 0 ] = address | _LDC1000_CMD_SPI_READ;

    hal_gpio_csSet( 0 );
    hal_spiWrite( writeReg, 1 );
    hal_spiRead( readReg, 1 );
    hal_gpio_csSet( 1 );

    return readReg[ 0 ];
}

/* Get proximity data function */
uint16_t ldc1000_getProximityData()
{
    uint8_t readReg[ 2 ];
    uint16_t result;

    readReg[ 0 ] = ldc1000_readData( _LDC1000_CMD_PROXLSB | _LDC1000_CMD_SPI_READ );
    readReg[ 1 ] = ldc1000_readData( _LDC1000_CMD_PROXMSB | _LDC1000_CMD_SPI_READ );
    
    result = readReg[ 1 ];
    result <<= 8;
    result |= readReg[ 0 ];
    
    return result;
}

/* Get inductance data function */
float ldc1000_getInductance()
{
    uint8_t readReg[ 3 ];
    uint32_t valueFreqCount;
    float fFreqCount;
    float result;

    readReg[ 0 ] = ldc1000_readData( _LDC1000_CMD_FREQCTRLSB | _LDC1000_CMD_SPI_READ );
    readReg[ 1 ] = ldc1000_readData( _LDC1000_CMD_FREQCTRMID | _LDC1000_CMD_SPI_READ );
    readReg[ 2 ] = ldc1000_readData( _LDC1000_CMD_FREQCTRMSB | _LDC1000_CMD_SPI_READ );

    valueFreqCount = readReg[ 2 ];
    valueFreqCount <<= 8;
    valueFreqCount |= readReg[ 1 ];
    valueFreqCount <<= 8;
    valueFreqCount |= readReg[ 0 ];
    
    fFreqCount = ( 1.0 / 3.0 ) * ( 8000000.0 / ( ( float ) valueFreqCount ) ) * 6144.0;
    
    result = 1000000.0 / ( 0.0000000001 * ( ( 2.0 * 3.14 * fFreqCount ) * ( 2.0 * 3.14 * fFreqCount ) ) );

    return result;
}

/* Get interrupt status */
uint8_t ldc1000_getInterrupt()
{
    return hal_gpio_intGet();
}




/* -------------------------------------------------------------------------- */
/*
  __ldc1000_driver.c

  Copyright (c) 2017, MikroElektonika - http://www.mikroe.com

  All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the distribution.

3. All advertising materials mentioning features or use of this software
   must display the following acknowledgement:
   This product includes software developed by the MikroElektonika.

4. Neither the name of the MikroElektonika nor the
   names of its contributors may be used to endorse or promote products
   derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY MIKROELEKTRONIKA ''AS IS'' AND ANY
EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL MIKROELEKTRONIKA BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

----------------------------------------------------------------------------- */