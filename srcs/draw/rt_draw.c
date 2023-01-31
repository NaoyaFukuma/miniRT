/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyamagis <kyamagis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 14:24:48 by kyamagis          #+#    #+#             */
/*   Updated: 2023/01/24 12:02:41 by kyamagis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mlx.h"
#include "rt_draw.h"
#include "rt_structs.h"
#include "rt_vector.h"

int	rt_rgb_vec_to_int_color(t_rgb_vec col)
{
	int	r;
	int	g;
	int	b;

	r = (int)(col.r);
	g = (int)(col.g);
	b = (int)(col.b);
	return ((r << 16) + (g << 8) + b);
}

void	rt_pixel_put(t_rt_data *rt, int x, int y, int color)
{
	char	*dst;

	dst = rt->mlx.image.addr + (y * rt->mlx.image.line_length + \
								x * (rt->mlx.image.bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	rt_to_color(t_rgb_vec col)
{
	int	r;
	int	g;
	int	b;

	r = (int)(255 * rt_constrain(col.r, 0.0, 1.0));
	g = (int)(255 * rt_constrain(col.g, 0.0, 1.0));
	b = (int)(255 * rt_constrain(col.b, 0.0, 1.0));
	return ((r << 16) + (g << 8) + b);
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
		fx = x - width / 2;
		rt->scene.current_x = x;
		color = rt_rgb_vec_to_int_color(rt_rgb_vec_constructor_3(0));
		col = rt_eye_raytrace(rt, fx, fy);
		if (col.r != NOT_INTERSECT)
		{
			color = rt_to_color(col);
		}
		rt_pixel_put(rt, x, y, color);
		++x;
	}
}

void	rt_draw(t_rt_data *rt)
{
	int		y;
	double	fy;
	int		height;
	int		width;

	height = rt->scene.scr_height;
	width = rt->scene.scr_width;
	y = 0;
	while (y < height)
	{
		fy = -y + height / 2;
		rt->scene.current_y = y;
		rt_x_draw(rt, y, width, fy);
		++y;
		rt_indicator(height, y);
	}
	mlx_put_image_to_window(rt->mlx.mlx, rt->mlx.win, rt->mlx.image.img, 0, 0);
}
