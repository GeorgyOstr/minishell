#include "shell.h"
#include "token.h"
#include "command.h"

static void test_print_tokens(t_token *tokens)
{
    while(tokens)
    {
        printf("value=[%s] type=%d\n", tokens->value, tokens->type);
        tokens = tokens->next;
    }
}

static void	print_indent(int depth)
{
	while (depth--)
		printf("  ");
}

static void	test_print_ast(t_ast *node, int depth)
{
	int	i;

	if (!node)
		return ;
	print_indent(depth);
	if (node->type == NODE_PIPE)
		printf("PIPE\n");
	else if (node->type == NODE_REDIR)
		printf("REDIR (%d)\n", node->redir_type);
	else if (node->type == NODE_CMD)
	{
		printf("CMD:");
		i = 0;
		while (node->argv && node->argv[i])
		{
			printf(" %s", node->argv[i]);
			i++;
		}
		printf("\n");
	}
	if (node->file)
	{
		print_indent(depth + 1);
		printf("FILE: %s\n", node->file);
	}
	test_print_ast(node->left, depth + 1);
	test_print_ast(node->right, depth + 1);
}