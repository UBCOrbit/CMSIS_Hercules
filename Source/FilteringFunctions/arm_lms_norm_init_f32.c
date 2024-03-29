/*-----------------------------------------------------------------------------      
* Copyright (C) 2011 ARM Limited. All rights reserved. 
*      
* $Date:        15. December 2011   
* $Revision: 	V2.0.0  
*      
* Project:      Cortex-R DSP Library 
* Title:        arm_lms_norm_init_f32.c      
*      
* Description:  Floating-point NLMS filter initialization function.      
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
* ---------------------------------------------------------------------------*/     
#include "arm_math.h"     
     
/**      
 * @ingroup groupFilters      
 */     
     
/**      
 * @addtogroup LMS_NORM      
 * @{      
 */     
     
  /**      
   * @brief Initialization function for floating-point normalized LMS filter.      
   * @param[in] *S points to an instance of the floating-point LMS filter structure.      
   * @param[in] numTaps  number of filter coefficients.      
   * @param[in] *pCoeffs points to coefficient buffer.      
   * @param[in] *pState points to state buffer.      
   * @param[in] mu step size that controls filter coefficient updates.      
   * @param[in] blockSize number of samples to process.      
   * @return none.      
   *      
 * \par Description:      
 * <code>pCoeffs</code> points to the array of filter coefficients stored in time reversed order:      
 * <pre>      
 *    {b[numTaps-1], b[numTaps-2], b[N-2], ..., b[1], b[0]}      
 * </pre>      
 * The initial filter coefficients serve as a starting point for the adaptive filter.      
 * <code>pState</code> points to an array of length <code>numTaps+blockSize-1</code> samples,      
 * where <code>blockSize</code> is the number of input samples processed by each call to <code>arm_lms_norm_f32()</code>.      
 */     
     
void arm_lms_norm_init_f32(     
  arm_lms_norm_instance_f32 * S,     
  uint16_t numTaps,     
  float32_t * pCoeffs,     
  float32_t * pState,     
  float32_t mu,     
  uint32_t blockSize)     
{     
  /* Assign filter taps */     
  S->numTaps = numTaps;     
     
  /* Assign coefficient pointer */     
  S->pCoeffs = pCoeffs;     
     
  /* Clear state buffer and size is always blockSize + numTaps - 1 */     
  memset(pState, 0, (numTaps + (blockSize - 1u)) * sizeof(float32_t));     
     
  /* Assign state pointer */     
  S->pState = pState;     
     
  /* Assign Step size value */     
  S->mu = mu;     
     
  /* Initialise Energy to zero */     
  S->energy = 0.0f;     
     
  /* Initialise x0 to zero */     
  S->x0 = 0.0f;     
     
}     
     
/**      
 * @} end of LMS_NORM group      
 */     
