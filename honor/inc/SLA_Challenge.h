/*
* Copyright © Honor Device Co., Ltd. 2020-2021. All rights reserved.
* Description: MTK平台SLA鉴权使用
* Author: y00011914
* Create: 2021-06-17
*/

#ifndef SLA_CHALLENGE_H
#define SLA_CHALLENGE_H

#ifndef WAIT_SLA_CHALLENGE_EXPORT
#define SLA_CHALLENGE_API __declspec(dllimport)
#else
#define SLA_CHALLENGE_API __declspec(dllexport)
#endif

#ifdef __cplusplus 
extern "C" { 
#endif // _cplusplus

SLA_CHALLENGE_API __stdcall int SLA_Challenge(void *usr_arg, const unsigned char *p_challenge_in, unsigned int challenge_in_len, unsigned char **pp_challenge_out, unsigned int *p_challenge_out_len);
SLA_CHALLENGE_API __stdcall int SLA_Challenge_END(void *usr_arg, unsigned char *p_challenge_out);
SLA_CHALLENGE_API int SLA_Feature_Config();

#ifdef __cplusplus 
} 
#endif // _cplusplus

#endif