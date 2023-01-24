/* ************************************************************************** */
/*		                                                                     */
/*                                                        :::      ::::::::   */
/*   rt_vector_operation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyamagis <kyamagis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 10:24:34 by kyamagis          #+#    #+#             */
/*   Updated: 2023/01/18 11:13:16 by kyamagis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_structs.h"
#include "rt_vector.h"
#include <math.h>
#include <stdio.h>

t_3d_vec	rt_vec_constructor(double x, double y, double z)
{
	t_3d_vec	vector;

	vector.x = x;
	vector.y = y;
	vector.z = z;
	return (vector);
}

t_3d_vec	rt_vec_constructor_3(double num)
{
	t_3d_vec	vector;

	vector.x = num;
	vector.y = num;
	vector.z = num;
	return (vector);
}

t_3d_vec	rt_vec_add(t_3d_vec a, t_3d_vec b)
{
	t_3d_vec	vector;

	vector.x = a.x + b.x;
	vector.y = a.y + b.y;
	vector.z = a.z + b.z;
	return (vector);
}

t_3d_vec	rt_vec_sub(t_3d_vec a, t_3d_vec b)
{
	t_3d_vec	vector;

	vector.x = a.x - b.x;
	vector.y = a.y - b.y;
	vector.z = a.z - b.z;
	return (vector);
}

t_3d_vec	rt_vec_mult(t_3d_vec a, double t)
{
	t_3d_vec	vector;

	vector.x = a.x * t;
	vector.y = a.y * t;
	vector.z = a.z * t;
	return (vector);
}

double	rt_vec_dot(t_3d_vec a, t_3d_vec b)
{
	return ((a.x * b.x) + (a.y * b.y) + (a.z * b.z));
}

t_3d_vec	rt_vec_cross(t_3d_vec a, t_3d_vec b)
{
	t_3d_vec	vector;

	vector.x = a.y * b.z - a.z * b.y;
	vector.y = a.z * b.x - a.x * b.z;
	vector.z = a.x * b.y - a.y * b.x;
	return (vector);
}

double	rt_vec_mag(t_3d_vec a)
{
	return (sqrt((a.x * a.x) + (a.y * a.y) + (a.z * a.z)));
}

t_3d_vec	rt_vec_to_unit(t_3d_vec a)
{
	t_3d_vec	vector;
	double		magnitude;

	magnitude = rt_vec_mag(a);
	if (magnitude == 0.0)
	{
		return (rt_vec_constructor_3(0.0));
	}
	vector.x = a.x / magnitude;
	vector.y = a.y / magnitude;
	vector.z = a.z / magnitude;
	return (vector);
}

t_3d_vec	rt_vec_copy(t_3d_vec a)
{
	t_3d_vec	vector;

	vector.x = a.x;
	vector.y = a.y;
	vector.z = a.z;
	return (vector);
}

t_rgb_vec	rt_rgb_vec_copy(t_rgb_vec a)
{
	t_rgb_vec	vector;

	vector.r = a.r;
	vector.g = a.g;
	vector.b = a.b;
	return (vector);
}

t_rgb_vec	rt_rgb_vec_constructor(double r, double g, double b)
{
	t_rgb_vec	vector;

	vector.r = r;
	vector.g = g;
	vector.b = b;
	return (vector);
}

t_rgb_vec	rt_rgb_vec_constructor_3(double num)
{
	t_rgb_vec	vector;

	vector.r = num;
	vector.g = num;
	vector.b = num;
	return (vector);
}

t_rgb_vec	rt_rgb_vec_add(t_rgb_vec a, t_rgb_vec b)
{
	t_rgb_vec	vector;

	vector.r = a.r + b.r;
	vector.g = a.g + b.g;
	vector.b = a.b + b.b;
	return (vector);
}

t_rgb_vec	rt_rgb_vec_mult(t_rgb_vec a, double t)
{
	t_rgb_vec	vector;

	vector.r = a.r * t;
	vector.g = a.g * t;
	vector.b = a.b * t;
	return (vector);
}

t_rgb_vec	rt_rgb_vec_pi(t_rgb_vec intensity, t_rgb_vec factor, t_rgb_vec n_dot_l)
{
	t_rgb_vec	color;

	color.r = intensity.r * factor.r * n_dot_l.r;
	color.g = intensity.g * factor.g * n_dot_l.g;
	color.b = intensity.b * factor.b * n_dot_l.b;
	return (color);
}

t_rgb_vec	rt_rgb_vec_pi_2(t_rgb_vec intensity, t_rgb_vec factor)
{
	t_rgb_vec	color;

	color.r = intensity.r * factor.r;
	color.g = intensity.g * factor.g;
	color.b = intensity.b * factor.b;
	return (color);
}
