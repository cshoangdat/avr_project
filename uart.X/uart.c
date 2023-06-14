/*
 * File:   uart.c
 * Author: csdat
 *
 * Created on April 19, 2023, 1:36 PM
 */


#define F_CPU 8000000UL
#include <xc.h>
#include <util/delay.h>
#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>


void uart_char_tx(unsigned char chr){
    //bit_is_clear de kiem tra bit UDRE trong thanh ghi UCSR0A.Neu bit UDRE = 0 la chua 1 byte du lieu chua truyen di
    while (bit_is_clear(UCSR0A,UDRE)) {}; //cho den khi bit UDRE=1  
            UDR0 =chr;//truyen ky tu vao thanh ghi UDR0
}


int docadc(void)
{   ADCSRA|=(1<<ADSC);
    while((ADCSRA&(0b00010000))==0);
    ADCSRA|=0b00010000;
    return ADCW;
}

int main(void) {
    volatile unsigned int giatriadc;
    DDRB=0xFF;
    PORTB=0xFF;
    
    ADMUX=0;//Ch?n ADC0 làm tín hi?u ??u vào
    ADMUX=0b01000000;//gán giá tr? tham chi?u là AVCC
    DDRA&=0b11111110;
    ADCSRA|=(1<<ADEN)|(1<<ADPS2)|(1<<ADPS0);
    //set baud, 57.6k ung voi f=8Mhz, xem bang 70 trang 165, Atmega32 datasheet
    UBRR0H=0;  
    UBRR0L=8;
  
    //set khung truyen va kich hoat bo nhan du lieu
    UCSR0A=0x00;//cau hinh lai thanh ghi
    UCSR0C=(1<<UCSZ01)|(1<<UCSZ00);//set truyen 8 bit
    UCSR0B=(1<<TXEN); //cho phep bo truyen hoat dong 
  
    char i = 32;
    while(i<128)
    {
//        unsigned char giatriadc;
//        giatriadc = docadc();
//        uart_char_tx(giatriadc)
            uart_char_tx(i);
            _delay_ms(100);
            i++;
    }
    return 1;
}

/*
 * File:   UART.c
 * Author: HP
 *
 * Created on February 21, 2023, 1:08 PM
 */

//#define F_CPU 8000000UL
//#include <xc.h>
//#include <util/delay.h>
//#include <stdio.h>
//#include <avr/io.h>
//#include <avr/interrupt.h>
////UDR thanh ghi d? li?u
//void USART_Transmit( unsigned char data )
//{
//	while ( !( UCSR0A & (1<<UDRE)) );   
//    //Cho den khi UDRE = 1, bo dem trong UDR san sang nhan data
//  	UDR0 = data;
//}
//
//unsigned char USART_Receive( void )
//{
//	while ( !(UCSR0A & (1<<RXC)) );    
//    //Cho den khi RXC = 1, có data chua doc trong UDR
//	return UDR0;
//}
//
//void USART_Init()
//{
//	/* Set baud rate */
//    //Baud rate 57600; Fosc = 8Mhz; 
//	UBRR0H =0;
//	UBRR0L =8;
//
//	UCSR0B = (1<<RXEN)|(1<<TXEN);
//    //Cho phep bo truyen, nhan ho?t dong
//
//	UCSR0C = (1<<USBS)|(1<<UCSZ00)|(1<<UCSZ01);
//    //USBS = 1 --> Chon Stop bit = 2bit
//    //UCSZ0 = 11 --> 8 bit data
//}
// 
//
//int main (void)
//{
//    unsigned char giatriadc;
//    DDRA=0xFF;
//    PORTA=0xFF;
//	DDRC=0xFF;
//    PORTC=0xFF;
//    ADMUX=0;
//    ADMUX=0b01000000;
//    //Dien ap tham chieu 2,56V
//    DDRF&=0b11111110;
//    //Chon chan dau vao ADC0 PORT F
//    ADCSRA|=(1<<ADEN)|(1<<ADPS1)|(1<<ADPS0);
//    //ADEN: ADC enable
//    //ADPS2: 1
//    //ADPS1: 0
//    //ADPS0: 1
//    //prescaler = 8
//    
//	USART_Init();
//	while (1)
//	{
////      giatriadc=USART_Receive();
////      PORTC=giatriadc;
////   
////      USART_Transmit(giatriadc);
////        USART_Transmit(USART_Receive());
////        PORTC= USART_Receive();
////      _delay_ms(50);
//        if(USART_Receive()==1)
//            PORTC |= (1<<PC0);
//        else if(USART_Receive()==0)
//            PORTC &= (0<<PC0);
//        _delay_ms(50);
//	}
}