#include <bur/plctypes.h>

#ifdef __cplusplus
extern "C"
{
#endif
	#include "DriveLib.h"
#ifdef __cplusplus
};
#endif

#define STATE_MASK        0x006F
#define STATE_OP_ENABLED  0x0027   /* drive: operation enabled */

#define SPEED_SLOW        150      /* rpm, sections s0-s1 and s2-s3 and homing */
#define SPEED_FAST        800      /* rpm, section s1-s2 (nominal speed is 890 rpm) */

/*
 Geometry: s0 - fully open end, s3 - fully closed end.
 direction = 0 : open  (move towards s0)
 direction = 1 : close (move towards s3)
 Positive speed = motion s0 -> s3 (ST_*_POS), negative speed = motion s3 -> s0 (ST_*_NEG).
*/
void DoorStateMashine(struct DoorStateMashine* inst)
{
	/* drive is not ready: stop and wait, position becomes unknown again */
	if ((inst->state & STATE_MASK) != STATE_OP_ENABLED)
	{
		inst->current   = ST_INIT;
		inst->speed     = 0;
		inst->doorState = ST_INIT;
		return;
	}

	switch (inst->current)
	{
		case ST_INIT:
			inst->speed = 0;
			inst->current = ST_UNKNOWN;
			break;

		case ST_UNKNOWN:	/* creep in the requested direction until an end sensor is found */
			inst->speed = inst->direction ? SPEED_SLOW : -SPEED_SLOW;
			if (inst->s0 && !inst->direction)
				inst->current = ST_OPEN;
			else if (inst->s3 && inst->direction)
				inst->current = ST_CLOSE;
			break;

		case ST_OPEN:
			inst->speed = 0;
			if (inst->direction)
				inst->current = ST_ACC_POS;
			break;

		case ST_CLOSE:
			inst->speed = 0;
			if (!inst->direction)
				inst->current = ST_ACC_NEG;
			break;

		/* ---- closing: s0 -> s3 ---- */
		case ST_ACC_POS:
			inst->speed = SPEED_SLOW;
			if (inst->s1)
				inst->current = ST_POS;
			else if (!inst->direction)
				inst->current = ST_DEC_NEG;	/* reverse before s1 */
			break;

		case ST_POS:
			inst->speed = SPEED_FAST;
			if (inst->s2)
				inst->current = ST_DEC_POS;
			else if (!inst->direction)
				inst->current = ST_NEG;
			break;

		case ST_DEC_POS:
			inst->speed = SPEED_SLOW;
			if (inst->s3)
				inst->current = ST_CLOSE;
			else if (!inst->direction)
				inst->current = ST_ACC_NEG;
			break;

		/* ---- opening: s3 -> s0 ---- */
		case ST_ACC_NEG:
			inst->speed = -SPEED_SLOW;
			if (inst->s2)
				inst->current = ST_NEG;
			else if (inst->direction)
				inst->current = ST_DEC_POS;
			break;

		case ST_NEG:
			inst->speed = -SPEED_FAST;
			if (inst->s1)
				inst->current = ST_DEC_NEG;
			else if (inst->direction)
				inst->current = ST_POS;
			break;

		case ST_DEC_NEG:
			inst->speed = -SPEED_SLOW;
			if (inst->s0)
				inst->current = ST_OPEN;
			else if (inst->direction)
				inst->current = ST_ACC_POS;
			break;

		default:
			inst->current = ST_INIT;
			break;
	}

	inst->doorState = inst->current;
}
