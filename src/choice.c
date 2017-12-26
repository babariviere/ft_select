/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   choice.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briviere <briviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/26 14:11:43 by briviere          #+#    #+#             */
/*   Updated: 2017/12/26 14:47:02 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "select.h"

void	build_choices(t_choice *choices, char **select)
{
	size_t		idx;

	if (select == 0 || *select == 0)
		return ;
	idx = 0;
	while (select[idx])
	{
		choices[idx].choice = select[idx];
		choices[idx].selected = 0;
		idx++;
	}
	choices[idx].choice = 0;
}
