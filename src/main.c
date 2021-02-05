#include <stdint.h>

int main()
{
	volatile const void *GPIOA = (void*)0x48000000UL;

	// configure PA5 as output
	*(volatile uint32_t *)GPIOA = 0x28000400;

	while (1) {}

	return (0);
}