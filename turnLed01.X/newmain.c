/*
 * File:   newmain.c
 * Author: csdat
 *
 * Created on March 29, 2023, 1:43 PM
 */

#include <avr/io.h>
#include <util/delay.h>
#include <xc.h>

void main(void) {
//H�m DDRx: H�m n�y ???c s? d?ng ?? c?u h�nh ch? ?? ??u ra ho?c ??u v�o cho c�c ch�n I/O tr�n thanh ghi DDRx. V� d?: DDRB |= (1<<PB3) s? c?u h�nh ch�n PB3 c?a thanh ghi DDRB l� ??u ra.
//
//H�m PORTx: H�m n�y ???c s? d?ng ?? ghi gi� tr? v�o c�c ch�n ??u ra tr�n thanh ghi PORTx. V� d?: PORTB |= (1<<PB3) s? thi?t l?p ch�n PB3 c?a thanh ghi PORTB l� m?c cao.
//
//H�m PINx: H�m n�y ???c s? d?ng ?? ??c gi� tr? t? c�c ch�n ??u v�o tr�n thanh ghi PINx. V� d?: if(PINB & (1<<PB3)) s? ki?m tra xem ch�n PB3 c?a thanh ghi PINB c� ? m?c cao hay kh�ng.
//
//H�m ADC_read: H�m n�y ???c s? d?ng ?? ??c gi� tr? t? m?t k�nh ADC. N� s? d?ng thanh ghi ADC ?? c?u h�nh v� ??c gi� tr? t? k�nh ADC.
//
//H�m UART_send: H�m n�y ???c s? d?ng ?? g?i d? li?u qua k?t n?i UART. N� s? d?ng thanh ghi UART ?? c?u h�nh v� g?i d? li?u qua k?t n?i UART.
//
//H�m PWM_set: H�m n�y ???c s? d?ng ?? c?u h�nh v� ?i?u khi?n m?t k�nh PWM. N� s? d?ng thanh ghi PWM ?? c?u h�nh c�c th�ng s? nh? t?n s?, chu k? v� ?? r?ng xung.
    DDRB |= (1<<PB0);
    DDRB &= (0<<PB1);
    while(1)
    {
        if(PINB & (1<<PB1))
        {
            _delay_ms(200);
            if(PINB & (1<<PB1))
            PORTB ^= (1<<PB0);
        }
    }
    return;
//    PORTA = 0x55;
    }
    return;
}
