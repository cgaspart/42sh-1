/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_char_to_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 19:11:55 by jjaniec           #+#    #+#             */
/*   Updated: 2018/02/13 16:25:27 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

char	*ft_char_to_str(char c)
{
	char	*s;

	s = malloc(2);
	s[0] = c;
	s[1] = '\0';
	return (s);
}