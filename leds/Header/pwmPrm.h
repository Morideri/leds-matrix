/*
 * pwmPrm.h
 *
 * Created: 29/05/2024 14:49:49
 *  Author: gabri
 */ 


//-------------------------------------- Include Files ----------------------------------------------------------------
#include "..\Header\cTypes.h"


#ifndef PWMPRM_H_
#define PWMPRM_H_

#define CONFIG_PWM0 DISABLED
#define CONFIG_PWM1 DISABLED
#define CONFIG_PWM2 ENABLED		//OC1A
#define CONFIG_PWM3 DISABLED
#define CONFIG_PWM4 DISABLED
#define CONFIG_PWM5 ENABLED		//OC2B

#define PWM0_FREQUENCY 0
#define PWM1_FREQUENCY 0
#define PWM2_FREQUENCY 0
#define PWM3_FREQUENCY 0
#define PWM4_FREQUENCY 0
#define PWM5_FREQUENCY 0




#endif /* PWMPRM_H_ */