/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 18:05:46 by nbelouni          #+#    #+#             */
/*   Updated: 2017/04/26 18:10:12 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

t_node_p		new_node(t_type_node type, size_t size)
{
	t_node_p	ptr;

	ptr = malloc(sizeof(*ptr));
	bzero(ptr, sizeof(*ptr));
	ptr->type = type;
	ptr->size = size;
	return (ptr);
}

void			*delete_node(t_node_p node)
{
	void	*data;

	data = node->data;
	free(node);
	return (data);
}

t_process_p		new_process(char **argv)
{
	t_process_p ptr;

	ptr = malloc(sizeof(*ptr));
	bzero(ptr, sizeof(*ptr));
	ptr->argv = argv;
	return (ptr);
}

int				is_builtin(char **args)
{
	if (args != NULL && args[0] != NULL)
	{
		if (!ft_strcmp(args[0], "exit"))
			return (TRUE);
		else if (!ft_strcmp(args[0], "env") && !ft_env_binary(args))
			return (TRUE);
		else if (!ft_strcmp(args[0], "setenv"))
			return (TRUE);
		else if (!ft_strcmp(args[0], "loc"))
			return (TRUE);
		else if (!ft_strcmp(args[0], "unsetenv"))
			return (TRUE);
		else if (!ft_strcmp(args[0], "export"))
			return (TRUE);
		else if (!ft_strcmp(args[0], "unset"))
			return (TRUE);
		else if (!ft_strcmp(args[0], "echo"))
			return (TRUE);
		else if (!ft_strcmp(args[0], "cd"))
			return (TRUE);
		else if (!ft_strcmp(args[0], "history"))
			return (TRUE);
	}
	return (FALSE);
}

t_node_p		create_process(t_tree *node_proc)
{
	t_node_p	ptr;
	t_process	*p;

	ptr = new_node(PROCESS, sizeof(struct s_process));
	p = new_process(node_proc->cmd);
	ptr->data = new_link(p, sizeof(struct s_process));
	if (!node_proc->cmd || is_builtin(node_proc->cmd))
		p->flag |= BUILTIN;
	return (ptr);
}
