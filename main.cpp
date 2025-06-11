#include <stdio.h>
#include <stdbool.h>
#include "hal/gpio_api.h"
#include "PinNames.h"
#include "arm_book_lib.h"   

int main(void)
{
    gpio_t gasDetector;
    gpio_t overTempDetector;
    gpio_t alarmOffButton;
    gpio_t alarmLed;

    // Reemplaza: DigitalIn gasDetector(D2);
    gpio_init_in(&gasDetector, D2);
    gpio_mode(&gasDetector, PullDown);  // Reemplaza: gasDetector.mode(PullDown);

    // Reemplaza: DigitalIn overTempDetector(D3);
    gpio_init_in(&overTempDetector, D3);
    gpio_mode(&overTempDetector, PullDown);  // Reemplaza: overTempDetector.mode(PullDown);

    // Reemplaza: DigitalIn alarmOffButton(BUTTON1);
    gpio_init_in(&alarmOffButton, BUTTON1);

    // Reemplaza: DigitalOut alarmLed(LED1);
    gpio_init_out_ex(&alarmLed, LED1, OFF);

    // Reemplaza: bool alarmState = OFF;
    bool alarmState = OFF;

    while (true) {

        // Reemplaza: if ( gasDetector || overTempDetector )
        if (gpio_read(&gasDetector) || gpio_read(&overTempDetector)) {
            printf("Escape de gas o sobre-temperatura detectada.\n");
            alarmState = ON;
        }
 
        // Reemplaza: alarmLed = alarmState;
        gpio_write(&alarmLed, alarmState);

        // Reemplaza: if ( alarmOffButton )
        if (gpio_read(&alarmOffButton)) {
            printf("Todo en orden.\n");
            alarmState = OFF;
        }

        // Agregado
        delay(100);
    }
}