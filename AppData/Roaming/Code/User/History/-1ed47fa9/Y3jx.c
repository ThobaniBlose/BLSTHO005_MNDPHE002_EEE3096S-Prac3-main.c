#include <stdio.h>
#include "stm32f0xx.h"
#include <lcd_stm32f0.c>
#include <stdint.h>

#define DELAY1 950
#define DELAY2 1000

typedef uint8_t flag_t;
flag_t startFlag = FALSE;
flag_t firstFlag = FALSE;
flag_t secondFlag = FALSE;
flag_t thirdFlag = FALSE;

char bitpattern1 = 0b00000000;
char bitpattern2 = 0b11111111;
char bitpattern3 = 0b10101010;

void initGPIO(void);
void Delay(void);
void firstDisplay(void);
void secondDisplay(void);
void thirdDisplay(void);
void checkPB(void);
void display(void);

int main(void) {
    init_LCD();
    lcd_command(CLEAR);
    lcd_putstring("BLSTHO005");
    lcd_command(LINE_TWO);
    lcd_putstring("EEE2046F Prac4");

    initGPIO();
    while ((GPIOA->IDR & GPIO_IDR_0) != 0) {}

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
    while (firstFlag) {
        GPIOB->ODR = 0b00000000;
        Delay();
        GPIOB->ODR = bitpattern1;
        Delay();
        GPIOB->ODR = 0b00000000;
        Delay();
        GPIOB->ODR = bitpattern2;
        Delay();
        GPIOB->ODR = 0b00000000;
        Delay();
        GPIOB->ODR = bitpattern3;
        Delay();
    }
}

void secondDisplay(void) {
    while (secondFlag) {
        GPIOB->ODR = 0x00;
        Delay();
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
    while (thirdFlag) {
        volatile int i;
        for (i = 0; i <= 255; i++) {
            GPIOB->ODR = i;
            Delay();
        }
    }
}

void checkPB(void) {
    if ((GPIOA->IDR & GPIO_IDR_0) == 0) {
        startFlag = TRUE;
        firstFlag = FALSE;
        secondFlag = FALSE;
        thirdFlag = FALSE;
    } else if ((GPIOA->IDR & GPIO_IDR_1) == 0) {
        startFlag = TRUE;
        firstFlag = TRUE;
        secondFlag = FALSE;
        thirdFlag = FALSE;
    } else if ((GPIOA->IDR & GPIO_IDR_2) == 0) {
        startFlag = TRUE;
        firstFlag = FALSE;
        secondFlag = TRUE;
        thirdFlag = FALSE;
    } else if ((GPIOA->IDR & GPIO_IDR_3) == 0) {
        startFlag = TRUE;
        firstFlag = FALSE;
        secondFlag = FALSE;
        thirdFlag = TRUE;
    }
}

void display(void) {
    if (startFlag) {
        if (firstFlag) {
            firstDisplay();
        } else if (secondFlag) {
            secondDisplay();
        } else if (thirdFlag) {
            thirdDisplay();
        }
    } else {
        GPIOB->ODR = 0x00; // Turn off LEDs if no flags are set
    }
}
