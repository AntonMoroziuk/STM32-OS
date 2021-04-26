#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>

typedef struct GPIO_s
{
    volatile uint32_t    MODER;      /* GPIO mode register,                          Address offset 0x00 */
    volatile uint32_t    OTYPER;     /* GPIO output type register,                   Address offset 0x04 */
    volatile uint32_t    OSPEEDR;    /* GPIO output speed register,                  Address offset 0x08 */
    volatile uint32_t    PUPDR;      /* GPIO pull-up/pull-down register,             Address offset 0x0c */
    volatile uint32_t    IDR;        /* GPIO input data register,                    Address offset 0x10 */
    volatile uint32_t    ODR;        /* GPIO output data register,                   Address offset 0x14 */
    volatile uint32_t    BSRR;       /* GPIO bit set/reset register register,        Address offset 0x18 */
    volatile uint32_t    LCKR;       /* GPIO configuration lock register,            Address offset 0x1c */
    volatile uint32_t    AFRL;       /* GPIO alternate function low register,        Address offset 0x20 */
    volatile uint32_t    AFRH;       /* GPIO alternate function high register,       Address offset 0x24 */
    volatile uint32_t    BRR;        /* GPIO bit reset register register,            Address offset 0x28 */
} GPIO;

typedef struct GPIO_config_s
{
    uint32_t   mode;        /* Should be one of GPIO_MODER values */
    uint32_t   pin;         /* Pin number from 0 to 15 */
    uint32_t   pull;        /* Should be one of GPIO_PUPDR values */
    uint32_t   speed;       /* Should be one of GPIO_OSPEEDR values */
    uint32_t   alternate;   /* TODO: alternate options */
} GPIO_config;

typedef struct GPIO_pin_s
{
    uint32_t   pin;
    GPIO       *port;
} GPIO_pin;

/* GPIO_MODER possible values */
#define GPIO_MODE_INPUT             (0x00000000U)
#define GPIO_MODE_OUTPUT            (0x00000001U)
#define GPIO_MODE_ALTERNATE_FUNC    (0x00000002U)
#define GPIO_MODE_ANALOG            (0x00000003U)

/* GPIO_OTYPER possible values */
#define GPIO_TYPE_PUSH_PULL         (0x00000000U)
#define GPIO_TYPE_OPEN_DRAIN        (0x00000001U)

/* GPIO_OSPEEDR possible values */
#define GPIO_SPEED_LOW              (0x00000000U)
#define GPIO_SPEED_MEDIUM           (0x00000001U)
#define GPIO_SPEED_HIGH             (0x00000003U)

/* GPIO_PUPDR possible values */
#define GPIO_NO_PUPD                (0x00000000U)
#define GPIO_PULL_UP                (0x00000001U)
#define GPIO_PULL_DOWN              (0x00000002U)

/* GPIO group object */
#define GPIOA                       ((GPIO *)0x48000000U)
#define GPIOB                       ((GPIO *)0x48000400U)
#define GPIOC                       ((GPIO *)0x48000800U)
#define GPIOD                       ((GPIO *)0x48000C00U)
#define GPIOE                       ((GPIO *)0x48001000U)
#define GPIOF                       ((GPIO *)0x48001400U)

/* GPIO pin offset inside group */
#define GPIO_PIN_0                  0x00000000U
#define GPIO_PIN_1                  0x00000001U
#define GPIO_PIN_2                  0x00000002U
#define GPIO_PIN_3                  0x00000003U
#define GPIO_PIN_4                  0x00000004U
#define GPIO_PIN_5                  0x00000005U
#define GPIO_PIN_6                  0x00000006U
#define GPIO_PIN_7                  0x00000007U
#define GPIO_PIN_8                  0x00000008U
#define GPIO_PIN_9                  0x00000009U
#define GPIO_PIN_10                 0x0000000aU
#define GPIO_PIN_11                 0x0000000bU
#define GPIO_PIN_12                 0x0000000cU
#define GPIO_PIN_13                 0x0000000dU
#define GPIO_PIN_14                 0x0000000eU
#define GPIO_PIN_15                 0x0000000fU

/* Alternate function selection values */
#define AF0                         0x0
#define AF1                         0x1
#define AF2                         0x2
#define AF3                         0x3
#define AF4                         0x4
#define AF5                         0x5
#define AF6                         0x6
#define AF7                         0x7

/* Note that to use GPIO you need to enable corresponding RCC */
void gpio_init(GPIO *GPIOx, GPIO_config *GPIO_init);
void gpio_select_alternate_function(GPIO_pin gpio, uint8_t function);
void gpio_set(GPIO_pin gpio, uint8_t value);

#endif
