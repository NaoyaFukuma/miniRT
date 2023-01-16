/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyamagis <kyamagis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 14:24:48 by kyamagis          #+#    #+#             */
/*   Updated: 2023/01/16 16:53:54 by kyamagis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "rt_strucs.h"
#include "rt_vector.h"

t_3d_vec	re_calculate_pw(t_rt_data *rt)
{
	t_3d_vec	center_position_on_screen;
	t_3d_vec	variation_form_center_position_on_screen;
	
	center_position_on_screen = scene.eyePosition, rt_vector_mult(forwardDir, scene.screenDistance));
	variation_form_center_position_on_screen = rt_vector_add(rt_vector_mult(xDir , fx), rt_vector_mult(yDir , fy))
	return (rt_vector_add(center_position_on_screen + variation_form_center_position_on_screen))
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

		position_on_screen = //スクリーン上の点 𝐩𝐞→+𝑚𝐝′𝐟→+𝑓𝑥𝐝𝐱→+𝑓𝑦𝐝𝐲→
		
		


		PVector eyeDir  = PVector.sub(pw, scene.eyePosition); // 視線方向 pw - eyePos
		Ray eyeRay = new Ray(scene.eyePosition, eyeDir);
		stroke(color(100, 149, 237)); // 背景色だよ
		FColor col = rayTrace(scene, eyeRay);
		if (col != null)
			stroke(col.toColor()); // colをcolorに変換して描画色を設定する.
		point(x, y);
		++x;
	} //for
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
