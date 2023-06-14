/*
 * File:   uart_trans.c
 * Author: csdat
 *
 * Created on May 17, 2023, 9:36 AM
 */


//#define F_CPU 8000000UL
#include <xc.h>
#include <util/delay.h>
#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
//UDR thanh ghi d? li?u
void USART_Transmit( unsigned char data )
{
	while ( !( UCSR0A & (1<<UDRE)) );   
    //Cho den khi UDRE = 1, bo dem trong UDR san sang nhan data
  	UDR0 = data;
}

unsigned char USART_Receive( void )
{
	while ( !(UCSR0A & 0b10000000));     
    //Cho den khi RXC = 1, có data chua doc trong UDR
	return UDR0;
}

void USART_Init()
{
	/* Set baud rate */
    //Baud rate 57600; Fosc = 8Mhz; 
	UBRR0H = 0;
	UBRR0L = 8;

	UCSR0B = (1<<RXEN)|(1<<TXEN);
    //Cho phep bo truyen, nhan ho?t dong

	UCSR0C =(1<<USBS)|(1<<UCSZ00)|(1<<UCSZ01);  //(1<<USBS)|(1<<UCSZ00)|(1<<UCSZ01)
    //USBS = 1 --> Chon Stop bit = 2bit
    //UCSZ0 = 11 --> 8 bit data
}

int docadc(void)
{   ADCSRA|=(1<<ADSC);
    //Bat dau chuyen doi ADC
    while((ADCSRA&(0b00010000))==0);
    //Cho den khi ADC chuyen doi hoan tat
    ADCSRA|=0b00010000;
    //ADIF = 1
    return ADCW;
    //Tra ve gia tri cho thanh ghi ADCW
}  

int main (void)
{
    unsigned char giatriadc;
    DDRB &= (0<<PB3);
    DDRB &= (0<<PB1);
   // PORTC=0xFF;
    ADMUX=0;
    ADMUX=0b01000000;
    //Dien ap tham chieu 2,56V
    //DDRF&=0b11111110;
    //Chon chan dau vao ADC0 PORT F
    ADCSRA|=(1<<ADEN)|(1<<ADPS2)|(1<<ADPS0);
    //ADEN: ADC enable
    //ADPS2: 1
    //ADPS1: 0
    //ADPS0: 1
    //prescaler = 8
    
	USART_Init();
	while (1)
	{
//      giatriadc=docadc();
//      PORTC=giatriadc;
//      USART_Transmit(giatriadc);
//      _delay_ms(50);
        
//         USART_Transmit(1);
//         _delay_ms(1000);
//        if(a==1)
//          USART_Transmit(5);
//        else
//          USART_Transmit(3);
//          _delay_ms(1000);
//          a=!a;
        if(PINB & (1<<PB1)){
            _delay_ms(1100);
            if(PINB & (1<<PB1))
            USART_Transmit(54);
        }
        else if(PINB & (1<<PB3)){
            _delay_ms(1100);
            if(PINB & (1<<PB3))
            USART_Transmit(55);
        }
	}
}
