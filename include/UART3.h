#ifndef UART3_H
#define UART3_H

#include <stdint.h>

void UART3_Init(uint32_t baud_rate);
void UART3_SendChar(char c);
void UART3_SendString(const char *str);

#endif