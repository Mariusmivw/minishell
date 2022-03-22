/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_exec_single_file.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/19 13:14:29 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/03/22 16:04:29 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cmds.h"
#include "builtins.h"
#include "safe.h"
#include "libft.h"
#include "envp.h"
#include "error.h"
#include "signals.h"
#include <unistd.h>
#include <stdio.h>

static void	execute_command(t_cmd_node *nodes, t_env_var *envp)
{
	char	*valid_path;

	valid_path = cmd_get_valid_path(nodes->cmd);
	if (valid_path == NULL)
		exit(EXIT_FAILURE);
	safe_check_access(valid_path, nodes->cmd, X_OK);
	error_is_dir(valid_path);
	change_signals(SIG_DFL, SIG_DFL);
	execve(valid_path, nodes->argv, env_list_to_arr(envp));
	perror("execve");
	exit(EXIT_FAILURE);
}

/**
 * Executes a single file or builtin, in case of a file
 * it will create a child process
 * @param nodes pointer to `t_cmd_node *`
 * @param envp pointer to `t_env_var *`
 * @return nothing, if file is executed the process is replaced
 */
void	cmd_exec_single_file(t_cmd_node *nodes, t_env_var *envp,
									int write_fd)
{
	int			ret;

	if (nodes->pipe_to)
	{
		safe_dup2(write_fd, STDOUT_FILENO);
		safe_close(write_fd);
	}
	cmd_redirect_stdin(nodes->files);
	cmd_redirect_stdout(nodes->files);
	ret = builtin_check_and_exec(nodes, envp);
	if (ret == SUCCESFULLY_EXECUTED_BUILTIN)
		return ;
	else if (ret == NO_BUILTIN)
		execute_command(nodes, envp);
	ft_putendl_fd("Error: builtin_check_and_exec == 1", STDERR_FILENO);
	g_exit_status = FAILURE;
}
