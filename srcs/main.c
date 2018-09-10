/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 16:19:06 by jjaniec           #+#    #+#             */
/*   Updated: 2018/09/10 22:34:57 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

static t_exec		*loop_body(char *input, char **envp)
{
	t_lexeme	*lex;
	t_ast		*ast_root;
	t_exec		*exe;

	errno = 0;
	if (!VERBOSE_MODE)
		log_set_quiet(1);
	lex = lexer(input);
	//print_colorized_input(input, envp, lex);
	ast_root = ast(lex);
	exe = create_exec((const char **)envp);
	if (!ast_root)
	{
		free_lexemes(lex);
		return (exe);
	}
	exe = create_exec((const char **)envp);
	exe = exec_cmd(ast_root, exe);
	ast_free(ast_root);
	free_lexemes(lex);
	return (exe);
}

static void 	twentyonesh(char **envp)
{
	char		*input;
	t_exec		*exe;

	tty_debug = fopen(TTY_DEBUG, "w");
	while (1)
	{
		ft_putstr("%> ");
		input = line_edition();
		ft_putchar('\n');
		exe = loop_body(input, envp);
		if (exe && exe->tmp_envp)
			envp = exe->tmp_envp;
		else if (exe)
			envp = exe->envp;
		else
			exit(1);
		free_exec(&exe);
		free(input);
	}
}

int				main(int ac, char **av, char **envp)
{
	t_option	*twenty_one_sh_opts;

	twenty_one_sh_opts = malloc(sizeof(t_option) * SH_OPT_COUNT + 1);
	init_option_list(&twenty_one_sh_opts, SH_OPT_LIST);
/*	while (twenty_one_sh_opts && twenty_one_sh_opts->opt_name)
	{
		printf("1st opt desc: %s\n", twenty_one_sh_opts[0].opt_desc);
		twenty_one_sh_opts = twenty_one_sh_opts + 1;
	}*/
	parse_options(ac, av, twenty_one_sh_opts);
	if (!VERBOSE_MODE)
		log_set_quiet(1);
	if (ac > 1)
		loop_body(ft_strjoin(av[1], "\n"), cp_envp((const char **)envp));
	else
		twentyonesh(cp_envp((const char **)envp));
	return (0);
}
