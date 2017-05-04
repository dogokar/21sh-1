/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmdnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogokar <dogokar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 21:13:27 by dogokar           #+#    #+#             */
/*   Updated: 2017/05/03 21:13:27 by dogokar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

t_cmd	*ft_cmdnew(int token, char *cmd)
{
	t_cmd	*elem;

	if (!(elem = ft_memalloc(sizeof(t_cmd))))
		return (NULL);
	if (cmd == NULL)
	{
		elem->token = token;
		elem->s = NULL;
	}
	else
	{
		elem->s = cmd;
		elem->token = token;
	}
	elem->next = NULL;
	elem->prev = NULL;
	return (elem);
}
