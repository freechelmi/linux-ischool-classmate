/******************************************************************************
 * Copyright(c) 2008 - 2010 Realtek Corporation. All rights reserved.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110, USA
 *
 * The full GNU General Public License is included in this distribution in the
 * file called LICENSE.
 *
 * Contact Information:
 * wlanfae <wlanfae@realtek.com>
******************************************************************************/
#include "../rtl_core.h"

#ifdef _RTL8192_EXT_PATCH_
#include "../../../mshclass/msh_class.h"
#endif

DIG_T	DM_DigTable;
PS_T		DM_PSTable;
SWAT_T	DM_SWAT_Table;

#if 1
static u32 edca_setting_DL[HT_IOT_PEER_MAX] = 
{ 0xa44f, 		0x5ea44f, 	0x5e4322, 		0x5ea42b, 		0xa44f, 		0xa630, 		0xa630,		0xa44f,		0xa42b,		0xa42b};


static u32 edca_setting_UL[HT_IOT_PEER_MAX] = 
{ 0x5e4322, 	0xa44f, 		0x5e4322,			0x5ea32b,  		0x5ea422, 	0x5ea322,		0x3ea430,		0x5ea44f,		0x5e4322,		0x5e4322};
#endif

static u32 OFDMSwingTable[OFDM_TABLE_SIZE] = {
	0x7f8001fe, 
	0x788001e2, 
	0x71c001c7, 
	0x6b8001ae, 
	0x65400195, 
	0x5fc0017f, 
	0x5a400169, 
	0x55400155, 
	0x50800142, 
	0x4c000130, 
	0x47c0011f, 
	0x43c0010f, 
	0x40000100, 
	0x3c8000f2, 
	0x390000e4, 
	0x35c000d7, 
	0x32c000cb, 
	0x300000c0, 
	0x2d4000b5, 
	0x2ac000ab, 
	0x288000a2, 
	0x26000098, 
	0x24000090, 
	0x22000088, 
	0x20000080, 
	0x1e400079, 
	0x1c800072, 
	0x1b00006c, 
	0x19800066, 
	0x18000060, 
	0x16c0005b, 
	0x15800056, 
	0x14400051, 
	0x1300004c, 
	0x12000048, 
	0x11000044, 
	0x10000040, 
};


static u8 CCKSwingTable_Ch1_Ch13[CCK_TABLE_SIZE][8] = {
{0x36, 0x35, 0x2e, 0x25, 0x1c, 0x12, 0x09, 0x04},	
{0x33, 0x32, 0x2b, 0x23, 0x1a, 0x11, 0x08, 0x04},	
{0x30, 0x2f, 0x29, 0x21, 0x19, 0x10, 0x08, 0x03},	
{0x2d, 0x2d, 0x27, 0x1f, 0x18, 0x0f, 0x08, 0x03},	
{0x2b, 0x2a, 0x25, 0x1e, 0x16, 0x0e, 0x07, 0x03},	
{0x28, 0x28, 0x22, 0x1c, 0x15, 0x0d, 0x07, 0x03},	
{0x26, 0x25, 0x21, 0x1b, 0x14, 0x0d, 0x06, 0x03},	
{0x24, 0x23, 0x1f, 0x19, 0x13, 0x0c, 0x06, 0x03},	
{0x22, 0x21, 0x1d, 0x18, 0x11, 0x0b, 0x06, 0x02},	
{0x20, 0x20, 0x1b, 0x16, 0x11, 0x08, 0x05, 0x02},	
{0x1f, 0x1e, 0x1a, 0x15, 0x10, 0x0a, 0x05, 0x02},	
{0x1d, 0x1c, 0x18, 0x14, 0x0f, 0x0a, 0x05, 0x02},	
{0x1b, 0x1a, 0x17, 0x13, 0x0e, 0x09, 0x04, 0x02},	
{0x1a, 0x19, 0x16, 0x12, 0x0d, 0x09, 0x04, 0x02},	
{0x18, 0x17, 0x15, 0x11, 0x0c, 0x08, 0x04, 0x02},	
{0x17, 0x16, 0x13, 0x10, 0x0c, 0x08, 0x04, 0x02},	
{0x16, 0x15, 0x12, 0x0f, 0x0b, 0x07, 0x04, 0x01},	
{0x14, 0x14, 0x11, 0x0e, 0x0b, 0x07, 0x03, 0x02},	
{0x13, 0x13, 0x10, 0x0d, 0x0a, 0x06, 0x03, 0x01},	
{0x12, 0x12, 0x0f, 0x0c, 0x09, 0x06, 0x03, 0x01},	
{0x11, 0x11, 0x0f, 0x0c, 0x09, 0x06, 0x03, 0x01},	
{0x10, 0x10, 0x0e, 0x0b, 0x08, 0x05, 0x03, 0x01},	
{0x0f, 0x0f, 0x0d, 0x0b, 0x08, 0x05, 0x03, 0x01},	
{0x0e, 0x0e, 0x0c, 0x0a, 0x08, 0x05, 0x02, 0x01},	
{0x0d, 0x0d, 0x0c, 0x0a, 0x07, 0x05, 0x02, 0x01},	
{0x0d, 0x0c, 0x0b, 0x09, 0x07, 0x04, 0x02, 0x01},	
{0x0c, 0x0c, 0x0a, 0x09, 0x06, 0x04, 0x02, 0x01},	
{0x0b, 0x0b, 0x0a, 0x08, 0x06, 0x04, 0x02, 0x01},	
{0x0b, 0x0a, 0x09, 0x08, 0x06, 0x04, 0x02, 0x01},	
{0x0a, 0x0a, 0x09, 0x07, 0x05, 0x03, 0x02, 0x01},	
{0x0a, 0x09, 0x08, 0x07, 0x05, 0x03, 0x02, 0x01},	
{0x09, 0x09, 0x08, 0x06, 0x05, 0x03, 0x01, 0x01},	
{0x09, 0x08, 0x07, 0x06, 0x04, 0x03, 0x01, 0x01}	
};

static u8 CCKSwingTable_Ch14 [CCK_TABLE_SIZE][8]= {
{0x36, 0x35, 0x2e, 0x1b, 0x00, 0x00, 0x00, 0x00},	
{0x33, 0x32, 0x2b, 0x19, 0x00, 0x00, 0x00, 0x00},	
{0x30, 0x2f, 0x29, 0x18, 0x00, 0x00, 0x00, 0x00},	
{0x2d, 0x2d, 0x17, 0x17, 0x00, 0x00, 0x00, 0x00},	
{0x2b, 0x2a, 0x25, 0x15, 0x00, 0x00, 0x00, 0x00},	
{0x28, 0x28, 0x24, 0x14, 0x00, 0x00, 0x00, 0x00},	
{0x26, 0x25, 0x21, 0x13, 0x00, 0x00, 0x00, 0x00},	
{0x24, 0x23, 0x1f, 0x12, 0x00, 0x00, 0x00, 0x00},	
{0x22, 0x21, 0x1d, 0x11, 0x00, 0x00, 0x00, 0x00},	
{0x20, 0x20, 0x1b, 0x10, 0x00, 0x00, 0x00, 0x00},	
{0x1f, 0x1e, 0x1a, 0x0f, 0x00, 0x00, 0x00, 0x00},	
{0x1d, 0x1c, 0x18, 0x0e, 0x00, 0x00, 0x00, 0x00},	
{0x1b, 0x1a, 0x17, 0x0e, 0x00, 0x00, 0x00, 0x00},	
{0x1a, 0x19, 0x16, 0x0d, 0x00, 0x00, 0x00, 0x00},	
{0x18, 0x17, 0x15, 0x0c, 0x00, 0x00, 0x00, 0x00},	
{0x17, 0x16, 0x13, 0x0b, 0x00, 0x00, 0x00, 0x00},	
{0x16, 0x15, 0x12, 0x0b, 0x00, 0x00, 0x00, 0x00},	
{0x14, 0x14, 0x11, 0x0a, 0x00, 0x00, 0x00, 0x00},	
{0x13, 0x13, 0x10, 0x0a, 0x00, 0x00, 0x00, 0x00},	
{0x12, 0x12, 0x0f, 0x09, 0x00, 0x00, 0x00, 0x00},	
{0x11, 0x11, 0x0f, 0x09, 0x00, 0x00, 0x00, 0x00},	
{0x10, 0x10, 0x0e, 0x08, 0x00, 0x00, 0x00, 0x00},	
{0x0f, 0x0f, 0x0d, 0x08, 0x00, 0x00, 0x00, 0x00},	
{0x0e, 0x0e, 0x0c, 0x07, 0x00, 0x00, 0x00, 0x00},	
{0x0d, 0x0d, 0x0c, 0x07, 0x00, 0x00, 0x00, 0x00},	
{0x0d, 0x0c, 0x0b, 0x06, 0x00, 0x00, 0x00, 0x00},	
{0x0c, 0x0c, 0x0a, 0x06, 0x00, 0x00, 0x00, 0x00},	
{0x0b, 0x0b, 0x0a, 0x06, 0x00, 0x00, 0x00, 0x00},	
{0x0b, 0x0a, 0x09, 0x05, 0x00, 0x00, 0x00, 0x00},	
{0x0a, 0x0a, 0x09, 0x05, 0x00, 0x00, 0x00, 0x00},	
{0x0a, 0x09, 0x08, 0x05, 0x00, 0x00, 0x00, 0x00},	
{0x09, 0x09, 0x08, 0x05, 0x00, 0x00, 0x00, 0x00},	
{0x09, 0x08, 0x07, 0x04, 0x00, 0x00, 0x00, 0x00}	
};	


void DM_RFPathCheckWorkItemCallBack(void *data)
{}
void dm_TXPowerTrackingCallback_Dummy(void *data)
{}
/*-----------------------------------------------------------------------------
 * Function:	dm_DIGInit()
 *
 * Overview:	Set DIG scheme init value.
 *
 * Input:		NONE
 *
 * Output:		NONE
 *
 * Return:		NONE
 *
 * Revised History:
 *	When		Who		Remark
 *
 *---------------------------------------------------------------------------*/
void	dm_DIGInit(struct net_device *dev)
{


	DM_DigTable.Dig_Enable_Flag = true;
	DM_DigTable.Dig_Ext_Port_Stage = DIG_EXT_PORT_STAGE_MAX;
	
	DM_DigTable.CurIGValue = 0x20;
	DM_DigTable.PreIGValue = 0x0;

	DM_DigTable.CurSTAConnectState = DM_DigTable.PreSTAConnectState = DIG_STA_DISCONNECT;
	DM_DigTable.CurMultiSTAConnectState = DIG_MultiSTA_DISCONNECT;

	DM_DigTable.RssiLowThresh 	= DM_DIG_THRESH_LOW;
	DM_DigTable.RssiHighThresh 	= DM_DIG_THRESH_HIGH;

	DM_DigTable.FALowThresh	= DM_FALSEALARM_THRESH_LOW;
	DM_DigTable.FAHighThresh	= DM_FALSEALARM_THRESH_HIGH;

	
	DM_DigTable.rx_gain_range_max = DM_DIG_MAX;
	DM_DigTable.rx_gain_range_min = DM_DIG_MIN;

	DM_DigTable.BackoffVal = DM_DIG_BACKOFF_DEFAULT;
	DM_DigTable.BackoffVal_range_max = DM_DIG_BACKOFF_MAX;
	DM_DigTable.BackoffVal_range_min = DM_DIG_BACKOFF_MIN;

	DM_DigTable.PreCCKPDState = CCK_PD_STAGE_MAX;
	DM_DigTable.CurCCKPDState = CCK_PD_STAGE_MAX;
}

u8
dm_initial_gain_MinPWDB(struct net_device *dev)
{
	struct r8192_priv* priv = rtllib_priv(dev);
	long			Rssi_val_min = 0;
	if(	(DM_DigTable.CurMultiSTAConnectState == DIG_MultiSTA_CONNECT) &&
		(DM_DigTable.CurSTAConnectState == DIG_STA_CONNECT) )
	{
		if(priv->EntryMinUndecoratedSmoothedPWDB != 0)
			Rssi_val_min  =  (priv->EntryMinUndecoratedSmoothedPWDB > priv->undecorated_smoothed_pwdb)?
					priv->undecorated_smoothed_pwdb:priv->EntryMinUndecoratedSmoothedPWDB;		
		else
			Rssi_val_min = priv->undecorated_smoothed_pwdb;
	}
	else if(	DM_DigTable.CurSTAConnectState == DIG_STA_CONNECT || 
			DM_DigTable.CurSTAConnectState == DIG_STA_BEFORE_CONNECT) 
		Rssi_val_min = priv->undecorated_smoothed_pwdb;
	else if(DM_DigTable.CurMultiSTAConnectState == DIG_MultiSTA_CONNECT)
		Rssi_val_min = priv->EntryMinUndecoratedSmoothedPWDB;

	return (u8)Rssi_val_min;
}


void 
dm_FalseAlarmCounterStatistics(struct net_device *dev)
{
	u32 ret_value;
	struct r8192_priv* priv = rtllib_priv(dev);
	PFALSE_ALARM_STATISTICS FalseAlmCnt = &(priv->FalseAlmCnt);
	
	ret_value = PHY_QueryBBReg(dev, rOFDM_PHYCounter1, bMaskDWord);
       FalseAlmCnt->Cnt_Parity_Fail = ((ret_value&0xffff0000)>>16);	

       ret_value = PHY_QueryBBReg(dev, rOFDM_PHYCounter2, bMaskDWord);
	FalseAlmCnt->Cnt_Rate_Illegal = (ret_value&0xffff);
	FalseAlmCnt->Cnt_Crc8_fail = ((ret_value&0xffff0000)>>16);
	ret_value = PHY_QueryBBReg(dev, rOFDM_PHYCounter3, bMaskDWord);
	FalseAlmCnt->Cnt_Mcs_fail = (ret_value&0xffff);
	ret_value = PHY_QueryBBReg(dev, rOFDM0_FrameSync, bMaskDWord);
	FalseAlmCnt->Cnt_Fast_Fsync = (ret_value&0xffff);
	FalseAlmCnt->Cnt_SB_Search_fail = ((ret_value&0xffff0000)>>16);

	FalseAlmCnt->Cnt_Ofdm_fail = 	FalseAlmCnt->Cnt_Parity_Fail + FalseAlmCnt->Cnt_Rate_Illegal +
								FalseAlmCnt->Cnt_Crc8_fail + FalseAlmCnt->Cnt_Mcs_fail+
								FalseAlmCnt->Cnt_Fast_Fsync + FalseAlmCnt->Cnt_SB_Search_fail;

	
	PHY_SetBBReg(dev, rCCK0_FalseAlarmReport, BIT14, 1);
	
	ret_value = PHY_QueryBBReg(dev, rCCK0_FACounterLower, bMaskByte0);
	FalseAlmCnt->Cnt_Cck_fail = ret_value;

	ret_value = PHY_QueryBBReg(dev, rCCK0_FACounterUpper, bMaskByte3);
	FalseAlmCnt->Cnt_Cck_fail +=  (ret_value& 0xff)<<8;
	
	
	FalseAlmCnt->Cnt_all = (	FalseAlmCnt->Cnt_Parity_Fail +
						FalseAlmCnt->Cnt_Rate_Illegal +
						FalseAlmCnt->Cnt_Crc8_fail +
						FalseAlmCnt->Cnt_Mcs_fail +
						FalseAlmCnt->Cnt_Cck_fail);	
	
	PHY_SetBBReg(dev, rOFDM1_LSTF, 0x08000000, 1);
	PHY_SetBBReg(dev, rOFDM1_LSTF, 0x08000000, 0);
	PHY_SetBBReg(dev, rCCK0_FalseAlarmReport, 0x0000c000, 0);
	PHY_SetBBReg(dev, rCCK0_FalseAlarmReport, 0x0000c000, 2);

	RT_TRACE(	COMP_DIG, "Cnt_Parity_Fail = %d, Cnt_Rate_Illegal = %d, Cnt_Crc8_fail = %d, Cnt_Mcs_fail = %d\n", 
				FalseAlmCnt->Cnt_Parity_Fail, FalseAlmCnt->Cnt_Rate_Illegal, FalseAlmCnt->Cnt_Crc8_fail, FalseAlmCnt->Cnt_Mcs_fail);	
	RT_TRACE(	COMP_DIG, "Cnt_Fast_Fsync = %d, Cnt_SB_Search_fail = %d\n", 
				FalseAlmCnt->Cnt_Fast_Fsync, FalseAlmCnt->Cnt_SB_Search_fail);
	RT_TRACE(COMP_DIG, "Cnt_Ofdm_fail = %x, Cnt_Cck_fail = %x, Cnt_all = %x\n", 
				FalseAlmCnt->Cnt_Ofdm_fail, FalseAlmCnt->Cnt_Cck_fail , FalseAlmCnt->Cnt_all);		
}

void 
dm_CtrlInitGainByFA(struct net_device *dev)	
{
	struct r8192_priv* priv = rtllib_priv(dev);
	u8	value_IGI = DM_DigTable.CurIGValue;
	
	if(priv->FalseAlmCnt.Cnt_all < DM_DIG_FA_TH0)	
		value_IGI --;
	else if(priv->FalseAlmCnt.Cnt_all < DM_DIG_FA_TH1)	
		value_IGI += 0;
	else if(priv->FalseAlmCnt.Cnt_all < DM_DIG_FA_TH2)	
		value_IGI ++;
	else if(priv->FalseAlmCnt.Cnt_all >= DM_DIG_FA_TH2)	
		value_IGI +=2;
	
	if(value_IGI > DM_DIG_FA_UPPER)			
		value_IGI = DM_DIG_FA_UPPER;
	else if(value_IGI < DM_DIG_FA_LOWER)		
		value_IGI = DM_DIG_FA_LOWER;

	if(priv->FalseAlmCnt.Cnt_all > 10000)
		value_IGI = 0x32;
	DM_DigTable.CurIGValue = value_IGI;
	
	DM_Write_DIG(dev);
}

void
dm_CtrlInitGainByRssi(struct net_device *dev)	
{
	struct r8192_priv* priv = rtllib_priv(dev);

	u8 isBT;
	isBT = read_nic_byte(dev, 0x4fd) & 0x01;

	if(!isBT){
		if(priv->FalseAlmCnt.Cnt_all > DM_DigTable.FAHighThresh)
		{
			if((DM_DigTable.BackoffVal -2) < DM_DigTable.BackoffVal_range_min)
				DM_DigTable.BackoffVal = DM_DigTable.BackoffVal_range_min;
			else
				DM_DigTable.BackoffVal -= 2; 
		}	
		else if(priv->FalseAlmCnt.Cnt_all < DM_DigTable.FALowThresh)
		{
			if((DM_DigTable.BackoffVal+2) > DM_DigTable.BackoffVal_range_max)
				DM_DigTable.BackoffVal = DM_DigTable.BackoffVal_range_max;
			else
				DM_DigTable.BackoffVal +=2;
		}
	}
	else
		DM_DigTable.BackoffVal = DM_DIG_BACKOFF_DEFAULT;
	
	if((DM_DigTable.Rssi_val_min+10-DM_DigTable.BackoffVal) > DM_DigTable.rx_gain_range_max)
		DM_DigTable.CurIGValue = DM_DigTable.rx_gain_range_max;
	else if((DM_DigTable.Rssi_val_min+10-DM_DigTable.BackoffVal) < DM_DigTable.rx_gain_range_min)
		DM_DigTable.CurIGValue = DM_DigTable.rx_gain_range_min;
	else
		DM_DigTable.CurIGValue = DM_DigTable.Rssi_val_min+10-DM_DigTable.BackoffVal;

	RT_TRACE(COMP_DIG, "Rssi_val_min = %x BackoffVal %x\n", 
				DM_DigTable.Rssi_val_min, DM_DigTable.BackoffVal);

	DM_Write_DIG(dev);
}

void
dm_initial_gain_Multi_STA(struct net_device *dev)
{
	static u8		binitialized = false;
	struct r8192_priv* priv = rtllib_priv(dev);
	long 			rssi_strength =  priv->EntryMinUndecoratedSmoothedPWDB;	
	bool			bMulti_STA = false;

#if 0
#else
	if(priv->rtllib->iw_mode == IW_MODE_ADHOC)
		bMulti_STA = true;
#endif
	
	if(	(bMulti_STA == false) 
		|| (DM_DigTable.CurSTAConnectState != DIG_STA_DISCONNECT))
	{
		binitialized = false;
		DM_DigTable.Dig_Ext_Port_Stage = DIG_EXT_PORT_STAGE_MAX;
		return;
	}	
	else if(binitialized == false)
	{
		binitialized = true;
		DM_DigTable.Dig_Ext_Port_Stage = DIG_EXT_PORT_STAGE_0;
		DM_DigTable.CurIGValue = 0x20;
		DM_Write_DIG(dev);
	}

	if(DM_DigTable.CurMultiSTAConnectState == DIG_MultiSTA_CONNECT)
	{
		if (	(rssi_strength < DM_DigTable.RssiLowThresh) 	&& 
			(DM_DigTable.Dig_Ext_Port_Stage != DIG_EXT_PORT_STAGE_1))
		{					
			if(DM_DigTable.Dig_Ext_Port_Stage == DIG_EXT_PORT_STAGE_2)
			{
				DM_DigTable.CurIGValue = 0x20;
				DM_Write_DIG(dev);				
			}	
			DM_DigTable.Dig_Ext_Port_Stage = DIG_EXT_PORT_STAGE_1;	
		}	
		else if (rssi_strength > DM_DigTable.RssiHighThresh)
		{
			DM_DigTable.Dig_Ext_Port_Stage = DIG_EXT_PORT_STAGE_2;
			dm_CtrlInitGainByFA(dev);
		} 
	}	
	else if(DM_DigTable.Dig_Ext_Port_Stage != DIG_EXT_PORT_STAGE_0)
	{
		DM_DigTable.Dig_Ext_Port_Stage = DIG_EXT_PORT_STAGE_0;
		DM_DigTable.CurIGValue = 0x20;
		DM_Write_DIG(dev);
	}

	RT_TRACE(COMP_DIG, "CurMultiSTAConnectState = %x Dig_Ext_Port_Stage %x\n", 
				DM_DigTable.CurMultiSTAConnectState, DM_DigTable.Dig_Ext_Port_Stage);
}


void 
dm_initial_gain_STA(struct net_device *dev)
{
	
	RT_TRACE(COMP_DIG, "PreSTAConnectState = %x, CurSTAConnectState = %x\n", 
				DM_DigTable.PreSTAConnectState, DM_DigTable.CurSTAConnectState);


	if(DM_DigTable.PreSTAConnectState == DM_DigTable.CurSTAConnectState||
	   DM_DigTable.CurSTAConnectState == DIG_STA_BEFORE_CONNECT ||
	   DM_DigTable.CurSTAConnectState == DIG_STA_CONNECT)
	{
		if(	DM_DigTable.CurSTAConnectState != DIG_STA_DISCONNECT)
		{
			DM_DigTable.Rssi_val_min = dm_initial_gain_MinPWDB(dev);
			dm_CtrlInitGainByRssi(dev);
		}	
	}
	else	
	{		
		DM_DigTable.Rssi_val_min = 0;
		DM_DigTable.Dig_Ext_Port_Stage = DIG_EXT_PORT_STAGE_MAX;
		DM_DigTable.BackoffVal = DM_DIG_BACKOFF_DEFAULT;
		DM_DigTable.CurIGValue = 0x20;
		DM_DigTable.PreIGValue = 0;	
		DM_Write_DIG(dev);
	}
}

void dm_CCK_PacketDetectionThresh(struct net_device *dev)
{
	struct r8192_priv* priv = rtllib_priv(dev);
	
	if(DM_DigTable.CurSTAConnectState == DIG_STA_CONNECT)
	{
		DM_DigTable.Rssi_val_min = dm_initial_gain_MinPWDB(dev);
		if(DM_DigTable.PreCCKPDState == CCK_PD_STAGE_LowRssi)
		{
			if(DM_DigTable.Rssi_val_min <= 25)
				DM_DigTable.CurCCKPDState = CCK_PD_STAGE_LowRssi;
			else
				DM_DigTable.CurCCKPDState = CCK_PD_STAGE_HighRssi;
		}
		else{
			if(DM_DigTable.Rssi_val_min <= 20)
				DM_DigTable.CurCCKPDState = CCK_PD_STAGE_LowRssi;
			else
				DM_DigTable.CurCCKPDState = CCK_PD_STAGE_HighRssi;
		}
	}
	else
		DM_DigTable.CurCCKPDState=CCK_PD_STAGE_MAX;
	
	if(DM_DigTable.PreCCKPDState != DM_DigTable.CurCCKPDState)
	{
		if(DM_DigTable.CurCCKPDState == CCK_PD_STAGE_LowRssi)
		{
			if(priv->FalseAlmCnt.Cnt_Cck_fail > 800)
				DM_DigTable.CurCCKFAState = CCK_FA_STAGE_High;				
			else
				DM_DigTable.CurCCKFAState = CCK_FA_STAGE_Low;
			
			if(DM_DigTable.PreCCKFAState != DM_DigTable.CurCCKFAState)
			{
				if(DM_DigTable.CurCCKFAState == CCK_FA_STAGE_Low)
					PHY_SetBBReg(dev, rCCK0_CCA, bMaskByte2, 0x83);
				else
					PHY_SetBBReg(dev, rCCK0_CCA, bMaskByte2, 0xcd);
				DM_DigTable.PreCCKFAState = DM_DigTable.CurCCKFAState;
			}
			
			PHY_SetBBReg(dev, rCCK0_System, bMaskByte1, 0x40);
			if(IS_92C_SERIAL(priv->card_8192_version))
				PHY_SetBBReg(dev, rCCK0_FalseAlarmReport , bMaskByte2, 0xd7);
		}
		else
		{
			PHY_SetBBReg(dev, rCCK0_CCA, bMaskByte2, 0xcd);
			PHY_SetBBReg(dev,rCCK0_System, bMaskByte1, 0x47);
			if(IS_92C_SERIAL(priv->card_8192_version))
				PHY_SetBBReg(dev, rCCK0_FalseAlarmReport , bMaskByte2, 0xd3);
		}
		DM_DigTable.PreCCKPDState = DM_DigTable.CurCCKPDState;
	}
	RT_TRACE(	COMP_DIG, "CCKPDStage=%x\n",DM_DigTable.CurCCKPDState);
	RT_TRACE(	COMP_DIG, "is92C=%x\n",IS_92C_SERIAL(priv->card_8192_version));
}


static	void
dm_CtrlInitGainByTwoPort(struct net_device *dev)
{
	struct r8192_priv* priv = rtllib_priv(dev);
	
	if(rtllib_act_scanning(priv->rtllib,false) == true)
		return;

	if((priv->rtllib->state > RTLLIB_NOLINK) && (priv->rtllib->state < RTLLIB_LINKED))
		DM_DigTable.CurSTAConnectState = DIG_STA_BEFORE_CONNECT;
	else if(priv->rtllib->state >= RTLLIB_LINKED)
		DM_DigTable.CurSTAConnectState = DIG_STA_CONNECT;
	else
		DM_DigTable.CurSTAConnectState = DIG_STA_DISCONNECT;

	dm_initial_gain_STA(dev);	
	dm_initial_gain_Multi_STA(dev);
	dm_CCK_PacketDetectionThresh(dev);
	
	DM_DigTable.PreSTAConnectState = DM_DigTable.CurSTAConnectState;
}


void dm_DIG(struct net_device *dev)
{
	struct r8192_priv* priv = rtllib_priv(dev);
	
	RTPRINT(FDM, DM_Monitor, ("dm_DIG() ==>\n"));
	
	if(priv->bDMInitialGainEnable == false)
		return;
	
	if (DM_DigTable.Dig_Enable_Flag == false)
		return;
	
	RTPRINT(FDM, DM_Monitor, ("dm_DIG() progress \n"));

	dm_CtrlInitGainByTwoPort(dev);
	
	RTPRINT(FDM, DM_Monitor, ("dm_DIG() <==\n"));
}

void
DM_ChangeDynamicInitGainThresh(
	struct net_device *dev,
	u32		DM_Type,
	u32		DM_Value)
{
	if (DM_Type == DIG_TYPE_THRESH_HIGH)
	{
		DM_DigTable.RssiHighThresh = DM_Value;		
	}
	else if (DM_Type == DIG_TYPE_THRESH_LOW)
	{
		DM_DigTable.RssiLowThresh = DM_Value;
	}
	else if (DM_Type == DIG_TYPE_ENABLE)
	{
		DM_DigTable.Dig_Enable_Flag	= true;
	}	
	else if (DM_Type == DIG_TYPE_DISABLE)
	{
		DM_DigTable.Dig_Enable_Flag = false;
	}	
	else if (DM_Type == DIG_TYPE_BACKOFF)
	{
		if(DM_Value > 30)
			DM_Value = 30;
		DM_DigTable.BackoffVal = (u8)DM_Value;
	}
	else if(DM_Type == DIG_TYPE_RX_GAIN_MIN)
	{
		if(DM_Value == 0)
			DM_Value = 0x1;
		DM_DigTable.rx_gain_range_min = (u8)DM_Value;
	}
	else if(DM_Type == DIG_TYPE_RX_GAIN_MAX)
	{
		if(DM_Value > 0x50)
			DM_Value = 0x50;
		DM_DigTable.rx_gain_range_max = (u8)DM_Value;
	}
}	/* DM_ChangeDynamicInitGainThresh */

void
DM_Write_DIG(struct net_device *dev)
{
	RT_TRACE(COMP_DIG, "CurIGValue = 0x%x, PreIGValue = 0x%x, BackoffVal = %d\n", 
				DM_DigTable.CurIGValue, DM_DigTable.PreIGValue, DM_DigTable.BackoffVal);
	
	if(DM_DigTable.PreIGValue != DM_DigTable.CurIGValue)
	{

		PHY_SetBBReg(dev, rOFDM0_XAAGCCore1, 0x7f, DM_DigTable.CurIGValue);
		PHY_SetBBReg(dev, rOFDM0_XBAGCCore1, 0x7f, DM_DigTable.CurIGValue);
	
		DM_DigTable.PreIGValue = DM_DigTable.CurIGValue;
	}
}


void dm_InitDynamicTxPower(struct net_device *dev)
{
	struct r8192_priv* priv = rtllib_priv(dev);

#ifdef ENABLE_DYNAMIC_TXPOWER
	priv->rtllib->bdynamic_txpower_enable = true; 
#else
	priv->rtllib->bdynamic_txpower_enable = false; 
#endif

	priv->LastDTPLvl = TxHighPwrLevel_Normal;
	priv->DynamicTxHighPowerLvl = TxHighPwrLevel_Normal;
}

void dm_DynamicTxPower(struct net_device *dev)
{
	struct r8192_priv* priv = rtllib_priv(dev);
	long	UndecoratedSmoothedPWDB;

	if(!priv->rtllib->bdynamic_txpower_enable)
		return;
	
	if( (priv->DMFlag & HAL_DM_HIPWR_DISABLE) ||
		priv->rtllib->pHTInfo->IOTAction & HT_IOT_ACT_DISABLE_HIGH_POWER)
	{
		priv->DynamicTxHighPowerLvl = TxHighPwrLevel_Normal;
		return;
	}

	if((priv->rtllib->state < RTLLIB_LINKED) &&	
		(priv->EntryMinUndecoratedSmoothedPWDB == 0))
	{
		RT_TRACE(COMP_POWER, "Not connected to any \n");
		priv->DynamicTxHighPowerLvl = TxHighPwrLevel_Normal;

		 priv->LastDTPLvl=TxHighPwrLevel_Normal;
		return;
	}
	
	if(priv->rtllib->state >= RTLLIB_LINKED)	
	{
		if(priv->rtllib->iw_mode == IW_MODE_ADHOC)
		{
			UndecoratedSmoothedPWDB = priv->EntryMinUndecoratedSmoothedPWDB;
			RT_TRACE(COMP_POWER, "AP Client PWDB = 0x%lx \n", UndecoratedSmoothedPWDB);
		}
		else
		{
			UndecoratedSmoothedPWDB = priv->undecorated_smoothed_pwdb;
			RT_TRACE(COMP_POWER, "STA Default Port PWDB = 0x%lx \n", UndecoratedSmoothedPWDB);
		}
	}
	else 
	{	
		UndecoratedSmoothedPWDB = priv->EntryMinUndecoratedSmoothedPWDB;
		RT_TRACE(COMP_POWER, "AP Ext Port PWDB = 0x%lx \n", UndecoratedSmoothedPWDB);
	}
		
	if(UndecoratedSmoothedPWDB >= TX_POWER_NEAR_FIELD_THRESH_LVL2)
	{
		priv->DynamicTxHighPowerLvl = TxHighPwrLevel_Level1;
		RT_TRACE(COMP_POWER, "TxHighPwrLevel_Level1 (TxPwr=0x0)\n");
	}
	else if((UndecoratedSmoothedPWDB < (TX_POWER_NEAR_FIELD_THRESH_LVL2-3)) &&
		(UndecoratedSmoothedPWDB >= TX_POWER_NEAR_FIELD_THRESH_LVL1) )
	{
		priv->DynamicTxHighPowerLvl = TxHighPwrLevel_Level1;
		RT_TRACE(COMP_POWER, "TxHighPwrLevel_Level1 (TxPwr=0x10)\n");
	}
	else if(UndecoratedSmoothedPWDB < (TX_POWER_NEAR_FIELD_THRESH_LVL1-5))
	{
		priv->DynamicTxHighPowerLvl = TxHighPwrLevel_Normal;
		RT_TRACE(COMP_POWER, "TxHighPwrLevel_Normal\n");
	}

	if( (priv->DynamicTxHighPowerLvl != priv->LastDTPLvl) )
	{
		RT_TRACE(COMP_POWER, "PHY_SetTxPowerLevel8192S() Channel = %d \n" , priv->rtllib->current_network.channel);
		PHY_SetTxPowerLevel8192C(dev, priv->rtllib->current_network.channel);
	}
	priv->LastDTPLvl = priv->DynamicTxHighPowerLvl;
}

void
DM_InitEdcaTurbo(struct net_device *dev)
{
	struct r8192_priv* priv = rtllib_priv(dev);

	priv->bcurrent_turbo_EDCA = false;
	priv->bis_any_nonbepkts = false;
	priv->bis_cur_rdlstate = false;
	
}	

void
dm_CheckEdcaTurbo(struct net_device *dev)
{
	struct r8192_priv* priv = rtllib_priv(dev);

	static u64		lastTxOkCnt = 0;
	static u64		lastRxOkCnt = 0;
	u64			curTxOkCnt = 0;
	u64			curRxOkCnt = 0;	
	u32			EDCA_BE_UL = 0x5ea42b;
	u32			EDCA_BE_DL = 0x5ea42b;

	bool			bBtChangeEDCA = false;
	
	static u32		lastBtEdcaUL = 0;
	static u32		lastBtEdcaDL = 0;
	
	if((priv->rtllib->pHTInfo->IOTPeer == HT_IOT_PEER_MARVELL) || (priv->rf_type == RF_1T1R)){
		EDCA_BE_UL = edca_setting_UL[priv->rtllib->pHTInfo->IOTPeer];
		EDCA_BE_DL = edca_setting_DL[priv->rtllib->pHTInfo->IOTPeer];
	}

	
	if(priv->rtllib->mode & (WIRELESS_MODE_G | WIRELESS_MODE_B)){
		EDCA_BE_UL = 0x5ea42b;
		EDCA_BE_DL = 0x5ea42b;
	}

#if 1


	if((lastBtEdcaUL != priv->bt_coexist.BtEdcaUL) ||
		(lastBtEdcaDL != priv->bt_coexist.BtEdcaDL))
			{
		priv->bcurrent_turbo_EDCA = false;
		lastBtEdcaUL = priv->bt_coexist.BtEdcaUL;
		lastBtEdcaDL = priv->bt_coexist.BtEdcaDL;
				}
	
	if(priv->bt_coexist.BtEdcaUL != 0)
				{
		EDCA_BE_UL = priv->bt_coexist.BtEdcaUL;
					bBtChangeEDCA = true;
				}

	if(priv->bt_coexist.BtEdcaDL != 0)
			{
		EDCA_BE_DL = priv->bt_coexist.BtEdcaDL;
		bBtChangeEDCA = true;
	}
	
#endif

	if(priv->rtllib->iw_mode == IW_MODE_ADHOC)
		goto dm_CheckEdcaTurbo_EXIT;

	if(priv->rtllib->pHTInfo->IOTAction & HT_IOT_ACT_DISABLE_EDCA_TURBO)
		goto dm_CheckEdcaTurbo_EXIT;

	if(priv->rtllib->state != RTLLIB_LINKED)
	{
		priv->bcurrent_turbo_EDCA = false;
		return;
	}

	if((!priv->bDisableFrameBursting) && (!priv->bt_coexist.BluetoothCoexist) &&
		(priv->rtllib->pHTInfo->IOTAction & (HT_IOT_ACT_FORCED_ENABLE_BE_TXOP|HT_IOT_ACT_AMSDU_ENABLE)))
	{
		if(!(EDCA_BE_UL & 0xffff0000))
			EDCA_BE_UL |= 0x005e0000; 
		if(!(EDCA_BE_DL & 0xffff0000))
			EDCA_BE_DL |= 0x005e0000; 
	}
	
	if(!bBtChangeEDCA)
	{
		if(priv->rtllib->pHTInfo->IOTPeer == HT_IOT_PEER_CISCO && (priv->rtllib->mode & (WIRELESS_MODE_N_24G)))
		{
			EDCA_BE_DL = edca_setting_DL[priv->rtllib->pHTInfo->IOTPeer];
			EDCA_BE_UL = edca_setting_UL[priv->rtllib->pHTInfo->IOTPeer];
		}
		else if(priv->rtllib->pHTInfo->IOTPeer == HT_IOT_PEER_AIRGO && (priv->rtllib->mode & (WIRELESS_MODE_G ||WIRELESS_MODE_B)))
		{
			EDCA_BE_DL = 0xa630;
		}		
	}


	if((bBtChangeEDCA) || ((!priv->bis_any_nonbepkts) && (!priv->bDisableFrameBursting)))
	{
				
		curTxOkCnt = priv->stats.txbytesunicast - lastTxOkCnt;
		curRxOkCnt = priv->stats.rxbytesunicast - lastRxOkCnt;

		if((priv->rtllib->pHTInfo->IOTAction & HT_IOT_ACT_EDCA_BIAS_ON_RX) && (priv->rf_type == RF_1T2R))
		{
			if(curTxOkCnt > 4*curRxOkCnt)
			{
				if(priv->bis_cur_rdlstate || !priv->bcurrent_turbo_EDCA)
				{
					write_nic_dword(dev, REG_EDCA_BE_PARAM, EDCA_BE_UL);
					priv->bis_cur_rdlstate = false;
				}
			}
			else
			{
				if(!priv->bis_cur_rdlstate || !priv->bcurrent_turbo_EDCA)
				{
					write_nic_dword(dev, REG_EDCA_BE_PARAM, EDCA_BE_DL);
					priv->bis_cur_rdlstate = true;
				}
			}
			priv->bcurrent_turbo_EDCA = true;
		}
		else
		{

			if(curRxOkCnt > 4*curTxOkCnt)
			{

				if(!priv->bis_cur_rdlstate || !priv->bcurrent_turbo_EDCA)
				{
					write_nic_dword(dev, REG_EDCA_BE_PARAM, EDCA_BE_DL);
					priv->bis_cur_rdlstate = true;
				}
			}
			else
			{

				if(priv->bis_cur_rdlstate || !priv->bcurrent_turbo_EDCA)
				{
					write_nic_dword(dev, REG_EDCA_BE_PARAM, EDCA_BE_UL);
					priv->bis_cur_rdlstate = false;
				}
			}
			priv->bcurrent_turbo_EDCA = true;
		}
	}
	else
	{

		 if(priv->bcurrent_turbo_EDCA)
		{
			u8 tmp = AC0_BE;
			priv->rtllib->SetHwRegHandler(dev, HW_VAR_AC_PARAM, (u8*)(&tmp) );
			priv->bcurrent_turbo_EDCA = false;
		}
	}

dm_CheckEdcaTurbo_EXIT:
	priv->bis_any_nonbepkts = false;
	lastTxOkCnt = priv->stats.txbytesunicast;
	lastRxOkCnt = priv->stats.rxbytesunicast;
}	

#define		DPK_DELTA_MAPPING_NUM	13
#define		index_mapping_HP_NUM	15	
static	void
dm_TXPowerTrackingCallback_ThermalMeter_92C(struct net_device *dev)
{
#if 1
	struct r8192_priv* priv = rtllib_priv(dev);
	u8			ThermalValue = 0, delta, delta_LCK, delta_IQK, delta_HP;
	char		delta_DPK;
	long 		ele_A = 0, ele_D, TempCCk, X, value32;
	long		Y, ele_C = 0;
	u8		OFDM_index[2], CCK_index = 0, OFDM_index_old[2], CCK_index_old = 0;
	int	    	i = 0;
	bool		is2T = IS_92C_SERIAL(priv->card_8192_version);
	u8			TxPwrLevel[2] = {0,0};
	u8			OFDM_min_index = 6, rf; 

	u32			DPK_delta_mapping[2][DPK_DELTA_MAPPING_NUM] = {
					{0x1c, 0x1c, 0x1d, 0x1d, 0x1e, 
					 0x1f, 0x00, 0x00, 0x01, 0x01,
					 0x02, 0x02, 0x03},
					{0x1c, 0x1d, 0x1e, 0x1e, 0x1e,
					 0x1f, 0x00, 0x00, 0x01, 0x02,
					 0x02, 0x03, 0x03}};
	
	
	priv->btxpower_trackingInit = true;

	RT_TRACE(COMP_POWER_TRACKING, "===>dm_TXPowerTrackingCallback_ThermalMeter_92C\n");

	ThermalValue = (u8)PHY_QueryRFReg(dev, RF90_PATH_A, RF_T_METER, 0x1f);	
	RT_TRACE(COMP_POWER_TRACKING, "Readback Thermal Meter = 0x%x pre thermal meter 0x%x EEPROMthermalmeter 0x%x\n", ThermalValue, priv->ThermalValue, priv->EEPROMThermalMeter);

	PHY_APCalibrate(dev, (ThermalValue - priv->EEPROMThermalMeter));
	PHY_DigitalPredistortion(dev);

	if(is2T)
		rf = 2;
	else
		rf = 1;
	
#ifdef MERGE_TO_DO 
	while(PlatformAtomicExchange(dev, &priv->IntrCCKRefCount, true) == true) 
	{
		udelay(100);
		TimeOut--;
		if(TimeOut <= 0)
		{
			RTPRINT(FINIT, INIT_TxPower, 
			 ("!!!dm_TXPowerTrackingCallback_ThermalMeter_92C Wait for check CCK gain index too long!!!\n" ));
			break;
		}
	}
#endif

	if(ThermalValue)
	{
		{
			ele_D = PHY_QueryBBReg(dev, rOFDM0_XATxIQImbalance, bMaskDWord)&bMaskOFDM_D;
			for(i=0; i<OFDM_Table_Length; i++)	
			{
				if(ele_D == (OFDMSwingTable[i]&bMaskOFDM_D))
				{
					OFDM_index_old[0] = (u8)i;
					RT_TRACE(COMP_POWER_TRACKING, "Initial pathA ele_D reg0x%x = 0x%lx, OFDM_index=0x%x\n", 
						rOFDM0_XATxIQImbalance, ele_D, OFDM_index_old[0]);
					break;
				}
			}

			if(is2T)
			{
				ele_D = PHY_QueryBBReg(dev, rOFDM0_XBTxIQImbalance, bMaskDWord)&bMaskOFDM_D;
				for(i=0; i<OFDM_Table_Length; i++)	
				{
					if(ele_D == (OFDMSwingTable[i]&bMaskOFDM_D))
					{
						OFDM_index_old[1] = (u8)i;
						RT_TRACE(COMP_POWER_TRACKING, "Initial pathB ele_D reg0x%x = 0x%lx, OFDM_index=0x%x\n", 
							rOFDM0_XBTxIQImbalance, ele_D, OFDM_index_old[1]);
						break;
					}
				}
			}

			TempCCk = PHY_QueryBBReg(dev, rCCK0_TxFilter2, bMaskDWord)&bMaskCCK;
			for(i=0 ; i<CCK_Table_length ; i++)
			{
				if(priv->bCCKinCH14)
				{
					if(memcmp((void*)&TempCCk, (void*)&CCKSwingTable_Ch14[i][2], 4)==0)
					{
						CCK_index_old =(u8) i;
						RT_TRACE(COMP_POWER_TRACKING, "Initial reg0x%x = 0x%lx, CCK_index=0x%x, ch 14 %d\n", 
							rCCK0_TxFilter2, TempCCk, CCK_index_old, priv->bCCKinCH14);
						break;
					}
				}
				else
				{
					if(memcmp((void*)&TempCCk, (void*)&CCKSwingTable_Ch1_Ch13[i][2], 4)==0)
					{
						CCK_index_old =(u8) i;
						RT_TRACE(COMP_POWER_TRACKING, "Initial reg0x%x = 0x%lx, CCK_index=0x%x, ch14 %d\n", 
							rCCK0_TxFilter2, TempCCk, CCK_index_old, priv->bCCKinCH14);
						break;
					}			
				}
			}	

			if(!priv->ThermalValue)
			{
				priv->ThermalValue = priv->EEPROMThermalMeter;
				priv->ThermalValue_LCK = ThermalValue;				
				priv->ThermalValue_IQK = ThermalValue;	
				priv->ThermalValue_DPK = priv->EEPROMThermalMeter;
				
				for(i = 0; i < rf; i++)
					priv->OFDM_index[i] = OFDM_index_old[i];
				priv->CCK_index = CCK_index_old;
			}			
		}
		
		delta = (ThermalValue > priv->ThermalValue)?(ThermalValue - priv->ThermalValue):(priv->ThermalValue - ThermalValue);
		delta_HP = 0;			
		delta_LCK = (ThermalValue > priv->ThermalValue_LCK)?(ThermalValue - priv->ThermalValue_LCK):(priv->ThermalValue_LCK - ThermalValue);
		delta_IQK = (ThermalValue > priv->ThermalValue_IQK)?(ThermalValue - priv->ThermalValue_IQK):(priv->ThermalValue_IQK - ThermalValue);
		delta_DPK = priv->ThermalValue_DPK - ThermalValue;
		
		RT_TRACE(COMP_POWER_TRACKING, "Readback Thermal Meter = 0x%x pre thermal meter 0x%x EEPROMthermalmeter 0x%x delta 0x%x delta_LCK 0x%x delta_IQK 0x%x\n", ThermalValue, priv->ThermalValue, priv->EEPROMThermalMeter, delta, delta_LCK, delta_IQK);

		if(delta_LCK > 1)
		{
			priv->ThermalValue_LCK = ThermalValue;
			PHY_LCCalibrate(dev);
		}
		
		if((delta > 0 || delta_HP > 0) && priv->TxPowerTrackControl)
		{
			if(ThermalValue > priv->ThermalValue)
			{ 
				for(i = 0; i < rf; i++)
				 	priv->OFDM_index[i] -= delta;
				priv->CCK_index -= delta;
			}
			else
			{
				for(i = 0; i < rf; i++)			
					priv->OFDM_index[i] += delta;
				priv->CCK_index += delta;
			}
			
			if(is2T)
			{
				RT_TRACE(COMP_POWER_TRACKING, "temp OFDM_A_index=0x%x, OFDM_B_index=0x%x, CCK_index=0x%x\n", 
					priv->OFDM_index[0], priv->OFDM_index[1], priv->CCK_index);			
			}
			else
			{
				RT_TRACE(COMP_POWER_TRACKING, "temp OFDM_A_index=0x%x, CCK_index=0x%x\n", 
					priv->OFDM_index[0], priv->CCK_index);			
			}
			
			if(ThermalValue > priv->EEPROMThermalMeter)
			{
				for(i = 0; i < rf; i++)			
					OFDM_index[i] = priv->OFDM_index[i]+1;
				CCK_index = priv->CCK_index+1;			
			}
			else
			{
				for(i = 0; i < rf; i++)			
					OFDM_index[i] = priv->OFDM_index[i];
				CCK_index = priv->CCK_index;						
			}

			for(i = 0; i < rf; i++)
			{
				if(TxPwrLevel[i] >=0 && TxPwrLevel[i] <=26)
				{
					if(ThermalValue > priv->EEPROMThermalMeter)
					{
						if (delta < 5)
							OFDM_index[i] -= 1;					
						else 
							OFDM_index[i] -= 2;					
					}
					else if(delta > 5 && ThermalValue < priv->EEPROMThermalMeter)
					{
						OFDM_index[i] += 1;
					}
				}
				else if (TxPwrLevel[i] >= 27 && TxPwrLevel[i] <= 32 && ThermalValue > priv->EEPROMThermalMeter)
				{
					if (delta < 5)
						OFDM_index[i] -= 1;					
					else 
						OFDM_index[i] -= 2;								
				}
				else if (TxPwrLevel[i] >= 32 && TxPwrLevel[i] <= 38 && ThermalValue > priv->EEPROMThermalMeter && delta > 5)
				{
					OFDM_index[i] -= 1;								
				}
			}

			{
				if(TxPwrLevel[i] >=0 && TxPwrLevel[i] <=26)
				{
					if(ThermalValue > priv->EEPROMThermalMeter)
					{
						if (delta < 5)
							CCK_index -= 1; 				
						else 
							CCK_index -= 2; 				
					}
					else if(delta > 5 && ThermalValue < priv->EEPROMThermalMeter)
					{
						CCK_index += 1;
					}
				}
				else if (TxPwrLevel[i] >= 27 && TxPwrLevel[i] <= 32 && ThermalValue > priv->EEPROMThermalMeter)
				{
					if (delta < 5)
						CCK_index -= 1; 				
					else 
						CCK_index -= 2; 							
				}
				else if (TxPwrLevel[i] >= 32 && TxPwrLevel[i] <= 38 && ThermalValue > priv->EEPROMThermalMeter && delta > 5)
				{
					CCK_index -= 1; 							
				}
			}
			
			for(i = 0; i < rf; i++)
			{
				if(OFDM_index[i] > (OFDM_TABLE_SIZE-1))
					OFDM_index[i] = (OFDM_TABLE_SIZE-1);
				else if (OFDM_index[i] < OFDM_min_index)
					OFDM_index[i] = OFDM_min_index;
			}
						
			if(CCK_index > (CCK_TABLE_SIZE-1))
				CCK_index = (CCK_TABLE_SIZE-1);
			else if (CCK_index < 0)
				CCK_index = 0;		

			if(is2T)
			{
				RT_TRACE(COMP_POWER_TRACKING, "new OFDM_A_index=0x%x, OFDM_B_index=0x%x, CCK_index=0x%x\n", 
					OFDM_index[0], OFDM_index[1], CCK_index);
			}
			else
			{
				RT_TRACE(COMP_POWER_TRACKING, "new OFDM_A_index=0x%x, CCK_index=0x%x\n", 
					OFDM_index[0], CCK_index);			
			}
		}

		if(priv->TxPowerTrackControl && (delta != 0 || delta_HP != 0))
		{
			ele_D = (OFDMSwingTable[OFDM_index[0]] & 0xFFC00000)>>22;
			X = priv->RegE94;
			Y = priv->RegE9C;		

			if(X != 0)
			{
				if ((X & 0x00000200) != 0)
					X = X | 0xFFFFFC00;
				ele_A = ((X * ele_D)>>8)&0x000003FF;
					
				if ((Y & 0x00000200) != 0)
					Y = Y | 0xFFFFFC00;
				ele_C = ((Y * ele_D)>>8)&0x000003FF;
				
				value32 = (ele_D<<22)|((ele_C&0x3F)<<16)|ele_A;
				PHY_SetBBReg(dev, rOFDM0_XATxIQImbalance, bMaskDWord, value32);
				
				value32 = (ele_C&0x000003C0)>>6;
				PHY_SetBBReg(dev, rOFDM0_XCTxAFE, bMaskH4Bits, value32);

				value32 = ((X * ele_D)>>7)&0x01;
				PHY_SetBBReg(dev, rOFDM0_ECCAThreshold, BIT31, value32);

				value32 = ((Y * ele_D)>>7)&0x01;
				PHY_SetBBReg(dev, rOFDM0_ECCAThreshold, BIT29, value32);
				
			}
			else
			{
				PHY_SetBBReg(dev, rOFDM0_XATxIQImbalance, bMaskDWord, OFDMSwingTable[OFDM_index[0]]);				
				PHY_SetBBReg(dev, rOFDM0_XCTxAFE, bMaskH4Bits, 0x00);
				PHY_SetBBReg(dev, rOFDM0_ECCAThreshold, BIT31|BIT29, 0x00);			
			}

			RTPRINT(FINIT, INIT_IQK, ("TxPwrTracking path A: X = 0x%lx, Y = 0x%lx ele_A = 0x%lx ele_C = 0x%lx ele_D = 0x%lx\n", X, Y, ele_A, ele_C, ele_D));		

			if(!priv->bCCKinCH14){
				write_nic_byte(dev, 0xa22, CCKSwingTable_Ch1_Ch13[CCK_index][0]);
				write_nic_byte(dev, 0xa23, CCKSwingTable_Ch1_Ch13[CCK_index][1]);
				write_nic_byte(dev, 0xa24, CCKSwingTable_Ch1_Ch13[CCK_index][2]);
				write_nic_byte(dev, 0xa25, CCKSwingTable_Ch1_Ch13[CCK_index][3]);
				write_nic_byte(dev, 0xa26, CCKSwingTable_Ch1_Ch13[CCK_index][4]);
				write_nic_byte(dev, 0xa27, CCKSwingTable_Ch1_Ch13[CCK_index][5]);
				write_nic_byte(dev, 0xa28, CCKSwingTable_Ch1_Ch13[CCK_index][6]);
				write_nic_byte(dev, 0xa29, CCKSwingTable_Ch1_Ch13[CCK_index][7]);		
			}
			else{
				write_nic_byte(dev, 0xa22, CCKSwingTable_Ch14[CCK_index][0]);
				write_nic_byte(dev, 0xa23, CCKSwingTable_Ch14[CCK_index][1]);
				write_nic_byte(dev, 0xa24, CCKSwingTable_Ch14[CCK_index][2]);
				write_nic_byte(dev, 0xa25, CCKSwingTable_Ch14[CCK_index][3]);
				write_nic_byte(dev, 0xa26, CCKSwingTable_Ch14[CCK_index][4]);
				write_nic_byte(dev, 0xa27, CCKSwingTable_Ch14[CCK_index][5]);
				write_nic_byte(dev, 0xa28, CCKSwingTable_Ch14[CCK_index][6]);
				write_nic_byte(dev, 0xa29, CCKSwingTable_Ch14[CCK_index][7]);	
			}		

			if(is2T)
			{						
				ele_D = (OFDMSwingTable[OFDM_index[1]] & 0xFFC00000)>>22;
				
				X = priv->RegEB4;
				Y = priv->RegEBC;
				
				if(X != 0){
					if ((X & 0x00000200) != 0)	
						X = X | 0xFFFFFC00;
					ele_A = ((X * ele_D)>>8)&0x000003FF;
					
					if ((Y & 0x00000200) != 0)
						Y = Y | 0xFFFFFC00;
					ele_C = ((Y * ele_D)>>8)&0x00003FF;
					
					value32=(ele_D<<22)|((ele_C&0x3F)<<16) |ele_A;
					PHY_SetBBReg(dev, rOFDM0_XBTxIQImbalance, bMaskDWord, value32);

					value32 = (ele_C&0x000003C0)>>6;
					PHY_SetBBReg(dev, rOFDM0_XDTxAFE, bMaskH4Bits, value32);	
					
					value32 = ((X * ele_D)>>7)&0x01;
					PHY_SetBBReg(dev, rOFDM0_ECCAThreshold, BIT27, value32);

					value32 = ((Y * ele_D)>>7)&0x01;
					PHY_SetBBReg(dev, rOFDM0_ECCAThreshold, BIT25, value32);


				}
				else{
					PHY_SetBBReg(dev, rOFDM0_XBTxIQImbalance, bMaskDWord, OFDMSwingTable[OFDM_index[1]]);										
					PHY_SetBBReg(dev, rOFDM0_XDTxAFE, bMaskH4Bits, 0x00);	
					PHY_SetBBReg(dev, rOFDM0_ECCAThreshold, BIT27|BIT25, 0x00);				
				}

				RTPRINT(FINIT, INIT_IQK, ("TxPwrTracking path B: X = 0x%lx, Y = 0x%lx ele_A = 0x%lx ele_C = 0x%lx ele_D = 0x%lx\n", X, Y, ele_A, ele_C, ele_D));			
			}

			RTPRINT(FINIT, INIT_IQK, ("TxPwrTracking 0xc80 = 0x%x, 0xc94 = 0x%x RF 0x24 = 0x%x\n", PHY_QueryBBReg(dev, 0xc80, bMaskDWord), PHY_QueryBBReg(dev, 0xc94, bMaskDWord), PHY_QueryRFReg(dev, RF90_PATH_A, 0x24, bMaskDWord)));
		}
		
		if(delta_IQK > 3)
		{
			priv->ThermalValue_IQK = ThermalValue;
			PHY_IQCalibrate(dev, false);
		}

		if(delta_DPK != 0)
		{
			delta_DPK = ThermalValue - priv->EEPROMThermalMeter;

			if(priv->bDPPathAOK || priv->bDPPathBOK)
				RTPRINT(FINIT, INIT_IQK, ("TxPwrTracking delata_DPK = %d\n", delta_DPK));			
			
			if(priv->bDPPathAOK)
				PHY_SetBBReg(dev, 0xb68, 0x7c00, DPK_delta_mapping[0][((delta_DPK+13)/2)]);					
			if(priv->bDPPathBOK)
				PHY_SetBBReg(dev, 0xb6c, 0x7c00, DPK_delta_mapping[1][((delta_DPK+13)/2)]);							
			priv->ThermalValue_DPK = ThermalValue;			
		}
		
		if(priv->TxPowerTrackControl)
			priv->ThermalValue = ThermalValue;
			
	}

	RT_TRACE(COMP_POWER_TRACKING, "<===dm_TXPowerTrackingCallback_ThermalMeter_92C\n");
	
#ifdef MERGE_TO_DO
	PlatformAtomicExchange(dev, &priv->IntrCCKRefCount, FALSE);		
#endif

	priv->txpower_count = 0;
	
#endif
}


static	void
dm_InitializeTXPowerTracking_ThermalMeter(struct net_device *dev)
{
	struct r8192_priv* priv = rtllib_priv(dev);
	
	priv->btxpower_tracking = true;
	priv->txpower_count       = 0;
	priv->btxpower_trackingInit = false;
	priv->TxPowerTrackControl = true;		

	RT_TRACE(COMP_POWER_TRACKING, "pMgntInfo->btxpower_tracking = %d\n", priv->btxpower_tracking);
}


void
DM_InitializeTXPowerTracking(struct net_device *dev)
{
	dm_InitializeTXPowerTracking_ThermalMeter(dev);
}	

void
DM_TXPowerTracking92CDirectCall(struct net_device *dev)
{	
	dm_TXPowerTrackingCallback_ThermalMeter_92C(dev);
}

void
dm_CheckTXPowerTracking_ThermalMeter(struct net_device *dev)
{
#if 1
	struct r8192_priv* priv = rtllib_priv(dev);
	static u8			TM_Trigger = 0;

	if(!priv->btxpower_tracking /*|| (!pHalData->TxPowerTrackControl && pHalData->bAPKdone)*/)
	{
		return;
	}

	if(!TM_Trigger)		
	{
		PHY_SetRFReg(dev, RF90_PATH_A, RF_T_METER, bRFRegOffsetMask, 0x60);
		RT_TRACE(COMP_POWER_TRACKING, "Trigger 92S Thermal Meter!!\n");

		TM_Trigger = 1;
		return;
	}
	else
	{
		RT_TRACE(COMP_POWER_TRACKING, "Schedule TxPowerTracking direct call!!\n");		
		DM_TXPowerTracking92CDirectCall(dev); 
		TM_Trigger = 0;
	}
#endif
}

void
dm_CheckTXPowerTracking(struct net_device *dev)
{
	dm_CheckTXPowerTracking_ThermalMeter(dev);
}

void
dm_InitRateAdaptiveMask(struct net_device *dev)
{
	struct r8192_priv* 			priv = rtllib_priv(dev);
	prate_adaptive			pRA = (prate_adaptive)&priv->rate_adaptive;

	pRA->ratr_state = DM_RATR_STA_INIT;
	pRA->PreRATRState = DM_RATR_STA_INIT;

	if (priv->DM_Type == DM_Type_ByDriver)
		priv->rtllib->bUseRAMask = true;
	else
		priv->rtllib->bUseRAMask = false;	
}

/*-----------------------------------------------------------------------------
 * Function:	dm_RefreshRateAdaptiveMask()
 *
 * Overview:	Update rate table mask according to rssi
 *
 * Input:		NONE
 *
 * Output:		NONE
 *
 * Return:		NONE
 *
 * Revised History:
 *	When		Who		Remark
 *	05/27/2009	hpfan	Create Version 0.  
 *
 *---------------------------------------------------------------------------*/
void
dm_RefreshRateAdaptiveMask(struct net_device *dev)
{
	struct r8192_priv* 		priv = rtllib_priv(dev);
	prate_adaptive		pRA = (prate_adaptive)&priv->rate_adaptive;
	u32					LowRSSIThreshForRA = 0, HighRSSIThreshForRA = 0;

	if(IS_NIC_DOWN(priv))
	{
		RT_TRACE(COMP_RATE, "<---- dm_RefreshRateAdaptiveMask(): driver is going to unload\n");
		return;
	}

	if(!priv->rtllib->bUseRAMask)
	{
		RT_TRACE(COMP_RATE, "<---- dm_RefreshRateAdaptiveMask(): driver does not control rate adaptive mask\n");
		return;
	}

#ifdef _RTL8192_EXT_PATCH_
	if((priv->rtllib->state == RTLLIB_LINKED) || ((priv->rtllib->state == RTLLIB_LINKED) 
		&& (priv->rtllib->iw_mode == IW_MODE_MESH) && (priv->rtllib->only_mesh == 0))) 
#else
	if(priv->rtllib->state == RTLLIB_LINKED)
#endif
	{
		
		switch (pRA->PreRATRState)
		{
			case DM_RATR_STA_HIGH:
				HighRSSIThreshForRA = 50;
				LowRSSIThreshForRA = 20;
				break;
			
			case DM_RATR_STA_MIDDLE:
				HighRSSIThreshForRA = 55;
				LowRSSIThreshForRA = 20;
				break;
			
			case DM_RATR_STA_LOW:
				HighRSSIThreshForRA = 50;
				LowRSSIThreshForRA = 25;
				break;

			default:
				HighRSSIThreshForRA = 50;
				LowRSSIThreshForRA = 20;
				break;
		}

		if(priv->undecorated_smoothed_pwdb > (long)HighRSSIThreshForRA)
			pRA->ratr_state = DM_RATR_STA_HIGH;
		else if(priv->undecorated_smoothed_pwdb > (long)LowRSSIThreshForRA)
			pRA->ratr_state = DM_RATR_STA_MIDDLE;
		else
			pRA->ratr_state = DM_RATR_STA_LOW;

		if(pRA->PreRATRState != pRA->ratr_state)
		{
			RT_TRACE(COMP_RATE,  "RSSI = %ld\n", priv->undecorated_smoothed_pwdb);
			RT_TRACE(COMP_RATE,  "RSSI_LEVEL = %d\n", pRA->ratr_state);
			RT_TRACE(COMP_RATE,  "PreState = %d, CurState = %d\n", pRA->PreRATRState, pRA->ratr_state);
			priv->rtllib->UpdateHalRAMaskHandler(
					dev,
					false,
					0,
					priv->rtllib->pHTInfo->PeerMimoPs,
					priv->rtllib->mode,
					priv->rtllib->pHTInfo->bCurTxBW40MHz,
					pRA->ratr_state,
					NULL,
					NULL,
					NULL,
					NULL,
					false);
			pRA->PreRATRState = pRA->ratr_state;
		}
	}

#ifdef MERGE_TO_DO
	if(priv->rtllib->iw_mode == IW_MODE_ADHOC)
	{
		pTargetAdapter = pAdapter;
	}
	else
	{
			pTargetAdapter = NULL;
	}

	if(pTargetAdapter != NULL)
		;
#endif

#ifdef _RTL8192_EXT_PATCH_                      
        if(priv->rtllib->iw_mode == IW_MODE_MESH)
        {
                if(priv->mshobj->ext_refresh_rate_adaptive_mask)
                        priv->mshobj->ext_refresh_rate_adaptive_mask(priv);
        }
#endif

}

void dm_InitDynamicBBPowerSaving(struct net_device *dev)
{
	DM_PSTable.PreCCAState = CCA_MAX;
	DM_PSTable.CurCCAState = CCA_MAX;
	DM_PSTable.PreRFState = RF_MAX;
	DM_PSTable.CurRFState = RF_MAX;
	DM_PSTable.Rssi_val_min = 0;
}

void dm_1R_CCA(struct net_device *dev)
{	
	struct r8192_priv* priv = rtllib_priv(dev);
	
	if(DM_PSTable.Rssi_val_min != 0)
	{
		 
		if(DM_PSTable.PreCCAState == CCA_2R)
		{
			if(DM_PSTable.Rssi_val_min >= 35)
				DM_PSTable.CurCCAState = CCA_1R;
			else
				DM_PSTable.CurCCAState = CCA_2R;
			
		}
		else{
			if(DM_PSTable.Rssi_val_min <= 30)
				DM_PSTable.CurCCAState = CCA_2R;
			else
				DM_PSTable.CurCCAState = CCA_1R;
		}
	}
	else
		DM_PSTable.CurCCAState=CCA_MAX;
	
	if(DM_PSTable.PreCCAState != DM_PSTable.CurCCAState)
	{
		if(DM_PSTable.CurCCAState == CCA_1R)
		{
			if(priv->rf_type==RF_2T2R)
			{
				PHY_SetBBReg(dev, rOFDM0_TRxPathEnable  , bMaskByte0, 0x13);
				PHY_SetBBReg(dev, 0xe70, bMaskByte3, 0x20);
			}
			else
			{
				PHY_SetBBReg(dev, rOFDM0_TRxPathEnable  , bMaskByte0, 0x23);
				PHY_SetBBReg(dev, 0xe70, 0x7fc00000, 0x10c); 
			}
		}
		else
		{
			PHY_SetBBReg(dev, rOFDM0_TRxPathEnable  , bMaskByte0, 0x33);
			PHY_SetBBReg(dev,0xe70, bMaskByte3, 0x63);
		}
		DM_PSTable.PreCCAState = DM_PSTable.CurCCAState;
	}
}

void
dm_RF_Saving(struct net_device *dev, u8 bForceInNormal )
{
	static u8	initialize = 0;
	static u32	Reg874,RegC70,Reg85C,RegA74;

	if(initialize == 0){
		Reg874 = (PHY_QueryBBReg(dev, rFPGA0_XCD_RFInterfaceSW, bMaskDWord)&0x1CC000)>>14;
		RegC70 = (PHY_QueryBBReg(dev, rOFDM0_AGCParameter1, bMaskDWord)&BIT3)>>3;
		Reg85C = (PHY_QueryBBReg(dev, rFPGA0_XCD_SwitchControl, bMaskDWord)&0xFF000000)>>24;
		RegA74 = (PHY_QueryBBReg(dev, 0xa74, bMaskDWord)&0xF000)>>12;
		initialize = 1;
	}

	if(!bForceInNormal)
	{
		if(DM_PSTable.Rssi_val_min != 0)
		{
			 
			if(DM_PSTable.PreRFState == RF_Normal)
			{
				if(DM_PSTable.Rssi_val_min >= 30)
					DM_PSTable.CurRFState = RF_Save;
				else
					DM_PSTable.CurRFState = RF_Normal;
			}
			else{
				if(DM_PSTable.Rssi_val_min <= 25)
					DM_PSTable.CurRFState = RF_Normal;
				else
					DM_PSTable.CurRFState = RF_Save;
			}
		}
		else
			DM_PSTable.CurRFState=RF_MAX;
	}
	else
	{
		DM_PSTable.CurRFState = RF_Normal;
	}
	
	if(DM_PSTable.PreRFState != DM_PSTable.CurRFState)
	{
		if(DM_PSTable.CurRFState == RF_Save)
		{
			PHY_SetBBReg(dev, rFPGA0_XCD_RFInterfaceSW  , 0x1C0000, 0x2); 
			PHY_SetBBReg(dev, rOFDM0_AGCParameter1, BIT3, 0); 
			PHY_SetBBReg(dev, rFPGA0_XCD_SwitchControl, 0xFF000000, 0x63); 
			PHY_SetBBReg(dev, rFPGA0_XCD_RFInterfaceSW, 0xC000, 0x2); 
			PHY_SetBBReg(dev, 0xa74, 0xF000, 0x3); 
			PHY_SetBBReg(dev, 0x818, BIT28, 0x0); 
			PHY_SetBBReg(dev, 0x818, BIT28, 0x1); 
		}
		else
		{
			PHY_SetBBReg(dev, rFPGA0_XCD_RFInterfaceSW  , 0x1CC000, Reg874); 
			PHY_SetBBReg(dev, rOFDM0_AGCParameter1, BIT3, RegC70); 
			PHY_SetBBReg(dev, rFPGA0_XCD_SwitchControl, 0xFF000000, Reg85C);
			PHY_SetBBReg(dev, 0xa74, 0xF000, RegA74); 
			PHY_SetBBReg(dev, 0x818, BIT28, 0x0);  
		}
		DM_PSTable.PreRFState = DM_PSTable.CurRFState;
	}
}

void
dm_DynamicBBPowerSaving(struct net_device *dev)
{	

	struct r8192_priv* priv = rtllib_priv(dev);

	if((!(priv->rtllib->state == RTLLIB_LINKED)) &&	
		(priv->EntryMinUndecoratedSmoothedPWDB == 0))
	{
		DM_PSTable.Rssi_val_min = 0;
	}
	if(priv->rtllib->state == RTLLIB_LINKED)	
	{
		if(priv->rtllib->iw_mode == IW_MODE_ADHOC)
		{
			DM_PSTable.Rssi_val_min = priv->EntryMinUndecoratedSmoothedPWDB;
		}
		else
		{
			DM_PSTable.Rssi_val_min = priv->undecorated_smoothed_pwdb;
		}
	}
	else 
	{	
		DM_PSTable.Rssi_val_min = priv->EntryMinUndecoratedSmoothedPWDB;
	}
	
	if(IS_92C_SERIAL(priv->card_8192_version))
	{
		dm_1R_CCA(dev);
	}

	else
	{
		dm_RF_Saving(dev, false);
	}
}

#ifdef CONFIG_SW_ANT_SWICH
void
ODM_SwAntDivResetBeforeLink(struct net_device *dev)
{
	DM_SWAT_Table.SWAS_NoLink_State = 0;
}


void
dm_SW_AntennaSwitchCallback(unsigned long data)
{
	struct net_device* dev = (struct net_device *)data;
	struct r8192_priv* priv = rtllib_priv(dev);
	long		curRSSI;
	u8		curAntenna;

	if(priv->RSSI_cnt == 0)
		curRSSI = 0;
	else
		curRSSI = priv->RSSI_sum /priv->RSSI_cnt;
	RT_TRACE(DBG_LOUD, "SWAS: preAntenna= %s, curAntenna= %s \n", 
		(DM_SWAT_Table.PreAntenna == Antenna_A?"A":"B"), (DM_SWAT_Table.CurAntenna == Antenna_A?"A":"B"));
	RT_TRACE(DBG_LOUD, "SWAS: PreRSSI= %d, curRSSI= %d, RSSI_cnt = %d\n",
		DM_SWAT_Table.PreRSSI, curRSSI, priv->RSSI_cnt);

	DM_SWAT_Table.stop_trying = 0;
	if(!(priv->rtllib->state == RTLLIB_LINKED) || priv->rtllib->eRFPowerState==eRfOff)
	{
		 curAntenna = DM_SWAT_Table.CurAntenna;
		 DM_SWAT_Table.try_flag = 0;
		 DM_SWAT_Table.failure_cnt = 0;
	}
	else
	{
		if(DM_SWAT_Table.try_flag == 1)
		{	
			if(curRSSI < DM_SWAT_Table.PreRSSI) 
			{
				RT_TRACE(DBG_LOUD, "SWAS: Switch back to another antenna");
				curAntenna = (DM_SWAT_Table.CurAntenna == Antenna_A)? Antenna_B : Antenna_A;
				DM_SWAT_Table.failure_cnt ++;
				RT_TRACE(DBG_LOUD, "SWAS: failure_cnt= %d\n ",DM_SWAT_Table.failure_cnt);
				if(DM_SWAT_Table.failure_cnt == 3)
				{
					RT_TRACE(DBG_LOUD, "SWAS: Stop Trying!\n ");
					DM_SWAT_Table.stop_trying = 1;
					DM_SWAT_Table.failure_cnt = 0;
				}
			}
			else 
			{
				curAntenna = DM_SWAT_Table.CurAntenna;
				RT_TRACE(DBG_LOUD, "SWAS: current anntena is good");
				DM_SWAT_Table.failure_cnt = 0;
			}
			DM_SWAT_Table.try_flag = 0;
		}

		else
		{
			if((curRSSI < DM_SWAT_Table.Trying_Threshold)||(curRSSI < (DM_SWAT_Table.PreRSSI -10)))
			{
				curAntenna = (DM_SWAT_Table.CurAntenna == Antenna_A)? Antenna_B : Antenna_A;
				DM_SWAT_Table.try_flag = 1;
				RT_TRACE(DBG_LOUD, "SWAS: Begin Trying!\n ");
			}
			else
				curAntenna = DM_SWAT_Table.CurAntenna;
		}
	}

	if(curAntenna != DM_SWAT_Table.CurAntenna)
	{
		RT_TRACE(DBG_LOUD, "SWAS: Change TX Antenna!\n ");
		PHY_SetBBReg(dev, rFPGA0_XA_RFInterfaceOE, 0x300, curAntenna);
	}

	DM_SWAT_Table.PreAntenna = DM_SWAT_Table.CurAntenna;
	DM_SWAT_Table.CurAntenna = curAntenna;
	DM_SWAT_Table.PreRSSI = curRSSI;
	priv->RSSI_cnt = 0;
	priv->RSSI_sum = 0;

	if(DM_SWAT_Table.stop_trying == 1) 
		mod_timer(&priv->SwAntennaSwitchTimer,  jiffies + MSECS(5000)); 
	else
		mod_timer(&priv->SwAntennaSwitchTimer,  jiffies + MSECS(500)); 

	RT_TRACE(DBG_LOUD, "SWAS: -----The End-----\n ");
}

void
dm_SW_AntennaSwitchInit(struct net_device *dev)
{
	struct r8192_priv* priv = rtllib_priv(dev);

	RT_TRACE(DBG_LOUD, "SWAS:Init SW Antenna Switch\n");
	priv->RSSI_sum = 0;
	priv->RSSI_cnt = 0;
	DM_SWAT_Table.CurAntenna = Antenna_A;
	DM_SWAT_Table.PreAntenna = Antenna_A;
	DM_SWAT_Table.try_flag = 0;
	DM_SWAT_Table.stop_trying = 0;
	DM_SWAT_Table.failure_cnt = 0;
	DM_SWAT_Table.PreRSSI = 0;
	DM_SWAT_Table.Trying_Threshold = 20;

}
#endif

void ODM_DMInit(struct net_device *dev)
{
	dm_DIGInit(dev);
	dm_InitDynamicTxPower(dev);
	DM_InitEdcaTurbo(dev);

	dm_InitRateAdaptiveMask(dev);
	DM_InitializeTXPowerTracking(dev);
	
	dm_InitDynamicBBPowerSaving(dev);
#ifdef CONFIG_SW_ANT_SWICH
	dm_SW_AntennaSwitchInit(dev);
#endif
}

void
ODM_DMWatchdog(struct net_device *dev)
{
#ifdef CONFIG_SW_ANT_SWICH
	static u8	bTriggerAntennaSwitch = 0;
#endif

	RTPRINT(FDM, DM_Monitor, ("HalDmWatchDog() ==>\n"));

	dm_DIG(dev);
	dm_FalseAlarmCounterStatistics(dev);


	dm_DynamicBBPowerSaving(dev);

	dm_DynamicTxPower(dev);

	dm_CheckTXPowerTracking(dev);

	dm_RefreshRateAdaptiveMask(dev);

	dm_BTCoexist(dev);

	dm_CheckEdcaTurbo(dev);

#ifdef CONFIG_SW_ANT_SWICH
	if((!IS_92C_SERIAL(priv->card_8192_version)) && (bTriggerAntennaSwitch == 0))
	{
		mod_timer(&priv->SwAntennaSwitchTimer,  jiffies + MSECS(1000)); 
		bTriggerAntennaSwitch = 1;
	}
#endif

	RTPRINT(FDM, DM_Monitor, ("HalDmWatchDog() <==\n"));
}
