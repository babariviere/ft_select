/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briviere <briviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 13:09:11 by briviere          #+#    #+#             */
/*   Updated: 2017/12/21 13:29:41 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SELECT_H
# define SELECT_H

# include "libft.h"
# include <signal.h>
# include <stdio.h>
# include <sys/ioctl.h>

int		eval_needed_col(char **choices, int col, int row);
void	signal_handler(int sig);

#endif
