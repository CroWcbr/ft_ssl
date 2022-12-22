/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 11:43:45 by cdarrell          #+#    #+#             */
/*   Updated: 2022/12/22 22:04:48 by cdarrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static void	check_usage(int argc, char **argv)
{
	if (argc == 1)
		printf("usage: ft_ssl command [flags] [file/string]");
	else if (ft_strcmp(argv[1], "md5") && \
			ft_strcmp(argv[1], "sha256") && \
			ft_strcmp(argv[1], "sha512") && \
			ft_strcmp(argv[1], "whirlpool"))
	{
		printf("ft_ssl: Error: '%s' is an invalid command.\n", argv[1]);
		printf("\n");
		printf("Commands:\n");
		printf("md5\n");
		printf("sha256\n");
		printf("sha512\n");
		printf("whirlpool\n");
		printf("\n");
		printf("Flags:\n");
		printf("-p -q -r -s\n");
	}
	else
		return ;
	exit (1);
}

static t_ssl	*init_ssl(char *hash_alg)
{	
	t_ssl	*ssl;

	ssl = malloc(sizeof(t_ssl));
	if (!ssl)
		ft_error("Error malloc: parsing.c - init_ssl");
	ssl->hash = ft_strdup(hash_alg);
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
			ft_error("Error malloc: parsing.c - parse_hash_list");
		input->type = true;
		if (ssl->s == true)
		{
			ssl->s = false;
			input->type = false;
		}
		input->name = ft_strdup(*argv);
		if (!input->name)
			ft_error("Error malloc: parsing.c - parse_hash_list");
		input->hash = NULL;
		new_list = ft_lstnew(input);
		if (!new_list)
			ft_error("Error malloc: parsing.c - parse_hash_list");
		ft_lstadd_back(&ssl->hash_list, new_list);
		argv++;
	}
}

static void	parse_argv(char **argv, t_ssl *ssl)
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
				ft_error("Error parse_argv: flag s, but no string after");
			break ;
		}
		else
			break ;
		argv++;
	}
	if (*argv)
		parse_hash_list(argv, ssl);
}

t_ssl	*parse(int argc, char **argv)
{
	t_ssl	*ssl;

	check_usage(argc, argv);
	ssl = init_ssl(argv[1]);
	parse_argv(argv + 2, ssl);
	if (ssl->p == true || !ssl->hash_list)
		parse_flag_p(ssl);
	return (ssl);
}
