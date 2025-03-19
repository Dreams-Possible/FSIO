//启用命令行
#if 1
#ifndef CMD_H
#define CMD_H

//引用
#include<stdint.h>
#include<stdio.h>
#include"fsio.h"

//命令行初始化
uint8_t cmd_init();
//命令行保持运行
void cmd_run();

#endif//#ifndef CMD_H
#endif//#if 1
