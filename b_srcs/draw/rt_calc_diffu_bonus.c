/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_calc_diffu_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 18:49:47 by kyamagis          #+#    #+#             */
/*   Updated: 2023/01/24 17:03:31 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_draw_bonus.h"
#include "rt_structs_bonus.h"
#include "rt_vector_bonus.h"
#include <math.h>
#include <stdbool.h>

static t_rgb_vec	rt_get_obj_color(t_obj *obj)
{
	if (e_PLANE == obj->shape)
	{
		return (obj->plane->color);
	}
	else if (e_SPHERE == obj->shape)
	{
		return (obj->sphere->color);
	}
	else if (e_CYLINDER == obj->shape)
	{
		return (obj->cylinder->color);
	}
	else
	{
		return (obj->cone->color);
	}
}

t_rgb_vec	rt_calc_diffu(t_lighting lighting, t_insec_res \
									result, double n_dot_l)
{
	t_rgb_vec	obj_color;

	obj_color = rt_rgb_vec_mult(rt_get_obj_color(result.obj), n_dot_l);
	return (rt_rgb_vec_pi_2(lighting.intensity, obj_color));
}
