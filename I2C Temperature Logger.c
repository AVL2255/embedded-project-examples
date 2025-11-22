#include "stm32f4xx_hal.h"
#include <string.h>

I2C_HandleTypeDef hi2c1;
UART_HandleTypeDef huart2;

uint8_t read_temp_sensor()
{
    uint8_t temp;
    HAL_I2C_Mem_Read(&hi2c1, 0x48<<1, 0x00, 1, &temp, 1, 100);
    return temp;
}

void log_to_flash(uint8_t temp)
{
    // Placeholder for flash log
}

int main(void)
{
    HAL_Init();

    while(1)
    {
        uint8_t t = read_temp_sensor();
        char msg[32];
        sprintf(msg, "Temp: %d C\r\n", t);
        HAL_UART_Transmit(&huart2, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);

        log_to_flash(t);
        HAL_Delay(1000);
    }
}
