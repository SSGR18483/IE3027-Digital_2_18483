#include <stdint.h>
#include <stdbool.h>
#include "driverlib/gpio.c"
#include "driverlib/gpio.h"
#include "driverlib/debug.h"
#include "inc/hw_types.h"
#include "inc/hw_gpio.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.c"
#include "driverlib/sysctl.h"
#include "driverlib/pin_map.h"


int main(void)
{
    //Configuracion del reloj  para una frecuencia de 40MHz y con el oscilador principal
    SysCtlClockSet ( SYSCTL_SYSDIV_5 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ );
    //Se configura para poder utilizar los perifericos del puerto F
    SysCtlPeripheralEnable ( SYSCTL_PERIPH_GPIOF );
    //Se configuran los pines de los leds rojo, azul y verde para output
    GPIOPinTypeGPIOOutput (GPIO_PORTF_BASE,GPIO_PIN_1);
    GPIOPinTypeGPIOOutput (GPIO_PORTF_BASE, GPIO_PIN_2);
    GPIOPinTypeGPIOOutput (GPIO_PORTF_BASE, GPIO_PIN_3);
    //Se configura el boton uno para que funcione como entrada y weak pull up
    GPIOPinTypeGPIOInput(GPIO_PORTF_BASE , GPIO_PIN_4 );
    GPIOPadConfigSet(GPIO_PORTF_BASE,GPIO_PIN_4, GPIO_STRENGTH_4MA , GPIO_PIN_TYPE_STD_WPU );

    while(1) {

        //Se trabaja con hexadecimales para que encienda un respectivo color
        if ((GPIOPinRead (GPIO_PORTF_BASE,GPIO_PIN_4) & 0x16)==0) {
            while ((GPIOPinRead (GPIO_PORTF_BASE,GPIO_PIN_4) & 0x16)==0) { }
            //Se enciende el verde
            GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3,0x08);
            SysCtlDelay (20000000);
            GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3,0x00);
            SysCtlDelay (5000000);
            //Se enciende el verde que parpadea
            GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3,0x08);
            SysCtlDelay (5000000);
            GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3,0x00);
            SysCtlDelay (5000000);
            GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3,0x08);
            SysCtlDelay (5000000);
            GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3,0x00);
            SysCtlDelay (5000000);
            GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3,0x08);
            SysCtlDelay (5000000);
            GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3,0x00);
            SysCtlDelay (5000000);
            //Se enciende el amarillo
            GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3,0x0A);
            SysCtlDelay (20000000);
            GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3,0x00);
            SysCtlDelay (5000000);
            //Se enciende el rojo
            GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3,0x02);
            SysCtlDelay (20000000);
            GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3,0x00);
            SysCtlDelay (5000000);

        }
    }

}
