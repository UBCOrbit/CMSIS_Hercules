/* ----------------------------------------------------------------------      
* Copyright (C) 2011 ARM Limited. All rights reserved. 
*      
* $Date:        15. December 2011   
* $Revision: 	V2.0.0  
*      
* Project:      Cortex-R DSP Library 
* Title:	    arm_cfft_mag_q31.c      
*      
* Description:	This file has function definition of Radix-4 FFT with magnitude function and      
*				In-place bit reversal using bit reversal table      
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
* -------------------------------------------------------------------- */     
#include "arm_math.h"     
     
     
/**      
 * @ingroup groupTransforms      
 */     
     
/**      
 * @addtogroup CFFT_MAG 
 * @{      
 */     
     
/**      
 * @details      
 * @brief Processing function for the Q31 CFFT Magnitude      
 * @param[in]      *S    points to an instance of the Q31 CFFT structure.     
 * @param[in, out] *pSrc points to the complex data buffer of size <code>2*fftLen</code>. Processing occurs in-place.     
 * @return none.      
 *       
 * \par Input and output formats:      
 * \par      
 * Internally input is downscaled by 2 for every stage to avoid saturations inside CFFT_MAG process.     
 * Hence the output format is different for different FFT sizes.      
 * The input and output formats for different FFT sizes and number of bits to upscale are mentioned in the tables below for CFFT and CIFFT:     
 * \par     
 * \image html CFFTQ31.gif "Input and Output Formats for Q31 CFFT Magnitude"      
 *  
 * \par      
 * Refer to the function <code>arm_cfft_radix4_q31()</code> for a detailed description of CFFT Q31.     
 */     
     
void arm_cfft_mag_q31(     
  const arm_cfft_radix4_instance_q31 * S,     
  q31_t * pSrc)     
{     
  /* Complex FFT Magnitude */     
  arm_cfft_mag_butterfly_q31(pSrc, S->fftLen, S->pTwiddle,     
                             S->twidCoefModifier);     
     
     
  if(S->bitReverseFlag == 1u)     
  {     
    /*  Bit Reversal */     
    arm_cfft_mag_bitreversal_q31(pSrc, S->fftLen, S->bitRevFactor, S->pBitRevTable);     
  }     
     
}     
     
/**      
 * @} end of CFFT_CIFFT group      
 */     
     
/*      
* Radix-4 FFT algorithm used is :      
*      
* Input real and imaginary data:      
* x(n) = xa + j * ya      
* x(n+N/4 ) = xb + j * yb      
* x(n+N/2 ) = xc + j * yc      
* x(n+3N 4) = xd + j * yd      
*      
*      
* Output real and imaginary data:      
* x(4r) = xa'+ j * ya'      
* x(4r+1) = xb'+ j * yb'      
* x(4r+2) = xc'+ j * yc'      
* x(4r+3) = xd'+ j * yd'      
*      
*      
* Twiddle factors for radix-4 FFT:      
* Wn = co1 + j * (- si1)      
* W2n = co2 + j * (- si2)      
* W3n = co3 + j * (- si3)      
*      
*  Butterfly implementation:      
* xa' = xa + xb + xc + xd      
* ya' = ya + yb + yc + yd      
* xb' = (xa+yb-xc-yd)* co1 + (ya-xb-yc+xd)* (si1)      
* yb' = (ya-xb-yc+xd)* co1 - (xa+yb-xc-yd)* (si1)      
* xc' = (xa-xb+xc-xd)* co2 + (ya-yb+yc-yd)* (si2)      
* yc' = (ya-yb+yc-yd)* co2 - (xa-xb+xc-xd)* (si2)      
* xd' = (xa-yb-xc+yd)* co3 + (ya+xb-yc-xd)* (si3)      
* yd' = (ya+xb-yc-xd)* co3 - (xa-yb-xc+yd)* (si3)      
*      
*/     
     
/**      
 * @brief  Core function for the Q31 CFFT butterfly process.     
 * @param[in, out] *pSrc            points to the in-place buffer of Q31 data type.     
 * @param[in]      fftLen           length of the FFT.     
 * @param[in]      *pCoef           points to twiddle coefficient buffer.     
 * @param[in]      twidCoefModifier twiddle coefficient modifier that supports different size FFTs with the same twiddle factor table.     
 * @return none.     
 */     
     
void arm_cfft_mag_butterfly_q31(     
  q31_t * pSrc,    
  uint32_t fftLen,     
  q31_t * pCoef,     
  uint32_t twidCoefModifier)     
{     
  uint32_t n1, n2, ia1, ia2, ia3, i0, i1, i2, i3, j, k;     
  q31_t t1, t2, r1, r2, s1, s2, co1, co2, co3, si1, si2, si3;     
     
  q31_t xa, xb, xc, xd;   
  q31_t ya, yb, yc, yd;   
  q31_t xa_out, xb_out, xc_out, xd_out;   
  q31_t ya_out, yb_out, yc_out, yd_out;     
     
  q31_t *ptr1, *pDst = &pSrc[0];   
  q63_t xaya, xbyb, xcyc, xdyd;   
  /* Total process is divided into three stages */     
     
  /* process first stage, middle stages, & last stage */     
     
     
  /* start of first stage process */     
     
  /*  Initializations for the first stage */     
  n2 = fftLen;     
  n1 = n2;     
  /* n2 = fftLen/4 */     
  n2 >>= 2u;     
  i0 = 0u;     
  ia1 = 0u;     
     
  j = n2;     
     
  /*  Calculation of first stage */     
  do     
  {     
    /*  index calculation for the input as, */     
    /*  pSrc[i0 + 0], pSrc[i0 + fftLen/4], pSrc[i0 + fftLen/2u], pSrc[i0 + 3fftLen/4] */     
    i1 = i0 + n2;     
    i2 = i1 + n2;     
    i3 = i2 + n2;     
     
    /* input is in 1.31(q31) format and provide 4 guard bits for the input */     
     
    /*  Butterfly implementation */     
    /* xa + xc */     
    r1 = (pSrc[(2u * i0)] >> 4u) + (pSrc[(2u * i2)] >> 4u);     
    /* xa - xc */     
    r2 = (pSrc[2u * i0] >> 4u) - (pSrc[2u * i2] >> 4u);     
     
    /* xb + xd */     
    t1 = (pSrc[2u * i1] >> 4u) + (pSrc[2u * i3] >> 4u);   
       
    /* ya + yc */     
    s1 = (pSrc[(2u * i0) + 1u] >> 4u) + (pSrc[(2u * i2) + 1u] >> 4u);     
    /* ya - yc */     
    s2 = (pSrc[(2u * i0) + 1u] >> 4u) - (pSrc[(2u * i2) + 1u] >> 4u);     
     
    /* xa' = xa + xb + xc + xd */     
    pSrc[2u * i0] = (r1 + t1);     
    /* (xa + xc) - (xb + xd) */     
    r1 = r1 - t1;     
    /* yb + yd */     
    t2 = (pSrc[(2u * i1) + 1u] >> 4u) + (pSrc[(2u * i3) + 1u] >> 4u);    
       
       
    /* ya' = ya + yb + yc + yd */     
    pSrc[(2u * i0) + 1u] = (s1 + t2);     
     
    /* (ya + yc) - (yb + yd) */     
    s1 = s1 - t2;     
     
    /* yb - yd */     
    t1 = (pSrc[(2u * i1) + 1u] >> 4u) - (pSrc[(2u * i3) + 1u] >> 4u);     
    /* xb - xd */     
    t2 = (pSrc[2u * i1] >> 4u) - (pSrc[2u * i3] >> 4u);     
     
    /*  index calculation for the coefficients */     
    ia2 = 2u * ia1;     
    co2 = pCoef[ia2 * 2u];     
    si2 = pCoef[(ia2 * 2u) + 1u];     
     
    /* xc' = (xa-xb+xc-xd)co2 + (ya-yb+yc-yd)(si2) */     
    pSrc[2u * i1] = (((int32_t) (((q63_t) r1 * co2) >> 32)) +     
                     ((int32_t) (((q63_t) s1 * si2) >> 32))) << 1u;     
     
    /* yc' = (ya-yb+yc-yd)co2 - (xa-xb+xc-xd)(si2) */     
    pSrc[(2u * i1) + 1u] = (((int32_t) (((q63_t) s1 * co2) >> 32)) -     
                            ((int32_t) (((q63_t) r1 * si2) >> 32))) << 1u;     
     
    /* (xa - xc) + (yb - yd) */     
    r1 = r2 + t1;     
    /* (xa - xc) - (yb - yd) */     
    r2 = r2 - t1;     
     
    /* (ya - yc) - (xb - xd) */     
    s1 = s2 - t2;     
    /* (ya - yc) + (xb - xd) */     
    s2 = s2 + t2;     
     
    co1 = pCoef[ia1 * 2u];     
    si1 = pCoef[(ia1 * 2u) + 1u];     
     
    /* xb' = (xa+yb-xc-yd)co1 + (ya-xb-yc+xd)(si1) */     
    pSrc[2u * i2] = (((int32_t) (((q63_t) r1 * co1) >> 32)) +     
                     ((int32_t) (((q63_t) s1 * si1) >> 32))) << 1u;     
     
    /* yb' = (ya-xb-yc+xd)co1 - (xa+yb-xc-yd)(si1) */     
    pSrc[(2u * i2) + 1u] = (((int32_t) (((q63_t) s1 * co1) >> 32)) -     
                            ((int32_t) (((q63_t) r1 * si1) >> 32))) << 1u;     
     
    /*  index calculation for the coefficients */     
    ia3 = 3u * ia1;     
    co3 = pCoef[ia3 * 2u];     
    si3 = pCoef[(ia3 * 2u) + 1u];     
     
    /* xd' = (xa-yb-xc+yd)co3 + (ya+xb-yc-xd)(si3) */     
    pSrc[2u * i3] = (((int32_t) (((q63_t) r2 * co3) >> 32)) +     
                     ((int32_t) (((q63_t) s2 * si3) >> 32))) << 1u;     
     
    /* yd' = (ya+xb-yc-xd)co3 - (xa-yb-xc+yd)(si3) */     
    pSrc[(2u * i3) + 1u] = (((int32_t) (((q63_t) s2 * co3) >> 32)) -     
                            ((int32_t) (((q63_t) r2 * si3) >> 32))) << 1u;     
     
    /*  Twiddle coefficients index modifier */     
    ia1 = ia1 + twidCoefModifier;     
     
    /*  Updating input index */     
    i0 = i0 + 1u;     
     
  } while(--j);     
     
  /* end of first stage process */     
     
  /* data is in 5.27(q27) format */     
     
     
  /* start of Middle stages process */     
     
     
  /* each stage in middle stages provides two down scaling of the input */     
     
  twidCoefModifier <<= 2u;     
     
     
  for (k = fftLen / 4u; k > 4u; k >>= 2u)     
  {     
    /*  Initializations for the first stage */     
    n1 = n2;     
    n2 >>= 2u;     
    ia1 = 0u;     
     
    /*  Calculation of first stage */     
    for (j = 0u; j <= (n2 - 1u); j++)     
    {     
      /*  index calculation for the coefficients */     
      ia2 = ia1 + ia1;     
      ia3 = ia2 + ia1;     
      co1 = pCoef[ia1 * 2u];     
      si1 = pCoef[(ia1 * 2u) + 1u];     
      co2 = pCoef[ia2 * 2u];     
      si2 = pCoef[(ia2 * 2u) + 1u];     
      co3 = pCoef[ia3 * 2u];     
      si3 = pCoef[(ia3 * 2u) + 1u];     
         
      /*  Twiddle coefficients index modifier */     
      ia1 = ia1 + twidCoefModifier;     
     
      for (i0 = j; i0 < fftLen; i0 += n1)     
      {     
        /*  index calculation for the input as, */     
        /*  pSrc[i0 + 0], pSrc[i0 + fftLen/4], pSrc[i0 + fftLen/2u], pSrc[i0 + 3fftLen/4] */     
        i1 = i0 + n2;     
        i2 = i1 + n2;     
        i3 = i2 + n2;     
     
        /*  Butterfly implementation */     
        /* xa + xc */     
        r1 = pSrc[2u * i0] + pSrc[2u * i2];     
        /* xa - xc */     
        r2 = pSrc[2u * i0] - pSrc[2u * i2];     
     
        /* ya + yc */     
        s1 = pSrc[(2u * i0) + 1u] + pSrc[(2u * i2) + 1u];     
        /* ya - yc */     
        s2 = pSrc[(2u * i0) + 1u] - pSrc[(2u * i2) + 1u];     
     
        /* xb + xd */     
        t1 = pSrc[2u * i1] + pSrc[2u * i3];     
     
        /* xa' = xa + xb + xc + xd */     
        pSrc[2u * i0] = (r1 + t1) >> 2u;     
        /* xa + xc -(xb + xd) */     
        r1 = r1 - t1;     
     
        /* yb + yd */     
        t2 = pSrc[(2u * i1) + 1u] + pSrc[(2u * i3) + 1u];     
        /* ya' = ya + yb + yc + yd */     
        pSrc[(2u * i0) + 1u] = (s1 + t2) >> 2u;     
     
        /* (ya + yc) - (yb + yd) */     
        s1 = s1 - t2;     
     
        /* (yb - yd) */     
        t1 = pSrc[(2u * i1) + 1u] - pSrc[(2u * i3) + 1u];     
        /* (xb - xd) */     
        t2 = pSrc[2u * i1] - pSrc[2u * i3];     
     
        /* xc' = (xa-xb+xc-xd)co2 + (ya-yb+yc-yd)(si2) */     
        pSrc[2u * i1] = (((int32_t) (((q63_t) r1 * co2) >> 32)) +     
                         ((int32_t) (((q63_t) s1 * si2) >> 32))) >> 1u;     
     
        /* yc' = (ya-yb+yc-yd)co2 - (xa-xb+xc-xd)(si2) */     
        pSrc[(2u * i1) + 1u] = (((int32_t) (((q63_t) s1 * co2) >> 32)) -     
                                ((int32_t) (((q63_t) r1 * si2) >> 32))) >> 1u;     
     
        /* (xa - xc) + (yb - yd) */     
        r1 = r2 + t1;     
        /* (xa - xc) - (yb - yd) */     
        r2 = r2 - t1;     
     
        /* (ya - yc) -  (xb - xd) */     
        s1 = s2 - t2;     
        /* (ya - yc) +  (xb - xd) */     
        s2 = s2 + t2;     
     
        /* xb' = (xa+yb-xc-yd)co1 + (ya-xb-yc+xd)(si1) */     
        pSrc[2u * i2] = (((int32_t) (((q63_t) r1 * co1) >> 32)) +     
                         ((int32_t) (((q63_t) s1 * si1) >> 32))) >> 1u;     
     
        /* yb' = (ya-xb-yc+xd)co1 - (xa+yb-xc-yd)(si1) */     
        pSrc[(2u * i2) + 1u] = (((int32_t) (((q63_t) s1 * co1) >> 32)) -     
                                ((int32_t) (((q63_t) r1 * si1) >> 32))) >> 1u;     
     
        /* xd' = (xa-yb-xc+yd)co3 + (ya+xb-yc-xd)(si3) */     
        pSrc[2u * i3] = (((int32_t) (((q63_t) r2 * co3) >> 32)) +     
                         ((int32_t) (((q63_t) s2 * si3) >> 32))) >> 1u;     
     
        /* yd' = (ya+xb-yc-xd)co3 - (xa-yb-xc+yd)(si3) */     
        pSrc[(2u * i3) + 1u] = (((int32_t) (((q63_t) s2 * co3) >> 32)) -     
                                ((int32_t) (((q63_t) r2 * si3) >> 32))) >> 1u;     
      }     
    }     
    twidCoefModifier <<= 2u;     
  }     
     
  /* End of Middle stages process */     
     
  /* data is in 11.21(q21) format for the 1024 point as there are 3 middle stages */     
  /* data is in 9.23(q23) format for the 256 point as there are 2 middle stages */     
  /* data is in 7.25(q25) format for the 64 point as there are 1 middle stage */     
  /* data is in 5.27(q27) format for the 16 point as there are no middle stages */     
     
  /* start of Last stage process */     
  /*  Initializations for the last stage */   
  j = fftLen >> 2;   
  ptr1 = &pSrc[0];   
   
  /*  Calculations of last stage */   
  do   
  {   
   
#ifndef ARM_MATH_BIG_ENDIAN   
   
		/* Read xa (real), ya(imag) input */   
    	xaya = *__SIMD64(ptr1)++; xa = (q31_t)xaya; ya = (q31_t)(xaya >> 32);   	   
   
		/* Read xb (real), yb(imag) input */   
    	xbyb = *__SIMD64(ptr1)++; xb = (q31_t)xbyb; yb = (q31_t)(xbyb >> 32);   
   
	  	/* Read xc (real), yc(imag) input */   
    	xcyc = *__SIMD64(ptr1)++; xc = (q31_t)xcyc; yc = (q31_t)(xcyc >> 32);	   
   
		/* Read xc (real), yc(imag) input */   
    	xdyd = *__SIMD64(ptr1)++; xd = (q31_t)xdyd; yd = (q31_t)(xdyd >> 32);   
   
#else   
   
		/* Read xa (real), ya(imag) input */   
    	xaya = *__SIMD64(ptr1)++; ya = (q31_t)xaya; xa = (q31_t)(xaya >> 32);   	   
   
		/* Read xb (real), yb(imag) input */   
    	xbyb = *__SIMD64(ptr1)++; yb = (q31_t)xbyb; xb = (q31_t)(xbyb >> 32);   
   
	  	/* Read xc (real), yc(imag) input */   
    	xcyc = *__SIMD64(ptr1)++; yc = (q31_t)xcyc; xc = (q31_t)(xcyc >> 32);	   
   
		/* Read xc (real), yc(imag) input */   
    	xdyd = *__SIMD64(ptr1)++; yd = (q31_t)xdyd; xd = (q31_t)(xdyd >> 32);   
   
   
#endif   
   
		/* xa' = xa + xb + xc + xd */   
		xa_out = xa + xb + xc + xd;   
   
		/* ya' = ya + yb + yc + yd */   
		ya_out = ya + yb + yc + yd;      
   
		xc_out = (xa-xb+xc-xd);   
		yc_out = (ya-yb+yc-yd);   
  
		/* writing xa' and ya' */   
		xa_out = (q31_t) (((q63_t) xa_out * xa_out) >> 33);  
		ya_out = (q31_t) (((q63_t) ya_out * ya_out) >> 33);  
  
		/* writing xc' and yc' */   
		xc_out = (q31_t) (((q63_t) xc_out * xc_out) >> 33);  
   
		yc_out = (q31_t) (((q63_t) yc_out * yc_out) >> 33);  
  
  		arm_sqrt_q31(ya_out+xa_out, pDst++);  
		arm_sqrt_q31(xc_out+yc_out, pDst++);  
  
		xb_out = (xa+yb-xc-yd);   
		yb_out = (ya-xb-yc+xd);   
   
		xd_out = (xa-yb-xc+yd);   
		yd_out = (ya+xb-yc-xd);   
   
		/* writing xb' and yb' */   
		xb_out = (q31_t) (((q63_t) xb_out * xb_out) >> 33);  
		yb_out = (q31_t) (((q63_t) yb_out * yb_out) >> 33);  
  
  
		/* writing xd' and yd' */   
		xd_out = (q31_t) (((q63_t) xd_out * xd_out) >> 33);	  
		yd_out = (q31_t) (((q63_t) yd_out * yd_out) >> 33);  
  
 		arm_sqrt_q31(xb_out+yb_out, pDst++);  
 		arm_sqrt_q31(xd_out+yd_out, pDst++);  
  
	   
	}while(--j);     
     
  /* output is in 11.21(q21) format for the 1024 point */     
  /* output is in 9.23(q23) format for the 256 point */     
  /* output is in 7.25(q25) format for the 64 point */     
  /* output is in 5.27(q27) format for the 16 point */     
     
  /* End of last stage process */     
     
}     
    
     
/*      
 * @brief  In-place bit reversal function.     
 * @param[in, out] *pSrc        points to the in-place buffer of Q31 data type.     
 * @param[in]      fftLen       length of the FFT.     
 * @param[in]      bitRevFactor bit reversal modifier that supports different size FFTs with the same bit reversal table     
 * @param[in]      *pBitRevTab  points to bit reversal table.     
 * @return none.     
 */     
     
void arm_cfft_mag_bitreversal_q31(     
  q31_t * pSrc,     
  uint32_t fftLen,     
  uint16_t bitRevFactor,     
  uint16_t * pBitRevTable)     
{     
  uint32_t fftLenBy2, fftLenBy2p1, i, j;     
  q31_t in;     
    
  /*  Initializations      */     
  j = 0u;     
  fftLenBy2 = fftLen / 2u;     
  fftLenBy2p1 = (fftLen / 2u) + 1u;     
     
  /* Bit Reversal Implementation */     
  for (i = 0u; i <= (fftLenBy2-2u); i+=2)     
  {     
    if(i < j)     
    {     
      /*  pSrc[i] <-> pSrc[j]; */     
      in = pSrc[i];     
      pSrc[i] = pSrc[j];     
      pSrc[j] = in;     
     
      /*  pSrc[i+fftLenBy2p1] <-> pSrc[j+fftLenBy2p1] */     
      in = pSrc[(i + fftLenBy2p1)];     
      pSrc[(i + fftLenBy2p1)] = pSrc[(j + fftLenBy2p1)];     
      pSrc[(j + fftLenBy2p1)] = in;        
     
    }     
     
    /*  pSrc[i+1u] <-> pSrc[j+1u] */     
    in = pSrc[(i + 1u)];     
    pSrc[(i + 1u)] = pSrc[(j + fftLenBy2)];     
    pSrc[(j + fftLenBy2)] = in;     
     
    /*  Reading the index for the bit reversal */     
    j = *pBitRevTable;     
     
    /*  Updating the bit reversal index depending on the fft length */     
    pBitRevTable += bitRevFactor;     
  }     
}     
