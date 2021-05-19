//Universida del Valle de Guatemala
//Facultad de ingenieria
//Departamento de ingenieria Electronica mecatronica y biomedica
//Electronica digital 2
//Santiago Galicia Reyes
//carnet 18483
#include <stdint.h>
#include <stdbool.h>
#include "inc/tm4c123gh6pm.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_ints.h"
#include "driverlib/sysctl.h"
#include "driverlib/interrupt.h"
#include "driverlib/gpio.h"
#include "driverlib/timer.h"
#include "driverlib/uart.h"
#include "driverlib/pin_map.h"

#ifdef DEBUG
void
__error__(char *pcFilename, uint32_t ui32Line)
{
}
#endif

/*
 * Interrupciones
 */

/*
 * Variables
 */
uint8_t var1 = 0;
uint8_t var2 = 1;//variable de contador general
uint8_t LED = 0;// variable de estado de la led
uint8_t dato = 0; // variable para uart


/*
 * Prototipado de funciones
 */
void timerf(void);
void funUART(void);

//main.c
int main(void)
{
    //++++++++++++++++++++++++++++++++++Setup++++++++++++++++++++++++++++++
    //OSC
    SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);

    IntMasterEnable();
    // + ++++++++++++++++++++++++++++++CONFIGURACIONES DEL MODULO UART+++++++++++++++++++++++++++++++++++++++++
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0);
    UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), 115200, UART_CONFIG_WLEN_8|UART_CONFIG_STOP_ONE|UART_CONFIG_PAR_NONE);
    UARTFIFOEnable(UART0_BASE);
    UARTIntEnable(UART0_BASE, UART_INT_RX|UART_INT_RT);
    UARTIntRegister(UART0_BASE, funUART);
    UARTEnable(UART0_BASE);
    IntEnable(INT_UART0);
    //CONFIGURACIONES DEL GPIO PARA DIGITAL OUTPUT
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);
    //CONFIGURACION DEL +}+++++++++++++++++++TIMER0 DE 32 BITS++++++++++++++++++++++++++++++++++++++++++
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
    TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);
    TimerLoadSet(TIMER0_BASE, TIMER_A, ((SysCtlClockGet()/2)-1));//0.5 interrupción
    IntEnable(INT_TIMER0A);
    TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
    TimerEnable(TIMER0_BASE, TIMER_A);

    //******************Loop****************************
    while(1){
// loop infinito
    }
}
void timerf(void){
    TimerIntClear(TIMER0_BASE, TIMER_A);
    var1++;// incremento del contador cada ciclo de interrupcion
    if (var1==1){
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, LED);
    }
    else if (var1==2){
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0);
        // cuando hace una sobrecarga del contador entonces se reinicia y escribe la led para que se apague
        var1=0;
        }

}
void funUART(void){
    UARTIntClear(UART0_BASE, UART_INT_RX|UART_INT_RT);
    dato=UARTCharGet(UART0_BASE);// funcion para obtener el dato de uart
    if(dato==var2){
        LED=0;
        var2=0;
    }
    else{
        if(dato==114){
            LED=2;
        }
        else if(dato==98){
            LED=4;
        }
        else if(dato==103){
            LED=8;
        }
        var2=dato;
    }
}
