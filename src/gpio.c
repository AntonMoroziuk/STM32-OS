#include <stdint.h>

#include "gpio.h"

/**
  * @brief  Initialize the GPIOx peripheral according to the specified parameters in the GPIO_init.
  * @param  GPIOx where x can be (A..F) to select the GPIO peripheral for STM32F0 family.
  * @param  GPIO_init pointer to a GPIO_init_config structure that contains
  *         the configuration information for the specified GPIO peripheral.
  * @retval None
  */
void		init_gpio(GPIO_config *GPIOx, GPIO_init_config *GPIO_init)
{
	GPIOx->GPIO_MODER &= ~(3U << (GPIO_init->pin * 2U));
	GPIOx->GPIO_MODER |= (GPIO_init->mode << (GPIO_init->pin * 2U));
	GPIOx->GPIO_OSPEEDR &= ~(3U << (GPIO_init->pin * 2U));
	GPIOx->GPIO_OSPEEDR |= (GPIO_init->speed << (GPIO_init->pin * 2U));
	GPIOx->GPIO_PUPDR &= ~(3U << (GPIO_init->pin * 2U));
	GPIOx->GPIO_PUPDR |= (GPIO_init->pull << (GPIO_init->pin * 2U));
}

/**
  * @brief  Set GPIO pin according to the specified value.
  * @param  GPIOx where x can be (A..F) to select the GPIO peripheral for STM32F0 family.
  * @param  pin number to set.
  * @param	value to set (1 or 0)
  * @retval None
  */
void	set_gpio(GPIO_config *GPIOx, uint8_t pin, uint8_t value)
{
	if (value)
		GPIOx->GPIO_BSRR = 1 << pin;
	else
		GPIOx->GPIO_BSRR = 1 << (pin + 16);
}