/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_init_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 13:25:32 by nfukuma           #+#    #+#             */
/*   Updated: 2023/01/17 15:53:42 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_strucs.h"
#include "rt_init_utils.h"
#include "rt_vector.h"
#include "libft.h"
#include "rt_put_error.h"
#include <stdlib.h>

#include <stdio.h>

void	rt_double_ptr_free(const char **d_ptr)
{
	size_t	i;

	i = 0;
	while (d_ptr[i])
	{
		free((void *)d_ptr[i]);
		d_ptr[i] = NULL;
	}
	free((void *)d_ptr);
	d_ptr = NULL;
}

int	rt_count_str(const char **strs)
{
	int	i;

	if (strs == NULL)
		return (-1);
	i = 0;
	while (strs[i])
		++i;
	return (i);
}

void	rt_addback_objs_list(t_obj **begin, t_obj *new)
{
	t_obj	*tmp;

	if (*begin == NULL)
	{
		*begin = new;
		return ;
	}
	tmp = *begin;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void	rt_addback_lite_list(t_point_lite_source **begin,
							t_point_lite_source *new)
{
	t_point_lite_source	*tmp;

	if (*begin == NULL)
	{
		*begin = new;
		return ;
	}
	tmp = *begin;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}
