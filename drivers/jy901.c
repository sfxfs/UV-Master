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

static const uint8_t __auchCRCHi[256] = {
        0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81,
        0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
        0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01,
        0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
        0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81,
        0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
        0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01,
        0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
        0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81,
        0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
        0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01,
        0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
        0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81,
        0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
        0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01,
        0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
        0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81,
        0x40
};
static const uint8_t __auchCRCLo[256] = {
        0x00, 0xC0, 0xC1, 0x01, 0xC3, 0x03, 0x02, 0xC2, 0xC6, 0x06, 0x07, 0xC7, 0x05, 0xC5, 0xC4,
        0x04, 0xCC, 0x0C, 0x0D, 0xCD, 0x0F, 0xCF, 0xCE, 0x0E, 0x0A, 0xCA, 0xCB, 0x0B, 0xC9, 0x09,
        0x08, 0xC8, 0xD8, 0x18, 0x19, 0xD9, 0x1B, 0xDB, 0xDA, 0x1A, 0x1E, 0xDE, 0xDF, 0x1F, 0xDD,
        0x1D, 0x1C, 0xDC, 0x14, 0xD4, 0xD5, 0x15, 0xD7, 0x17, 0x16, 0xD6, 0xD2, 0x12, 0x13, 0xD3,
        0x11, 0xD1, 0xD0, 0x10, 0xF0, 0x30, 0x31, 0xF1, 0x33, 0xF3, 0xF2, 0x32, 0x36, 0xF6, 0xF7,
        0x37, 0xF5, 0x35, 0x34, 0xF4, 0x3C, 0xFC, 0xFD, 0x3D, 0xFF, 0x3F, 0x3E, 0xFE, 0xFA, 0x3A,
        0x3B, 0xFB, 0x39, 0xF9, 0xF8, 0x38, 0x28, 0xE8, 0xE9, 0x29, 0xEB, 0x2B, 0x2A, 0xEA, 0xEE,
        0x2E, 0x2F, 0xEF, 0x2D, 0xED, 0xEC, 0x2C, 0xE4, 0x24, 0x25, 0xE5, 0x27, 0xE7, 0xE6, 0x26,
        0x22, 0xE2, 0xE3, 0x23, 0xE1, 0x21, 0x20, 0xE0, 0xA0, 0x60, 0x61, 0xA1, 0x63, 0xA3, 0xA2,
        0x62, 0x66, 0xA6, 0xA7, 0x67, 0xA5, 0x65, 0x64, 0xA4, 0x6C, 0xAC, 0xAD, 0x6D, 0xAF, 0x6F,
        0x6E, 0xAE, 0xAA, 0x6A, 0x6B, 0xAB, 0x69, 0xA9, 0xA8, 0x68, 0x78, 0xB8, 0xB9, 0x79, 0xBB,
        0x7B, 0x7A, 0xBA, 0xBE, 0x7E, 0x7F, 0xBF, 0x7D, 0xBD, 0xBC, 0x7C, 0xB4, 0x74, 0x75, 0xB5,
        0x77, 0xB7, 0xB6, 0x76, 0x72, 0xB2, 0xB3, 0x73, 0xB1, 0x71, 0x70, 0xB0, 0x50, 0x90, 0x91,
        0x51, 0x93, 0x53, 0x52, 0x92, 0x96, 0x56, 0x57, 0x97, 0x55, 0x95, 0x94, 0x54, 0x9C, 0x5C,
        0x5D, 0x9D, 0x5F, 0x9F, 0x9E, 0x5E, 0x5A, 0x9A, 0x9B, 0x5B, 0x99, 0x59, 0x58, 0x98, 0x88,
        0x48, 0x49, 0x89, 0x4B, 0x8B, 0x8A, 0x4A, 0x4E, 0x8E, 0x8F, 0x4F, 0x8D, 0x4D, 0x4C, 0x8C,
        0x44, 0x84, 0x85, 0x45, 0x87, 0x47, 0x46, 0x86, 0x82, 0x42, 0x43, 0x83, 0x41, 0x81, 0x80,
        0x40
};

static uint16_t __CRC16(uint8_t *puchMsg, uint16_t usDataLen)
{
    uint8_t uchCRCHi = 0xFF;
    uint8_t uchCRCLo = 0xFF;
    uint8_t uIndex;
    int i = 0;
    uchCRCHi = 0xFF;
    uchCRCLo = 0xFF;
    for (; i<usDataLen; i++)
    {
        uIndex = uchCRCHi ^ puchMsg[i];
        uchCRCHi = uchCRCLo ^ __auchCRCHi[uIndex];
        uchCRCLo = __auchCRCLo[uIndex];
    }
    return (uint16_t)(((uint16_t)uchCRCHi << 8) | (uint16_t)uchCRCLo) ;
}


static uint8_t __CaliSum(uint8_t *data, uint32_t len)
{
    uint32_t i;
    uint8_t ucCheck = 0;
    for(i=0; i<len; i++) ucCheck += *(data + i);
    return ucCheck;
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
        handle->RegUpdateCb(uiReg1, uiReg1Len);
    }
    if(uiReg2Len)
    {
        memcpy(&handle->sReg[uiReg2], p_usReg2Val, uiReg2Len<<1);
        handle->RegUpdateCb(uiReg2, uiReg2Len);
    }
}


void WitSerialDataIn(jy901_handle_t *handle, uint8_t ucData)
{
    uint16_t usCRC16, usTemp, i, usData[4];
    uint8_t ucSum;

    if(handle->RegUpdateCb == NULL)return ;
    handle->s_ucWitDataBuff[handle->s_uiWitDataCnt++] = ucData;
    switch(handle->s_uiProtoclo)
    {
        case WIT_PROTOCOL_JY61:
        case WIT_PROTOCOL_NORMAL:
            if(handle->s_ucWitDataBuff[0] != 0x55)
            {
                handle->s_uiWitDataCnt--;
                memcpy(handle->s_ucWitDataBuff, &handle->s_ucWitDataBuff[1], handle->s_uiWitDataCnt);
                return ;
            }
            if(handle->s_uiWitDataCnt >= 11)
            {
                ucSum = __CaliSum(handle->s_ucWitDataBuff, 10);
                if(ucSum != handle->s_ucWitDataBuff[10])
                {
                    handle->s_uiWitDataCnt--;
                    memcpy(handle->s_ucWitDataBuff, &handle->s_ucWitDataBuff[1], handle->s_uiWitDataCnt);
                    return ;
                }
                usData[0] = ((uint16_t)handle->s_ucWitDataBuff[3] << 8) | (uint16_t)handle->s_ucWitDataBuff[2];
                usData[1] = ((uint16_t)handle->s_ucWitDataBuff[5] << 8) | (uint16_t)handle->s_ucWitDataBuff[4];
                usData[2] = ((uint16_t)handle->s_ucWitDataBuff[7] << 8) | (uint16_t)handle->s_ucWitDataBuff[6];
                usData[3] = ((uint16_t)handle->s_ucWitDataBuff[9] << 8) | (uint16_t)handle->s_ucWitDataBuff[8];
                CopeWitData(handle, handle->s_ucWitDataBuff[1], usData, 4);
                handle->s_uiWitDataCnt = 0;
            }
            break;
        case WIT_PROTOCOL_905x_MODBUS:
        case WIT_PROTOCOL_MODBUS:
            if(handle->s_uiWitDataCnt > 2)
            {
                if(handle->s_ucWitDataBuff[1] != FuncR)
                {
                    handle->s_uiWitDataCnt--;
                    memcpy(handle->s_ucWitDataBuff, &handle->s_ucWitDataBuff[1], handle->s_uiWitDataCnt);
                    return ;
                }
                if(handle->s_uiWitDataCnt < (handle->s_ucWitDataBuff[2] + 5))return ;
                usTemp = ((uint16_t)handle->s_ucWitDataBuff[handle->s_uiWitDataCnt-2] << 8) | handle->s_ucWitDataBuff[handle->s_uiWitDataCnt-1];
                usCRC16 = __CRC16(handle->s_ucWitDataBuff, handle->s_uiWitDataCnt-2);
                if(usTemp != usCRC16)
                {
                    handle->s_uiWitDataCnt--;
                    memcpy(handle->s_ucWitDataBuff, &handle->s_ucWitDataBuff[1], handle->s_uiWitDataCnt);
                    return ;
                }
                usTemp = handle->s_ucWitDataBuff[2] >> 1;
                for(i = 0; i < usTemp; i++)
                {
                    handle->sReg[i+handle->s_uiReadRegIndex] = ((uint16_t)handle->s_ucWitDataBuff[(i<<1)+3] << 8) | handle->s_ucWitDataBuff[(i<<1)+4];
                }
                handle->RegUpdateCb(handle->s_uiReadRegIndex, usTemp);
                handle->s_uiWitDataCnt = 0;
            }
            break;
        case WIT_PROTOCOL_905x_CAN:
        case WIT_PROTOCOL_CAN:
        case WIT_PROTOCOL_I2C:
            handle->s_uiWitDataCnt = 0;
            break;
    }
    if(handle->s_uiWitDataCnt == WIT_DATA_BUFF_SIZE)handle->s_uiWitDataCnt = 0;
}


int32_t WitWriteReg(jy901_handle_t *handle, uint32_t uiReg, uint16_t usData)
{
    uint16_t usCRC;
    uint8_t ucBuff[8];
    if(uiReg >= REGSIZE)return WIT_HAL_INVAL;
    switch(handle->s_uiProtoclo)
    {
        case WIT_PROTOCOL_JY61:
            return WIT_HAL_INVAL;
        case WIT_PROTOCOL_NORMAL:
            if(handle->SerialWrite == NULL)return WIT_HAL_EMPTY;
            ucBuff[0] = 0xFF;
            ucBuff[1] = 0xAA;
            ucBuff[2] = uiReg & 0xFF;
            ucBuff[3] = usData & 0xff;
            ucBuff[4] = usData >> 8;
            handle->SerialWrite(ucBuff, 5);
            break;
        case WIT_PROTOCOL_905x_MODBUS:
        case WIT_PROTOCOL_MODBUS:
            if(handle->SerialWrite == NULL)return WIT_HAL_EMPTY;
            ucBuff[0] = handle->s_ucAddr;
            ucBuff[1] = FuncW;
            ucBuff[2] = uiReg >> 8;
            ucBuff[3] = uiReg & 0xFF;
            ucBuff[4] = usData >> 8;
            ucBuff[5] = usData & 0xff;
            usCRC = __CRC16(ucBuff, 6);
            ucBuff[6] = usCRC >> 8;
            ucBuff[7] = usCRC & 0xff;
            handle->SerialWrite(ucBuff, 8);
            break;
        case WIT_PROTOCOL_I2C:
            if(handle->WitI2cWrite == NULL)return WIT_HAL_EMPTY;
            ucBuff[0] = usData & 0xff;
            ucBuff[1] = usData >> 8;
            if(handle->WitI2cWrite(handle->s_ucAddr << 1, uiReg, ucBuff, 2) != 1)
            {
                return  WIT_HAL_ERROR;
            }
            break;
        default:
            return WIT_HAL_INVAL;
    }
    return WIT_HAL_OK;
}
int32_t WitReadReg(jy901_handle_t *handle, uint32_t uiReg, uint32_t uiReadNum)
{
    uint16_t usTemp, i;
    uint8_t ucBuff[8];
    if((uiReg + uiReadNum) >= REGSIZE)return WIT_HAL_INVAL;
    switch(handle->s_uiProtoclo)
    {
        case WIT_PROTOCOL_JY61:
            return WIT_HAL_INVAL;
        case WIT_PROTOCOL_NORMAL:
            if(uiReadNum > 4)return WIT_HAL_INVAL;
            if(handle->SerialWrite == NULL)return WIT_HAL_EMPTY;
            ucBuff[0] = 0xFF;
            ucBuff[1] = 0xAA;
            ucBuff[2] = 0x27;
            ucBuff[3] = uiReg & 0xff;
            ucBuff[4] = uiReg >> 8;
            handle->SerialWrite(ucBuff, 5);
            break;
        case WIT_PROTOCOL_905x_MODBUS:
        case WIT_PROTOCOL_MODBUS:
            if(handle->SerialWrite == NULL)return WIT_HAL_EMPTY;
            usTemp = uiReadNum << 1;
            if((usTemp + 5) > WIT_DATA_BUFF_SIZE)return WIT_HAL_NOMEM;
            ucBuff[0] = handle->s_ucAddr;
            ucBuff[1] = FuncR;
            ucBuff[2] = uiReg >> 8;
            ucBuff[3] = uiReg & 0xFF;
            ucBuff[4] = uiReadNum >> 8;
            ucBuff[5] = uiReadNum & 0xff;
            usTemp = __CRC16(ucBuff, 6);
            ucBuff[6] = usTemp >> 8;
            ucBuff[7] = usTemp & 0xff;
            handle->SerialWrite(ucBuff, 8);
            break;
        case WIT_PROTOCOL_I2C:
            if(handle->WitI2cRead == NULL)return WIT_HAL_EMPTY;
            usTemp = uiReadNum << 1;
            if(WIT_DATA_BUFF_SIZE < usTemp)return WIT_HAL_NOMEM;
            if(handle->WitI2cRead(handle->s_ucAddr << 1, uiReg, handle->s_ucWitDataBuff, usTemp) == 1)
            {
                if(handle->RegUpdateCb == NULL)return WIT_HAL_EMPTY;
                for(i = 0; i < uiReadNum; i++)
                {
                    handle->sReg[i+uiReg] = ((uint16_t)handle->s_ucWitDataBuff[(i<<1)+1] << 8) | handle->s_ucWitDataBuff[i<<1];
                }
                handle->RegUpdateCb(uiReg, uiReadNum);
            }
            break;
        default:
            return WIT_HAL_INVAL;
    }
    handle->s_uiReadRegIndex = uiReg;

    return WIT_HAL_OK;
}


int32_t WitInit(jy901_handle_t *handle, uint32_t uiProtocol, uint8_t ucAddr)
{
    memset(handle, 0, sizeof(jy901_handle_t));
    if(uiProtocol > WIT_PROTOCOL_905x_CAN)return WIT_HAL_INVAL;
    handle->s_uiProtoclo = uiProtocol;
    handle->s_ucAddr = ucAddr;
    handle->s_uiWitDataCnt = 0;
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
    uint8_t ucBuff[3];
    if(handle->s_uiProtoclo == WIT_PROTOCOL_JY61)
    {
        if(handle->SerialWrite == NULL)return WIT_HAL_EMPTY;
        ucBuff[0] = 0xFF;
        ucBuff[1] = 0xAA;
        ucBuff[2] = 0x67;
        handle->SerialWrite(ucBuff, 3);
        return WIT_HAL_OK;
    }
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
    if(handle->s_uiProtoclo == WIT_PROTOCOL_JY61) return WIT_HAL_INVAL;
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
    if(handle->s_uiProtoclo == WIT_PROTOCOL_JY61) return WIT_HAL_INVAL;
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
    if(handle->s_uiProtoclo == WIT_PROTOCOL_JY61) return WIT_HAL_INVAL;
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
int32_t WitSetUartBaud(jy901_handle_t *handle, int32_t uiBaudIndex)
{
    uint8_t ucBuff[3];
    if(!CheckRange(uiBaudIndex,WIT_BAUD_4800,WIT_BAUD_230400))
    {
        return WIT_HAL_INVAL;
    }
    if(handle->s_uiProtoclo == WIT_PROTOCOL_JY61)
    {
        if((uiBaudIndex == WIT_BAUD_115200) || (uiBaudIndex == WIT_BAUD_9600))
        {
            if(handle->SerialWrite == NULL)return WIT_HAL_EMPTY;
            ucBuff[0] = 0xFF;
            ucBuff[1] = 0xAA;
            if(uiBaudIndex==WIT_BAUD_115200) ucBuff[2] = 0x63;
            else if(uiBaudIndex==WIT_BAUD_9600) ucBuff[2] = 0x64;
            handle->SerialWrite(ucBuff, 3);
            return WIT_HAL_OK;
        }
        else return WIT_HAL_INVAL;
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
int32_t WitSetBandwidth(jy901_handle_t *handle, int32_t uiBaudWidth)
{
    if(handle->s_uiProtoclo == WIT_PROTOCOL_JY61) return WIT_HAL_INVAL;
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
int32_t WitSetOutputRate(jy901_handle_t *handle, int32_t uiRate)
{
    if(handle->s_uiProtoclo == WIT_PROTOCOL_JY61) return WIT_HAL_INVAL;
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
int32_t WitSetContent(jy901_handle_t *handle, int32_t uiRsw)
{
    if(handle->s_uiProtoclo == WIT_PROTOCOL_JY61) return WIT_HAL_INVAL;
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
    if(handle->s_uiProtoclo == WIT_PROTOCOL_JY61) return WIT_HAL_INVAL;
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
    if(handle->s_uiProtoclo == WIT_PROTOCOL_JY61) return WIT_HAL_INVAL;
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
    if(handle->s_uiProtoclo == WIT_PROTOCOL_JY61) return WIT_HAL_INVAL;
    if(WitWriteReg(handle, KEY, KEY_UNLOCK) != WIT_HAL_OK)	    return  WIT_HAL_ERROR;
    if(handle->DelaymsCb != NULL)
    {
        handle->DelaymsCb(20);
    }
    else return WIT_HAL_EMPTY;
    if(WitWriteReg(handle, CALSW, CALREFANGLE) != WIT_HAL_OK)	return  WIT_HAL_ERROR;
    return WIT_HAL_OK;
}
