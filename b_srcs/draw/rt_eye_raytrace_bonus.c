/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_eye_raytrace_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 14:24:48 by kyamagis          #+#    #+#             */
/*   Updated: 2023/01/27 16:40:57 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_draw_bonus.h"
#include "rt_structs_bonus.h"
#include "rt_vector_bonus.h"
#include <stdio.h>

t_3d_vec	rt_calc_pw(t_rt_data *rt, double fx, double fy)
{
	t_3d_vec	center_p_on_scr_vec;
	t_3d_vec	var_form_center_p_on_scr_vec;
	t_3d_vec	var_x;
	t_3d_vec	var_y;
	t_3d_vec	cam_to_scr_vec;

	cam_to_scr_vec = rt_vec_mult(rt->scene.cam.unit_cam_dir, \
									rt->scene.cam.scr_dist);
	center_p_on_scr_vec = rt_vec_add(rt->scene.cam.cam_p_vec, cam_to_scr_vec);
	var_x = rt_vec_mult(rt->scene.cam.unit_scr_dir_x_vec, fx);
	var_y = rt_vec_mult(rt->scene.cam.unit_scr_dir_y_vec, fy);
	var_form_center_p_on_scr_vec = rt_vec_add(var_x, var_y);
	return (rt_vec_add(center_p_on_scr_vec, var_form_center_p_on_scr_vec));
}

t_ray	rt_eye_ray_constructor(t_3d_vec position_on_screen, t_rt_data *rt)
{
	const double	epsilon = 1.0 / 512.0;
	const t_ray		eye_ray = {
		.start = rt_vec_add(rt->scene.cam.cam_p_vec, rt_vec_mult(
				rt->scene.cam.unit_cam_dir, epsilon)),
		.unit_d_vec = rt_vec_to_unit(rt_vec_sub(position_on_screen,
				rt->scene.cam.cam_p_vec))
	};

	return (eye_ray);
}

t_rgb_vec	rt_eye_raytrace(t_rt_data *rt, double fx, double fy)
{
	t_3d_vec	position_on_screen;
	t_ray		eye_ray;

	position_on_screen = rt_calc_pw(rt, fx, fy);
	eye_ray = rt_eye_ray_constructor(position_on_screen, rt);
	return (rt_raytrace(rt, eye_ray));
}
