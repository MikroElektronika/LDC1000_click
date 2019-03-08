/*
    __ldc1000_driver.h

-----------------------------------------------------------------------------

  This file is part of mikroSDK.
  
  Copyright (c) 2017, MikroElektonika - http://www.mikroe.com

  All rights reserved.

----------------------------------------------------------------------------- */

/**
@file   __ldc1000_driver.h
@brief    LDC1000 Driver
@mainpage LDC1000 Click
@{

@image html libstock_fb_view.jpg

@}

@defgroup   LDC1000
@brief      LDC1000 Click Driver
@{

| Global Library Prefix | **LDC1000** |
|:---------------------:|:-----------------:|
| Version               | **1.0.0**    |
| Date                  | **Sep 2018.**      |
| Developer             | **Nenad Filipovic**     |

*/
/* -------------------------------------------------------------------------- */

#include "stdint.h"

#ifndef _LDC1000_H_
#define _LDC1000_H_

/** 
 * @macro T_LDC1000_P
 * @brief Driver Abstract type 
 */
#define T_LDC1000_P    const uint8_t*

/** @defgroup LDC1000_COMPILE Compilation Config */              /** @{ */

   #define   __LDC1000_DRV_SPI__                            /**<     @macro __LDC1000_DRV_SPI__  @brief SPI driver selector */
//  #define   __LDC1000_DRV_I2C__                            /**<     @macro __LDC1000_DRV_I2C__  @brief I2C driver selector */                                          
// #define   __LDC1000_DRV_UART__                           /**<     @macro __LDC1000_DRV_UART__ @brief UART driver selector */ 

                                                                       /** @} */
/** @defgroup LDC1000_VAR Variables */                           /** @{ */

extern const uint8_t _LDC1000_CMD_ID;
extern const uint8_t _LDC1000_CMD_REVID;
extern const uint8_t _LDC1000_CMD_RPMAX;
extern const uint8_t _LDC1000_CMD_RPMIN;
extern const uint8_t _LDC1000_CMD_SENSORFREQ;
extern const uint8_t _LDC1000_CMD_LDCCONFIG;
extern const uint8_t _LDC1000_CMD_CLKCONFIG;
extern const uint8_t _LDC1000_CMD_THRESHILSB;
extern const uint8_t _LDC1000_CMD_THRESHIMSB;
extern const uint8_t _LDC1000_CMD_THRESLOLSB;
extern const uint8_t _LDC1000_CMD_THRESLOMSB;
extern const uint8_t _LDC1000_CMD_INTCONFIG;
extern const uint8_t _LDC1000_CMD_PWRCONFIG;
extern const uint8_t _LDC1000_CMD_STATUS;
extern const uint8_t _LDC1000_CMD_PROXLSB;
extern const uint8_t _LDC1000_CMD_PROXMSB;
extern const uint8_t _LDC1000_CMD_FREQCTRLSB;
extern const uint8_t _LDC1000_CMD_FREQCTRMID;
extern const uint8_t _LDC1000_CMD_FREQCTRMSB;
extern const uint8_t _LDC1000_RPMAX_38_785K;
extern const uint8_t _LDC1000_RPMIN_2_39K;
extern const uint8_t _LDC1000_SENSORFREQ_N217_F20;
extern const uint8_t _LDC1000_LDCCONFIG_A2V_T6144;
extern const uint8_t _LDC1000_CLKCONFIG_EC_ET_ENABLE;
extern const uint8_t _LDC1000_PWRCONFIG_ACTIVE_MODE;
extern const uint8_t _LDC1000_CMD_SPI_READ;

                                                                       /** @} */
/** @defgroup LDC1000_TYPES Types */                             /** @{ */



                                                                       /** @} */
#ifdef __cplusplus
extern "C"{
#endif

/** @defgroup LDC1000_INIT Driver Initialization */              /** @{ */

#ifdef   __LDC1000_DRV_SPI__
void ldc1000_spiDriverInit(T_LDC1000_P gpioObj, T_LDC1000_P spiObj);
#endif
#ifdef   __LDC1000_DRV_I2C__
void ldc1000_i2cDriverInit(T_LDC1000_P gpioObj, T_LDC1000_P i2cObj, uint8_t slave);
#endif
#ifdef   __LDC1000_DRV_UART__
void ldc1000_uartDriverInit(T_LDC1000_P gpioObj, T_LDC1000_P uartObj);
#endif


/** @defgroup LDC1000_FUNC Driver Functions */                   /** @{ */


/**
 * @brief Generic write 8-bit data function
 *
 * @param[in] addressCommand         8-bit data register address
 *
 * @param[in] writeData              8-bit data to write
 *
 * Function write 8-bit data to 8-bit data register address
 * on the LDC1000 sensor.
 */
void ldc1000_writeData( uint8_t addressCommand, uint8_t writeData );

/**
 * @brief Generic read 8-bit data function
 *
 * @return
 * 8-bit data from addressed register on the LDC1000
 *
 * Function read 8-bit data from 8-bit data register address
 * on the LDC1000 sensor.
 */
uint8_t ldc1000_readData( uint8_t addressCommand );

/**
 * @brief Get proximity data function
 *
 * @return
 * 16-bit proximity data
 *
 * Function read 16-bit proximity data
 * from two register address
 * on the LDC1000 sensor.
 */
uint16_t ldc1000_getProximityData();

/**
 * @brief Get inductance data function
 *
 * @return
 * float inductance [ uH ]
 *
 * Function read 24-bit frequency counter data,
 * calculate ( float ) Inductance ( Impedance L ) [ uH ]
 * from the LDC1000 sensor.
 */
float ldc1000_getInductance();

/**
 * @brief Get interrupt status
 *
 * @return
 * status reading from pins
 *
 * Functions for reads interrupt pin.
 */
uint8_t ldc1000_getInterrupt();



                                                                       /** @} */
#ifdef __cplusplus
} // extern "C"
#endif
#endif

/**
    @example Click_LDC1000_STM.c
    @example Click_LDC1000_TIVA.c
    @example Click_LDC1000_CEC.c
    @example Click_LDC1000_KINETIS.c
    @example Click_LDC1000_MSP.c
    @example Click_LDC1000_PIC.c
    @example Click_LDC1000_PIC32.c
    @example Click_LDC1000_DSPIC.c
    @example Click_LDC1000_AVR.c
    @example Click_LDC1000_FT90x.c
    @example Click_LDC1000_STM.mbas
    @example Click_LDC1000_TIVA.mbas
    @example Click_LDC1000_CEC.mbas
    @example Click_LDC1000_KINETIS.mbas
    @example Click_LDC1000_MSP.mbas
    @example Click_LDC1000_PIC.mbas
    @example Click_LDC1000_PIC32.mbas
    @example Click_LDC1000_DSPIC.mbas
    @example Click_LDC1000_AVR.mbas
    @example Click_LDC1000_FT90x.mbas
    @example Click_LDC1000_STM.mpas
    @example Click_LDC1000_TIVA.mpas
    @example Click_LDC1000_CEC.mpas
    @example Click_LDC1000_KINETIS.mpas
    @example Click_LDC1000_MSP.mpas
    @example Click_LDC1000_PIC.mpas
    @example Click_LDC1000_PIC32.mpas
    @example Click_LDC1000_DSPIC.mpas
    @example Click_LDC1000_AVR.mpas
    @example Click_LDC1000_FT90x.mpas
*/                                                                     /** @} */
/* -------------------------------------------------------------------------- */
/*
  __ldc1000_driver.h

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