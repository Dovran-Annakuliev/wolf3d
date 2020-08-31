GCC = gcc -Wall -Wextra -Werror
NAME = wolf3d
SRC_DIR = sources/
CONTROLLERS_DIR = $(SRC_DIR)controllers/
SRCS = $(SRC_DIR)main.c\
		$(SRC_DIR)data_init.c\
		$(SRC_DIR)error.c\
		$(SRC_DIR)read_arg.c\
		$(SRC_DIR)render.c

INC = includes/
OBJS = $(SRCS:.c=.o)

ifeq ($(OS),Windows_NT)
	detected_OS := Windows
else
	detected_OS := $(shell uname)
endif
ifeq ($(detected_OS),Linux)
	LIB :=  -L libft -lft -L -lXrandr -lXrender -lXi -lXfixes -lXxf86vm -lXext -lX11 -lpthread -lxcb -lXau -lXdmcp -lm -lOpenCL -lrt
endif
ifeq ($(detected_OS),Darwin)  
	LIB = -L libft -lft -framework OpenGL -framework Appkit -framework OpenCL -I SDL2.framework/Headers -F ./ -framework SDL2 -I SDL2_image.framework/Headers -F ./ -framework SDL2_image
endif

all: $(NAME)

sources%.o: %.c
		$(GCC) -c $< -o $@ -I $(INC)

lib: install
		make -C libft

install:
		cp -r SDL2.framework ~/Library/Frameworks/
		cp -r SDL2_image.framework ~/Library/Frameworks/

$(NAME): lib $(OBJS) $(INC)*.h
		 $(GCC) $(OBJS) $(LIB) -o $(NAME)

clean:
		rm -f $(OBJS)
		make -C libft clean

fclean: clean uninstall
		rm -f $(NAME)
		make -C libft fclean

re: fclean all

uninstall:
		rm -rf ~/Library/Frameworks/SDL2.framework
		rm -rf ~/Library/Frameworks/SDL2_image.framework
