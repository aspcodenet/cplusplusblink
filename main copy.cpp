#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdbool.h>

// https://wokwi.com/projects/365047092561218561

// PORTB B (digital pin 8 to 13)
// C (analog input pins)
// PORTD D (digital pins 0 to 7)
#define LED_PIN 2
#define BUTTON_PIN 1

#define BIT_SET(a, b) ((a) |= (1ULL << (b)))
#define BIT_CLEAR(a,b) ((a) &= ~(1ULL<<(b)))
#define BIT_FLIP(a,b) ((a) ^= (1ULL<<(b)))
#define BIT_CHECK(a,b) (!!((a) & (1ULL<<(b)))) 


#define BUTTON_IS_CLICKED(PINB,BUTTON_PIN) !BIT_CHECK(PINB,BUTTON_PIN)

int main(void){
    BIT_SET(DDRB,LED_PIN); //OUTPUT MODE

    // //Sätt till INPUT_PULLUP
    // BIT_CLEAR(DDRB,BUTTON_PIN); // INPUT MODE
    // BIT_SET(PORTB,BUTTON_PIN); 

    // DATA DIRECTION = avgör mode
    // om output så skickar vi  1 eller 0 på motsvarande pinne på PORT
    // om input så läser vi  1 eller 0 på motsvarande pinne på PIN
    //bool blinking = false;
    while(1){
        BIT_SET(PORTB,LED_PIN);        
        _delay_ms(1000);
        BIT_CLEAR(PORTB,LED_PIN);
        _delay_ms(1000);
        // if(!BIT_CHECK(PINB,BUTTON_PIN)){ 
        //     _delay_ms(100); //Delay = vi ska göra bättre debouncing senare!
        //     printf("Clicking");
        //     blinking = !blinking;
        //     if(blinking)   
        //         BIT_SET(PORTB,LED_PIN);
        //     else
        //         BIT_CLEAR(PORTB,LED_PIN);
        //     antalMilliSekunderSenasteBytet = millis_get();
        // }
        // millis_t s = millis_get() - antalMilliSekunderSenasteBytet;

        // if(blinking && (s > 300 )){
        //     BIT_FLIP(PORTB,LED_PIN);
        //     antalMilliSekunderSenasteBytet = millis_get();
        // }
    }
    return 0;
}
