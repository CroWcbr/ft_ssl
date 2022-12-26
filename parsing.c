/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 11:43:45 by cdarrell          #+#    #+#             */
/*   Updated: 2022/12/25 15:15:08 by cdarrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static int	check_usage(char *argv)
{
	if (ft_strcmp(argv, "md5") && \
			ft_strcmp(argv, "sha256") && \
			ft_strcmp(argv, "sha512") && \
			ft_strcmp(argv, "whirlpool"))
	{
		ft_putstr("ft_ssl: Error: [");
		ft_putstr(argv);
		ft_putstr("] is an invalid command.\n");
		ft_putstr("\n");
		ft_putstr("Commands:\n");
		ft_putstr("md5\n");
		ft_putstr("sha256\n");
		ft_putstr("sha512\n");
		ft_putstr("whirlpool\n");
		ft_putstr("\n");
		ft_putstr("Flags:\n");
		ft_putstr("-p -q -r -s\n");
		return (0);
	}
	else
		return (1);
}

static t_ssl	*init_ssl(char *hash_alg)
{	
	t_ssl	*ssl;

	ssl = malloc(sizeof(t_ssl));
	if (!ssl)
		ft_err("Error malloc: parsing.c - init_ssl - ssl");
	ssl->hash = hash_alg;
	if (!ft_strcmp(hash_alg, "md5"))
		ssl->hash_func = &md5;
	else if (!ft_strcmp(hash_alg, "sha256"))
		ssl->hash_func = &sha256;
	else if (!ft_strcmp(hash_alg, "sha512"))
		ssl->hash_func = &sha512;
	else if (!ft_strcmp(hash_alg, "whirlpool"))
		ssl->hash_func = &whirlpool;
	ssl->p = false;
	ssl->q = false;
	ssl->r = false;
	ssl->s = false;
	ssl->hash_list = NULL;
	return (ssl);
}

static void	parse_hash_list(char **argv, t_ssl	*ssl)
{
	t_list	*new_list;
	t_hash	*input;

	while (*argv)
	{
		input = malloc(sizeof(t_hash));
		if (!input)
			ft_err("Error malloc: parsing.c - parse_hash_list - input");
		input->type = true;
		if (ssl->s == true)
		{
			ssl->s = false;
			input->type = false;
		}
		input->name = ft_strdup(*argv);
		if (!input->name)
			ft_err("Error malloc: parsing.c - parse_hash_list - input->name");
		input->len = 0;
		if (!input->type)
			input->len = ft_strlen(input->name);
		new_list = ft_lstnew(input);
		if (!new_list)
			ft_err("Error malloc: parsing.c - parse_hash_list - new_list");
		ft_lstadd_back(&ssl->hash_list, new_list);
		argv++;
	}
}

static int	parse_argv(char **argv, t_ssl *ssl)
{
	while (*argv)
	{
		if (!ft_strcmp(*argv, "-p"))
			ssl->p = true;
		else if (!ft_strcmp(*argv, "-q"))
			ssl->q = true;
		else if (!ft_strcmp(*argv, "-r"))
			ssl->r = true;
		else if (!ft_strcmp(*argv, "-s"))
		{
			ssl->s = true;
			argv++;
			if (!(*argv))
			{
				ft_putstr("Error parse_argv: flag s, but no string after\n");
				return (0);
			}
			break ;
		}
		else
			break ;
		argv++;
	}
	parse_hash_list(argv, ssl);
	return (1);
}

t_ssl	*parse(char **argv)
{
	t_ssl	*ssl;

	if (!check_usage(argv[0]))
		return (NULL);
	ssl = init_ssl(argv[0]);
	if (!parse_argv(argv + 1, ssl))
	{
		free(ssl);
		return (NULL);
	}
	if (ssl->p == true || !ssl->hash_list)
		parse_flag_p(ssl);
	return (ssl);
}
