/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_highlighting.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/22 17:39:24 by jjaniec           #+#    #+#             */
/*   Updated: 2018/08/27 19:22:43 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SYNTAX_HIGHLIGHTING_H
# define SYNTAX_HIGHLIGHTING_H

# include <twenty_one_sh.h>

/*
** 8/16 colors sequences,
** supported by most terminals
*/

# define COL_DEFAULT "\e[0;39m"

# define COL_PROG_NAME_NOT_FOUND "\e[1;31m"
# define COL_PROG_NAME_FOUND "\e[1;32m"

# define COL_PROG_OPT "\e[0;36m"

# define COL_PROG_ARG_NOT_FOUND "\e[0;49;31m"
# define COL_PROG_ARG_FILE "\e[2;49;32m"
# define COL_PROG_ARG_DIR "\e[2;49;33m"

# define COL_QUOTED_ARG "\e[0;33m"

# define COL_OPERATORS "\e[0;96m" // 97

# define COL_REDIRS	"\e[2;49;39m"

# define COL_ENV_VAR_EXPANSION "\e[2;49;39m"

void			print_lexeme_colorized(char *lexeme_begin, char *lexeme_end, char *input_ptr, t_lexeme *lexeme, char **envp);

void			print_colorized_input(char *input_str, char **env, t_lexeme *lexemes);

int				elem_path_found(struct stat *elem_stats, char *lexeme_data, char **env, int item_nb);

#endif