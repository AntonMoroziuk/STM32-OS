#include <stdint.h>

int main()
{
	const void *GPIOA = (void*)0x48000000UL;

	// configure PA5 as output
	*(uint32_t *)GPIOA |= (0x1 << 10);

	// set value to high
	*((uint32_t *)GPIOA + 6) |= (0x1 << 5);

	while (1) {}

	return (0);
}