#include "../minishell.h"

void	bash_syntax_error(const char *token)
{
    if (!token)
    {
        write(2, "bash: syntax error near unexpected token `newline'\n", 50);
        return;
    }
    write(2, "bash: syntax error near unexpected token `", 42);
    write(2, token, ft_strlen(token));
    write(2, "'\n", 2);
}

void	bash_unclosed_quote_error(char quote)
{
    write(2, "bash: unexpected EOF while looking for matching `", 48);
    write(2, &quote, 1);
    write(2, "'\n", 2);
    write(2, "bash: syntax error: unexpected end of file\n", 43);
}
