/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyamagis <kyamagis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 14:24:48 by kyamagis          #+#    #+#             */
/*   Updated: 2023/01/16 21:21:39 by kyamagis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "rt_strucs.h"
#include "rt_vector.h"
#include "rt_draw.h"

t_3d_vec	re_calculate_pw(t_rt_data *rt, double fx, double fy)
{
	PVector upDir = new PVector(0, 1, 0); // 上方向（ey_vec）
	PVector forwardDir = PVector.sub(scene.lookAt , scene.eyePosition); // df
	forwardDir.normalize(); // df'
	PVector xDir = upDir.cross(forwardDir);
	PVector yDir = forwardDir.cross(xDir);

	t_3d_vec	center_position_on_screen;
	t_3d_vec	variation_form_center_position_on_screen;
	
	center_position_on_screen = rt_vector_add(CAMERA_POSITION, \
											rt_vector_mult(forwardDir, SCREEN_DISTANCE));
	variation_form_center_position_on_screen = rt_vector_add(rt_vector_mult(xDir , fx), rt_vector_mult(yDir , fy));
	return (rt_vector_add(center_position_on_screen, variation_form_center_position_on_screen));
}

void	rt_x_draw(t_rt_data *rt, int y, int width, double fy)
{
	int			x;
	double		fx;
	t_3d_vec	position_on_screen;

	x = 0;
	while (x < width)
	{
		fx = (2.0 * (x / (double)(width - 1))) - 1.0;
		position_on_screen = re_calculate_pw(rt, fx, fy);//スクリーン上の点 𝐩𝐞→+𝑚𝐝′𝐟→+𝑓𝑥𝐝𝐱→+𝑓𝑦𝐝𝐲→

		t_3d_vec	eyeDir  = rt_vector_sub(position_on_screen, CAMERA_POSITION); // 視線方向 pw - eyePos
		t_ray		eyeRay;
	
		eyeRay.start = CAMERA_POSITION;
		eyeRay.direction = eyeDir;

		stroke(color(100, 149, 237)); // 背景色だよ
		t_rgb_vec col = rt_raytrace(rt, eyeRay);
		if (col != null)
			stroke(col.toColor()); // colをcolorに変換して描画色を設定する.
		point(x, y);
		++x;
	}
}

void	rt_draw(t_rt_data *rt)
{
	int		y;
	int		width;
	int		height;
	double	fy;

	y = 0;
	height = rt->scene.screean_height;
	width = rt->scene.screean_width;
	while (y < rt->scene.screean_height)
	{
		fy = ( - 2.0 * (y / (double)(height - 1))) + 1.0;
		rt_x_draw(rt, y, width, height);
		++y;
	}
}
