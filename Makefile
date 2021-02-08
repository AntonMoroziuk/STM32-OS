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
			main.c

SRC_P 	= ./src/
OBJ 	= $(addprefix $(OBJ_P),$(SRC_N:.c=.o))
OBJ_P	= ./obj/
INC 	= $(addprefix -I, $(INC_P))
INC_P	= ./includes/
NAME 	= kernel.elf


all: obj $(NAME)

obj:
	mkdir -p $(OBJ_P)

$(OBJ_P)%.o:$(SRC_P)%.c $(HEADER)
	$(CC) $(CCFLAGS) -I $(INC_P) -o $@ -c $<

$(NAME): $(OBJ)
	$(CC) $(LDFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -rf $(OBJ_P)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re