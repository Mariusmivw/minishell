/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_export.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/20 13:04:28 by rvan-duy      #+#    #+#                 */
/*   Updated: 2021/11/23 16:24:26 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "envp.h"
#include "libft.h"
#include <stdio.h>

static void	bubble_sort(t_env_var **head)
{
	t_env_var	*current;
	t_env_var	*tmp;
	char		*tmp_name;

	current = *head;
	if (current == NULL)
		return ;
	while (current != NULL)
	{
		tmp = current->next;
		while (tmp != NULL)
		{
			if (ft_strcmp(current->name, tmp->name) > 0)
			{
				tmp_name = current->name;
				current->name = tmp->name;
				tmp->name = tmp_name;
			}
			tmp = tmp->next;
		}
		current = current->next;
	}
}

static t_status	list_export(t_env_var *envp)
{
	t_env_var	*sorted_envp;

	sorted_envp = env_list_dup(envp);
	bubble_sort(&sorted_envp);
	while (sorted_envp)
	{
		if (sorted_envp->value != NULL)
			printf("declare -x %s=\"%s\"\n", sorted_envp->name, sorted_envp->value);
		else
			printf("declare -x %s\n", sorted_envp->name);
		sorted_envp = sorted_envp->next;
	}
	env_list_free(sorted_envp);
	return (SUCCESS);
}

t_status	builtin_export(t_cmd_node *nodes, t_env_var *envp)
{
	t_env_var	*new_env_var;
	size_t		i;

	if (nodes->argv[1] == NULL)
		return (list_export(envp));
	i = 1;
	while (nodes->argv[i] != NULL)
	{
		new_env_var = env_node_new(nodes->argv[i]);
		if (new_env_var == NULL)
			return (FAILURE);
		env_node_del(new_env_var->name, &envp);
		env_node_add(&envp, new_env_var);
		i++;
	}
	return (SUCCESS);
}
