/** @file pinmux.c 
*   @brief PINMUX Driver Implementation File
*   @date 15.December.2011
*   @version 03.00.00
*
*/

/* (c) Texas Instruments 2009-2012, All rights reserved. */

/* Include Files */

#include "pinmux.h"

#define PINMUX_SET(REG, BALLID, MUX)								\
				pinMuxReg->PINMUX##REG## = (pinMuxReg->PINMUX##REG## & PINMUX_BALL_##BALLID##_MASK) | (PINMUX_BALL_##BALLID##_##MUX##)

#define PINMUX_GATE_EMIF_CLK_ENABLE		\
			pinMuxReg->PINMUX29 = (pinMuxReg->PINMUX29 & PINMUX_GATE_EMIF_CLK_MASK) | PINMUX_GATE_EMIF_CLK

#define PINMUX_GIOB_DISABLE_HET2_ENABLE	\
			pinMuxReg->PINMUX29 = (pinMuxReg->PINMUX29 & PINMUX_GIOB_DISABLE_HET2_MASK) | PINMUX_GIOB_DISABLE_HET2
			
#define PINMUX_ALT_ADC_TRIGGER_SELECT(num)	\
			pinMuxReg->PINMUX30 = (pinMuxReg->PINMUX30 & PINMUX_ALT_ADC_TRIGGER_MASK) | (PINMUX_ALT_ADC_TRIGGER_##num##)
			
#define PINMUX_ETHERNET_SELECT(interface)	\
			pinMuxReg->PINMUX29 = (pinMuxReg->PINMUX29 & PINMUX_ETHERNET_MASK) | (PINMUX_ETHERNET_##interface##)

/* USER CODE BEGIN (0) */
/* USER CODE END */

void muxInit(void){

/* USER CODE BEGIN (1) */
/* USER CODE END */

	/* Enable Pin Muxing */
	kickerReg->KICKER0 = 0x83E70B13;
	kickerReg->KICKER1 = 0x95A4F1E0;
	
/* USER CODE BEGIN (2) */
/* USER CODE END */

        pinMuxReg->PINMUX0 = PINMUX_BALL_C3_MIBSPI3NCS_3 | PINMUX_BALL_B2_MIBSPI3NCS_2;
	
	pinMuxReg->PINMUX1 = PINMUX_BALL_E3_HET1_11 | PINMUX_BALL_E4_ETMDATA_20 | PINMUX_BALL_F4_ETMDATA_21;
	
	pinMuxReg->PINMUX2 = PINMUX_BALL_C1_GIOA_2 | PINMUX_BALL_G4_ETMDATA_22 | PINMUX_BALL_E1_GIOA_3 | PINMUX_BALL_B5_GIOA_5;
	
	pinMuxReg->PINMUX3 = PINMUX_BALL_K4_ETMDATA_23 | PINMUX_BALL_H3_GIOA_6 | PINMUX_BALL_L4_ETMDATA_24;
	
	pinMuxReg->PINMUX4 = PINMUX_BALL_M1_GIOA_7 | PINMUX_BALL_M4_ETMDATA_25 | PINMUX_BALL_V2_HET1_01 | PINMUX_BALL_U1_HET1_03;
	
	pinMuxReg->PINMUX5 = PINMUX_BALL_K18_HET1_0 | PINMUX_BALL_W5_HET1_02 | PINMUX_BALL_V6_HET1_05 | PINMUX_BALL_N4_ETMDATA_26;
	
	pinMuxReg->PINMUX6 = PINMUX_BALL_T1_HET1_07 | PINMUX_BALL_P4_ETMDATA_27 | PINMUX_BALL_V7_HET1_09 | PINMUX_BALL_R5_ETMDATA_28;
	
	pinMuxReg->PINMUX7 = PINMUX_BALL_R6_ETMDATA_29 | PINMUX_BALL_V5_MIBSPI3NCS_1 | PINMUX_BALL_W3_HET1_06 | PINMUX_BALL_R7_ETMDATA_30;
	
	pinMuxReg->PINMUX8 = PINMUX_BALL_N2_HET1_13 | PINMUX_BALL_G3_MIBSPI1NCS_2 | PINMUX_BALL_N1_HET1_15 | PINMUX_BALL_R8_ETMDATA_31;
	
	pinMuxReg->PINMUX9 = PINMUX_BALL_R9_ETMTRACECLKIN | PINMUX_BALL_W9_MIBSPI3NENA | PINMUX_BALL_V10_MIBSPI3NCS_0 | PINMUX_BALL_J3_MIBSPI1NCS_3;
	
	pinMuxReg->PINMUX10 = PINMUX_BALL_N19_AD1EVT | PINMUX_BALL_N15_ETMDATA_19 | PINMUX_BALL_N17_EMIF_nCS_0 | PINMUX_BALL_M15_ETMDATA_18;
	
	pinMuxReg->PINMUX11 = PINMUX_BALL_K17_EMIF_nCS_3 | PINMUX_BALL_M17_EMIF_nCS_4 | PINMUX_BALL_L15_ETMDATA_17 | PINMUX_BALL_P1_HET1_24;
	
	pinMuxReg->PINMUX12 = PINMUX_BALL_A14_HET1_26 | PINMUX_BALL_K15_ETMDATA_16 | PINMUX_BALL_G19_MIBSPI1NENA | PINMUX_BALL_H18_MIBSPI5NENA;
	
	pinMuxReg->PINMUX13 = PINMUX_BALL_J18_MIBSPI5SOMI_0 | PINMUX_BALL_J19_MIBSPI5SIMO_0 | PINMUX_BALL_H19_MIBSPI5CLK | PINMUX_BALL_R2_MIBSPI1NCS_0;
	
	pinMuxReg->PINMUX14 = PINMUX_BALL_E18_HET1_08 | PINMUX_BALL_K19_HET1_28 | PINMUX_BALL_D17_EMIF_nWE | PINMUX_BALL_D16_EMIF_BA_1;
	
	pinMuxReg->PINMUX15 = PINMUX_BALL_C17_EMIF_ADDR_21 | PINMUX_BALL_C16_EMIF_ADDR_20 | PINMUX_BALL_C15_EMIF_ADDR_19 | PINMUX_BALL_D15_EMIF_ADDR_18;
	
	pinMuxReg->PINMUX16 = PINMUX_BALL_D13_ETMDATA_12 | PINMUX_BALL_C14_EMIF_ADDR_17 | PINMUX_BALL_D14_EMIF_ADDR_16 | PINMUX_BALL_D12_ETMDATA_13;
	
	pinMuxReg->PINMUX17 = PINMUX_BALL_D19_HET1_10 | PINMUX_BALL_D11_ETMDATA_14 | PINMUX_BALL_B4_HET1_12 | PINMUX_BALL_D9_ETMDATA_08;
	
	pinMuxReg->PINMUX18 = PINMUX_BALL_C13_EMIF_ADDR_15 | PINMUX_BALL_C12_EMIF_ADDR_14 | PINMUX_BALL_M2_GIOB_0;
	
	pinMuxReg->PINMUX19 = PINMUX_BALL_D8_ETMDATA_09 | PINMUX_BALL_B11_HET1_30 | PINMUX_BALL_D10_ETMDATA_15 | PINMUX_BALL_D7_ETMDATA_10;
	
	pinMuxReg->PINMUX20 = PINMUX_BALL_C11_EMIF_ADDR_13 | PINMUX_BALL_C10_EMIF_ADDR_12 | PINMUX_BALL_F3_MIBSPI1NCS_1 | PINMUX_BALL_C9_EMIF_ADDR_11;
	
	pinMuxReg->PINMUX21 = PINMUX_BALL_D5_EMIF_ADDR_1 | PINMUX_BALL_C8_EMIF_ADDR_10 | PINMUX_BALL_C7_EMIF_ADDR_9;
	
	pinMuxReg->PINMUX22 = PINMUX_BALL_D4_EMIF_ADDR_0 | PINMUX_BALL_C5_EMIF_ADDR_7 | PINMUX_BALL_C4_EMIF_ADDR_6 | PINMUX_BALL_D6_ETMDATA_11;
	
	pinMuxReg->PINMUX23 =  0x01010100|
                               PINMUX_BALL_C6_EMIF_ADDR_8;
	
	pinMuxReg->PINMUX24 = 0x01010101;
	
	pinMuxReg->PINMUX25 = 0x01010101;
	
	pinMuxReg->PINMUX26 = PINMUX_BALL_W6_MIBSPI5NCS_2 | PINMUX_BALL_T12_MIBSPI5NCS_3;
	
	pinMuxReg->PINMUX27 = PINMUX_BALL_E19_MIBSPI5NCS_0 | PINMUX_BALL_B6_MIBSPI5NCS_1 | PINMUX_BALL_E16_MIBSPI5SIMO_1 | PINMUX_BALL_H17_MIBSPI5SIMO_2;
	
	pinMuxReg->PINMUX28 = PINMUX_BALL_G17_MIBSPI5SIMO_3 | PINMUX_BALL_E17_MIBSPI5SOMI_1 | PINMUX_BALL_H16_MIBSPI5SOMI_2 | PINMUX_BALL_G16_MIBSPI5SOMI_3;
	
	pinMuxReg->PINMUX29 = PINMUX_BALL_D3_SPI2NENA;
	

	
	
	PINMUX_ALT_ADC_TRIGGER_SELECT(1);
	PINMUX_ETHERNET_SELECT(RMII);
	
	PINMUX_SET(0,A5,GIOA_0);
	PINMUX_SET(18,A11,HET1_14);
	PINMUX_SET(3,B3,HET1_22);
	PINMUX_SET(1,C2,GIOA_1);
	PINMUX_SET(21,K2,GIOB_1);
	PINMUX_SET(0,W10,GIOB_3);
	
/* USER CODE BEGIN (3) */
/* USER CODE END */
	
	/* Disable Pin Muxing */
	kickerReg->KICKER0 = 0x00000000;
	kickerReg->KICKER1 = 0x00000000;
	
/* USER CODE BEGIN (4) */
/* USER CODE END */
}

/* USER CODE BEGIN (5) */
/* USER CODE END */
