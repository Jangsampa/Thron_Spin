#include "motor_player.h"

#include "main.h"


Motor_t motor[MOTOR_COUNT] =
{
	{Motor_1_STEP_GPIO_Port, Motor_1_STEP_Pin, 0, 0, 0},
	{Motor_2_STEP_GPIO_Port, Motor_2_STEP_Pin, 0, 0, 0},
};

static const Note_t gt1[] =
{
	{C4, NOTE_8}, {REST_FREQ, NOTE_8}, {B4, NOTE_8}, {REST_FREQ, NOTE_8},
	{A4, NOTE_8}, {B4, NOTE_8}, {REST_FREQ, NOTE_8}, {D5, NOTE_8},

	{REST_FREQ, NOTE_8}, {B4, NOTE_8}, {REST_FREQ, NOTE_8}, {A4, NOTE_8},
	{REST_FREQ, NOTE_8}, {B4, NOTE_8}, {A4, NOTE_8}, {G4, NOTE_8},

	{C4, NOTE_8}, {REST_FREQ, NOTE_8}, {B4, NOTE_8}, {REST_FREQ, NOTE_8},
	{A4, NOTE_8}, {B4, NOTE_8}, {REST_FREQ, NOTE_8}, {D5, NOTE_8},

	{REST_FREQ, NOTE_8}, {B4, NOTE_8}, {REST_FREQ, NOTE_8}, {A4, NOTE_8},
	{REST_FREQ, NOTE_8}, {B4, NOTE_8}, {A4, NOTE_8}, {G4, NOTE_8},

	{E4, NOTE_8}, {REST_FREQ, NOTE_8}, {E5, NOTE_8}, {REST_FREQ, NOTE_8},
	{D5, NOTE_8}, {B4, NOTE_8}, {REST_FREQ, NOTE_8}, {A4, NOTE_8},

	{REST_FREQ, NOTE_8}, {A4, NOTE_8}, {B4, NOTE_8}, {D5, NOTE_8},
	{REST_FREQ, NOTE_8}, {B4, NOTE_8}, {A4, NOTE_8}, {D4, NOTE_8},

	{E4, NOTE_8}, {REST_FREQ, NOTE_8}, {E5, NOTE_8}, {REST_FREQ, NOTE_8},
	{D5, NOTE_8}, {B4, NOTE_8}, {REST_FREQ, NOTE_8}, {A4, NOTE_8},

	{REST_FREQ, NOTE_8}, {A4, NOTE_8}, {B4, NOTE_8}, {D5, NOTE_8},
	{REST_FREQ, NOTE_8}, {E5, NOTE_16}, {D5, NOTE_16}, {B4, NOTE_8}, {REST_FREQ, NOTE_8},

	{C4, NOTE_8}, {REST_FREQ, NOTE_8}, {B4, NOTE_8}, {REST_FREQ, NOTE_8},
	{A4, NOTE_8}, {B4, NOTE_8}, {REST_FREQ, NOTE_8}, {D5, NOTE_8},

	{REST_FREQ, NOTE_8}, {B4, NOTE_8}, {REST_FREQ, NOTE_8}, {A4, NOTE_8},
	{REST_FREQ, NOTE_8}, {B4, NOTE_8}, {A4, NOTE_8}, {G4, NOTE_8},

	{C4, NOTE_8}, {REST_FREQ, NOTE_8}, {B4, NOTE_8}, {REST_FREQ, NOTE_8},
	{A4, NOTE_8}, {B4, NOTE_8}, {REST_FREQ, NOTE_8}, {D5, NOTE_8},

	{REST_FREQ, NOTE_8}, {B4, NOTE_8}, {REST_FREQ, NOTE_8}, {A4, NOTE_8},
	{REST_FREQ, NOTE_8}, {B4, NOTE_8}, {A4, NOTE_8}, {G4, NOTE_8},

	{E4, NOTE_8}, {REST_FREQ, NOTE_8}, {E5, NOTE_8}, {REST_FREQ, NOTE_8},
	{D5, NOTE_8}, {B4, NOTE_8}, {REST_FREQ, NOTE_8}, {A4, NOTE_8},

	{REST_FREQ, NOTE_8}, {A4, NOTE_8}, {B4, NOTE_8}, {D5, NOTE_8},
	{REST_FREQ, NOTE_8}, {B4, NOTE_8}, {A4, NOTE_8}, {D4, NOTE_8},

	{E4, NOTE_8}, {REST_FREQ, NOTE_8}, {E5, NOTE_8}, {REST_FREQ, NOTE_8},
	{D5, NOTE_8}, {B4, NOTE_8}, {D5, NOTE_8}, {E5, NOTE_4},

	{G5, NOTE_8}, {A5, NOTE_8}, {B5, NOTE_8}, {D6, NOTE_8},
	{B5, NOTE_8}, {A5, NOTE_8}, {B5, NOTE_8}, {REST_FREQ, NOTE_8},
};

void MotorPlayer_Init(void)
{
	LL_GPIO_ResetOutputPin(Motor_1_STEP_GPIO_Port, Motor_1_STEP_Pin);
	LL_GPIO_ResetOutputPin(Motor_1_DIR_GPIO_Port, Motor_1_DIR_Pin);
	LL_GPIO_ResetOutputPin(Motor_1_EN_GPIO_Port, Motor_1_EN_Pin);

	LL_GPIO_ResetOutputPin(Motor_2_STEP_GPIO_Port, Motor_2_STEP_Pin);
	LL_GPIO_ResetOutputPin(Motor_2_DIR_GPIO_Port, Motor_2_DIR_Pin);
	LL_GPIO_ResetOutputPin(Motor_2_EN_GPIO_Port, Motor_2_EN_Pin);

	LL_TIM_EnableIT_UPDATE(TIM2);
	LL_TIM_EnableCounter(TIM2);
}

void Motor_SetFreq(UINT8 ch, UINT16 freq)
{
	if(ch >= MOTOR_COUNT)
	{
		return;
	}

    if(freq == 0)
    {
        motor[ch].inc = 0;
        motor[ch].acc = 0;
        motor[ch].state = 0;
        LL_GPIO_ResetOutputPin(motor[ch].step_port, motor[ch].step_pin);
        return;
    }

    motor[ch].inc = (UINT32)(((UINT64)freq * 2ULL * 0xFFFFFFFFULL) / ISR_FREQ_HZ);
}

void MotorPlayer_Play(void)
{
    for(UINT16 i = 0; i < sizeof(gt1) / sizeof(gt1[0]); i++)
    {
        Motor_SetFreq(0, gt1[i].freq);       // 모터1: Gt1
        Motor_SetFreq(1, gt1[i].freq * 2);   // 모터2: 한 옥타브 위

        LL_mDelay(gt1[i].ms);
    }

    Motor_SetFreq(0, 0);
    Motor_SetFreq(1, 0);
    LL_mDelay(1000);
}

// void MotorPlayer_TIM2_IRQHandler(void)
// {
//	 if(!LL_TIM_IsActiveFlag_UPDATE(TIM2))
//	 {
//		 return;
//	 }

//	 LL_TIM_ClearFlag_UPDATE(TIM2);

//	 for(UINT8 i = 0; i < MOTOR_COUNT; i++)
//	 {
//		 if(motor[i].inc == 0)
//		 {
//			 continue;
//		 }

//		 UINT32 old = motor[i].acc;
//		 motor[i].acc += motor[i].inc;

//		 if(motor[i].acc < old)
//		 {
//			 if(motor[i].state)
//			 {
//				 LL_GPIO_ResetOutputPin(motor[i].step_port, motor[i].step_pin);
//				 motor[i].state = 0;
//			 }
//			 else
//			 {
//				 LL_GPIO_SetOutputPin(motor[i].step_port, motor[i].step_pin);
//				 motor[i].state = 1;
//			 }
//		 }
//	 }
// }
