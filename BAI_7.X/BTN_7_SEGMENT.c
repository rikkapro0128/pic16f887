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
#define timeTest 50 // declare time delay 
#define timeForOneSecond 1000 // declare time delay 

void declarePort();
void showWord(unsigned int times);
unsigned int showNumberToThisNumber(unsigned int nonShow);
void showNumber();

void main(void){
    declarePort();
    while(1)
    {
       if(!RB0)
       {
          // do something
          showWord(4); // "fill number" is number second so, you want run for this number second
       }else if(!RB1) { 
          // do something
           showNumberToThisNumber(26); // "fill number" what you want don't show this number
       }else if(!RB2) {
           showNumber();
       }
    }
}

void showNumber() {
    unsigned char listNumber[10] = {0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90};
    unsigned int i = 10, j = 10;
    while(j--) {
        PORTC = listNumber[j];
        i = 10;
        while(i--) {
            PORTD = listNumber[i];
            __delay_ms(timeTest);
        }
    }
    PORTD = PORTC = 0xff;
}

unsigned int showNumberToThisNumber(unsigned int nonShow) {
    unsigned int dozen = nonShow / 10;
    unsigned int unit = nonShow % 10;
    unsigned char listNumber[10] = {0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90};
    unsigned int i = 0, j = 0;
    while(j < 10) {
        PORTC = listNumber[j];
        i = 0;
        while(i < 10) {
            PORTD = listNumber[i];
            __delay_ms(timeTest);
            if(j == dozen && i == unit) {
                PORTD = PORTC = 0xff;
                return 1;
            }
            i++;
        }
        j++;
    }
}

void showWord(unsigned int times) {
    unsigned char letterAUpCase = 0x08, letterBLowerCase = 0x03;
    while(times--) {
        PORTC = letterAUpCase;
        PORTD = letterBLowerCase;
        __delay_ms(timeForOneSecond / 2);
        PORTD = PORTC = 0xff;
        __delay_ms(timeForOneSecond / 2);
    }
}

void declarePort() { // declare port
    ANSEL = ANSELH = 0;
    TRISD = 0;
    PORTD = 0xff;
    TRISC = 0;
    PORTC = 0xff;
    // declare Pin RB0 - RB2 is input
    TRISB0 = 1;
    TRISB1 = 1;
    TRISB2 = 1;
    // declare resistance pull-up
    nRBPU = 0; // set permit all PORTB have resistance pull-up
    WPUB = 0x07; // set only pin RB0 - RB2 have resistance pull-up
}
