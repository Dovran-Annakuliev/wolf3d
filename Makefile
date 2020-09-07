GCC = gcc -Wall -Wextra -Werror
NAME = wolf3d
SRC_DIR = sources/
CONTROLLERS_DIR = $(SRC_DIR)controllers/
SRCS =	$(SRC_DIR)main.c\
		$(SRC_DIR)data_init.c\
		$(SRC_DIR)error.c\
		$(SRC_DIR)read_arg.c\
		$(SRC_DIR)render.c\
		$(SRC_DIR)player.c\
		$(CONTROLLERS_DIR)controller.c\
		$(CONTROLLERS_DIR)keyboard_controller.c\
		$(CONTROLLERS_DIR)mouse_controller.c

INC = includes/
OBJS = $(SRCS:.c=.o)

ifeq ($(OS),Windows_NT)
	detected_OS := Windows
else
	detected_OS := $(shell uname)
endif
ifeq ($(detected_OS),Linux)
	LIB :=  -L libft -lft -L -lXrandr -lXrender -lXi -lXfixes -lXxf86vm -lXext -lX11 -lpthread -lxcb -lXau \
				-lXdmcp -lm -lOpenCL -lrt -lSDL2 -lSDL2_image
	INSTALL :=		sudo apt install libsdl2-dev libsdl2-2.0-0 -y && \
    				sudo apt install libjpeg-dev libwebp-dev libtiff5-dev libsdl2-image-dev libsdl2-image-2.0-0 -y
	UNINSATLL :=	sudo apt remove libsdl2-dev libsdl2-2.0-0 -y && \
                	sudo apt remove libjpeg-dev libwebp-dev libtiff5-dev libsdl2-image-dev libsdl2-image-2.0-0 -y
endif
ifeq ($(detected_OS),Darwin)
	LIB = -L libft -lft -framework OpenGL -framework Appkit -framework OpenCL \
				-I SDL2.framework/Headers -F ./ -framework SDL2 -I SDL2_image.framework/Headers -F ./ -framework SDL2_image
	INSTALL :=		cp -r SDL2.framework ~/Library/Frameworks/ && \
					cp -r SDL2_image.framework ~/Library/Frameworks/
	UNINSTALL :=	rm -rf ~/Library/Frameworks/SDL2.framework && \
					rm -rf ~/Library/Frameworks/SDL2_image.framework
endif

all: $(NAME)

sources%.o: %.c
		$(GCC) -c $< -o $@ -I $(INC)

lib: install
		make -C libft

install:
		$(INSTALL)


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
		$(UNINSTALL)

