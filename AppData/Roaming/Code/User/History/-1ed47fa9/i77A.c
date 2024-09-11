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
#include <stm32f0xx.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

// Your bit patterns
uint32_t bitpattern1 = 0x00000000;
uint32_t bitpattern2 = 0x000000FF;
uint32_t bitpattern3 = 0x000000AA;

typedef uint8_t flag_t;
volatile flag_t startflag = 0;
volatile flag_t firstflag = 0;
volatile flag_t secondflag = 0;
volatile flag_t thirdflag = 0;

// Function declarations
void initGPIO(void);
void delay(void);
void firstDisplay(void);
void secondDisplay(void);
void thirdDisplay(void);
void checkPD(void);
void display(void);

int main(void) {
    initGPIO();
    for(;;) {
        checkPD();
        display();
    }
}

void firstDisplay(void) {
    while (firstflag) {
        GPIOB->ODR = bitpattern1;
        delay();
        GPIOB->ODR = bitpattern2;
        delay();
        GPIOB->ODR = bitpattern3;
        delay();
        checkPD();
    }  
}

void secondDisplay(void) {
    while (secondflag) {
        GPIOB->ODR = 0x00000001;
        delay();
        GPIOB->ODR = 0x00000002;
        delay();
        GPIOB->ODR = 0x00000004;
        delay();
        GPIOB->ODR = 0x00000008;
        delay();
        GPIOB->ODR = 0x00000010;
        delay();
        GPIOB->ODR = 0x00000020;
        delay();
        GPIOB->ODR = 0x00000040;
        delay();
        GPIOB->ODR = 0x00000080;
        delay();
        checkPD();
    }
}

void thirdDisplay(void) {
    while (thirdflag) {
        volatile int i;
        GPIOB->ODR = 0x00000000;
        delay();
        for (i = 0; i < 256; i++) {
            GPIOB->ODR += 1;
            delay();
            checkPD();
        }
    }
}

void checkPD(void) {
    if (!GPIOA->IDR & GPIO_IDR_0) {
        startflag = 1;
        firstflag = 0;
        secondflag = 0;
        thirdflag = 0;
    } else if (!GPIOA->IDR & GPIO_IDR_1) {
        startflag = 1;
        firstflag = 1;
        secondflag = 0;
        thirdflag = 0;
    } else if (!GPIOA->IDR & GPIO_IDR_2) {
        startflag = 1;
        firstflag = 0;
        secondflag = 1;
        thirdflag = 0;
    } else if ((!GPIOA->IDR & GPIO_IDR_3)) {
        startflag = 1;
        firstflag = 0;
        secondflag = 0;
        thirdflag = 1;
    }
}

void display(void) {
    if (startflag) {
        GPIOB->ODR = 0x00000001;
        if (firstflag) {
            firstDisplay();
        } else if (secondflag) {
            secondDisplay();
        } else if (thirdflag) {
            thirdDisplay();
        }           
    } else {
        GPIOB->ODR = 0x00000000;
        startflag = 0;
    }
}

void delay(void) { 
    volatile int i, j;
    for (i = 0; i <= 9; i++) {
        for (j = 0; j <= 65535; j++);
    }
}

void initGPIO(void) {
    RCC->AHBENR |= RCC_AHBENR_GPIOBEN;
    GPIOB->MODER |= GPIO_MODER_MODER0_0 | GPIO_MODER_MODER1_0 | GPIO_MODER_MODER2_0 |
                    GPIO_MODER_MODER3_0 | GPIO_MODER_MODER4_0 | GPIO_MODER_MODER5_0 |
                    GPIO_MODER_MODER6_0 | GPIO_MODER_MODER7_0;

    GPIOB->ODR &= ~0xFF; // Turn off LEDs initially

    RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
    GPIOA->MODER &= ~(GPIO_MODER_MODER0 | GPIO_MODER_MODER1 | GPIO_MODER_MODER2 | GPIO_MODER_MODER3);
    GPIOA->PUPDR |= GPIO_PUPDR_PUPDR0_0 | GPIO_PUPDR_PUPDR1_0 | GPIO_PUPDR_PUPDR2_0 | GPIO_PUPDR_PUPDR3_0;
}
