#include <stdint.h>
#include <string.h>
#include "headers/stm32h7a3xxq.h"
#include "drivers/uart/uart.h"
#include "timers/systick/systick.h"

#include <stdio.h>

/**
 * Pin  - Motor
 * 
 * PE8  - UART7_TX
 * PE7  - UART7_RX
 *
 */
uint8_t uart_pins[2] = {
    8,
    7};

/**
 * @brief Initialises the UART pins
 * 
 */
int8_t init_uart(void)
{
    // enable the UART4 clock as well as the GPIO clock
    RCC->APB1LENR |= RCC_APB1LENR_UART7EN;
    RCC->AHB4ENR |= RCC_AHB4ENR_GPIOEEN;

    // set the alternate function
    GPIOE->AFR[1] |= (0b0111 << ((8 - 8) * 4));
    GPIOE->AFR[0] |= (0b0111 << (7 * 4));

    GPIOE->MODER &= ~(0b11 << (8 * 2));
    GPIOE->MODER &= ~(0b11 << (7 * 2));
    // set the mode to alternate function
    GPIOE->MODER |= (0b10 << (8 * 2)) |
                    (0b10 << (7 * 2));

    // calculate and set the baud rate
    uint16_t uartdiv = CORE_CLOCK / BAUD_RATE;
    UART7->BRR = uartdiv;

    // enable the RX, TX and then enable the UART
    UART7->CR1 |= USART_CR1_RE |
                  USART_CR1_TE |
                  USART_CR1_UE;

    return 0;
}

// writes a single character to the UART
// // this UART is typically used for IO
// void print(char byte)
// {
//     // interrupt and status register
//     uint16_t isr;
//     do
//     {
//         // set current value
//         // to prevent compiler from optimising this bit out
//         isr = !(UART5->ISR & USART_ISR_TXE);
//     } while (isr);
//     // transmit the byte
//     UART5->TDR = byte;
// }

// // writes a string to the UART followed by CRLF
// void print_full(char *message)
// {
//     // iterate over the message and output each character one by one
//     while (*message != '\0')
//         print(*(message++));
//     // output the line termination sequence
//     print('\r');
//     print('\n');
// }

// writes a single character to the UART
void write_uart(char byte)
{
    // interrupt and status register
    uint16_t isr;
    do
    {
        // set current value
        // to prevent compiler from optimising this bit out
        isr = !((UART7->ISR & USART_ISR_TXE_TXFNF) == USART_ISR_TXE_TXFNF);
    } while (isr);
    // transmit the byte
    UART7->TDR = byte;
}

// reads a single character from the UART
char read_uart(uint16_t timeout)
{
    uint64_t readUntil = ticks + (uint64_t)timeout;
    // interrupt and status register
    uint16_t isr;
    do
    {
        // set current value
        // prevents compiler from optimising this loop out
        isr = !(UART7->ISR & USART_ISR_RXNE_RXFNE);
        if (ticks > readUntil)
            return '\0';
    } while (isr);
    // return the register value
    return UART7->RDR;
}

// writes a string to the UART followed by CRLF
void write_full_uart(char *message)
{
    // iterate over the message and output each character one by one
    while (*message != '\0')
        write_uart(*(message++));
    // output the line termination sequence
    write_uart('\r');
    write_uart('\n');
}

// reads the UART and expects a specified message
int8_t read_full_uart_and_expect(char *message, uint16_t timeout)
{
    // iterate over every character of the expected message
    while (*message != '\0')
    {
        // read the uart and check that the character matches
        char currentValue = read_uart(timeout);
        if (*(message++) != currentValue)
            return -1;
    }
    return 0;
}

// reads the UART until a match is found with the specified pattern of characters
int8_t find_pattern(char *pattern, uint16_t patternLength, uint16_t timeout)
{
    uint8_t matchingChars = 0;
    while (matchingChars != patternLength)
    {
        char currentValue = read_uart(timeout);
        if (currentValue == *(pattern + matchingChars))
            matchingChars++;
        else
            matchingChars = 0;
    }
    return 0;
}