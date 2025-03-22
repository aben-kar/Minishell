#include "shell.h"

char *cmd_executable(char *cmd, char **envp)
{
    if ((access(cmd, F_OK | X_OK)) == 0)
        return (cmd);
    char **directory = get_path(envp);
    int i = 0;
    while (directory[i])
    {
        char *add_slash = ft_strjoin(directory[i], "/");
        char *cmd_path = ft_strjoin(add_slash, cmd);
        if ((access(cmd_path, F_OK | X_OK)) == 0)
            return(cmd_path);
        i++;
    }
    return (NULL);
}

int main(int ac, char **av, char **envp)
{
    if (ac > 1)
    {
        int in_file = open(av[1], O_RDONLY, 0644);
        dup2(in_file, STDIN_FILENO);
        char *cmd = cmd_executable(av[2], envp);
        if (cmd)
            execve(cmd, &av[2], envp);
    }
    return 0;
}