/*
 * File:   tuHoc.c
 * Author: csdat
 *
 * Created on May 16, 2023, 8:42 AM
 */


#include <xc.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdlib.h>

int docadc(void)
{   ADCSRA|=(1<<ADSC);//Ghi giá tr? 1 vào bit ADSC c?a thanh ghi ADCSRA ?? b?t ??u quá trình chuy?n ??i analog sang digital.
    while(ADCSRA&(0b00010000)==0);//l?p cho ??n khi ADIF = 1
//    ADCSRA|=0b00010000;//xóa c? báo ng?t
    return ADCW;//thanh ghi ch?a giá tr? chuy?n ??i
}
void display_value(unsigned int value){
    unsigned char hex[10] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};
    unsigned int temp = value;
    unsigned int hangChuc = temp/10;
    unsigned int hangDonVi = temp%10;
    PORTA = 0x00;
    PORTA = 0b00000001;
    PORTC = hex[hangChuc];
    _delay_ms(1);
    PORTA = 0x00;
    PORTA = 0b00000010;
    PORTC = hex[hangDonVi];
    _delay_ms(1);
}

void uart_char_tx(unsigned char chr){
    //bit_is_clear de kiem tra bit UDRE trong thanh ghi UCSR0A.Neu bit UDRE = 0 la chua 1 byte du lieu chua truyen di
    while (bit_is_clear(UCSR0A,UDRE)) {}; //cho den khi bit UDRE=1  
            UDR0 =chr;//truyen ky tu vao thanh ghi UDR0
}

int main(void) {
    //Nhan nut giu trang thai
//    DDRB |= (1<<PB0);
//    DDRB &= (0<<PB1);
//    while(1)
//    {
//        if(PINB & (1<<PB1))
//        {
//            _delay_ms(200);
//            if(PINB & (1<<PB1))
//            PORTB ^= (1<<PB0);
//        }
//    }
    //bam xung PWM:
//    DDRB |= (1<<PB2);               
//    PORTB = 0x00;
//
//    TCCR0=(1<<CS01);// CS02=0, CS01=0, CS00=1: chon Prescaler = 1
////    TCNT0= 216;              //gan gia tri khoi tao cho T/C0
//    TIMSK=(1<<TOIE0);//cho phep ngat khi co tran o T/C0
//    sei();                       //set bit I cho phep ngat toan cuc
//
//    while (1){           //vòng l?p vô t?n 
//           //do nothing
//    }
    //ADC:
//    unsigned int giatriadc;
//    DDRC=0xFF;
//    DDRA |= (1<<PA0) | (1<<PA1);
//    PORTC=0x00;
//    ADMUX |= 0b00000011;//Ch?n ADC3 làm tín hi?u ??u vào
//    ADMUX |= 0b01000000;//gán giá tr? tham chi?u là AVCC
////    DDRA&=0b11111110;
//    ADCSRA|=(1<<ADEN)|(1<<ADPS2)|(1<<ADPS0); //enable adc
//    
//    while(1)
//    {
//    giatriadc=docadc();
//    giatriadc = giatriadc/73;
//    display_value(giatriadc);
//    }
    //UART:
//    DDRD=0xFF;
//    PORTD=0xFF;
//    //set baud, 57.6k ung voi f=8Mhz, xem bang 70 trang 165, Atmega32 datasheet
//    UBRR0H=0;  
//    UBRR0L=8;
//    //set khung truyen va kich hoat bo nhan du lieu
//    UCSR0A=0x00;//cau hinh lai thanh ghi
//    UCSR0C=(1<<UCSZ01)|(1<<UCSZ00);//set truyen 8 bit
//    UCSR0B=(1<<TXEN); //cho phep bo truyen hoat dong 
//    char mssv[8] = {50,48,49,49,57,50,49,52};
//    //    char mssv[8] = {2,0,1,1,9,2,1,4};
//    for(int i = 0; i<8;i++){
//        uart_char_tx(mssv[i]);
//        _delay_ms(1000);
//    }
}

ISR (TIMER0_OVF_vect ){ 
    if(PORTB==0)
        {  
            PORTB |= (1<<PB2); 
            TCNT0 = 250;
        }
        else 
        {  
            TCNT0 = 221;//221
            PORTB &= (0<<PB2); 
        }
}