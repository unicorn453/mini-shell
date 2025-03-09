#include "../mini_shell.h"

char *search_var(t_env *env_list, char *token)
{
    t_env *temp;
    char *placeholder;

    temp = env_list;
    while (temp)
    {
        if (ft_strncmp(temp->key, token, ft_strlen(token)) == 0)
        {
            placeholder = ft_strdup(temp->value);
            if (placeholder == NULL)
                return (perror("Minishell: memory allocation error"), NULL);
            return (placeholder);
        }
        temp = temp->next;
    }
    return (NULL);
}

void echo_call_check(t_cmd *cmd, t_env **env_list)
{
    int i = 1;
    while (cmd->cmd[i])
    {
        if (cmd->cmd[i][0] == '$')
        {
            char *env_var = search_var(*env_list, cmd->cmd[i] + 1);
            if (env_var)
                printf("%s ", env_var);
        }
        else
            printf("%s ", cmd->cmd[i]);
        i++;
    }
    printf("\n");
}