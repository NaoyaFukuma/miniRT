/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_init_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 15:53:27 by nfukuma           #+#    #+#             */
/*   Updated: 2023/01/18 15:17:30 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_strucs.h"
#include "rt_init_utils.h"
#include "rt_vector.h"
#include "libft.h"
#include "rt_put_error.h"
#include <stdlib.h>
#include <errno.h>
#include <math.h>

#include <stdio.h>

#define VEC_MAX 1000000.000000 // 基準がわからない！とりあえず拾ってきたNGファイルの数値を入れている

t_obj	*rt_new_obj(t_rt_data *rt, int shapes_id)
{
	t_obj	*new_obj;

	new_obj = ft_calloc(1, sizeof(t_obj));
	if (new_obj == NULL)
		rt_perror_exit(NULL);
	new_obj->shape = shapes_id;
	if (shapes_id == E_SPHERE)
		new_obj->sphere = malloc(sizeof(t_sphere));
	if (shapes_id == E_PLANE)
		new_obj->plane = malloc(sizeof(t_plane));
	if (shapes_id == E_CYLINDER)
		new_obj->cylinder = malloc(sizeof(t_cylinder));
	if (shapes_id == E_CONE)
		new_obj->cone = malloc(sizeof(t_cone));
	if ((shapes_id == E_SPHERE && !new_obj->sphere) || (shapes_id == E_PLANE
			&& !new_obj->plane) || (shapes_id == E_CYLINDER
			&& !new_obj->cylinder) || (shapes_id == E_CONE && !new_obj->cone))
		rt_perror_exit(NULL);
	rt_addback_objs_list(&rt->scene.objs, new_obj);
	return (new_obj);
}

t_3d_vec	rt_str_to_3dvector(const char *str, double min, double max)
{
	int		i;
	double	tmp;
	char	**elements;
	double	mod;

	elements = ft_split(str, ',');
	if (elements == NULL)
		rt_perror_exit(NULL);
	if (rt_count_str((const char **)elements) != 3)
		rt_put_rt_file_format_error_exit("Not 3 vector elements");
	i = 0;
	while (i < 3)
	{
		tmp = ft_atof(elements[i]);
		mod = fmod(tmp / 0.01 , 10);
		if (mod != 0)
			rt_put_rt_file_format_error_exit("Point light ratio are not to the first decimal place");
		if (!(min <= tmp && tmp <= max))
			rt_put_rt_file_format_error_exit("Vector elements not in range");
		if (!(-VEC_MAX < tmp && tmp < VEC_MAX))
			rt_put_rt_file_format_error_exit("Vector elements value range is lower or greater");
		++i;
	}
	return (rt_vector_constructor(ft_atof(elements[0]), ft_atof(elements[1]), ft_atof(elements[2])));
	rt_double_ptr_free((const char **)elements);
}

t_rgb_vec	rt_str_to_rbg(const char *str)
{
	int		i;
	int		tmp;
	char	**rgb;

	rgb = ft_split(str, ',');
	if (rgb == NULL)
		rt_perror_exit(NULL);
	if (rt_count_str((const char **)rgb) != 3)
		rt_put_rt_file_format_error_exit("Not three RGB elements.");
	i = 0;
	while (i < 3)
	{
		if (ft_strchar(rgb[i], '.'))
			rt_put_rt_file_format_error_exit("RGB elements are not integer type");
		tmp = ft_atoi(rgb[i]);
		if (errno == ERANGE)
			rt_put_rt_file_format_error_exit("The value of the RGB element is overflowing");
		if (!(0 <= tmp && tmp <= 255))
			rt_put_rt_file_format_error_exit("RGB value range is not [0 - 255]");
		++i;
	}
	return (rt_rgb_vec_constructor(ft_atof(rgb[0]), ft_atof(rgb[1]), ft_atof(rgb[2])));
	rt_double_ptr_free((const char **)rgb);
}
