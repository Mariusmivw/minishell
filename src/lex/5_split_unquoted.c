/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   5_split_unquoted.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/16 14:49:53 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/02/22 11:24:20 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"

void	split_unquoted_token(t_list **token)
{
	char	**splitted;
	t_list	*next;
	int		i;

	splitted = ft_protect(ft_split(((t_token *)(*token)->content)->value, ' '));
	i = 0;
	while (splitted[i] != NULL)
	{
		ft_protect(ft_lstnew_front(create_token(splitted[i], UNQUOTED), token));
		token = &(*token)->next;
		if (splitted[i + 1] != NULL)
		{
			ft_protect(ft_lstnew_front(create_token(NULL, WHITESPACE), token));
			token = &(*token)->next;
		}
		i++;
	}
	next = (*token)->next;
	ft_lstdelone(*token, &free_token);
	*token = next;
}

void	split_unquoted(t_list **tokens)
{
	while (*tokens != NULL)
	{
		if (is_type(((t_token *)(*tokens)->content)->type, UNQUOTED)
			&& ft_strchr(((t_token *)(*tokens)->content)->value, ' ') != NULL)
		{
			split_unquoted_token(tokens);
		}
		tokens = &(*tokens)->next;
	}
}
