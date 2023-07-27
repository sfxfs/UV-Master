//
// Created by fxf on 2023/7/27.
//

#ifndef DRIVER_JY901_H
#define DRIVER_JY901_H

#include <stdint.h>

#ifdef __cplusplus
extern "C"{
#endif

#define WIT_DATA_BUFF_SIZE  256
#define REGSIZE        0x90

typedef enum
{
    WIT_HAL_OK = 0,
    WIT_HAL_BUSY = -1,
    WIT_HAL_TIMEOUT = -2,
    WIT_HAL_ERROR = -3,
    WIT_HAL_NOMEM = -4,
    WIT_HAL_EMPTY = -5,
    WIT_HAL_INVAL = -6,
} wit_status_t;

typedef enum
{
    WIT_PROTOCOL_NORMAL = 0,
    WIT_PROTOCOL_MODBUS,
    WIT_PROTOCOL_CAN,
    WIT_PROTOCOL_I2C,
    WIT_PROTOCOL_JY61,
    WIT_PROTOCOL_905x_MODBUS,
    WIT_PROTOCOL_905x_CAN,
} wit_protocol_t;

typedef enum
{
    RSW_TIME = 0x01,
    RSW_ACC = 0x02,
    RSW_GYRO = 0x04,
    RSW_ANGLE = 0x08,
    RSW_MAG = 0x10,
    RSW_PORT = 0x20,
    RSW_PRESS = 0x40,
    RSW_GPS = 0x80,
    RSW_V = 0x100,
    RSW_Q = 0x200,
    RSW_GSA = 0x400,
    RSW_MASK = 0xfff,
} wit_rsw_t;

typedef enum
{
    RRATE_02HZ = 1,
    RRATE_05HZ,
    RRATE_1HZ,
    RRATE_2HZ,
    RRATE_5HZ,
    RRATE_10HZ,
    RRATE_20HZ,
    RRATE_50HZ,
    RRATE_100HZ,
    RRATE_125HZ,	//only WT931
    RRATE_200HZ,
    RRATE_ONCE,
    RRATE_NONE,
} wit_rrate_t;

typedef enum
{
    WIT_BAUD_4800 = 1,
    WIT_BAUD_9600,
    WIT_BAUD_19200,
    WIT_BAUD_38400,
    WIT_BAUD_57600,
    WIT_BAUD_115200,
    WIT_BAUD_230400,
    WIT_BAUD_460800,
    WIT_BAUD_921600,
} wit_baud_t;

typedef enum
{
    KEY_UNLOCK = 0xB588,
} wit_key_t;

typedef enum
{
    SAVE_PARAM = 0x00,
    SAVE_SWRST = 0xff,
} wit_save_t;

typedef enum
{
    ORIENT_HERIZONE = 0,
    ORIENT_VERTICLE,
} wit_orient_t;

typedef enum
{
    BANDWIDTH_256HZ = 0,
    BANDWIDTH_184HZ,
    BANDWIDTH_94HZ,
    BANDWIDTH_44HZ,
    BANDWIDTH_21HZ,
    BANDWIDTH_10HZ,
    BANDWIDTH_5HZ,
} wit_bandwidth_t;

typedef struct jy901_handle_s
{
    void (*SerialWrite)(uint8_t *p_ucData, uint32_t uiLen);
    int32_t (*WitI2cWrite)(uint8_t ucAddr, uint8_t ucReg, uint8_t *p_ucVal, uint32_t uiLen);
    int32_t (*WitI2cRead)(uint8_t ucAddr, uint8_t ucReg, uint8_t *p_ucVal, uint32_t uiLen);
    void (*DelaymsCb)(uint16_t ucMs);
    void (*RegUpdateCb)(uint32_t uiReg, uint32_t uiRegNum);
    uint8_t s_ucAddr;
    uint8_t s_ucWitDataBuff[WIT_DATA_BUFF_SIZE];
    uint32_t s_uiWitDataCnt;
    uint32_t s_uiProtoclo;
    uint32_t s_uiReadRegIndex;
    int16_t sReg[REGSIZE];
} jy901_handle_t;

void WitSerialDataIn(jy901_handle_t *handle, uint8_t ucData);
int32_t WitWriteReg(jy901_handle_t *handle, uint32_t uiReg, uint16_t usData);
int32_t WitReadReg(jy901_handle_t *handle, uint32_t uiReg, uint32_t uiReadNum);
int32_t WitInit(jy901_handle_t *handle, uint32_t uiProtocol, uint8_t ucAddr);
void WitDeInit(jy901_handle_t *handle);

int32_t WitStartAccCali(jy901_handle_t *handle);
int32_t WitStopAccCali(jy901_handle_t *handle);
int32_t WitStartMagCali(jy901_handle_t *handle);
int32_t WitStopMagCali(jy901_handle_t *handle);
int32_t WitSetUartBaud(jy901_handle_t *handle, int32_t uiBaudIndex);
int32_t WitSetBandwidth(jy901_handle_t *handle, int32_t uiBaudWidth);
int32_t WitSetOutputRate(jy901_handle_t *handle, int32_t uiRate);
int32_t WitSetContent(jy901_handle_t *handle, int32_t uiRsw);
int32_t WitSaveParameter(jy901_handle_t *handle);
int32_t WitSetForReset(jy901_handle_t *handle);
int32_t WitCaliRefAngle(jy901_handle_t *handle);

#ifdef __cplusplus
}
#endif

#endif //DRIVER_JY901_H
