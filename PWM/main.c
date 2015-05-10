/*
 * main.c
 *
 *  Created on: 3 maj 2015
 *      Author: Kuba
 */

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define LED1 PB1
#define LED2 PB5
#define PWM PB3

void PWM_Init()
{
    TCCR2 |= (1<<WGM21)|(1<<WGM20)|(1<<COM21)|(0<<COM20)|(1<<CS20); //wlaczenie fast pwm, non inverting mode pomiedzy 0 a OCR2 sygnal 0, preskaler 0
    //TIMSK |= (1<<TOIE2)|(1<<OCIE2);

}

int main()
{
    //PWM_Init();

    DDRB |= _BV(PWM); //tu jest PWM na timerze 2
    DDRB |= _BV(LED2); //wyjscie na leda
    DDRB |= _BV(LED1);

    sei();
    int licznik=0;

   // OCR2 = licznik;
    while(1)
    {
    	_delay_ms(1);
        PORTB ^= _BV(LED1);
    }

}
