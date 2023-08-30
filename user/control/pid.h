#ifndef CONTROL_PID_H
#define CONTROL_PID_H

#include <stdint.h>

#define constrain(amt,low,high) ((amt)<(low)?(low):((amt)>(high)?(high):(amt))) //限幅函数

typedef struct pid_param
{
    uint8_t Err_Limit_Flag : 1;            //偏差限幅标志   位定义
    uint8_t Integrate_Limit_Flag : 1;      //积分限幅标志
    uint8_t Integrate_Separation_Flag : 1; //积分分离标志
    float Expect;                          //期望
    float FeedBack;                        //反馈值
    float Err;                             //偏差
    float Last_Err;                        //上次偏差
    float Err_Max;                         //偏差限幅值
    float Integrate_Separation_Err;        //积分分离偏差值
    float Integrate;                       //积分值
    float Integrate_Max;                   //积分限幅值
    float Kp;                              //控制参数Kp  12
    float Ki;                              //控制参数Ki  13
    float Kd;                              //控制参数Kd  14
    float Control_OutPut;                  //控制器总输出
    float Last_Control_OutPut;             //上次控制器总输出
    float Control_OutPut_Limit;            //输出限幅
    /***************************************/
    float Pre_Last_Err;         //上上次偏差
    float Adaptable_Kd;         //自适应微分参数
    float Last_FeedBack;        //上次反馈值
    float Dis_Err;              //微分量
    float Dis_Error_History[5]; //历史微分量
    float Err_LPF;
    float Last_Err_LPF;
    float Dis_Err_LPF;
    float Last_Dis_Err_LPF;
    float Pre_Last_Dis_Err_LPF;
    float Scale_Kp;
    float Scale_Ki;
    float Scale_Kd;
} pid_param_t;

int pid_parm_init(pid_param_t *pid);
float pid_control(pid_param_t *pid);

#endif
