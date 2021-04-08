/*
 * File:   8led chop tat.c
 * Author: 84347
 *
 * Created on March 3, 2021, 7:10 AM
 */


// PIC16F887 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator: High-speed crystal/resonator on RA6/OSC2/CLKOUT and RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = ON       // RE3/MCLR pin function select bit (RE3/MCLR pin function is MCLR)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#define _XTAL_FREQ 4000000
#include <xc.h>

void declarePort();

unsigned int count = 0, isOn = 1;

void main(void) {
    declarePort();
    while(1);
}

void declarePort() { // declare port
    ANSEL = ANSELH = 0;
    TRISE = 0;
    PORTE = 0;
    TRISB = WPUB = 0x01; // declare resistance pull-up
    nRBPU = 0; // set permit all PORTB have resistance pull-up
    GIE = 1;
    RBIE = 1;
    IOCB = 0x01;
}

void __interrupt() myIsr() {
    if(!RB0) {
        while(!RB0);
        if(isOn) {
            PORTE = 0xff;
            isOn = !isOn;
        }else {
            PORTE = 0;
            isOn = !isOn;
        }
    }
    RBIF = 0;
}
