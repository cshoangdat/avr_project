/*
 * File:   uart_rev.c
 * Author: csdat
 *
 * Created on May 17, 2023, 9:38 AM
 */


#define F_CPU 8000000UL
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
	while ( !(UCSR0A & (1<<RXC)) );    
    //Cho den khi RXC = 1, có data chua doc trong UDR
	return UDR0;
}

void USART_Init()
{
	/* Set baud rate */
    //Baud rate 57600; Fosc = 8Mhz; 
	UBRR0H =0;
	UBRR0L =8;

	UCSR0B = (1<<RXEN)|(1<<TXEN);
    //Cho phep bo truyen, nhan ho?t dong

	UCSR0C = (1<<USBS)|(1<<UCSZ00)|(1<<UCSZ01);
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
	DDRC |= (1<<PB0);
    PORTC=0x00;
    ADMUX=0;
    ADMUX=0b01000000;
    //Dien ap tham chieu 2,56V
    DDRF&=0b11111110;
    //Chon chan dau vao ADC0 PORT F
    ADCSRA|=(1<<ADEN)|(1<<ADPS1)|(1<<ADPS0);
    //ADEN: ADC enable
    //ADPS2: 1
    //ADPS1: 0
    //ADPS0: 1
    //prescaler = 8
    
	USART_Init();
	while (1)
	{
//      giatriadc=USART_Receive();
//      PORTC=giatriadc;
//   
//      USART_Transmit(giatriadc);
//        USART_Transmit(USART_Receive());
//        PORTC= USART_Receive();
//      _delay_ms(50);
        if(USART_Receive()==1)
            PORTC |= (1<<PB0);
        else if(USART_Receive()==0)
            PORTC &= ~(1<<PB0);
        _delay_ms(50);
	}
}