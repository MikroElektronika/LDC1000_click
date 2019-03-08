/*
Example for LDC1000 Click

    Date          : Sep 2018.
    Author        : Nenad Filipovic

Test configuration CEC :
    
    MCU              : CEC1702
    Dev. Board       : Clicker 2 for CEC1702
    ARM Compiler ver : v6.0.0.0

---

Description :

The application is composed of three sections :

- System Initialization - Initializes GPIO, SPI and LOG structures,
     set INT pin as input and CS pin as output.
- Application Initialization - Initialization driver enable's - SPI,
     initialization the LDC1000 sensor and start write log.
- Application Task - (code snippet) This is a example which demonstrates the use of LDC1000 Click board.
     Read Proximity and Inductance data from register on the LDC1000 sensor,
     display Proximity and calculated Inductance data [ uH ].
     Results are being sent to the Usart Terminal where you can track their changes.
     All data logs on usb uart for aproximetly every 100 ms
     when Proximity data changes with sensitivity of tolerance +- 100.

Additional Functions :

- UART
- Conversions

*/

#include "Click_LDC1000_types.h"
#include "Click_LDC1000_config.h"


uint16_t proximityValue;
uint16_t proximityValueOld = 0;
uint16_t sensitivity = 100;
float inductance;
char logText[50];

void systemInit()
{
    mikrobus_gpioInit( _MIKROBUS1, _MIKROBUS_INT_PIN, _GPIO_INPUT );
    mikrobus_gpioInit( _MIKROBUS1, _MIKROBUS_CS_PIN, _GPIO_OUTPUT );

    mikrobus_spiInit( _MIKROBUS1, &_LDC1000_SPI_CFG[0] );

    mikrobus_logInit( _MIKROBUS2, 9600 );

    Delay_100ms();
}

void applicationInit()
{
    ldc1000_spiDriverInit( (T_LDC1000_P)&_MIKROBUS1_GPIO, (T_LDC1000_P)&_MIKROBUS1_SPI );

    // Rp Maximum
    ldc1000_writeData( _LDC1000_CMD_RPMAX, _LDC1000_RPMAX_38_785K );
    // Rp Minimum
    ldc1000_writeData( _LDC1000_CMD_RPMIN, _LDC1000_RPMIN_2_39K );
    // Sensor Frequency
    ldc1000_writeData( _LDC1000_CMD_SENSORFREQ, _LDC1000_SENSORFREQ_N217_F20 );
    // LDC Configuration
    ldc1000_writeData( _LDC1000_CMD_LDCCONFIG, _LDC1000_LDCCONFIG_A2V_T6144 );
    // Clock Configuration
    ldc1000_writeData( _LDC1000_CMD_CLKCONFIG, _LDC1000_CLKCONFIG_EC_ET_ENABLE );
    // Power Configuration
    ldc1000_writeData( _LDC1000_CMD_PWRCONFIG, _LDC1000_PWRCONFIG_ACTIVE_MODE );

    mikrobus_logWrite( "---------------------------", _LOG_LINE);
    mikrobus_logWrite("   Initialisation LDC1000   ",_LOG_LINE);
    mikrobus_logWrite( "---------------------------", _LOG_LINE);

    Delay_100ms();
}

void applicationTask()
{
    proximityValue = ldc1000_getProximityData();

    inductance = ldc1000_getInductance();

    if ( ( ( proximityValue - proximityValueOld ) > sensitivity ) && ( ( proximityValueOld - proximityValue ) > sensitivity ) )
    {
        mikrobus_logWrite( " Proximity   : ", _LOG_TEXT );
        IntToStr( proximityValue, logText );
        mikrobus_logWrite( logText, _LOG_LINE );

        mikrobus_logWrite( " Impedance L : ", _LOG_TEXT );
        FloatToStr( inductance, logText );
        mikrobus_logWrite( logText, _LOG_TEXT );
        mikrobus_logWrite( " uH", _LOG_LINE );

        mikrobus_logWrite( "---------------------------", _LOG_LINE);

        proximityValueOld = proximityValue;

        Delay_100ms();
    }
}

void main()
{
    systemInit();
    applicationInit();

    while (1)
    {
            applicationTask();
    }
}