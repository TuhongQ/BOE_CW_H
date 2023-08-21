/*
 * Copyright © Honor Device Co., Ltd. 2020-2021. All rights reserved.
 * Description: LOG打印和数据回传基础模块的回调函数类型定义
 * Author: y00011914
 * Create: 2021-01-01
 */
#ifndef SHOWINFORMATION_DEFINE_H
#define SHOWINFORMATION_DEFINE_H

using CallbackInfo = void(void* param, const char* info);
using CallbackInfoValue = void(void* param, const char* info, const char* value);
using CallbackInfoValueLimit = void(void* param, const char* info, double value, double upLimit, double lowLimit);
using CallbackStop = int(void* param); // 当外部需要停止时此函数返回-1，当外部不需要停止时次函数返回0

struct CallbackParam {
    CallbackInfo* saveFunctionRecord;
    CallbackInfo* showNormalInformation;
    CallbackInfo* showFailInformation;
    CallbackInfo* showDebugInformation;
    CallbackInfoValue* uploadStringValue;
    CallbackInfoValueLimit* uploadDoubleValue;
    CallbackStop* stopWhenNeed;
    void* callbackFunctionReserve1;
    void* callbackFunctionReserve2;
    void* callbackFunctionReserve3;
    void* param;
    char* logPath;
    char* sn;
    void* record;
    void* paramReserve1;
    void* paramReserve2;
    void* paramReserve3;
};

#endif // SHOWINFORMATION_DEFINE_H
