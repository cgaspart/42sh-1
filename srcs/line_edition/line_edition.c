/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_edition.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/25 16:29:25 by cyfermie          #+#    #+#             */
/*   Updated: 2018/06/25 20:26:02 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h> // debug
FILE *tty_debug = NULL; // debug
#define FOOLOL // debug

#include "../../includes/line_edition.h"
#undef FOOLOL // debug

static void		read_key(char key[LE_KEY_SIZE])
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

static t_kno	get_key_number(const char *key)
{
	t_kno	key_no;
	t_kno	i;

	key_no = 0;
	i = 0;
	while (i < LE_KEY_SIZE)
	{
		key_no += ((t_kno)key[i]) << i;
		++i;
	}
	return (key_no);
}

char			*line_edition(void)
{
	char			*final_line;
	char			key[LE_KEY_SIZE];
	struct s_line	le;
	t_kno			key_no;

	set_term_attr(SET_NEW);
	init_line_edition_attributes(&le);

	while ("INFINITY")
	{
		ft_memset(key, '\0', LE_KEY_SIZE);
		read_key(key);
		key_no = get_key_number(key);

		fprintf(tty_debug, "key = %" PRIu64 "\n" , key_no); // debug

		if (key_no == '\n')
		{
			set_term_attr(SET_OLD);
			break ;
			// need more things to do in the future when line is finished
		} 

		process_key(key_no, &le);

	}

	if ((final_line = ft_strdup(le.line)) == NULL)
		le_exit("Memory allocation failed\n", "malloc");
	return (final_line);
}


////////////////////////////////////////////////////////////// for tests
void	prompt(void)
{
	printf("JJANIEC $> ");
	fflush(stdout);
}

void	prepare_test(void)
{
	tty_debug = fopen(TTY_DEBUG, "w");
	if (tty_debug == NULL)
	{
		perror("perror report - fopen() failed in prepare_test()");
		exit(123);
	}
}

int	 main(void)
{
	prepare_test();
	prompt();
	free( line_edition() );

	return 0;
}
