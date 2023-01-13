/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 11:00:21 by nfukuma           #+#    #+#             */
/*   Updated: 2022/11/17 12:38:51 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	const unsigned char	*a;
	const unsigned char	*b;
	size_t				i;

	a = (const unsigned char *)s1;
	b = (const unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if ((a[i] == '\0' && b[i] == '\0'))
			break ;
		if (a[i] != b[i])
			return ((unsigned char)a[i] - (unsigned char)b[i]);
		i++;
	}
	return (0);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (1)
	{
		if ((s1[i] - s2[i]) != 0)
		{
			return (s1[i] - s2[i]);
		}
		if (!(s1[i]) && !(s2[i]))
			break ;
		i++;
	}
	return (0);
}
