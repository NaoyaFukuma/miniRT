/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_eye_raytrace.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 14:24:48 by kyamagis          #+#    #+#             */
/*   Updated: 2023/01/20 15:06:08 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_structs.h"
#include "rt_vector.h"
#include "rt_draw.h"

#include <stdio.h>

t_3d_vec	rt_calculate_pw(t_rt_data *rt, double fx, double fy)
{
	t_3d_vec	center_position_on_screen;
	t_3d_vec	variation_form_center_position_on_screen;

	center_position_on_screen = rt_vector_add(rt->scene.camara.camera_position, \
											rt_vector_mult(rt->scene.camara.unit_camera_direction, rt->scene.camara.screen_distance));

	variation_form_center_position_on_screen = \
		rt_vector_add(rt_vector_mult(rt->scene.camara.unit_screen_direction_x_vec , fx), rt_vector_mult(rt->scene.camara.unit_screen_direction_y_vec , fy));
	return (rt_vector_add(center_position_on_screen, variation_form_center_position_on_screen));
}

t_ray	rt_eye_ray_constructor(t_3d_vec position_on_screen, t_rt_data *rt)
{
	t_ray		eye_ray;

	eye_ray.start = rt->scene.camara.camera_position;
	eye_ray.direction = rt_vector_normalize(rt_vector_sub(position_on_screen, rt->scene.camara.camera_position));// 視線方向 pw - eyePos
	return (eye_ray);
}

t_rgb_vec	rt_eye_raytrace(t_rt_data *rt, double fx, double fy)
{
	t_3d_vec	position_on_screen;
	t_ray		eye_ray;

	position_on_screen = rt_calculate_pw(rt, fx, fy);//スクリーン上の点 pw = 𝐩𝐞→+𝑚𝐝′𝐟→+𝑓𝑥𝐝𝐱→+𝑓𝑦𝐝𝐲→
	eye_ray = rt_eye_ray_constructor(position_on_screen, rt);
	return (rt_raytrace(rt, eye_ray));
}
