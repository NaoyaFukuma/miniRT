/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_raytrace.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 18:49:47 by kyamagis          #+#    #+#             */
/*   Updated: 2023/01/24 14:50:54 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_draw.h"
#include "rt_structs.h"
#include "rt_vector.h"
#include <stdbool.h>

t_lighting	rt_calc_lighting_at_intersection(t_p_lite_src *pls,
													t_3d_vec insect_p_vec)
{
	t_lighting	res;
	t_3d_vec	tmp_direction;

	tmp_direction = rt_vec_sub(pls->p_vec, insect_p_vec);
	res.dist = rt_vec_mag(tmp_direction);
	res.unit_d_vec = rt_vec_to_unit(tmp_direction);
	res.intensity = pls->lite_color;
	return (res);
}

t_rgb_vec	rt_add_spec_and_diffu_with_all(t_rt_data *rt, t_3d_vec eye_dir, \
											t_insec_res result)
{
	t_p_lite_src	*pls;
	t_rgb_vec		col;
	t_lighting		lighting;
	t_rgb_vec		spec_and_diffu;

	pls = rt->scene.pls_s;
	col = rt_rgb_vec_constructor_3(0);
	while (pls)
	{
		lighting = rt_calc_lighting_at_intersection(pls, result.insec_p.p_vec);
		if (rt_shadow_intersection(rt, result, lighting) == true)
		{
			pls = pls->next;
			continue ;
		}
		spec_and_diffu = rt_calc_spec_and_diffu(rt, eye_dir, result, lighting);
		col = rt_rgb_vec_add(col, spec_and_diffu);
		pls = pls->next;
	}
	return (col);
}

t_rgb_vec	rt_raytrace(t_rt_data *rt, t_ray ray)
{
	t_insec_res	result;
	t_rgb_vec	amb;
	t_rgb_vec	spec_diffu;

	result = rt_all_insec_ambient(rt->scene.objs, ray);
	if (result.insec_p.unit_n_vec.x == NOT_INTERSECT)
	{
		return (rt_rgb_vec_constructor(NOT_INTERSECT, 0, 0));
	}
	amb = rt_rgb_vec_pi_2(rt->scene.amb_color, rt->scene.material.amb_fact);
	spec_diffu = rt_add_spec_and_diffu_with_all(rt, ray.unit_d_vec, result);
	return (rt_rgb_vec_add(amb, spec_diffu));
}
