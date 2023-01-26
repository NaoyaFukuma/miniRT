/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_sp_intersec.c                          :+:      :+:    :+:   */
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

static double	rt_calc_abd(t_sphere *sp, t_ray ray, double *a, double *b)
{
	t_3d_vec	tmp;
	double		c;

	tmp = rt_vec_sub(ray.start, sp->center_p_vec);
	*a = pow(rt_vec_mag(ray.unit_d_vec), 2.0);
	*b = 2.0 * rt_vec_dot(tmp, ray.unit_d_vec);
	c = rt_vec_dot(tmp, tmp) - pow(sp->radius, 2.0);
	return (*b * *b - 4.0 * *a * c);
}

static double	rt_sp_calc_dir_vec(t_sphere *sp, t_ray ray)
{
	double	a;
	double	b;
	double	d;

	d = rt_calc_abd(sp, ray, &a, &b);
	if (d == 0.0)
		return (-b / (2.0 * a));
	if (d < 0.0)
		return (-1.0);
	if ((-b - sqrt(d)) / (2.0 * a) > 0.0 && (-b + sqrt(d)) / (2.0 * a) > 0.0)
		return (rt_min((-b - sqrt(d)) / (2.0 * a), (-b + sqrt(d)) / (2.0 * a)));
	else
		return (rt_max((-b - sqrt(d)) / (2.0 * a), (-b + sqrt(d)) / (2.0 * a)));
}

t_3d_vec	rt_bump_mapping(t_insec_p *res, double u, double v)
{
	extern t_rt_data	rt;
	const double	x
		= fmod(u, 1.0) * rt.mlx.n_unit_vec_xpm.width;
	const double	y
		= fmod(v, 1.0) * rt.mlx.n_unit_vec_xpm.height;
	const t_rgb_vec	c = rt_get_color_from_image(&rt.mlx.n_unit_vec_xpm, (int)x, (int)y);
	const t_3d_vec tangent = rt_vec_constructor((c.r * 2) - 1,(c.b * 2) - 1,  (c.g * 2) - 1);

	t_3d_vec	dx;
	t_3d_vec	dy;

	dx = rt_vec_to_unit(rt_vec_cross(res->unit_n_vec, rt_vec_constructor(0, 1, 0)));
	if (rt_vec_mag(dx) == 0)
		dx = rt_vec_constructor(1, 0, 0);
	dy = rt_vec_cross(res->unit_n_vec, dx);

	t_3d_vec res_x = rt_vec_mult(dx, tangent.x);
	t_3d_vec res_y = rt_vec_mult(dy, tangent.z);
	t_3d_vec res_z = rt_vec_mult(res->unit_n_vec, tangent.y);
	return (rt_vec_to_unit(rt_vec_add(rt_vec_add(res_x, res_y) , res_z)));
}

t_rgb_vec	rt_checker(t_insec_p *res, t_sphere *sphere)
{
	extern	t_rt_data	rt;
	const t_3d_vec	pw_pc = rt_vec_sub(res->p_vec, sphere->center_p_vec);
	const double phi = atan2(pw_pc.x, pw_pc.z);
	const double theta = acos(pw_pc.y / sphere->radius);
	double			u;
	double			v;

	u = (1 - (phi / (2 * M_PI) + 0.5));
	v = (theta / M_PI);

	u = fmod(u, 1.0) * rt.mlx.texture_xpm.width;
	v = fmod(v, 1.0) * rt.mlx.texture_xpm.height;
	res->unit_n_vec = rt_bump_mapping(res, u, v);
	return (rt_get_color_from_image(&rt.mlx.texture_xpm, (int)u, (int)v));

	// if ((int)(floor(u * 10) + floor(v * 10)) % 2 == 0)
	// 	return (rt_rgb_vec_constructor(1, 1, 1));
	// return (rt_rgb_vec_constructor(0.2, 0.2, 0.2));
}

t_insec_p	rt_sp_intersec(t_sphere *sphere, t_ray ray)
{
	t_insec_p	res;
	double		t;

	t = rt_sp_calc_dir_vec(sphere, ray);
	res.unit_n_vec.x = NOT_INTERSECT;
	if (t > 0.0)
	{
		res.dist = t * rt_vec_mag(ray.unit_d_vec);
		res.p_vec = rt_get_point(ray, t);
		res.unit_n_vec = rt_vec_to_unit(rt_vec_sub(res.p_vec,
					sphere->center_p_vec));
		sphere->color = rt_checker(&res, sphere);
		return (res);
	}
	return (res);
}
