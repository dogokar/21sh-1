/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 18:05:21 by nbelouni          #+#    #+#             */
/*   Updated: 2017/04/26 18:10:12 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

t_prompt	manage_prompt(char *s, int num)
{
	static t_prompt	prompt;

	if (s)
		prompt.s = s;
	if (num)
		prompt.len = num;
	return (prompt);
}

char		*get_prompt_str(void)
{
	return (manage_prompt(NULL, 0).s);
}

void		set_prompt(char *s, int len)
{
	manage_prompt(s, len);
}

size_t		get_prompt_len(void)
{
	return ((size_t)manage_prompt(NULL, 0).len);
}
