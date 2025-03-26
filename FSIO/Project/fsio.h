//启用FSIO
#if 1
#ifndef FSIO_H
#define FSIO_H
//引用
#include<stdint.h>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>//提供写入文件支持
#include<dirent.h>//提供遍历目录支持
#include<fcntl.h>//提供创建文件支持
#include<unistd.h>//提供删除文件支持
#include<sys/stat.h>//提供创建目录支持
#include<unistd.h>//提供删除目录支持

//定义
#define FSIO_TYPE_DIR 1
#define FSIO_TYPE_FILE 2
#define FSIO_TYPE_NULL 3

//FSIO初始化
uint8_t fsio_init();
//FSIO打开目标
uint8_t fsio_open(char*path);
//FSIO创建目标
uint8_t fsio_creat(uint8_t type,char*path);
//FSIO删除目标
uint8_t fsio_delete(char*path);

#endif//#ifndef FSIO_H
#endif//#if 1
