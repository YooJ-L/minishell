/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoojlee <yoojlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 06:24:17 by yoojlee           #+#    #+#             */
/*   Updated: 2022/04/10 13:08:39 by yoojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


/*
cat << doc1 | cat << doc2 | cat << doc3
이런식으로 heredoc이 여러번 들어오면
순서대로 들어와야 끝남.
이 결과는 doc2 들어오고, 그 뒤에 입력한 것만 출력. 앞에것들은 결과가 파이프로 넘어감.
*/


//여기서 굳이 파이프를 써야 하는 이유가 따로 있나..?
//어차피 input 내용들 다 process->heredoc_str에 저장할거면 파이프fd에
//쓸 필요 없을 것 같은데
//=>fork를 하면 무조건 파이프fd에 무조건 써야 함. 자식프로세스 끝나면 다 지워지니까.
//근데 여기서 fork안해줘도 될 것 같은데?

// #include "../../includes/structure.h"
#include "../../includes/parsing.h"

static void	exec_heredoc(const char *eof_str, int output_fd)
{
	char	*save;
	char	*input;

	save = (char *)malloc(sizeof(char) * 1);
	if (!save)
		perror_and_exit("cannot allocate memory\n", ENOMEM);
	save[0] = '\0';
	while (1)
	{
		input = readline("> ");
		if (input && input[0] == '\0')
			continue ;
		if (!ft_strncmp(input, eof_str, ft_strlen(eof_str) + 1))
		{
			free(input);
			break ;
		}
		save_str(&save, input);
		free(input);
	}
	add_char_to_str(&save, '\n');
	ft_putstr_fd(save, output_fd);
	free(save);
	// system("leaks minishell");
	exit(0);
}

static void	read_heredoc_str(t_process *process, int input_fd)
{
	char	*save;
	char	*temp;

	while (get_next_line(input_fd, &save) > 0)
	{
		if (!(process->heredoc_str))
		{
			process->heredoc_str = ft_strdup(save);
		}
		else
		{
			temp = process->heredoc_str;
			process->heredoc_str = ft_strjoin(temp, save);
			if (temp)
				free(temp);
		}
		add_char_to_str(&(process->heredoc_str), '\n');
		free(save);
	}
	free(save);
}

int	fork_heredoc_process(t_info *info, t_process *process, char *eof)
{
	pid_t	pid;
	int		exit_status;
	int		pipe_fd[2];

	if (process->heredoc_str)
	{
		free(process->heredoc_str);
		process->heredoc_str = NULL;
	}
	pipe(pipe_fd);
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		close(pipe_fd[0]);
		exec_heredoc(eof, pipe_fd[1]);
	}
	signal(SIGINT, SIG_IGN); //자식프로세스에서 바꿔준건데 왜 굳이 써야함?
	close(pipe_fd[1]);
	waitpid(pid, &exit_status, 0);
	read_heredoc_str(process, pipe_fd[0]);
	close(pipe_fd[0]);
	// set_parent_process(info); //왜 여기 들어가야함?
	return (exit_status);
}

int	get_heredoc_input(t_info *info, t_process *process)
{
	char			*eof_str;
	int				exit_status;
	t_redirection	*redirect;

	redirect = process->redirect;
	while (redirect)
	{
		if (redirect->symbol == DOUBLE_IN)
		{
			if (redirect->filename == NULL)
			{
				perror_in_parsing("newline");
				return (0);
			}
			eof_str = redirect->filename;
			exit_status = fork_heredoc_process(info, process, eof_str);
			if (exit_status != 0)
			{
				sig_exit_handler(exit_status);
				return (0);
			}
		}
		redirect = redirect->next;
	}
	return (1);
}

//eof str 들어올 때까지 입력 계속 받고 그 입력 내용 저장해서 파이프로 보내는 함수
int	run_heredoc(t_info *info, t_process *process)
{
	int	i;

	i = 0;
	if (!info)
		return (0);
	while (i < info->process_cnt)
	{
		if (!&process[i] || !get_heredoc_input(info, &process[i])) //eof만나기 전까지의 내용 저장하기
			return (0);
		i++;
	}
	return (1);
}
