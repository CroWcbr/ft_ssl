/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 11:43:49 by cdarrell          #+#    #+#             */
/*   Updated: 2023/03/13 00:57:36 by cdarrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ssl.h"
#include <signal.h>

static char	*g_line;

void	_signal_handler(int signal)
{
	ft_putstr("\rSTOP SIGNAL");
	if (signal == -1)
		ft_putstr(" Ctrl + D ");
	else if (signal == 2)
		ft_putstr(" Ctrl + C ");
	else if (signal == 3)
		ft_putstr(" Ctrl + / ");
	else if (signal == 20)
		ft_putstr(" Ctrl + Z ");
	else
		ft_putstr(" Unknown signal ");
	ft_putstr("from user");
	free(g_line);
	exit(signal);
}

static void	free_ssl(t_ssl	*ssl)
{
	ft_lstclear(&ssl->hash_list, free);
	free(ssl->hash_to_upper);
	free(ssl);
}

static void	mandatory_part(char **argv)
{
	t_ssl		*ssl;
	t_list		*tmp;
	t_hash		*hash;
	uint8_t		*result;

	ssl = parse(argv);
	if (!ssl)
		return ;
	if (IS_DEBUG)
		parse_print(ssl);
	tmp = ssl->hash_list;
	while (tmp)
	{
		hash = (t_hash *)tmp->content;
		if (hash->type == false)
			result = ssl->hash_func(hash->name, ft_strlen(hash->name));
		else
			result = read_file(ssl->hash_func, hash, ssl->hash);
		print_hash(ssl, hash, result);
		free(hash->name);
		tmp = tmp->next;
		free(result);
	}
	free_ssl(ssl);
}

static void	work_like_openssl(void)
{
	int		r;
	char	**argv;

	signal(SIGINT, _signal_handler);
	signal(SIGQUIT, _signal_handler);
	signal(SIGTSTP, _signal_handler);
	while (1)
	{
		ft_putstr("OPENSSL > ");
		r = gnl(0, &g_line);
		if (g_line && g_line[0] != '\0')
		{
			argv = ft_split(g_line, ' ');
			free(g_line);
			mandatory_part(argv);
			ft_free_split(argv);
		}
		if (r == 0)
			break ;
		if (r < 0)
			ft_err("Error gnl: ft_ssl - work_like_openssl - line in gnl");
	}
}

int	main(int argc, char **argv)
{
	if (argc == 1)
		work_like_openssl();
	else
		mandatory_part(argv + 1);
	return (0);
}
