/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_fill_struct_cn_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyamagis <kyamagis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 13:18:36 by nfukuma           #+#    #+#             */
/*   Updated: 2023/02/02 13:05:06 by kyamagis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "rt_init_utils_bonus.h"
#include "rt_put_error_bonus.h"
#include "rt_structs_bonus.h"
#include "rt_vector_bonus.h"
#include <math.h>
#include <stdlib.h>
#include <float.h>
#include <errno.h>
#include <rt_define.h>

#include <stdio.h>

void	rt_fill_struct_cn_2(const char **tokens, t_obj *obj_ptr)
{
	obj_ptr->cone->radius = ft_atof(tokens[3]);
	if (obj_ptr->cone->radius <= 0 || errno == ERANGE)
		rt_put_rt_file_format_error_exit("Cone height invalid value");
	obj_ptr->cone->radius /= 2;
	if (rt_check_decimal_point(tokens[4]) == false)
		rt_put_rt_file_format_error_exit(ER_CN_HEI);
	obj_ptr->cone->height = ft_atof(tokens[4]);
	if (obj_ptr->cone->height <= 0 || errno == ERANGE)
		rt_put_rt_file_format_error_exit("Cone height invalid value");
	obj_ptr->cone->color = rt_str_to_rbg(tokens[5]);
	if (1.0 / 512.0 < obj_ptr->cone->radius)
	{
		obj_ptr->cone->radius -= 1.0 / 512.0;
	}
	if (obj_ptr->cone->height < FLT_MAX - 1.0 / 512.0)
	{
		obj_ptr->cone->height += 1.0 / 512.0;
	}
}

void	rt_fill_struct_cn(t_rt_data *rt, const char **tokens)
{
	t_obj	*obj_ptr;

	if (rt_count_str(tokens) != 6)
		rt_put_rt_file_format_error_exit("rt file invalid format");
	obj_ptr = rt_new_obj(rt, e_CONE);
	obj_ptr->cone->center_p_vec
		= rt_str_to_3dvector(tokens[1], -DBL_MAX, DBL_MAX);
	obj_ptr->cone->unit_orient_vec = rt_str_to_3dvector(tokens[2],
			-1, 1);
	if (rt_vec_mag(obj_ptr->cone->unit_orient_vec) != 1.0)
		ft_putstr_fd("Cone orientation vec not normarized\n", 2);
	obj_ptr->cone->unit_orient_vec
		= rt_vec_to_unit(obj_ptr->cone->unit_orient_vec);
	if (rt_check_decimal_point(tokens[3]) == false)
		rt_put_rt_file_format_error_exit(ER_CN_DIA);
	rt_fill_struct_cn_2(tokens, obj_ptr);
}
