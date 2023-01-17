/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_fill_struct_sp_pl_cy_cn.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 13:18:36 by nfukuma           #+#    #+#             */
/*   Updated: 2023/01/17 15:52:29 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "rt_init_utils.h"
#include "rt_put_error.h"
#include "rt_strucs.h"
#include "rt_vector.h"
#include <math.h>
#include <stdlib.h>
#include <float.h>

#include <stdio.h> // for debug

void	rt_fill_struct_sp(t_rt_data *rt, const char **tokens)
{
	t_obj	*obj_ptr;

	if (rt_count_str(tokens) != 4)
		rt_put_error_exit("rt file invalid format");
	obj_ptr = rt_new_obj(rt, E_SPHERE);
	obj_ptr->sphere->center_position = rt_str_to_3dvector(tokens[1], -DBL_MAX, DBL_MAX);
	obj_ptr->sphere->radius = ft_atof(tokens[2]) / 2;
	obj_ptr->sphere->color = rt_str_to_rbg(tokens[3]);

	printf("obj_ptr->sphere->center_position x[%f] y[%f] z[%f]\n",
			obj_ptr->sphere->center_position.x,
			obj_ptr->sphere->center_position.y,
			obj_ptr->sphere->center_position.z);
	printf("obj_ptr->sphere->radius [%f]\n", obj_ptr->sphere->radius);
	printf("rt->scene.objs->sphere->color r = %f g = %f b = %f\n",
			rt->scene.objs->sphere->color.r,
			rt->scene.objs->sphere->color.g,
			rt->scene.objs->sphere->color.b);
}

void	rt_fill_struct_pl(t_rt_data *rt, const char **tokens)
{
	t_obj	*obj_ptr;

	if (rt_count_str(tokens) != 4)
		rt_put_error_exit("rt file invalid format");
	obj_ptr = rt_new_obj(rt, E_PLANE);
	obj_ptr->plane->position = rt_str_to_3dvector(tokens[1], -DBL_MAX, DBL_MAX);
	obj_ptr->plane->unit_normal_vec = rt_str_to_3dvector(tokens[2], -1.0, 1.0);
	obj_ptr->plane->color = rt_str_to_rbg(tokens[3]);
	printf("obj_ptr->plane->position x[%f] y[%f] z[%f]\n",
			obj_ptr->plane->position.x,
			obj_ptr->plane->position.y,
			obj_ptr->plane->position.z);
	printf("obj_ptr->plane->unit_normal_vec x[%f] y[%f] z[%f]\n",
			obj_ptr->plane->unit_normal_vec.x,
			obj_ptr->plane->unit_normal_vec.y,
			obj_ptr->plane->unit_normal_vec.z);
	printf("obj_ptr->plane->color r = %f g = %f b = %f\n",
			obj_ptr->plane->color.r,
			obj_ptr->plane->color.g,
			obj_ptr->plane->color.b);

}

void	rt_fill_struct_cy(t_rt_data *rt, const char **tokens)
{
	t_obj	*obj_ptr;

	if (rt_count_str(tokens) != 6)
		rt_put_error_exit("rt file invalid format");
	obj_ptr = rt_new_obj(rt, E_CYLINDER);
	obj_ptr->cylinder->center_position = rt_str_to_3dvector(tokens[1], -DBL_MAX, DBL_MAX);
	obj_ptr->cylinder->unit_orientation_vec = rt_str_to_3dvector(tokens[2], -1.0, 1.0);
	obj_ptr->cylinder->radius = ft_atof(tokens[3]) / 2;
	obj_ptr->cylinder->height = ft_atof(tokens[4]);
	obj_ptr->cylinder->color = rt_str_to_rbg(tokens[5]);

	printf("obj_ptr->cylinder->center_position x[%f] y[%f] z[%f]\n",
			obj_ptr->cylinder->center_position.x,
			obj_ptr->cylinder->center_position.y,
			obj_ptr->cylinder->center_position.z);
	printf("obj_ptr->cylinder->unit_orientation_vec x[%f] y[%f] z[%f]\n",
			obj_ptr->cylinder->unit_orientation_vec.x,
			obj_ptr->cylinder->unit_orientation_vec.y,
			obj_ptr->cylinder->unit_orientation_vec.z);
	printf("obj_ptr->cylinder->radius [%f]\n", obj_ptr->cylinder->radius);
	printf("obj_ptr->cylinder->radius [%f]\n", obj_ptr->cylinder->height);
	printf("obj_ptr->cylinder->color r = %f g = %f b = %f\n",
			obj_ptr->cylinder->color.r,
			obj_ptr->cylinder->color.g,
			obj_ptr->cylinder->color.b);

}

void	rt_fill_struct_cn(t_rt_data *rt, const char **tokens)
{
	t_obj	*obj_ptr;

	if (rt_count_str(tokens) != 6)
		rt_put_error_exit("rt file invalid format");
	obj_ptr = rt_new_obj(rt, E_CONE);
	obj_ptr->cone->center_position = rt_str_to_3dvector(tokens[1], -DBL_MAX, DBL_MAX);
	obj_ptr->cone->unit_orientation_vec = rt_str_to_3dvector(tokens[2], -1.0, 1.0);
	obj_ptr->cone->radius = ft_atof(tokens[3]) / 2;
	obj_ptr->cone->height = ft_atof(tokens[4]);
	obj_ptr->cone->color = rt_str_to_rbg(tokens[5]);

	printf("obj_ptr->cone->center_position x[%f] y[%f] z[%f]\n",
			obj_ptr->cone->center_position.x,
			obj_ptr->cone->center_position.y,
			obj_ptr->cone->center_position.z);
	printf("obj_ptr->cone->unit_orientation_vec x[%f] y[%f] z[%f]\n",
			obj_ptr->cone->unit_orientation_vec.x,
			obj_ptr->cone->unit_orientation_vec.y,
			obj_ptr->cone->unit_orientation_vec.z);
	printf("obj_ptr->cone->radius [%f]\n", obj_ptr->cone->radius);
	printf("obj_ptr->cone->radius [%f]\n", obj_ptr->cone->height);
	printf("obj_ptr->cone->color r = %f g = %f b = %f\n",
			obj_ptr->cone->color.r,
			obj_ptr->cone->color.g,
			obj_ptr->cone->color.b);

}
