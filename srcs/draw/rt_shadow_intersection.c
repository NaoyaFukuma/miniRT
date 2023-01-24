/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_shadow_intersection.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 18:49:47 by kyamagis          #+#    #+#             */
/*   Updated: 2023/01/24 16:16:30 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_draw.h"
#include "rt_structs.h"
#include "rt_vector.h"
#include <stdbool.h>

t_ray	rt_make_shadow_ray(t_3d_vec insect_p_vec, t_lighting lighting)
{
	t_ray		shadow_ray;
	double		epsilon;

	epsilon = 1.0 / 512.0;
	shadow_ray.start = rt_vec_add(insect_p_vec, \
								rt_vec_mult(lighting.unit_d_vec, epsilon));
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
	double		epsilon;

	res = result.insec_p;
	shadow_ray = rt_make_shadow_ray(res.p_vec, lighting);
	epsilon = 1.0 / 512.0;
	shadow_res = rt_all_insec(rt->scene.objs, shadow_ray,
			lighting.dist - epsilon, true);
	if (shadow_res.insec_p.unit_n_vec.x != NOT_INTERSECT)
	{
		return (true);
	}
	return (false);
}
