![MikroE](http://www.mikroe.com/img/designs/beta/logo_small.png)

---

# LDC1000 Click

---

- **CIC Prefix**  : LDC1000
- **Author**      : Nenad Filipovic
- **Verison**     : 1.0.0
- **Date**        : Sep 2018.

---

### Software Support

We provide a library for the LDC1000 Click on our [LibStock](https://libstock.mikroe.com/projects/view/1069/ldc1000-click-example) 
page, as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). The demo can run on all the main 
MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

**Library Description**

The library covers all the necessary functions to control LDC1000 Click board. 
Library performs the communication with the device via SPI driver by writting to registers and by reading from registers.
Library set default configuration by writting to registers, get Proximity and Inductance data from register. 
Convert calculate ( float ) Inductance ( Impedance L ) data [ uH ]
from the LDC1000 Click sensor and send results via UART.

Key functions :

- ``` uint8_t ldc1000_readData( uint8_t address ) ``` - Generic read 8-bit data function
- ``` uint16_t ldc1000_getProximityData() ``` - Get proximity data function
- ``` float ldc1000_getInductance() ``` - Get inductance data function

**Examples Description**

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


```.c

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

```



The full application code, and ready to use projects can be found on our 
[LibStock](https://libstock.mikroe.com/projects/view/1069/ldc1000-click-example) page.

Other mikroE Libraries used in the example:

- SPI
- UART
- Conversions

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART click](http://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](http://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](http://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](http://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.

---
---
