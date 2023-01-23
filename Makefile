NAME = miniRT
B_NAME = miniRT_bonus
CC = cc
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address
# CFLAGS = -Wall -Wextra -Werror -MMD -MP -g -fsanitize=address
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
		rt_init_utils2.c \
		rt_draw.c \
		rt_draw_utils.c \
		rt_random.c \
		rt_eye_raytrace.c \
		rt_raytrace.c \
		rt_co_test_intersection.c \
		rt_cy_test_intersection.c \
		rt_pl_test_intersection.c \
		rt_sp_test_intersection.c

B_SRCS =	b_main.c

VPATH =	srcs:\
		srcs/init:\
		srcs/arg:\
		srcs/error:\
		srcs/draw:\
		srcs/draw/test_intersection:\
		srcs/vector_operation:\
		b_srcs:\
		b_srcs/init:\
		b_srcs/arg:\
		b_srcs/error:\
		b_srcs/draw:\
		b_srcs/draw/test_intersection:\
		b_srcs/vector_operation


OBJDIR = ./obj
OBJS = $(addprefix $(OBJDIR)/, $(SRCS:.c=.o))
B_OBJDIR = ./b_obj
B_OBJS = $(addprefix $(B_OBJDIR)/, $(B_SRCS:.c=.o))

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

bonus: fclean $(B_NAME)

$(B_NAME) : $(B_OBJDIR) $(LIBFT) $(MINILIB) $(B_OBJS)
	$(CC) $(CFLAGS) $(B_OBJS) $(LIBFT) $(LIBS) $(FRMEWORK) $(INLCUDE) -o $(B_NAME)

$(OBJDIR) :
	mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS) $(INLCUDE)

$(B_OBJDIR) :
	mkdir -p $(B_OBJDIR)

$(B_OBJDIR)/%.o: %.c
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
	$(RM) -rf $(B_OBJDIR)

fclean : clean
	make fclean -C $(LIBFT_PATH)
	$(RM) ./libmlx.dylib $(NAME) $(B_NAME)

debug: CFLAGS += -DDEBUG
debug: re

sanitize: CFLAGS += -g -fsanitize=address
sanitize: re

re : fclean all

PHONY : clean fclean all debug sanitize re
