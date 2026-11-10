#include <bur/plctypes.h>

#ifdef __cplusplus
extern "C"
{
#endif
	#include "DriveLib.h"
#ifdef __cplusplus
};
#endif

/* Cyclic#1 = 2 ms  ->  500 ms half-period of 1 Hz blinking = 250 calls */
#define BLINK_HALF_PERIOD 250

void LedStateMashine(struct LedStateMashine* inst)
{
	BOOL l1 = 0, l2 = 0, l3 = 0, l4 = 0;

	if (inst->state == ST_UNKNOWN)
	{
		/* all LEDs blink at 1 Hz while the door looks for its position */
		inst->timer++;
		if (inst->timer >= 2 * BLINK_HALF_PERIOD)
			inst->timer = 0;
		l1 = l2 = l3 = l4 = (inst->timer < BLINK_HALF_PERIOD);
	}
	else
	{
		inst->timer = 0;
		switch (inst->state)
		{
			case ST_OPEN:
			case ST_INIT:
				break;							/* 0000 */

			case ST_ACC_POS:
			case ST_DEC_NEG:
				l1 = 1;							/* 1000 */
				break;

			case ST_POS:
			case ST_NEG:
				l1 = 1; l2 = 1;					/* 1100 */
				break;

			case ST_DEC_POS:
			case ST_ACC_NEG:
				l1 = 1; l2 = 1; l3 = 1;			/* 1110 */
				break;

			case ST_CLOSE:
				l1 = 1; l2 = 1; l3 = 1; l4 = 1;	/* 1111 */
				break;

			default:
				break;
		}
	}

	inst->led1 = l1;
	inst->led2 = l2;
	inst->led3 = l3;
	inst->led4 = l4;
}
