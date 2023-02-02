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

static double	rt_calc_abd(t_cone *cone, t_ray ray, double *a, double *b)
{
	t_3d_vec	d;
	t_3d_vec	s_cy_c;
	double		rad_div_h;
	double		c;

	d = ray.unit_d_vec;
	s_cy_c = rt_vec_sub(ray.start, cone->center_p_vec);
	rad_div_h = cone->radius / cone->height;
	*a = rt_vec_dot(d, d) - pow(rt_vec_dot(d, cone->unit_orient_vec), 2.0)
		- pow(rad_div_h, 2.0) * pow(rt_vec_dot(d, cone->unit_orient_vec), 2.0);
	*b = 2.0 * (rt_vec_dot(d, s_cy_c) - (rt_vec_dot(d, cone->unit_orient_vec))
			* (rt_vec_dot(s_cy_c, cone->unit_orient_vec))) - 2.0
		* pow(rad_div_h, 2.0) * rt_vec_dot(d, cone->unit_orient_vec)
		* rt_vec_dot(s_cy_c, cone->unit_orient_vec);
	c = rt_vec_dot(s_cy_c, s_cy_c) - pow(rt_vec_dot(s_cy_c,
				cone->unit_orient_vec), 2.0) - pow(rad_div_h, 2.0)
		* pow(rt_vec_dot(s_cy_c, cone->unit_orient_vec), 2.0);
	return (*b * *b - 4.0 * *a * c);
}

static double	rt_co_calc_dir_vec_t(t_cone *cone, t_ray ray, double *flag)
{
	double	a;
	double	b;
	double	d;
	double	t;
	double	h_dis;

	d = rt_calc_abd(cone, ray, &a, &b);
	t = -1.0;
	if (d == 0.0)
		return (-b / (2.0 * a));
	if (d < 0.0)
		return (rt_max((-b - sqrt(d)) / (2.0 * a), (-b + sqrt(d)) / (2.0 * a)));
	if (!((-b - sqrt(d)) / (2.0 * a) > 0 && (-b + sqrt(d)) / (2.0 * a) > 0))
		return (rt_max((-b - sqrt(d)) / (2.0 * a), (-b + sqrt(d)) / (2.0 * a)));
	t = rt_min((-b - sqrt(d)) / (2.0 * a), (-b + sqrt(d)) / (2.0 * a));
	h_dis = rt_vec_dot(rt_vec_sub(rt_get_point(ray, t),
				cone->center_p_vec), cone->unit_orient_vec);
	if (!(-cone->height <= h_dis && h_dis <= 0))
	{
		t = rt_max((-b - sqrt(d)) / (2.0 * a), (-b + sqrt(d)) / (2.0 * a));
		*flag = 1.0;
	}
	return (t);
}

double	rt_calc_height(t_cone *cone, t_ray ray, double t)
{
	t_3d_vec	x;
	t_3d_vec	dt;
	t_3d_vec	x_plus_dt;
	double		m;
	double		k;

	x = rt_vec_sub(ray.start, cone->center_p_vec);
	dt = rt_vec_mult(ray.unit_d_vec, t);
	x_plus_dt = rt_vec_add(x, dt);
	m = rt_vec_dot(x_plus_dt, cone->unit_orient_vec);
	k = 1 + pow(cone->radius / cone->height, 2.0);
	return (k * m);
}

t_3d_vec	rt_calc_unit_n_vec(t_cone *cone, t_ray ray, double flag, double t)
{
	t_3d_vec	pa_minus_pc;
	t_3d_vec	h_mult_v;
	double		height;
	t_3d_vec	n_vec;

	pa_minus_pc = rt_vec_sub(rt_get_point(ray, t), cone->center_p_vec);
	height = rt_calc_height(cone, ray, t);
	h_mult_v = rt_vec_mult(cone->unit_orient_vec, height);
	n_vec = rt_vec_mult(rt_vec_sub(pa_minus_pc, h_mult_v), flag);
	return (rt_vec_to_unit(n_vec));
}

t_insec_p	rt_co_intersec(t_cone *cone, t_ray ray)
{
	double					t;
	double					flag;
	double					h_dis;
	t_insec_p				res;
	t_3d_vec				pa;

	flag = 1.0;
	t = rt_co_calc_dir_vec_t(cone, ray, &flag);
	res.unit_n_vec.x = NOT_INTERSECT;
	if (t <= 0)
		return (res);
	pa = rt_get_point(ray, t);
	h_dis = rt_vec_dot(rt_vec_sub(pa, cone->center_p_vec),
			cone->unit_orient_vec);
	if (-cone->height <= h_dis && h_dis <= 0)
	{
		if (rt_discrim_co_n_vev_negative(cone, ray) == true)
			flag = -1.0;
		res.dist = t * rt_vec_mag(ray.unit_d_vec);
		res.p_vec = pa;
		res.unit_n_vec = rt_calc_unit_n_vec(cone, ray, flag, t);
		return (res);
	}
	return (res);
}
