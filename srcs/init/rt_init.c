/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 14:53:32 by nfukuma           #+#    #+#             */
/*   Updated: 2023/01/17 11:53:47 by nfukuma          ###   ########.fr       */
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
#include "rt_vector.h"

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
	rt_mlx(rt);
	rt_import_rt_file(rt, file);
	rt_hooks(rt);
	mlx_loop(rt->mlx.mlx);
	MATERIAL_AMBIENTFACTOR = rt_rgb_vec_constructor(1.00f, 1.00f, 1.00f);
	MATERIAL_DIFFUSEFACTOR = rt_rgb_vec_constructor(0.69f, 0.69f, 0.69f);
	MATERIAL_SPECULARFACTOR = rt_rgb_vec_constructor(0.30f, 0.30f, 0.30f);
	MATERIAL_SHININESS = 8.0f;
	printf("MATERIAL_AMBIENTFACTOR r[%f] g[%f] b[%f]\n", MATERIAL_AMBIENTFACTOR.r, MATERIAL_AMBIENTFACTOR.g, MATERIAL_AMBIENTFACTOR.b );
	printf("MATERIAL_DIFFUSEFACTOR r[%f] g[%f] b[%f]\n", MATERIAL_DIFFUSEFACTOR.r, MATERIAL_DIFFUSEFACTOR.g, MATERIAL_DIFFUSEFACTOR.b );
	printf("MATERIAL_SPECULARFACTOR r[%f] g[%f] b[%f]\n", MATERIAL_SPECULARFACTOR.r, MATERIAL_SPECULARFACTOR.g, MATERIAL_SPECULARFACTOR.b );
	printf("MATERIAL_SHININESS [%f]\n", MATERIAL_SHININESS);
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
	{
		if (!ft_strcmp(str, id_set[id]))
			break ;
		++id;
	}
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

void	rt_addback_objs_list(t_obj **begin, t_obj *new)
{
	t_obj *tmp;
	if (*begin == NULL)
	{
		*begin = new;
		return;
	}
	tmp = *begin;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
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
	rt->scene.ambient_color = rt_rgb_vec_constructor(ratio * ft_atof(rgb[0]), ratio * ft_atof(rgb[1]), ratio * ft_atof(rgb[2]));
	printf("ambient r = %f g = %f b = %f\n", rt->scene.ambient_color.r, rt->scene.ambient_color.g, rt->scene.ambient_color.b);
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

	CAMERA_POSITION = rt_vector_constructor(ft_atof(position[0]),  ft_atof(position[1]),  ft_atof(position[2]));


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
	UNIT_CAMERA_DIRECTION = rt_vector_constructor(ft_atof(direction[0]),  ft_atof(direction[1]),  ft_atof(direction[2]));

	fov = ft_atoi(tokens[3]);
	if (!(0 < fov && fov <= 180))
		rt_put_error_exit("rt file invalid format");
	SCREEN_DISTANCE = (rt->scene.screean_width / 2) / tan((long double)fov * M_PI / 180.0l / 2.0l);

	SCREEN_CENTER_POSITION = rt_vector_add(CAMERA_POSITION, rt_vector_mult(UNIT_CAMERA_DIRECTION, SCREEN_DISTANCE));

	t_3d_vec	ey = rt_vector_constructor(0, 1, 0);
	UNIT_SCREEN_DIRECTION_X_VEC = rt_vector_cross(UNIT_CAMERA_DIRECTION, ey);
	UNIT_SCREEN_DIRECTION_Y_VEC = rt_vector_cross(UNIT_SCREEN_DIRECTION_X_VEC, UNIT_CAMERA_DIRECTION);

	printf("camera posi x = %f  y = %f z = %f\n", CAMERA_POSITION.x,CAMERA_POSITION.y,CAMERA_POSITION.z);
	printf("camera dir x = %f  y = %f z = %f\n", UNIT_CAMERA_DIRECTION.x,UNIT_CAMERA_DIRECTION.y,UNIT_CAMERA_DIRECTION.z);
	printf("fov == %d\n", fov);
	printf("rt->scene.screean_width / 2 == %d * tan((long double)fov * M_PI / 180.0l / 2.0l) == %f   ", rt->scene.screean_width / 2, tan((long double)fov * M_PI / 180.0l / 2.0l));
	printf("distance = %f\n",SCREEN_DISTANCE);
	printf("screen center position x = %f  y = %f z = %f\n", SCREEN_CENTER_POSITION.x,SCREEN_CENTER_POSITION.y,SCREEN_CENTER_POSITION.z);
	printf("screen dir_x x = %f  y = %f z = %f\n", UNIT_SCREEN_DIRECTION_X_VEC.x,UNIT_SCREEN_DIRECTION_X_VEC.y,UNIT_SCREEN_DIRECTION_X_VEC.z);
	printf("screen dir_y  x = %f  y = %f z = %f\n", UNIT_SCREEN_DIRECTION_Y_VEC.x,UNIT_SCREEN_DIRECTION_Y_VEC.y,UNIT_SCREEN_DIRECTION_Y_VEC.z);

	rt_double_ptr_free((const char **)position);
	rt_double_ptr_free((const char **)direction);
}

void	rt_fill_struct_L(t_rt_data *rt, const char **tokens)
{
	int	i;
	char	**position;
	double	ratio;
	char	**rgb;

	double	tmp;


	if (rt_count_str(tokens) != 4)
		rt_put_error_exit("rt file invalid format");

	position = ft_split(tokens[1], ',');
	if (rt_count_str((const char **)position) != 3)
		rt_put_error_exit("rt file invalid format");

	POINT_LITE_POSITION = rt_vector_constructor(ft_atof(position[0]),  ft_atof(position[1]),  ft_atof(position[2]));



	ratio = ft_atof(tokens[2]);
	if (!(0.0 <= ratio && ratio <= 1.0))
		rt_put_error_exit("rt file invalid format");
	rgb = ft_split(tokens[3], ',');
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
	POINT_LITE_COLOR = rt_rgb_vec_constructor(ratio * ft_atof(rgb[0]), ratio * ft_atof(rgb[1]), ratio * ft_atof(rgb[2]));

	printf("point lite souce\nposition x[%f] y[%f] z[%f]\n", POINT_LITE_POSITION.x,POINT_LITE_POSITION.y,POINT_LITE_POSITION.z);
	printf("color r[%f] g[%f] b[%f]\n", POINT_LITE_POSITION.x,POINT_LITE_POSITION.y,POINT_LITE_POSITION.z);

	rt_double_ptr_free((const char **)position);
}

void	rt_fill_struct_sp(t_rt_data *rt, const char **tokens)
{
	int	i;
	double	tmp;
	char	**rgb;
	char	**position;
	t_obj *obj_ptr;

	obj_ptr = malloc(sizeof (t_obj));
	rt_addback_objs_list(&rt->scene.objs, obj_ptr);
	if (obj_ptr == NULL)
		rt_perror_exit(NULL);
	obj_ptr->next = NULL;
	obj_ptr->plane = NULL;
	obj_ptr->cylinder = NULL;
	obj_ptr->cone = NULL;
	obj_ptr->shape = E_SPHERE;
	obj_ptr->sphere = malloc(sizeof(t_sphere));
	if (obj_ptr->sphere == NULL)
		rt_perror_exit(NULL);


	if (rt_count_str(tokens) != 4)
		rt_put_error_exit("rt file invalid format");

	position = ft_split(tokens[1], ',');
	if (rt_count_str((const char **)position) != 3)
		rt_put_error_exit("rt file invalid format");

	obj_ptr->sphere->center_position = rt_vector_constructor(ft_atof(position[0]),  ft_atof(position[1]),  ft_atof(position[2]));

	obj_ptr->sphere->radius = ft_atof(tokens[2]);

	rgb = ft_split(tokens[3], ',');
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
	rt->scene.objs->sphere->color = rt_rgb_vec_constructor(ft_atof(rgb[0]), ft_atof(rgb[1]), ft_atof(rgb[2]));

	printf("obj_ptr->sphere->center_position x[%f] y[%f] z[%f]\n", obj_ptr->sphere->center_position.x, obj_ptr->sphere->center_position.y,obj_ptr->sphere->center_position.z);
	printf("obj_ptr->sphere->radius [%f]\n", obj_ptr->sphere->radius);
	printf("rt->scene.objs->sphere->color r = %f g = %f b = %f\n", rt->scene.objs->sphere->color.r, rt->scene.objs->sphere->color.g, rt->scene.objs->sphere->color.b);

	rt_double_ptr_free((const char **)position);
	rt_double_ptr_free((const char **)rgb);
}

void	rt_fill_struct_pl(t_rt_data *rt, const char **tokens)
{
	int	i;
	double	tmp;
	char	**rgb;
	char	**position;
	char	**orient_vec;
	t_obj *obj_ptr;

	obj_ptr = malloc(sizeof (t_obj));
	rt_addback_objs_list(&rt->scene.objs, obj_ptr);
	if (obj_ptr == NULL)
		rt_perror_exit(NULL);
	obj_ptr->next = NULL;
	obj_ptr->sphere = NULL;
	obj_ptr->cylinder = NULL;
	obj_ptr->cone = NULL;
	obj_ptr->shape = E_PLANE;
	obj_ptr->plane = malloc(sizeof(t_plane));
	if (obj_ptr->plane == NULL)
		rt_perror_exit(NULL);


	if (rt_count_str(tokens) != 4)
		rt_put_error_exit("rt file invalid format");

	position = ft_split(tokens[1], ',');
	if (rt_count_str((const char **)position) != 3)
		rt_put_error_exit("rt file invalid format");

	obj_ptr->plane->position = rt_vector_constructor(ft_atof(position[0]),  ft_atof(position[1]),  ft_atof(position[2]));

	orient_vec = ft_split(tokens[2], ',');
	if (rt_count_str((const char **)position) != 3)
		rt_put_error_exit("rt file invalid format");

	i = 0;
	while (i < 3)
	{
		tmp = ft_atof(orient_vec[i]);
		if (!(-1.0 <= tmp && tmp <= 1.0))
			rt_put_error_exit("rt file invalid format");
		++i;
	}

	obj_ptr->plane->unit_normal_vec = rt_vector_constructor(ft_atof(orient_vec[0]),  ft_atof(orient_vec[1]),  ft_atof(orient_vec[2]));



	rgb = ft_split(tokens[3], ',');
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
	obj_ptr->plane->color = rt_rgb_vec_constructor(ft_atof(rgb[0]), ft_atof(rgb[1]), ft_atof(rgb[2]));

	printf("obj_ptr->plane->position x[%f] y[%f] z[%f]\n", obj_ptr->plane->position.x, obj_ptr->plane->position.y,obj_ptr->plane->position.z);
	printf("obj_ptr->plane->unit_normal_vec x[%f] y[%f] z[%f]\n", obj_ptr->plane->unit_normal_vec.x, obj_ptr->plane->unit_normal_vec.y,obj_ptr->plane->unit_normal_vec.z);
	printf("rt->scene.objs->plane->color r = %f g = %f b = %f\n", rt->scene.objs->plane->color.r, rt->scene.objs->plane->color.g, rt->scene.objs->plane->color.b);

	rt_double_ptr_free((const char **)position);
	rt_double_ptr_free((const char **)orient_vec);
	rt_double_ptr_free((const char **)rgb);

}
void	rt_fill_struct_cy(t_rt_data *rt, const char **tokens)
{
	(void)rt;
	(void)tokens;
}
void	rt_fill_struct_cn(t_rt_data *rt, const char **tokens)
{
	(void)rt;
	(void)tokens;
}

void	rt_fill_struct(t_rt_data *rt, const char *line)
{
	int		id;
	char	**tokens;
	void	(* const fill_funcs[])(t_rt_data *rt, const char **tokens) = {rt_fill_struct_A, rt_fill_struct_C, rt_fill_struct_L, rt_fill_struct_sp, rt_fill_struct_pl, rt_fill_struct_cy, rt_fill_struct_cn};

	tokens = ft_split(line, ' ');
	if (tokens == NULL)
		rt_perror_exit(NULL);
	id = rt_check_id(tokens[0]);
	if (id < 0)
		rt_put_error_exit("rt file invalid format");
	fill_funcs[id](rt, (const char **)tokens);
	rt_double_ptr_free((const char **)tokens);
}

void	rt_import_rt_file(t_rt_data *rt, const char *file)
{
	char	*line;
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		rt_perror_exit(NULL);
	line = get_next_line(fd);
	while (line)
	{
		printf("\n%s", line);
		rt_fill_struct(rt, line);
		free(line);
		line = get_next_line(fd);
	}
	if (close(fd) < 0)
		rt_perror_exit(NULL);
}

void	rt_mlx(t_rt_data *rt)
{
	rt->mlx.mlx = mlx_init();
	if (!rt->mlx.mlx)
		rt_put_error_exit("mlx_init() fatal.\n");
	mlx_get_screen_size(rt->mlx.mlx, &rt->scene.screean_width, &rt->scene.screean_height);
	rt->scene.screean_width /= 2;
	rt->scene.screean_height /= 2;
	rt->mlx.win = mlx_new_window(rt->mlx.mlx, rt->scene.screean_width, rt->scene.screean_height, "Bravo! Bravo!! Bravo!!!!!");
	rt->mlx.image.width = rt->scene.screean_width;
	rt->mlx.image.height = rt->scene.screean_height;

	if (!rt->mlx.win)
		rt_put_error_exit("mlx_new_window() fatal.\n");
	rt->mlx.image.img = mlx_new_image(rt->mlx.mlx, rt->mlx.image.width, rt->mlx.image.height);
	if (!rt->mlx.image.img)
		rt_put_error_exit("mlx_new_window() fatal.\n");
	rt->mlx.image.addr = mlx_get_data_addr(rt->mlx.image.img, &rt->mlx.image.bits_per_pixel, &rt->mlx.image.line_length, &rt->mlx.image.endian);
	if (!rt->mlx.image.addr)
		rt_put_error_exit("mlx_new_window() fatal.\n");
}

void	rt_hooks(t_rt_data *rt)
{
	mlx_hook(rt->mlx.win, KeyPress, 0, rt_KeyPress, rt);
	mlx_hook(rt->mlx.win, DestroyNotify, 0, rt_DestroyNotify, rt);

}
