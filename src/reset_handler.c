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

typedef struct _DeviceVectors
{
  /* Stack pointer */
  void* pvStack;

  /* Cortex-M handlers */
  void* pfnReset_Handler;
  void* pfnNMI_Handler;
  void* pfnHardFault_Handler;
  void* pvReservedM12;
  void* pvReservedM11;
  void* pvReservedM10;
  void* pvReservedM9;
  void* pvReservedM8;
  void* pvReservedM7;
  void* pvReservedM6;
  void* pfnSVC_Handler;
  void* pvReservedM4;
  void* pvReservedM3;
  void* pfnPendSV_Handler;
  void* pfnSysTick_Handler;

  /* Peripheral handlers */
  void* pfnPM_Handler;                    /*  0 Power Manager */
  void* pfnSYSCTRL_Handler;               /*  1 System Control */
  void* pfnWDT_Handler;                   /*  2 Watchdog Timer */
  void* pfnRTC_Handler;                   /*  3 Real-Time Counter */
  void* pfnEIC_Handler;                   /*  4 External Interrupt Controller */
  void* pfnNVMCTRL_Handler;               /*  5 Non-Volatile Memory Controller */
  void* pfnDMAC_Handler;                  /*  6 Direct Memory Access Controller */
  void* pfnUSB_Handler;                   /*  7 Universal Serial Bus */
  void* pfnEVSYS_Handler;                 /*  8 Event System Interface */
  void* pfnSERCOM0_Handler;               /*  9 Serial Communication Interface 0 */
  void* pfnSERCOM1_Handler;               /* 10 Serial Communication Interface 1 */
  void* pfnSERCOM2_Handler;               /* 11 Serial Communication Interface 2 */
  void* pfnSERCOM3_Handler;               /* 12 Serial Communication Interface 3 */
  void* pfnSERCOM4_Handler;               /* 13 Serial Communication Interface 4 */
  void* pfnSERCOM5_Handler;               /* 14 Serial Communication Interface 5 */
  void* pfnTCC0_Handler;                  /* 15 Timer Counter Control 0 */
  void* pfnTCC1_Handler;                  /* 16 Timer Counter Control 1 */
  void* pfnTCC2_Handler;                  /* 17 Timer Counter Control 2 */
  void* pfnTC3_Handler;                   /* 18 Basic Timer Counter 3 */
  void* pfnTC4_Handler;                   /* 19 Basic Timer Counter 4 */
  void* pfnTC5_Handler;                   /* 20 Basic Timer Counter 5 */
  void* pvReserved21;
  void* pvReserved22;
  void* pfnADC_Handler;                   /* 23 Analog Digital Converter */
  void* pfnAC_Handler;                    /* 24 Analog Comparators */
  void* pfnDAC_Handler;                   /* 25 Digital Analog Converter */
  void* pfnPTC_Handler;                   /* 26 Peripheral Touch Controller */
  void* pfnI2S_Handler;                   /* 27 Inter-IC Sound Interface */
  void* pvReserved28;
} DeviceVectors;

/* Forward define main */
int main(void);
void HardFault_Handler(void);
void Reset_Handler(void);
void NMI_Handler(void);

__attribute__ ((section(".vectors")))
const DeviceVectors exception_table = {
        /* Configure Initial Stack Pointer, using linker-generated symbols */
        .pvStack                = (void*) (&_estack),
        .pfnReset_Handler       = (void*) Reset_Handler,
        .pfnNMI_Handler         = (void*) NMI_Handler,
        .pfnHardFault_Handler   = (void*) HardFault_Handler,

};

void NMI_Handler(void) {
    while (1) {}
}

void HardFault_Handler(void) {
    while (1) {}
}

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