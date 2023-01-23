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

// static double	rt_calc_abd(t_cone *cone, t_ray ray, double *a, double *b)
// {
// 	t_3d_vec	d;
// 	t_3d_vec	s_cy_c;
// 	double		rad_div_h;
// 	double		c;
//
// 	d = rt_vec_copy(ray.unit_d_vec);
// 	s_cy_c = rt_vec_sub(ray.start, cone->center_p_vec);
// 	rad_div_h = cone->radius / cone->height;
// 	*a = rt_vec_dot(d, d) - pow(rt_vec_dot(d, cone->unit_orient_vec), 2.0)
// 		- pow(rad_div_h, 2.0) * pow(rt_vec_dot(d, cone->unit_orient_vec), 2.0);
// 	*b = 2.0 * (rt_vec_dot(d, s_cy_c) - (rt_vec_dot(d, cone->unit_orient_vec))
// 			* (rt_vec_dot(s_cy_c, cone->unit_orient_vec))) - 2.0
// 		* pow(rad_div_h, 2.0) * rt_vec_dot(d, cone->unit_orient_vec)
// 		* rt_vec_dot(s_cy_c, cone->unit_orient_vec);
// 	c = rt_vec_dot(s_cy_c, s_cy_c) - pow(rt_vec_dot(s_cy_c,
// 				cone->unit_orient_vec), 2.0) - pow(rad_div_h, 2.0)
// 		* pow(rt_vec_dot(s_cy_c, cone->unit_orient_vec), 2.0);
// 	return (*b * *b - 4.0 * *a * c);
// }

double	rt_cy_calc_dir_vec_t(t_cylinder *cy, t_ray ray, double *flag)
{
	t_3d_vec d = rt_vec_copy(ray.unit_d_vec);
	t_3d_vec s_cy_c = rt_vec_sub(ray.start, cy->center_p_vec);

	double A = rt_vec_dot(d, d) - pow(rt_vec_dot(d, cy->unit_orient_vec), 2.0);
	double B = 2.0 * (rt_vec_dot(d, s_cy_c) - (rt_vec_dot(d, cy->unit_orient_vec)) * (rt_vec_dot(s_cy_c, cy->unit_orient_vec)));
	double C = rt_vec_dot(s_cy_c, s_cy_c) - pow(rt_vec_dot(s_cy_c, cy->unit_orient_vec), 2.0) - pow(cy->radius, 2.0);
	double D = B * B - 4.0 * A * C;
	double t = -1.0;

	if (D == 0.0)
	{
		t = -B / (2.0 * A);
	}
	else if (D > 0.0)
	{
		double t1 = ( -B - sqrt(D)) / (2.0 * A);
		double t2 = ( -B + sqrt(D)) / (2.0 * A);

		if (t1 > 0 && t2 > 0)
		{
			t = rt_min(t1, t2);
			t_3d_vec pa = rt_get_point(ray, t);

			double h_dis = rt_vec_dot(rt_vec_sub(pa, cy->center_p_vec), cy->unit_orient_vec);
			if (h_dis < (- 1.0 * cy->height / 2.0f) || (cy->height / 2.0f) < h_dis)
			{
				t = rt_max(t1, t2);
				*flag = -1.0;
			}
		}
		else
		{
			t = rt_max(t1, t2);
		}
	}
	return (t);
}

static t_3d_vec	rt_calc_normal(double flag, t_cylinder *cy, t_3d_vec pa)
{
	t_3d_vec	tmp_normal;

	tmp_normal.x = 2 * flag * (cy->unit_orient_vec.z
			* (cy->unit_orient_vec.z * (pa.x - cy->center_p_vec.x)
				- cy->unit_orient_vec.x * (pa.z - cy->center_p_vec.z))
			- cy->unit_orient_vec.y * (cy->unit_orient_vec.x * (pa.y
					- cy->center_p_vec.y) - cy->unit_orient_vec.y * (pa.x
					- cy->center_p_vec.x)));
	tmp_normal.y = 2 * flag * (cy->unit_orient_vec.x
			* (cy->unit_orient_vec.x * (pa.y - cy->center_p_vec.y)
				- cy->unit_orient_vec.y * (pa.x - cy->center_p_vec.x))
			- cy->unit_orient_vec.z * (cy->unit_orient_vec.y * (pa.z
					- cy->center_p_vec.z) - cy->unit_orient_vec.z * (pa.y
					- cy->center_p_vec.y)));
	tmp_normal.z = 2 * flag * (cy->unit_orient_vec.y
			* (cy->unit_orient_vec.y * (pa.z - cy->center_p_vec.z)
				- cy->unit_orient_vec.z * (pa.y - cy->center_p_vec.y))
			- cy->unit_orient_vec.x * (cy->unit_orient_vec.z * (pa.x
					- cy->center_p_vec.x) - cy->unit_orient_vec.x * (pa.z
					- cy->center_p_vec.z)));
	return (tmp_normal);
}

t_insec_p	rt_cy_intersec(t_cylinder *cy, t_ray ray)
{
	double					t;
	double 					flag;
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
	if ((- 1.0 * cy->height / 2.0f) <= h_dis && h_dis <= (cy->height / 2.0f))
	{
		res.dist = t * rt_vec_mag(ray.unit_d_vec);
		res.p_vec = pa;
		res.unit_n_vec = rt_vec_to_unit(rt_calc_normal(flag, cy, pa));
		return (res);
	}
	return (res);
}
