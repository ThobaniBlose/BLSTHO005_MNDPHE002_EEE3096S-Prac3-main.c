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
#include <lcd_stm32f0.c>
#include <stdint.h>
//====================================================================
// GLOBAL CONSTANTS
//====================================================================
// 1s = 1000 ms
# define DELAY1 950
# define DELAY2 1000
# define TRUE 1
# define FALSE 0
//====================================================================
// GLOBAL VARIABLES
//====================================================================
char bitpattern1 = 0b00000000;
char bitpattern2 = 0b11111111;
char bitpattern3 = 0b10101010;

typedef uint8_t flag_t; // New variable type (8 bit unsigned integer)
flag_t startFlag = 0;
flag_t firstFlag = 0;
flag_t secondFlag = 0;
flag_t thirdFlag = 0;
//====================================================================
// FUNCTION DECLARATIONS
void initGPIO(void);
void Delay(void);
void firstDisplay(void);
void secondDisplay(void);
void thirdDisplay(void);
void checkPB(void);
void display(void);
//====================================================================
//====================================================================
// MAIN FUNCTION
//====================================================================
int main (void){
    init_LCD();                     // Initialize lcd
    lcd_command(CLEAR);
    lcd_putstring("BLSTHO005");
    lcd_command(LINE_TWO);
    lcd_putstring("EEE2046F Prac4");

    initGPIO();
    while((GPIOA->IDR & GPIO_IDR_0) != 0){
    }
        for (;;)
        {
            checkPB();
            display();       
        }
        return 1;
}							// End of main

//====================================================================
// FUNCTION DEFINITIONS
//====================================================================
void initGPIO(void){
    // Initializes GPIOB and RCC
    RCC  ->AHBENR |=RCC_AHBENR_GPIOBEN;
    GPIOB->MODER  |= 0x00005555;
    GPIOB->ODR    = 0b00000000;

    //initialize GPIOA and RCC
	RCC  ->AHBENR |= RCC_AHBENR_GPIOAEN;
	GPIOA->MODER  &= ~(GPIO_MODER_MODER0 | GPIO_MODER_MODER1 | GPIO_MODER_MODER2 | GPIO_MODER_MODER3);
	GPIOA->PUPDR  |= (GPIO_PUPDR_PUPDR0_0 | GPIO_PUPDR_PUPDR1_0 | GPIO_PUPDR_PUPDR2_0 | GPIO_PUPDR_PUPDR3_0);
}
void Delay(void){
    volatile int i,j;
    for(i = 0; i <= DELAY1; i++){
        for(j = 0; j <= DELAY2; j++)
        {}
    }
}
void firstDisplay(void){
    while(1){
        GPIOB -> ODR &= 0b0;
        GPIOB -> ODR |= bitpattern1;
        Delay();
        GPIOB -> ODR &= 0b0;
        GPIOB -> ODR |= bitpattern2;
        Delay();
        GPIOB -> ODR &= 0b0;
        GPIOB -> ODR |= bitpattern3;
        Delay();
    }
}
void secondDisplay(void){
    while(TRUE){
    GPIOB->ODR = 0x01;          // Set only the first bit (bit 0) to 1
    Delay();
    GPIOB->ODR = 0x02;          // Set only the second bit (bit 1) to 1
    Delay();
    GPIOB->ODR = 0x04;          // Set only the third bit (bit 2) to 1
    Delay();
    GPIOB->ODR = 0x08;          // Set only the fourth bit (bit 3) to 1
    Delay();
    GPIOB->ODR = 0x10;          // Set only the fifth bit (bit 4) to 1
    Delay();
    GPIOB->ODR = 0x20;          // Set only the sixth bit (bit 5) to 1
    Delay();
    GPIOB->ODR = 0x40;          // Set only the seventh bit (bit 6) to 1
    Delay();
    GPIOB->ODR = 0x80;          // Set only the eighth bit (bit 7) to 1
    Delay();
    }
}

void thirdDisplay(void){
    while (1){
        volatile int i;
        for (i=0; i<=255; i++){
            GPIOB -> ODR = i;
            Delay();
        }
    }
}
// Check pressed button
void checkPB(void){
    if ((GPIOA->IDR & GPIO_IDR_0) == 0){
        startFlag = TRUE;
        firstFlag = FALSE;
        secondFlag = FALSE;
        thirdFlag = FALSE;
    }
    if ((GPIOA->IDR & GPIO_IDR_1) == 0){
        startFlag = TRUE;
        firstFlag = TRUE;
        secondFlag = FALSE;
        thirdFlag = FALSE;
    }
    if ((GPIOA->IDR & GPIO_IDR_2) == 0){
        startFlag = TRUE;
        firstFlag = FALSE;
        secondFlag = TRUE;
        thirdFlag = FALSE;
    }
    if ((GPIOA->IDR & GPIO_IDR_3) == 0){ 
        startFlag = TRUE;
        firstFlag = FALSE;
        secondFlag = FALSE;
        thirdFlag = TRUE;
    }
}

void display(void)
{
    if ((startFlag == TRUE) && (firstFlag == FALSE) && (secondFlag == FALSE) && (thirdFlag == FALSE))
    {   
        GPIOB -> ODR =  0b00000001;
    }
    else if((startFlag == TRUE) && (firstFlag == TRUE) && (secondFlag == FALSE) && (thirdFlag == FALSE))
    {   
        firstDisplay();
    }    
    else if((startFlag == TRUE) && (firstFlag == FALSE) && (secondFlag == TRUE) && (thirdFlag == FALSE))
    {   
        secondDisplay();
    }    
    else if((startFlag == TRUE) && (firstFlag == FALSE) && (secondFlag == FALSE) && (thirdFlag == TRUE))
    {  
        thirdDisplay();
    }     
}
//********************************************************************
// END OF PROGRAM
//********************************************************************
