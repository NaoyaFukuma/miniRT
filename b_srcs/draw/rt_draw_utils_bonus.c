/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_draw_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 14:24:48 by kyamagis          #+#    #+#             */
/*   Updated: 2023/01/27 16:39:57 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_draw_bonus.h"

double	rt_min(double a, double b)
{
	if (a < b)
		return (a);
	return (b);
}

double	rt_max(double a, double b)
{
	if (b < a)
		return (a);
	return (b);
}

t_rgb_vec	rt_get_color_from_image(const t_img *img, int x, int y)
{
	const int			pixel = (y * img->line_length) + (x * 4);
	const char			*dst = &img->addr[pixel];
	const unsigned int	color = *(unsigned int *)dst;
	t_rgb_vec			c;

	c.b = (double)(color & 0xFF) / 255;
	c.g = (double)((color >> 8) & 0xFF) / 255;
	c.r = (double)((color >> 16) & 0xFF) / 255;
	return (c);
}
