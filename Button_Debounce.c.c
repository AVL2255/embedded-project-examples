#include "stm32f4xx_hal.h"

#define DEBOUNCE_DELAY 50

uint8_t read_button(GPIO_TypeDef *port, uint16_t pin)
{
    if (HAL_GPIO_ReadPin(port, pin) == GPIO_PIN_RESET)
    {
        HAL_Delay(DEBOUNCE_DELAY);
        if (HAL_GPIO_ReadPin(port, pin) == GPIO_PIN_RESET)
            return 1;
    }
    return 0;
}

int main(void)
{
    HAL_Init();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();

    GPIO_InitTypeDef led = {0};
    led.Pin = GPIO_PIN_5;
    led.Mode = GPIO_MODE_OUTPUT_PP;
    HAL_GPIO_Init(GPIOA, &led);

    GPIO_InitTypeDef button = {0};
    button.Pin = GPIO_PIN_13;
    button.Mode = GPIO_MODE_INPUT;
    button.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(GPIOC, &button);

    while(1)
    {
        if(read_button(GPIOC, GPIO_PIN_13))
        {
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
            HAL_Delay(200);
        }
    }
}
