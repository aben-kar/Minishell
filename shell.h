#ifndef SHELL_H
#define SHELL_H


# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <stdint.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include "libft/libft.h"

char **get_path(char **envp);

#endif