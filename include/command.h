/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hisasano <hisasano@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/14 22:13:00 by hisasano          #+#    #+#             */
/*   Updated: 2026/06/14 22:14:17 by hisasano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H

typedef struct s_cmd
{
	char	**argv;
	int		type;
	char	*outfile;
	struct s_cmd *next;
} t_cmd;

#endif