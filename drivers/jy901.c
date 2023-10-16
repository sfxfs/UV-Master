//
// Created by fxf on 2023/7/27.
//

#include <string.h>

#include "jy901.h"

#define FuncW 0x06
#define FuncR 0x03

/*------------Reg define------------*/
#define SAVE 		       0x00
#define CALSW 		     0x01
#define RSW 		       0x02
#define RRATE		       0x03
#define BAUD 		       0x04
#define AXOFFSET	     0x05
#define AYOFFSET	     0x06
#define AZOFFSET	     0x07
#define GXOFFSET	     0x08
#define GYOFFSET	     0x09
#define GZOFFSET	     0x0a
#define HXOFFSET	     0x0b
#define HYOFFSET	     0x0c
#define HZOFFSET	     0x0d
#define D0MODE		     0x0e
#define D1MODE		     0x0f
#define D2MODE		     0x10
#define D3MODE		     0x11
#define D0PWMH		     0x12
#define D1PWMH		     0x13
#define D2PWMH		     0x14
#define D3PWMH		     0x15
#define D0PWMT		     0x16
#define D1PWMT		     0x17
#define D2PWMT		     0x18
#define D3PWMT		     0x19
#define IICADDR		     0x1a
#define LEDOFF 		     0x1b
#define MAGRANGX	     0x1c
#define MAGRANGY	     0x1d
#define MAGRANGZ	     0x1e
#define BANDWIDTH	     0x1f
#define GYRORANGE	     0x20
#define ACCRANGE	     0x21
#define SLEEP          0x22
#define ORIENT		     0x23
#define AXIS6          0x24
#define FILTK          0x25
#define GPSBAUD		     0x26
#define READADDR	     0x27
#define BWSCALE		     0x28
#define MOVETHR		     0x28
#define MOVESTA		     0x29
#define ACCFILT		     0x2A
#define GYROFILT	     0x2b
#define MAGFILT		     0x2c
#define POWONSEND	     0x2d
#define VERSION		     0x2e
#define CCBW	         0x2f
#define YYMM		       0x30
#define DDHH		       0x31
#define MMSS		       0x32
#define MS			       0x33
#define AX			       0x34
#define AY			       0x35
#define AZ			       0x36
#define GX			       0x37
#define GY			       0x38
#define GZ			       0x39
#define HX			       0x3a
#define HY			       0x3b
#define HZ			       0x3c
#define Roll		       0x3d
#define Pitch		       0x3e
#define Yaw			       0x3f
#define TEMP		       0x40

/* High precision */
#define LRoll          0x3d
#define HRoll          0x3e
#define LPitch         0x3f
#define HPitch         0x40
#define LYaw           0x41
#define HYaw           0x42
#define TEMP905x       0x43

#define D0Status	     0x41
#define D1Status	     0x42
#define D2Status	     0x43
#define D3Status	     0x44
#define PressureL	     0x45
#define PressureH	     0x46
#define HeightL		     0x47
#define HeightH		     0x48
#define LonL		       0x49
#define LonH		       0x4a
#define LatL		       0x4b
#define LatH		       0x4c
#define GPSHeight      0x4d
#define GPSYAW         0x4e
#define GPSVL		       0x4f
#define GPSVH		       0x50
#define q0			       0x51
#define q1			       0x52
#define q2			       0x53
#define q3			       0x54
#define SVNUM		       0x55
#define PDOP		       0x56
#define HDOP		       0x57
#define VDOP		       0x58
#define DELAYT		     0x59
#define XMIN           0x5a
#define XMAX           0x5b
#define BATVAL         0x5c
#define ALARMPIN       0x5d
#define YMIN           0x5e
#define YMAX           0x5f
#define GYROZSCALE		 0x60
#define GYROCALITHR    0x61
#define ALARMLEVEL     0x62
#define GYROCALTIME		 0x63
#define REFROLL			   0x64
#define REFPITCH		   0x65
#define REFYAW			   0x66
#define GPSTYPE        0x67
#define TRIGTIME       0x68
#define KEY            0x69
#define WERROR         0x6a
#define TIMEZONE       0x6b
#define CALICNT        0x6c
#define WZCNT          0x6d
#define WZTIME         0x6e
#define WZSTATIC       0x6f
#define ACCSENSOR 	   0x70
#define GYROSENSOR 	   0x71
#define MAGSENSOR 	   0x72
#define PRESSENSOR 	   0x73
#define MODDELAY       0x74

#define ANGLEAXIS      0x75
#define XRSCALE			   0x76
#define YRSCALE			   0x77
#define ZRSCALE			   0x78

#define XREFROLL		   0x79
#define YREFPITCH		   0x7a
#define ZREFYAW			   0x7b

#define ANGXOFFSET		 0x7c
#define ANGYOFFSET		 0x7d
#define ANGZOFFSET		 0x7e

#define NUMBERID1      0x7f
#define NUMBERID2      0x80
#define NUMBERID3      0x81
#define NUMBERID4      0x82
#define NUMBERID5      0x83
#define NUMBERID6      0x84

#define XA85PSCALE     0x85
#define XA85NSCALE     0x86
#define YA85PSCALE     0x87
#define YA85NSCALE     0x88
#define XA30PSCALE     0x89
#define XA30NSCALE     0x8a
#define YA30PSCALE     0x8b
#define YA30NSCALE     0x8c

#define CHIPIDL        0x8D
#define CHIPIDH        0x8E
#define REGINITFLAG    REGSIZE-1


/* AXIS6 */
#define ALGRITHM9   0
#define ALGRITHM6   1

/************CALSW**************/
#define NORMAL            0x00
#define CALGYROACC        0x01
#define CALMAG            0x02
#define CALALTITUDE       0x03
#define CALANGLEZ         0x04
#define CALACCL           0x05
#define CALACCR           0x06
#define CALMAGMM          0x07
#define CALREFANGLE	   	  0x08
#define CALMAG2STEP		    0x09
//#define CALACCX         0x09
//#define ACC45PRX        0x0A
//#define ACC45NRX        0x0B
//#define CALACCY         0x0C
//#define ACC45PRY        0x0D
//#define ACC45NRY     	  0x0E
//#define CALREFANGLER    0x0F
//#define CALACCINIT      0x10
//#define CALREFANGLEINIT 0x11
#define CALHEXAHEDRON		  0x12

/************OUTPUTHEAD**************/
#define WIT_TIME          0x50
#define WIT_ACC           0x51
#define WIT_GYRO          0x52
#define WIT_ANGLE         0x53
#define WIT_MAGNETIC      0x54
#define WIT_DPORT         0x55
#define WIT_PRESS         0x56
#define WIT_GPS           0x57
#define WIT_VELOCITY      0x58
#define WIT_QUATER        0x59
#define WIT_GSA           0x5A
#define WIT_REGVALUE      0x5F
/*----------Reg define end----------*/

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

/**
 * @brief 初始化函数执行
 * @param handle jy901_handle_t结构体参数
 * @return WIT_HAL_OK：成功（0）    WIT_HAL_ERROR：失败（-3）
 */
int32_t WitInit(jy901_handle_t *handle)
{
    if (handle->SerialInit() != 0)
        return WIT_HAL_ERROR;
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
