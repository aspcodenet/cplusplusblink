#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include "lcd.h"
#include "AnalogPin.h"
#include "millis.h"

// https://wokwi.com/projects/365067824797777921

// B (digital pin 8 to 13)
// C (analog input pins)
// D (digital pins 0 to 7)
#define LED_PIN 2
#define BUTTON_PIN 1




#define BUTTON_IS_CLICKED(PINB,BUTTON_PIN) !BIT_CHECK(PINB,BUTTON_PIN)

int main(void){

    HD44780 lcd;
    lcd.GoTo(0,0);
    lcd.WriteText("Tjena moss ");

    Ntc ntc(AnalogPin(0));

    millis_init();
    sei();

    char text[20];
    char *ch1 = "Tjena ";
    char *ch2 = "Moss  ";
    char *message = ch1;

    millis_t millis = millis_get();

    lcd.Clear();
    while(1){
		//uint16_t value = ntc.analogRead(); // 0 - 1023
        int d = (int)(ntc.getTemp() * 100)/100; //5.23 523
        sprintf(text, "%d     ", d);
        lcd.GoTo(0,0);
        lcd.WriteText(text);
        _delay_ms(1000);
        millis_t current = millis_get();
        sprintf(text, "%d ", current - millis);
        if(current - millis > 10000){
            if(message == ch1)
                message = ch2;
            else
                message = ch1;
            millis = current;
        }
        
        lcd.GoTo(0,1);
        lcd.WriteText(message);

    }
    return 0;
}
