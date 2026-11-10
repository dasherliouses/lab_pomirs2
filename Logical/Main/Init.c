#include <bur/plctypes.h>
#ifdef _DEFAULT_INCLUDES
	#include <AsDefault.h>
#endif

void _INIT ProgramInit(void)
{
	enable = 1;		/* allow the drive initialization sequence at power-on */
}
