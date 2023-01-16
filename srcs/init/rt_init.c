/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 14:53:32 by nfukuma           #+#    #+#             */
/*   Updated: 2023/01/16 16:53:21 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mlx.h"
#include "rt_put_error.h"
#include "rt_strucs.h"
#include <fcntl.h>
#include <stdio.h>
#include <limits.h>
#include "rt_define.h"
#include <math.h>


void	rt_mlx(t_rt_data *rt);
void	rt_import_rt_file(t_rt_data *rt, const char *file);
void	rt_hooks(t_rt_data *rt);

int rt_KeyPress(int keycode, t_rt_data *rt)
{
	(void)rt;
	if (keycode == KEY_ESC)
		exit(EXIT_SUCCESS);
	return (0);
}

int rt_DestroyNotify(t_rt_data *rt)
{
	(void)rt;
	exit(0);
	return (0);
}

void	rt_init(t_rt_data *rt, const char *file)
{
	rt_import_rt_file(rt, file);
	rt_mlx(rt);
	rt_hooks(rt);
	// mlx_loop(rt->mlx.mlx);
}

void	rt_double_ptr_free(const char **d_ptr)
{
	size_t	i;

	i = 0;
	while (d_ptr[i])
	{
		free((void *)d_ptr[i]);
		d_ptr[i] = NULL;
	}
	free((void *)d_ptr);
	d_ptr = NULL;
}

enum id
{
	A,
	C,
	L,
	sp,
	pl,
	cy,
	cn,
};

int	rt_check_id(const char *str)
{
	int	id;
	const char	*id_set[] = {"A", "C", "L", "sp", "pl", "cy", "cn"};

	id = 0;
	while (id_set[id])
		if (!ft_strcmp(str, id_set[id]))
			break ;
	if (id_set[id] == NULL)
		return (-1);
	return (id);
}

int	rt_count_str(const char **strs)
{
	int	i;

	if (strs == NULL)
		return (-1);
	i = 0;
	while (strs[i])
		++i;
	return (i);
}

double		ft_atof(const char *str)
{
	double	ans;
	double	i;
	int		sign;

	if (!str)
		return 0;
	sign = 1;
	while (!ft_isalnum(*str))
		if (*str++ == '-')
			sign = -1;
	ans = 0;
	while (ft_isdigit(*str))
		ans = ans * 10 + *str++ - '0';
	i = 0.1;
	if (*str == '.')
	{
		str++;
		while(ft_isdigit(*str))
		{
			ans += (*str - '0') * i;
			i *= 0.1;
			str++;
		}
	}
	return (sign * ans);
}

void	rt_set_3d_vec(t_3d_vec *vec, double x, double y, double z)
{
	vec->x = x;
	vec->y = y;
	vec->z = z;
}

void	rt_set_rgb_vec(t_rgb_vec *vec, double r, double g, double b)
{
	vec->r = r;
	vec->g = g;
	vec->b = b;
}

void	rt_3d_vec_mult(t_3d_vec *vec, double k)
{
	vec->x *= k;
	vec->y *= k;
	vec->z *= k;
}

void	rt_rgb_vec_mult(t_rgb_vec *vec, double k)
{
	vec->r *= k;
	vec->g *= k;
	vec->b *= k;
}


void	rt_fill_struct_A(t_rt_data *rt, const char **tokens)
{
	int	i;
	double	ratio;
	double	tmp;
	char	**rgb;

	if (rt_count_str(tokens) != 3)
		rt_put_error_exit("rt file invalid format");
	ratio = ft_atof(tokens[1]);
	if (!(0.0 <= ratio && ratio <= 1.0))
		rt_put_error_exit("rt file invalid format");
	rgb = ft_split(tokens[2], ',');
	if (rgb == NULL)
		rt_perror_exit(NULL);
	if (rt_count_str((const char **)rgb) != 3)
		rt_put_error_exit("rt file invalid format");
	i = 0;
	while (i < 3)
	{
		tmp = ft_atof(rgb[i]);
		if (!(0 <= tmp && tmp <= 255))
			rt_put_error_exit("rt file invalid format");
		++i;
	}
	rt_set_rgb_vec(&rt->scene.ambient_color, ft_atof(rgb[0]), ft_atof(rgb[1]), ft_atof(rgb[2]));
	rt_double_ptr_free((const char **)rgb);
}

void	rt_fill_struct_C(t_rt_data *rt, const char **tokens)
{
	int	i;
	char	**position;
	char	**direction;
	int		fov;
	double	tmp;

	if (rt_count_str(tokens) != 4)
		rt_put_error_exit("rt file invalid format");

	position = ft_split(tokens[1], ',');
	if (rt_count_str((const char **)position) != 3)
		rt_put_error_exit("rt file invalid format");
	rt_set_3d_vec(&CAMERA_POSITION, ft_atof(position[0]),  ft_atof(position[1]),  ft_atof(position[2]));


	direction = ft_split(tokens[2], ',');
	i = 0;
	while (i < 3)
	{
		tmp = ft_atof(direction[i]);
		if (!(-1.0 <= tmp && tmp <= 1.0))
			rt_put_error_exit("rt file invalid format");
		++i;
	}
	if (rt_count_str((const char **)direction) != 3)
		rt_put_error_exit("rt file invalid format");
	rt_set_3d_vec(&UNIT_CAMERA_DIRECTION, ft_atof(direction[0]),  ft_atof(direction[1]),  ft_atof(direction[2]));


	fov = ft_atoi(tokens[3]);
	if (!(0 < fov && fov <= 180))
		rt_put_error_exit("rt file invalid format");

	SCREEN_DISTANCE = (1440 / 2) / tan(fov / 2);
	rt_vec_mult(&SCREEN_CENTER_POSITION, SCREEN_DISTANCE);

	t_3d_vec	ey;
	rt_set_3d_vec(&ey, 0, 1, 0);

	rt_vec_cross(&UNIT_SCREEN_DIRECTION_X_VEC, ey, UNIT_CAMERA_DIRECTION);
	rt_vec_cross(&UNIT_SCREEN_DIRECTION_Y_VEC, UNIT_SCREEN_DIRECTION_X_VEC, UNIT_CAMERA_DIRECTION);

	rt_double_ptr_free((const char **)position);
	rt_double_ptr_free((const char **)direction);
}
// void	rt_fill_struct_L(t_rt_data *rt, const char **tokens)
// {
// }
// void	rt_fill_struct_sp(t_rt_data *rt, const char **tokens)
// {
// }
// void	rt_fill_struct_pl(t_rt_data *rt, const char **tokens)
// {
// }
// void	rt_fill_struct_cy(t_rt_data *rt, const char **tokens)
// {
// }
// void	rt_fill_struct_cn(t_rt_data *rt, const char **tokens)
// {
// }

void	rt_fill_struct(t_rt_data *rt, const char *line)
{
	int		id;
	char	**tokens;
	// const void	(*fill_funcs[])(t_rt_data *rt, const char **tokens) = {rt_fill_struct_A, rt_fill_struct_C, rt_fill_struct_L, rt_fill_struct_sp, rt_fill_struct_pl, rt_fill_struct_cy, rt_fill_struct_cn};
	const void	(*fill_funcs[])(t_rt_data *rt, const char **tokens) = {rt_fill_struct_A, rt_fill_struct_C};


	tokens = ft_split(line, ' ');
	if (tokens == NULL)
		rt_perror_exit(NULL);
	id = rt_check_id(tokens[0]);
	if (id < 0)
		rt_put_error_exit("rt file invalid format");
	if (id < 1)
		fill_funcs[id](rt, (const char **)tokens);
	rt_double_ptr_free((const char **)tokens);
}

void	rt_import_rt_file(t_rt_data *rt, const char *file)
{
	char	*line;
	int		fd;

	(void)rt;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		rt_perror_exit(NULL);
	line = get_next_line(fd);
	while (line)
	{
		rt_fill_struct(rt, line);
		printf("%s\n", line);
		free(line);
		line = get_next_line(fd);
	}
	if (close(fd) < 0)
		rt_perror_exit(NULL);
}

void	rt_mlx(t_rt_data *rt)
{
	int	x;
	int	y;

	rt->mlx.mlx = mlx_init();
	if (!rt->mlx.mlx)
		rt_put_error_exit("mlx_init() fatal.\n");
	mlx_get_screen_size(rt->mlx.mlx, &x, &y);
	// 指定されたFOVと実行環境のディスプレイを比較して、実行環境のディスプレイが小さければ、その大きさで描画する。ということは、、、
	printf("width == %d height == %d\n", x, y);
	rt->mlx.win = mlx_new_window(rt->mlx.mlx, 1440, 900, "miniRT\n");
	if (!rt->mlx.win)
		rt_put_error_exit("mlx_new_window() fatal.\n");
	// image 作成
	// image のアドレス取得
}

void	rt_hooks(t_rt_data *rt)
{
	mlx_hook(rt->mlx.win, KeyPress, 0, rt_KeyPress, rt);
	mlx_hook(rt->mlx.win, DestroyNotify, 0, rt_DestroyNotify, rt);
	// mlx_loop_hook(rt->mlx.mlx, draw, rt);
}

