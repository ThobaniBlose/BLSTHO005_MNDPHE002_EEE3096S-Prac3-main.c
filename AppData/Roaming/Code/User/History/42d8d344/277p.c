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

//====================================================================
// GLOBAL CONSTANTS
//====================================================================
#define SW0 !((GPIOA->IDR)&GPIO_IDR_0)
#define SW1 !((GPIOA->IDR)&GPIO_IDR_1)
#define SW2 !((GPIOA->IDR)&GPIO_IDR_2)
#define SW3 !((GPIOA->IDR)&GPIO_IDR_3)

// 1s = 1000 ms
# define DELAY1 950
# define DELAY2 1000
#define FALSE 0
#define TRUE 1
//====================================================================
// GLOBAL VARIABLES
//====================================================================
uint32_t bitpattern1 = 0x00000000;
uint32_t bitpattern2 = 0x000000FF;
uint32_t bitpattern3 = 0x000000AA;

typedef uint8_t flag_t;
volatile flag_t startflag = FALSE;
volatile flag_t firstflag = FALSE;
volatile flag_t secondflag = FALSE;
volatile flag_t thirdflag = FALSE;

//====================================================================
// FUNCTION DECLARATIONS
//====================================================================
void initGPIO(void);
void delay(void);
void firstDisplay(void);
void secondDisplay(void);
void thirdDisplay(void);
void checkPD(void);
void display(void);
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
    for(;;){
        checkPD();
        display();
    }
}							// End of main

//====================================================================
// FUNCTION DEFINITIONS
//====================================================================


//display alternating patterns in LEDs
void firstDisplay(void){
    while(firstflag){
        GPIOB->ODR=bitpattern1;
        delay();
        GPIOB->ODR=bitpattern2;
        delay();
        GPIOB->ODR=bitpattern3;
        delay();
        checkPD();
    }  
}

//display each LED on for 1 second from the left
void secondDisplay(void){
    while(secondflag){
        GPIOB->ODR=0x00000001;
        delay();
        GPIOB->ODR=0x00000002;
        delay();
        GPIOB->ODR=0x00000004;
        delay();
        GPIOB->ODR=0x00000008;
        delay();
        GPIOB->ODR=0x00000010;
        delay();
        GPIOB->ODR=0x00000020;
        delay();
        GPIOB->ODR=0x00000040;
        delay();
        GPIOB->ODR=0x00000080;
        delay();
        checkPD();
    }
}

//display counting in binary up to 8-bits
void thirdDisplay(void){
    while(thirdflag){
        volatile int i;
        GPIOB->ODR=0x00000000;
        delay();
        for(i = 0; i < 256; i++){
            GPIOB->ODR+=1;
            delay();
            checkPD();
        }
    }
}

//check which push button is pressed
void checkPD(void){
    if(SW0){
        startflag = TRUE;
        firstflag = FALSE;
        secondflag = FALSE;
        thirdflag = FALSE;
    }else if(SW1){
        startflag = TRUE;
        firstflag = TRUE;
        secondflag = FALSE;
        thirdflag = FALSE;
    }else if(SW2){
        startflag = TRUE;
        firstflag = FALSE;
        secondflag = TRUE;
        thirdflag = FALSE;
    }else if(SW3){
        startflag = TRUE;
        firstflag = FALSE;
        secondflag = FALSE;
        thirdflag = TRUE;
    }
}

//select what to display on LEDs
void display(void){
    if(startflag){
        GPIOB->ODR=0x00000001;
        if(firstflag){
            firstDisplay();
        }else if (secondflag){
            secondDisplay();
        }else if (thirdflag){
            thirdDisplay();
        }           
    }else{
        GPIOB->ODR=0x00000000;
        startflag = FALSE;
    }
}

//create a 1 second delay
void delay(void){ 
    volatile int i, j;
    for(i = 0; i <= DELAY1; i++){
        for(j = 0; j <= DELAY2; j++);
    }
    
}

//initialize the pins that will be used
void initGPIO(void){
    //initLEDs
    RCC->AHBENR|=RCC_AHBENR_GPIOBEN;
    //output mode and turn off LEDs
    GPIOB->MODER|=GPIO_MODER_MODER0_0;//LED D0
    GPIOB->ODR&=~GPIO_ODR_0;
    GPIOB->MODER|=GPIO_MODER_MODER1_0;//LED D1
    GPIOB->ODR&=~GPIO_ODR_1;
    GPIOB->MODER|=GPIO_MODER_MODER2_0;//LED D2
    GPIOB->ODR&=~GPIO_ODR_2;
    GPIOB->MODER|=GPIO_MODER_MODER3_0;//LED D3
    GPIOB->ODR&=~GPIO_ODR_3;
    GPIOB->MODER|=GPIO_MODER_MODER4_0;//LED D4
    GPIOB->ODR&=~GPIO_ODR_4;
    GPIOB->MODER|=GPIO_MODER_MODER5_0;//LED D5
    GPIOB->ODR&=~GPIO_ODR_5;
    GPIOB->MODER|=GPIO_MODER_MODER6_0;//LED D6
    GPIOB->ODR&=~GPIO_ODR_6;
    GPIOB->MODER|=GPIO_MODER_MODER7_0;//LED D7
    GPIOB->ODR&=~GPIO_ODR_7;

    //initButtons
    RCC->AHBENR|=RCC_AHBENR_GPIOAEN;
    //input mode and pull up resistors
    GPIOA->MODER&=~GPIO_MODER_MODER0;
    GPIOA->PUPDR|=GPIO_PUPDR_PUPDR0_0;//SW0
    GPIOA->MODER&=~GPIO_MODER_MODER1;
    GPIOA->PUPDR|=GPIO_PUPDR_PUPDR1_0;//SW1
    GPIOA->MODER&=~GPIO_MODER_MODER2;
    GPIOA->PUPDR|=GPIO_PUPDR_PUPDR2_0;//SW2
    GPIOA->MODER&=~GPIO_MODER_MODER3;
    GPIOA->PUPDR|=GPIO_PUPDR_PUPDR3_0;//SW3
    
}
//********************************************************************
// END OF PROGRAM
//********************************************************************