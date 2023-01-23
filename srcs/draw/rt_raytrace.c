/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_raytrace.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 18:49:47 by kyamagis          #+#    #+#             */
/*   Updated: 2023/01/23 13:18:56 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "rt_draw.h"
#include "rt_structs.h"
#include "rt_vector.h"
#include <float.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>

t_intersection_testresult	rt_intersection_testresult(t_obj *nearest_shape, t_intersection_point nearest_intp, bool t_or_f)
{
	t_intersection_testresult	it;

	it.intersection_point.normal.x = NOT_INTERSECT;
	if (t_or_f == true)
	{
		it.obj = nearest_shape;
		it.intersection_point = nearest_intp;
	}
	return (it);
}

t_intersection_point	rt_get_intersection_point_form_objs(t_obj *objs, t_ray ray)
{
	t_intersection_point	res;

	res.normal.x = NOT_INTERSECT;
	if (E_PLANE == objs->shape)
	{
		res = rt_pl_test_intersection(objs->plane, ray);
	}
	else if (E_SPHERE == objs->shape)
	{
		res = rt_sp_test_intersection(objs->sphere, ray);
	}
	else if (E_CYLINDER == objs->shape)
	{
		res = rt_cy_test_intersection(objs->cylinder, ray);
	}
	else if (E_CONE == objs->shape)
	{
		res = rt_co_test_intersection(objs->cone, ray);
	}
	return (res);
}

t_intersection_testresult	rt_test_intersection_with_all(t_obj *objs, t_ray ray, double maxDist, bool exitFound)
{
	t_intersection_point	res;
	t_obj					*nearest_shape;
	t_intersection_point	nearest_intp;

	nearest_shape = NULL;
	nearest_intp.normal.x = NOT_INTERSECT;
	while (objs)
	{
		res = rt_get_intersection_point_form_objs(objs, ray);
		if (res.normal.x != NOT_INTERSECT && maxDist >= res.distance)
		{
			if (nearest_intp.normal.x == NOT_INTERSECT
				|| nearest_intp.distance > res.distance)
			{
				nearest_intp = res;
				nearest_shape = objs;
				if (exitFound == true)
					return (rt_intersection_testresult(nearest_shape, nearest_intp, true));
			}
		}
		objs = objs->next;
	}
	if (nearest_intp.normal.x != NOT_INTERSECT)
		return (rt_intersection_testresult(nearest_shape, nearest_intp, true));
	return (rt_intersection_testresult(nearest_shape, nearest_intp, false));
}

t_intersection_testresult	rt_test_intersection_with_all_ambient(t_obj *objs, t_ray ray)
{
	return (rt_test_intersection_with_all(objs, ray, DBL_MAX, false));
}

t_rgb_vec	rt_get_obj_color(t_obj *obj)
{
	if (E_PLANE == obj->shape)
	{
		return (obj->plane->color);
	}
	else if (E_SPHERE == obj->shape)
	{
		return (obj->sphere->color);
	}
	else if (E_CYLINDER == obj->shape)
	{
		return (obj->cylinder->color);
	}
	else
	{
		return (obj->cone->color);
	}
}

t_rgb_vec	*rt_malloc_rgb_vec(double r, double g, double b)
{
	t_rgb_vec	*col;

	col = (t_rgb_vec *)malloc(sizeof(t_rgb_vec));
	if (col == NULL)
	{
		ft_putendl_fd("malloc", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	col->r = r;
	col->g = g;
	col->b = b;
	return (col);
}

t_rgb_vec	rt_rgb_vec_pi(t_rgb_vec intensity, t_rgb_vec factor,
		t_rgb_vec nldot)
{
	t_rgb_vec	color;

	color.r = intensity.r * factor.r * nldot.r;
	color.g = intensity.g * factor.g * nldot.g;
	color.b = intensity.b * factor.b * nldot.b;
	return (color);
}

t_lighting	rt_calculate_lighting_at_intersection(t_p_lite_src *pls,
													t_3d_vec intersection_position)
{
	t_lighting	res;
	t_3d_vec	tmp_direction;

	tmp_direction = rt_vector_sub(pls->p_vec, intersection_position);
	res.distance = rt_vector_magnitude(tmp_direction);
	res.unit_direction = rt_vector_normalize(tmp_direction);
	res.intensity = rt_rgb_vec_copy(pls->lite_color);
	return (res);
}

t_ray	rt_make_shadow_ray(t_3d_vec intersection_position, t_lighting lighting)
{
	t_ray	shadow_ray;

	shadow_ray.start = rt_vector_add(intersection_position, rt_vector_mult(lighting.unit_direction, C_EPSILON));
	shadow_ray.direction = lighting.unit_direction;
	return (shadow_ray);
}

double	rt_constrain(double num, double low, double high)
{
	return (rt_min(rt_max(num, low), high));
}

void	rt_calculate_specular_and_diffuse_with_all(t_rt_data *rt, t_ray ray,
		t_rgb_vec *col, t_intersection_point res, t_rgb_vec mat)
{
	t_3d_vec					eye_dir;
	t_p_lite_src			*pls;
	t_intersection_testresult	shadow_res;
	static int					i;
	double						cosine_phi;
	double						nlDot;

	eye_dir = ray.direction;
	pls = rt->scene.pls_s;
	while (pls)
	{
		t_lighting lighting = rt_calculate_lighting_at_intersection(pls, res.p_vec);
		t_ray shadow_ray = rt_make_shadow_ray(res.p_vec, lighting);
		shadow_res = rt_test_intersection_with_all(rt->scene.objs, shadow_ray, lighting.distance - C_EPSILON, true);
		if (shadow_res.intersection_point.normal.x != NOT_INTERSECT)
		{
			pls = pls->next;
			continue ;
		}
		nlDot = rt_constrain(rt_vector_dot(res.normal, lighting.unit_direction), 0, 1);
		nlDot *= return_random_ratio(rt->scene.current_x * rt->scene.current_y, 50);
		i = 0;
		*col = rt_rgb_vec_add(*col, rt_rgb_vec_pi(lighting.intensity, mat, rt_rgb_vec_constructor(nlDot, nlDot, nlDot)));
		if (nlDot > 0.0)
		{
			t_3d_vec ref_dir = rt_vector_sub(rt_vector_mult(rt_vector_mult(res.normal, nlDot), 2), lighting.unit_direction);
			t_3d_vec unit_invEyeDir = rt_vector_normalize(rt_vector_mult(eye_dir, -1));
			double vrDot = rt_constrain(rt_vector_dot(unit_invEyeDir, ref_dir), 0, 1);
			cosine_phi = pow(vrDot, rt->scene.material.shininess);
			*col = rt_rgb_vec_add(*col, rt_rgb_vec_pi(lighting.intensity, rt->scene.material.spec_fact, rt_rgb_vec_constructor(cosine_phi, cosine_phi, cosine_phi)));
		}
		i++;
		pls = pls->next;
	}
}

t_rgb_vec	rt_raytrace(t_rt_data *rt, t_ray ray)
{
	t_intersection_testresult	test_result;
	t_intersection_point		res;
	t_rgb_vec					mat;
	t_rgb_vec					col;

	test_result = rt_test_intersection_with_all_ambient(rt->scene.objs, ray);
	if (test_result.intersection_point.normal.x == NOT_INTERSECT)
		return (rt_rgb_vec_constructor(NOT_INTERSECT, 0, 0));
	res = test_result.intersection_point;
	mat = rt_get_obj_color(test_result.obj);
	col = rt_rgb_vec_constructor(0, 0, 0);
	col = rt_rgb_vec_add(col, rt_rgb_vec_pi(rt->scene.amb_color, rt->scene.material.amb_fact, rt_rgb_vec_constructor(1, 1, 1)));
	rt_calculate_specular_and_diffuse_with_all(rt, ray, &col, res, mat);
	return (col);
}
