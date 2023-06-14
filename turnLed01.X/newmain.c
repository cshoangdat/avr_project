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
//Hàm DDRx: Hàm này ???c s? d?ng ?? c?u hình ch? ?? ??u ra ho?c ??u vào cho các chân I/O trên thanh ghi DDRx. Ví d?: DDRB |= (1<<PB3) s? c?u hình chân PB3 c?a thanh ghi DDRB là ??u ra.
//
//Hàm PORTx: Hàm này ???c s? d?ng ?? ghi giá tr? vào các chân ??u ra trên thanh ghi PORTx. Ví d?: PORTB |= (1<<PB3) s? thi?t l?p chân PB3 c?a thanh ghi PORTB là m?c cao.
//
//Hàm PINx: Hàm này ???c s? d?ng ?? ??c giá tr? t? các chân ??u vào trên thanh ghi PINx. Ví d?: if(PINB & (1<<PB3)) s? ki?m tra xem chân PB3 c?a thanh ghi PINB có ? m?c cao hay không.
//
//Hàm ADC_read: Hàm này ???c s? d?ng ?? ??c giá tr? t? m?t kênh ADC. Nó s? d?ng thanh ghi ADC ?? c?u hình và ??c giá tr? t? kênh ADC.
//
//Hàm UART_send: Hàm này ???c s? d?ng ?? g?i d? li?u qua k?t n?i UART. Nó s? d?ng thanh ghi UART ?? c?u hình và g?i d? li?u qua k?t n?i UART.
//
//Hàm PWM_set: Hàm này ???c s? d?ng ?? c?u hình và ?i?u khi?n m?t kênh PWM. Nó s? d?ng thanh ghi PWM ?? c?u hình các thông s? nh? t?n s?, chu k? và ?? r?ng xung.
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
