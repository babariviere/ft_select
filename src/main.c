/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briviere <briviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 13:08:49 by briviere          #+#    #+#             */
/*   Updated: 2018/01/08 17:14:24 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "select.h"

//static void	print_grid(t_rect c)
//{
//	int		idx;
//
//	idx = 1;
//	ft_term_putwat("\u250c", (t_pos){c.x, c.y});
//	ft_term_putwat("\u2514", (t_pos){c.x, c.y + c.height - 1});
//	ft_term_putwat("\u2510", (t_pos){c.x + c.width - 1, c.y});
//	ft_term_putwat("\u2518", (t_pos){c.x + c.width - 1, c.y + c.height - 1});
//	while (idx < ((int)c.width - 1))
//	{
//		ft_term_putwat("\u2500", (t_pos){c.x + idx, c.y});
//		ft_term_putwat("\u2500", (t_pos){c.x + idx, c.y + c.height - 1});
//		idx++;
//	}
//	idx = 1;
//	while (idx < ((int)c.height - 1))
//	{
//		ft_term_putwat("\u2502", (t_pos){c.x, c.y + idx});
//		ft_term_putwat("\u2502", (t_pos){c.x + c.width - 1, c.y + idx});
//		idx++;
//	}
//}

void	print_choice(char *choice, t_rect zone)
{
	char	tmp[zone.width + 1];
	int		len;
	int		x;
	int		y;

	len = ft_strlen(choice);
	x = zone.x + ((zone.width - len) / 2);
	y = zone.y + (zone.height / 2);
	if ((size_t)len > zone.width)
	{
		x = zone.x;
		y = zone.y;
		while (len > ((int)zone.width) && y < (zone.y + (int)zone.height))
		{
			ft_strncpy(tmp, choice, zone.width);
			tmp[zone.width] = 0;
			ft_term_putwat(tmp, (t_pos){x, y});
			choice += zone.width;
			y++;
			len -= zone.width;
		}
	}
	else
		ft_term_putwat(choice, (t_pos){x, y});
}

void	print_choices(t_choice *choices, size_t selected, size_t len, t_rect curr_zone)
{
	size_t	idx;
	int		col;
	int		row;

	col = ft_term_col();
	row = ft_term_row();
	idx = 0;
	while (idx < len)
	{
		//print_grid(curr_zone);
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
		if ((curr_zone.y + (int)curr_zone.height) > row)
		{
			curr_zone.x += curr_zone.width;
			curr_zone.y = 0;
		}
		idx++;
	}
}

void	print_choices_smart(t_choice *choices, size_t select, size_t len)
{
	static int		col;
	static int		row;
	static t_rect	zone;

	if (col != ft_term_col() || row != ft_term_row())
	{
		col = ft_term_col();
		row = ft_term_row();
		zone = eval_needed_zone(choices, len, col, row);
	}
	print_choices(choices, select, len, zone);
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

void	main_loop(t_choice *choices, size_t len)
{
	unsigned char	buf[4];
	size_t	selected;

	selected = 0;
	while (read(0, &buf, 4) > 0)
	{
		if (len == 0)
		{
			ft_term_stop();
			exit (0);
		}
		if (buf[2] == 65 && selected > 0)
			selected--;
		else if (buf[2] == 66 && selected < (len - 1))
			selected++;
		else if (buf[2] == 65)
			selected = len - 1;
		else if (buf[2] == 66)
			selected = 0;
		else if (buf[0] == 32)
			choices[selected].selected = !choices[selected].selected;
		else if (buf[0] == 10)
			break ;
		else if ((buf[0] == 126 || buf[0] == 127) && len > 0)
			ft_memcpy(choices + selected, choices + selected + 1, len-- - selected);
		else if (buf[0] == 27 && buf[1] == 0)
		{
			ft_term_stop();
			exit(0);
		}
		ft_term_clr();
		print_choices_smart(choices, selected, len);
		ft_bzero(buf, 4);
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
	t_choice	choices[ac];
	size_t		len;

	(void)ac;
	(void)av;
	if ((termtype = ft_term_type()) == 0)
		return (0);
	if (ft_term_init(termtype, 1) == 0)
		return (0);
	signal(SIGINT, signal_handler);
	signal(SIGCONT, signal_handler);
	signal(SIGTSTP, signal_handler);
	signal(SIGWINCH, signal_resize);
	ft_term_start(0, 1);
	build_choices(choices, av + 1);
	len = ac - 1;
	print_choices_smart(choices, 0, len);
	main_loop(choices, len);
	ft_term_stop();
	print_results(choices, len);
	return (0);
}
