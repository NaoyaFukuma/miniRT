/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_raytrace_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 18:49:47 by kyamagis          #+#    #+#             */
/*   Updated: 2023/01/27 16:26:24 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_draw_bonus.h"
#include "rt_structs_bonus.h"
#include "rt_vector_bonus.h"
#include <math.h>
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

	if (result.obj->shape == e_SPHERE && result.obj->sphere->radius >= 1.5)
		result.obj->sphere->color = rt_norm_tex_mapping(rt, &result.insec_p, result.obj->sphere);
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

#define MAX_RECURSION 8

t_rgb_vec	ray_trace_recursive(t_rt_data *rt, t_ray ray, int recusion_lev);

t_ray	rt_calc_re_ray(t_insec_res result, t_3d_vec unit_v, double n_dot_v)
{
	t_3d_vec	re;
	t_ray		re_ray;

	re = rt_vec_sub(rt_vec_mult(result.insec_p.unit_n_vec, 2 * n_dot_v), unit_v);
	re_ray.start = rt_vec_add(result.insec_p.p_vec, rt_vec_mult(re, 1.0 / 512.0));
	re_ray.unit_d_vec = re;
	return (re_ray);
}

t_rgb_vec	rt_calc_r_m(t_rt_data *rt, int recusion_lev, t_ray re_ray)
{
	t_rgb_vec	r_re;

	r_re = ray_trace_recursive(rt, re_ray, recusion_lev + 1);
	if (r_re.r == NOT_INTERSECT)
	{
		r_re.r = 0;
	}
	return (rt_rgb_vec_mult(r_re, 0.8));
}

t_rgb_vec	rt_calc_comp_spec(t_rt_data *rt, t_ray ray, \
								int recusion_lev, t_insec_res result)
{
	t_3d_vec	unit_v;
	double		n_dot_v;
	t_ray		re_ray;

	unit_v = rt_vec_mult(ray.unit_d_vec, -1);
	unit_v = rt_vec_to_unit(unit_v);
	n_dot_v = rt_vec_dot(unit_v, result.insec_p.unit_n_vec);
	if (n_dot_v <= 0)
	{
		return (rt_rgb_vec_constructor_3(0));
	}
	re_ray = rt_calc_re_ray(result, unit_v, n_dot_v);
	return (rt_calc_r_m(rt, recusion_lev, re_ray));
}

t_rgb_vec	rt_calc_refraction(t_rt_data *rt, t_ray ray, \
								int recusion_lev, t_insec_res result)
{
	t_3d_vec	unit_v;
	double		n_dot_v;
	t_ray		re_ray;
	double		eta1;
	double		eta2;

	eta1 = 0.80;
	eta2 = 1.0;
	unit_v = rt_vec_mult(ray.unit_d_vec, -1);
	unit_v = rt_vec_to_unit(unit_v);
	n_dot_v = rt_vec_dot(unit_v, result.insec_p.unit_n_vec);
	if (n_dot_v < 0)
	{
		eta1 = 1.0;
		eta2 = 0.80;
		result.insec_p.unit_n_vec = rt_vec_mult(result.insec_p.unit_n_vec, -1);
		n_dot_v = rt_vec_dot(unit_v, result.insec_p.unit_n_vec);
	}
	double eta = eta2 / eta1;
	double cos1 = rt_vec_dot(unit_v, result.insec_p.unit_n_vec);
	double cos2 = eta * sqrt((eta * eta) - (1 - cos1 * cos1));
	double omega = eta * cos2 - cos1;
	re_ray.unit_d_vec = rt_vec_sub(rt_vec_mult(ray.unit_d_vec, eta), rt_vec_mult(result.insec_p.unit_n_vec, eta * omega));
	re_ray.unit_d_vec = rt_vec_to_unit(re_ray.unit_d_vec);
	re_ray.start = rt_vec_add(result.insec_p.p_vec, rt_vec_mult(re_ray.unit_d_vec, 1.0 / 512.0));
	return (rt_calc_r_m(rt, recusion_lev, re_ray));
}

t_rgb_vec	rt_calc_reflection(t_rt_data *rt, t_ray ray, \
									int recusion_lev, t_insec_res result)
{
	t_rgb_vec	amb;
	t_rgb_vec	spec_diffu;
	t_rgb_vec	r_m;
	t_rgb_vec	col;

	amb = rt_rgb_vec_pi_2(rt->scene.amb_color, rt->scene.material.amb_fact);
	spec_diffu = rt_add_spec_and_diffu_with_all(rt, ray.unit_d_vec, result);
	col = rt_rgb_vec_add(amb, spec_diffu);

	if (result.obj->shape == e_CONE)
	{
		r_m = rt_calc_comp_spec(rt, ray, recusion_lev, result);
		return (rt_rgb_vec_add(col, r_m));
	}
	if (result.obj->shape == e_SPHERE && result.obj->sphere->radius < 1.5)
	{
		r_m = rt_calc_refraction(rt, ray, recusion_lev, result);
		return (rt_rgb_vec_add(col, r_m));
	}
	return (col);
}


t_rgb_vec	ray_trace_recursive(t_rt_data *rt, t_ray ray, int recusion_lev)
{
	t_insec_res	result;

	if (recusion_lev > MAX_RECURSION )
	{
		return rt_rgb_vec_constructor(NOT_INTERSECT, 0, 0);
	}
	else
	{
		result = rt_all_insec_ambient(rt->scene.objs, ray);
		if (result.insec_p.unit_n_vec.x == NOT_INTERSECT)
		{
			return (rt_rgb_vec_constructor(NOT_INTERSECT, 0, 0));
		}
		return (rt_calc_reflection(rt, ray, recusion_lev, result));
	}
}


t_rgb_vec	rt_raytrace(t_rt_data *rt, t_ray ray)
{
	return (ray_trace_recursive(rt, ray, 0));
}
