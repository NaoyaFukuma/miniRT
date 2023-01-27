/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_fill_struct_dl_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyamagis <kyamagis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 13:18:36 by nfukuma           #+#    #+#             */
/*   Updated: 2023/01/27 22:58:42 by kyamagis         ###   ########.fr       */
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

t_3d_vec	rt_calc_g_and_length(t_delta *delta)
{
	t_3d_vec	a_b;
	t_3d_vec	a_b_c;

	a_b = rt_vec_add(delta->a, delta->b);
	a_b_c = rt_vec_add(a_b, delta->c);
	return (rt_vec_mult(a_b_c, 1.0 / 3.0));
}

t_3d_vec	rt_calc_dl_unit_n_vec(t_delta *delta)
{
	t_3d_vec	a_b;
	t_3d_vec	c_b;
	t_3d_vec	n_vec;

	a_b = rt_vec_sub(delta->a, delta->b);
	c_b = rt_vec_sub(delta->c, delta->b);
	n_vec = rt_vec_cross(a_b, c_b);
	return (rt_vec_mult(rt_vec_to_unit(n_vec), -1));
}

void	rt_fill_struct_dl(t_rt_data *rt, const char **tokens)
{
	t_obj	*obj_ptr;

	if (rt_count_str(tokens) != 5)
		rt_put_rt_file_format_error_exit("Not four delta elements");
	obj_ptr = rt_new_obj(rt, e_DELTA);
	obj_ptr->delta->a = rt_str_to_3dvector(tokens[1], -DBL_MAX, DBL_MAX);
	obj_ptr->delta->b = rt_str_to_3dvector(tokens[2], -DBL_MAX, DBL_MAX);
	obj_ptr->delta->c = rt_str_to_3dvector(tokens[3], -DBL_MAX, DBL_MAX);
	obj_ptr->delta->color = rt_str_to_rbg(tokens[4]);
	obj_ptr->delta->g = rt_calc_g_and_length(obj_ptr->delta);
	obj_ptr->delta->unit_n_vec = rt_calc_dl_unit_n_vec(obj_ptr->delta);
	// if (rt_vec_mag(obj_ptr->delta->unit_norm_vec) != 1.0)
	// {
	// 	ft_putstr_fd("delta orientation vec not normarized\n", 2);
	// 	obj_ptr->delta->unit_norm_vec
	// 		= rt_vec_to_unit(obj_ptr->delta->unit_norm_vec);
	// }
}
