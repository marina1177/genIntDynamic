NAME = verle

WFLAGS = #-Wall -Werror -Wextra
FLAGS = -g $(WFLAGS)
CC = gcc
INC = -I ./includes

### PATH ###
HEADPATH = includes/
HEADLIST = verle.h
SRCS_PATH = src/
OBJ_PATH = obj/

SRCS_NAME = main.c \
			mem_manage.c \
			io_read_input.c \
			io_write_input.c \
			io_print_file.c \
			gen_main.c \
			gen_params.c \
			gen_initial_val.c \
			gen_mem_manage.c \
			io_tools.c \
			int_main.c \
			int_tools.c \
			int_algo.c \
			io_read_map.c \
			int_mem_manage.c\
			ft_strsplit.c \
			int_tension.c \
			int_exception.c \
			int_Stokes.c \
			int_velocity_calc.c \
			int_acc_calc.c \
			int_interparticle_forces.c \
			int_tension_for_particle.c \
			int_coord_calc.c \
			io_write_output.c \
			io_write_gradient.c \


SRCS = $(addprefix $(SRCS_PATH), $(SRCS_NAME))
OBJ = $(addprefix $(OBJ_PATH), $(SRCS_NAME:.c=.o))


### COMPILE ###
all: $(NAME)

$(OBJ_PATH):
		@mkdir -p $(OBJ_PATH)

$(OBJ_PATH)%.o: $(SRCS_PATH)%.c includes/verle.h
		@echo "\033[34m\033[1mCompilation of \033[0m\033[36m$(notdir $<)\033[1m\033[34m done.\033[0m"
		$(CC) -g $(WFLAGS) $(INC) -c $< -o $@

$(NAME): $(OBJ_PATH) $(OBJ)
		$(CC) $(OBJ) $(INC) -lm  -o $(NAME)
		@echo "\033[32mBinary \033[1;32m$(NAME)\033[1;0m\033[32m created.\033[0m"


clean:
		@/bin/rm -rf $(OBJ_PATH)
		@/bin/rm -rf vis.json
		@echo "\033[1;31m$(NAME) \033[1;0m\033[31mobjects files removed.\033[0m"


fclean: clean
		@/bin/rm -f $(NAME)
		@echo "\033[31mBin \033[1;31m$(NAME)\033[1;0m\033[31m removed.\033[0m"
		@/bin/rm -f  ./params.bin ./test_18_04.bin

re: fclean all

.PHONY: all clean fclean re
