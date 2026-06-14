#include <stdio.h>

int main(int ac, char **av, char **envp)
{
    // envp[i] が NULL になるまで回す
    for (int i = 0; envp[i] != NULL; i++)
    {
        printf("envp[%d]: %s\n", i, envp[i]);
    }
    return 0;
}
