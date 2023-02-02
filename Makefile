NAME = miniRT
B_NAME = miniRT_bonus
CC = cc
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address
# CFLAGS = -Wall -Wextra -Werror -MMD -MP -g -fsanitize=address
LIBS = -L$(MINILIB_PATH) -lmlx_Linux -L/usr/X11R6/lib -lXext -lX11 -lm
INLCUDE = -I ./inc -I /usr/X11R6/inxlude -I$(MINILIB_PATH) -I$(LIBFT_PATH)

#以下の2項目はベタ打ち
SRCS =	main.c \
		rt_check_arg.c \
		rt_put_error.c \
		rt_init.c \
		rt_rgb_vec_cons_add_mult.c \
		rt_vec_cons_sub_add_mult.c \
		rt_rgv_vec_pi.c \
		rt_vec_product.c \
		rt_fill_struct_a_c_l.c \
		rt_fill_struct_cn.c\
		rt_fill_struct_sp_pl_cy.c \
		rt_init_fill_struct.c \
		rt_init_hook.c \
		rt_init_utils.c \
		rt_init_utils2.c \
		rt_draw.c \
		rt_draw_utils.c \
		rt_eye_raytrace.c \
		rt_raytrace.c \
		rt_intersec_utils.c\
		rt_co_intersec.c \
		rt_cy_intersec.c \
		rt_pl_intersec.c \
		rt_sp_intersec.c \
		rt_all_insec.c \
		rt_shadow_intersection.c \
		rt_calc_spec_and_diffu.c \
		rt_calc_diffu.c

B_SRCS =	main_bonus.c \
			rt_check_arg_bonus.c \
			rt_put_error_bonus.c \
			rt_init_bonus.c \
			rt_rgb_vec_cons_add_mult_bonus.c \
			rt_vec_cons_sub_add_mult_bonus.c \
			rt_rgv_vec_pi_bonus.c \
			rt_vec_product_bonus.c \
			rt_fill_struct_a_c_l_bonus.c \
			rt_fill_struct_cn_bonus.c\
			rt_fill_struct_sp_pl_cy_bonus.c \
			rt_init_fill_struct_bonus.c \
			rt_init_hook_bonus.c \
			rt_init_utils_bonus.c \
			rt_init_utils2_bonus.c \
			rt_draw_bonus.c \
			rt_draw_utils_bonus.c \
			rt_bump_mapping.c \
			rt_eye_raytrace_bonus.c \
			rt_raytrace_bonus.c \
			rt_raytrace2_bonus.c \
			rt_intersec_utils_bonus.c\
			rt_co_intersec_bonus.c \
			rt_cy_intersec_bonus.c \
			rt_pl_intersec_bonus.c \
			rt_sp_intersec_bonus.c \
			rt_all_insec_bonus.c \
			rt_shadow_intersection_bonus.c \
			rt_calc_spec_and_diffu_bonus.c \
			rt_calc_diffu_bonus.c \
			rt_dl_intersec_bonus.c \
			rt_fill_struct_dl_bonus.c \

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

# MINILIB_PATH = ./minilibx-linux
# MINILIB = $(MINILIB_PATH)/libmlx_Linux.a


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

norm :
	norminette ./srcs ./b_srcs ./inc $(LIBFT_PATH) | grep Error

re : fclean all

PHONY : clean fclean all debug sanitize re norm
