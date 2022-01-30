#include "stm8s.h"
#include "milis.h"

/*#include "delay.h"*/
#include <stdio.h>
#include "uart1.h"
#include "swi2c.h"

#define _ISOC99_SOURCE
#define _GNU_SOURCE

#define LED_PORT GPIOC
#define LED_PIN  GPIO_PIN_5
#define LED_HIGH   GPIO_WriteHigh(LED_PORT, LED_PIN)
#define LED_LOW  GPIO_WriteLow(LED_PORT, LED_PIN)
#define LED_REVERSE GPIO_WriteReverse(LED_PORT, LED_PIN)

#define BTN_PORT GPIOE
#define BTN_PIN  GPIO_PIN_4
#define BTN_PUSH (GPIO_ReadInputPin(BTN_PORT, BTN_PIN)==RESET) 


void setup(void)
{
    CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);      // taktovani MCU na 16MHz
    GPIO_Init(LED_PORT, LED_PIN, GPIO_MODE_OUT_PP_LOW_SLOW);
    GPIO_Init(BTN_PORT, BTN_PIN, GPIO_MODE_IN_FL_NO_IT);


    init_milis();
    init_uart1();
    swi2c_init();
}


int main(void)
{
    uint32_t time = 0;
    uint8_t precteno[10] = {0,0,0,0,0,0,0,0,0,0};
    uint8_t zapsano[10] = {0,0,0,0,0,0,0,0,0,0};
    uint8_t err;
    uint16_t *pteplota;
    uint8_t teplota;
    uint8_t desetina;


    setup();

    /*error=swi2c_read_buf(0b11010000,0x00,precteno,4) */
    zapsano[0] = 0x40;  // sekundy
    zapsano[1] = 0x25;  // minuty
    zapsano[2] = 0x13;  // hodiny
    zapsano[3] = 0x05;  // den v týdnu
    zapsano[4] = 0x28;  // den
    zapsano[5] = 0x01;  // měsíc
    zapsano[6] = 0x22;  // rok

    // když tento řádek odkomentuješ, tak se čas zapíše do obvodu
    //printf("ErrorCode: %X\n",  swi2c_write_buf(0x68, 0x00, zapsano, 7));

    printf("\nScan:\n");
    for (uint8_t addr = 0; addr < 128; addr++) {
        if (swi2c_test_slave(addr) == 0) {
            printf("%02X\n", addr);
        }
    }
    printf("---------------------------------\n");
    


    LED_REVERSE;

    while (1) {
        if (milis() - time > 1111 /*&& BTN_PUSH*/) {

            LED_REVERSE;

            // čtu RTC
            err = swi2c_read_buf(0x68, 0x00, precteno, 7);

            printf("%d%d.%d%d. 20%d%d %d%d:%d%d:%d%d ",       // v RTC obvodu je čas uložen v BCD
                   precteno[4] >> 4, precteno[4] & 0x0F,
                   precteno[5] >> 4, precteno[5] & 0x0F,
                   precteno[6] >> 4, precteno[6] & 0x0F,
                   precteno[2] >> 4, precteno[2] & 0x0F,
                   precteno[1] >> 4, precteno[1] & 0x0F,
                   precteno[0] >> 4, precteno[0] & 0x0F);

            // čtu Teploměr
            err = swi2c_read_buf(0x48, 0x00, precteno, 2);
            pteplota = (uint16_t *) precteno;
            teplota = precteno[0];
            if (precteno[1] & 0b1000000) {
                desetina = 5; 
            } else {
                desetina = 0; 
            }

            printf("%d.%d°C\n", teplota, desetina);


            time = milis();
        }
    }
}

/*-------------------------------  Assert -----------------------------------*/
#include "__assert__.h"
