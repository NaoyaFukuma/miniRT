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
#include "rt_draw.h"
#include "rt_structs.h"
#include "rt_vector.h"
#include <float.h>
#include <math.h>
#include <stdbool.h>

double	rt_calc_abd(t_cone *cone, t_ray ray, double *a, double *b)
{
	t_3d_vec	d;
	t_3d_vec	s_cy_c;
	double		rad_div_h;
	double		c;

	d = rt_vec_copy(ray.unit_d_vec);
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

double	rt_co_calc_dir_vec_t(t_cone *cone, t_ray ray, double *flag)
{
	double	a;
	double	b;
	double	d;
	double	t;
	double	h_dis;

	d = rt_calc_abd(cone, ray, &a, &b);
	t = -1.0;
	if (d == 0.0)
		t = -b / (2.0 * a);
	else if (d > 0.0)
	{
		if ((-b - sqrt(d)) / (2.0 * a) > 0 && (-b + sqrt(d)) / (2.0 * a) > 0)
		{
			t = rt_min((-b - sqrt(d)) / (2.0 * a), (-b + sqrt(d)) / (2.0 * a));
			h_dis = rt_vec_dot(rt_vec_sub(rt_get_point(ray, t),
					cone->center_p_vec), cone->unit_orient_vec);
			if (!(-cone->height <= h_dis && h_dis <= 0))
			{
				t = rt_max((-b - sqrt(d)) / (2.0 * a), (-b + sqrt(d))
						/ (2.0 * a));
				*flag = -1.0;
			}
		}
	}
	else
		t = rt_max((-b - sqrt(d)) / (2.0 * a), (-b + sqrt(d)) / (2.0 * a));
	return (t);
}

t_3d_vec	rt_calc_normal(double flag, t_cone *cone, t_3d_vec pa)
{
	t_3d_vec	tmp_normal;

	tmp_normal.x = 2 * flag * (cone->unit_orient_vec.z
			* (cone->unit_orient_vec.z * (pa.x - cone->center_p_vec.x)
				- cone->unit_orient_vec.x * (pa.z - cone->center_p_vec.z))
			- cone->unit_orient_vec.y * (cone->unit_orient_vec.x * (pa.y
					- cone->center_p_vec.y) - cone->unit_orient_vec.y * (pa.x
					- cone->center_p_vec.x)));
	tmp_normal.y = 2 * flag * (cone->unit_orient_vec.x
			* (cone->unit_orient_vec.x * (pa.y - cone->center_p_vec.y)
				- cone->unit_orient_vec.y * (pa.x - cone->center_p_vec.x))
			- cone->unit_orient_vec.z * (cone->unit_orient_vec.y * (pa.z
					- cone->center_p_vec.z) - cone->unit_orient_vec.z * (pa.y
					- cone->center_p_vec.y)));
	tmp_normal.z = 2 * flag * (cone->unit_orient_vec.y
			* (cone->unit_orient_vec.y * (pa.z - cone->center_p_vec.z)
				- cone->unit_orient_vec.z * (pa.y - cone->center_p_vec.y))
			- cone->unit_orient_vec.x * (cone->unit_orient_vec.z * (pa.x
					- cone->center_p_vec.x) - cone->unit_orient_vec.x * (pa.z
					- cone->center_p_vec.z)));
	return (tmp_normal);
}

t_insec_p	rt_co_intersec(t_cone *cone, t_ray ray)
{
	double					t;
	double					flag;
	double					h_dis;
	t_insec_p	res;
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
		res.dist = t * rt_vec_mag(ray.unit_d_vec);
		res.p_vec = pa;
		res.unit_n_vec = rt_vec_to_unit(rt_calc_normal(flag, cone, pa));
		return (res);
	}
	return (res);
}
