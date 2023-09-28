#include <math.h>
#include <string.h>
#include "other.h"

#include "pid.h"

const pid_param_t initial_pid = {                   //初始 pid 参数
        .Expect = 0,                          //期望
        .FeedBack = 0,                        //反馈值
        .Err = 0,                             //偏差
        .Err_Max = 0,                         //偏差限幅值
        .Integrate_Separation_Err = 0,        //积分分离偏差值
        .Integrate = 0,                       //积分值
        .Integrate_Max = 0,                   //积分限幅值
        .Kp = 0,                              //控制参数Kp
        .Ki = 0,                              //控制参数Ki
        .Kd = 0,                              //控制参数Kd
        .Control_OutPut = 0,                  //控制器总输出
        .Last_Control_OutPut = 0,             //上次控制器总输出
        .Control_OutPut_Limit = 0,            //输出限幅
        .Pre_Last_Err = 0,                    //上上次偏差
        .Adaptable_Kd = 0,                    //自适应微分参数
        .Last_FeedBack = 0,                   //上次反馈值
        .Dis_Err = 0,                         //微分量
        .Dis_Error_History = {0},             //历史微分量
        .Err_LPF = 0,
        .Last_Err_LPF = 0,
        .Dis_Err_LPF = 0,
        .Last_Dis_Err_LPF = 0,
        .Pre_Last_Dis_Err_LPF = 0,
        .Scale_Kp = 0,
        .Scale_Ki = 0,
        .Scale_Kd = 0,
};

/**
 * @brief PID参数初始化函数
 * @param pid 参数
 * @return 失败返回 -1, 成功返回 0
 */
int pid_parm_init(pid_param_t *pid)
{
    if (memcpy(pid, &initial_pid, sizeof(pid_param_t)) == NULL)
    {
        return -1;
    }
    return 0;
}

/**
 * @brief PID 控制器（计算输出）
 * @param pid 参数
 * @return 返回 pid 的输出
 */
float pid_control(pid_param_t *pid)
{
    /*******偏差计算*********************/
    pid->Last_Err = pid->Err;                     //保存上次偏差
    pid->Err = pid->Expect - pid->FeedBack; //期望减去反馈得到偏差
    if (pid->Err_Limit_Flag == 1)                       //偏差限幅度标志位
    {
        pid->Err = constrain(pid->Err, -pid->Err_Max, pid->Err_Max);
    }
    /*******积分计算*********************/
    if (pid->Integrate_Separation_Flag == 1) //积分分离标志位
    {
        if (fabs((double)pid->Err) <= pid->Integrate_Separation_Err)
            pid->Integrate += pid->Scale_Ki * pid->Ki * pid->Err;
    }
    else
    {
        pid->Integrate += pid->Scale_Ki * pid->Ki * pid->Err;
    }
    /*******积分限幅*********************/
    if (pid->Integrate_Limit_Flag == 1) //积分限制幅度标志
    {
        pid->Integrate = constrain(pid->Integrate, -pid->Integrate_Max, pid->Integrate_Max);
    }
    /*******总输出计算*********************/
    pid->Last_Control_OutPut = pid->Control_OutPut; //输出值递推
    pid->Control_OutPut =
            pid->Scale_Kp * pid->Kp * pid->Err      //比例
            + pid->Integrate                        //积分
            + pid->Kd * (pid->Err - pid->Last_Err); //微分
    /*******总输出限幅*********************/
    pid->Control_OutPut = constrain(pid->Control_OutPut, -pid->Control_OutPut_Limit, pid->Control_OutPut_Limit);
    /*******返回总输出*********************/
    return pid->Control_OutPut;
}
