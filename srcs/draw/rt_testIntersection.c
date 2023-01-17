/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_testIntersection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyamagis <kyamagis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 18:49:47 by kyamagis          #+#    #+#             */
/*   Updated: 2023/01/16 20:26:28 by kyamagis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_vector.h"
#include "rt_strucs.h"
#include "rt_draw.h"
#include "libft.h"
#include <stdbool.h>
#include <float.h>
#include <stdlib.h>

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

t_intersection_point	rt_sp_test_intersection(t_sphere *sphere, t_ray ray)
{
	t_3d_vec tmp    = t_3d_vec.sub(ray.start, center);
	double A = ray.direction.mag() * ray.direction.mag();
	double B = 2 * tmp.dot(ray.direction);
	double C = tmp.dot(tmp) - (radius * radius);
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
		IntersectionPoint res = new IntersectionPoint();
		res.distance = t * ray.direction.mag();
		res.position = ray.getPoint(t);
		res.normal = t_3d_vec.sub(res.position, center);
		res.normal.normalize();
		return res;
	}
	return null;
}

t_intersection_point	rt_cy_test_intersection(t_cylinder *cylinder, t_ray ray)
	{
		t_3d_vec dM = ray.direction.copy();
		dM.y = 0;
		t_3d_vec mM = t_3d_vec.sub(ray.start, center);
		mM.y = 0;

		double A = dM.magSq();
		double B = 2 * dM.dot(mM);
		double C = mM.magSq() - (radius * radius);

		double D = B * B - 4 * A * C;
		double t = -1;

    int flag = 1;

		if (D == 0)
		{
			t = -B / (2 * A);
		}
		// else if (D > 0)
		// {
		// 	double t1 = ( -B - sqrt(D)) / (2 * A);
		// 	double t2 = ( -B + sqrt(D)) / (2 * A);
		// 	t = t1 > 0 && t2 > 0 ? min(t1, t2) : max(t1, t2);
		// }
		else if (D > 0)
        {
            double t1 = ( -B - sqrt(D)) / (2 * A);
            double t2 = ( -B + sqrt(D)) / (2 * A);
            //t = t1 > 0 && t2 > 0 ? min(t1, t2) : max(t1, t2);

            if (t1 > 0 && t2 > 0)
            {
                t = min(t1, t2);
                t_3d_vec pa = ray.getPoint(t);
                double hDis = t_3d_vec.sub(pa, center).y;
                if (hDis < (-height / 2.0f) || (height / 2.0f) < hDis)
                {
                     t = max(t1, t2);
                     flag = 0;
                }
                 
            }
            else
            {
                t = max(t1, t2);
            }
        }

		if (t > 0)
		{
			t_3d_vec pa = ray.getPoint(t);
			double hDis = t_3d_vec.sub(pa, center).y;
			if (( -height / 2.0f) <= hDis && hDis <= (height / 2.0f))
			{
				IntersectionPoint res = new IntersectionPoint();
				res.distance = t * ray.direction.mag();
				res.position = pa;
				res.normal = new t_3d_vec(); //法線方向の計算
				
        if (flag == 1)
        {
          res.normal.x = 2 * (pa.x - center.x);
          res.normal.y = 0;
          res.normal.z = 2 * (pa.z - center.z);  
        }
        else
        {
          res.normal.x = -2 * (pa.x - center.x);
          res.normal.y = 0;
          res.normal.z = -2 * (pa.z - center.z);  
        }
       	res.normal.normalize();
				return res;
			}
		}
		return null;
}


t_intersection_point	rt_co_test_intersection(t_cone *cone, t_ray ray)
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
