/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_cd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maissa-b <maissa-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/07 18:21:51 by maissa-b          #+#    #+#             */
/*   Updated: 2017/04/13 21:55:23 by maissa-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

/*
**	change le chemin qu'empruntera chdir si une option est spécifié
**	et que le chemin passé a chdir est un lien symbolique
**	opt -> {fin options, 'L', 'P'}
*/

static char	*ft_cd_opt(char *path, mode_t mode, int *opt)
{
	char	*buf;
	char	*tmp;

	buf = NULL;
	tmp = NULL;
	if ((buf = ft_strnew(PATH_MAX)) == NULL)
	{
		return (NULL);
	}
	if (S_ISLNK(mode) && opt != NULL && opt[2])
	{
		if ((tmp = ft_strnew(PATH_MAX)) == NULL)
		{
			ft_strdel(&buf);
			return (NULL);
		}
		readlink(path, tmp, PATH_MAX);
	}
	ft_strncpy(buf, path, (ft_strlen(path) - ft_strlen(ft_strlchr(path, '/'))));
	buf = (tmp) ? ft_strcat(buf, tmp) : ft_strcat(buf, ft_strlchr(path, '/'));
	(tmp) ? ft_strdel(&tmp) : 0;
	return (buf);
}

/*
**	ft_cd est l'etape finale du builtin cd, permettant de changer de dossier
**	et actualisant/creant le PWD et l'OLDPWD
*/

static int	ft_cd(t_lst *env, int *opt, char *s, mode_t m)
{
	char	*buf;
	char	*b2;
	char	*owd;
	int		ret;

	if ((buf = ft_cd_opt(s, m, opt)) == NULL)
		return (-1);
	if (ft_is_valid_dir(buf) == -1)
		return (ft_free_and_return(-1, buf, NULL, NULL));
	if ((owd = getcwd(NULL, PATH_MAX)) == NULL)
		return (ft_free_and_return(-1, buf, NULL, NULL));
	chdir(buf);
	if ((b2 = getcwd(NULL, PATH_MAX)) == NULL)
		return (ft_free_and_return(-1, owd, NULL, NULL));
	if (S_ISLNK(m) != 0 && opt != NULL && opt[0] > 0 && opt[1] > 0)
	{
		ft_memset(ft_strlchr(b2, '/'), 0, ft_strlen(ft_strlchr(b2, '/')));
		if ((b2 = ft_free_and_join(b2, ft_strlchr(s, '/'))) == NULL)
			return (ft_free_and_return(ERR_EXIT, owd, b2, NULL));
	}
	ret = ft_pwd_swap(env, owd, b2);
	(buf) ? ft_strdel(&buf) : NULL;
	return (ft_free_and_return(ret, owd, b2, NULL));
}

/*
**	ft_concat_path est une etape intermediaire permettant de remplacer
**	s1 par s2 et de tester la validité du dossier. Elle est appelé si cd
**	possede 2 arguments en dehors des options.
*/

char		*ft_concat_path(char *res, char *s1, char *s2, size_t len)
{
	char		*b1;
	char		*b2;
	size_t		i;

	i = ft_strlen(res);
	if ((b1 = ft_strsub(res, 0, (i - len))) == NULL)
		return (NULL);
	if ((b2 = ft_strsub(res, (i - len + ft_strlen(s1)), PATH_MAX)) == NULL)
	{
		ft_strdel(&b1);
		return (NULL);
	}
	ft_memset(res, 0, PATH_MAX);
	res = ft_multi_concat(res, b1, s2, b2);
	ft_multi_free(b1, b2, NULL, NULL);
	if (ft_is_valid_dir(res) == -1)
	{
		ft_strdel(&res);
	}
	return (res);
}

/*
**	check s'il y a des arguments pour creer le path, s'il n'y en a pas,
**	il prend par default la valeur de la variable HOME, qui, si elle n'est
**	pas set, sera NULL.
*/

static char	*ft_builtin_cd_norm(t_lst *env, int *op, char **args)
{
	char		*path;
	t_elem		*e;

	path = NULL;
	if (args != NULL && args[op[0]] != NULL && args[op[0]][0] != '\0')
	{
		if ((path = ft_create_path(env, args[op[0]], args[op[0] + 1])) == NULL)
			return (NULL);
	}
	else
	{
		if ((e = ft_find_elem("HOME", env)) == NULL)
			ft_print_error("cd", ERR_HOME_NOT_SET, ERR_NEW_CMD);
		if (e != NULL && e->value != NULL)
		{
			if ((path = ft_create_path(env, e->value, NULL)) == NULL)
				return (NULL);
		}
	}
	return (path);
}

/*
**	builtin qui permet de changer de directory, il peut recevoir, hors options,
**	soit aucun arguments, soit jusqu'a 2 arguments. Il renverra une erreur si
**	plus d'arguments sont trouvés.
*/

int			ft_builtin_cd(t_core *core, char **args)
{
	struct stat	st;
	int			*opt;
	int			i;
	char		*s;

	opt = ft_opt_parse(CD_OPT, args, 1);
	if (opt == NULL)
		return (ERR_EXIT);
	else if (opt[0] == -1)
		return (ft_free_and_return(ERR_NEW_CMD, opt, NULL, NULL));
	if (args != NULL && args[opt[0]] != NULL && ft_tablen(&(args[opt[0]])) > 2)
	{
		(opt != NULL) ? free(opt) : 0;
		return (ft_print_error("cd", ERR_TOO_MANY_ARGS, ERR_NEW_CMD));
	}
	i = -1;
	if ((s = ft_builtin_cd_norm(core->env, opt, args)) != NULL)
	{
		i = ((lstat(s, &st)) != -1) ? ft_cd(core->env, opt, s, st.st_mode) :\
			ft_print_error(s, ERR_NO_FILE, ERR_NEW_CMD);
		ft_strdel(&s);
	}
	(opt) ? free(opt) : 0;
	return (i);
}
