/*
 * LCD_projekt.c
 *
 * Created: 2015-07-01 15:57:10
 *  Author: Ludvig
 */ 

#define F_CPU 800000UL

#include <avr/io.h>
#include "lcd_lib.h"
#include <inttypes.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include "lcd_lib.h"
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

//----------------------Funktioner------------------------
void init_LCD()
{
	const char lcd_text[] = "ADC value:";
	LCDinit();
	_delay_ms(1000);
	LCDclr();
	_delay_ms(1000);
	LCDhome();
	_delay_ms(1000);
	LCDstring((uint8_t*) lcd_text, (uint8_t) strlen(lcd_text));
	_delay_ms(1000);
	LCDvisible();
}

void init_ADC()
{
	DDRC &= ~(1<<PC3); //Set PC3 to input
	ADMUX |= (1<<3); //| (1<<REFS0); // mux PC3 to adc input
	ADCSRA |= (1<<ADEN) | (1<<ADPS2) | (1<<ADPS1); // Enable adc and set prescaler to 64
	
}


int read_ADC()
{
	uint16_t value=0;
	ADCSRA |= (1<<ADSC);
	while(ADCSRA & (1<<ADSC)); // Wait for adc to finish
	
	value = ADCL;
	value |= (ADCH<<8);
	
	return value;
}

int main(void)
{
	/* Variables */
	uint16_t ad_value = 0;
    char ad_value_text[8];
	
	init_LCD();
	init_ADC();
	
	DDRD = 0xFF;
	PORTD = 0;
	
    while(1)
    {
		ad_value = read_ADC();
		itoa(ad_value,ad_value_text,10);
		LCDGotoXY(0,1);
		LCDstring((uint8_t*) ad_value_text, (uint8_t) strlen(ad_value_text));
		
    }
}