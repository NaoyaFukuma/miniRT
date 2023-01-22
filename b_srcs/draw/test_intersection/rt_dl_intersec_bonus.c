/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_co_intersec.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 18:49:47 by kyamagis          #+#    #+#             */
/*   Updated: 2023/01/23 16:05:51 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "rt_draw_bonus.h"
#include "rt_structs_bonus.h"
#include "rt_vector_bonus.h"
#include <float.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>

t_3d_vec	rt_calc_delta_cross_vec(t_3d_vec pa, t_3d_vec top, t_3d_vec next)
{
	t_3d_vec	next_top;
	t_3d_vec	top_pa;
	t_3d_vec	cross;

	next_top = rt_vec_sub(next, top);
	top_pa = rt_vec_sub(top, pa);
	cross = rt_vec_cross(next_top, top_pa);
	return (cross);
}

bool	rt_in_or_out_judg(t_delta *delta, t_3d_vec pa)
{
	t_3d_vec	pa_a_b;
	t_3d_vec	pa_b_c;
	t_3d_vec	pa_c_a;

	pa_a_b = rt_calc_delta_cross_vec(pa, delta->a, delta->b);
	pa_b_c = rt_calc_delta_cross_vec(pa, delta->b, delta->c);
	pa_c_a = rt_calc_delta_cross_vec(pa, delta->c, delta->a);
	if (rt_vec_dot(pa_a_b, delta->unit_n_vec) <= 0.0)
	{
		return (false);
	}
	if (rt_vec_dot(pa_b_c, delta->unit_n_vec) <= 0.0)
	{
		return (false);
	}
	if (rt_vec_dot(pa_c_a, delta->unit_n_vec) <= 0.0)
	{
		return (false);
	}
	return (true);
}

t_insec_p	rt_dl_intersec(t_delta *delta, t_ray ray)
{
	double		t;
	double		d_dot_n;
	t_insec_p	res;
	t_3d_vec	pa;

	d_dot_n = rt_vec_dot(ray.unit_d_vec, delta->unit_n_vec);
	res.unit_n_vec.x = NOT_INTERSECT;
	if (d_dot_n == 0.0)
		return (res);
	t = (rt_vec_dot(delta->g, delta->unit_n_vec)
			- rt_vec_dot(ray.start, delta->unit_n_vec)) / d_dot_n;
	res.unit_n_vec.x = NOT_INTERSECT;
	if (t <= 0.0)
		return (res);
	pa = rt_get_point(ray, t);
	if (rt_in_or_out_judg(delta, pa) == true)
	{
		res.dist = t * rt_vec_mag(ray.unit_d_vec);
		res.p_vec = pa;
		res.unit_n_vec = delta->unit_n_vec;
		return (res);
	}
	return (res);
}
