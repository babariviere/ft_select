/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briviere <briviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 16:56:42 by briviere          #+#    #+#             */
/*   Updated: 2017/12/21 16:34:39 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "select.h"

void	signal_handler(int sig)
{
	char	flag[2];

	if (sig == SIGINT || sig == SIGTSTP)
		ft_term_set_alt_scr(0);
	else if (sig == SIGCONT)
	{
		ft_term_set_alt_scr(1);
		signal(SIGTSTP, signal_handler);
	}
	if (sig == SIGINT)
		exit(1);
	if (sig == SIGTSTP)
	{
		flag[0] = 26;
		flag[1] = 0;
		signal(SIGTSTP, SIG_DFL);
		ioctl(0, TIOCSTI, &flag);
	}
}
