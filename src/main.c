/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briviere <briviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 13:08:49 by briviere          #+#    #+#             */
/*   Updated: 2017/12/19 16:56:20 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "select.h"

void	print_choice(char *choice, t_rect zone, char **termbuf)
{
	size_t	len;
	int		x;
	int		y;

	len = ft_strlen(choice);
	x = zone.x + ((zone.width - len) / 2);
	y = zone.y + (zone.height / 2);
	// TODO: check if len is too long
	ft_term_cur_mv(termbuf, x, y);
	tputs(choice, 0, ft_fputchar);
}

void	print_choices(char **choices, int len, char **termbuf)
{
	int		max_col;
	size_t	idx;
	int		col;
	int		row;
	t_rect	curr_zone;

	col = ft_term_col();
	row = ft_term_row();
	max_col = eval_needed_col(choices, col, row);
	curr_zone = (t_rect){0, 0, ft_ceil((float)col / (float)max_col), ft_ceil((float)row / (float)(len + max_col))};
	idx = 0;
	ft_term_mr(termbuf);
	//ft_term_us(termbuf);
	while (choices[idx])
	{
		print_choice(choices[idx], curr_zone, termbuf);
		curr_zone.y += curr_zone.height;
		if (curr_zone.y >= row)
		{
			curr_zone.x += curr_zone.width;
			curr_zone.y = 0;
		}
		idx++;
	}
	//ft_term_ue(termbuf);
	ft_term_me(termbuf);
}

int		main(int ac, char **av)
{
	char	*termtype;
	char	*termbuf;

	(void)ac;
	(void)av;
	if ((termtype = ft_term_type()) == 0)
		return (0);
	if ((termbuf = ft_term_init(termtype)) == 0)
		return (0);
	ft_term_ti(&termbuf);
	ft_term_hidein();
	ft_term_clr(&termbuf);
	print_choices(av + 1, ac - 1, &termbuf);
	while (1);
	ft_term_te(&termbuf);
	return (0);
}
