/*
 * File:   demo.c
 * Author: Yatte Miru
 *
 * Created on March 3, 2021, 11:44 PM
 */

// CONFIG
#define _XTAL_FREQ 20000000
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config CP = OFF         // FLASH Program Memory Code Protection bits (Code protection off)
#pragma config BOREN = ON      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low Voltage In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EE Memory Code Protection (Code Protection off)
#pragma config WRT = OFF        // FLASH Program Memory Write Enable (Unprotected program memory may not be written to by EECON control)

#include <xc.h>
#define TRISD0 = 0;
void main(void) {
    while (1) {
        __delay_ms(1000); // Delay 1 giay 
        RB0 = 0;  // LED TAT    
        __delay_ms(1000); // Delay 1 giay
    }
}
