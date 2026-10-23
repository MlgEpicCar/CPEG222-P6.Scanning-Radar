// ****************************************************************
// * Authors: T. LUM and R. MARTIN
// * CPEG222 Demo Program5, 9/28/2026
// * NucleoF446ZE CMSIS STM32F4xx example Proj5
// * Sends text to the OLED display using SPI
// ****************************************************************
#include "stm32f4xx.h"
#include "OLED.h"
#include "UART3.h"
#include "SysClock180MHz.h"
#include <stdint.h> // Include stdint.h for uint32_t type
#include <stdio.h> // Include stdio.h for snprintf function

void delay_ms(uint32_t ms); // Function prototype for delay function
char buffer[90];
uint32_t initialClock; // Initial system clock frequency (16 MHz)
uint32_t finalClock;   // Final system clock frequency (180 MHz)

int main(void){
    SystemCoreClockUpdate(); // CMSIS function to update SystemCoreClock variable
    initialClock = SystemCoreClock; // Store the initial clock frequency (16 MHz)
    SystemClock_Config(); // Configure the system clock to 180 MHz
    SystemCoreClockUpdate(); // Update SystemCoreClock variable after clock change
    finalClock = SystemCoreClock; // Store the final clock frequency (180 MHz)
    OLED_Init();
    UART3_Init(115200);
    SH1106_RenderFullScreenLogo();
    delay_ms(2000); // Delay for 2 seconds to display the logo
    OLED_Clear();
    OLED_Print(0, 0, "Range Finder Demo");
    OLED_Print(1, 0, "C. Munar: 10/23/26");
    snprintf(buffer, sizeof(buffer), "Pulse: %lu MHz  ", initialClock / 1000000U);               
    OLED_Print(5, 1, buffer);
    snprintf(buffer, sizeof(buffer), "Dist: %lu MHz  ", finalClock / 1000000U);
    OLED_Print(6, 1, buffer);
    while(1){
        // Main loop
        delay_ms(150);
        UART3_SendString("UART3 is working!\r\n");
    }   
    return 0;// Program should never reach here due to infinite loop
}
void delay_ms(uint32_t ms){
    if(SystemCoreClock == 16000000U){ // If the system clock is 16 MHz
        for(uint32_t i = 0; i < ms * 2000; i++){
            __NOP();
        }
    } else if(SystemCoreClock == 180000000U){ // If the system clock is 180 MHz
        for(uint32_t i = 0; i < ms * 22500; i++){
            __NOP();
        }
    }
}