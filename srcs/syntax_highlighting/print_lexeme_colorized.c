/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_lexeme_colorized.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/25 07:13:38 by jjaniec           #+#    #+#             */
/*   Updated: 2018/12/06 20:30:13 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

extern t_option		g_sh_opts[];

/*
** Returns 1 if file in lexeme_data was found by searching directories in
** $PATH or if path in lexeme_data exists,
** and store stat of file in elem_stats,
** otherwise return 0
*/

static int		elem_path_found(struct stat *elem_stats, \
					char *lexeme_data, t_environ *env, int item_nb)
{
	t_shell_vars	*vars;
	char			*tmp;

	(void)env;
	if (ft_strchr(lexeme_data, '/') || item_nb > 0)
	{
		if (lstat(lexeme_data, elem_stats) != -1)
			return (1);
		return (0);
	}
	else if (is_builtin(lexeme_data, NULL))
		return (1);
	else
	{
		ht_update(env);
		vars = get_shell_vars();
		if ((tmp = ht_get_key_value(vars->hashtable, lexeme_data)))
		{
			lstat(tmp, elem_stats);
			return (1);
		}
	}
	return (0);
}

/*
** Print color associated w/ stats of program argument
** (directory / file / not found)
*/

static void		print_prog_name_arg_col(struct stat *elem_stats, \
					int elem_found, int item_nb)
{
	if (elem_found)
	{
		if (item_nb == 0)
			ft_putstr(COL_PROG_NAME_FOUND);
		else
		{
			if (elem_stats != NULL && S_ISDIR(elem_stats->st_mode))
				ft_putstr(COL_PROG_ARG_DIR);
			else
				ft_putstr(COL_PROG_ARG_FILE);
		}
	}
	else
	{
		if (item_nb == 0)
			ft_putstr(COL_PROG_NAME_NOT_FOUND);
		else
			ft_putstr(COL_PROG_ARG_NOT_FOUND);
	}
}

static void		put_lexeme_word_color(t_lexeme *lexeme, char *lexeme_begin, \
					t_environ *env, int item_nb)
{
	struct stat		elem_stats;

	if (*(char *)(lexeme->data) == '-')
		ft_putstr(COL_PROG_OPT);
	else if (*(lexeme_begin) == '$')
		ft_putstr(COL_ENV_VAR_EXPANSION);
	else if (*(lexeme_begin) == '\'' || *(lexeme_begin) == '"')
		ft_putstr(COL_QUOTED_ARG);
	else if (script_colodyn(lexeme, &item_nb))
		ft_putstr(COL_SCRIPT);
	else if (ft_strequ(lexeme->data, "[") || ft_strequ(lexeme->data, "]") \
	|| ft_strequ(lexeme->data, "!"))
		print_prog_name_arg_col(NULL, 1, item_nb);
	else
		print_prog_name_arg_col(&elem_stats, \
		elem_path_found(&elem_stats, lexeme->data, env, item_nb), item_nb);
}

/*
** Prints color associated w/ type of current element
*/

static void		put_lexeme_color(t_lexeme *lexeme, char *lexeme_begin, \
					t_environ *env)
{
	static int		item_nb = -1;

	item_nb++;
	if (is_an_alias(lexeme->data, access_alias_datas()))
		ft_putstr(COL_ALIAS);
	else if (lexeme->type == T_CTRL_OPT)
	{
		ft_putstr(COL_OPERATORS);
		item_nb = -1;
	}
	else if (lexeme->type == T_REDIR_OPT)
		ft_putstr(COL_REDIRS);
	else if (lexeme->type == T_WORD)
	{
		if (ft_strequ(lexeme->data, "!") && lexeme->next && \
		lexeme->next->type == T_WORD && item_nb == 0)
			item_nb--;
		put_lexeme_word_color(lexeme, lexeme_begin, env, item_nb);
	}
	if (!lexeme->next)
		item_nb = -1;
}

/*
** Print color associated w/ current lexeme w/ put_lexeme_color()
** and reset colors to COL_DEFAULT
*/

void			print_lexeme_colorized(char *lexeme_begin, char *lexeme_end, \
					char *input_ptr, t_lexeme *lexeme)
{
	t_environ	*env;

	env = get_shell_vars()->env;
	put_lexeme_color(lexeme, lexeme_begin, env);
	if (is_option_activated("c", g_sh_opts, NULL))
		write(1, input_ptr, (lexeme_end - input_ptr));
	else
		print_to_line_edition(input_ptr, (lexeme_end - input_ptr));
	ft_putstr(COL_DEFAULT);
}
