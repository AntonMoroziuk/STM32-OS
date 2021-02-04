#include <stdint.h>
/* These are defined in the linker script */
extern uint32_t _stext;
extern uint32_t _etext;
extern uint32_t _sbss;
extern uint32_t _ebss;
extern uint32_t _sdata;
extern uint32_t _edata;
extern uint32_t _sstack;
extern uint32_t _estack;

/* Forward define main */
int main(void);

__attribute__ ((section(".vectors")))
void Reset_Handler(void)
{
        /* Copy init values from text to data */
        uint32_t *init_values_ptr = &_etext;
        uint32_t *data_ptr = &_sdata;

        if (init_values_ptr != data_ptr)
            for (; data_ptr < &_edata; data_ptr++, init_values_ptr++)
                    *data_ptr = *init_values_ptr;

        /* Clear the zero segment */
        for (uint32_t *bss_ptr = &_sbss; bss_ptr < &_ebss; bss_ptr++)
                *bss_ptr = 0;

        /* Branch to main function */
        main();

        /* Infinite loop */
        while (1);
}