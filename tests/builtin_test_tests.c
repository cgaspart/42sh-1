/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_test_tests.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/26 17:16:41 by sbrucker          #+#    #+#             */
/*   Updated: 2018/09/29 21:58:07 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

static char **env;

static	void exec(char *input)
{
	t_lexeme	*lex;
	t_ast		*ast_root;
	t_exec		*exe;

	log_set_quiet(1);
	lexer(input, &lex, NULL);
	ast_root = ast(lex);
	exe = create_exec((const char **)env);
	if (!ast_root)
		return ;
	exe = create_exec((const char **)env);
	exe = exec_cmd(ast_root, exe);
	ast_free(ast_root);
	free_lexemes(lex);
	free(exe);
}

static void test_framework(char *str_test, char *expected_stdout, char *test_name)
{
	int		backup_stdout_fd;
	int		backup_stderr_fd;
	char	*tmp;

	redirect_both_fds(&backup_stdout_fd, &backup_stderr_fd);
	exec(ft_strjoin(str_test, " && echo 0 || echo 1\n"));
	compare_fds_with_strings(test_name, (tmp = ft_strjoin(expected_stdout, "\n")), NULL, backup_stdout_fd, backup_stderr_fd);
	free(tmp);
}

void		builtin_test_tests(char **envp)
{
	env = envp;
	test_framework("[ -b /dev/disk0 ]", "0", "Block special file /dev/disk0");
	test_framework("[ -b /dev/disk0s1 ]", "0", "Block special file /dev/disk0s1");
	test_framework("[ -b /dev/null ]", "1", "Block special file /dev/null");
	test_framework("[ -c /dev/null ]", "0", "Character special file /dev/null");
	test_framework("[ -c /dev/zero ]", "0", "Character special file /dev/zero");
	test_framework("[ -c notafile ]", "1", "Character special file notafile");
	test_framework("[ -c . ]", "1", "Character special file .");
	test_framework("[ -d . ]", "0", "Directory .");
	test_framework("[ -d .. ]", "0", "Directory ..");
	test_framework("[ -d notafile ]", "1", "Directory notafile");
	test_framework("touch a; [ -e a ]", "0", "File a");
	test_framework("[ -e notafile ]", "1", "File notafile");
	test_framework("[ -e . ]", "0", "File .");
	test_framework("[ -e /dev/null ]", "0", "File /dev/null");
	test_framework("[ -f /dev/null ]", "1", "Regular file /dev/null");
	test_framework("[ -f /dev/disk0 ]", "1", "Regular file /dev/disk0");
	test_framework("[ -f a ]", "0", "Regular file a");
	test_framework("[ -f . ]", "1", "Regular file .");
	test_framework("[ -f notafile ]", "1", "Regular file notafile");
	test_framework("[ -k . ]", "1", "Sticky bit .");
	test_framework("[ -k a ]", "1", "Sticky bit a");
	test_framework("mkfifo b; [ -p b ]", "0", "Fifo b");
	test_framework("[ -p a ]", "1", "Fifo a");
	test_framework("[ -p . ]", "1", "Fifo .");
	test_framework("[ -p notafile ]", "1", "Fifo notafile");
	test_framework("chmod 000 a; [ -r a ]", "1", "Readable file a");
	test_framework("chmod 644 a; [ -r a ]", "0", "Readable file a");
	test_framework("[ -r notafile ]", "1", "Readable file notafile");
	test_framework("[ -r . ]", "0", "Readable file .");
	test_framework("[ -s . ]", "0", "File size greater than 0 .");
	test_framework("[ -s .. ]", "0", "File size greater than 0 ..");
	test_framework("[ -s a ]", "1", "File size greater than 0 a");
	test_framework("echo ABC > a;[ -s a ]", "0", "File size greater than 0 a");
	test_framework("[ -s b ]", "1", "File size greater than 0 b");
	test_framework("[ -s notafile ]", "1", "File size greater than 0 notafile");
	test_framework("[ -u . ]", "1", "User ID flag set .");
	test_framework("[ -u b ]", "1", "User ID flag set b");
	test_framework("[ -u notafile ]", "1", "User ID flag set notafile");
	test_framework("[ -w . ]", "0", "Writeable file .");
	test_framework("chmod 777 b; [ -w b ]", "0", "Writeable file b");
	test_framework("chmod 000 b; [ -w b ]", "1", "Writeable file b");
	test_framework("chmod 777 b; [ -x b ]", "0", "Executable file b");
	test_framework("chmod 000 b; [ -x b ]", "1", "Executable file b");
	test_framework("chmod 644 b; rm -rf b; ln -s . c; [ -L c ]", "1", "Symbolic link c");
	test_framework("[ -L a ]", "1", "Symbolic link a");
	test_framework("[ -L notafile ]", "1", "Symbolic link notafile");
	test_framework("[ -S notafile ]", "1", "Socket notafile");
	test_framework("[ -S a ]", "1", "Socket a");
	test_framework("rm a c;[ -S . ]", "1", "Socket .");
}