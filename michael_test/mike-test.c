#include "main.h"
int main(void)
{
	if (isatty(0))
	{
		printf("interactive\n");
		loop_for_interactive();
	}
	else
	{
		printf("non-interactive\n");
		non_interactive();
	}
	return (0);
}
