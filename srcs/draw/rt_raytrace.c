/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_raytrace.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyamagis <kyamagis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 18:49:47 by kyamagis          #+#    #+#             */
/*   Updated: 2023/01/17 15:30:07 by kyamagis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_vector.h"
#include "rt_strucs.h"
#include "rt_draw.h"
#include "libft.h"
#include <stdbool.h>
#include <float.h>
#include <stdlib.h>

t_intersection_testresult	*malloc_intersection_testresult(t_obj *nearest_shape, t_intersection_point *nearest_intp)
{
	t_intersection_testresult	*it;

	it = (t_intersection_testresult *)malloc(sizeof(t_intersection_testresult));
	if (it == NULL)
	{
		ft_putendl_fd("malloc\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	it->obj = nearest_shape;
	it->intersection_point = nearest_intp;
	return (it);
}

t_intersection_point	*rt_get_intersection_point_form_objs(t_obj *objs, t_ray ray)
{
	t_intersection_point 	*res;

	if (E_PLANE == objs)
	{
		res = rt_pl_test_intersection(objs->plane, ray);
	}
	else if (E_SPHERE == objs)
	{
		res = rt_sp_test_intersection(objs->sphere, ray);
	}
	else if (E_CYLINDER == objs)
	{
		res = rt_cy_test_intersection(objs->cylinder, ray);
	}
	else if (E_CONE == objs)
	{
		res = rt_co_test_intersection(objs->cone, ray);
	}
	return (NULL);
}

t_intersection_testresult	*testIntersectionWithAll(t_obj *objs, t_ray ray, double maxDist, bool exitFound)
{
	t_obj 					*nearest_shape = NULL; // 最も近い物体
	t_intersection_point	*nearest_intp = NULL; // 最も近い交点位置
	t_intersection_point 	*res = NULL;

	while (objs)//tmpでなくて良いか？
	{
		res = rt_get_intersection_point_form_objs(objs, ray);
		if (res != NULL && maxDist >= res->distance)
		{
			if (nearest_intp == NULL || nearest_intp->distance > res->distance)
			{
				nearest_intp = res;
				nearest_shape = objs;
				if (exitFound == true)
					return (malloc_intersection_testresult(nearest_shape, nearest_intp));
			}
		}
		objs = objs->next;
	}
	if (nearest_intp != NULL)
		return (malloc_intersection_testresult(nearest_shape, nearest_intp));
	free(res);
	return NULL;
}

// t_intersection_testresult *rt_testIntersectionWithAll_ray(t_obj *objs, t_ray ray, double maxDist, bool exitFound)
// {
// 	t_intersection_point	*nearest_intp = NULL; // 最も近い交点位置
// 	t_obj 					*nearest_shape = NULL; // 最も近い物体

// 	while(objs)
// 	{
// 		t_intersection_point *res = rt_get_intersection_point_form_objs(objs, ray);

// 		if (res != NULL && maxDist >= res->distance)
// 		{
// 			if (nearest_intp == NULL || nearest_intp->distance > res->distance)
// 			{
// 				nearest_intp = res;
// 				nearest_shape = objs;
// 				if (exitFound == true)
// 					return (malloc_intersection_testresult(nearest_shape, nearest_intp));
// 			}
// 		}
// 		objs = objs->next;
// 	}
// 	if (nearest_intp != NULL)
// 		return (malloc_intersection_testresult(nearest_shape, nearest_intp));
// 	free(res);
// 	return NULL;
// }

t_intersection_testresult *testIntersectionWithAll_ambient(t_obj *objs, t_ray ray)
{
	return testIntersectionWithAll(objs, ray, DBL_MAX, false);
}

t_rgb_vec	rt_get_obj_color(t_obj *obj)
{
	if (E_PLANE == obj)
	{
		return (obj->plane->color);
	}
	else if (E_SPHERE == obj)
	{
		return (obj->sphere->color);
	}
	else if (E_CYLINDER == obj)
	{
		return (obj->cylinder->color);
	}
	else if (E_CONE == obj)
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
		ft_putendl_fd("malloc\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	col->r = r;
	col->g = g;
	col->b = b;
	return (col);
}

void	rt_rgb_vec_add(t_rgb_vec *col, t_rgb_vec reflected_light)
{
	col->r += reflected_light.r;
	col->g += reflected_light.g;
	col->b += reflected_light.b;
}

t_rgb_vec	rt_rgb_vec_pi(t_rgb_vec intensity, t_rgb_vec factor, t_rgb_vec nldot)
{
	t_rgb_vec	color;

	color.r = intensity.r * factor.r * nldot.r;
	color.g = intensity.g * factor.g * nldot.g;
	color.b = intensity.b * factor.b * nldot.b;
	return (color);
}

t_lighting	rt_calculate_lighting_at_intersection(t_point_lite_source *pls, t_3d_vec intersection_position)
{
	t_lighting	res;
	t_3d_vec	tmp_direction;

	tmp_direction = rt_vector_sub(pls->position, intersection_position);
	res.distance = rt_vector_magnitude(tmp_direction);
	res.unit_direction = rt_vector_normalize(tmp_direction);
	res.intensity = rt_rgb_vec_copy(pls->lite_color);
	return (res);
}

t_ray	rt_shadow_ray(t_3d_vec intersection_position, t_lighting lighting)
{
	t_3d_vec	microincrease;

	microincrease = rt_vector_mult(lighting.unit_direction, (1.0f + C_EPSILON));
	return (rt_vector_add(intersection_position, microincrease));
}

double	rt_constrain_between_0_and_1(double	num)
{
	if (num < 0.0)
		return (0.0);
	else if (1.0 < num)
		return (1.0);
	return (num);
}


t_rgb_vec	*rt_raytrace(t_rt_data *rt, t_ray ray)
{
	t_3d_vec eyeDir = ray.direction;

	// 全ての物体との交差判定をしてるよ
	t_intersection_testresult *test_result = testIntersectionWithAll_ambient(rt->scene.objs, ray);//free()を忘れずに

	if (test_result != NULL) // 交点があったとき
	{
		t_obj					*obj = test_result->obj; // 最も近い交点を持つ物体
		t_intersection_point	*res = test_result->intersection_point; // 最も近い交点の情報
		t_rgb_vec				mat = rt_get_obj_color(obj); // // 最も近い交点を持つ物体の材質情報
		t_rgb_vec				*col = rt_malloc_rgb_vec(0, 0, 0);// 放射輝度を保存するためのFColorのインスタンスを生成

		rt_rgb_vec_add(col, rt_rgb_vec_pi(rt->scene.ambient_color, mat, rt_rgb_vec_constructor(1, 1, 1)));// 環境光の反射光の放射輝度を計算する ambientIntensityがない

		t_point_lite_source	*pls = rt->scene->pls_s;
		
		while (pls)// 全ての光源に対して処理を行う
		{
			t_lighting	lighting = rt_calculate_lighting_at_intersection(pls, res->position);// 交点におけるライティングを計算する
			t_ray 		shadow_ray =  rt_shadow_ray(res->position, lighting);// シャドウレイを作る

			t_intersection_testresult *shadow_res = rt_testIntersectionWithAll(rt->scene.objs, shadow_ray, lighting.distance - C_EPSILON, true);
			if (shadow_res != NULL) // 交点が見つかった＝影になるので、次の点光源へ（continue）
				continue;
			/*?????*/double nlDot = rt_constrain_between_0_and_1(rt_vector_dot(res->normal, lighting.unit_direction));// 法線ベクトルと入射ベクトルの内積を計算して,値の範囲を[0, 1]に制限する.
			rt_rgb_vec_add(col, rt_rgb_vec_pi(lighting.intensity, rt->scene.material.diffuseFactor, rt_rgb_vec_constructor(nlDot, nlDot, nlDot)));// 拡散反射光の放射輝度を計算する.

			if (nlDot > 0.0)
			{
				t_3d_vec refDir = rt_vector_sub(rt_vector_mult(rt_vector_mult(res->normal, nlDot), 2), lighting.unit_direction);// 正反射ベクトル
				t_3d_vec unit_invEyeDir =  rt_vector_normalize(rt_vector_mult(eyeDir, -1));// 視線ベクトルの逆ベクトル

				double	vrDot = rt_constrain_between_0_and_1(rt_vector_dot(unit_invEyeDir, refDir));// 視線ベクトルの逆ベクトルと正反射ベクトルの内積を計算して,値を[0, 1]に制限する.

				double	cosine_phi = pow(vrDot, rt->scene.material.shininess);
				rt_rgb_vec_add(col, rt_rgb_vec_pi(lighting.intensity, rt->scene.material.specularFactor, rt_rgb_vec_constructor(cosine_phi, cosine_phi, cosine_phi)));// 鏡面反射光の放射輝度を計算する.
			}
			pls = pls->next;
		}
		return (col);
	}

	return (NULL);
}