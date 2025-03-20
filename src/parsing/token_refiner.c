/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_refiner.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrendaf <dtrendaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 22:04:59 by dtrendaf          #+#    #+#             */
/*   Updated: 2025/03/19 22:33:59 by dtrendaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

// t_token *new_token(char *value)
// {
//     t_token *new;
	
// 	new = gc_malloc(sizeof(t_token));
//     CHECK(new == NULL, 1);
// 	new->in_qoutes = false;
//     new->value = ft_strdup(value);
// 	CHECK(new->value == NULL, 1);
// 	gc_track(new->value);
//     new->next = NULL;
//     return new;
// }

// void append_token(t_token **head, char *value)
// {
//     t_token *new;
// 	t_token *temp;
	
// 	new = new_token(value);
//     if (*head == NULL)
//         *head = new;
//     else
// 	{
//         temp = *head;
//         while (temp->next != NULL)
//             temp = temp->next;
//         temp->next = new;
//     }
// }
// void print_tokens(t_token *head) {
//     while (head != NULL) {
//         printf("New shit %s\n", head->value);
//         head = head->next;
//     }
// }

// void split_tokens(char **tokens, t_token **refined_tokens) {
//     static char *charset[] = {"<<", "<", ">>", ">", "|", "$?", NULL};
//     int i = 0, j, start, len;
//     char *no_charse_str;
//     bool in_single = false, in_double = false;
    
//     while (tokens[i]) {
//         start = 0;
//         len = strlen(tokens[i]);
//         no_charse_str = ft_strdup("");
//         CHECK(no_charse_str == NULL, 1);
        
//         while (start < len) {
//             // Toggle quote state
//             if (tokens[i][start] == '\'' && !in_double)
//                 in_single = !in_single;
//             else if (tokens[i][start] == '"' && !in_single)
//                 in_double = !in_double;
            
//             // Always add the current character to the token
//             char temp[2] = {tokens[i][start], '\0'};
//             char *new_str = ft_strjoin(no_charse_str, temp);
//             CHECK(new_str == NULL, 1);
//             free(no_charse_str);
//             no_charse_str = new_str;
            
//             // Only process operators if we're not inside quotes and the next character isn't part of a quoted section
//             if (!in_single && !in_double && start + 1 < len) {
//                 j = 0;
//                 while (charset[j]) {
//                     int op_len = strlen(charset[j]);
//                     if (start + op_len <= len && strncmp(&tokens[i][start + 1], charset[j], op_len) == 0) {
//                         // Complete the current token
//                         if (*no_charse_str) {
//                             append_token(refined_tokens, no_charse_str);
//                             free(no_charse_str);
//                             no_charse_str = ft_strdup("");
//                             CHECK(no_charse_str == NULL, 1);
//                         }
//                         break;
//                     }
//                     j++;
//                 }
//             }
            
//             start++;
//         }
        
//         if (*no_charse_str) {
//             append_token(refined_tokens, no_charse_str);
//         }
//         free(no_charse_str);
//         i++;
//     }
// }

t_token *new_token(char *value)
{
    t_token *new;
    
    new = gc_malloc(sizeof(t_token));
    CHECK(new == NULL, 1);
    new->value = ft_strdup(value);
    CHECK(new->value == NULL, 1);
    gc_track(new->value);
    new->next = NULL;
    return new;
}

void append_token(t_token **head, char *value)
{
    t_token *new;
    t_token *temp;
    
    if (value[0] == '\0')
    {
        return ;
    }
    new = new_token(value);
    if (*head == NULL)
        *head = new;
    else
    {
        temp = *head;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = new;
    }
}
void split_tokens(char **tokens, t_token **refined_tokens) {
    static char *charset[] = {"<<", "<", ">>", ">", "|", "$?", NULL};
    int i = 0, j, start, len;
    char *no_charse_str;
    bool in_single = false, in_double = false;

    while (tokens[i]) {
        start = 0;
        len = strlen(tokens[i]);
        no_charse_str = ft_strdup("");
        CHECK(no_charse_str == NULL, 1);
        while (start < len) {
            if (tokens[i][start] == '\'' && !in_double) {
                in_single = !in_single;
            } else if (tokens[i][start] == '"' && !in_single) {
                in_double = !in_double;
            }
            if (!in_single && !in_double) {
                j = 0;
                while (charset[j]) {
                    int op_len = strlen(charset[j]);
                    if (strncmp(&tokens[i][start], charset[j], op_len) == 0) {
                        if (*no_charse_str) {
                            append_token(refined_tokens, no_charse_str);
                            free(no_charse_str);
                            no_charse_str = ft_strdup("");
                            CHECK(no_charse_str == NULL, 1);
                        }
                        append_token(refined_tokens, charset[j]);
                        start += op_len;
                        goto next_iteration;
                    }
                    j++;
                }
            }
            char temp[2] = {tokens[i][start], '\0'};
            char *new_str = ft_strjoin(no_charse_str, temp);
            CHECK(new_str == NULL, 1);
            free(no_charse_str);
            no_charse_str = new_str;
            start++;
        next_iteration:;
        }
        if (*no_charse_str) {
            append_token(refined_tokens, no_charse_str);
        }
        free(no_charse_str);
        i++;
    }
}

// void split_tokens(char **tokens, t_token **refined_tokens) {
//     static char *charset[] = {"<<", "<", ">>", ">", "|", "$?", NULL};
//     int i = 0, j, start, len;
//     char *no_charse_str;
//     bool in_single = false, in_double = false;
    
//     while (tokens[i]) {
//         start = 0;
//         len = strlen(tokens[i]);
//         no_charse_str = ft_strdup("");
//         CHECK(no_charse_str == NULL, 1);
        
//         while (start < len) {
//             // Toggle quote state
//             if (tokens[i][start] == '\'' && !in_double)
//                 in_single = !in_single;
//             else if (tokens[i][start] == '"' && !in_single)
//                 in_double = !in_double;
            
//             // Always add the current character to the token
//             char temp[2] = {tokens[i][start], '\0'};
//             char *new_str = ft_strjoin(no_charse_str, temp);
//             CHECK(new_str == NULL, 1);
//             free(no_charse_str);
//             no_charse_str = new_str;
            
//             // Only process operators if we're not inside quotes and the next character isn't part of a quoted section
//             if (!in_single && !in_double && start + 1 < len) {
//                 j = 0;
//                 while (charset[j]) {
//                     int op_len = strlen(charset[j]);
//                     if (start + op_len <= len && strncmp(&tokens[i][start + 1], charset[j], op_len) == 0) {
//                         // Complete the current token
//                         if (*no_charse_str) {
//                             append_token(refined_tokens, no_charse_str);
//                             free(no_charse_str);
//                             no_charse_str = ft_strdup("");
//                             CHECK(no_charse_str == NULL, 1);
//                         }
//                         break;
//                     }
//                     j++;
//                 }
//             }
//             start++;
//         }
//         if (*no_charse_str) {
//             append_token(refined_tokens, no_charse_str);
//         }
//         free(no_charse_str);
//         i++;
//     }
// }

// void print_tokens(t_token *head) {
//     while (head != NULL) {
//         printf("New shit %s (in_quotes: %s)\n", head->value, 
        
//         head = head->next;
//     }
// }

// void split_tokens(char **tokens, t_token **refined_tokens) 
// {
//     static char *charset[] = {"<<", "<", ">>", ">", "|", "$?", NULL};
//     int i = 0, j, start, len;
//     char *no_charse_str;
//     bool in_single = false, in_double = false;
//     bool was_in_quotes = false;
    
//     while (tokens[i]) {
//         start = 0;
//         len = strlen(tokens[i]);
//         no_charse_str = ft_strdup("");
//         CHECK(no_charse_str == NULL, 1);
//         was_in_quotes = false;
        
//         while (start < len) {
//             // Toggle quote state and track if this token was ever in quotes
//             if (tokens[i][start] == '\'' && !in_double) {
//                 in_single = !in_single;
//                 was_in_quotes = true;
//             }
//             else if (tokens[i][start] == '"' && !in_single) {
//                 in_double = !in_double;
//                 was_in_quotes = true;
//             }
            
//             // Always add the current character to the token
//             char temp[2] = {tokens[i][start], '\0'};
//             char *new_str = ft_strjoin(no_charse_str, temp);
//             CHECK(new_str == NULL, 1);
//             free(no_charse_str);
//             no_charse_str = new_str;
            
//             // Only process operators if we're not inside quotes and the next character isn't part of a quoted section
//             if (!in_single && !in_double && start + 1 < len) {
//                 j = 0;
//                 while (charset[j]) {
//                     int op_len = strlen(charset[j]);
//                     if (start + op_len <= len && strncmp(&tokens[i][start + 1], charset[j], op_len) == 0) {
//                         // Complete the current token
//                         if (*no_charse_str) {
//                             append_token(refined_tokens, no_charse_str, was_in_quotes);
//                             free(no_charse_str);
//                             no_charse_str = ft_strdup("");
//                             CHECK(no_charse_str == NULL, 1);
//                             was_in_quotes = false; // Reset for the next token
//                         }
//                         break;
//                     }
//                     j++;
//                 }
//             }
            
//             start++;
//         }
        
//         if (*no_charse_str) {
//             append_token(refined_tokens, no_charse_str, was_in_quotes);
//         }
//         free(no_charse_str);
//         i++;
        
//         // Reset quote state between tokens
//         in_single = false;
//         in_double = false;
//     }
// }

// void split_tokens(char **tokens, t_token **refined_tokens)
// {
//     static char *charset[] = {"<<", "<", ">>", ">", "|", "$?", NULL};
//     int i = 0;
//     int j;
//     int start;
//     int len;
//     char *no_charse_str;

//     while (tokens[i])
//     {
//         start = 0;
//         len = strlen(tokens[i]);
//         no_charse_str = ft_strdup("");

//         while (start < len)
//         {
//             j = 0;
//             while (charset[j])
//             {
//                 int op_len = strlen(charset[j]);

//                 if (strncmp(&tokens[i][start], charset[j], op_len) == 0)
//                 {
//                     if (*no_charse_str)
//                     {
//                         append_token(refined_tokens, no_charse_str);
//                         free(no_charse_str);
//                         no_charse_str = ft_strdup("");
//                     }

//                     append_token(refined_tokens, charset[j]);
//                     start += op_len;
//                     break;
//                 }
//                 j++;
//             }

//             if (!charset[j])
//             {
//                 char temp[2] = {tokens[i][start], '\0'};
//                 char *new_str = ft_strjoin(no_charse_str, temp);
// 				CHECK(new_str == NULL, 1);
//                 free(no_charse_str);
//                 no_charse_str = new_str;
//                 start++;
//             }
//         }

//         if (*no_charse_str)
//         {
//             append_token(refined_tokens, no_charse_str);
//             // free(no_charse_str);
//         }

//         i++;
//     }
// }

// static int ft_strnstr_plus(const char *haystack, const char *needle, size_t len)
// {
// 	size_t	i;
// 	size_t	j;

// 	if (needle[0] == '\0')
// 		return (-1);
// 	i = 0;
// 	while (i < len && haystack[i] != '\0')
// 	{
// 		if (haystack[i] == needle[0])
// 		{
// 			j = 0;
// 			while (needle[j] != '\0' && haystack[i + j] == needle[j] && (i
// 					+ j) < len)
// 				j++;
// 			if (needle[j] == '\0')
// 				return ((int)i);
// 		}
// 		i++;
// 	}
// 	return (-1);
// }

// bool	split_tokes(t_token	**head, char *token, char *charset) 
// {
// 	int 	result; // res can be moved to char *token_refiner() if needed for norm
// 	char	*temp;
	
// 	temp = NULL;
// 	result = ft_strnstr_plus(token, charset, ft_strlen(token));
// 	if (result > -1)
// 	{
// 		if (result > 0) // if there is something before the "charset"
// 		{
// 			append_token(head, temp = ft_substr(token, 0, result));
// 			free(temp);
// 			append_token(head, temp = ft_substr(token, result, ft_strlen(charset)));
// 			free(temp);
// 			temp = NULL;
// 			if (result + ft_strlen(charset) < ft_strlen(token)) // if there is something after the charset
// 				append_token(head, temp = ft_substr(token,result + ft_strlen(charset), ft_strlen(token)));
// 			return(free(temp), true);
// 		}
// 			if (ft_strlen(token) == ft_strlen(charset))// if the token is only the charset
// 				return (true); // def case gets handelt in char *token_refiner() 
// 			append_token(head, temp = ft_substr(token, 0, ft_strlen(charset))); // charset is at the start
// 				free (temp);
// 			temp = ft_substr(token, ft_strlen(charset),(ft_strlen(token) - ft_strlen(charset))); // substring the rest
// 			append_token(head, temp);
// 			return (free(temp), true);	// false == no def case
// 	}
// 	return(false);
// }

// void print_tokens(t_token *head) {
//     while (head != NULL) {
//         printf("New shit %s\n", head->value);
//         head = head->next;
//     }
// }

// char	*token_refiner(char **tokens,t_token	**head)
// {
// 	static char	*charset[] = {"<<", "<", ">>", ">", "|", "$?", NULL};
// 	int			j;
// 	int			i;
	
// 	i = -1;
// 	while (tokens[++i])
// 	{
// 		j = -1;
// 		while (charset[++j])
// 			split_tokes(head, tokens[i], charset[j]);
// 		// if (default_case == true)
// 		// 	append_token(&head, tokens[i]);
// 	}
// 	print_tokens(*head);
// 	return(NULL);
// }