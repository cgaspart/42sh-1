/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_end_lexeme_solo.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrucker <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/20 19:29:38 by sbrucker          #+#    #+#             */
/*   Updated: 2018/09/25 15:59:56 by sebastien        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

static t_lexeme	*to_end(t_lexeme *lex)
{
	size_t	end_token;
	t_lexeme	*save_lex;

	if (lex->type_details == TK_SCRIPT_IF)
		end_token = TK_SCRIPT_FI;
	else if (lex->type_details == TK_SCRIPT_WHILE)
		end_token = TK_SCRIPT_DONE;
	else
		return (lex);
	while (lex && lex->type_details != end_token)
	{
		lex = lex->next;
		save_lex = lex;
		lex = to_end(lex);
		if (save_lex != lex)
			lex = lex->next;
	}
	return (lex);
}

t_lexeme	*find_end_lexeme_solo(t_lexeme *start, const size_t end_token)
{
	t_lexeme	*lex;

	start = start->next;
	lex = start;
	while (lex && lex->type_details != end_token)
	{
		lex = to_end(lex);
		lex = lex->next;
	}
	if (lex)
		return (lex);
	return (start);
}
