/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briviere <briviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 12:51:02 by briviere          #+#    #+#             */
/*   Updated: 2017/12/26 14:46:40 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "select.h"

static size_t	ft_strmax_choices(t_choice *choices, size_t len)
{
	size_t	idx;
	size_t	longest;
	size_t	res;

	idx = 0;
	longest = 0;
	while (idx < len)
	{
		if (choices[idx].choice)
			res = ft_strlen(choices[idx].choice);
		else
			break ;
		if (res > longest)
			longest = res;
		idx++;
	}
	return (longest);
}

int				eval_needed_col(t_choice *choices, size_t len,
		int col, int row)
{
	int		max;
	int		res;

	max = ft_strmax_choices(choices, len);
	res = 1;
	while (((int)len / res) > row || (max / res) > col)
		res++;
	return (res);
}
