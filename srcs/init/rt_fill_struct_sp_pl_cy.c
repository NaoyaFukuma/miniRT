/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_fill_struct_sp_pl_cy.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyamagis <kyamagis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 13:18:36 by nfukuma           #+#    #+#             */
/*   Updated: 2023/02/02 13:08:54 by kyamagis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "rt_init_utils.h"
#include "rt_put_error.h"
#include "rt_structs.h"
#include "rt_vector.h"
#include <math.h>
#include <stdlib.h>
#include <float.h>
#include <errno.h>
#include <rt_define.h>

#include <stdio.h>

void	rt_fill_struct_sp(t_rt_data *rt, const char **tokens)
{
	t_obj	*obj_ptr;

	if (rt_count_str(tokens) != 4)
		rt_put_rt_file_format_error_exit("Not four sphere light elements");
	obj_ptr = rt_new_obj(rt, e_SPHERE);
	obj_ptr->sphere->center_p_vec
		= rt_str_to_3dvector(tokens[1], -DBL_MAX, DBL_MAX);
	if (rt_check_decimal_point(tokens[2]) == false)
		rt_put_rt_file_format_error_exit(ER_SP_DIA);
	obj_ptr->sphere->radius = ft_atof(tokens[2]);
	if (obj_ptr->sphere->radius <= 0 || errno == ERANGE)
		rt_put_rt_file_format_error_exit("Sphere diameter is invalid value");
	obj_ptr->sphere->radius /= 2.0;
	obj_ptr->sphere->color = rt_str_to_rbg(tokens[3]);
}

void	rt_fill_struct_pl(t_rt_data *rt, const char **tokens)
{
	t_obj	*obj_ptr;

	if (rt_count_str(tokens) != 4)
		rt_put_rt_file_format_error_exit("Not four plane elements");
	obj_ptr = rt_new_obj(rt, e_PLANE);
	obj_ptr->plane->p_vec = rt_str_to_3dvector(tokens[1], -DBL_MAX, DBL_MAX);
	obj_ptr->plane->unit_norm_vec = rt_str_to_3dvector(tokens[2], -1.0, 1.0);
	obj_ptr->plane->color = rt_str_to_rbg(tokens[3]);
	obj_ptr->plane->defalt_color = obj_ptr->plane->color;
	if (rt_vec_mag(obj_ptr->plane->unit_norm_vec) != 1.0)
	{
		ft_putstr_fd("Plane orientation vec not normarized\n", 2);
		obj_ptr->plane->unit_norm_vec
			= rt_vec_to_unit(obj_ptr->plane->unit_norm_vec);
	}
}

void	rt_fill_struct_cy_sub(t_obj *obj_ptr, const char **tokens)
{
	obj_ptr->cylinder->center_p_vec
		= rt_str_to_3dvector(tokens[1], -DBL_MAX, DBL_MAX);
	obj_ptr->cylinder->unit_orient_vec
		= rt_str_to_3dvector(tokens[2], -1.0, 1.0);
	if (rt_vec_mag(obj_ptr->cylinder->unit_orient_vec) != 1.0)
	{
		ft_putstr_fd("Cylinder orientation vec not normarized\n", 2);
		obj_ptr->cylinder->unit_orient_vec
			= rt_vec_to_unit(obj_ptr->cylinder->unit_orient_vec);
	}
	if (rt_check_decimal_point(tokens[4]) == false)
		rt_put_rt_file_format_error_exit(ER_CY_DIA);
	obj_ptr->cylinder->radius = ft_atof(tokens[3]);
	if (obj_ptr->cylinder->radius <= 0 || errno == ERANGE)
		rt_put_rt_file_format_error_exit("Cylinder height invalid value");
}

void	rt_fill_struct_cy(t_rt_data *rt, const char **tokens)
{
	t_obj	*obj_ptr;

	if (rt_count_str(tokens) != 6)
		rt_put_rt_file_format_error_exit("rt file invalid format");
	obj_ptr = rt_new_obj(rt, e_CYLINDER);
	rt_fill_struct_cy_sub(obj_ptr, tokens);
	obj_ptr->cylinder->radius /= 2;
	if (rt_check_decimal_point(tokens[4]) == false)
		rt_put_rt_file_format_error_exit(ER_CY_HEI);
	obj_ptr->cylinder->height = ft_atof(tokens[4]);
	if (obj_ptr->cylinder->height <= 0 || errno == ERANGE)
		rt_put_rt_file_format_error_exit("Cylinder height invalid value");
	obj_ptr->cylinder->color = rt_str_to_rbg(tokens[5]);
	if (obj_ptr->cylinder->radius <= 1.0 / 512.0)
		return ;
	obj_ptr->cylinder->radius -= 1.0 / 512.0;
	if (FLT_MAX - 1.0 / 512.0 < obj_ptr->cylinder->height)
		return ;
	obj_ptr->cylinder->height += 1.0 / 512.0;
}
