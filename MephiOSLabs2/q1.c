#include <stdio.h>
#include <stdlib.h>

/*
Написать программу, которая добавляет новые строки в среду процесса.
*/

extern char** environ;
int q1(char* env[])
{
    printf("=== question 1 start ===\n\n");
    
    char firstVarName[] = "Var1";
    char firstVarValue[] = "Var1Value";

    char secondVarName[] = "Var2";
    char secondVarNameValue[] = "Var2=Var2Value";

    printf("Current environment:\n");
    printCurrentEnvironment(environ);
    printf("\n");

    setenv(firstVarName, firstVarValue, 0);

    printf("Added first variable: %s=%s\n", firstVarName, getenv(firstVarName));
    printf("\n");

    putenv(secondVarNameValue);

    printf("Added first variable: %s=%s\n", secondVarName, getenv(secondVarName));
    printf("\n");

    printf("Environment after two variables add:\n");
    printCurrentEnvironment(environ);
    printf("\n");

    unsetenv(firstVarName);
    printf("Removed variable %s\n", firstVarName);
    printf("\n");

    printf("Environment after first variable removal:\n");
    printCurrentEnvironment(environ);

    printf("\n==== question 1 end ====\n");

    return 0;
}

int printCurrentEnvironment(char* env[])
{
    for (char** v = env; *v != 0; v++)
        printf("%s\n", *v);

    return catch();
}