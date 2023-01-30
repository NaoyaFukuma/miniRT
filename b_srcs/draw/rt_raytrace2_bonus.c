/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_raytrace2_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 12:20:53 by nfukuma           #+#    #+#             */
/*   Updated: 2023/01/30 12:42:50 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_draw_bonus.h"
#include "rt_structs_bonus.h"
#include "rt_vector_bonus.h"
#include <math.h>
#include <stdbool.h>
#include <stdio.h>

#define MAX_RECURSION 8

t_rgb_vec	ray_trace_recursive(t_rt_data *rt, t_ray ray, int recusion_lev);

t_ray	rt_calc_re_ray(t_insec_res result, t_3d_vec unit_v, double n_dot_v)
{
	t_3d_vec	re;
	t_ray		re_ray;

	re = rt_vec_sub(rt_vec_mult(result.insec_p.unit_n_vec, 2 * n_dot_v),
			unit_v);
	re_ray.start = rt_vec_add(result.insec_p.p_vec, rt_vec_mult(re, 1.0
				/ 512.0));
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

t_rgb_vec	rt_calc_comp_spec(t_rt_data *rt, t_ray ray, int recusion_lev,
		t_insec_res result)
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

t_ray	rt_calc_re_ray2(t_ray ray, t_insec_res result, double eta, double omega)
{
	t_ray		re_ray;

	re_ray.unit_d_vec = rt_vec_sub(rt_vec_mult(ray.unit_d_vec, eta),
			rt_vec_mult(result.insec_p.unit_n_vec, eta * omega));
	re_ray.unit_d_vec = rt_vec_to_unit(re_ray.unit_d_vec);
	re_ray.start = rt_vec_add(result.insec_p.p_vec,
			rt_vec_mult(re_ray.unit_d_vec, 1.0 / 512.0));
	return (re_ray);
}

t_rgb_vec	rt_calc_refraction(t_rt_data *rt, t_ray ray, int recusion_lev,
		t_insec_res result)
{
	const t_3d_vec	unit_v = rt_vec_to_unit(rt_vec_mult(ray.unit_d_vec, -1));
	double			n_dot_v;
	double			eta1;
	double			eta2;
	double			omega;

	eta1 = 0.80;
	eta2 = 1.0;
	n_dot_v = rt_vec_dot(unit_v, result.insec_p.unit_n_vec);
	if (n_dot_v < 0)
	{
		eta1 = 1.0;
		eta2 = 0.80;
		result.insec_p.unit_n_vec = rt_vec_mult(result.insec_p.unit_n_vec, -1);
		n_dot_v = rt_vec_dot(unit_v, result.insec_p.unit_n_vec);
	}
	omega = (eta2 / eta1) * (eta2 / eta1) * sqrt(((eta2 / eta1)
				* (eta2 / eta1)) - (1 - (rt_vec_dot(unit_v,
						result.insec_p.unit_n_vec))
				* (rt_vec_dot(unit_v, result.insec_p.unit_n_vec))))
		- (rt_vec_dot(unit_v, result.insec_p.unit_n_vec));
	return (rt_calc_r_m(rt, recusion_lev, rt_calc_re_ray2(ray, result,
				(eta2 / eta1), omega)));
}
