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
#include "stm32f0xx.h"
#include <lcd_stm32f0.c>
#include <stdio.h>

// Delay
#define DELAY1 800
#define DELAY2 1200
#define TRUE 1
#define FALSE 0
#define MAX_VALUE 255 // Define the maximum value for an 8-bit counter
#define SW0 (GPIOA -> IDR | (GPIO_IDR_0))
#define SW1 (GPIOA -> IDR | (GPIO_IDR_1))
#define SW2 (GPIOA -> IDR | (GPIO_IDR_2))
#define SW3 (GPIOA -> IDR | (GPIO_IDR_3))

// Bitpattern
uint16_t bitpattern1 = 0x0000;
uint16_t bitpattern2 = 0xFFFF;
uint16_t bitpattern3 = ~(uint16_t)0xAA55;
typedef uint8_t flag_t;

//  Variables
flag_t startFlag = FALSE;
flag_t firstFlag = FALSE;
flag_t secondFlag = FALSE;
flag_t thirdFlag = FALSE;

// Function initialization
void initGPIO(void);
void Delay(void);
void firstDisplay(void);
void secondDisplay(void);
void thirdDisplay(void);
void display(void);
//====================================================================
// MAIN FUNCTION
//====================================================================
void helloWorld(){
    init_LCD();
    lcd_command(CLEAR);
    lcd_putstring("GOAT!");
    lcd_command(LINE_TWO);
    lcd_putstring("Thobani Blose");

}
int main(void) {
    initGPIO(); // Initialize GPIO
    helloWorld();  // Initialize LCD
    
    while (SW0) {
        checkPB();  // Check button states
        display();  // Update LED displays based on button states
    }
    return 0;
}
				// End of main
//====================================================================
// FUNCTION DEFINITIONS
//====================================================================
void initGPIO(void){
    RCC -> AHBENR |= RCC_AHBENR_GPIOBEN;
    RCC -> AHBENR |= RCC_AHBENR_GPIOAEN;
    GPIOA-> PUPDR = 0b01010101; // Enable pull-up resistors for all pins in GPIOB
    GPIOA -> MODER &= ~(0b11111111);
    GPIOB -> MODER |= GPIO_MODER_MODER0_0 | GPIO_MODER_MODER1_0 | GPIO_MODER_MODER2_0 |GPIO_MODER_MODER3_0 | GPIO_MODER_MODER4_0 |
                       GPIO_MODER_MODER5_0 | GPIO_MODER_MODER6_0 | GPIO_MODER_MODER7_0 ;
    GPIOB -> PUPDR &= ~(GPIO_PUPDR_PUPDR0);
}
void Delay(void){
    volatile int i,j;
    for (i=0; i <= DELAY1; ++i){
        for (j=0; j <= DELAY2; ++j);
    }
}
void firstDisplay(void){
    while(1){
        GPIOB -> ODR = bitpattern1;
        Delay();
        GPIOB -> ODR = bitpattern2;
        Delay();
        GPIOB -> ODR = bitpattern3;
        Delay();
        break;
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
    flag_t counter = 0; // Initialize the counter to 0
    while(TRUE){
        while(counter <= MAX_VALUE){
            GPIOB->ODR = counter;
            Delay(); // Delay approximately 1 second
            counter++; // Increment the counter
        }
        counter = 0; // Reset the counter to 0 when it reaches the maximum value
    }
}
void checkPB(void) {
    if (SW0) {
        startFlag = TRUE;
        firstFlag = FALSE;
        secondFlag = FALSE;
        thirdFlag = FALSE;
    } else if (SW1) {
        startFlag = TRUE;
        firstFlag = TRUE;
        secondFlag = FALSE;
        thirdFlag = FALSE;
    } else if (SW2) {
        startFlag = TRUE;
        firstFlag = FALSE;
        secondFlag = TRUE;
        thirdFlag = FALSE;
    } else if (SW3) {
        startFlag = TRUE;
        firstFlag = FALSE;
        secondFlag = FALSE;
        thirdFlag = TRUE;
    }
}
void display(void)
{
    if ((startFlag == TRUE) & (firstFlag == FALSE) & (secondFlag == FALSE) & (thirdFlag == FALSE))
    {   
        GPIOB -> ODR =  0b00000001;
    }
    if ((startFlag == TRUE) & (firstFlag == TRUE) & (secondFlag == FALSE) & (thirdFlag == FALSE))
    {   
        firstDisplay();
    }    
    if ((startFlag == TRUE) & (firstFlag == FALSE) & (secondFlag == TRUE) & (thirdFlag == FALSE))
    {   
        secondDisplay();
    }    
    if ((startFlag == TRUE) & (firstFlag == FALSE) & (secondFlag == FALSE) & (thirdFlag == TRUE))
    {  
        thirdDisplay();
    }     
}

//********************************************************************
// END OF PROGRAM
//********************************************************************