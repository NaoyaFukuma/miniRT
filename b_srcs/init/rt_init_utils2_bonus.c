/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_init_utils2_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 15:53:27 by nfukuma           #+#    #+#             */
/*   Updated: 2023/01/30 12:42:28 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "rt_define_bonus.h"
#include "rt_init_utils_bonus.h"
#include "rt_put_error_bonus.h"
#include "rt_structs_bonus.h"
#include "rt_vector_bonus.h"
#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define VEC_MAX 1000000.000000 // 基準がわからない！とりあえず拾ってきたNGファイルの数値を入れている

bool	rt_check_decimal_point(const char *str)
{
	size_t	i;
	char	*point_inx;

	point_inx = ft_strchr(str, '.');
	if (point_inx == NULL)
		return (true);
	i = 1;
	while (point_inx[i] != '\0')
	{
		if (ft_isdigit(point_inx[i]) == false)
			break ;
		++i;
	}
	if (3 < i)
		return (false);
	else
		return (true);
}

t_obj	*rt_new_obj(t_rt_data *rt, int shapes_id)
{
	t_obj	*new_obj;

	new_obj = ft_calloc(1, sizeof(t_obj));
	if (new_obj == NULL)
		rt_perror_exit(NULL);
	new_obj->shape = shapes_id;
	if (shapes_id == e_SPHERE)
		new_obj->sphere = malloc(sizeof(t_sphere));
	if (shapes_id == e_PLANE)
		new_obj->plane = malloc(sizeof(t_plane));
	if (shapes_id == e_CYLINDER)
		new_obj->cylinder = malloc(sizeof(t_cylinder));
	if (shapes_id == e_CONE)
		new_obj->cone = malloc(sizeof(t_cone));
	if (shapes_id == e_DELTA)
		new_obj->delta = malloc(sizeof(t_delta));
	if ((shapes_id == e_SPHERE && !new_obj->sphere) || (shapes_id == e_PLANE
			&& !new_obj->plane) || (shapes_id == e_CYLINDER
			&& !new_obj->cylinder) || (shapes_id == e_CONE && !new_obj->cone)
		|| (shapes_id == e_DELTA && !new_obj->delta))
		rt_perror_exit(NULL);
	rt_addback_objs_list(&rt->scene.objs, new_obj);
	return (new_obj);
}

static void	rt_check_value(const char **elements, double min, double max)
{
	double	tmp;
	int		i;

	i = 0;
	while (i < 3)
	{
		tmp = ft_atof(elements[i]);
		if (errno == ERANGE)
			rt_put_rt_file_format_error_exit(ER_RANGE);
		if (rt_check_decimal_point(elements[i]) == false)
			rt_put_rt_file_format_error_exit(ER_DECIMAL);
		if (!(min <= tmp && tmp <= max))
			rt_put_rt_file_format_error_exit("Vector elements not in range");
		if (!(-VEC_MAX < tmp && tmp < VEC_MAX))
			rt_put_rt_file_format_error_exit(ER_ELE);
		++i;
	}
}

t_3d_vec	rt_str_to_3dvector(const char *str, double min, double max)
{
	char		**elements;
	t_3d_vec	tmp;

	elements = ft_split(str, ',');
	if (elements == NULL)
		rt_perror_exit("ft_split() failure");
	if (rt_count_str((const char **)elements) != 3)
		rt_put_rt_file_format_error_exit("Not 3 vector elements");
	rt_check_value((const char **)elements, min, max);
	tmp = rt_vec_constructor(ft_atof(elements[0]), ft_atof(elements[1]),
			ft_atof(elements[2]));
	rt_double_ptr_free((const char **)elements);
	return (tmp);
}

t_rgb_vec	rt_str_to_rbg(const char *str)
{
	int			i;
	int			tmp;
	char		**rgb;
	t_rgb_vec	tmp_rgb;

	rgb = ft_split(str, ',');
	if (rgb == NULL)
		rt_perror_exit(NULL);
	if (rt_count_str((const char **)rgb) != 3)
		rt_put_rt_file_format_error_exit("Not three RGB elements");
	i = -1;
	while (++i < 3)
	{
		if (ft_strchar(rgb[i], '.'))
			rt_put_rt_file_format_error_exit(ER_NOT_INT);
		tmp = ft_atoi(rgb[i]);
		if (errno == ERANGE)
			rt_put_rt_file_format_error_exit(ER_OVER_FLOW);
		if (!(0 <= tmp && tmp <= 255))
			rt_put_rt_file_format_error_exit(ER_RGB_RANGE);
	}
	tmp_rgb = rt_rgb_vec_constructor(ft_atof(rgb[0]) / 255.0,
			ft_atof(rgb[1]) / 255.0, ft_atof(rgb[2]) / 255.0);
	rt_double_ptr_free((const char **)rgb);
	return (tmp_rgb);
}
