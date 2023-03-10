#include "RFFC2071.h"
#include "esp_log.h"
#include <unistd.h>
#include <math.h>

#define Num_Max 10

#define REF_IN (2000) // 10MHz  //default 1000
#define REF_DIV (1)	  // 10MHz  //default 1

// uint16_t databuf_2071[TABLE_2071_NUM*2] = {
// 	/* chip1: rx */
// 	0xBEFA, 0x4064, 0x9055, 0x2D02, 0xACBF,
// 	0xACBF, 0x0028, 0x0028, 0xFF00, 0x8220,
// 	0x0202, 0x4800, 0x1A94, 0xD89D, 0x8900,
// 	0x1E84, 0x89D8, 0x9D00, 0x2A80, 0x0000,
// 	0x0000, 0x0000, 0x0000, 0x4900, 0x0281,
// 	0xF00F, 0x0000, 0x0005, 0xC840, 0x1000, 0x0005,
// 	/* chip2: tx */
// 	0xBEFA, 0x4064, 0x9055, 0x2D02, 0xACBF,
// 	0xACBF, 0x0028, 0x0028, 0xFF00, 0x8220,
// 	0x0202, 0x4800, 0x1A94, 0xD89D, 0x8900,
// 	0x1E84, 0x89D8, 0x9D00, 0x2A80, 0x0000,
// 	0x0000, 0x0000, 0x0000, 0x4900, 0x0281,
// 	0xF00F, 0x0000, 0x0005, 0xC840, 0x1000, 0x0005,
// }
uint32_t F_PD; // 10kHz
uint32_t F_VCO;

// bool RFFC2071_lock(void)
// {
// 	return LOCK?1:0;
// }

void wait_time(void)
{
	uint8_t i = 0;
	for (i = 0; i < 100; i++)
		;
	// usleep(5);
}

void wait_long_time(void)
{
	int j = 0;
	for (j = 0; j < 2000; j++)
		;
	// usleep(5);
}

/*
** Function name:           RFFC2071_write
** Descriptions:            写数据
** input parameters:        chip:	要操作的芯片
**													add：	寄存器地址, 7位
**													ret:	要写入的数据，16位
** output parameters:       none
** Returned value:          none
*/
void RFFC2071_write(uint8_t add, uint16_t ret)
{
	uint8_t i;

	CLK_2071_1;
	usleep(1);
	//usleep(1);
	CLK_2071_0;

	//	switch(chip)
	//	{
	//		case chip_rx_2071:	RX_2071_LE_0;	break;
	//		case chip_tx_2071:	TX_2071_LE_0;	break;
	//	}
	LE_2071_0;
	usleep(1);
	//usleep(1);
	CLK_2071_1;
	usleep(1);
	//usleep(1);
	CLK_2071_0;
	/* 发 "写" 操作标志 */
	add &= ~0x80;
	/* 发送7位地址，高位在前，上升沿有效 */
	for (i = 0; i < 8; i++)
	{
		if ((add & 0x80) != 0)
			DATA_2071_1;
		else
			DATA_2071_0;

		add <<= 1;
		usleep(1);
		//usleep(1);
		CLK_2071_1;
		usleep(1);
		//usleep(1);
		CLK_2071_0;
	}

	/* 发送16位数据，高位在前，上升沿有效 */
	for (i = 0; i < 16; i++)
	{
		if ((ret & 0x8000) != 0)
			DATA_2071_1;
		else
			DATA_2071_0;

		ret <<= 1;
		usleep(1);
		//usleep(1);
		CLK_2071_1;
		usleep(1);
		//usleep(1);
		CLK_2071_0;
	}
	LE_2071_1;
	//	switch(chip)
	//	{
	//		case chip_rx_2071:	RX_2071_LE_1;	break;
	//		case chip_tx_2071:	TX_2071_LE_1;	break;
	//	}
	usleep(1);
	CLK_2071_1;
	usleep(1);
	CLK_2071_0;

	usleep(1);
	CLK_2071_1;
	usleep(1);
	CLK_2071_0;
	// 我再加两个，nnd
	// usleep(1);
	// //usleep(1);
	// CLK_2071_1;
	// usleep(1);
	// //usleep(1);
	// CLK_2071_0;
	// usleep(1);
	// //usleep(1);
	// CLK_2071_1;
	// usleep(1);
	// //usleep(1);
	// CLK_2071_0;
	usleep(10);
	//  
	// CLK_2071_1;
	//  
	// CLK_2071_0;
}

/*
** Function name:           RFFC2071_read，三线制总线
** Descriptions:            读数据
** input parameters:        chip:	要操作的芯片
**													add：	寄存器地址, 7位
**
** output parameters:       ret:	要读出的数据，16位
** Returned value:          none
// */
uint16_t RFFC2071_read(uint8_t add)
{
	uint8_t i ;
	uint16_t ret =0 ;

	CLK_2071_1;
	usleep(1);
	CLK_2071_0;

	LE_2071_0;
//	switch(chip)
//	{
//		case chip_rx_2071:	RX_2071_LE_0;	break;
//		case chip_tx_2071:	TX_2071_LE_0;	break;
//	}
	usleep(1);
	CLK_2071_1;
	usleep(1);
	CLK_2071_0;

	add |= 0x80 ;
	/* 发送7位地址，高位在前，上升沿有效 */
	for(i=0;i<8;i++)
	{
		if((add & 0x80)!=0)
			DATA_2071_1;
		else
			DATA_2071_0;

		add<<=1 ;
		usleep(1);
		CLK_2071_1;
		usleep(1);
		CLK_2071_0;
	}

	usleep(1);//1
	CLK_2071_1;
	usleep(1);//2
	CLK_2071_0;
	usleep(1);//3
	CLK_2071_1;
	usleep(1);//4

	//输入
//	GPIO_DDR_INPUT(DATA_2071_PORT, DATA_2071_PIN);
	/* 发送16位数据，高位在前，下降沿有效 */
	for(i=0;i<16;i++)
	{
		ret <<= 1 ;
		CLK_2071_0;
		if(DATA_2071_R)
			ret |= 1;
		else
			ret &= ~1;

		usleep(1);
		CLK_2071_1;
		usleep(1);
	}

//	//输出
//	GPIO_DDR_OUTPUT(DATA_2071_PORT, DATA_2071_PIN);
	LE_2071_1;
//	switch(chip)
//	{
//		case chip_rx_2071:	RX_2071_LE_1;	break;
//		case chip_tx_2071:	TX_2071_LE_1;	break;
//	}
	usleep(1);
	CLK_2071_0;

	usleep(1);
	CLK_2071_1;
	usleep(1);
	CLK_2071_0;

	return ret;
}

void RFFC2071_REG_INIT(S_RFFC2071_REG *rffc2071_reg_t)
{
	*(uint16_t *)&(rffc2071_reg_t->reg_LF) = RFFC2071_VALUE_LF;
	*(uint16_t *)&(rffc2071_reg_t->reg_XO) = RFFC2071_VALUE_XO;
	*(uint16_t *)&(rffc2071_reg_t->reg_CAL_TIME) = RFFC2071_VALUE_CAL_TIME;
	*(uint16_t *)&(rffc2071_reg_t->reg_VCO_CTRL) = RFFC2071_VALUE_VCO_CTRL;
	*(uint16_t *)&(rffc2071_reg_t->reg_CT_CAL1) = RFFC2071_VALUE_CT_CAL1;
	*(uint16_t *)&(rffc2071_reg_t->reg_CT_CAL2) = RFFC2071_VALUE_CT_CAL2;
	*(uint16_t *)&(rffc2071_reg_t->reg_PLL_CAL1) = RFFC2071_VALUE_PLL_CAL1;
	*(uint16_t *)&(rffc2071_reg_t->reg_PLL_CAL2) = RFFC2071_VALUE_PLL_CAL2;
	*(uint16_t *)&(rffc2071_reg_t->reg_VCO_AUTO) = RFFC2071_VALUE_VCO_AUTO;
	*(uint16_t *)&(rffc2071_reg_t->reg_PLL_CTRL) = RFFC2071_VALUE_PLL_CTRL;
	*(uint16_t *)&(rffc2071_reg_t->reg_PLL_BIAS) = RFFC2071_VALUE_PLL_BIAS;
	*(uint16_t *)&(rffc2071_reg_t->reg_MIX_CONT) = RFFC2071_VALUE_MIX_CONT;
	*(uint16_t *)&(rffc2071_reg_t->reg_P1_FREQ1) = RFFC2071_VALUE_P1_FREQ1;
	*(uint16_t *)&(rffc2071_reg_t->reg_P1_FREQ2) = RFFC2071_VALUE_P1_FREQ2;
	*(uint16_t *)&(rffc2071_reg_t->reg_P1_FREQ3) = RFFC2071_VALUE_P1_FREQ3;
	*(uint16_t *)&(rffc2071_reg_t->reg_P2_FREQ1) = RFFC2071_VALUE_P2_FREQ1;
	*(uint16_t *)&(rffc2071_reg_t->reg_P2_FREQ2) = RFFC2071_VALUE_P2_FREQ2;
	*(uint16_t *)&(rffc2071_reg_t->reg_P2_FREQ3) = RFFC2071_VALUE_P2_FREQ3;
	*(uint16_t *)&(rffc2071_reg_t->reg_FN_CTRL) = RFFC2071_VALUE_FN_CTRL;
	*(uint16_t *)&(rffc2071_reg_t->reg_EXT_MOD) = RFFC2071_VALUE_EXT_MOD;
	*(uint16_t *)&(rffc2071_reg_t->reg_FMOD) = RFFC2071_VALUE_FMOD;
	*(uint16_t *)&(rffc2071_reg_t->reg_SDI_CTRL) = RFFC2071_VALUE_SDI_CTRL;
	*(uint16_t *)&(rffc2071_reg_t->reg_GPO) = RFFC2071_VALUE_GPO;
	*(uint16_t *)&(rffc2071_reg_t->reg_T_VCO) = RFFC2071_VALUE_T_VCO;
	*(uint16_t *)&(rffc2071_reg_t->reg_IQMOD1) = RFFC2071_VALUE_IQMOD1;
	*(uint16_t *)&(rffc2071_reg_t->reg_IQMOD2) = RFFC2071_VALUE_IQMOD2;
	*(uint16_t *)&(rffc2071_reg_t->reg_IQMOD3) = RFFC2071_VALUE_IQMOD3;
	*(uint16_t *)&(rffc2071_reg_t->reg_IQMOD4) = RFFC2071_VALUE_IQMOD4;
	*(uint16_t *)&(rffc2071_reg_t->reg_T_CTRL) = RFFC2071_VALUE_T_CTRL;
	*(uint16_t *)&(rffc2071_reg_t->reg_DEV_CTRL) = RFFC2071_VALUE_DEV_CTRL;
	*(uint16_t *)&(rffc2071_reg_t->reg_TEST) = RFFC2071_VALUE_TEST;
}
// 返回f_pd鉴相频率
uint32_t RFFC2071_PD_INIT(S_RFFC2071_REG *rffc2071_reg_t)
{
	if (REF_DIV > 1)
	{
		rffc2071_reg_t->reg_PLL_CTRL.divby = 0;
		rffc2071_reg_t->reg_PLL_CTRL.clkdiv = REF_DIV;
	}
	else
	{
		rffc2071_reg_t->reg_PLL_CTRL.divby = 1;
		rffc2071_reg_t->reg_PLL_CTRL.clkdiv = 0;
	}

	F_PD = REF_IN / REF_DIV; // Hz
	return F_PD;
}
// 配置N分频
void RFFC2071_N_INIT(uint32_t Fre, S_RFFC2071_REG *rffc2071_reg_t)
{
	uint16_t N, N_msb, N_lsb;
	uint32_t buffer, fbkdiv;
	uint8_t i, n_lo;

	n_lo = 540000 / Fre; // 10kHz

	for (i = 1; i <= 5; i++)
	{
		if (n_lo < pow(2, i))
		{
			n_lo = i - 1;
			break;
		}
	}

	rffc2071_reg_t->reg_P1_FREQ1.p1lodiv = n_lo;
	rffc2071_reg_t->reg_P2_FREQ1.p2lodiv = n_lo; 

	F_VCO = Fre * pow(2, n_lo);

	if (F_VCO > 320000) // 10kHz
	{
		fbkdiv = 4;
		rffc2071_reg_t->reg_P1_FREQ1.p1presc = 2; //added
		rffc2071_reg_t->reg_P2_FREQ1.p2presc = 2; //added
	}
	else
	{
		fbkdiv = 2;
		rffc2071_reg_t->reg_P1_FREQ1.p1presc = 1; //added
		rffc2071_reg_t->reg_P2_FREQ1.p2presc = 1; //added 有问题
	}

	N = F_VCO / F_PD / fbkdiv;

	buffer = F_VCO - (N * F_PD * fbkdiv);

	N_msb = ((buffer << 16) / F_PD) / fbkdiv;

	buffer = (buffer << 16) - (N_msb * F_PD * fbkdiv);

	N_lsb = ((buffer << 8) / F_PD) / fbkdiv;

	rffc2071_reg_t->reg_P1_FREQ1.p1n = N;
	rffc2071_reg_t->reg_P1_FREQ2.p1nmsb = N_msb;
	rffc2071_reg_t->reg_P1_FREQ3.p1nlsb = N_lsb;

	rffc2071_reg_t->reg_P2_FREQ1.p2n = N;
	rffc2071_reg_t->reg_P2_FREQ2.p2nmsb = N_msb;
	rffc2071_reg_t->reg_P2_FREQ3.p2nlsb = N_lsb;
}

void RFFC2071_reset_device(S_RFFC2071_REG *rffc2071_reg_t)
{
	uint16_t ret = 0;

	// D_RESET	=	1;
	// RESET_2071_0;
	// ENBL_2071_0;
	// usleep(1);
	RESET_2071_1;
	// ENBL_2071_1;
	// ENBL		=	1;
	usleep(10);

	rffc2071_reg_t->reg_SDI_CTRL.reset = 1;
	ret = *(uint16_t *)&(rffc2071_reg_t->reg_SDI_CTRL);
	RFFC2071_write(RFFC2071_MAP_SDI_CTRL, ret);
	 
	rffc2071_reg_t->reg_SDI_CTRL.reset = 0;
}

// 1
void RFFC2071_setup_device(S_RFFC2071_REG *rffc2071_reg_t)
{
	uint16_t ret = 0;

	/* P2_FREQ1: p2vcosel = 0 */
	// rffc2071_reg_t->reg_P2_FREQ1.p2vcosel = 0;
	// ret = *(uint16_t *)&(rffc2071_reg_t->reg_P2_FREQ1);
	// RFFC2071_write(RFFC2071_MAP_P2_FREQ1, ret);
	 

	/* VCO_AUTO: ct_max =127, ct_min = 0*/
	///* VCO_AUTO: ct_max =127, ct_min = 3*/
	//	rffc2071_reg_t->reg_VCO_AUTO._auto = 1;
	// rffc2071_reg_t->reg_VCO_AUTO.ctmin = 0;
	// rffc2071_reg_t->reg_VCO_AUTO.ctmax = 0x7f;
	// ret = *(uint16_t *)&(rffc2071_reg_t->reg_VCO_AUTO);
	// RFFC2071_write(RFFC2071_MAP_VCO_AUTO, ret);
	 

	/* CT_CAL1: p1ctv = 16 */
	//	/* CT_CAL1: p1cgain	= 5 */
	//	/* CT_CAL1: p1ctv = 16 */
	//	rffc2071_reg_t->reg_CT_CAL1.p1ctgain = 5;
	// rffc2071_reg_t->reg_CT_CAL1.p1ctv = 12;
	// ret = *(uint16_t *)&(rffc2071_reg_t->reg_CT_CAL1);
	// RFFC2071_write(RFFC2071_MAP_CT_CAL1, ret);
	 
	/* CT_CAL2: p2ctv = 12 */
	//	/* CT_CAL2: p1cgai	= 5 */
	//	/* CT_CAL2: p1ctv = 16 */
	//	rffc2071_reg_t->reg_CT_CAL2.p2ctgain = 5;
	// rffc2071_reg_t->reg_CT_CAL2.p2ctv = 12;
	// ret = *(uint16_t *)&(rffc2071_reg_t->reg_CT_CAL2);
	// RFFC2071_write(RFFC2071_MAP_CT_CAL2, ret);
	 
	/* TEST: rgbyp = 1 */
	// rffc2071_reg_t->reg_TEST.rgbyp = 1;
	// ret = *(uint16_t *)&(rffc2071_reg_t->reg_TEST);
	// RFFC2071_write(RFFC2071_MAP_TEST, ret);
	 
	rffc2071_reg_t->reg_PLL_CTRL.ldlev = 1; //added
	ret = *(uint16_t *)&(rffc2071_reg_t->reg_PLL_CTRL);
	RFFC2071_write(RFFC2071_MAP_PLL_CTRL, ret);
	 
	rffc2071_reg_t->reg_VCO_CTRL.icpup =3; //added
	ret = *(uint16_t *)&(rffc2071_reg_t->reg_VCO_CTRL);
	RFFC2071_write(RFFC2071_MAP_VCO_CTRL, ret);
	 

	/* SDI_CTRL: sipin =1 */
#if CONTROL_3_WIRE_BUS
	rffc2071_reg_t->reg_SDI_CTRL.sipin = 1;
	ret = *(uint16_t *)&(rffc2071_reg_t->reg_SDI_CTRL);
	RFFC2071_write(RFFC2071_MAP_SDI_CTRL, ret);
#endif

	/* SDI_CTRL: addr = 1 */
#if MULTISLICE_MODE
	rffc2071_reg_t->reg_SDI_CTRL.addr = 1;
#else
	rffc2071_reg_t->reg_SDI_CTRL.addr = 0;
#endif
	ret = *(uint16_t *)&(rffc2071_reg_t->reg_SDI_CTRL);
	RFFC2071_write(RFFC2071_MAP_SDI_CTRL, ret);
	 

	/* MIX_CONT: fulld = 1 */
#if FULL_DUPLEX
	rffc2071_reg_t->reg_MIX_CONT.fulld = 1;
#else
	rffc2071_reg_t->reg_MIX_CONT.fulld = 0;
#endif
	ret = *(uint16_t *)&(rffc2071_reg_t->reg_MIX_CONT);
	RFFC2071_write(RFFC2071_MAP_MIX_CONT, ret);
	 

	/* MIX_CONT: p1mixidd, p2mixidd */
	rffc2071_reg_t->reg_MIX_CONT.p1mixidd = VALUE_MIX_CONT_P1MIXIDD;
	rffc2071_reg_t->reg_MIX_CONT.p2mixidd = VALUE_MIX_CONT_P2MIXIDD;
	ret = *(uint16_t *)&(rffc2071_reg_t->reg_MIX_CONT);
	RFFC2071_write(RFFC2071_MAP_MIX_CONT, ret);
	 
}
// 2
void RFFC2071_set_calibration(S_RFFC2071_REG *rffc2071_reg_t)
{
	uint16_t ret = 0;

/* GPO: p1gpio, p2gpio and gate */
#if GENE_PURP_OUTPUT
	rffc2071_reg_t->reg_GPO.p1gpo = VALUE_GPO_P1GPIO;
	rffc2071_reg_t->reg_GPO.p2gpo = VALUE_GPO_P2GPIO;
	rffc2071_reg_t->reg_GPO.gate = VALUE_GPO_GATE; // gate disable
#endif

/* GPO: lock */
#if GPO_LOCK
	rffc2071_reg_t->reg_GPO.lock = 1;
#else
	rffc2071_reg_t->reg_GPO.lock = 0;
#endif
	ret = *(uint16_t *)&(rffc2071_reg_t->reg_GPO);
	RFFC2071_write(RFFC2071_MAP_GPO, ret);
	 

/* SDI_CTRL: 4 wire */
#if PROG_4_WIRE
	rffc2071_reg_t->reg_SDI_CTRL._4wire = 1;
#else
	rffc2071_reg_t->reg_SDI_CTRL._4wire = 0;
#endif
	ret = *(uint16_t *)&(rffc2071_reg_t->reg_SDI_CTRL);
	RFFC2071_write(RFFC2071_MAP_SDI_CTRL, ret);
	 

/*
	EXT_MOD: modstep, modsetup
	FMOD:		 modulation
*/
#if FREQ_MODUL
	rffc2071_reg_t->reg_EXT_MOD.modstep = VALUE_EXT_MOD_MODSTEP;
	rffc2071_reg_t->reg_EXT_MOD.modsetup = VALUE_EXT_MOD_MODSETUP;
	ret = *(uint16_t *)&(rffc2071_reg_t->reg_EXT_MOD);
	RFFC2071_write(RFFC2071_MAP_EXT_MOD, ret);

	rffc2071_reg_t->reg_FMOD.modulation = VALUE_FMOD;
	RFFC2071_write(RFFC2071_MAP_FMOD, ret);
#endif
}

// 3
void RFFC2071_set_oper_freq(S_RFFC2071_REG *rffc2071_reg_t)
{
	uint16_t ret = 0;

/*
	VCO_AUTO: auto
	P1_FREQ1: p1vcosel
	P2_FREQ1: p2vcosel
*/
#if UNAUTO_VCO_SELECT
	rffc2071_reg_t->reg_VCO_AUTO._auto = VALUE_VCO_AUTO_AUTO;
	ret = *(uint16_t *)&(rffc2071_reg_t->reg_VCO_AUTO);
	RFFC2071_write(RFFC2071_MAP_VCO_AUTO, ret);

	rffc2071_reg_t->reg_P1_FREQ1.p1vcosel = VALUE_P1_FREQ1_P1VOSEL;
	ret = *(uint16_t *)&(rffc2071_reg_t->reg_P1_FREQ1);
	RFFC2071_write(RFFC2071_MAP_P1_FREQ1, ret);

	rffc2071_reg_t->reg_P2_FREQ1.p2vcosel = VALUE_P2_FREQ1_P2VOSEL;
	ret = *(uint16_t *)&(rffc2071_reg_t->reg_P2_FREQ1);
	RFFC2071_write(RFFC2071_MAP_P2_FREQ1, ret);
#endif

/*
	CT_CAL1: p1ct, p1ctdef
	CT_CAL2: p2ct, p2ctdef
*/
#if AUTO_CT_CAL
	rffc2071_reg_t->reg_CT_CAL1.p1ct = VALUE_CT_CAL1_P1CT;
	rffc2071_reg_t->reg_CT_CAL1.p1ctdef = VALUE_CT_CAL1_P1CTDEF;
	ret = *(uint16_t *)&(rffc2071_reg_t->reg_CT_CAL1);
	RFFC2071_write(RFFC2071_MAP_CT_CAL1, ret);

	rffc2071_reg_t->reg_CT_CAL2.p2ct = VALUE_CT_CAL2_P2CT;
	rffc2071_reg_t->reg_CT_CAL2.p2ctdef = VALUE_CT_CAL2_P2CTDEF;
	ret = *(uint16_t *)&(rffc2071_reg_t->reg_CT_CAL2);
	RFFC2071_write(RFFC2071_MAP_CT_CAL2, ret);
#endif

	/*
		P1_FREQ1: p1presc=4
		LF			: pllcpl=3
	*/
	// ZGF default 4,3
	if (F_VCO > 320000) // FVCO_3.2G
	{
		rffc2071_reg_t->reg_P1_FREQ1.p1presc = 2; //added 和Datasheet有问题
		ret = *(uint16_t *)&(rffc2071_reg_t->reg_P1_FREQ1);
		RFFC2071_write(RFFC2071_MAP_P1_FREQ1, ret);
		 

		rffc2071_reg_t->reg_LF.pllcpl = 3; //added 和Datasheet有问题
		ret = *(uint16_t *)&(rffc2071_reg_t->reg_LF);
		RFFC2071_write(RFFC2071_MAP_LF, ret);
		 
	}
	/* P1_FREQ1: p1presc=2 */
	else
	{
		rffc2071_reg_t->reg_P1_FREQ1.p1presc = 1; // ZGF defaule :2 //added 和Datasheet有问题
		ret = *(uint16_t *)&(rffc2071_reg_t->reg_P1_FREQ1);
		RFFC2071_write(RFFC2071_MAP_P1_FREQ1, ret);
		 
	}

	/*
		P1_FREQ1: p1n, p1lodiv
		P1_FREQ2: p1nmsb
		P1_FREQ3: p1nlsb
	*/
	//	rffc2071_reg_t->reg_P1_FREQ1.p1n			= VALUE_P1_FREQ1_P1N;
	//	rffc2071_reg_t->reg_P1_FREQ1.p1lodiv	= VALUE_P1_FREQ1_P1LODIV;
	ret = *(uint16_t *)&(rffc2071_reg_t->reg_P1_FREQ1);
	RFFC2071_write(RFFC2071_MAP_P1_FREQ1, ret);
	 

	// 	rffc2071_reg_t->reg_P1_FREQ2.p1nmsb		= VALUE_P1_FREQ2_P1NMSB;
	ret = *(uint16_t *)&(rffc2071_reg_t->reg_P1_FREQ2);
	RFFC2071_write(RFFC2071_MAP_P1_FREQ2, ret);
	 

	// 	rffc2071_reg_t->reg_P1_FREQ3.p1nlsb		= VALUE_P1_FREQ3_P1NLSB;
	ret = *(uint16_t *)&(rffc2071_reg_t->reg_P1_FREQ3);
	RFFC2071_write(RFFC2071_MAP_P1_FREQ3, ret);
	 

	/*
		P2_FREQ1: p2n, p2lodiv
		P2_FREQ2: p2nmsb
		P2_FREQ3: p2nlsb
	*/
	//	rffc2071_reg_t->reg_P2_FREQ1.p2n			= VALUE_P2_FREQ1_P2N;
	//	rffc2071_reg_t->reg_P2_FREQ1.p2presc	= 1;
	//	rffc2071_reg_t->reg_P2_FREQ1.p2lodiv	= VALUE_P2_FREQ1_P2LODIV;
	ret = *(uint16_t *)&(rffc2071_reg_t->reg_P2_FREQ1);
	RFFC2071_write(RFFC2071_MAP_P2_FREQ1, ret);
	 

	//	rffc2071_reg_t->reg_P2_FREQ2.p2nmsb		= VALUE_P2_FREQ2_P2NMSB;
	ret = *(uint16_t *)&(rffc2071_reg_t->reg_P2_FREQ2);
	RFFC2071_write(RFFC2071_MAP_P2_FREQ2, ret);
	 

	//	rffc2071_reg_t->reg_P2_FREQ3.p2nlsb		= VALUE_P2_FREQ3_P2NLSB;
	ret = *(uint16_t *)&(rffc2071_reg_t->reg_P2_FREQ3);
	RFFC2071_write(RFFC2071_MAP_P2_FREQ3, ret);
	 
}

// 4
void RFFC2071_set_calibration_mode(S_RFFC2071_REG *rffc2071_reg_t)
{
	uint16_t ret = 0;

/*
	PLL_CAL1: p1kv = 0
	PLL_CAL2: p2kv = 0
*/
#if ENABLE_LOOP_CAL
	rffc2071_reg_t->reg_PLL_CAL1.p1kv = 1;
	rffc2071_reg_t->reg_PLL_CAL2.p2kv = 1;
#else
	rffc2071_reg_t->reg_PLL_CAL1.p1kv = 0;
	rffc2071_reg_t->reg_PLL_CAL2.p2kv = 0;
#endif
	ret = *(uint16_t *)&(rffc2071_reg_t->reg_PLL_CAL1);
	RFFC2071_write(RFFC2071_MAP_PLL_CAL1, ret);
	 

	ret = *(uint16_t *)&(rffc2071_reg_t->reg_PLL_CAL2);
	RFFC2071_write(RFFC2071_MAP_PLL_CAL2, ret);
	 
}
// 5
void RFFC2071_enable_device(S_RFFC2071_REG *rffc2071_reg_t)
{
	uint16_t ret = 0;

#if ENABLE_DEVICE /* programming bus */ // 1=ENBL and MODE pins are ignored and become available as GPO5 and GPO6
	rffc2071_reg_t->reg_SDI_CTRL.sipin = 1;
	ret = *(uint16_t *)&(rffc2071_reg_t->reg_SDI_CTRL);
	RFFC2071_write(RFFC2071_MAP_SDI_CTRL, ret);

	rffc2071_reg_t->reg_SDI_CTRL.enbl = 1;
#else
	rffc2071_reg_t->reg_SDI_CTRL.sipin = 0;
	rffc2071_reg_t->reg_SDI_CTRL.enbl = 0;
#endif
	ret = *(uint16_t *)&(rffc2071_reg_t->reg_SDI_CTRL);
	RFFC2071_write(RFFC2071_MAP_SDI_CTRL, ret);
	 

	// 	rffc2071_reg_t->reg_GPO.lock = 1;
	// 	rffc2071_reg_t->reg_GPO.p1gpo = 1<<0;
	// 	rffc2071_reg_t->reg_GPO.p1gpo = 1<<1;
	// 	ret = 	*(uint16_t *)&(rffc2071_reg_t->reg_GPO);
	// 	RFFC2071_write(chip, RFFC2071_MAP_GPO, ret );
}
