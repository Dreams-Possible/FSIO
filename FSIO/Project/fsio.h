//启用FSIO
#if 1
#ifndef FSIO_H
#define FSIO_H
//引用
#include<stdint.h>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<dirent.h>

//FSIO初始化
uint8_t fsio_init();
//FSIO打开目标
uint8_t fsio_open(char*path);

#endif//#ifndef FSIO_H
#endif//#if 1
