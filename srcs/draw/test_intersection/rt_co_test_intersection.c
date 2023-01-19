/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_co_test_intersection.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyamagis <kyamagis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 18:49:47 by kyamagis          #+#    #+#             */
/*   Updated: 2023/01/19 12:23:56 by kyamagis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_vector.h"
#include "rt_strucs.h"
#include "rt_draw.h"
#include "libft.h"
#include <stdbool.h>
#include <float.h>
#include <math.h>

double	rt_co_calculate_directional_vector_coefficients(t_cone *cone, t_ray ray, double *flag)
{
	t_3d_vec d = rt_vector_copy(ray.direction);
	t_3d_vec s_cy_c = rt_vector_sub(ray.start, cone->center_position);
	
	double radius_squared = pow(cone->radius, 2.0);
	double radius_divided_by_height = cone->radius / cone->height;

	double A = rt_vector_dot(d, d) - pow(rt_vector_dot(d, cone->unit_orientation_vec), 2.0) - \
				radius_squared * pow(radius_divided_by_height, 2.0) * rt_vector_dot(d, cone->unit_orientation_vec);
	double B = 2.0 * (rt_vector_dot(d, s_cy_c) - (rt_vector_dot(d, cone->unit_orientation_vec)) * (rt_vector_dot(s_cy_c, cone->unit_orientation_vec))) - \
				2.0 * radius_divided_by_height * rt_vector_dot(d, cone->unit_orientation_vec) * (radius_divided_by_height * rt_vector_dot(s_cy_c, cone->unit_orientation_vec) - 1);
	double C = rt_vector_dot(s_cy_c, s_cy_c) - pow(rt_vector_dot(s_cy_c, cone->unit_orientation_vec), 2.0) - pow(cone->radius, 2.0) - \
				radius_squared * pow(radius_divided_by_height * rt_vector_dot(s_cy_c, cone->unit_orientation_vec) - 1, 2.0);
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
			if (!(0 <= hDis && hDis <= cone->height))
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
	if (!(0 <= hDis && hDis <= cone->height))
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

// double	rt_co_calculate_directional_vector_coefficients(t_cone *cone, t_ray ray, double *flag)
// {
// 	t_3d_vec d = ray.direction;
// 	t_3d_vec m = rt_vector_sub(rt_vector_sub(ray.start, cone->center_position), rt_vector_constructor(0, cone->height, 0));

// 	double A = pow(d.x, 2.0) - pow(d.y * cone->radius / cone->height, 2.0) + pow(d.z, 2.0);
// 	double B = 2.0 * (d.x * m.x - pow(cone->radius / cone->height, 2.0) * d.y * m.y + d.z * m.z);
// 	double C = pow(m.x, 2.0) - pow(m.y * cone->radius / cone->height, 2.0) + pow(d.z, 2.0);
// 	double D = B * B - 4 * A * C;
// 	double t = -1;

// 	if (D == 0)
// 	{
// 		t = -B / (2 * A);
// 	}
// 	else if (D > 0)
// 	{
// 		double t1 = ( -B - sqrt(D)) / (2.0 * A);
// 		double t2 = ( -B + sqrt(D)) / (2.0 * A);

// 		if (t1 > 0 && t2 > 0)
// 		{
// 			t = rt_min(t1, t2);
// 			t_3d_vec pa = rt_get_point(ray, t);

// 			double hDis = rt_vector_sub(pa, cone->center_position).y;
// 			if (!(0 <= hDis && hDis <= cone->height))
// 			{
// 				t = rt_max(t1, t2);
// 				*flag = -1.0;
// 			}
// 		}
// 		else
// 		{
// 			t = rt_max(t1, t2);
// 		}

// 	}
// 	return (t);
// }

// t_intersection_point	rt_co_test_intersection(t_cone *cone, t_ray ray)
// {
// 	double 					t;
// 	double					flag;
// 	t_intersection_point	res;

// 	flag = 1.0;
// 	t = rt_co_calculate_directional_vector_coefficients(cone, ray, &flag);
// 	res.normal.x = NOT_INTERSECT;
// 	if (t <= 0)
// 	{
// 		return (res);
// 	}

// 	t_3d_vec pa = rt_get_point(ray, t);
// 	double hDis = rt_vector_sub(pa, cone->center_position).y;
// 	if (0 <= hDis && hDis <= cone->height)
// 	{
// 		res.distance = t * rt_vector_magnitude(ray.direction);
// 		res.position = pa;

// 		res.normal.x = 2 * flag * (pa.x - cone->center_position.x);
// 		res.normal.y = -2 * flag * ((cone->radius / cone->height) * (cone->radius / cone->height)) * (pa.y - cone->center_position.y - cone->height);
// 		res.normal.z = 2 * flag * (pa.z - cone->center_position.z);
// 		res.normal = rt_vector_normalize(res.normal);
// 		return (res);
// 	}
// 	return (res);
// }