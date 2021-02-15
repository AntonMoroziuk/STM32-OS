CC 		= arm-none-eabi-gcc
CCFLAGS	= 	-Wall \
			-Werror \
			-Wextra \
			-mcpu=cortex-m0 \
			-mthumb \
			-ffreestanding \
			-g

LDFLAGS	= 	-T flash.ld \
			-nostdlib \
			-mthumb \
			-nostartfiles \
			-g \
			-mcpu=cortex-m0

SRC_N 	= 	reset_handler.c \
			main.c \
			gpio.c \
			utils.c \
			rcc.c \
			uart.c

HEADERS_N =	gpio.h \
			utils.h \
			rcc.h \
			uart.h

SRC_P 	= ./src/
OBJ 	= $(addprefix $(OBJ_P),$(SRC_N:.c=.o))
OBJ_P	= ./obj/
INC 	= $(addprefix -I, $(INC_P))
INC_P	= ./includes/
HEADERS = $(addprefix $(INC_P), $(HEADERS_N))
NAME 	= kernel.elf


all: obj $(NAME)

obj:
	mkdir -p $(OBJ_P)

$(OBJ_P)%.o: $(SRC_P)%.c $(HEADERS)
	$(CC) $(CCFLAGS) -I $(INC_P) -o $@ -c $<

$(NAME): $(OBJ)
	$(CC) $(LDFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -rf $(OBJ_P)

fclean: clean
	rm -rf $(NAME)

flash: all
	openocd -f "board/st_nucleo_f0.cfg" -c "program kernel.elf"

debug: all
	arm-none-eabi-gdb kernel.elf

re: fclean all

.PHONY: all clean fclean re