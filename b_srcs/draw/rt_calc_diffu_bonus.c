/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_calc_diffu.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyamagis <kyamagis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 18:49:47 by kyamagis          #+#    #+#             */
/*   Updated: 2023/01/23 20:11:56 by kyamagis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_draw.h"
#include "rt_structs.h"
#include "rt_vector.h"
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
