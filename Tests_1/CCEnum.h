#pragma once


enum CC_STATE : unsigned char
{
	CC_STATE_IDLE,
	CC_STATE_START,
	CC_STATE_END,
	CC_STATE_CANCEL_SKILL,
	CC_STATE_PROCESS_SKILL_LOCK,
	CC_STATE_PROCESS_SKILL_UNLOCK,
	CC_STATE_PROCESS_SKILL_CLEAR,
	CC_STATE_PROCESS_SKILL_CANCEL
};
