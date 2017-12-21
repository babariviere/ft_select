/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briviere <briviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 13:08:49 by briviere          #+#    #+#             */
/*   Updated: 2017/12/21 17:00:18 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "select.h"

void	print_choice(char *choice, t_rect zone)
{
	size_t	len;
	int		x;
	int		y;

	len = ft_strlen(choice);
	x = zone.x + ((zone.width - len) / 2);
	y = zone.y + (zone.height / 2);
	// TODO: check if len is too long
	ft_term_putat(choice, (t_pos){x, y});
}

void	print_choices(char **choices, int len, size_t selected, size_t choice)
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
	while (choices[idx])
	{
		if (selected == idx)
			ft_term_set_rv(1);
		if (choice == idx)
			ft_term_set_ul(1);
		print_choice(choices[idx], curr_zone);
		if (selected == idx)
			ft_term_set_rv(0);
		if (choice == idx)
			ft_term_set_rv(0);
		curr_zone.y += curr_zone.height;
		if (curr_zone.y >= row)
		{
			curr_zone.x += curr_zone.width;
			curr_zone.y = 0;
		}
		idx++;
	}
}

/*
 * UP: 65
 * DOWN: 66
 * RIGHT: 67
 * LEFT: 68
 */
int		main(int ac, char **av)
{
	char	*termtype;
	struct sigaction act;
	char	buf[2];
	int		selected;
	int		choice;

	(void)ac;
	(void)av;
	act.sa_handler = signal_handler;
	act.sa_flags = SA_RESTART;
	act.sa_mask = 0;
	if ((termtype = ft_term_type()) == 0)
		return (0);
	if (ft_term_init(termtype, 1) == 0)
		return (0);
	sigaction(SIGINT, &act, 0);
	sigaction(SIGCONT, &act, 0);
	sigaction(SIGTSTP, &act, 0);
	ft_term_set_alt_scr(1);
	ft_term_hidein();
	ft_term_clr();
	print_choices(av + 1, ac - 1, 0, 0);
	selected = 0;
	choice = 0;
	while (read(0, &buf, 1) > 0)
	{
		ft_term_clr();
		if (buf[0] == 65 && selected > 0)
			selected--;
		else if (buf[0] == 66 && selected < (ac - 2))
			selected++;
		if (buf[0] == 32 || buf[0] == 10)
			choice = selected;
		if (buf[0] == 10)
			break;
		print_choices(av + 1, ac - 1, selected, choice);
		ft_term_putat("choice: ", (t_pos){0, 0});
		ft_term_putat(ft_itoa(buf[0]), (t_pos){8, 0});
	}
	ft_term_clr();
	ft_term_set_alt_scr(0);
	ft_putendl(av[1 + choice]);
	return (0);
}
