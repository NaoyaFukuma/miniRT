/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_testIntersection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyamagis <kyamagis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 18:49:47 by kyamagis          #+#    #+#             */
/*   Updated: 2023/01/17 15:47:00 by kyamagis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_vector.h"
#include "rt_strucs.h"
#include "rt_draw.h"
#include "libft.h"
#include <stdbool.h>
#include <float.h>
#include <stdlib.h>
#include <math.h>

t_3d_vec	rt_get_point(t_ray ray, double t)
{
	return (rt_vector_add(ray.start, rt_vector_mult(ray.direction, t)));
}

t_intersection_point	*rt_pl_test_intersection(t_plane *plane, t_ray ray)
{
	double dn_dot = rt_vector_dot(ray.direction, plane->unit_normal_vec);
	if (dn_dot != 0)
	{
		double t = (rt_vector_dot(ray.direction, plane->position) - \
					rt_vector_dot(ray.start, plane->unit_normal_vec)) / dn_dot;
		if (t > 0)
		{
			t_intersection_point	*res;

			res = (t_intersection_point *)malloc(sizeof(t_intersection_point));
			if (res == NULL)
			{
				ft_putendl_fd("malloc\n", STDERR_FILENO);
				exit(EXIT_FAILURE);
			}
			res->distance = t * rt_vector_magnitude(ray.direction);
			res->position = rt_get_point(ray, t);
			res->normal = rt_vector_copy(plane->unit_normal_vec);//いらないか？
			return (res);
		}
	}
	return (NULL);//どうする？
}

double	rt_min(double a, double b)
{
	if (a < b)
		return (a);
	return (b);
}

double	rt_max(double a, double b)
{
	if (b < a)
		return (a);
	return (b);
}

t_intersection_point	*rt_sp_test_intersection(t_sphere *sphere, t_ray ray)
{
	t_3d_vec tmp    = rt_vector_sub(ray.start, sphere->center_position);
	
	double A = pow(rt_vector_magnitude(ray.direction), 2.0);
	double B = 2 * rt_vector_dot(tmp, ray.direction);
	double C = rt_vector_dot(tmp, tmp) - pow(sphere->radius, 2.0);
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
		t = t1 > 0.0 && t2 > 0.0 ? rt_min(t1, t2) : rt_max(t1, t2);
	}
	if (t > 0.0)
	{
		t_intersection_point	*res;

		res = (t_intersection_point *)malloc(sizeof(t_intersection_point));
		if (res == NULL)
		{
			ft_putendl_fd("malloc\n", STDERR_FILENO);
			exit(EXIT_FAILURE);
		}
		res->distance = t * rt_vector_magnitude(ray.direction);
		res->position = rt_get_point(ray, t);
		t_3d_vec tmp_normal = rt_vector_sub(res->position, sphere->center_position);
		res->normal = rt_vector_normalize(tmp_normal);
		return (res);
	}
	return (NULL);
}

t_intersection_point	*rt_cy_test_intersection(t_cylinder *cylinder, t_ray ray)
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

    	double flag = 1.0;

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
					flag = -1.0;
				}
			}
			else
			{
				t = rt_max(t1, t2);
			}
		}

		if (t > 0)
		{
			t_3d_vec pa = rt_get_point(ray, t);
			
			double hDis = rt_vector_sub(pa, cylinder->center_position).y;
			if ((- 1.0 * cylinder->height / 2.0f) <= hDis && hDis <= (cylinder->height / 2.0f))
			{
				t_intersection_point	*res;

				res = (t_intersection_point *)malloc(sizeof(t_intersection_point));
				if (res == NULL)
				{
					ft_putendl_fd("malloc\n", STDERR_FILENO);
					exit(EXIT_FAILURE);
				}
				res->distance = t * rt_vector_magnitude(ray.direction);
				res->position = pa;
				t_3d_vec	tmp_normal;
				tmp_normal.x = 2 * flag *(pa.x - cylinder->center_position.x);//法線方向の計算
				tmp_normal.y = 0;												//法線方向の計算
				tmp_normal.z = 2 * flag *(pa.z - cylinder->center_position.z);//法線方向の計算
				res->normal = rt_vector_normalize(tmp_normal);
				return (res);
			}
		}
		return (NULL);
}


t_intersection_point	*rt_co_test_intersection(t_cone *cone, t_ray ray)
{
	t_3d_vec d = ray.direction.copy();
	t_3d_vec m = t_3d_vec.sub(t_3d_vec.sub(ray.start, center), new t_3d_vec(0, height, 0));

	double A = d.x * d.x - (d.y * radius / height) * (d.y * radius / height) + d.z * d.z;
	double B = 2 * (d.x * m.x - (radius / height) * (radius / height) * d.y * m.y + d.z * m.z);
	double C = m.x * m.x - (m.y * radius / height) * (m.y * radius / height) + m.z * m.z;
	double D = B * B - 4 * A * C;
	double t = -1;

	if (D == 0)
	{
		t = -B / (2 * A);
	}
	else if (D > 0)
	{
		double t1 = ( -B - sqrt(D)) / (2 * A);
		double t2 = ( -B + sqrt(D)) / (2 * A);
		t = t1 > 0 && t2 > 0 ? min(t1, t2) : max(t1, t2);
	}
	if (t > 0)
	{
		t_3d_vec pa = ray.getPoint(t);
		double hDis = t_3d_vec.sub(pa, center).y;
		if (0 <= hDis && hDis <= height)
		{
			IntersectionPoint res = new IntersectionPoint();
			res.distance = t * ray.direction.mag();
			res.position = pa;
			res.normal = new t_3d_vec(); //法線方向の計算

			res.normal.x = 2 * (pa.x - center.x);
			res.normal.y = -2 * ((radius / height) * (radius / height)) * (pa.y - center.y - height);
			res.normal.z = 2 * (pa.z - center.z);
			res.normal.normalize();
			return res;
		}
	}
	return null;
}
