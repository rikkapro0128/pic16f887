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
#define timeTest 50 // khai bao thoi gian delay cua sang don

void declarePort();
//void resetTime(unsigned int &hours, unsigned int &minutes, unsigned int &seconds);

void main(void){
    declarePort();
    unsigned char listNumber[10] = {0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90};
    unsigned char testLed = 0;
    unsigned int numberLed7Segment = 4, hours = 0, minutes = 0, seconds = 0, hold = 0x08, dozen, unit;
    unsigned int i;
    while(1) {
        //hold = 0x08;
        if(seconds == 60) {
            seconds = 0;
        }
        //for(i = 0; i < numberLed7Segment - 2; i++) {
            if(seconds >= 10) {
                dozen = seconds / 10;
                unit = seconds % 10;
            }else {
                dozen = seconds;
                unit = 0;
            }
            PORTD = 0x08;
            PORTC = listNumber[unit];
            __delay_ms(5);
            PORTD = PORTD >> 1;
            PORTC = listNumber[dozen];
            __delay_ms(5);
        //}
        __delay_ms(timeTest);
        seconds += 1;
    }
}

void declarePort() { // khai bao port
    ANSEL = ANSELH = 0;
    TRISD = 0;
    TRISC = 0;
    PORTC = 0;
    PORTD = 0xff;
}

//void resetTime(unsigned int &hours, unsigned int &minutes, unsigned int &seconds) {
//    if(minutes == 60) {
//        minutes == 0;
//    }else if(seconds == 60) {
//        seconds == 0;
//    }
//    else if(hours == 24) {
//        hours = 0;
//    }
//}
