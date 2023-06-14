/*
 * File:   timer.c
 * Author: csdat
 *
 * Created on April 5, 2023, 1:07 PM
 */


#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
unsigned char dem;
int main(void){
       DDRB=0xFF;                //PORTB la output PORT
       //PORTB=1;
       //DDRC=0xff;

       TCCR0 |=(1<<CS01);// CS02=0, CS01=1, CS00=0: chon Prescaler = 8
//       TCNT0=193;              //gan gia tri khoi tao cho T/C0
      TIMSK |=(1<<TOIE0);//cho phep ngat khi co tran o T/C0
       sei();                       //set bit I cho phep ngat toan cuc

       while (1){           //vòng l?p vô t?n 
              //do nothing
   
       }
       return 0;
}

//trinh phuc vu ngat tran T/C0
ISR (TIMER0_OVF_vect ){ 
    if(PORTB==0)
        {  
        PORTB=1; //doi trang thai Bit PB0
        TCNT0=230; //gan gia tri khoi tao cho T/C0
        }
        else 
        {  TCNT0=155; //gan gia tri khoi tao cho T/C0
       PORTB=0; //doi trang thai Bit PB0
        }
      //dem++; 
      //if(dem==200){PORTC++;dem=0;if(PORTC==10)PORTC=0;}
}
