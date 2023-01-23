/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_co_test_intersection.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 18:49:47 by kyamagis          #+#    #+#             */
/*   Updated: 2023/01/23 13:10:25 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_vector.h"
#include "rt_structs.h"
#include "rt_draw.h"
#include "libft.h"
#include <stdbool.h>
#include <float.h>
#include <math.h>


double	rt_co_calculate_directional_vector_coefficients(t_cone *cone, t_ray ray, double *flag)
{
	t_3d_vec d = rt_vector_copy(ray.direction);
	t_3d_vec s_cy_c = rt_vector_sub(ray.start, cone->center_p_vec);

	double radius_divided_by_height = cone->radius / cone->height;

	double A = rt_vector_dot(d, d) - pow(rt_vector_dot(d, cone->unit_orient_vec), 2.0) - \
				pow(radius_divided_by_height, 2.0) * pow(rt_vector_dot(d, cone->unit_orient_vec), 2.0) ;
	double B = 2.0 * (rt_vector_dot(d, s_cy_c) - (rt_vector_dot(d, cone->unit_orient_vec)) * (rt_vector_dot(s_cy_c, cone->unit_orient_vec))) - \
				2.0 * pow(radius_divided_by_height, 2.0) * rt_vector_dot(d, cone->unit_orient_vec) * rt_vector_dot(s_cy_c, cone->unit_orient_vec);
	double C = rt_vector_dot(s_cy_c, s_cy_c) - pow(rt_vector_dot(s_cy_c, cone->unit_orient_vec), 2.0) - \
				pow(radius_divided_by_height, 2.0) * pow(rt_vector_dot(s_cy_c, cone->unit_orient_vec), 2.0);
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

			double hDis = rt_vector_dot(rt_vector_sub(pa, cone->center_p_vec), cone->unit_orient_vec);
			if (!(- cone->height <= hDis && hDis <= 0))
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


t_intersection_point	rt_co_test_intersection(t_cone *cone, t_ray ray)
{
	double					t;
	double 					flag;
	t_intersection_point	res;

	flag = 1.0;
	t = rt_co_calculate_directional_vector_coefficients(cone, ray, &flag);
	res.normal.x = NOT_INTERSECT;
	if (t <= 0)
	{
		return (res);
	}

	t_3d_vec pa = rt_get_point(ray, t);

	double hDis = rt_vector_dot(rt_vector_sub(pa, cone->center_p_vec), cone->unit_orient_vec);
	if (- cone->height <= hDis && hDis <= 0)
	{
		res.distance = t * rt_vector_magnitude(ray.direction);
		res.p_vec = pa;

		t_3d_vec	tmp_normal;

		tmp_normal.x = 2 * flag * (cone->unit_orient_vec.z * (cone->unit_orient_vec.z * (pa.x - cone->center_p_vec.x) - cone->unit_orient_vec.x * (pa.z - cone->center_p_vec.z)) - \
									cone->unit_orient_vec.y * (cone->unit_orient_vec.x * (pa.y - cone->center_p_vec.y) - cone->unit_orient_vec.y * (pa.x - cone->center_p_vec.x)));//法線方向の計算

		tmp_normal.y = 2 * flag * (cone->unit_orient_vec.x * (cone->unit_orient_vec.x * (pa.y - cone->center_p_vec.y) - cone->unit_orient_vec.y * (pa.x - cone->center_p_vec.x)) - \
									cone->unit_orient_vec.z * (cone->unit_orient_vec.y * (pa.z - cone->center_p_vec.z) - cone->unit_orient_vec.z * (pa.y - cone->center_p_vec.y)));//法線方向の計算

		tmp_normal.z = 2 * flag * (cone->unit_orient_vec.y * (cone->unit_orient_vec.y * (pa.z - cone->center_p_vec.z) - cone->unit_orient_vec.z * (pa.y - cone->center_p_vec.y)) - \
									cone->unit_orient_vec.x * (cone->unit_orient_vec.z * (pa.x - cone->center_p_vec.x) - cone->unit_orient_vec.x * (pa.z - cone->center_p_vec.z)));//法線方向の計算



		res.normal = rt_vector_normalize(tmp_normal);

		return (res);
	}
	return (res);
}

/*
#include <stdio.h>
tmp_normal.x = flag * 2 * cone->unit_orient_vec.x * (cone->unit_orient_vec.x * (pa.x - cone->center_p_vec.x) * \
																cone->unit_orient_vec.y * (pa.y - cone->center_p_vec.y) * \
																cone->unit_orient_vec.z * (pa.z - cone->center_p_vec.z));

		tmp_normal.y = flag * 2 * cone->unit_orient_vec.y * (cone->unit_orient_vec.x * (pa.x - cone->center_p_vec.x) * \
																cone->unit_orient_vec.y * (pa.y - cone->center_p_vec.y) * \
																cone->unit_orient_vec.z * (pa.z - cone->center_p_vec.z));

		tmp_normal.z = flag * 2 * cone->unit_orient_vec.z * (cone->unit_orient_vec.x * (pa.x - cone->center_p_vec.x) * \
																cone->unit_orient_vec.y * (pa.y - cone->center_p_vec.y) * \
																cone->unit_orient_vec.z * (pa.z - cone->center_p_vec.z));
		tmp_normal.x = flag * cone->unit_orient_vec.x * pa.x;//法線方向の計算
		tmp_normal.y = flag * cone->unit_orient_vec.y * pa.y;//法線方向の計算
		tmp_normal.z = flag * cone->unit_orient_vec.z * pa.z;//法線方向の計算
			printf("cone x %f %f %f %f\n", res.normal.x, tmp_normal.x, pa.x, cone->unit_orient_vec.x);
		printf("cone y %f %f %f %f\n", res.normal.y, tmp_normal.y, pa.y, cone->unit_orient_vec.y);
		printf("cone z %f %f %f %f\n\n", res.normal.z, tmp_normal.z ,pa.z, cone->unit_orient_vec.z);
		//printf("cone %f %f %f\n", pa.x, cone->unit_orient_vec.y ,cone->unit_orient_vec.z);
*/
