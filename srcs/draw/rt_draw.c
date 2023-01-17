/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyamagis <kyamagis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 14:24:48 by kyamagis          #+#    #+#             */
/*   Updated: 2023/01/17 15:28:01 by kyamagis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "rt_strucs.h"
#include "rt_vector.h"
#include "rt_draw.h"

t_3d_vec	rt_calculate_pw(t_rt_data *rt, double fx, double fy)
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
	variation_form_center_position_on_screen = \
		rt_vector_add(rt_vector_mult(UNIT_SCREEN_DIRECTION_X_VEC , fx), rt_vector_mult(UNIT_SCREEN_DIRECTION_Y_VEC , fy));
	return (rt_vector_add(center_position_on_screen, variation_form_center_position_on_screen));
}

int	rgb_vec_p_to_int_color(t_rgb_vec *col)
{
	return (col->r * 0xffff + col->g * 0xff + col->b);
}

int	rgb_vec_to_int_color(t_rgb_vec col)
{
	return (col.r * 0xffff + col.g * 0xff + col.b);
}

void	rt_pixel_put(t_rt_data *rt, int x, int y, int color)
{
	char	*dst;

	// if (WINDOW_WIDTH <= x || WINDOW_DEPETH <= y)
	// 	return ;
	dst = IMAGE_ADDR + (y * IMAGE_LINE_LENGTH + x * (IMAGE_BITS_PER_PIXEL / 8));
	*(unsigned int *)dst = color;
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
		position_on_screen = rt_calculate_pw(rt, fx, fy);//スクリーン上の点 𝐩𝐞→+𝑚𝐝′𝐟→+𝑓𝑥𝐝𝐱→+𝑓𝑦𝐝𝐲→

		t_3d_vec	eyeDir  = rt_vector_sub(position_on_screen, CAMERA_POSITION); // 視線方向 pw - eyePos
		t_ray		eyeRay;
	
		eyeRay.start = CAMERA_POSITION;
		eyeRay.direction = eyeDir;

		int color = rgb_vec_to_int_color(rt_rgb_vec_constructor(100, 149, 237));// 背景色だよ
		t_rgb_vec *col = rt_raytrace(rt, eyeRay);
		if (col != NULL)
		{	
			color = rgb_vec_p_to_int_color(col);// colをcolorに変換して描画色を設定する.
			free(col);
		} 
		rt_pixel_put(rt, x, y, color);
		++x;
	}
}

void	rt_draw(t_rt_data *rt)
{
	int		y;
	double	fy;

	y = 0;
	while (y < SCREEEAN_HEIGHT)
	{
		fy = ( - 2.0 * (y / (double)(SCREEEAN_HEIGHT - 1))) + 1.0;
		rt_x_draw(rt, y, SCREEEAN_WIDTH, fy);
		++y;
	}
}
