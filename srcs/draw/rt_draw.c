/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 14:24:48 by kyamagis          #+#    #+#             */
/*   Updated: 2023/01/19 12:05:45 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "rt_strucs.h"
#include "rt_vector.h"
#include "rt_draw.h"
#include "mlx.h"

int	rt_rgb_vec_to_int_color(t_rgb_vec col)
{
	int	r;
	int	g;
	int	b;

	r = (int)(col.r);
	g = (int)(col.g);
	b = (int)(col.b);
	return (r * 0xffff + g * 0xff + b);
}

void	rt_pixel_put(t_rt_data *rt, int x, int y, int color)
{
	char	*dst;

	// if (WINDOW_WIDTH <= x || WINDOW_DEPETH <= y)
	// 	return ;
	dst = IMAGE_ADDR + (y * IMAGE_LINE_LENGTH + x * (IMAGE_BITS_PER_PIXEL / 8));
	*(unsigned int *)dst = color;
}

int	rt_to_color(t_rgb_vec col)
{
	int	r;
	int	g;
	int	b;

	r = (int)(255 * rt_constrain(col.r,   0.0, 1.0));
	g = (int)(255 * rt_constrain(col.g, 0.0, 1.0));
	b = (int)(255 * rt_constrain(col.b,  0.0, 1.0));
	return (r * 0xffff + g * 0xff + b);
}

void	rt_x_draw(t_rt_data *rt, int y, int width, double fy)
{
	int			x;
	double		fx;
	int			color;
	t_rgb_vec	col;

	x = 0;
	while (x < width)
	{
		fx = (2.0 * (x / (double)(width - 1))) - 1.0;
		color = rt_rgb_vec_to_int_color(rt_rgb_vec_constructor(100, 149, 237));// 背景色だよ
		col = rt_eye_raytrace(rt, fx, fy);
		if (col.r != NOT_INTERSECT)
		{
			color = rt_to_color(col);// colをcolorに変換して描画色を設定する.
		}
		rt_pixel_put(rt, x, y, color);
		++x;
	}
}

void	rt_draw(t_rt_data *rt)
{
	int		y;
	double	fy;
	int 	height;
	int 	width;

	height = SCREEEAN_HEIGHT;
	width  = SCREEEAN_WIDTH;
	y = 0;
	while (y < height)
	{
		fy = ( - 2.0 * (y / (double)(height - 1))) + 1.0;
		rt_x_draw(rt, y, width, fy);
		++y;
	}
	mlx_put_image_to_window(rt->mlx.mlx, rt->mlx.win, rt->mlx.image.img, 0, 0);
}
