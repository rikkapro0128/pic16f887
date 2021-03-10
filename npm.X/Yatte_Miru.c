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

#include <xc.h>

#define _XTAL_FREQ 4000000
#define delayBaiMot 50 // khai bao thoi gian delay cua sang dan
#define delayBaiHai 300 // khai bao thoi gian delay cua sang dan
#define delayBaiBa 400 // khai bao thoi gian delay cua sang don
#define delayBaiBon 300 // khai bao thoi gian delay cua sang don
#define delayBaiNam 300 // khai bao thoi gian delay cua sang don

void declarePort();
void sangDan();
void sangDon();
void tamLedPortC();
void muoiSauLed();
void sauLedSangDuoi();

void main(void){
    declarePort();
    unsigned int count = 0;
    while(1) {
        /*
        // bài 2
        * sangDan(); 
        */
        
        /*
        // bài 3
        * sangDon(); 
        */
        
        /*
        // bài 4
        if(count < 2) {
            tamLedPortC();
            count++;
        }else {
            PORTC = 0xff;
        }
        */
        // bài 5
//        if(count < 2) {
//            muoiSauLed();
//            count++;
//        }else {
//            PORTC = 0xff;
//        }
        sauLedSangDuoi();
    }
}

void declarePort() { // khai bao port
    ANSEL = ANSELH = 0;
    TRISD = 0;
    TRISC = 0;
    TRISB = 0;
    PORTB = 0;
    PORTC = 0;
    PORTD = 0;
}

void sauLedSangDuoi() {
    TRISB = 0b00100000;
    PORTB = 0b00001000; 
    __delay_ms(delayBaiMot);
    TRISB = 0b00100000;
    PORTB = 0b00010000; 
    __delay_ms(delayBaiMot);
    TRISB = 0b00001000;
    PORTB = 0b00010000;
    __delay_ms(delayBaiMot);
    TRISB = 0b00001000;
    PORTB = 0b00100000; 
    __delay_ms(delayBaiMot);
    TRISB = 0b00010000;
    PORTB = 0b00100000; 
    __delay_ms(delayBaiMot);
    TRISB = 0b00010000;
    PORTB = 0b00001000; 
    __delay_ms(delayBaiMot);
}

void sangDan() { // function sang dan
    int index = 0;
    int hold = 0x80;
    __delay_ms(delayBaiHai);
    while(index < 8) {
        PORTD = hold;
        __delay_ms(delayBaiHai);
        hold = (hold >> 1) | hold;
        index++;
    }
}

void sangDon() { // function sang don
    unsigned char sum = 0x00, i = 0, j, hold = 0x80;
    while(i < 8) {
        j = 0;
        while(j < (8 - i)) {
            PORTD = (hold >> j) | sum;
            __delay_ms(delayBaiBa);
            j++;
        }
        sum = PORTD;
        i++;
    }
}

void tamLedPortC() {
    unsigned int total = 0, numberFlash = 5, numberRace = 2, numberCountUp = 3, pressed = 2;
    // kh?i nh?p nháy 5 l?n
    while(numberFlash > 0) {
         __delay_ms(delayBaiBon);
        PORTC = 0xff;
        __delay_ms(delayBaiBon);
        PORTC = 0x00;
        numberFlash--;
    }
    // kh?i sáng ?u?i 2 l?n
    while(numberRace > 0) {
        PORTC = 0;
        __delay_ms(delayBaiBon);
        unsigned char score = 0;
        while(score < 8) {
            PORTC = (0x01 << score);
            __delay_ms(delayBaiBon);
            score++;
        }
        numberRace--;
    }
    // kh?i sáng d?n 3 l?n
    while(numberCountUp > 0) {
        unsigned char index = 0;
        unsigned char hold = 0x80;
        PORTC = 0;
        __delay_ms(delayBaiBon);
        while(index < 8) {
            PORTC = hold;
            __delay_ms(delayBaiBon);
            hold = (hold >> 1) | hold;
            index++;
        }
        hold = 0x80;
        numberCountUp--;
    }
    // kh?i sáng d?n 2 l?n
    while(pressed > 0) {
        PORTC = 0;
        __delay_ms(delayBaiBon);
        unsigned char sum = 0x00, i = 0, j, hold = 0x80;
        while(i < 8) {
            j = 0;
            while(j < (8 - i)) {
                PORTC = (hold >> j) | sum;
                __delay_ms(delayBaiBon);
                j++;
            }
            sum = PORTC;
            i++;
        }
        pressed--;
    }
}

void muoiSauLed() {
    unsigned int numberFlash = 4, numberRace = 2, numberCountUp = 3;
    // nhap nhay
    while(numberFlash > 0) {
        __delay_ms(delayBaiNam);
        PORTC = 0xff;
        PORTD = 0xff;
        __delay_ms(delayBaiNam);
        PORTC = 0x00;
        PORTD = 0x00;
        numberFlash--;
    }
    // sang duoi
    while(numberRace > 0) {
        PORTD = 0;
        __delay_ms(delayBaiNam);
        unsigned char score = 0;
        while(score < 8) {
            PORTD = (0x80 >> score);
            __delay_ms(delayBaiNam);
            score++;
        }
        PORTD = 0;
        score = 0;
        while(score < 8) {
            PORTC = (0x80 >> score);
            __delay_ms(delayBaiNam);
            score++;
        }
        PORTC = 0;
        numberRace--;
    }
    while(numberCountUp > 0) {
        unsigned char index = 0;
        unsigned char hold = 0x80;
        PORTD = 0;
        __delay_ms(delayBaiNam);
        while(index < 8) {
            PORTD = hold;
            __delay_ms(delayBaiNam);
            hold = (hold >> 1) | hold;
            index++;
        }
        index = 0;
        hold = 0x80;
        PORTC = 0;
        while(index < 8) {
            PORTC = hold;
            __delay_ms(delayBaiNam);
            hold = (hold >> 1) | hold;
            index++;
        }
        PORTC = 0;
        PORTD = 0;
        numberCountUp--;
    }
    PORTC = 0xff;
    PORTD = 0xff;
}
