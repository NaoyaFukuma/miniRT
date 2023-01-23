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


double	rt_cy_calculate_directional_vector_coefficients(t_cylinder *cylinder, t_ray ray, double *flag)
{
	t_3d_vec d = rt_vec_copy(ray.unit_d_vec);
	t_3d_vec s_cy_c = rt_vec_sub(ray.start, cylinder->center_p_vec);

	double A = rt_vec_dot(d, d) - pow(rt_vec_dot(d, cylinder->unit_orient_vec), 2.0);
	double B = 2.0 * (rt_vec_dot(d, s_cy_c) - (rt_vec_dot(d, cylinder->unit_orient_vec)) * (rt_vec_dot(s_cy_c, cylinder->unit_orient_vec)));
	double C = rt_vec_dot(s_cy_c, s_cy_c) - pow(rt_vec_dot(s_cy_c, cylinder->unit_orient_vec), 2.0) - pow(cylinder->radius, 2.0);
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

			double hDis = rt_vec_dot(rt_vec_sub(pa, cylinder->center_p_vec), cylinder->unit_orient_vec);
			if (hDis < (- 1.0 * cylinder->height / 2.0f) || (cylinder->height / 2.0f) < hDis)
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

t_insec_p	rt_cy_intersec(t_cylinder *cylinder, t_ray ray)
{
	double					t;
	double 					flag;
	t_insec_p	res;

	flag = 1.0;
	t = rt_cy_calculate_directional_vector_coefficients(cylinder, ray, &flag);
	res.unit_n_vec.x = NOT_INTERSECT;
	if (t <= 0)
	{
		return (res);
	}

	t_3d_vec pa = rt_get_point(ray, t);

	double hDis = rt_vec_dot(rt_vec_sub(pa, cylinder->center_p_vec), cylinder->unit_orient_vec);
	if ((- 1.0 * cylinder->height / 2.0f) <= hDis && hDis <= (cylinder->height / 2.0f))
	{
		res.dist = t * rt_vec_mag(ray.unit_d_vec);
		res.p_vec = pa;
		t_3d_vec	tmp_normal;
		tmp_normal.x = 2 * flag * (cylinder->unit_orient_vec.z * (cylinder->unit_orient_vec.z * (pa.x - cylinder->center_p_vec.x) - cylinder->unit_orient_vec.x * (pa.z - cylinder->center_p_vec.z)) - \
									cylinder->unit_orient_vec.y * (cylinder->unit_orient_vec.x * (pa.y - cylinder->center_p_vec.y) - cylinder->unit_orient_vec.y * (pa.x - cylinder->center_p_vec.x)));//法線方向の計算

		tmp_normal.y = 2 * flag * (cylinder->unit_orient_vec.x * (cylinder->unit_orient_vec.x * (pa.y - cylinder->center_p_vec.y) - cylinder->unit_orient_vec.y * (pa.x - cylinder->center_p_vec.x)) - \
									cylinder->unit_orient_vec.z * (cylinder->unit_orient_vec.y * (pa.z - cylinder->center_p_vec.z) - cylinder->unit_orient_vec.z * (pa.y - cylinder->center_p_vec.y)));//法線方向の計算

		tmp_normal.z = 2 * flag * (cylinder->unit_orient_vec.y * (cylinder->unit_orient_vec.y * (pa.z - cylinder->center_p_vec.z) - cylinder->unit_orient_vec.z * (pa.y - cylinder->center_p_vec.y)) - \
									cylinder->unit_orient_vec.x * (cylinder->unit_orient_vec.z * (pa.x - cylinder->center_p_vec.x) - cylinder->unit_orient_vec.x * (pa.z - cylinder->center_p_vec.z)));//法線方向の計算
		res.unit_n_vec = rt_vec_to_unit(tmp_normal);
		return (res);
	}
	return (res);
}
