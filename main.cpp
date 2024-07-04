#include "mbed.h"
#include "arm_book_lib.h"
//La ventaja de usar C en vez de C++ es que nos permite obtener un mejor entendimiento 
//A bajo nivel de los cambios que se estan llevando a cabo al desprendernos de las abstracciones
//asociadas al uso de clases en C++ 
#include "hal/gpio_api.h"

//Para C:
#define PIN_ALARM PB_0
#define PIN_GAS PF_15
#define PIN_TEMP PE_13
#define PIN_BOTON PC_13


#define C_
//#define C_MASMAS
void inicializar_pin_sal(gpio_t *obj, PinName pin){
    gpio_init_out(obj, pin);
}

void inicializar_pin_ent(gpio_t *obj, PinName pin){
    gpio_init_in(obj, pin);
}

void inicializar_pin_ent_modo(gpio_t *obj, PinName pin,PinMode modo){
    gpio_init_in_ex(obj, pin,modo);
}

int leer_entrada(gpio_t *obj){
    return gpio_read(obj);
}
 
void escribir_pin(gpio_t *obj, int value){
    gpio_write(obj, value);
} 
#ifdef C_MASMAS
int main()
{
    
    DigitalIn gasDetector(D2);
    DigitalIn overTempDetector(D3);
    DigitalIn alarmOffButton(BUTTON1);
    
    DigitalOut alarmLed(LED1);

    gasDetector.mode(PullDown);
    overTempDetector.mode(PullDown);

    alarmLed = 0;

    bool alarmState = 0;
    while (true) {

        if ( gasDetector || overTempDetector ) {
            printf("%s\n", "Escape de gas o sobre-temperatura detectada.");
            alarmState = 1;
        }

        alarmLed = alarmState;

        if ( alarmOffButton ) {
            printf("%s\n", "Todo en orden.");
            alarmState = 0;
        }
    }
}

#endif

#ifdef C_  //Aca va el mismo programa pero implementado en C
//Para este caso se utilizan las funciones de la biblioteca gpio_api para manejar los puerto GPIO

int main()
{
 gpio_t gpio_gas;   
 gpio_t gpio_temp; 
 gpio_t led;
 gpio_t boton;
 inicializar_pin_ent_modo(&gpio_gas ,PIN_GAS,PullDown);
 inicializar_pin_ent_modo(&gpio_temp ,PIN_TEMP,PullDown);
 inicializar_pin_ent(&boton ,BUTTON1);
 inicializar_pin_sal(&led,PIN_ALARM);

// DigitalIn alarmOffButton(BUTTON1);
 int EstadoAlarma = OFF;
 int detecto_gas = 0;
 int sobre_temp = 0;
int estado_boton = 0;

 while(1){
    detecto_gas = leer_entrada(&gpio_gas);
    sobre_temp = leer_entrada(&gpio_temp);
    estado_boton = leer_entrada(&boton);
    if(detecto_gas||sobre_temp){
    printf("Escape de gas o sobre-temperatura detectada.\n");
    EstadoAlarma = ON;
    escribir_pin(&led,EstadoAlarma);
    }
    
    if(estado_boton){
        printf("Alarma apagada");
        EstadoAlarma = OFF;
        escribir_pin(&led,EstadoAlarma);
    }
  }
}


//typedef struct {
  //  uint32_t mask;
    //__IO uint32_t *reg_in;
  //  __IO uint32_t *reg_set;
   // __IO uint32_t *reg_clr;
  ////  PinName  pin;
   // GPIO_TypeDef *gpio;
 //   uint32_t ll_pin;
//} gpio_t;

#endif