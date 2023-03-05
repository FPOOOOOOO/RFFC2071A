
//------------------------------------------------
//<<< Use Configuration Wizard in Context Menu >>>
//------------------------------------------------

#ifndef  __RFFC2071_H__
#define  __RFFC2071_H__

// #include "compiler_defs.h"
#include <stdint.h>
#include "driver/gpio.h"

	
enum{
	chip_rx_2071 = 0,
	chip_tx_2071,
};

#define TABLE_2071_NUM							31				//静态数据表的长度

/*GPIO MAP*/
#define GPIO_OUTPUT_IO_0 25  //DATA
#define GPIO_OUTPUT_IO_1 26  //LE
#define GPIO_OUTPUT_IO_2 27  // CLK
#define GPIO_OUTPUT_IO_3 12  //D_RESET
#define GPIO_OUTPUT_IO_4 13  // ENBL
#define GPIO_OUTPUT_PIN_SEL ((1ULL << GPIO_OUTPUT_IO_0) | (1ULL << GPIO_OUTPUT_IO_1) | (1ULL << GPIO_OUTPUT_IO_2)| (1ULL << GPIO_OUTPUT_IO_3)| (1ULL << GPIO_OUTPUT_IO_4))
#define GPIO_INPUT_IO_0 34
#define GPIO_INPUT_IO_1 5
#define GPIO_INPUT_PIN_SEL ((1ULL << GPIO_INPUT_IO_0) | (1ULL << GPIO_INPUT_IO_1))
#define ESP_INTR_FLAG_DEFAULT 0

#define DATA_2071_1 (gpio_set_level(GPIO_OUTPUT_IO_0, 1))
#define DATA_2071_0 (gpio_set_level(GPIO_OUTPUT_IO_0, 0))

#define LE_2071_1 (gpio_set_level(GPIO_OUTPUT_IO_1, 1))
#define LE_2071_0 (gpio_set_level(GPIO_OUTPUT_IO_1, 0))

#define CLK_2071_1 (gpio_set_level(GPIO_OUTPUT_IO_2, 1))
#define CLK_2071_0 (gpio_set_level(GPIO_OUTPUT_IO_2, 0))

#define RESET_2071_1 (gpio_set_level(GPIO_OUTPUT_IO_3, 1))
#define RESET_2071_0 (gpio_set_level(GPIO_OUTPUT_IO_3, 0))

#define ENBL_2071_1 (gpio_set_level(GPIO_OUTPUT_IO_4, 1))
#define ENBL_2071_0 (gpio_set_level(GPIO_OUTPUT_IO_4, 0))
//

#define DATA_2071_R (gpio_get_level(GPIO_OUTPUT_IO_0)) 



/* REGISTER MAP */
#define RFFC2071_MAP_LF						0x00			//Loop Filter Configuration
#define RFFC2071_MAP_XO						0x01			//Crystal Oscillator Configuration
#define RFFC2071_MAP_CAL_TIME				0x02			//Calibration Timing
#define RFFC2071_MAP_VCO_CTRL				0x03			//Calibration Control
#define RFFC2071_MAP_CT_CAL1				0x04			//Path 1 Coarse Tuning Calibration
#define RFFC2071_MAP_CT_CAL2				0x05			//Path 2 Coarse Tuning Calibration
#define RFFC2071_MAP_PLL_CAL1				0x06			//Path 1 PLL Calibration
#define RFFC2071_MAP_PLL_CAL2				0x07			//Path 2 PLL Calibration
#define RFFC2071_MAP_VCO_AUTO				0x08			//Auto VCO select control
#define RFFC2071_MAP_PLL_CTRL				0x09			//PLL Control
#define RFFC2071_MAP_PLL_BIAS				0x0A			//PLL Bias Settings
#define RFFC2071_MAP_MIX_CONT				0x0B			//Mixer Control
#define RFFC2071_MAP_P1_FREQ1				0x0C			//Path 1 Frequency 1
#define RFFC2071_MAP_P1_FREQ2				0x0D			//Path 1 Frequency 2
#define RFFC2071_MAP_P1_FREQ3				0x0E			//Path 1 Frequency 3
#define RFFC2071_MAP_P2_FREQ1				0x0F			//Path 2 Frequency 1
#define RFFC2071_MAP_P2_FREQ2				0x10			//Path 2 Frequency 2
#define RFFC2071_MAP_P2_FREQ3				0x11			//Path 2 Frequency 3
#define RFFC2071_MAP_FN_CTRL				0x12			//Frac-N Control
#define RFFC2071_MAP_EXT_MOD				0x13			//Frequency modulation control 1
#define RFFC2071_MAP_FMOD						0x14			//Frequency modulation control 2
#define RFFC2071_MAP_SDI_CTRL				0x15			//SDI Control
#define RFFC2071_MAP_GPO						0x16			//General Purpose Outputs
#define RFFC2071_MAP_T_VCO					0x17			//Temperature Compensation VCO Curves
#define RFFC2071_MAP_IQMOD1					0x18			//Modulator Calibration
#define RFFC2071_MAP_IQMOD2					0x19			//Modulator Control
#define RFFC2071_MAP_IQMOD3					0x1A			//Modulator Buffer Control
#define RFFC2071_MAP_IQMOD4					0x1B			//Modulator Core Control
#define RFFC2071_MAP_T_CTRL					0x1C			//Temperature compensation control
#define RFFC2071_MAP_DEV_CTRL				0x1D			//Readback register and RSM Control
#define RFFC2071_MAP_TEST						0x1E			//Test register
#define RFFC2071_MAP_READBACK				0x1F			//Readback register

/* register struct */
/* Loop Filter Configuration */
typedef struct 
{
	uint16_t	pllcpl	:	3;					/* 0~2 */
	uint16_t	p1cpdef	: 6;					/* 3~8 */
	uint16_t	p2cpdef	: 6;					/* 9~14 */
	uint16_t	ifact		: 1;					/* 15 */
}S_REG_LF;
// 
/* Crystal Oscillator Configuration */
typedef  struct
{
	uint16_t	suwait	:	10;					/* 0~9 */
	uint16_t	xocf		: 1;					/* 10  */
	uint16_t	xoc			: 4;					/* 11~14 */
	uint16_t	xoch		: 1;					/* 15 */
}S_REG_XO;

/* Calibration Timing */
typedef  struct  
{
	uint16_t	tkv2		:	4;					/* 0~3 */
	uint16_t	tkv1		: 4;					/* 4~7  */
	uint16_t	n_a			: 2;					/* 8~9 */
	uint16_t	tct			: 5;					/* 10~14 */
	uint16_t	wait		: 1;					/* 15 */
}S_REG_CAL_TIME;

/* Calibration Control */
typedef  struct 
{
	uint16_t	n_a			:	1;					/* 0 */
	uint16_t	icpup		: 2;					/* 2:1  */
	uint16_t	refst		: 1;					/* 3 */
	uint16_t	xoi3		: 1;					/* 4 */
	uint16_t	xoi2		: 1;					/* 5 */
	uint16_t	xoi1		:	1;					/* 6 */
	uint16_t	kvpol		: 1;					/* 7 */
	uint16_t	kvrng		: 1;					/* 8 */
	uint16_t	kvavg		: 2;					/* 10:9 */
	uint16_t	clkpl		: 1;					/* 11 */
	uint16_t	ctpol		: 1;					/* 12 */
	uint16_t	ctavg		: 2;					/* 14:13 */
	uint16_t	xtvco		: 1;					/* 15 */
}S_REG_VCO_CTRL;

/* Path 1 Coarse Tuning Calibration */
typedef  struct  
{
	uint16_t	p1ctdef	:	7;					/* 6:0 	*/
	uint16_t	p1ct		: 1;					/* 7  	*/
	uint16_t	p1ctv		: 5;					/* 12:8 */
	uint16_t	p1ctgain: 3;					/* 15:13 */
}S_REG_CT_CAL1;

/* Path 2 Coarse Tuning Calibration */
typedef  struct 
{
	uint16_t	p2ctdef	:	7;					/* 6:0 	*/
	uint16_t	p2ct		: 1;					/* 7  	*/
	uint16_t	p2ctv		: 5;					/* 12:8 */
	uint16_t	p2ctgain: 3;					/* 15:13 */
}S_REG_CT_CAL2;

/* Path 1 PLL Calibration */
typedef  struct 
{
	uint16_t	n_a			:	2;					/* 1:0 	*/
	uint16_t	p1sgn		: 1;					/* 2  	*/
	uint16_t	p1kvgain: 3;					/* 5:3 */
	uint16_t	p1dn		: 9;					/* 14:6 */
	uint16_t	p1kv		: 1;					/* 15 */
}S_REG_PLL_CAL1;

/* Path 2 PLL Calibration */
typedef  struct  
{
	uint16_t	n_a			:	2;					/* 1:0 	*/
	uint16_t	p2sgn		: 1;					/* 2  	*/
	uint16_t	p2kvgain: 3;					/* 5:3 */
	uint16_t	p2dn		: 9;					/* 14:6 */
	uint16_t	p2kv		: 1;					/* 15 */
}S_REG_PLL_CAL2;

/* Auto VCO select control */
typedef  struct 
{
	uint16_t	n_a			:	1;					/* 0 		*/
	uint16_t	ctmin		: 7;					/* 7:1	*/
	uint16_t	ctmax		: 7;					/* 14:8 */
	uint16_t	_auto		: 1;					/* 15 */
}S_REG_VCO_AUTO;

/* PLL Control */
typedef   struct  
{
	uint16_t	plldy		:	2;					/* 1:0	*/
	uint16_t	aloi		: 1;					/* 2		*/
	uint16_t	relok		: 1;					/* 3	 */
	uint16_t	ldlev		: 1;					/* 4	 */
	uint16_t	lden		:	1;					/* 5 		*/
	uint16_t	tvco		: 5;					/* 10:6	*/
	uint16_t	pllst		: 1;					/* 11 */
	uint16_t	clkdiv	: 3;					/* 14:12 */
	uint16_t	divby		: 1;					/* 15 */
}S_REG_PLL_CTRL;

/* PLL Bias Settings */
typedef   struct 
{
	uint16_t	p2vcoi	:	3;					/* 2:0	*/
	uint16_t	p2loi		: 4;					/* 6:3	*/
	uint16_t	n_a1		: 1;					/* 7	 */
	uint16_t	p1vcoi	: 3;					/* 10:8	 */
	uint16_t	p1loi		:	4;					/* 14:11	*/
	uint16_t	n_a2		: 1;					/* 15			*/
}S_REG_PLL_BIAS;

/* Mixer Control */
typedef   struct 
{
	uint16_t	n_a			:	9;					/* 8:0	*/
	uint16_t	p2mixidd: 3;					/* 11:9	*/
	uint16_t	p1mixidd: 3;					/* 14:12*/
	uint16_t	fulld		: 1;					/* 15		*/
}S_REG_MIX_CONT;

/* Path 1 Frequency 1 */
typedef   struct 
{
	uint16_t	p1vcosel:	2;					/* 1:0	*/
	uint16_t	p1presc : 2;					/* 3:2	*/
	uint16_t	p1lodiv	: 3;					/* 6:4  */
	uint16_t	p1n 		: 9;					/* 15:7	*/
}S_REG_P1_FREQ1;

/* Path 1 Frequency 2 */
typedef   struct 
{
	uint16_t	p1nmsb:	16;					/* 15:0	*/
}S_REG_P1_FREQ2;

/* Path 1 Frequency 3 */
typedef   struct 
{
	uint16_t	n_a			:	8;					/* 7:0	*/
	uint16_t	p1nlsb	: 8;					/* 15:8	*/
}S_REG_P1_FREQ3;

/* Path 2 Frequency 1 */
typedef   struct  
{
	uint16_t	p2vcosel:	2;					/* 1:0	*/
	uint16_t	p2presc : 2;					/* 3:2	*/
	uint16_t	p2lodiv	: 3;					/* 6:4  */
	uint16_t	p2n 		: 9;					/* 15:7	*/
}S_REG_P2_FREQ1;

/* Path 2 Frequency 2 */
typedef   struct  
{
	uint16_t	p2nmsb:	16;					/* 15:0	*/
}S_REG_P2_FREQ2;

/* Path 2 Frequency 3 */
typedef   struct  
{
	uint16_t	n_a			:	8;					/* 7:0	*/
	uint16_t	p2nlsb	: 8;					/* 15:8	*/
}S_REG_P2_FREQ3;

/* Frac-N Control */
typedef   struct 
{
	uint16_t	n_a			:	1;					/* 0		*/
	uint16_t	tzps		: 1;					/* 1		*/
	uint16_t	dmode		: 1;					/* 2		*/
	uint16_t	fm			: 1;					/* 3	 */
	uint16_t	dith		: 1;					/* 4	 */
	uint16_t	mode		:	1;					/* 5 		*/
	uint16_t	phsalndly	: 2;				/* 7:6	*/
	uint16_t	phsalngain: 3;				/* 10:8 */
	uint16_t	phaln		: 1;					/* 11   */
	uint16_t	sdm			: 2;					/* 13:12*/
	uint16_t	dithr		: 1;					/* 14 */
	uint16_t	fnz			: 1;					/* 15 */
}S_REG_FN_CTRL;

/* Frequency modulation control 1 */
typedef   struct 
{
	uint16_t	n_a			:	10;					/* 9:0	*/
	uint16_t	modstep : 4;					/* 13:10	*/
	uint16_t	modsetup: 2;					/* 15:14  */
}S_REG_EXT_MOD;

/* Frequency modulation control 2 */
typedef   struct 
{
	uint16_t	modulation		:	16;					/* 15:0	*/
}S_REG_FMOD;

/* SDI Control */
typedef   struct 
{
	uint16_t	n_a1		:	1;					/* 0		*/
	uint16_t	reset		: 1;					/* 1		*/
	uint16_t	n_a2		: 9;					/* 10:2		*/
	uint16_t	addr		: 1;					/* 11	 */
	uint16_t	_4wire	: 1;					/* 12	 */
	uint16_t	mode		:	1;					/* 13 	*/
	uint16_t	enbl		: 1;					/* 14		*/
	uint16_t	sipin		: 1;					/* 15	  */
}S_REG_SDI_CTRL;

/* General Purpose Outputs */
typedef   struct 
{
	uint16_t	lock		:	1;					/* 0		*/
	uint16_t	gate		: 1;					/* 1		*/
	uint16_t	p1gpo		: 7;					/* 8:2	 */
	uint16_t	p2gpo		: 7;					/* 15:9	 */
}S_REG_GPO;

/* Temperature Compensation VCO Curves */
typedef   struct 
{
	uint16_t	n_a				 : 7;					/* 6:0		*/
	uint16_t	curve_vco3 : 3;				/* 9:7		*/
	uint16_t	curve_vco2 : 3;				/* 12:10	*/
	uint16_t	curve_vco1 : 3;				/* 15:13	*/
}S_REG_T_VCO;

/* Modulator Calibration */
typedef   struct 
{
	uint16_t	bufdc		:	2;					/* 1:0	*/
	uint16_t	divbias	: 1;					/* 2		*/
	uint16_t	calblk	: 1;					/* 3		*/
	uint16_t	calnul	: 1;					/* 4	 	*/
	uint16_t	calon		: 1;					/* 5	 	*/
	uint16_t	lobias	:	2;					/* 7:6 	*/
	uint16_t	modbias	: 3;					/* 10:8	*/
	uint16_t	ctrl		: 5;					/* 15:11 */
}S_REG_IQMOD1;

/* Modulator Control */
typedef   struct 
{
	uint16_t	modbuf	:	2;					/* 1:0	*/
	uint16_t	mod			: 2;					/* 3:2	*/
	uint16_t	calatten: 2;					/* 5:4	*/
	uint16_t	rctune	: 6;					/* 11:6	*/
	uint16_t	bbatten	: 4;					/* 15:12*/
}S_REG_IQMOD2;

/* Modulator Buffer Control */
typedef   struct 
{
	uint16_t	n_a			:	3;					/* 2:0	*/
	uint16_t	dacen		: 1;					/* 3		*/
	uint16_t	bufdacq	: 6;					/* 9:4	*/
	uint16_t	bufdaci	: 6;					/* 15:10*/
}S_REG_IQMOD3;

/* Modulator Core Control */
typedef   struct 
{
	uint16_t	bufbias2:	2;					/* 1:0	*/
	uint16_t	bufbias1: 2;					/* 3:2	*/
	uint16_t	moddacq	: 6;					/* 9:4	*/
	uint16_t	moddaci	: 6;					/* 15:10*/
}S_REG_IQMOD4;

/* Temperature compensation control */
typedef   struct  
{
	uint16_t	n_a			:	5;					/* 4:0	*/
	uint16_t	v_test	:	1;					/* 5  	*/
	uint16_t	ldo_by	: 1;					/* 6		*/
	uint16_t	ext_filt: 1;					/* 7		*/
	uint16_t	ref_sel	: 1;					/* 8		*/
	uint16_t	filtr_ctrl:	2;				/* 10:9	*/
	uint16_t	fc_en		: 1;					/* 11		*/
	uint16_t	tbl_sel	: 2;					/* 13:12*/
	uint16_t	tc_en		: 2;					/* 15:14*/
}S_REG_T_CTRL;

/* Readback register and RSM Control */
typedef   struct  
{
	uint16_t	n_a			:	1;					/* 0	*/
	uint16_t	bypas		:	1;					/* 1  	*/
	uint16_t	ctclk		: 1;					/* 2		*/
	uint16_t	dac			: 1;					/* 3		*/
	uint16_t	cpd			: 1;					/* 4		*/
	uint16_t	cpu			:	1;					/* 5		*/
	uint16_t	rsmstopst	: 5;				/* 10:6	*/
	uint16_t	rsmst		: 1;					/* 11		*/
	uint16_t	readsel	: 4;					/* 15:12*/
}S_REG_DEV_CTRL;

/* Test register */
typedef   struct 
{
	uint16_t	lfsrd		:	1;					/* 0	*/
	uint16_t	rcbyp		:	1;					/* 1  	*/
	uint16_t	rgbyp		: 1;					/* 2		*/
	uint16_t	lfsrt		: 1;					/* 3		*/
	uint16_t	lfsrgatet	: 4;				/* 7:4	*/
	uint16_t	lfsrp		:	1;					/* 8		*/
	uint16_t	lfsr		: 1;					/* 9		*/
	uint16_t	tsel		: 2;					/* 11:10*/
	uint16_t	tmux		: 3;					/* 14:12*/
	uint16_t	ten			: 1;					/* 15		*/
}S_REG_TEST;

typedef   struct
{
	S_REG_LF 					reg_LF;
	S_REG_XO 					reg_XO;
	S_REG_CAL_TIME 		reg_CAL_TIME;
	S_REG_VCO_CTRL 		reg_VCO_CTRL;
	S_REG_CT_CAL1 		reg_CT_CAL1;
	S_REG_CT_CAL2 		reg_CT_CAL2;
	S_REG_PLL_CAL1 		reg_PLL_CAL1;
	S_REG_PLL_CAL2 		reg_PLL_CAL2;
	S_REG_VCO_AUTO 		reg_VCO_AUTO;
	S_REG_PLL_CTRL 		reg_PLL_CTRL;
	S_REG_PLL_BIAS 		reg_PLL_BIAS;
	S_REG_MIX_CONT 		reg_MIX_CONT;
	S_REG_P1_FREQ1 		reg_P1_FREQ1;
	S_REG_P1_FREQ2 		reg_P1_FREQ2;
	S_REG_P1_FREQ3 		reg_P1_FREQ3;
	S_REG_P2_FREQ1 		reg_P2_FREQ1;
	S_REG_P2_FREQ2 		reg_P2_FREQ2;
	S_REG_P2_FREQ3 		reg_P2_FREQ3;
	S_REG_FN_CTRL 		reg_FN_CTRL;
	S_REG_EXT_MOD 		reg_EXT_MOD;
	S_REG_FMOD 				reg_FMOD;
	S_REG_SDI_CTRL 		reg_SDI_CTRL;
	S_REG_GPO 				reg_GPO;
	S_REG_T_VCO 			reg_T_VCO;
	S_REG_IQMOD1 			reg_IQMOD1;
	S_REG_IQMOD2 			reg_IQMOD2;
	S_REG_IQMOD3 			reg_IQMOD3;
	S_REG_IQMOD4 			reg_IQMOD4;
	S_REG_T_CTRL 			reg_T_CTRL;
	S_REG_DEV_CTRL 		reg_DEV_CTRL;
	S_REG_TEST 				reg_TEST;
}S_RFFC2071_REG;

/* REGISTER DEFAULT SETTINGS *///From Internet
// #define RFFC2071_VALUE_LF					0xFFFA			//Loop Filter Configuration
// #define RFFC2071_VALUE_XO					0x4064			//Crystal Oscillator Configuration
// #define RFFC2071_VALUE_CAL_TIME				0x9055			//Calibration Timing
// #define RFFC2071_VALUE_VCO_CTRL				0x2D06			//Calibration Control
// #define RFFC2071_VALUE_CT_CAL1				0xB0BF			//Path 1 Coarse Tuning Calibration
// #define RFFC2071_VALUE_CT_CAL2				0xB0BF			//Path 2 Coarse Tuning Calibration
// #define RFFC2071_VALUE_PLL_CAL1				0x0028			//Path 1 PLL Calibration
// #define RFFC2071_VALUE_PLL_CAL2				0x0028			//Path 2 PLL Calibration
// #define RFFC2071_VALUE_VCO_AUTO				0xFC06			//Auto VCO select control
// #define RFFC2071_VALUE_PLL_CTRL				0x8230			//PLL Control
// #define RFFC2071_VALUE_PLL_BIAS				0x0202			//PLL Bias Settings
// #define RFFC2071_VALUE_MIX_CONT				0xDA00			//Mixer Control
// #define RFFC2071_VALUE_P1_FREQ1				0x2918			//Path 1 Frequency 1
// #define RFFC2071_VALUE_P1_FREQ2				0xC45A			//Path 1 Frequency 2
// #define RFFC2071_VALUE_P1_FREQ3				0x1C00			//Path 1 Frequency 3
// #define RFFC2071_VALUE_P2_FREQ1				0x301A			//Path 2 Frequency 1
// #define RFFC2071_VALUE_P2_FREQ2				0xBBA5			//Path 2 Frequency 2
// #define RFFC2071_VALUE_P2_FREQ3				0xE300			//Path 2 Frequency 3
// #define RFFC2071_VALUE_FN_CTRL				0x2A80			//Frac-N Control
// #define RFFC2071_VALUE_EXT_MOD				0x0000			//Frequency modulation control 1
// #define RFFC2071_VALUE_FMOD						0x0000			//Frequency modulation control 2
// #define RFFC2071_VALUE_SDI_CTRL				0x0000			//SDI Control
// #define RFFC2071_VALUE_GPO						0x0000			//General Purpose Outputs
// #define RFFC2071_VALUE_T_VCO					0x4900			//Temperature Compensation VCO Curves
// #define RFFC2071_VALUE_IQMOD1					0x0281			//Modulator Calibration
// #define RFFC2071_VALUE_IQMOD2					0xF00F			//Modulator Control
// #define RFFC2071_VALUE_IQMOD3					0x0000			//Modulator Buffer Control
// #define RFFC2071_VALUE_IQMOD4					0x0005			//Modulator Core Control
// #define RFFC2071_VALUE_T_CTRL					0xC840			//Temperature compensation control
// #define RFFC2071_VALUE_DEV_CTRL				0x1000			//Readback register and RSM Control
// #define RFFC2071_VALUE_TEST						0x0005			//Test register

/* REGISTER DEFAULT SETTINGS *///From Datasheet
#define RFFC2071_VALUE_LF					0xBEFA			//Loop Filter Configuration
#define RFFC2071_VALUE_XO					0x4064			//Crystal Oscillator Configuration
#define RFFC2071_VALUE_CAL_TIME				0x9055			//Calibration Timing
#define RFFC2071_VALUE_VCO_CTRL				0x2D02			//Calibration Control
#define RFFC2071_VALUE_CT_CAL1				0xACBF			//Path 1 Coarse Tuning Calibration
#define RFFC2071_VALUE_CT_CAL2				0xACBF			//Path 2 Coarse Tuning Calibration
#define RFFC2071_VALUE_PLL_CAL1				0x0028			//Path 1 PLL Calibration
#define RFFC2071_VALUE_PLL_CAL2				0x0028			//Path 2 PLL Calibration
#define RFFC2071_VALUE_VCO_AUTO				0xFF00			//Auto VCO select control
#define RFFC2071_VALUE_PLL_CTRL				0x8220			//PLL Control
#define RFFC2071_VALUE_PLL_BIAS				0x0202			//PLL Bias Settings
#define RFFC2071_VALUE_MIX_CONT				0x4800			//Mixer Control
#define RFFC2071_VALUE_P1_FREQ1				0x1A94			//Path 1 Frequency 1
#define RFFC2071_VALUE_P1_FREQ2				0xD89D			//Path 1 Frequency 2
#define RFFC2071_VALUE_P1_FREQ3				0x8900			//Path 1 Frequency 3
#define RFFC2071_VALUE_P2_FREQ1				0x1E84			//Path 2 Frequency 1
#define RFFC2071_VALUE_P2_FREQ2				0x89D8			//Path 2 Frequency 2
#define RFFC2071_VALUE_P2_FREQ3				0x9D00			//Path 2 Frequency 3
#define RFFC2071_VALUE_FN_CTRL				0x2A80			//Frac-N Control
#define RFFC2071_VALUE_EXT_MOD				0x0000			//Frequency modulation control 1
#define RFFC2071_VALUE_FMOD						0x0000			//Frequency modulation control 2
#define RFFC2071_VALUE_SDI_CTRL				0x0000			//SDI Control
#define RFFC2071_VALUE_GPO						0x0000			//General Purpose Outputs
#define RFFC2071_VALUE_T_VCO					0x4900			//Temperature Compensation VCO Curves
#define RFFC2071_VALUE_IQMOD1					0x0281			//Modulator Calibration
#define RFFC2071_VALUE_IQMOD2					0xF00F			//Modulator Control
#define RFFC2071_VALUE_IQMOD3					0x0000			//Modulator Buffer Control
#define RFFC2071_VALUE_IQMOD4					0x0005			//Modulator Core Control
#define RFFC2071_VALUE_T_CTRL					0xC840			//Temperature compensation control
#define RFFC2071_VALUE_DEV_CTRL				0x1000			//Readback register and RSM Control
#define RFFC2071_VALUE_TEST						0x0005			//Test register



// <h> Setting Up device Operation
// 	<q> Control chip with 3-wire bus?
				#define CONTROL_3_WIRE_BUS		1      //ZGF Hardware Control enable
// 	<q> Enable MultSlice mode?
				#define MULTISLICE_MODE				0
//	<q>	Full duplex operation?
				#define FULL_DUPLEX						1
//	<h> MIX_CONT
//		<o.12..14>	MIX_CONT: p1mixidd		<0=> min current	<7=> max current
				#define VALUE_MIX_CONT_P1MIXIDD					0x04
//		<o.9..11>		MIX_CONT: p2mixidd		<0=> min current	<7=> max current
				#define VALUE_MIX_CONT_P2MIXIDD 				0x04
//	</h>
// </h>


// <h> Setting Calibration Mode
//		<e> General Purpose Outputs?
					#define GENE_PURP_OUTPUT		0
//			<o.2..8> 	GPO: p1gpio
					#define VALUE_GPO_P1GPIO		1<<0
//			<o.9..15>	GPO: p2gpio
//						#define VALUE_GPO_P2GPIO	1<<1
						#define VALUE_GPO_P2GPIO	1<<0
//			<o.1>			GPO: gate    				<0=> low		<1=> high	
						#define VALUE_GPO_GATE		0x0
//						#define VALUE_GPO_GATE		0x1    //zgf: cinfigure the GPO5 as the ENBL pin
//		</e>

//		<q>	Lock output signal?									//zgf: cinfigure the GPO4 as the LOCK pin
					#define GPO_LOCK						1
//		<q>	4-wire programming?
					#define PROG_4_WIRE					0		    //zgf: 3-wire programming
//		<e>	Frequency modulator?
					#define FREQ_MODUL					0	
//			<o.14..15>	EXT_MOD: modsetup
//													<0=> modulation off			<1=>	modulation is analog
//													<2=> modulation off			<3=> modulation is binary
#define	VALUE_EXT_MOD_MODSETUP	0x0  //ZGF:modulation off	
//			<o.10..13>	EXT_MOD: modstep
						#define VALUE_EXT_MOD_MODSTEP		0x0
//			<o.0..15>		FMOD <0x0000-0xFFFF>
						#define VALUE_FMOD				0x0000
//		</e>					
// </h>



// <h> Setting OPerating frequencies
//	<e>	Don't Auto VCO select?
				#define UNAUTO_VCO_SELECT			 0 //added
//		<o.15> VCO_AUTO: auto						<0=> manual			<1=> auto
				#define VALUE_VCO_AUTO_AUTO				0x01
//		<o.0..1> P1_FREQ1: p1vcosel			
//																		<0=> vco1				<1=> vco2				<2=> vco3
				#define VALUE_P1_FREQ1_P1VOSEL		0x0
//		<o.0..1> P2_FREQ1: p2vcosel			
//																		<0=> vco1				<1=> vco2				<2=> vco3
				#define VALUE_P2_FREQ1_P2VOSEL		0x02
//	</e>
//	<e> Don't Auto CT_cal?
				#define AUTO_CT_CAL						0
//		<o.7> 		CT_CAL1: p1ct					<0=> disable				<1=> enable
					#define VALUE_CT_CAL1_P1CT			0x01
//		<o.0..6>	CT_CAL1: p1ctdef <0x0000-0x003F>
					#define VALUE_CT_CAL1_P1CTDEF		0x003f
//		<o.7> 		CT_CAL2: p2ct					<0=> disable				<1=> enable
					#define VALUE_CT_CAL2_P2CT			0x01
//		<o.0..6>	CT_CAL2: p2ctdef <0x0000-0x003F>
					#define VALUE_CT_CAL2_P2CTDEF		0x003f
// 	</e>
// 	<q> Is Fvco > 3.2GHz ?
				#define FVCO_32G							1				
//	<h>	P1_FREQn and P2_FREQn
//		<o.7..15> P1_FREQ1: p1n					<0x000-0x1FF>
					#define VALUE_P1_FREQ1_P1N				0x7D
//		<o.4..6>  P1_FREQ1: p1lodiv			<0x0-0x7>
					#define VALUE_P1_FREQ1_P1LODIV		0x4
//		<o.0..15>	P1_FREQ2: p1nmsb			<0x0000-0xFFFF>
					#define VALUE_P1_FREQ2_P1NMSB			0x0000
//		<o.8..15>	P1_FREQ3: p1nlsb			<0x00-0xFF>
					#define VALUE_P1_FREQ3_P1NLSB			0x00
//		<o.7..15> P2_FREQ1: p2n					<0x000-0x1FF>
					#define VALUE_P2_FREQ1_P2N				0x7D
//		<o.4..6>  P2_FREQ1: p2lodiv			<0x0-0x7>
					#define VALUE_P2_FREQ1_P2LODIV		0x04
//		<o.0..15>	P2_FREQ2: p2nmsb			<0x0000-0xFFFF>
					#define VALUE_P2_FREQ2_P2NMSB			0x0000
//		<o.8..15>	P2_FREQ3: p2nlsb			<0x00-0xFF>
					#define VALUE_P2_FREQ3_P2NLSB			0x0000
//	</h>
// </h>

// <h> Setting Loop Filter Calibration Mode
//	<q>	Enable Loop Filter Cal?
				#define	ENABLE_LOOP_CAL				0
// </h>

// <h> Enable Device
//	<o>	select control method		<0=> Control pins(default)		<1=> Programming Bus
				#define	ENABLE_DEVICE					1
// </h>

extern S_RFFC2071_REG		RFFC2071_reg_rx;	/* 频率综合器相关参数*/
extern S_RFFC2071_REG		RFFC2071_reg_tx;	/* 频率综合器相关参数*/

void RFFC2071_write(uint8_t add, uint16_t data1);
uint16_t RFFC2071_read(uint8_t add);

void RFFC2071_REG_INIT(S_RFFC2071_REG * rffc2071_reg_t);
void RFFC2071_reset_device(S_RFFC2071_REG * rffc2071_reg_t);
uint32_t RFFC2071_PD_INIT(S_RFFC2071_REG * rffc2071_reg_t);
void RFFC2071_N_INIT(uint32_t Fre,S_RFFC2071_REG * rffc2071_reg_t);
void RFFC2071_setup_device(S_RFFC2071_REG * rffc2071_reg_t);
void RFFC2071_set_calibration(S_RFFC2071_REG * rffc2071_reg_t);
void RFFC2071_set_oper_freq(S_RFFC2071_REG * rffc2071_reg_t);
void RFFC2071_set_calibration_mode(S_RFFC2071_REG * rffc2071_reg_t);
void RFFC2071_enable_device(S_RFFC2071_REG * rffc2071_reg_t);
void RFFC2071_test(S_RFFC2071_REG * rffc2071_reg_t);
void RFFC2071_setup(void);
// bool RFFC2071_lock(void);

void wait_time(void);
void wait_long_time(void);

#endif
