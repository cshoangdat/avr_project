/*
 * File:   ADC.c
 * Author: csdat
 *
 * Created on April 12, 2023, 12:52 PM
 */


//#include <avr/io.h>
//#include <util/delay.h>
//#define AREF_MODE 0 //Dien ap tham chieu ngoai chan Vref
//#define AVCC_MODE (1<<REFS0) //Dien ap tham chieu AVCC
//#define INT_MODE (1<<REFS1)|(1<<REFS0) //dien ap tham chieu noi 2.56V 
//#define ADC_VREF_TYPE AVCC_MODE //dinh nghia kieu dien ap tham chieu
//uint16_t giatriadc;
//uint16_t docadc(unsigned char adc_channel)
//{   
//    ADMUX = adc_channel|ADC_VREF_TYPE;
//    ADCSRA|=(1<<ADSC);
//    loop_until_bit_is_set(ADCSRA,ADIF);
//    return ADCW;
//}
//void led7_out(uint16_t val){
//    uint16_t dvi,chuc,tram,nghin,temp_val;
//    temp_val = val;
//    nghin = temp_val/1000;
//    temp_val -= (1000*nghin);
//    tram = temp_val/100;
//    temp_val -= (100*tram);
//    chuc = temp_val/10;
//    dvi = temp_val - (10*chuc);
//    
//    PORTB = (chuc<<4) + dvi;
//    PORTC = (nghin<<4) + tram;
//}
//
//int main(void) {
//    ADCSRA|=(1<<ADEN)|(1<<ADPS2)|(1<<ADPS0);
//    ADMUX = ADC_VREF_TYPE;
//    DDRB = 0xFF;
//    DDRC = 0xFF;
//    while(1)
//    {
//     giatriadc=docadc(2);
//     led7_out(giatriadc);
//     _delay_ms(100);
//    }
//}

//ADMUX 
#include <xc.h>
int docadc(void)
{   ADCSRA|=(1<<ADSC);//Ghi giá tr? 1 vào bit ADSC c?a thanh ghi ADCSRA ?? b?t ??u quá trình chuy?n ??i analog sang digital.
    while(ADCSRA&(0b00010000)==0);//l?p cho ??n khi ADIF = 1
//    ADCSRA|=0b00010000;//xóa c? báo ng?t
    return ADCW;//thanh ghi ch?a giá tr? chuy?n ??i
}

void main(void) {
    unsigned int giatriadc;
    unsigned int giatriLED;
    DDRB=0xFF;
    PORTB=0xFF;
    DDRA |= (1<<PA0) | (1<<PA1) | (1<<PA2) | (1<<PA3);
    
    ADMUX |= 0b00000011;//Ch?n ADC3 làm tín hi?u ??u vào
    ADMUX |= 0b11000000;
//    DDRA&=0b11111110;
    ADCSRA|=(1<<ADEN)|(1<<ADPS2)|(1<<ADPS0); //enable adc
    
    while(1)
    {
    giatriadc=docadc();
    PORTB=giatriadc;
    float voltage = (float)giatriadc * 4.0/ (1024.0);
    float voltage2 = voltage*2.56/4;
    if(voltage2 >= 0 && voltage2 <=1){ //0.64
       PORTA = (1<<PA0);
    }
    else if(voltage2 > 1 && voltage2 <=2) PORTA = (1<<PA1); //0.64 1.28
    else if(voltage2 > 2 && voltage2 <=2.5) PORTA = (1<<PA2); //1.28 1.6
    else PORTA = (1<<PA3);
    }
    return;
}
