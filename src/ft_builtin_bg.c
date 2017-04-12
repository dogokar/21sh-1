/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_bg.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maissa-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/07 19:13:35 by maissa-b          #+#    #+#             */
/*   Updated: 2017/04/12 15:42:32 by alallema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

static int		exec_job_bg(t_job *job)
{
	if (job == NULL)
		return (-1);
	if (job_is_stopped(job) && job->foreground)
	{
		job->foreground = 0;
		continue_job(job, job->foreground); // continue_job(j);
	}
	else
	{
		write(2, "42sh: bg: job already in background\n", 36);
		return (-1);
	}
	return (0);
}

int      ft_builtin_bg(t_core *core, char **args)
{
	(void)core;
	if (args && args[0])
	{
		exec_job_bg(ft_get_job(args[0]));
	}
	else
	{
		exec_job_bg(get_last_job());
	}
	return (0);
}
/*
int	main(void)
{
	t_job *test;
	char	*args;

	test = malloc(sizeof(t_job));
	scanf("bg %s", args)
	creat_job()
	return (0);
}
*/
