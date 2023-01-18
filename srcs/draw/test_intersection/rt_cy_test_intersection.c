/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_cy_test_intersection.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyamagis <kyamagis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 18:49:47 by kyamagis          #+#    #+#             */
/*   Updated: 2023/01/18 12:04:02 by kyamagis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_vector.h"
#include "rt_strucs.h"
#include "rt_draw.h"
#include "libft.h"
#include <stdbool.h>
#include <float.h>
#include <math.h>

double	rt_cy_calculate_directional_vector_coefficients(t_cylinder *cylinder, t_ray ray, double *flag)
{
	t_3d_vec dM = rt_vector_copy(ray.direction);
	t_3d_vec mM = rt_vector_sub(ray.start, cylinder->center_position);

	dM.y = 0.0;
	mM.y = 0.0;

	double A = pow(rt_vector_magnitude(dM), 2.0);
	double B = 2.0 * rt_vector_dot(dM, mM);
	double C = rt_vector_dot(mM, mM) - pow(cylinder->radius, 2.0);
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

			double hDis = rt_vector_sub(pa, cylinder->center_position).y;
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
	double hDis = rt_vector_sub(pa, cylinder->center_position).y;
	if ((- 1.0 * cylinder->height / 2.0f) <= hDis && hDis <= (cylinder->height / 2.0f))
	{
		res.distance = t * rt_vector_magnitude(ray.direction);
		res.position = pa;
		t_3d_vec	tmp_normal;
		tmp_normal.x = 2 * flag *(pa.x - cylinder->center_position.x);//法線方向の計算
		tmp_normal.y = 0;												//法線方向の計算
		tmp_normal.z = 2 * flag *(pa.z - cylinder->center_position.z);//法線方向の計算
		res.normal = rt_vector_normalize(tmp_normal);
		return (res);
	}
	return (res);
}
