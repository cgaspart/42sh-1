/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/20 12:34:09 by cyfermie          #+#    #+#             */
/*   Updated: 2018/10/22 20:55:25 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

#include <forty_two_sh.h>
#include <signal.h>

# ifndef SIGINFO
#  define SIGINFO 0
# endif

# ifndef SIGEMT
#  define SIGEMT 0
# endif

struct s_cmd_status
{
	bool			cmd_running;
	pid_t			cmd_pid;
	struct s_line	*keep_le_main_datas;
	bool			resize_happened;
	bool			sigint_happened;
};  

extern struct s_cmd_status  g_cmd_status;

void    init_signals(void);
void	handle_sigint(int sig);
void	handle_sigwinch(int sig);
void	handle_useless_signals(int sig);
void		handle_sigchild(int sig);

#endif
