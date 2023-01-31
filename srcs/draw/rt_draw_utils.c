/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_draw_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyamagis <kyamagis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 14:24:48 by kyamagis          #+#    #+#             */
/*   Updated: 2023/01/18 11:40:07 by kyamagis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_draw.h"
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
