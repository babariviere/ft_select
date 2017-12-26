/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briviere <briviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 13:08:49 by briviere          #+#    #+#             */
/*   Updated: 2017/12/26 17:02:21 by briviere         ###   ########.fr       */
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

void	print_choices(t_choice *choices, size_t selected, size_t len)
{
	int		max_col;
	size_t	idx;
	int		col;
	int		row;
	t_rect	curr_zone;

	col = ft_term_col();
	row = ft_term_row();
	max_col = eval_needed_col(choices, len, col, row);
	curr_zone = (t_rect){0, 0, ft_ceil((float)col / (float)max_col), ft_ceil((float)row / (float)(len + max_col))};
	idx = 0;
	while (idx < len)
	{
		if (selected == idx)
			ft_term_set_rv(1);
		if (choices[idx].selected)
			ft_term_set_ul(1);
		print_choice(choices[idx].choice, curr_zone);
		if (selected == idx)
			ft_term_set_rv(0);
		if (choices[idx].selected)
			ft_term_set_ul(0);
		curr_zone.y += curr_zone.height;
		if (curr_zone.y >= row)
		{
			curr_zone.x += curr_zone.width;
			curr_zone.y = 0;
		}
		idx++;
	}
}

void	print_results(t_choice *choices, size_t len)
{
	size_t	idx;
	int		printed;

	printed = 0;
	idx = 0;
	while (idx < len)
	{
		if (choices[idx].selected)
		{
			if (printed)
				ft_putchar(' ');
			ft_putstr(choices[idx].choice);
			printed = 1;
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
	char	buf[3];
	t_choice	choices[ac];
	size_t		len;
	size_t	selected;
	size_t	idx;

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
	if (isatty(1) == 1)
		ft_term_set_alt_scr(1);
	ft_term_hidein();
	ft_term_clr();
	ft_term_set_cur_vis(0);
	build_choices(choices, av + 1);
	len = ac - 1;
	print_choices(choices, 0, len);
	selected = 0;
	idx = 0;
	while (read(0, &buf, 3) > 0)
	{
		ft_term_clr();
		ft_term_putat("key:", (t_pos){0, 0});
		ft_term_putat(ft_itoa(buf[0]), (t_pos){5, 0});
		ft_term_putat(ft_itoa(buf[1]), (t_pos){5 + 4, 0});
		ft_term_putat(ft_itoa(buf[2]), (t_pos){5 + 8, 0});
		if (len == 0)
		{
			ft_term_clr();
			ft_term_set_alt_scr(0);
			return (0);
		}
		if (buf[2] == 65 && selected > 0)
			selected--;
		if (buf[2] == 66 && selected < (len - 1))
			selected++;
		if (buf[0] == 32)
			choices[selected].selected = !choices[selected].selected;
		if (buf[0] == 10)
			break ;
		if ((buf[0] == 126 || buf[0] == 127) && len > 0)
			ft_memcpy(choices + selected, choices + selected + 1, len-- - selected);
		if (buf[0] == 27 && buf[1] == 0)
		{
			ft_term_set_cur_vis(1);
			ft_term_clr();
			ft_term_set_alt_scr(0);
			return (0);
		}
		print_choices(choices, selected, len);
		ft_bzero(buf, 3);
	}
	ft_term_set_cur_vis(1);
	ft_term_clr();
	if (isatty(1) == 1)
		ft_term_set_alt_scr(0);
	print_results(choices, len);
	return (0);
}
