#include <xc.h>
#include <stdint.h>

#pragma config FWDTEN = OFF
#pragma config JTAGEN = OFF

#define FCY 8000000UL
#include <libpic30.h>

#define CS LATBbits.LATB2

volatile int32_t position = 0;

/* ---------- Encoder CN Interrupt ---------- */
void __attribute__((interrupt, no_auto_psv)) _CNInterrupt(void)
{
    IFS1bits.CNIF = 0;

    if (PORTBbits.RB0 == PORTBbits.RB1)
        position++;
    else
        position--;
}

/* ---------- SPI1 MASTER INIT (FIXED PINS) ---------- */
void SPI1_Init_Master(void)
{
    /* SPI1 fixed pins */
    TRISBbits.TRISB6 = 0; // SCK1
    TRISBbits.TRISB5 = 0; // SDO1 (MOSI)
    TRISBbits.TRISB4 = 1; // SDI1 (MISO)

    TRISBbits.TRISB2 = 0; // CS
    CS = 1;

    SPI1STATbits.SPIEN = 0;

    SPI1CON1bits.MSTEN = 1; // Master
    SPI1CON1bits.CKP   = 0;
    SPI1CON1bits.CKE   = 1;
    SPI1CON1bits.SMP   = 0;
    SPI1CON1bits.MODE16 = 0;
    SPI1CON1bits.SPRE  = 0b110;
    SPI1CON1bits.PPRE  = 0b10;

    SPI1STATbits.SPIEN = 1;
}

void SPI1_Send(uint8_t data)
{
    CS = 0;
    SPI1BUF = data;
    while(!SPI1STATbits.SPIRBF);
    CS = 1;
}

/* ---------- Encoder Init ---------- */
void Encoder_Init(void)
{
    TRISBbits.TRISB0 = 1; // Encoder A
    TRISBbits.TRISB1 = 1; // Encoder B

    CNEN1bits.CN2IE = 1; // RB0
    CNEN1bits.CN3IE = 1; // RB1

    IFS1bits.CNIF = 0;
    IEC1bits.CNIE = 1;
}

int main(void)
{
    CLKDIVbits.RCDIV = 0; // 8 MHz

    Encoder_Init();
    SPI1_Init_Master();

    while(1)
    {
        SPI1_Send((uint8_t)position);
        __delay_ms(200);
    }
}
