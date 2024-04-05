#include "mbed.h"
#include "arm_book_lib.h"
//La ventaja de usar C en vez de C++ es que nos permite obtener un mejor entendimiento 
//A bajo nivel de los cambios que se estan llevando a cabo al desprendernos de las abstracciones
//asociadas al uso de clases en C++ 

int main()
{
    // DigitalIn gasDetector(D2);
    // DigitalIn overTempDetector(D3);
    // DigitalIn alarmOffButton(BUTTON1);
    
    //DigitalOut alarmLed(LED1);

    //gasDetector.mode(PullDown);
    //overTempDetector.mode(PullDown);

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