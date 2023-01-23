/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_co_test_intersection.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 18:49:47 by kyamagis          #+#    #+#             */
/*   Updated: 2023/01/23 12:08:30 by nfukuma          ###   ########.fr       */
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
	t_3d_vec s_cy_c = rt_vector_sub(ray.start, cone->center_position);

	double radius_divided_by_height = cone->radius / cone->height;

	double A = rt_vector_dot(d, d) - pow(rt_vector_dot(d, cone->unit_orientation_vec), 2.0) - \
				pow(radius_divided_by_height, 2.0) * pow(rt_vector_dot(d, cone->unit_orientation_vec), 2.0) ;
	double B = 2.0 * (rt_vector_dot(d, s_cy_c) - (rt_vector_dot(d, cone->unit_orientation_vec)) * (rt_vector_dot(s_cy_c, cone->unit_orientation_vec))) - \
				2.0 * pow(radius_divided_by_height, 2.0) * rt_vector_dot(d, cone->unit_orientation_vec) * rt_vector_dot(s_cy_c, cone->unit_orientation_vec);
	double C = rt_vector_dot(s_cy_c, s_cy_c) - pow(rt_vector_dot(s_cy_c, cone->unit_orientation_vec), 2.0) - \
				pow(radius_divided_by_height, 2.0) * pow(rt_vector_dot(s_cy_c, cone->unit_orientation_vec), 2.0);
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

			double hDis = rt_vector_dot(rt_vector_sub(pa, cone->center_position), cone->unit_orientation_vec);
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

	double hDis = rt_vector_dot(rt_vector_sub(pa, cone->center_position), cone->unit_orientation_vec);
	if (- cone->height <= hDis && hDis <= 0)
	{
		res.distance = t * rt_vector_magnitude(ray.direction);
		res.position = pa;

		t_3d_vec	tmp_normal;

		tmp_normal.x = 2 * flag * (cone->unit_orientation_vec.z * (cone->unit_orientation_vec.z * (pa.x - cone->center_position.x) - cone->unit_orientation_vec.x * (pa.z - cone->center_position.z)) - \
									cone->unit_orientation_vec.y * (cone->unit_orientation_vec.x * (pa.y - cone->center_position.y) - cone->unit_orientation_vec.y * (pa.x - cone->center_position.x)));//法線方向の計算

		tmp_normal.y = 2 * flag * (cone->unit_orientation_vec.x * (cone->unit_orientation_vec.x * (pa.y - cone->center_position.y) - cone->unit_orientation_vec.y * (pa.x - cone->center_position.x)) - \
									cone->unit_orientation_vec.z * (cone->unit_orientation_vec.y * (pa.z - cone->center_position.z) - cone->unit_orientation_vec.z * (pa.y - cone->center_position.y)));//法線方向の計算

		tmp_normal.z = 2 * flag * (cone->unit_orientation_vec.y * (cone->unit_orientation_vec.y * (pa.z - cone->center_position.z) - cone->unit_orientation_vec.z * (pa.y - cone->center_position.y)) - \
									cone->unit_orientation_vec.x * (cone->unit_orientation_vec.z * (pa.x - cone->center_position.x) - cone->unit_orientation_vec.x * (pa.z - cone->center_position.z)));//法線方向の計算



		res.normal = rt_vector_normalize(tmp_normal);

		return (res);
	}
	return (res);
}

/*
#include <stdio.h>
tmp_normal.x = flag * 2 * cone->unit_orientation_vec.x * (cone->unit_orientation_vec.x * (pa.x - cone->center_position.x) * \
																cone->unit_orientation_vec.y * (pa.y - cone->center_position.y) * \
																cone->unit_orientation_vec.z * (pa.z - cone->center_position.z));

		tmp_normal.y = flag * 2 * cone->unit_orientation_vec.y * (cone->unit_orientation_vec.x * (pa.x - cone->center_position.x) * \
																cone->unit_orientation_vec.y * (pa.y - cone->center_position.y) * \
																cone->unit_orientation_vec.z * (pa.z - cone->center_position.z));

		tmp_normal.z = flag * 2 * cone->unit_orientation_vec.z * (cone->unit_orientation_vec.x * (pa.x - cone->center_position.x) * \
																cone->unit_orientation_vec.y * (pa.y - cone->center_position.y) * \
																cone->unit_orientation_vec.z * (pa.z - cone->center_position.z));
		tmp_normal.x = flag * cone->unit_orientation_vec.x * pa.x;//法線方向の計算
		tmp_normal.y = flag * cone->unit_orientation_vec.y * pa.y;//法線方向の計算
		tmp_normal.z = flag * cone->unit_orientation_vec.z * pa.z;//法線方向の計算
			printf("cone x %f %f %f %f\n", res.normal.x, tmp_normal.x, pa.x, cone->unit_orientation_vec.x);
		printf("cone y %f %f %f %f\n", res.normal.y, tmp_normal.y, pa.y, cone->unit_orientation_vec.y);
		printf("cone z %f %f %f %f\n\n", res.normal.z, tmp_normal.z ,pa.z, cone->unit_orientation_vec.z);
		//printf("cone %f %f %f\n", pa.x, cone->unit_orientation_vec.y ,cone->unit_orientation_vec.z);
*/
