/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briviere <briviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 12:51:02 by briviere          #+#    #+#             */
/*   Updated: 2018/01/08 16:45:14 by briviere         ###   ########.fr       */
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


static int	check_fit(t_rect parent, t_rect child, size_t count)
{
	size_t	idx;

	idx = 0;
	while (idx < count)
	{
//		print_grid(child);
		//ft_term_putat(ft_itoa(child.x), (t_pos){child.x, child.y});
		//ft_term_putat(ft_itoa(child.y), (t_pos){child.x, child.y + 1});
		if (child.x < parent.x || child.y < parent.y
			|| (child.x + child.width) > (parent.x + parent.width)
			|| (child.y + child.height) > (parent.y + parent.height))
			return (0);
		child.y += child.height;
		if ((child.y + child.height) > (parent.y + parent.height))
		{
			child.y = 0;
			child.x += child.width;
		}
		idx++;
	}
	return (1);
}

t_rect		eval_needed_zone(t_choice *choices, size_t len,
		int col, int row)
{
	int		max;
	t_rect	parent;
	t_rect	child;
	float	prop;

	max = ft_strmax_choices(choices, len);
	parent = (t_rect){0, 0, col, row};
	child = (t_rect){0, 0, col, row};
	prop = col / row;
	while (!check_fit(parent, child, len))
	{
		if (ft_ceil((float)child.width / prop) >= (int)child.height)
			child.width /= 2;
		else if (ft_ceil((float)child.height * prop) >= (int)child.width)
			child.height /= 2;
		else
		{
			child.height /= 2;
			child.width /= 2;
		}
//		ft_term_clr();
	}
	while (check_fit(parent, child, len))
	{
		child.height++;
//		ft_term_clr();
	}
	child.height--;
	while (check_fit(parent, child, len))
	{
		child.width++;
//		ft_term_clr();
	}
	child.width--;
//	ft_term_clr();
	return (child);
}
