/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_placer_if.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrucker <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/10 12:43:39 by sbrucker          #+#    #+#             */
/*   Updated: 2018/09/26 11:26:29 by sbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

void	node_placer_if(t_ast *root, t_ast *new)
{
	if (!root)
		log_error("!ROOT");
	if (!new)
		log_error("!NEW");
	if (root->parent && root->parent->type == T_WORD)
	{
		root = root->parent->parent;
		root->right = new;
		new->parent = root;
	}
	else
	{
		root->left = new;
		new->parent = root;
	}
}
