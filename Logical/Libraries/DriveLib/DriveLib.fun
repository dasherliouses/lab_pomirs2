FUNCTION_BLOCK DriveStateMashine
	VAR_INPUT
		state : UINT;
		enable : BOOL;
	END_VAR
	VAR_OUTPUT
		command : UINT;
		speed : INT;
	END_VAR
	VAR
		step : USINT;
		resetToggle : BOOL;
	END_VAR
END_FUNCTION_BLOCK

FUNCTION_BLOCK DoorStateMashine
	VAR_INPUT
		state : UINT;
		s0 : BOOL;
		s1 : BOOL;
		s2 : BOOL;
		s3 : BOOL;
		direction : BOOL;
	END_VAR
	VAR_OUTPUT
		speed : INT;
		doorState : UINT;
	END_VAR
	VAR
		current : DoorStates;
	END_VAR
END_FUNCTION_BLOCK

FUNCTION_BLOCK LedStateMashine
	VAR_INPUT
		state : UINT;
	END_VAR
	VAR_OUTPUT
		led1 : BOOL;
		led2 : BOOL;
		led3 : BOOL;
		led4 : BOOL;
		timer : INT;
	END_VAR
END_FUNCTION_BLOCK
