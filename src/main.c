#include <stdint.h>

int main()
{
	volatile uint32_t *RCC_AHBENR = (uint32_t *)0x40021014;

	*RCC_AHBENR |= (1 << 17);

	volatile uint32_t *GPIOA = (uint32_t *)0x48000000UL;

	// configure PA5 as output
	*GPIOA = 0x28000400;

	*(GPIOA + 6) = (1 << 5);

	while (1) {}

	return (0);
}