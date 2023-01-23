/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_raytrace.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyamagis <kyamagis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 18:49:47 by kyamagis          #+#    #+#             */
/*   Updated: 2023/01/23 15:46:15 by kyamagis         ###   ########.fr       */
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
	t_intersection_point	nearest_intp;
	t_obj					*nearest_shape;

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

t_rgb_vec	rt_rgb_vec_pi(t_rgb_vec intensity, t_rgb_vec factor,
		t_rgb_vec n_dot_l)
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


t_lighting	rt_calculate_lighting_at_intersection(t_p_lite_src *pls,
													t_3d_vec insect_p_vec)
{
	t_lighting	res;
	t_3d_vec	tmp_direction;

	tmp_direction = rt_vector_sub(pls->p_vec, insect_p_vec);
	res.distance = rt_vector_magnitude(tmp_direction);
	res.unit_direction = rt_vector_normalize(tmp_direction);
	res.intensity = rt_rgb_vec_copy(pls->lite_color);
	return (res);
}

t_ray	rt_make_shadow_ray(t_3d_vec insect_p_vec, t_lighting lighting)
{
	t_ray	shadow_ray;

	shadow_ray.start = rt_vector_add(insect_p_vec, rt_vector_mult(lighting.unit_direction, C_EPSILON));
	shadow_ray.direction = lighting.unit_direction;
	return (shadow_ray);
}

double	rt_constrain(double num, double low, double high)
{
	return (rt_min(rt_max(num, low), high));
}




double	rt_calculate_cos_phi(t_3d_vec eye_dir, t_lighting lighting, t_intersection_point res, double n_dot_l)
{
	t_3d_vec	ref_dir;
	t_3d_vec	unit_eyedir;

	ref_dir = rt_vector_sub(rt_vector_mult(rt_vector_mult(res.normal, n_dot_l), 2), lighting.unit_direction);
	unit_eyedir = rt_vector_normalize(rt_vector_mult(eye_dir, -1));
	return (rt_constrain(rt_vector_dot(unit_eyedir, ref_dir), 0, 1));
}

t_rgb_vec	rt_exp_cos_phi(t_rt_data *rt, double v_dot_r)
{
	double		cos_phi;

	cos_phi = pow(v_dot_r, rt->scene.material.shininess);
	return (rt_rgb_vec_constructor(cos_phi, cos_phi, cos_phi));
}



t_rgb_vec	rt_calculate_spec_and_diffu(t_rt_data *rt, t_3d_vec	eye_dir, t_intersection_testresult	test_result, t_lighting lighting)
{
	t_intersection_point	res;
	t_rgb_vec				col;
	double					n_dot_l;

	res = test_result.intersection_point;
	col = rt_rgb_vec_constructor(0, 0, 0);
	n_dot_l = rt_constrain(rt_vector_dot(res.normal, lighting.unit_direction), 0, 1);
	//n_dot_l *= return_random_ratio(rt->scene.current_x * rt->scene.current_y, 50);
	col = rt_rgb_vec_add(col, rt_rgb_vec_pi(lighting.intensity, \
											rt_get_obj_color(test_result.obj), \
											rt_rgb_vec_constructor(n_dot_l, n_dot_l, n_dot_l)));
	if (n_dot_l > 0.0)
	{
		// rt_exp_cos_phi(rt, rt_calculate_cos_phi(eye_dir, lighting, res, n_dot_l));
		col = rt_rgb_vec_add(col, \
							rt_rgb_vec_pi(lighting.intensity, rt->scene.material.spec_fact, rt_exp_cos_phi(rt, rt_calculate_cos_phi(eye_dir, lighting, res, n_dot_l))));
	}
	return(col);
}

bool	rt_shadow_intersection(t_rt_data *rt, t_intersection_testresult test_result, t_lighting lighting)
{
	t_intersection_testresult	shadow_res;
	t_intersection_point		res;
	t_ray						shadow_ray;

	res = test_result.intersection_point;
	shadow_ray = rt_make_shadow_ray(res.p_vec, lighting);
	shadow_res = rt_test_intersection_with_all(rt->scene.objs, shadow_ray, lighting.distance - C_EPSILON, true);
	if (shadow_res.intersection_point.normal.x != NOT_INTERSECT)
	{
		return (true);
	}
	return (false);
}


t_rgb_vec	rt_add_spec_and_diffu_with_all(t_rt_data *rt, t_3d_vec	eye_dir, t_intersection_testresult test_result)
{
	t_p_lite_src				*pls;
	t_intersection_point		res;
	t_rgb_vec					col;
	t_lighting					lighting;

	pls = rt->scene.pls_s;
	res = test_result.intersection_point;
	col = rt_rgb_vec_constructor(0, 0, 0);
	while (pls)
	{
		lighting = rt_calculate_lighting_at_intersection(pls, res.p_vec);
		if (rt_shadow_intersection(rt, test_result, lighting) == true)
		{
			pls = pls->next;
			continue ;
		}
		col = rt_rgb_vec_add(col, rt_calculate_spec_and_diffu(rt, eye_dir, test_result, lighting));
		pls = pls->next;
	}
	return (col);
}

t_rgb_vec	rt_raytrace(t_rt_data *rt, t_ray ray)
{
	t_intersection_testresult	test_result;
	t_rgb_vec					col;
	t_rgb_vec					amb;
	t_rgb_vec					spec_diffu;

	test_result = rt_test_intersection_with_all_ambient(rt->scene.objs, ray);
	if (test_result.intersection_point.normal.x == NOT_INTERSECT)
		return (rt_rgb_vec_constructor(NOT_INTERSECT, 0, 0));
	col = rt_rgb_vec_constructor(0, 0, 0);
	amb = rt_rgb_vec_pi_2(rt->scene.amb_color, rt->scene.material.amb_fact);
	col = rt_rgb_vec_add(col, amb);
	spec_diffu = rt_add_spec_and_diffu_with_all(rt, ray.direction, test_result);
	col = rt_rgb_vec_add(col, spec_diffu);
	return (col);
}
