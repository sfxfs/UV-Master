//
// Created by fxf on 2023/7/27.
//

#include <string.h>

#include "jy901.h"
#include "jy901_reg.h"

static uint8_t __CaliSum(uint8_t *data, uint32_t len)
{
    uint32_t i;
    uint8_t ucCheck = 0;
    for(i=0; i<len; i++) ucCheck += *(data + i);
    return ucCheck;
}

static void SensorDataUpdata(jy901_handle_t *handle, uint32_t uiReg, uint32_t uiRegNum)
{
    int i;
    for (i = 0; i < uiRegNum; i++)
    {
        switch (uiReg)
        {
        case AZ:
            for (i = 0; i < 3; i++)
                handle->fAcc[i] = handle->sReg[AX + i] / 32768.0f * 16.0f;
            break;
        case GZ:
            for (i = 0; i < 3; i++)
                handle->fGyro[i] = handle->sReg[GX + i] / 32768.0f * 2000.0f;
            break;
        case HZ:
            for (i = 0; i < 3; i++)
                handle->fMag[i] = handle->sReg[HX + i];
            break;
        case Yaw:
            for (i = 0; i < 3; i++)
                handle->fAngle[i] = handle->sReg[Roll + i] / 32768.0f * 180.0f;
            break;
        default:
            for (i = 0; i < 3; i++)
            {
                handle->fAcc[i] = handle->sReg[AX + i] / 32768.0f * 16.0f;
                handle->fGyro[i] = handle->sReg[GX + i] / 32768.0f * 2000.0f;
                handle->fAngle[i] = handle->sReg[Roll + i] / 32768.0f * 180.0f;
                handle->fMag[i] = handle->sReg[HX + i];
            }
            break;
        }
        uiReg++;
    }
}

static void CopeWitData(jy901_handle_t *handle, uint8_t ucIndex, uint16_t *p_data, uint32_t uiLen)
{
    uint32_t uiReg1 = 0, uiReg2 = 0, uiReg1Len = 0, uiReg2Len = 0;
    uint16_t *p_usReg1Val = p_data;
    uint16_t *p_usReg2Val = p_data+3;

    uiReg1Len = 4;
    switch(ucIndex)
    {
        case WIT_ACC:   uiReg1 = AX;    uiReg1Len = 3;  uiReg2 = TEMP;  uiReg2Len = 1;  break;
        case WIT_ANGLE: uiReg1 = Roll;  uiReg1Len = 3;  uiReg2 = VERSION;  uiReg2Len = 1;  break;
        case WIT_TIME:  uiReg1 = YYMM;	break;
        case WIT_GYRO:  uiReg1 = GX;  uiLen = 3;break;
        case WIT_MAGNETIC: uiReg1 = HX;  uiLen = 3;break;
        case WIT_DPORT: uiReg1 = D0Status;  break;
        case WIT_PRESS: uiReg1 = PressureL;  break;
        case WIT_GPS:   uiReg1 = LonL;  break;
        case WIT_VELOCITY: uiReg1 = GPSHeight;  break;
        case WIT_QUATER:    uiReg1 = q0;  break;
        case WIT_GSA:   uiReg1 = SVNUM;  break;
        case WIT_REGVALUE:  uiReg1 = handle->s_uiReadRegIndex;  break;
        default:
            return ;
    }
    if(uiLen == 3)
    {
        uiReg1Len = 3;
        uiReg2Len = 0;
    }
    if(uiReg1Len)
    {
        memcpy(&handle->sReg[uiReg1], p_usReg1Val, uiReg1Len<<1);
        SensorDataUpdata(handle, uiReg1, uiReg1Len);
    }
    if(uiReg2Len)
    {
        memcpy(&handle->sReg[uiReg2], p_usReg2Val, uiReg2Len<<1);
        SensorDataUpdata(handle, uiReg2, uiReg2Len);
    }
}

void WitSerialDataIn(jy901_handle_t *handle, uint8_t ucData)
{
    uint16_t usData[4];
    uint8_t ucSum;

    handle->s_ucWitDataBuff[handle->s_uiWitDataCnt++] = ucData;

    if (handle->s_ucWitDataBuff[0] != 0x55)
    {
        handle->s_uiWitDataCnt--;
        memcpy(handle->s_ucWitDataBuff, &handle->s_ucWitDataBuff[1], handle->s_uiWitDataCnt);
        return;
    }
    if (handle->s_uiWitDataCnt >= 11)
    {
        ucSum = __CaliSum(handle->s_ucWitDataBuff, 10);
        if (ucSum != handle->s_ucWitDataBuff[10])
        {
            handle->s_uiWitDataCnt--;
            memcpy(handle->s_ucWitDataBuff, &handle->s_ucWitDataBuff[1], handle->s_uiWitDataCnt);
            return;
        }
        usData[0] = ((uint16_t)handle->s_ucWitDataBuff[3] << 8) | (uint16_t)handle->s_ucWitDataBuff[2];
        usData[1] = ((uint16_t)handle->s_ucWitDataBuff[5] << 8) | (uint16_t)handle->s_ucWitDataBuff[4];
        usData[2] = ((uint16_t)handle->s_ucWitDataBuff[7] << 8) | (uint16_t)handle->s_ucWitDataBuff[6];
        usData[3] = ((uint16_t)handle->s_ucWitDataBuff[9] << 8) | (uint16_t)handle->s_ucWitDataBuff[8];
        CopeWitData(handle, handle->s_ucWitDataBuff[1], usData, 4);
        handle->s_uiWitDataCnt = 0;
    }

    if (handle->s_uiWitDataCnt == WIT_DATA_BUFF_SIZE)
        handle->s_uiWitDataCnt = 0;
}

int32_t WitWriteReg(jy901_handle_t *handle, uint32_t uiReg, uint16_t usData)
{
    uint8_t ucBuff[8];
    if (uiReg >= REGSIZE)
        return WIT_HAL_INVAL;

    if (handle->SerialWrite == NULL)
        return WIT_HAL_EMPTY;
    ucBuff[0] = 0xFF;
    ucBuff[1] = 0xAA;
    ucBuff[2] = uiReg & 0xFF;
    ucBuff[3] = usData & 0xff;
    ucBuff[4] = usData >> 8;
    handle->SerialWrite(ucBuff, 5);

    return WIT_HAL_OK;
}

int32_t WitReadReg(jy901_handle_t *handle, uint32_t uiReg, uint32_t uiReadNum)
{
    uint8_t ucBuff[8];
    if ((uiReg + uiReadNum) >= REGSIZE)
        return WIT_HAL_INVAL;

    if (uiReadNum > 4)
        return WIT_HAL_INVAL;
    if (handle->SerialWrite == NULL)
        return WIT_HAL_EMPTY;
    ucBuff[0] = 0xFF;
    ucBuff[1] = 0xAA;
    ucBuff[2] = 0x27;
    ucBuff[3] = uiReg & 0xff;
    ucBuff[4] = uiReg >> 8;
    handle->SerialWrite(ucBuff, 5);

    handle->s_uiReadRegIndex = uiReg;

    return WIT_HAL_OK;
}

void WitDeInit(jy901_handle_t *handle)
{
    memset(handle, 0, sizeof(jy901_handle_t));
}


char CheckRange(short sTemp,short sMin,short sMax)
{
    if ((sTemp>=sMin)&&(sTemp<=sMax)) return 1;
    else return 0;
}


/*Acceleration calibration demo*/
int32_t WitStartAccCali(jy901_handle_t *handle)
{
/*
	First place the equipment horizontally, and then perform the following operations
*/
    if(WitWriteReg(handle, KEY, KEY_UNLOCK) != WIT_HAL_OK) return  WIT_HAL_ERROR;
    if(handle->DelaymsCb != NULL)
    {
        handle->DelaymsCb(20);
    }
    else return WIT_HAL_EMPTY;
    if(WitWriteReg(handle, CALSW, CALGYROACC) != WIT_HAL_OK) return  WIT_HAL_ERROR;
    return WIT_HAL_OK;
}


int32_t WitStopAccCali(jy901_handle_t *handle)
{
    if(WitWriteReg(handle, KEY, KEY_UNLOCK) != WIT_HAL_OK)	return  WIT_HAL_ERROR;
    if(handle->DelaymsCb != NULL)
    {
        handle->DelaymsCb(20);
    }
    else return WIT_HAL_EMPTY;
    if(WitWriteReg(handle, CALSW, NORMAL) != WIT_HAL_OK)	return  WIT_HAL_ERROR;
    return WIT_HAL_OK;
}


/*Magnetic field calibration*/
int32_t WitStartMagCali(jy901_handle_t *handle)
{
    if(WitWriteReg(handle, KEY, KEY_UNLOCK) != WIT_HAL_OK)	return  WIT_HAL_ERROR;
    if(handle->DelaymsCb != NULL)
    {
        handle->DelaymsCb(20);
    }
    else return WIT_HAL_EMPTY;
    if(WitWriteReg(handle, CALSW, CALMAGMM) != WIT_HAL_OK)	return  WIT_HAL_ERROR;
    return WIT_HAL_OK;
}


int32_t WitStopMagCali(jy901_handle_t *handle)
{
    if(WitWriteReg(handle, KEY, KEY_UNLOCK) != WIT_HAL_OK)	return  WIT_HAL_ERROR;
    if(handle->DelaymsCb != NULL)
    {
        handle->DelaymsCb(20);
    }
    else return WIT_HAL_EMPTY;
    if(WitWriteReg(handle, CALSW, NORMAL) != WIT_HAL_OK)	return  WIT_HAL_ERROR;
    return WIT_HAL_OK;
}


/*change Band*/
int32_t WitSetUartBaud(jy901_handle_t *handle, wit_baud_t uiBaudIndex)
{
    if(!CheckRange(uiBaudIndex,WIT_BAUD_4800,WIT_BAUD_230400))
    {
        return WIT_HAL_INVAL;
    }
    if(WitWriteReg(handle, KEY, KEY_UNLOCK) != WIT_HAL_OK)	return  WIT_HAL_ERROR;
    if(handle->DelaymsCb != NULL)
    {
        handle->DelaymsCb(20);
    }
    else return WIT_HAL_EMPTY;
    if(WitWriteReg(handle, BAUD, uiBaudIndex) != WIT_HAL_OK)	return  WIT_HAL_ERROR;
    return WIT_HAL_OK;
}


/*change Bandwidth*/
int32_t WitSetBandwidth(jy901_handle_t *handle, wit_bandwidth_t uiBaudWidth)
{
    if(!CheckRange(uiBaudWidth,BANDWIDTH_256HZ,BANDWIDTH_5HZ))
    {
        return WIT_HAL_INVAL;
    }
    if(handle->DelaymsCb != NULL)
    {
        handle->DelaymsCb(20);
    }
    else return WIT_HAL_EMPTY;
    if(WitWriteReg(handle, BANDWIDTH, uiBaudWidth) != WIT_HAL_OK)	return  WIT_HAL_ERROR;
    return WIT_HAL_OK;
}


/*change output rate */
int32_t WitSetOutputRate(jy901_handle_t *handle, wit_rrate_t uiRate)
{
    if(!CheckRange(uiRate,RRATE_02HZ,RRATE_NONE))
    {
        return WIT_HAL_INVAL;
    }
    if(WitWriteReg(handle, KEY, KEY_UNLOCK) != WIT_HAL_OK)	return  WIT_HAL_ERROR;
    if(handle->DelaymsCb != NULL)
    {
        handle->DelaymsCb(20);
    }
    else return WIT_HAL_EMPTY;
    if(WitWriteReg(handle, RRATE, uiRate) != WIT_HAL_OK)	return  WIT_HAL_ERROR;
    return WIT_HAL_OK;
}


/*change WitSetContent */
int32_t WitSetContent(jy901_handle_t *handle, wit_rsw_t uiRsw)
{
    if(!CheckRange(uiRsw,RSW_TIME,RSW_MASK))
    {
        return WIT_HAL_INVAL;
    }
    if(WitWriteReg(handle, KEY, KEY_UNLOCK) != WIT_HAL_OK)	return  WIT_HAL_ERROR;
    if(handle->DelaymsCb != NULL)
    {
        handle->DelaymsCb(20);
    }
    else return WIT_HAL_EMPTY;
    if(WitWriteReg(handle, RSW, uiRsw) != WIT_HAL_OK)	return  WIT_HAL_ERROR;
    return WIT_HAL_OK;
}

/* save parameters */
int32_t WitSaveParameter(jy901_handle_t *handle)
{
    if(WitWriteReg(handle, KEY, KEY_UNLOCK) != WIT_HAL_OK)	return  WIT_HAL_ERROR;
    if(handle->DelaymsCb != NULL)
    {
        handle->DelaymsCb(20);
    }
    else return WIT_HAL_EMPTY;
    if(WitWriteReg(handle, SAVE, SAVE_PARAM) != WIT_HAL_OK)	return  WIT_HAL_ERROR;
    return WIT_HAL_OK;
}

/* set software reset */
int32_t WitSetForReset(jy901_handle_t *handle)
{
    if(WitWriteReg(handle, KEY, KEY_UNLOCK) != WIT_HAL_OK)	return  WIT_HAL_ERROR;
    if(handle->DelaymsCb != NULL)
    {
        handle->DelaymsCb(20);
    }
    else return WIT_HAL_EMPTY;
    if(WitWriteReg(handle, SAVE, SAVE_SWRST) != WIT_HAL_OK)	return  WIT_HAL_ERROR;
    return WIT_HAL_OK;
}

/* set Angle reference */
int32_t WitCaliRefAngle(jy901_handle_t *handle)
{
    if(WitWriteReg(handle, KEY, KEY_UNLOCK) != WIT_HAL_OK)	    return  WIT_HAL_ERROR;
    if(handle->DelaymsCb != NULL)
    {
        handle->DelaymsCb(20);
    }
    else return WIT_HAL_EMPTY;
    if(WitWriteReg(handle, CALSW, CALREFANGLE) != WIT_HAL_OK)	return  WIT_HAL_ERROR;
    return WIT_HAL_OK;
}
