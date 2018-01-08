/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briviere <briviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 13:09:11 by briviere          #+#    #+#             */
/*   Updated: 2018/01/08 13:48:45 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SELECT_H
# define SELECT_H

# include "libft.h"
# include <signal.h>
# include <stdio.h>
# include <sys/ioctl.h>

typedef struct	s_choice {
	char			*choice;
	int				selected;
}				t_choice;

void			build_choices(t_choice *choices, char **select);

t_rect			eval_needed_zone(t_choice *choices, size_t len,
		int col, int row);
void			signal_handler(int sig);
void			signal_resize(int sig);

#endif
