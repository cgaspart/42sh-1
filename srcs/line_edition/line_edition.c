/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_edition.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/22 15:43:27 by cyfermie          #+#    #+#             */
/*   Updated: 2018/06/22 20:27:02 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h> // debug
FILE *tty_debug = NULL; // debug
#define FOOLOL // debug

#include "../../includes/line_edition.h"
#undef FOOLOL // debug

void	read_key(char key[LE_KEY_SIZE])
{
	ssize_t read_ret;

	read_ret = read(STDIN_FILENO, key, LE_KEY_SIZE - 1);
	if (read_ret == -1)
	{
		write(STDERR_FILENO, "\nError while reading on stdin\n", 30);
		perror("read() - perror() report");
	}

	// if (read_ret == 0) ?  ctrl + d causes EOF ? think about that later ... 
}

void	line_edition(void)
{
	char    final_line[LE_LINE_SIZE];
	char    key[LE_KEY_SIZE];

	ft_memset(final_line, '\0', LE_LINE_SIZE);
	set_term_attr(SET_NEW);

	while ("INFINITY")
	{
		ft_memset(key, '\0', LE_KEY_SIZE);
		read_key(key);

		if (*key == 'q') le_exit("\nquit\n", __func__); // tmp debug

		fprintf(tty_debug, "test\n");
	}
}


////////////////////////////////////////////////////////////// for tests
void    prompt(void)
{
	printf("JJANIEC $> ");
	fflush(stdout);
}

void    prepare_test(void)
{
	tty_debug = fopen(TTY_DEBUG, "w");
	if (tty_debug == NULL)
	{
		perror("perror report - fopen() failed in prepare_test()");
		exit(123);
	}
}

int     main(void)
{
	prepare_test();
	prompt();
	line_edition();

	return 0;
}
