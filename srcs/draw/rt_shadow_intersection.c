/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_shadow_intersection.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyamagis <kyamagis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 18:49:47 by kyamagis          #+#    #+#             */
/*   Updated: 2023/01/23 20:04:44 by kyamagis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_draw.h"
#include "rt_structs.h"
#include "rt_vector.h"
#include <stdbool.h>

t_ray	rt_make_shadow_ray(t_3d_vec insect_p_vec, t_lighting lighting)
{
	t_ray	shadow_ray;

	shadow_ray.start = rt_vec_add(insect_p_vec, \
								rt_vec_mult(lighting.unit_d_vec, C_EPSILON));
	shadow_ray.unit_d_vec = lighting.unit_d_vec;
	return (shadow_ray);
}

double	rt_constrain(double num, double low, double high)
{
	return (rt_min(rt_max(num, low), high));
}

bool	rt_shadow_intersection(t_rt_data *rt, t_insec_res result, \
											t_lighting lighting)
{
	t_insec_res	shadow_res;
	t_insec_p	res;
	t_ray		shadow_ray;

	res = result.insec_p;
	shadow_ray = rt_make_shadow_ray(res.p_vec, lighting);
	shadow_res = rt_all_insec(rt->scene.objs, shadow_ray, \
								lighting.dist - C_EPSILON, true);
	if (shadow_res.insec_p.unit_n_vec.x != NOT_INTERSECT)
	{
		return (true);
	}
	return (false);
}
