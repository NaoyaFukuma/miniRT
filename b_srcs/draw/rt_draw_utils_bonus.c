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
#include "libft.h"
#include <stdio.h>

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

int	rt_put_ten(int n)
{
	ssize_t	digcount;

	digcount = 0;
	if (-10 < n && n < 0)
		digcount += write(1, "-", 1);
	if (n <= -10 || 10 <= n)
		digcount += rt_put_ten(n / 10);
	n = n % 10;
	if (n < 0)
		n *= -1;
	return (digcount += write(1, &"0123456789"[n], 1));
}

void	rt_indicator(int height, int y)
{
	ft_putstr_fd("\rtime ", 1);
	rt_put_ten(height - y);
}
