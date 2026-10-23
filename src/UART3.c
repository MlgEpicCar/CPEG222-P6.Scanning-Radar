#include "stm32f4xx.h"
#include "UART3.h"

void UART3_Init(uint32_t baud_rate)
{
    // Enable the GPIOD clock
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;

    // Enable the USART3 clock on APB1
    RCC->APB1ENR |= RCC_APB1ENR_USART3EN;

    // Configure PD8 and PD9 for alternate function mode
    GPIOD->MODER &= ~((3U << (8U * 2U)) |
                      (3U << (9U * 2U)));

    GPIOD->MODER |=  ((2U << (8U * 2U)) |
                      (2U << (9U * 2U)));

    // Select alternate function AF7 for PD8 and PD9
    GPIOD->AFR[1] &= ~((0xFU << 0U) |
                       (0xFU << 4U));

    GPIOD->AFR[1] |=  ((7U << 0U) |
                       (7U << 4U));

    // Configure USART3
    USART3->CR1 = 0U;
    USART3->CR2 = 0U;
    USART3->CR3 = 0U;

    // APB1 clock is 45 MHz in SysClock180MHz.c
    #define USART3_CLOCK_HZ 45000000U

    USART3->BRR = (USART3_CLOCK_HZ + baud_rate / 2U) / baud_rate;

    // Enable transmitter and USART3
    USART3->CR1 |= USART_CR1_TE;
    USART3->CR1 |= USART_CR1_UE;
}

void UART3_SendChar(char c)
{
    // Wait until the transmit data register is empty
    while (!(USART3->SR & USART_SR_TXE))
    {
    }

    // Place the character in the transmit data register
    USART3->DR = (uint8_t)c;
}

void UART3_SendString(const char *str)
{
    // Send characters until the null terminator
    while (*str != '\0')
    {
        UART3_SendChar(*str);
        str++;
    }
}