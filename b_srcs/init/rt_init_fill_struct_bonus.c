/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_init_fill_struct.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 13:07:15 by nfukuma           #+#    #+#             */
/*   Updated: 2023/01/24 10:39:50 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "rt_define.h"
#include "rt_init_utils.h"
#include "rt_put_error.h"
#include "rt_structs.h"

void	rt_fill_struct_a(t_rt_data *rt, const char **tokens);
void	rt_fill_struct_c(t_rt_data *rt, const char **tokens);
void	rt_fill_struct_l(t_rt_data *rt, const char **tokens);
void	rt_fill_struct_sp(t_rt_data *rt, const char **tokens);
void	rt_fill_struct_pl(t_rt_data *rt, const char **tokens);
void	rt_fill_struct_cy(t_rt_data *rt, const char **tokens);
void	rt_fill_struct_cn(t_rt_data *rt, const char **tokens);
int		rt_check_id(const char *str);

enum e_funcs {
	e_A,
	e_C,
	e_L,
	e_sp,
	e_pl,
	e_cy,
	e_cn,
};

void	rt_fill_struct(t_rt_data *rt, const char *line)
{
	int				id;
	char			**tokens;

	tokens = ft_split(line, ' ');
	if (tokens == NULL)
		rt_perror_exit(NULL);
	id = rt_check_id(tokens[0]);
	if (id < 0)
		rt_put_rt_file_format_error_exit("Contains invalid identifier");
	else if (id == e_A)
		rt_fill_struct_a(rt, (const char **)tokens);
	else if (id == e_C)
		rt_fill_struct_c(rt, (const char **)tokens);
	else if (id == e_L)
		rt_fill_struct_l(rt, (const char **)tokens);
	else if (id == e_sp)
		rt_fill_struct_sp(rt, (const char **)tokens);
	else if (id == e_pl)
		rt_fill_struct_pl(rt, (const char **)tokens);
	else if (id == e_cy)
		rt_fill_struct_cy(rt, (const char **)tokens);
	else
		rt_fill_struct_cn(rt, (const char **)tokens);
	rt_double_ptr_free((const char **)tokens);
}

int	rt_check_id(const char *str)
{
	int			id;
	const char	*id_set[] = {"A", "C", "L", "sp", "pl", "cy", "cn"};

	id = 0;
	while (id < 7)
	{
		if (!ft_strcmp(str, id_set[id]))
			break ;
		++id;
	}
	if (id == 7)
	{
		return (-1);
	}
	return (id);
}
