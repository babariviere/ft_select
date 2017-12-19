/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briviere <briviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 12:51:02 by briviere          #+#    #+#             */
/*   Updated: 2017/12/19 13:08:19 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "select.h"

int		eval_needed_col(char **choices, int col, int row)
{
	int		max;
	int		num;
	int		res;

	num = ft_tablen(choices, sizeof(char *));
	max = ft_strmax(choices);
	res = 1;
	while ((num / res) > row || (max / res) > col)
		res++;
	return (res);
}
