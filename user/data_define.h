//
// Created by fxf on 23-7-9.
//

#ifndef DATA_DEFINE_H
#define DATA_DEFINE_H

typedef struct sensor
{
    float depth;
    float yaw;
    float temperature;
} sensor_t;

typedef struct rocket
{
    double x;  //左右
    double y;  //前后
    double z;  //上下
    double yaw;
} rocket_t;

typedef struct rov_info {
    struct rocket rocket;
    struct sensor sensor;
} rov_info_t;

#endif //DATA_DEFINE_H
