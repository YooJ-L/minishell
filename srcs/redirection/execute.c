/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoojlee <yoojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 20:57:54 by yoojlee           #+#    #+#             */
/*   Updated: 2022/03/31 21:50:52 by yoojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	execve_cmd(t_info *info, int idx, char **envp)
{
	init_cmd(info->execution, info->path, info->command[idx]);
	if (execve(info->execution->path, info->execution->cmd, envp) == -1)
		error("execve error");
}

void	child_process(t_info *info, int (*pipe_fd)[2], int idx, char **envp)
{
	int	*new_pipe;
	int	*old_pipe;

	new_pipe = pipe_fd[1];
	old_pipe = pipe_fd[0];
	if (idx == 0)
		redirect_stdin(info);
	if (idx == info->count_cmd - 1)
		redirect_stdout(info);
	if ((idx > 0) && (idx < info->count_cmd))
		connect_fd(old_pipe, STDIN_FILENO);
	if (idx < info->count_cmd - 1)
		connect_fd(new_pipe, STDOUT_FILENO);
	execve_cmd(info, idx, envp);
	exit(1);
}

void	execute(t_info *info, char **envp)
{
	pid_t	pid;
	int		status;
	int		pipe_fd[2][2];
	int		i;

	i = -1;
	while (++i < info->count_cmd)
	{
		if (pipe(pipe_fd[1]) == -1)
			error("pipe error");
		pid = fork();
		if (pid < 0)
			error("fork error");
		if (pid == 0)
			child_process(info, pipe_fd, i, envp);
		else if (pid > 0)
			close_fd(pipe_fd[0]);
		new_to_old(pipe_fd);
	}
	close_fd(pipe_fd[0]);
	i = 0;
	while (i < info->count_cmd && (wait(&status) != -1))
		i++;
}
