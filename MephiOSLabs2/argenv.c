#include <stdio.h>
#include <stdlib.h>

extern char** environ;
int argenv(int argc, char* argv[])
{
	printf("Current process name: %s\n", argv[0]);
	printArgs(argc, argv);
	printCurrentEnvironment(environ);
	printf("\n");
}

printArgs(int argc, char* argv[])
{
	for (int i = 1; i < argc; i++)
		printf("Arg %d value = %s\n", i, argv[i]);
}