/* ----------------------------------------------------------------------      
* Copyright (C) 2011 ARM Limited. All rights reserved. 
*      
* $Date:        15. December 2011   
* $Revision: 	V2.0.0  
*      
* Project:      Cortex-R DSP Library 
* Title:	    arm_pid_init_q31.c      
*      
* Description:	Q31 PID Control initialization function       
*      
* Target Processor:          Cortex-R4/R5
*
* Version 1.0.0 2011/03/08
*     Alpha release.
*
* Version 1.0.1 2011/09/30
*     Beta release.
*
* Version 2.0.0 2011/12/15
*     Final release. 
* 
* ------------------------------------------------------------------- */     
#include "arm_math.h"     
     
 /**      
 * @addtogroup PID      
 * @{      
 */     
     
/**      
 * @brief  Initialization function for the Q31 PID Control.     
 * @param[in,out] *S points to an instance of the Q31 PID structure.     
 * @param[in]     resetStateFlag  flag to reset the state. 0 = no change in state 1 = reset the state.     
 * @return none.      
 * \par Description:     
 * \par      
 * The <code>resetStateFlag</code> specifies whether to set state to zero or not. \n     
 * The function computes the structure fields: <code>A0</code>, <code>A1</code> <code>A2</code>      
 * using the proportional gain( \c Kp), integral gain( \c Ki) and derivative gain( \c Kd)      
 * also sets the state variables to all zeros.      
 */      
      
void arm_pid_init_q31(      
  arm_pid_instance_q31 * S,      
  int32_t resetStateFlag)     
{      
  /* Derived coefficient A0 */      
  S->A0 = __QADD(__QADD(S->Kp, S->Ki), S->Kd);      
      
  /* Derived coefficient A1 */      
  S->A1 = -__QADD(__QADD(S->Kd, S->Kd), S->Kp);      
      
  /* Derived coefficient A2 */      
  S->A2 = S->Kd;      
      
  /* Check whether state needs reset or not */      
  if(resetStateFlag)     
  {      
    /* Clear the state buffer.  The size will be always 3 samples */      
    memset(S->state, 0, 3u * sizeof(q31_t));      
  }      
      
}      
      
/**      
 * @} end of PID group      
 */     
