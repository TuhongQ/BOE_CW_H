/*
* Copyright © Honor Device Co., Ltd. 2020-2021. All rights reserved.
* Description: M平台产品物理号（MEID、IMEI）写入和校验测试模块
* Author: y00011914
* Create: 2021-01-01
*/
#ifndef METKPHYNUM_DEFINE_H
#define METKPHYNUM_DEFINE_H

#include <stdint.h>

struct PhyNumInfo {
    uint8_t meid_rule = 0;
    char meid[32] = {0};
    uint8_t imei_rule = 0;
    char imei[32] = {0};
    uint8_t imei_1_rule = 0;
    char imei_1[32] = {0};
    uint8_t imei_2_rule = 0;
    char imei_2[32] = {0};
    uint8_t imei_3_rule = 0;
    char imei_3[32] = {0};
};

#endif
