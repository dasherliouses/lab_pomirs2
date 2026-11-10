#include <bur/plctypes.h>
#ifdef _DEFAULT_INCLUDES
	#include <AsDefault.h>
#endif

void _CYCLIC ProgramCyclic(void)
{
	/* 1. drive initialization sequence (status word -> control word) */
	stateMachine.enable = enable;
	DriveStateMashine(&stateMachine);

	/* 2. door logic: sensors + direction switch + drive status -> speed setpoint */
	doorSM.state = stateMachine.state;
	DoorStateMashine(&doorSM);
	stateMachine.speed = doorSM.speed;

	/* 3. indication */
	ledSM.state = doorSM.doorState;
	LedStateMashine(&ledSM);
}
