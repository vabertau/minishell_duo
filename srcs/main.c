/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzaz <hzaz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 16:54:44 by vabertau          #+#    #+#             */
/*   Updated: 2024/04/24 18:20:36 by hzaz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
/*
int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	(void)argc;
	(void)argv;
	(void)envp;
	get_input(&data);
}
*/

//============ TEST NB_TOKENS ==============
/*
int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	(void)argc;
	(void)argv;
	(void)envp;
	//get_input(&data);
	data.cmdline = ft_strdup("test\"hey test\"");
	spaces_bet_tokens(&data);
	nb_tokens(&data);
	printf("nb tokens = %i\n", data.nb_tokens);
}
*/

// ============ TEST SPACES_BET_TOKENS ============

/*
int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	(void)argc;
	(void)argv;
	(void)envp;
	//while (1)
	//{
		get_input(&data);
		spaces_bet_tokens(&data);
		printf("cmdline = %s\n", data.cmdline);
	//}
	exit_free(&data, 0); //tmp
}
*/

// ============ TEST NB_TOKENS ===============
/*
int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	(void)argc;
	(void)argv;
	(void)envp;
	init_data(&data);
	while (1)
	{
		get_input(&data);
		spaces_bet_tokens(&data);
		nb_tokens(&data);
		printf("cmdline = %s\n", data.cmdline);
		printf("nb tokens = %i\n", data.nb_tokens);
	}
	exit_free(&data, 0); //tmp
}
*/

// ============ TEST FILL_TOKENS ================
/*
int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	t_data	tmp;
	int		i;

	(void)argc;
	(void)argv;
	(void)envp;
	i = 0;
	//while (1)
	//{
		init_data(&data);
		get_input(&data);
		spaces_bet_tokens(&data);
		nb_tokens(&data);
		malloc_tokens(&data);
		if (data.token == NULL)
			printf("token = NULL");
		fill_tokens(&data);
		printf("cmdline = %s\n", data.cmdline);
		printf("nb tokens = %i\n", data.nb_tokens);
		tmp = data;
		while (tmp.token != NULL)
		{
			printf("word = %s\n", tmp.token->word);
			printf("is_bq = %i\n", data.is_bq[i]);
			tmp.token = tmp.token->next;
			i++;
		}
	//	free_bf_newprompt(&data);
	//}
	exit_free(&data, 0); //tmp
}
*/
// ============ TEST FILL_TOKENS  LLDB ================
/*
int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	t_data	tmp;
	int		i;

	(void)argc;
	(void)argv;
	(void)envp;
	i = 0;
	//while (1)
	//{
		init_data(&data);
		//get_input(&data);
		data.cmdline = ft_strdup("test \" hey test\" hey\"");
		spaces_bet_tokens(&data);
		nb_tokens(&data);
		malloc_tokens(&data);
		if (data.token == NULL)
			printf("token = NULL");
		fill_tokens(&data);
		printf("cmdline = %s\n", data.cmdline);
		printf("nb tokens = %i\n", data.nb_tokens);
		tmp = data;
		while (tmp.token != NULL)
		{
			printf("word = %s\n", tmp.token->word);
			printf("is_bq = %i\n", data.is_bq[i]);
			tmp.token = tmp.token->next;
			i++;
		}
	//	free_bf_newprompt(&data);
	//}
	exit_free(&data, 0); //tmp
}

*/

// ======== TEST FILL_TYPES =========
/*
int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	t_data	tmp;
	t_type	test_type;
	int		i;

	(void)argc;
	(void)argv;
	(void)envp;
	i = 0;
	//while (1)
	//{
		init_data(&data);
		get_input(&data);
		spaces_bet_tokens(&data);
		nb_tokens(&data);
		malloc_tokens(&data);
		if (data.token == NULL)
			printf("token = NULL");
		fill_tokens(&data);
		fill_types(&data);
		printf("cmdline = %s\n\n", data.cmdline);
		printf("nb tokens = %i\n\n", data.nb_tokens);
		tmp = data;
		test_type = WORD;
		while (tmp.token != NULL)
		{
			printf("word = %s\n", tmp.token->word);
			printf("type = %u\n", tmp.token->type);
			printf("is_bq = %i\n\n", data.is_bq[i]);
			tmp.token = tmp.token->next;
			i++;
		}
	//	free_bf_newprompt(&data);
	//}
	exit_free(&data, 0); //tmp
}
*/
// ======== TEST LEXER LLDB =============
/*
int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	t_data	tmp;
	t_type	test_type;
	int		i;

	(void)argc;
	(void)argv;
	(void)envp;
	i = 0;
	//while (1)
	//{
		init_data(&data);
		//get_input(&data);
		data.cmdline = ft_strdup("hey \" hey\"");
		lexer(&data);
		printf("cmdline = %s\n\n", data.cmdline);
		printf("nb tokens = %i\n\n", data.nb_tokens);
		tmp = data;
		test_type = WORD;
		while (tmp.token != NULL)
		{
			printf("word = %s\n", tmp.token->word);
			printf("type = %u\n", tmp.token->type);
			printf("is_bq = %i\n\n", data.is_bq[i]);
			tmp.token = tmp.token->next;
			i++;
		}
	//	free_bf_newprompt(&data);
	//}
	exit_free(&data, 0); //tmp
}
*/
// ====== TEST LEXER =========

/*
int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	t_data	tmp;
	t_type	test_type;
	int		i;

	(void)argc;
	(void)argv;
	(void)envp;
	i = 0;
	//while (1)
	//{
		init_data(&data);
		get_input(&data);
		lexer(&data);
		printf("cmdline = %s\n\n", data.cmdline);
		printf("nb tokens = %i\n\n", data.nb_tokens);
		tmp = data;
		test_type = WORD;
		while (tmp.token != NULL)
		{
			printf("word = %s\n", tmp.token->word);
			printf("type = %u\n", tmp.token->type);
			printf("is_bq = %i\n\n", data.is_bq[i]);
			tmp.token = tmp.token->next;
			i++;
		}
	//	free_bf_newprompt(&data);
	//}
	exit_free(&data, 0); //tmp
}
*/
// ===== TEST NB_CMD =======
/*
int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	t_data	tmp;
	t_type	test_type;
	int		i;

	(void)argc;
	(void)argv;
	(void)envp;
	i = 0;
	//while (1)
	//{
		init_data(&data);
		get_input(&data);
		lexer(&data);
		parser(&data);
		printf("cmdline = %s\n\n", data.cmdline);
		printf("nb tokens = %i\n\n", data.nb_tokens);
		printf("nb_cmd = %i\n\n", data.nb_cmd);
		tmp = data;
		test_type = WORD;
		while (tmp.token != NULL)
		{
			printf("word = %s\n", tmp.token->word);
			printf("type = %u\n", tmp.token->type);
			printf("is_bq = %i\n\n", data.is_bq[i]);
			tmp.token = tmp.token->next;
			i++;
		}
	//	free_bf_newprompt(&data);
	//}
	exit_free(&data, 0); //tmp
}
*/
// ===== TEST MALLOC EXEC & FILL_FULL_CMD =====
/*
int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	t_data	tmp;
	t_exec	*tmp_exec;
	t_type	test_type;
	int		i;

	(void)argc;
	(void)argv;
	(void)envp;
	i = 0;
	//while (1)
	//{
		init_data(&data);
		get_input(&data);
		lexer(&data);
		parser(&data);
		printf("cmdline = %s\n\n", data.cmdline);
		printf("nb tokens = %i\n\n", data.nb_tokens);
		printf("nb_cmd = %i\n\n", data.nb_cmd);
		tmp = data;
		test_type = WORD;
		while (tmp.token != NULL)
		{
			printf("word = %s\n", tmp.token->word);
			printf("type = %u\n", tmp.token->type);
			printf("is_bq = %i\n\n", data.is_bq[i]);
			tmp.token = tmp.token->next;
			i++;
		}
		i = 0;
		tmp_exec = data.exec;
		while (i < data.nb_cmd)
		{
			printf("full cmd = %s\n", tmp_exec->full_cmd);
			tmp_exec = tmp_exec->next;
			i++;
		}
	//	free_bf_newprompt(&data);
	//}
	exit_free(&data, 0); //tmp
}
*/

// ========== TEST FILL FULL CMD  LLDB ===========
/*
int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	t_data	tmp;
	t_exec	*tmp_exec;
	t_type	test_type;
	int		i;

	(void)argc;
	(void)argv;
	(void)envp;
	i = 0;
	//while (1)
	//{
		init_data(&data);
		//get_input(&data);
		data.cmdline = ft_strdup("test1 test2 | test3 test4");
		lexer(&data);
		parser(&data);
		printf("cmdline = %s\n\n", data.cmdline);
		printf("nb tokens = %i\n\n", data.nb_tokens);
		printf("nb_cmd = %i\n\n", data.nb_cmd);
		tmp = data;
		test_type = WORD;
		while (tmp.token != NULL)
		{
			printf("word = %s\n", tmp.token->word);
			printf("type = %u\n", tmp.token->type);
			printf("is_bq = %i\n\n", data.is_bq[i]);
			tmp.token = tmp.token->next;
			i++;
		}
		i = 0;
		tmp_exec = data.exec;
		while (i < data.nb_cmd)
		{
			printf("full cmd = %s\n", tmp_exec->full_cmd);
			tmp_exec = tmp_exec->next;
			i++;
		}
		tmp_exec = data.exec;
		while (tmp_exec != NULL)
		{
			i = 0;
			while (tmp_exec->split_cmd[i] != NULL)
			{
				printf("split cmd = %s\n", tmp_exec->split_cmd[i]);
				i++;
			}
			tmp_exec = tmp_exec->next;
		}
	//	free_bf_newprompt(&data);
	//}
	exit_free(&data, 0); //tmp
}
*/
// ========== TEST FILL FULL CMD LLDB ===========
/*
int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	t_data	tmp;
	t_exec	*tmp_exec;
	t_type	test_type;
	int		i;

	(void)argc;
	(void)argv;
	(void)envp;
	i = 0;
	//while (1)
	//{
		init_data(&data);
		get_input(&data);
		lexer(&data);
		parser(&data);
		printf("cmdline = %s\n\n", data.cmdline);
		printf("nb tokens = %i\n\n", data.nb_tokens);
		printf("nb_cmd = %i\n\n", data.nb_cmd);
		tmp = data;
		test_type = WORD;
		while (tmp.token != NULL)
		{
			printf("word = %s\n", tmp.token->word);
			printf("type = %u\n", tmp.token->type);
			printf("is_bq = %i\n\n", data.is_bq[i]);
			tmp.token = tmp.token->next;
			i++;
		}
		i = 0;
		tmp_exec = data.exec;
		while (i < data.nb_cmd)
		{
			printf("full cmd = %s\n", tmp_exec->full_cmd);
			tmp_exec = tmp_exec->next;
			i++;
		}
		tmp_exec = data.exec;
		i = 0;
		while (tmp_exec != NULL)
		{
			i = 0;
			while (tmp_exec->split_cmd[i] != NULL)
			{
				printf("split cmd = %s\n", tmp_exec->split_cmd[i]);
				i++;
			}
			tmp_exec = tmp_exec->next;
		}
	//	free_bf_newprompt(&data);
	//}
	exit_free(&data, 0); //tmp
}
*/

// ===== NB_REDIR LLDB ======
/*
int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	t_data	tmp;
	t_exec	*tmp_exec;
	t_type	test_type;
	int		i;

	(void)argc;
	(void)argv;
	(void)envp;
	i = 0;
	//while (1)
	//{
		init_data(&data);
		//get_input(&data);
		data.cmdline = ft_strdup(">infile test1 test2 test3 test4");
		lexer(&data);
		parser(&data);
		nb_redir(&data);
		printf("cmdline = %s\n\n", data.cmdline);
		printf("nb tokens = %i\n\n", data.nb_tokens);
		printf("nb_cmd = %i\n\n", data.nb_cmd);
		tmp = data;
		test_type = WORD;
		while (tmp.token != NULL)
		{
			printf("word = %s\n", tmp.token->word);
			printf("type = %u\n", tmp.token->type);
			printf("is_bq = %i\n\n", data.is_bq[i]);
			tmp.token = tmp.token->next;
			i++;
		}
		i = 0;
		tmp_exec = data.exec;
		while (i < data.nb_cmd)
		{
			printf("full cmd = %s\n", tmp_exec->full_cmd);
			tmp_exec = tmp_exec->next;
			i++;
		}
		tmp_exec = data.exec;
		i = 0;
		while (tmp_exec != NULL)
		{
			printf("nb redir = %i\n", tmp_exec->nb_redir);
			tmp_exec = tmp_exec->next;
		}
	//	free_bf_newprompt(&data);
	//}
	exit_free(&data, 0); //tmp
}
*/
// ==== NB_REDIR ====

/*
int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	t_data	tmp;
	t_exec	*tmp_exec;
	t_type	test_type;
	int		i;

	(void)argc;
	(void)argv;
	(void)envp;
	i = 0;
	//while (1)
	//{
		init_data(&data);
		get_input(&data);
		lexer(&data);
		parser(&data);
		nb_redir(&data);
		printf("cmdline = %s\n\n", data.cmdline);
		printf("nb tokens = %i\n\n", data.nb_tokens);
		printf("nb_cmd = %i\n\n", data.nb_cmd);
		tmp = data;
		test_type = WORD;
		while (tmp.token != NULL)
		{
			printf("word = %s\n", tmp.token->word);
			printf("type = %u\n", tmp.token->type);
			printf("is_bq = %i\n\n", data.is_bq[i]);
			tmp.token = tmp.token->next;
			i++;
		}
		i = 0;
		tmp_exec = data.exec;
		while (i < data.nb_cmd)
		{
			printf("full cmd = %s\n", tmp_exec->full_cmd);
			tmp_exec = tmp_exec->next;
			i++;
		}
		tmp_exec = data.exec;
		i = 0;
		while (tmp_exec != NULL)
		{
			i = 0;
			while (tmp_exec->split_cmd[i] != NULL)
			{
				printf("split cmd = %s\n", tmp_exec->split_cmd[i]);
				i++;
			}
			tmp_exec = tmp_exec->next;
		}
		tmp_exec = data.exec;
		i = 0;
		while (tmp_exec != NULL)
		{
			printf("nb redir = %i\n", tmp_exec->nb_redir);
			tmp_exec = tmp_exec->next;
		}
	//	free_bf_newprompt(&data);
	//}
	exit_free(&data, 0); //tmp
}
*/

// ===== FILL_REDIR LLDB =====

/*
int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	t_data	tmp;
	t_exec	*tmp_exec;
	t_type	test_type;
	int		i;

	(void)argc;
	(void)argv;
	(void)envp;
	i = 0;
	//while (1)
	//{
		init_data(&data);
		//get_input(&data);
		data.cmdline = ft_strdup("< infile test1 test2");
		lexer(&data);
		parser(&data);
		printf("cmdline = %s\n\n", data.cmdline);
		printf("nb tokens = %i\n\n", data.nb_tokens);
		printf("nb_cmd = %i\n\n", data.nb_cmd);
		tmp = data;
		test_type = WORD;
		while (tmp.token != NULL)
		{
			printf("word = %s\n", tmp.token->word);
			printf("type = %u\n", tmp.token->type);
			printf("is_bq = %i\n\n", data.is_bq[i]);
			tmp.token = tmp.token->next;
			i++;
		}
		i = 0;
		tmp_exec = data.exec;
		while (i < data.nb_cmd)
		{
			printf("full cmd = %s\n", tmp_exec->full_cmd);
			tmp_exec = tmp_exec->next;
			i++;
		}
		tmp_exec = data.exec;
		i = 0;
		while (tmp_exec != NULL)
		{
			i = 0;
			while (tmp_exec->split_cmd[i] != NULL)
			{
				printf("split cmd = %s\n", tmp_exec->split_cmd[i]);
				i++;
			}
			tmp_exec = tmp_exec->next;
		}
		tmp_exec = data.exec;
		i = 0;
		while (tmp_exec != NULL)
		{
			printf("nb redir = %i\n", tmp_exec->nb_redir);
			tmp_exec = tmp_exec->next;
		}
		tmp_exec = data.exec;
		i = 0;
		while (tmp_exec != NULL)
		{
			if (tmp_exec->redir)
				printf("redir infile/outfile= %s\n", tmp_exec->redir->word);
			tmp_exec = tmp_exec->next;
		}
	//	free_bf_newprompt(&data);
	//}
	exit_free(&data, 0); //tmp
}
*/

// ==== FILL_REDIR ====


int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	t_data	tmp;
	t_exec	*tmp_exec;
	t_type	test_type;
	int		i;

	(void)argc;
	(void)argv;
	(void)envp;
	i = 0;
	//while (1)
	//{
		init_data(&data, envp);
		get_input(&data);
		lexer(&data);
		parser(&data);
		executor(&data);
		printf("cmdline = %s\n\n", data.cmdline);
		printf("nb tokens = %i\n\n", data.nb_tokens);
		printf("nb_cmd = %i\n\n", data.nb_cmd);
		tmp = data;
		test_type = WORD;
		while (tmp.token != NULL)
		{
			printf("word = %s\n", tmp.token->word);
			printf("type = %u\n", tmp.token->type);
			printf("is_bq = %i\n\n", data.is_bq[i]);
			tmp.token = tmp.token->next;
			i++;
		}
		i = 0;
		tmp_exec = data.exec;
		while (i < data.nb_cmd)
		{
			printf("full cmd = %s\n", tmp_exec->full_cmd);
			tmp_exec = tmp_exec->next;
			i++;
		}
		tmp_exec = data.exec;
		i = 0;
		while (tmp_exec != NULL)
		{
			i = 0;
			while (tmp_exec->split_cmd[i] != NULL)
			{
				printf("split cmd = %s\n", tmp_exec->split_cmd[i]);
				i++;
			}
			tmp_exec = tmp_exec->next;
		}
		tmp_exec = data.exec;
		i = 0;
		while (tmp_exec != NULL)
		{
			printf("nb redir = %i\n", tmp_exec->nb_redir);
			tmp_exec = tmp_exec->next;
		}
		tmp_exec = data.exec;
		i = 0;
		while (tmp_exec != NULL)
		{
			if (tmp_exec->redir)
			{
				printf("redir infile/outfile= %s\n", tmp_exec->redir->word);
				printf("redir type= %i\n\n", tmp_exec->redir->type);
			}
			tmp_exec = tmp_exec->next;
		}
	//	free_bf_newprompt(&data);
	//}
	exit_free(&data, 0); //tmp
}
