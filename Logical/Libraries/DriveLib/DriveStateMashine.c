#include <bur/plctypes.h>

#ifdef __cplusplus
extern "C"
{
#endif
	#include "DriveLib.h"
#ifdef __cplusplus
};
#endif

/* Drive control word commands (CiA 402 style, ACOPOSinverter) */
#define CMD_SHUTDOWN      0x0006
#define CMD_SWITCH_ON     0x0007
#define CMD_ENABLE        0x000F
#define CMD_FAULT_RESET   0x0080

/* Status word (ETAD) decoding: state & 0x6F */
#define STATE_MASK        0x006F
#define STATE_SWITCHED_ON 0x0021   /* "ready to switch on" - reached after CMD_SHUTDOWN */
#define STATE_READY       0x0023   /* "switched on"        - reached after CMD_SWITCH_ON */
#define STATE_FAULT_BIT   0x0008

/* internal steps */
#define DRV_DISABLED      0
#define DRV_SWITCHED_ON   1
#define DRV_READY         2

/* Drive initialization state machine: DISABLED -> SWITCHED_ON -> READY */
void DriveStateMashine(struct DriveStateMashine* inst)
{
	/* fault: pulse the fault-reset bit and restart the sequence */
	if (inst->state & STATE_FAULT_BIT)
	{
		inst->resetToggle = !inst->resetToggle;
		inst->command = inst->resetToggle ? CMD_FAULT_RESET : 0;
		inst->speed   = 0;
		inst->step    = DRV_DISABLED;
		return;
	}

	/* enable removed in any step: shut the drive down */
	if (!inst->enable)
	{
		inst->step = DRV_DISABLED;
	}

	switch (inst->step)
	{
		case DRV_DISABLED:
			inst->command = CMD_SHUTDOWN;
			inst->speed   = 0;
			if (inst->enable && (inst->state & STATE_MASK) == STATE_SWITCHED_ON)
				inst->step = DRV_SWITCHED_ON;
			break;

		case DRV_SWITCHED_ON:
			inst->command = CMD_SWITCH_ON;
			if (inst->enable && (inst->state & STATE_MASK) == STATE_READY)
				inst->step = DRV_READY;
			break;

		case DRV_READY:
			/* operation enabled; speed is set from outside (door FB) */
			inst->command = CMD_ENABLE;
			break;

		default:
			inst->step = DRV_DISABLED;
			break;
	}
}
