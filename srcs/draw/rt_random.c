/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_randam.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 12:25:35 by nfukuma           #+#    #+#             */
/*   Updated: 2023/01/23 13:20:03 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <stdio.h>

#define DECIMAL_DIGIT 7
#define PERIOD 10
#define CONST_NUM 5
#define ELEMENT 21000

int	rt_sum_int_sequence(int sequence[], int element_idx)
{
	int		int_sum;
	size_t	i;

	int_sum = 0;
	i = 0;
	while (i < DECIMAL_DIGIT)
	{
		int_sum += sequence[element_idx - i];
		if (i + 1 < DECIMAL_DIGIT)
			int_sum = int_sum << 1;
		i++;
	}
	return (int_sum);
}

void	rt_sequence_constructor(int seed, int sequence[])
{
	int		num;
	size_t	i;

	num = seed;
	i = 0;
	while (i < PERIOD)
	{
		sequence[i] = num % 2;
		num /= 2;
		++i;
	}
}

int	calculate_recurrence_formula(int seed, int sequence[], size_t i)
{
	size_t	digit_times_seed;

	digit_times_seed = seed * DECIMAL_DIGIT;
	while (i < digit_times_seed)
	{
		sequence[i] = sequence[i - CONST_NUM] + sequence[i - PERIOD];
		sequence[i] %= 2;
		i++;
	}
	if (seed < 1)
	{
		return (rt_sum_int_sequence(sequence, DECIMAL_DIGIT - 1));
	}
	return (rt_sum_int_sequence(sequence, digit_times_seed - 1));
}

int	rt_random_m_sequence(int seed)
{
	int	sequence[ELEMENT];

	rt_sequence_constructor(seed, sequence);
	seed %= (ELEMENT / DECIMAL_DIGIT);
	return (calculate_recurrence_formula(seed, sequence, PERIOD));
}

double	return_random_ratio(int seed, int bottom)
{
	int	random_num;

	random_num = rt_random_m_sequence(seed);
	if (random_num < bottom)
	{
		random_num = bottom;
	}
	return ((double)random_num / (1 << DECIMAL_DIGIT));
}
