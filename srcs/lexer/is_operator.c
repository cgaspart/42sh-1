/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_operator.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/13 19:25:45 by jjaniec           #+#    #+#             */
/*   Updated: 2018/07/19 15:04:02 by sbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

/*
** Return 1 if c is an operator char, else return 0
*/

int		is_operator(char c)
{
	if (c == '&' || c == '|' || c == ';' || c == '<' || c == '>' || c == '\n')
		return (1);
	return (0);
}
