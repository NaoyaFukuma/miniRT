/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_raytrace.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 18:49:47 by kyamagis          #+#    #+#             */
/*   Updated: 2023/01/23 16:07:43 by nfukuma          ###   ########.fr       */
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

t_insec_res	rt_intersection_testresult(t_obj *nearest_shape, t_insec_p nearest_intp, bool t_or_f)
{
	t_insec_res	it;

	it.insec_p.unit_n_vec.x = NOT_INTERSECT;
	if (t_or_f == true)
	{
		it.obj = nearest_shape;
		it.insec_p = nearest_intp;
	}
	return (it);
}

t_insec_p	rt_get_intersection_point_form_objs(t_obj *objs, t_ray ray)
{
	t_insec_p	res;

	res.unit_n_vec.x = NOT_INTERSECT;
	if (e_PLANE == objs->shape)
	{
		res = rt_pl_intersec(objs->plane, ray);
	}
	else if (e_SPHERE == objs->shape)
	{
		res = rt_sp_intersec(objs->sphere, ray);
	}
	else if (e_CYLINDER == objs->shape)
	{
		res = rt_cy_intersec(objs->cylinder, ray);
	}
	else if (e_CONE == objs->shape)
	{
		res = rt_co_intersec(objs->cone, ray);
	}
	return (res);
}

t_insec_res	rt_test_intersection_with_all(t_obj *objs, t_ray ray, double maxDist, bool exitFound)
{
	t_insec_p	res;
	t_insec_p	nearest_intp;
	t_obj					*nearest_shape;

	nearest_shape = NULL;
	nearest_intp.unit_n_vec.x = NOT_INTERSECT;
	while (objs)
	{
		res = rt_get_intersection_point_form_objs(objs, ray);
		if (res.unit_n_vec.x != NOT_INTERSECT && maxDist >= res.dist)
		{
			if (nearest_intp.unit_n_vec.x == NOT_INTERSECT
				|| nearest_intp.dist > res.dist)
			{
				nearest_intp = res;
				nearest_shape = objs;
				if (exitFound == true)
					return (rt_intersection_testresult(nearest_shape, nearest_intp, true));
			}
		}
		objs = objs->next;
	}
	if (nearest_intp.unit_n_vec.x != NOT_INTERSECT)
		return (rt_intersection_testresult(nearest_shape, nearest_intp, true));
	return (rt_intersection_testresult(nearest_shape, nearest_intp, false));
}

t_insec_res	rt_test_intersection_with_all_ambient(t_obj *objs, t_ray ray)
{
	return (rt_test_intersection_with_all(objs, ray, DBL_MAX, false));
}

t_rgb_vec	rt_get_obj_color(t_obj *obj)
{
	if (e_PLANE == obj->shape)
	{
		return (obj->plane->color);
	}
	else if (e_SPHERE == obj->shape)
	{
		return (obj->sphere->color);
	}
	else if (e_CYLINDER == obj->shape)
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

	tmp_direction = rt_vec_sub(pls->p_vec, insect_p_vec);
	res.dist = rt_vec_mag(tmp_direction);
	res.unit_d_vec = rt_vec_to_unit(tmp_direction);
	res.intensity = rt_rgb_vec_copy(pls->lite_color);
	return (res);
}

t_ray	rt_make_shadow_ray(t_3d_vec insect_p_vec, t_lighting lighting)
{
	t_ray	shadow_ray;

	shadow_ray.start = rt_vec_add(insect_p_vec, rt_vec_mult(lighting.unit_d_vec, C_EPSILON));
	shadow_ray.unit_d_vec = lighting.unit_d_vec;
	return (shadow_ray);
}

double	rt_constrain(double num, double low, double high)
{
	return (rt_min(rt_max(num, low), high));
}




double	rt_calculate_cos_phi(t_3d_vec eye_dir, t_lighting lighting, t_insec_p res, double n_dot_l)
{
	t_3d_vec	ref_dir;
	t_3d_vec	unit_eyedir;

	ref_dir = rt_vec_sub(rt_vec_mult(rt_vec_mult(res.unit_n_vec, n_dot_l), 2), lighting.unit_d_vec);
	unit_eyedir = rt_vec_to_unit(rt_vec_mult(eye_dir, -1));
	return (rt_constrain(rt_vec_dot(unit_eyedir, ref_dir), 0, 1));
}

t_rgb_vec	rt_exp_cos_phi(t_rt_data *rt, double v_dot_r)
{
	double		cos_phi;

	cos_phi = pow(v_dot_r, rt->scene.material.shininess);
	return (rt_rgb_vec_constructor(cos_phi, cos_phi, cos_phi));
}



t_rgb_vec	rt_calculate_spec_and_diffu(t_rt_data *rt, t_3d_vec	eye_dir, t_insec_res	test_result, t_lighting lighting)
{
	t_insec_p	res;
	t_rgb_vec				col;
	double					n_dot_l;

	res = test_result.insec_p;
	col = rt_rgb_vec_constructor(0, 0, 0);
	n_dot_l = rt_constrain(rt_vec_dot(res.unit_n_vec, lighting.unit_d_vec), 0, 1);
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

bool	rt_shadow_intersection(t_rt_data *rt, t_insec_res test_result, t_lighting lighting)
{
	t_insec_res	shadow_res;
	t_insec_p		res;
	t_ray						shadow_ray;

	res = test_result.insec_p;
	shadow_ray = rt_make_shadow_ray(res.p_vec, lighting);
	shadow_res = rt_test_intersection_with_all(rt->scene.objs, shadow_ray, lighting.dist - C_EPSILON, true);
	if (shadow_res.insec_p.unit_n_vec.x != NOT_INTERSECT)
	{
		return (true);
	}
	return (false);
}


t_rgb_vec	rt_add_spec_and_diffu_with_all(t_rt_data *rt, t_3d_vec	eye_dir, t_insec_res test_result)
{
	t_p_lite_src				*pls;
	t_insec_p		res;
	t_rgb_vec					col;
	t_lighting					lighting;

	pls = rt->scene.pls_s;
	res = test_result.insec_p;
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
	t_insec_res	test_result;
	t_rgb_vec					col;
	t_rgb_vec					amb;
	t_rgb_vec					spec_diffu;

	test_result = rt_test_intersection_with_all_ambient(rt->scene.objs, ray);
	if (test_result.insec_p.unit_n_vec.x == NOT_INTERSECT)
		return (rt_rgb_vec_constructor(NOT_INTERSECT, 0, 0));
	col = rt_rgb_vec_constructor(0, 0, 0);
	amb = rt_rgb_vec_pi_2(rt->scene.amb_color, rt->scene.material.amb_fact);
	col = rt_rgb_vec_add(col, amb);
	spec_diffu = rt_add_spec_and_diffu_with_all(rt, ray.unit_d_vec, test_result);
	col = rt_rgb_vec_add(col, spec_diffu);
	return (col);
}
