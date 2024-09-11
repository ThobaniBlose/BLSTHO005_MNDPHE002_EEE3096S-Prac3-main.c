//********************************************************************
//*                    EEE2046F C template                           *
//*==================================================================*
//* WRITTEN BY: Jesse Arendse   	                 		               *
//* DATE CREATED: 07/04/2023                                         *
//* MODIFIED:                                                        *
//*==================================================================*
//* PROGRAMMED IN: Visual Studio Code                                *
//* TARGET:        STM32F0                                           *
//*==================================================================*
//* DESCRIPTION:                                                     *
//*                                                                  *
//********************************************************************
// INCLUDE FILES
//====================================================================
#include <stdio.h>
#include "stm32f0xx.h"
#include <stdint.h>
#include <stdbool.h> 

#define DELAY1 950
#define DELAY2 1000

uint32_t bitpattern1 = 0x00000000;
uint32_t bitpattern2 = 0x000000FF;
uint32_t bitpattern3 = 0x000000AA;

typedef uint8_t flag_t;
volatile flag_t startflag = FALSE;
volatile flag_t firstflag = FALSE;
volatile flag_t secondflag = FALSE;
volatile flag_t thirdflag = FALSE;

void initGPIO(void);
void Delay(void);
void firstDisplay(void);
void secondDisplay(void);
void thirdDisplay(void);
void checkPB(void);
void display(void);

int main(void) {
    initGPIO();

    for (;;) {
        checkPB();
        display();
    }

    return 1;
}

void initGPIO(void) {
    RCC->AHBENR |= RCC_AHBENR_GPIOBEN;
    GPIOB->MODER |= GPIO_MODER_MODER0_0 | GPIO_MODER_MODER1_0 | GPIO_MODER_MODER2_0 |
                    GPIO_MODER_MODER3_0 | GPIO_MODER_MODER4_0 | GPIO_MODER_MODER5_0 |
                    GPIO_MODER_MODER6_0 | GPIO_MODER_MODER7_0;

    RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
    GPIOA->MODER &= ~(GPIO_MODER_MODER0 | GPIO_MODER_MODER1 | GPIO_MODER_MODER2 | GPIO_MODER_MODER3);
    GPIOA->PUPDR |= GPIO_PUPDR_PUPDR0_0 | GPIO_PUPDR_PUPDR1_0 | GPIO_PUPDR_PUPDR2_0 | GPIO_PUPDR_PUPDR3_0;
}

void Delay(void) {
    volatile int i, j;
    for (i = 0; i <= DELAY1; i++) {
        for (j = 0; j <= DELAY2; j++) {}
    }
}

void firstDisplay(void) {
    while (firstflag) {
        GPIOB->ODR = bitpattern1;
        Delay();
        GPIOB->ODR = bitpattern2;
        Delay();
        GPIOB->ODR = bitpattern3;
        Delay();
    }
}

void secondDisplay(void) {
    while (secondflag) {
        GPIOB->ODR = 0x01;
        Delay();
        GPIOB->ODR = 0x02;
        Delay();
        GPIOB->ODR = 0x04;
        Delay();
        GPIOB->ODR = 0x08;
        Delay();
        GPIOB->ODR = 0x10;
        Delay();
        GPIOB->ODR = 0x20;
        Delay();
        GPIOB->ODR = 0x40;
        Delay();
        GPIOB->ODR = 0x80;
        Delay();
    }
}

void thirdDisplay(void) {
    while (thirdflag) {
        volatile int i;
        for (i = 0; i < 256; i++) {
            GPIOB->ODR = i;
            Delay();
        }
    }
}

void checkPB(void) {
    if (!GPIOA->IDR & GPIO_IDR_0) {
        startflag = TRUE;
        firstflag = FALSE;
        secondflag = FALSE;
        thirdflag = FALSE;
    } else if (!GPIOA->IDR & GPIO_IDR_1) {
        startflag = TRUE;
        firstflag = TRUE;
        secondflag = FALSE;
        thirdflag = FALSE;
    } else if (!GPIOA->IDR & GPIO_IDR_2) {
        startflag = TRUE;
        firstflag = FALSE;
        secondflag = TRUE;
        thirdflag = FALSE;
    } else if (!GPIOA->IDR & GPIO_IDR_3) {
        startflag = TRUE;
        firstflag = FALSE;
        secondflag = FALSE;
        thirdflag = TRUE;
    }
}

void display(void) {
    if (startflag) {
        GPIOB->ODR = 0x01;
        if (firstflag) {
            firstDisplay();
        } else if (secondflag) {
            secondDisplay();
        } else if (thirdflag) {
            thirdDisplay();
        }           
    } else {
        GPIOB->ODR = 0x00;
        startflag = FALSE;
    }
}
