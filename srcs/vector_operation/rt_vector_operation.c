/* ************************************************************************** */
/*	                                                                        */
/*                                                        :::      ::::::::   */
/*   rt_vector_operation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyamagis <kyamagis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 10:24:34 by kyamagis          #+#    #+#             */
/*   Updated: 2023/01/18 11:13:16 by kyamagis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_strucs.h"
#include "rt_vector.h"
#include <math.h>

t_3d_vec	rt_vector_constructor(double x, double y, double z)
{
	t_3d_vec	vector;

	vector.x = x;
	vector.y = y;
	vector.z = z;
	return (vector);
}

t_3d_vec	rt_vector_add(t_3d_vec a, t_3d_vec b)
{
	t_3d_vec	vector;

	vector.x = a.x + b.x;
	vector.y = a.y + b.y;
	vector.z = a.z + b.z;
	return (vector);
}

t_3d_vec	rt_vector_sub(t_3d_vec a, t_3d_vec b)
{
	t_3d_vec	vector;

	vector.x = a.x - b.x;
	vector.y = a.y - b.y;
	vector.z = a.z - b.z;
	return (vector);
}

t_3d_vec	rt_vector_mult(t_3d_vec a, double t)
{
	t_3d_vec	vector;

	vector.x = a.x * t;
	vector.y = a.y * t;
	vector.z = a.z * t;
	return (vector);
}

double	rt_vector_dot(t_3d_vec a, t_3d_vec b)
{
	return ((a.x * b.x) + (a.y * b.y) + (a.z * b.z));
}

t_3d_vec	rt_vector_cross(t_3d_vec a, t_3d_vec b)
{
	t_3d_vec	vector;

	vector.x = a.y * b.z - a.z * b.y;
	vector.y = a.z * b.x - a.x * b.z;
	vector.z = a.x * b.y - a.y * b.z;
	return (vector);
}

double	rt_vector_magnitude(t_3d_vec a)
{
	return (sqrt((a.x * a.x) + (a.y * a.y) + (a.z * a.z)));
}

t_3d_vec	rt_vector_normalize(t_3d_vec a)
{
	t_3d_vec	vector;
	double		magnitude;

	magnitude = rt_vector_magnitude(a);
	vector.x = a.x / magnitude;
	vector.y = a.y / magnitude;
	vector.z = a.z / magnitude;
	return (vector);
}

t_3d_vec    rt_vector_copy(t_3d_vec a)
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
/*
#include <stdio.h>
int	main(void)
{
	t_3d_vec a = rt_vector_constructor(1, 2, 3);
	printf("a: x = %f, y = %f, z = %f\n", a.x, a.y, a.z);
	t_3d_vec b = rt_vector_constructor(3, 2, 1);
	printf("b: x = %f, y = %f, z = %f\n", b.x, b.y, b.z);

	t_3d_vec add = rt_vector_add(a, b);
	printf("add : x = %f, y = %f, z = %f\n", add.x, add.y, add.z);

	t_3d_vec sub = rt_vector_sub(a, b);
	printf("sub : x = %f, y = %f, z = %f\n", sub.x, sub.y, sub.z);

	t_3d_vec mult = rt_vector_mult(a, 4);
	printf("mult : x = %f, y = %f, z = %f\n", mult.x, mult.y, mult.z);

	double dot = rt_vector_dot(a, b);
	printf("dot = %f\n", dot);

	t_3d_vec d = rt_vector_constructor(1, 1, 0);
	t_3d_vec cross = rt_vector_cross(d, d);
	printf("cross : x = %f, y = %f, z = %f\n", cross.x, cross.y, cross.z);

	t_3d_vec One_third = rt_vector_constructor(1.0f / 3, 1.0f / 3, 1.0f / 3);
	printf("One_third: x = %f, y = %f, z = %f\n", One_third.x, One_third.y, One_third.z);
	double	magnitude = magnitude = rt_vector_magnitude(One_third);
	printf("magnitude = %f\n", magnitude);
	t_3d_vec normalize = rt_vector_normalize(One_third);
	printf("normalize : x = %f, y = %f, z = %f\n", normalize.x, normalize.y, normalize.z);
}
*/
