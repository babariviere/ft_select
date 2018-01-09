/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briviere <briviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 12:51:02 by briviere          #+#    #+#             */
/*   Updated: 2018/01/09 10:07:02 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "select.h"

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

static void	eval_needed_zone_sub(t_rect parent, t_rect *child, size_t len)
{

	while (check_fit(parent, *child, len))
		child->height++;
	child->height--;
	while (check_fit(parent, *child, len))
		child->width++;
	child->width--;
}

t_rect		eval_needed_zone(size_t len)
{
	t_rect	parent;
	t_rect	child;
	float	prop;

	parent = (t_rect){0, 0, ft_term_col(), ft_term_row()};
	prop = parent.width / parent.height;
	child = (t_rect){0, 0, parent.width, parent.height};
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
	}
	eval_needed_zone_sub(parent, &child, len);
	return (child);
}
