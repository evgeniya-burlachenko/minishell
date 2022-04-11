/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcris <zcris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 08:46:37 by zcris             #+#    #+#             */
/*   Updated: 2021/12/25 07:49:37 by zcris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# define ERRORS_SHELL_PARAMS 		"〰✖️: Run ./minishell without any params\n"
# define ERRORS_MALLOK 				"〰✖️: Heap memory error. Out of memory.\n"
# define ERRORS_FORK				"〰✖️: Can't get pid in fork()\n"
# define ERRORS_DUB2				"〰✖️: Can't reset file descriptor\n"
# define ERRORS_DUB				    "〰✖️: Can't clone file descriptor\n"
# define ERRORS_WAITPID				"〰✖️: Failed to collect child process\n"
# define ERRORS_PIPE				"〰✖️: Error creating pipe\n"
# define ERRORS_PROGRAMM			"〰✖️: "

# define ERROR_EMPTYPIPE_MSG		"〰✖️: Syntax error near \"|\" \n"
# define ERROR_QUOTES				"〰✖️: Not closed quotes founded\n"

# define ERRORS_2					"No such file or directory"
# define ERRORS_126					"Permission denied"
# define ERRORS_126_DIR				"is a directory"
# define ERRORS_127					"command not found"
# define ERRORS_128					"Invalid argument to exit"
# define ERRORS_130					"Script terminated by Control-C"
# define ERRORS_255					"Exit status out of range"
# define ERRORS_N_IDENTIFIER		"not a valid identifier"
# define ERRORS_REQ_NUMBER			"numeric argument required"
# define ERRORS_TOO_MANY			"too many argumentsn"
# define ERRORS_NOT_HOME			"HOME enviroment value is not set"
# define ERRORS_NOT_OPTION			"invalid option"
# define ERRORS_NOT_TOKEN			"syntax error near unexpected token"

#endif