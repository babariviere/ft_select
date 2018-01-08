/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briviere <briviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 16:56:42 by briviere          #+#    #+#             */
/*   Updated: 2018/01/08 13:49:24 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "select.h"

void	signal_handler(int sig)
{
	char	flag[2];

	flag[1] = 0;
	if (sig == SIGINT || sig == SIGTSTP)
		ft_term_stop();
	else if (sig == SIGCONT)
	{
		ft_term_start(0, 1);
		signal(SIGTSTP, signal_handler);
		flag[0] = 0;
		ioctl(0, TIOCSTI, &flag);
	}
	if (sig == SIGINT)
		exit(1);
	if (sig == SIGTSTP)
	{
		flag[0] = 26;
		signal(SIGTSTP, SIG_DFL);
		ioctl(0, TIOCSTI, &flag);
	}
}

void	signal_resize(int sig)
{
	char	flag[2];

	flag[0] = 0;
	flag[1] = 0;
	ft_term_resize(sig);
	ioctl(0, TIOCSTI, &flag);
}
