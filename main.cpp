#include "mbed.h"
#include "arm_book_lib.h"

int main()
{
    DigitalIn gasDetector(D2);
    DigitalIn overTempDetector(D3);
    DigitalIn alarmOffButton(BUTTON1);

    DigitalOut alarmLed(LED1);

    gasDetector.mode(PullDown);
    overTempDetector.mode(PullDown);

    alarmLed = OFF;

    bool alarmState = OFF;

    while (true) {

        if ( gasDetector || overTempDetector ) {
            printf("%s\n", "Escape de gas o sobre-temperatura detectada.");
            alarmState = ON;
        }

        alarmLed = alarmState;

        if ( alarmOffButton ) {
            printf("%s\n", "Todo en orden.");
            alarmState = OFF;
        }
    }
}