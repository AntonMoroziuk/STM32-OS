#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>

typedef struct 	GPIO_config_s
{
	uint32_t 	GPIO_MODER;  	/* GPIO mode register, 						Address offset 0x00 */
	uint32_t 	GPIO_OTYPER; 	/* GPIO output type register, 				Address offset 0x04 */
	uint32_t 	GPIO_OSPEEDR;	/* GPIO output speed register, 				Address offset 0x08 */
	uint32_t 	GPIO_PUPDR;  	/* GPIO pull-up/pull-down register register,	Address offset 0x0c */
	uint32_t 	GPIO_IDR;  		/* GPIO input data register, 					Address offset 0x10 */
	uint32_t 	GPIO_ODR;  		/* GPIO output data register, 				Address offset 0x14 */
	uint32_t 	GPIO_BSRR;  	/* GPIO bit set/reset register register, 		Address offset 0x18 */
	uint32_t 	GPIO_LCKR;  	/* GPIO configuration lock register, 			Address offset 0x1c */
}				GPIO_config;

typedef struct 	GPIO_init_config_s
{
	uint32_t 	mode;	  		/* Should be one of GPIO_MODER values */
	uint32_t 	pin; 			/* Pin number from 0 to 15 */
	uint32_t 	pull;			/* Should be one of GPIO_PUPDR values */
	uint32_t 	speed;  		/* Should be one of GPIO_OSPEEDR values */
	uint32_t 	alternate;  	/* TODO: alternate options */
}				GPIO_init_config;

/* GPIO_MODER possible values */
#define GPIO_MODE_INPUT 			(0x00000000U)
#define GPIO_MODE_OUTPUT 			(0x00000001U)
#define GPIO_MODE_ALTERNATE_FUNC	(0x00000010U)
#define GPIO_MODE_ANALOG 			(0x00000011U)

/* GPIO_OTYPER possible values */
#define GPIO_TYPE_PUSH_PULL 		(0x00000000U)
#define GPIO_TYPE_OPEN_DRAIN 		(0x00000001U)

/* GPIO_OSPEEDR possible values */
#define GPIO_SPEED_LOW 				(0x00000000U)
#define GPIO_SPEED_MEDIUM			(0x00000001U)
#define GPIO_SPEED_HIGH				(0x00000011U)

/* GPIO_PUPDR possible values */
#define GPIO_NO_PUPD				(0x00000000U)
#define GPIO_PULL_UP				(0x00000001U)
#define GPIO_PULL_DOWN				(0x00000010U)

/* GPIO group offset values */
#define GPIOA_BASE 					(0x48000000U)
#define GPIOB_BASE 					(0x48000400U)
#define GPIOC_BASE 					(0x48000800U)
#define GPIOD_BASE 					(0x48000C00U)
#define GPIOE_BASE 					(0x48001000U)
#define GPIOF_BASE 					(0x48001400U)

/* GPIO group object */
#define GPIOA						(*GPIO_config)GPIOA_BASE
#define GPIOB						(*GPIO_config)GPIOB_BASE
#define GPIOC						(*GPIO_config)GPIOC_BASE
#define GPIOD						(*GPIO_config)GPIOD_BASE
#define GPIOE						(*GPIO_config)GPIOE_BASE
#define GPIOF						(*GPIO_config)GPIOF_BASE

/* GPIO pin offset inside group */
#define GPIO_PIN_0					((uint16_t)0x0001U)
#define GPIO_PIN_1					((uint16_t)0x0002U)
#define GPIO_PIN_2					((uint16_t)0x0004U)
#define GPIO_PIN_3					((uint16_t)0x0008U)
#define GPIO_PIN_4					((uint16_t)0x0010U)
#define GPIO_PIN_5					((uint16_t)0x0020U)
#define GPIO_PIN_6					((uint16_t)0x0040U)
#define GPIO_PIN_7					((uint16_t)0x0080U)
#define GPIO_PIN_8					((uint16_t)0x0100U)
#define GPIO_PIN_9					((uint16_t)0x0200U)
#define GPIO_PIN_10					((uint16_t)0x0400U)
#define GPIO_PIN_11					((uint16_t)0x0800U)
#define GPIO_PIN_12					((uint16_t)0x1000U)
#define GPIO_PIN_13					((uint16_t)0x2000U)
#define GPIO_PIN_14					((uint16_t)0x4000U)
#define GPIO_PIN_15					((uint16_t)0x8000U)
#define GPIO_PIN_ALL				((uint16_t)0xFFFFU)


void	configure_gpio(GPIO_config *GPIOx, GPIO_init_config *GPIO_init);

#endif