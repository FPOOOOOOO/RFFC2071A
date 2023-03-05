#include "RFFC2071.h"
#include <unistd.h>
#define MAX_FRE (270000) // 2.7G
#define MIN_FRE (8500)	 // 85M

/*
uint8_t set_pll_reg(uint32_t freq)
{
	uint8_t  div = 0;
	uint16_t int_value		=	0;
	uint32_t frac_value	=	0;
	uint32_t undiv_freq	=	0;

	div	=	get_vco_divider(freq);
	if(div ==0)
	{
		return 0;
	}
	else
	{
		//RFOUT = [INT + (FRAC/MOD)] * [fPFD]/RF divider
		undiv_freq	=	div * freq;
		int_value 	=	(uint16_t)(undiv_freq/REF_F);
		frac_value	=	undiv_freq%REF_F;
		frac_value  = (frac_value/10000+5)/10; //Integer-valued
		set_pll(div,int_value,frac_value);
	}
	return 1;
}
void RFFC2071_test(S_RFFC2071_REG * rffc2071_reg_t)
{
	uint8_t i=31;
	uint16_t DATA;
	uint16_t * str = (uint16_t *)rffc2071_reg_t;

	for(i=0;i<=RFFC2071_MAP_DEV_CTRL;i++)
	{
		DATA = * str;

		RFFC2071_write(i, DATA );

		str += 1;
	}
}
void RFFC2071_setup(void)
{
	S8 * ret;

	uint32_t buffer,fre;
	uint32_t NoFre[4]={0,0,0,0};
	uint16_t NoWid[4]={0,0,0,0};
	uint8_t enabl=0,i,MAXf=0,MINf=0;

	if(!CENTER_FREQ_FLAG)		return;
	if(vSystem_Sw_s.IS_ON == OFF)  return;



	//ȡ��һ�Ӵ�����Ƶ��
	ret = DataBuf + RAM_NO1_FREQ;
	for(i=0;i<4;i++)
	{
		buffer = (uint32_t)*ret;
		buffer &= (uint32_t)0x000000ff;

		NoFre[0] |= (buffer << (8*i));
		ret++;
	}
	//ȡ��һ�Ӵ�����
	ret = DataBuf + RAM_NO1_BANDWIDTH;
	for(i=0;i<2;i++)
	{
		buffer = (uint32_t)*ret;
		buffer &= (uint32_t)0x000000ff;

		NoWid[0] |= (buffer << (8*i));
		ret++;
	}
	//ȡ��2�Ӵ�����Ƶ��
	ret = DataBuf + RAM_NO2_FREQ;
	for(i=0;i<4;i++)
	{
		buffer = (uint32_t)*ret;
		buffer &= (uint32_t)0x000000ff;

		NoFre[1] |= (buffer << (8*i));
		ret++;
	}
	//ȡ��2�Ӵ�����
	ret = DataBuf + RAM_NO2_BANDWIDTH;
	for(i=0;i<2;i++)
	{
		buffer = (uint32_t)*ret;
		buffer &= (uint32_t)0x000000ff;

		NoWid[1] |= (buffer << (8*i));
		ret++;
	}
	//ȡ��3�Ӵ�����Ƶ��
	ret = DataBuf + RAM_NO3_FREQ;
	for(i=0;i<4;i++)
	{
		buffer = (uint32_t)*ret;
		buffer &= (uint32_t)0x000000ff;

		NoFre[2] |= (buffer << (8*i));
		ret++;
	}
	//ȡ��3�Ӵ�����
	ret = DataBuf + RAM_NO3_BANDWIDTH;
	for(i=0;i<2;i++)
	{
		buffer = (uint32_t)*ret;
		buffer &= (uint32_t)0x000000ff;

		NoWid[2] |= (buffer << (8*i));
		ret++;
	}
	//ȡ��4�Ӵ�����Ƶ��
	ret = DataBuf + RAM_NO4_FREQ;
	for(i=0;i<4;i++)
	{
		buffer = (uint32_t)*ret;
		buffer &= (uint32_t)0x000000ff;

		NoFre[3] |= (buffer << (8*i));
		ret++;
	}
	//ȡ��4�Ӵ�����
	ret = DataBuf + RAM_NO4_BANDWIDTH;
	for(i=0;i<2;i++)
	{
		buffer = (uint32_t)*ret;
		buffer &= (uint32_t)0x000000ff;

		NoWid[3] |= (buffer << (8*i));
		ret++;
	}
	//ʹ���Ӵ�
	if(DataBuf[RAM_NO1_OFFON])
	{enabl |= 1;}
	if(DataBuf[RAM_NO2_OFFON])
	{enabl |= 2;}
	if(DataBuf[RAM_NO3_OFFON])
	{enabl |= 4;}
	if(DataBuf[RAM_NO4_OFFON])
	{enabl |= 8;}

	//ȥ�����С����Ƶ�� ���
	for(i=0;i<4;i++)
	{
		if(enabl & (0x01<<i))
		{
			MAXf = i;MINf = i;
			break;
		}
	}
	for(i=MAXf;i<4;i++)
	{
		if(!(enabl & (0x01<<i)))
		{continue;}

		if(NoFre[MAXf] < NoFre[i])
		{MAXf = i;}

		if(NoFre[MINf] > NoFre[i])
		{MINf = i;}
	}

	//�õ���������Ƶ��
	fre = (NoFre[MINf] - (NoWid[MINf] / 2) + NoFre[MAXf] + (NoWid[MAXf] / 2))/2 ;
	ret = DataBuf + RAM_TX_CENTER_FREQ;
	for(i=0;i<4;i++)
	{
		*ret = (S8) (fre >> (8*i));
		ret++;
	}
	fre += 9216 ;	//10kHz
	RFFC2071_set(fre) ;

	//�õ���������Ƶ��
	fre -= 9216 ;	//10kHz
	fre -= 9500 ; //10kHz
	ret = DataBuf + RAM_RX_CENTER_FREQ;
	for(i=0;i<4;i++)
	{
		*ret = (S8) (fre >> (8*i));
		ret++;
	}
	fre -= 9216 ;	//10kHz
	RFFC2071_set(fre) ;

	CENTER_FREQ_FLAG = 0;		//clear flag

}
*/

// the unit of freq: 10Khz

uint8_t pll_set(uint32_t fre)
{
	S_RFFC2071_REG str;

	if ((fre > MAX_FRE) || (fre < MIN_FRE))
	{
		return 0;
	}
	else
	{

		RFFC2071_reset_device(&str); // ��������û����

		RFFC2071_REG_INIT(&str); 

		RFFC2071_PD_INIT(&str);

		RFFC2071_N_INIT(fre, &str); // 10kHz

		RFFC2071_setup_device(&str); // 1  д��11REG

		RFFC2071_set_calibration(&str); // 2 д��2REG

		RFFC2071_set_oper_freq(&str); // 3 VALUE_P1_FREQ1_P1N

		RFFC2071_set_calibration_mode(&str); // 4

		RFFC2071_enable_device(&str); // 5
		return 1;
	}
}

// bool pll_get_lockstate(void)
// {
// 	return RFFC2071_lock();
// }