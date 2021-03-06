/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refresh_colosyn.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/17 15:36:29 by cyfermie          #+#    #+#             */
/*   Updated: 2018/11/30 14:11:46 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

/*
**	The command line is checked in order to reprint it with the good colors.
*/

void		refresh_colosyn(struct s_line *le, char *cmd)
{
	t_lexeme	*lexemes;
	char		*unmatched_quote_err_ptr;

	log_set_quiet(1);
	lexer(cmd, &lexemes, &unmatched_quote_err_ptr);
	actionk_delete_current_input(le);
	print_colorized_input(cmd, lexemes, unmatched_quote_err_ptr);
	free_lexemes(lexemes);
	if (VERBOSE_MODE || is_option_activated("v", g_sh_opts, NULL))
		log_set_quiet(0);
}
