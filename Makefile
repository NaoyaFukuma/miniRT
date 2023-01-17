NAME = miniRT
CC = cc
CFLAGS = -Wall -Wextra -Werror -MMD -MP -g -fsanitize=address
LIBS = -L$(MINILIB_PATH) -lmlx_Linux -L/usr/X11R6/lib -lXext -lX11
INLCUDE = -I ./inc -I /usr/X11R6/inxlude -I$(MINILIB_PATH) -I$(LIBFT_PATH)

#以下の2項目はベタ打ち
SRCS =	main.c \
		rt_check_arg.c \
		rt_put_error.c \
		rt_init.c \
		rt_vector_operation.c \
		rt_fill_struct_A_C_L.c \
		rt_fill_struct_sp_pl_cy_cn.c \
		rt_init_fill_struct.c \
		rt_init_hook.c \
		rt_init_utils.c \
		rt_init_utils2.c


VPATH =	srcs:\
		srcs/init:\
		srcs/arg:\
		srcs/error:\
		srcs/vector_operation


OBJDIR = ./obj
OBJS = $(addprefix $(OBJDIR)/, $(SRCS:.c=.o))
# DEPENDS = $(OBJS:.o=.d)
# -include $(DEPENDS)

LIBFT_PATH = ./libft
LIBFT = $(LIBFT_PATH)/libft.a

MINILIB_PATH = ./minilibx_mms_20200219
MINILIB = $(MINILIB_PATH)/libmlx.dylib


ifeq ($(shell uname),Darwin)
MINILIB = $(MINILIB_PATH)/libmlx.dylib
FRMEWORK = -framework OpenGL -framework Appkit
LIBS = $(MINILIB_PATH)/libmlx.dylib -L/usr/X11R6/lib -lXext -lX11
endif

all : $(NAME)

$(NAME) : $(OBJDIR) $(LIBFT) $(MINILIB) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LIBS) $(FRMEWORK) $(INLCUDE) -o $(NAME)

$(OBJDIR) :
	mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS) $(INLCUDE)

$(LIBFT) :
	make -C $(LIBFT_PATH)

$(MINILIB) :
	make -C $(MINILIB_PATH)
	cp $(MINILIB) ./libmlx.dylib

clean :
	make clean -C $(LIBFT_PATH)
	make clean -C $(MINILIB_PATH)
	$(RM) -rf $(OBJDIR)

fclean : clean
	make fclean -C $(LIBFT_PATH)
	$(RM) ./libmlx.dylib $(NAME)

debug: CFLAGS += -DDEBUG
debug: re

sanitize: CFLAGS += -g -fsanitize=address
sanitize: re

re : fclean all

PHONY : clean fclean all debug sanitize re
