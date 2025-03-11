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
    int k = 0;
    bool found_var = false;
    while (cmd->cmd[i])
    {
        while(cmd->cmd[i][k] != '\0' && cmd->cmd[i][k] != '\'')
        {
            if (cmd->cmd[i][k] == '$')
            {
                found_var = true;
                char *env_var = search_env_var(*env_list, cmd->cmd[i]);
                if (env_var == NULL)
                    return;
                printf("%s", env_var);
                k += ft_strlen(env_var);
            }
            else if (!found_var)
                printf("%s", cmd->cmd[i]);
            k++;
        }
        if (cmd->cmd[i][k] == '\'')
        {
            while (cmd->cmd[i][k] != '\0')
            {
                if (cmd->cmd[i][k] != '\'')
                printf("%c", cmd->cmd[i][k]);
                k++;
            }
        }
        i++;
    }
    printf("\n");
}