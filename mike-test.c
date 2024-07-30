#include "main.h"
int main(void)
{
	if (isatty(0))
	{
		loop_for_interactive();
	}
	else
	{
		non_interactive();
	}
	return (0);
}
