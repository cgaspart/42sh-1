/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_str_on_term.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfermier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/10 21:18:37 by cfermier          #+#    #+#             */
/*   Updated: 2018/08/10 21:18:37 by cfermier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/line_edition.h"

unsigned int	print_str_on_term(const char *str,
								  unsigned int tmp_current_cursor_pos,
								  struct s_line *le, int foo)
{
    while (*str != '\0')
    {
        ++tmp_current_cursor_pos;
        if (tmp_current_cursor_pos - foo == le->term_line_size - 1)
        {
            tputs(le->tcaps->_do, 1, &write_one_char);
            cursor_crosses_screen(le, CROSS_TO_LEFT);
            tmp_current_cursor_pos = 0;
        }
        print_key(*str);
        ++str;
    }
	return (tmp_current_cursor_pos);
}
