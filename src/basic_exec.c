/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 17:13:46 by kruseva           #+#    #+#             */
/*   Updated: 2025/02/07 20:38:15 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include <stdbool.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>

typedef struct s_cmd
{
    char *delimiter;
    char ***cmd;
    char **envp;
    bool pipe;
    bool redir_in;
    bool redir_out;
    bool redir_append;
    char *file_in;
    char *file_out;
    bool end_of_cmd;
} t_cmd;

void exec_pipes(t_cmd *cmd, int fd_in, int fd_out);
void exec_cmd(char *cmd_path, char **cmd, char **envp);

void init_cmd(t_cmd *cmd)
{
    cmd->delimiter = NULL;
    cmd->cmd = malloc(3 * sizeof(char **));
    cmd->cmd[0] = (char *[]) {"/usr/bin/wc", NULL};
    cmd->cmd[1] = (char *[]) {"wc", "-l", NULL}; 
    cmd->cmd[2] = NULL; 

    cmd->envp =  (char *[]) {
        "TERM_PROGRAM=vscode", "TERM=xterm-256color", "SHELL=/bin/zsh",
        "TMPDIR=/var/folders/zz/zyxvpxvq6csfxvn_n000clnm0034xd/T/",
        "TERM_PROGRAM_VERSION=1.96.2", "TERM_SESSION_ID=53526D26-6581-48AF-B72E-1DA2B681CCC8",
        "USER=kruseva", "SSH_AUTH_SOCK=/private/tmp/com.apple.launchd.Jc8nhrjb3X/Listeners",
        "PATH=/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki:/Library/Apple/usr/bin:/Users/kruseva/valgrind/bin:/Users/kruseva/.local/bin:/Applications/Visual Studio Code.app/Contents/Resources/app/bin:/Users/kruseva/Library/Application Support/Code/User/globalStorage/github.copilot-chat/debugCommand:/Users/kruseva/.local/bin",
        "PWD=/Users/kruseva/Desktop/AllProjects/pipex", "LANG=en_US.UTF-8", "XPC_FLAGS=0x0",
        "XPC_SERVICE_NAME=0", "HOME=/Users/kruseva", "SHLVL=3", "LOGNAME=kruseva",
        "__CF_USER_TEXT_ENCODING=0x193AD:0x0:0x0", "ORIGINAL_XDG_CURRENT_DESKTOP=undefined",
        "COLORTERM=truecolor", "GIT_ASKPASS=/Applications/Visual Studio Code.app/Contents/Resources/app/extensions/git/dist/askpass.sh",
        "VSCODE_GIT_ASKPASS_NODE=/Applications/Visual Studio Code.app/Contents/Frameworks/Code Helper (Plugin).app/Contents/MacOS/Code Helper (Plugin)",
        "VSCODE_GIT_ASKPASS_EXTRA_ARGS=", "VSCODE_GIT_ASKPASS_MAIN=/Applications/Visual Studio Code.app/Contents/Resources/app/extensions/git/dist/askpass-main.js",
        "VSCODE_GIT_IPC_HANDLE=/var/folders/zz/zyxvpxvq6csfxvn_n000clnm0034xd/T/vscode-git-872da38eab.sock", "VSCODE_INJECTION=1",
        "ZDOTDIR=/Users/kruseva", "USER_ZDOTDIR=/Users/kruseva", "OLDPWD=/Users/kruseva",
        "_=/Users/kruseva/Desktop/AllProjects/pipex/./pipex", NULL
    };
    cmd->pipe = true;
    cmd->redir_in = false;
    cmd->redir_out = false;
    cmd->redir_append = false;
    cmd->file_in = NULL;
    cmd->file_out = NULL;
    cmd->end_of_cmd = false;
}

void init_second_cmd(t_cmd *cmd)
{
    cmd->delimiter = NULL;
    cmd->cmd = malloc(3 * sizeof(char **));
    cmd->cmd[0] = (char *[]) {"/bin/cat", NULL};
    cmd->cmd[1] = (char *[]) {"cat"};
    cmd->cmd[2] = NULL;

    cmd->envp =  (char *[]) {
        "TERM_PROGRAM=vscode", "TERM=xterm-256color", "SHELL=/bin/zsh",
        "TMPDIR=/var/folders/zz/zyxvpxvq6csfxvn_n000clnm0034xd/T/",
        "TERM_PROGRAM_VERSION=1.96.2", "TERM_SESSION_ID=53526D26-6581-48AF-B72E-1DA2B681CCC8",
        "USER=kruseva", "SSH_AUTH_SOCK=/private/tmp/com.apple.launchd.Jc8nhrjb3X/Listeners",
        "PATH=/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki:/Library/Apple/usr/bin:/Users/kruseva/valgrind/bin:/Users/kruseva/.local/bin:/Applications/Visual Studio Code.app/Contents/Resources/app/bin:/Users/kruseva/Library/Application Support/Code/User/globalStorage/github.copilot-chat/debugCommand:/Users/kruseva/.local/bin",
        "PWD=/Users/kruseva/Desktop/AllProjects/pipex", "LANG=en_US.UTF-8", "XPC_FLAGS=0x0",
        "XPC_SERVICE_NAME=0", "HOME=/Users/kruseva", "SHLVL=3", "LOGNAME=kruseva",
        "__CF_USER_TEXT_ENCODING=0x193AD:0x0:0x0", "ORIGINAL_XDG_CURRENT_DESKTOP=undefined",
        "COLORTERM=truecolor", "GIT_ASKPASS=/Applications/Visual Studio Code.app/Contents/Resources/app/extensions/git/dist/askpass.sh",
        "VSCODE_GIT_ASKPASS_NODE=/Applications/Visual Studio Code.app/Contents/Frameworks/Code Helper (Plugin).app/Contents/MacOS/Code Helper (Plugin)",
        "VSCODE_GIT_ASKPASS_EXTRA_ARGS=", "VSCODE_GIT_ASKPASS_MAIN=/Applications/Visual Studio Code.app/Contents/Resources/app/extensions/git/dist/askpass-main.js",
        "VSCODE_GIT_IPC_HANDLE=/var/folders/zz/zyxvpxvq6csfxvn_n000clnm0034xd/T/vscode-git-872da38eab.sock", "VSCODE_INJECTION=1",
        "ZDOTDIR=/Users/kruseva", "USER_ZDOTDIR=/Users/kruseva", "OLDPWD=/Users/kruseva",
        "_=/Users/kruseva/Desktop/AllProjects/pipex/./pipex", NULL
    };

    cmd->pipe = true;
    cmd->redir_in = false;
    cmd->redir_out = true;
    cmd->redir_append = false;
    cmd->file_in = NULL;
    cmd->file_out = "output.txt";
    cmd->end_of_cmd = true;
}


int ft_in_out(char *file, int mode)
{
    int fd;

    if (mode == 0)
    {
        fd = open(file, O_RDONLY);
        if (fd < 0)
            return (-1);
    }
    else if (mode == 1)
    {
        fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd < 0)
            return (-1);
    }
    else
    {
        fd = -1;
    }
    return (fd);
}

void find_right_exec(t_cmd *cmd, int fd_in, int fd_out)
{
    if (cmd->pipe)
        exec_pipes(cmd, fd_in, fd_out);
    else
        exec_cmd(cmd->cmd[0][0], cmd->cmd[1], cmd->envp);
}

void exec_cmd(char *cmd_path, char **cmd, char **envp)
{
    pid_t pid = fork();
    int status;

    if (pid == 0)
    {
        fprintf(stderr, "Executing: %s\n", cmd_path);
        for (int i = 0; cmd[i] != NULL; i++)
            printf("Arg[%d]: %s\n", i, cmd[i]);

        if (execve(cmd_path, cmd, envp) == -1)
        {
            perror("execve");
            exit(EXIT_FAILURE);
        }
    }
    else if (pid < 0)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else
    {
        waitpid(pid, &status, 0);
    }
}

void exec_pipes(t_cmd *cmd, int fd_in, int fd_out)
{
    int fd_pipe[2];
    pid_t pid;
    int status;

    if (pipe(fd_pipe) == -1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0)
    {
        if (fd_in != -1) 
        {
            dup2(fd_in, 0);
            close(fd_in);
        }
        else
        {
            dup2(fd_pipe[0], 0);
        }

        if (fd_out != -1) 
        {
            dup2(fd_out, 1);
            close(fd_out);
        }
        else
        {
            dup2(fd_pipe[1], 1);
        }

        close(fd_pipe[0]);
        close(fd_pipe[1]);

        // fprintf(stderr, "Executing (pipe): %s\n", cmd->cmd[0][0]);
        if (execve(cmd->cmd[0][0], cmd->cmd[1], cmd->envp) == -1)
        {
            perror("execve");
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        close(fd_pipe[1]);
        waitpid(pid, &status, 0);
    }
    waitpid(pid, &status, 0);
}

int main_execution(t_cmd *cmd)
{
    int fd_in = -1;
    int fd_out = -1;

    if (cmd->redir_in)
    {
        fd_in = ft_in_out(cmd->file_in, 0);
        if (fd_in < 0)
            return (1);
    }
    if (cmd->redir_out || cmd->redir_append)
    {
        int mode = 1;
        fd_out = ft_in_out(cmd->file_out, mode);
        if (fd_out < 0)
            return (1);
    }

    find_right_exec(cmd, fd_in, fd_out);
    return (0);
}

int main(void)
{
    t_cmd cmd;
    int command_done = -1;

    init_cmd(&cmd);
    command_done = main_execution(&cmd);

    if (command_done == 0) 
    {
        init_second_cmd(&cmd);
        main_execution(&cmd);
    }

    return (0);
}
