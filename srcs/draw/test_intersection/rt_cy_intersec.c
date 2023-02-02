/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_cy_intersec.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 18:49:47 by kyamagis          #+#    #+#             */
/*   Updated: 2023/01/23 16:05:51 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_vector.h"
#include "rt_structs.h"
#include "rt_draw.h"
#include "libft.h"
#include <stdbool.h>
#include <float.h>
#include <math.h>

static double	rt_calc_abd(t_cylinder *cy, t_ray ray, double *a, double *b)
{
	t_3d_vec	d;
	t_3d_vec	s_cy_c;
	double		c;

	d = ray.unit_d_vec;
	s_cy_c = rt_vec_sub(ray.start, cy->center_p_vec);
	*a = rt_vec_dot(d, d) - pow(rt_vec_dot(d, cy->unit_orient_vec), 2.0);
	*b = 2.0 * (rt_vec_dot(d, s_cy_c) - (rt_vec_dot(d, cy->unit_orient_vec))
			* (rt_vec_dot(s_cy_c, cy->unit_orient_vec)));
	c = rt_vec_dot(s_cy_c, s_cy_c) - pow(rt_vec_dot(s_cy_c,
				cy->unit_orient_vec), 2.0) - pow(cy->radius, 2.0);
	return (*b * *b - 4.0 * *a * c);
}

static double	rt_cy_calc_dir_vec_t(t_cylinder *cy, t_ray ray, double *flag)
{
	double	a;
	double	b;
	double	d;
	double	t;
	double	h_dis;

	d = rt_calc_abd(cy, ray, &a, &b);
	t = -1.0;
	if (d == 0.0)
		return (-b / (2.0 * a));
	if (d < 0.0)
		return (t);
	if (!((-b - sqrt(d)) / (2.0 * a) > 0 && (-b + sqrt(d)) / (2.0 * a) > 0))
		return (rt_max((-b - sqrt(d)) / (2.0 * a), (-b + sqrt(d)) / (2.0 * a)));
	t = rt_min((-b - sqrt(d)) / (2.0 * a), (-b + sqrt(d)) / (2.0 * a));
	h_dis = rt_vec_dot(rt_vec_sub(rt_get_point(ray, t),
				cy->center_p_vec), cy->unit_orient_vec);
	if (h_dis < (-1.0 * cy->height / 2.0f) || (cy->height / 2.0f) < h_dis)
	{
		t = rt_max((-b - sqrt(d)) / (2.0 * a), (-b + sqrt(d)) / (2.0 * a));
		*flag = -1.0;
	}
	return (t);
}

static t_3d_vec	rt_calc_normal(double flag, t_cylinder *cy, double t, t_ray ray)
{
	t_3d_vec	pa_minus_pc;
	t_3d_vec	h_mult_v;
	double		height;
	t_3d_vec	n_vec;

	pa_minus_pc = rt_vec_sub(rt_get_point(ray, t), cy->center_p_vec);
	height = rt_vec_dot(pa_minus_pc, cy->unit_orient_vec);
	h_mult_v = rt_vec_mult(cy->unit_orient_vec, height);
	n_vec = rt_vec_mult(rt_vec_sub(pa_minus_pc, h_mult_v), flag);
	return (rt_vec_to_unit(n_vec));
}

t_insec_p	rt_cy_intersec(t_cylinder *cy, t_ray ray)
{
	double					t;
	double					flag;
	double					h_dis;
	t_insec_p				res;
	t_3d_vec				pa;

	flag = 1.0;
	t = rt_cy_calc_dir_vec_t(cy, ray, &flag);
	res.unit_n_vec.x = NOT_INTERSECT;
	if (t <= 0)
		return (res);
	pa = rt_get_point(ray, t);
	h_dis = rt_vec_dot(rt_vec_sub(pa, cy->center_p_vec), cy->unit_orient_vec);
	if ((-1.0 * cy->height / 2.0f) <= h_dis && h_dis <= (cy->height / 2.0f))
	{
		if (rt_cam_to_orient_vec_len(ray.start, cy->center_p_vec, \
									cy->unit_orient_vec) < cy->radius)
			flag = -1.0;
		res.dist = t * rt_vec_mag(ray.unit_d_vec);
		res.p_vec = pa;
		res.unit_n_vec = rt_vec_to_unit(rt_calc_normal(flag, cy, t, ray));
		return (res);
	}
	return (res);
}
