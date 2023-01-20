/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_init_fill_struct.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 13:07:15 by nfukuma           #+#    #+#             */
/*   Updated: 2023/01/20 13:59:57 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "rt_define.h"
#include "rt_put_error.h"
#include "rt_structs.h"
#include "rt_init_utils.h"

void	rt_fill_struct_A(t_rt_data *rt, const char **tokens);
void	rt_fill_struct_C(t_rt_data *rt, const char **tokens);
void	rt_fill_struct_L(t_rt_data *rt, const char **tokens);
void	rt_fill_struct_sp(t_rt_data *rt, const char **tokens);
void	rt_fill_struct_pl(t_rt_data *rt, const char **tokens);
void	rt_fill_struct_cy(t_rt_data *rt, const char **tokens);
void	rt_fill_struct_cn(t_rt_data *rt, const char **tokens);
int		rt_check_id(const char *str);

void	rt_fill_struct(t_rt_data *rt, const char *line)
{
	int		id;
	char	**tokens;
	void (*const fill_funcs[])(t_rt_data * rt,
			const char **tokens) = {rt_fill_struct_A,
			rt_fill_struct_C, rt_fill_struct_L,
			rt_fill_struct_sp, rt_fill_struct_pl,
			rt_fill_struct_cy, rt_fill_struct_cn};

	tokens = ft_split(line, ' ');
	if (tokens == NULL)
		rt_perror_exit(NULL);
	id = rt_check_id(tokens[0]);
	if (id < 0)
		rt_put_rt_file_format_error_exit("Contains invalid identifier");
	fill_funcs[id](rt, (const char **)tokens);
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
		return (-1);
	return (id);
}
