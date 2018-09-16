/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actionk_delete_character.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/19 14:53:51 by cyfermie          #+#    #+#             */
/*   Updated: 2018/09/06 20:58:51 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

/*
**	Delete the last character of the command line and the cursor moves one step
**	to the left. (backspace mode)
*/

static void	delete_last_char_while_moving_back_cursor(struct s_line *le)
{
	unsigned int	keep_current_cursor_line;

	keep_current_cursor_line = le->current_cursor_line;
	actionk_cursor_move_left(le);
	tputs(le->tcaps->dc, 1, &write_one_char);
	if (cursor_is_at_end_of_term_line(le->current_cursor_pos, le) == true)
		weird_trick_to_erase_char(le);
	--(le->line_index);
	le->line[le->line_index] = '\0';
	if ((keep_current_cursor_line + 1) == le->nb_li_currently_writing)
	{
		if (le->nb_car_written_on_last_current_line == 0)
		{
			--(le->nb_li_currently_writing);
			le->nb_car_written_on_last_current_line = le->term_line_size - 1;
			if (!(le->current_cursor_line) && le->nb_li_currently_writing == 1)
				le->nb_car_written_on_last_current_line = le->term_line_size \
				- le->start_pos - 1;
		}
		else
			--(le->nb_car_written_on_last_current_line);
	}
}

/*
**	Delete the last character of the command line without moving the cursor
**	(delete mode)
*/

static void	delete_last_char_without_moving_cursor(struct s_line *le)
{
	tputs(le->tcaps->dc, 1, &write_one_char);
	if (cursor_is_at_end_of_term_line(le->current_cursor_pos, le) == true)
		weird_trick_to_erase_char(le);
	--(le->line_index);
	le->line[le->line_index] = '\0';
	if (cursor_is_at_end_of_term_line(le->current_cursor_pos, le) == true)
	{
		--(le->nb_li_currently_writing);
		le->nb_car_written_on_last_current_line = le->term_line_size - 1;
		if (!(le->current_cursor_line) && le->nb_li_currently_writing == 1)
			le->nb_car_written_on_last_current_line = le->term_line_size \
			- le->start_pos - 1;
		else if (cursor_is_at_end_of_term_line(le->current_cursor_pos, le) == false)
			--(le->nb_car_written_on_last_current_line);
	}
	else
		--(le->nb_car_written_on_last_current_line);
}

/*
**	Delete a character using 2 different modes :
**	mode backspace : the character just before the cursor is deleted
**					 and the cursor moves one step left.
**					 If the cursor is on the start-position of the command line,
**					 there is no character to delete and nothing happens.
**	mode delete : the character under the cursor is deleted and the cursor
**				  does not move.
**				  If there is no character under the cursor, nothing happens.
*/

void		actionk_delete_character(struct s_line *le)
{
	if (le->le_state.opt_colosyn == true)
	{
		colosyn_delete_char(le);
		return ;
	}
	if (le->key_no == LE_BACKSPACE)
	{
		if (le->current_cursor_line == 0
		&& le->current_cursor_pos == le->start_pos)
			return ;
		if (cursor_is_at_end_of_cmd(le) == true)
			delete_last_char_while_moving_back_cursor(le);
		else
			delete_char_into_cmdline_while_moving_back_cursor(le);
	}
	else if (le->key_no == LE_DELETE)
	{
		if (cursor_is_at_end_of_cmd(le) == true)
			return ;
		if (le->cursor_index_for_line == (le->line_index - 1))
			delete_last_char_without_moving_cursor(le);
		else
			delete_char_into_cmdline_without_moving_cursor(le);
	}
}
