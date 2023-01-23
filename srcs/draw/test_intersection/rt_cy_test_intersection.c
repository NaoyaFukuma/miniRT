/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_cy_test_intersection.c                          :+:      :+:    :+:   */
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


double	rt_cy_calculate_directional_vector_coefficients(t_cylinder *cylinder, t_ray ray, double *flag)
{
	t_3d_vec d = rt_vector_copy(ray.direction);
	t_3d_vec s_cy_c = rt_vector_sub(ray.start, cylinder->center_p_vec);

	double A = rt_vector_dot(d, d) - pow(rt_vector_dot(d, cylinder->unit_orient_vec), 2.0);
	double B = 2.0 * (rt_vector_dot(d, s_cy_c) - (rt_vector_dot(d, cylinder->unit_orient_vec)) * (rt_vector_dot(s_cy_c, cylinder->unit_orient_vec)));
	double C = rt_vector_dot(s_cy_c, s_cy_c) - pow(rt_vector_dot(s_cy_c, cylinder->unit_orient_vec), 2.0) - pow(cylinder->radius, 2.0);
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

			double hDis = rt_vector_dot(rt_vector_sub(pa, cylinder->center_p_vec), cylinder->unit_orient_vec);
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





t_intersection_point	rt_cy_test_intersection(t_cylinder *cylinder, t_ray ray)
{
	double					t;
	double 					flag;
	t_intersection_point	res;

	flag = 1.0;
	t = rt_cy_calculate_directional_vector_coefficients(cylinder, ray, &flag);
	res.normal.x = NOT_INTERSECT;
	if (t <= 0)
	{
		return (res);
	}

	t_3d_vec pa = rt_get_point(ray, t);

	double hDis = rt_vector_dot(rt_vector_sub(pa, cylinder->center_p_vec), cylinder->unit_orient_vec);
	if ((- 1.0 * cylinder->height / 2.0f) <= hDis && hDis <= (cylinder->height / 2.0f))
	{
		res.distance = t * rt_vector_magnitude(ray.direction);
		res.p_vec = pa;
		t_3d_vec	tmp_normal;
		tmp_normal.x = 2 * flag * (cylinder->unit_orient_vec.z * (cylinder->unit_orient_vec.z * (pa.x - cylinder->center_p_vec.x) - cylinder->unit_orient_vec.x * (pa.z - cylinder->center_p_vec.z)) - \
									cylinder->unit_orient_vec.y * (cylinder->unit_orient_vec.x * (pa.y - cylinder->center_p_vec.y) - cylinder->unit_orient_vec.y * (pa.x - cylinder->center_p_vec.x)));//法線方向の計算

		tmp_normal.y = 2 * flag * (cylinder->unit_orient_vec.x * (cylinder->unit_orient_vec.x * (pa.y - cylinder->center_p_vec.y) - cylinder->unit_orient_vec.y * (pa.x - cylinder->center_p_vec.x)) - \
									cylinder->unit_orient_vec.z * (cylinder->unit_orient_vec.y * (pa.z - cylinder->center_p_vec.z) - cylinder->unit_orient_vec.z * (pa.y - cylinder->center_p_vec.y)));//法線方向の計算

		tmp_normal.z = 2 * flag * (cylinder->unit_orient_vec.y * (cylinder->unit_orient_vec.y * (pa.z - cylinder->center_p_vec.z) - cylinder->unit_orient_vec.z * (pa.y - cylinder->center_p_vec.y)) - \
									cylinder->unit_orient_vec.x * (cylinder->unit_orient_vec.z * (pa.x - cylinder->center_p_vec.x) - cylinder->unit_orient_vec.x * (pa.z - cylinder->center_p_vec.z)));//法線方向の計算
		res.normal = rt_vector_normalize(tmp_normal);
		return (res);
	}
	return (res);
}


// 交点の位置ベクトルをP、シリンダーの中心の位置ベクトルをC、視点の位置ベクトルS、視線方向の単位方向ベクトルをD
// P = S + tD;
// P - C = S + tD - C; 交点から中心に向かうベクトル

// シリンダーのオリエンタルベクトルV、Vと同じ方向にあるベクトルA
// A = C + mV; mは実数( -h/2 <=  m <= h/2)

// (P - A)dot V = 0; Vと直行する(P - A)を算出
// mag(P - C) = r ; Vと直行する(P - A)の大きさ
// (P - C -mV) dot V = 0; Aを展開
// ここでVの大きさが1なので
// (P - C -m) dot V = 0;
// (P - C) dot V - m dot V = 0;
// m = (P - C) dot V;
//   = (S + tD - C) dot V;



// double	rt_cy_calculate_directional_vector_coefficients(t_cylinder *cylinder, t_ray ray, double *flag)
// {
// 	t_3d_vec dM = rt_vector_copy(ray.direction);
// 	t_3d_vec mM = rt_vector_sub(ray.start, cylinder->center_p_vec);

// 	dM.y = 0.0;
// 	mM.y = 0.0;

// 	double A = pow(rt_vector_magnitude(dM), 2.0);
// 	double B = 2.0 * rt_vector_dot(dM, mM);
// 	double C = rt_vector_dot(mM, mM) - pow(cylinder->radius, 2.0);
// 	double D = B * B - 4.0 * A * C;
// 	double t = -1.0;

// 	if (D == 0.0)
// 	{
// 		t = -B / (2.0 * A);
// 	}
// 	else if (D > 0.0)
// 	{
// 		double t1 = ( -B - sqrt(D)) / (2.0 * A);
// 		double t2 = ( -B + sqrt(D)) / (2.0 * A);

// 		if (t1 > 0 && t2 > 0)
// 		{
// 			t = rt_min(t1, t2);
// 			t_3d_vec pa = rt_get_point(ray, t);

// 			double hDis = rt_vector_sub(pa, cylinder->center_p_vec).y;
// 			if (hDis < (- 1.0 * cylinder->height / 2.0f) || (cylinder->height / 2.0f) < hDis)
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

// t_intersection_point	rt_cy_test_intersection(t_cylinder *cylinder, t_ray ray)
// {
// 	double					t;
// 	double 					flag;
// 	t_intersection_point	res;

// 	flag = 1.0;
// 	t = rt_cy_calculate_directional_vector_coefficients(cylinder, ray, &flag);
// 	res.normal.x = NOT_INTERSECT;
// 	if (t <= 0)
// 	{
// 		return (res);
// 	}

// 	t_3d_vec pa = rt_get_point(ray, t);
// 	double hDis = rt_vector_sub(pa, cylinder->center_p_vec).y;
// 	if ((- 1.0 * cylinder->height / 2.0f) <= hDis && hDis <= (cylinder->height / 2.0f))
// 	{
// 		res.distance = t * rt_vector_magnitude(ray.direction);
// 		res.p_vec = pa;
// 		t_3d_vec	tmp_normal;
// 		tmp_normal.x = 2 * flag *(pa.x - cylinder->center_p_vec.x);//法線方向の計算
// 		tmp_normal.y = 0;												//法線方向の計算
// 		tmp_normal.z = 2 * flag *(pa.z - cylinder->center_p_vec.z);//法線方向の計算
// 		res.normal = rt_vector_normalize(tmp_normal);
// 		return (res);
// 	}
// 	return (res);
// }
