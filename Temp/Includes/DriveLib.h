/* Automation Studio generated header file */
/* Do not edit ! */
/* DriveLib 1.00.0 */

#ifndef _DRIVELIB_
#define _DRIVELIB_
#ifdef __cplusplus
extern "C" 
{
#endif
#ifndef _DriveLib_VERSION
#define _DriveLib_VERSION 1.00.0
#endif

#include <bur/plctypes.h>

#ifndef _BUR_PUBLIC
#define _BUR_PUBLIC
#endif
/* Datatypes and datatypes of function blocks */
typedef enum DoorStates
{	ST_INIT = 0,
	ST_UNKNOWN = 1,
	ST_OPEN = 2,
	ST_CLOSE = 3,
	ST_ACC_POS = 4,
	ST_ACC_NEG = 5,
	ST_POS = 6,
	ST_NEG = 7,
	ST_DEC_POS = 8,
	ST_DEC_NEG = 9
} DoorStates;

typedef struct DriveStateMashine
{
	/* VAR_INPUT (analog) */
	unsigned short state;
	/* VAR_OUTPUT (analog) */
	unsigned short command;
	signed short speed;
	/* VAR (analog) */
	unsigned char step;
	/* VAR_INPUT (digital) */
	plcbit enable;
	/* VAR (digital) */
	plcbit resetToggle;
} DriveStateMashine_typ;

typedef struct DoorStateMashine
{
	/* VAR_INPUT (analog) */
	unsigned short state;
	/* VAR_OUTPUT (analog) */
	signed short speed;
	unsigned short doorState;
	/* VAR (analog) */
	enum DoorStates current;
	/* VAR_INPUT (digital) */
	plcbit s0;
	plcbit s1;
	plcbit s2;
	plcbit s3;
	plcbit direction;
} DoorStateMashine_typ;

typedef struct LedStateMashine
{
	/* VAR_INPUT (analog) */
	unsigned short state;
	/* VAR_OUTPUT (analog) */
	signed short timer;
	/* VAR_OUTPUT (digital) */
	plcbit led1;
	plcbit led2;
	plcbit led3;
	plcbit led4;
} LedStateMashine_typ;



/* Prototyping of functions and function blocks */
_BUR_PUBLIC void DriveStateMashine(struct DriveStateMashine* inst);
_BUR_PUBLIC void DoorStateMashine(struct DoorStateMashine* inst);
_BUR_PUBLIC void LedStateMashine(struct LedStateMashine* inst);


#ifdef __cplusplus
};
#endif
#endif /* _DRIVELIB_ */

