#include"fsio.h"
//如果启用FSIO
#ifdef FSIO_H

//配置
#define ui_print printf//FSIO界面输出
#define err_print printf//FSIO错误输出
#define MAX_PATH_LEN 1*1024//路径长度上限
#define ROOT_PATH "/Users/Windows/Desktop/FSIO"//must begin with /

//定义
#define DIR_TYPE 1
#define FILE_TYPE 2
#define NULL_TYPE 3

//FSIO资源
typedef struct fsio_t
{
    char*path;
}fsio_t;
static fsio_t*fsio=NULL;

//FSIO初始化
uint8_t fsio_init();
//判断目标类型
static uint8_t data_type(char*path);
//FSIO打开目标
uint8_t fsio_open(char*path);
//补全路径
static char*fill_path(char*path);
//列出当前目录
static uint8_t dir_list();
//打印当前文件
static uint8_t file_print();

//FSIO初始化
uint8_t fsio_init()
{
    //申请资源
    fsio=malloc(sizeof(fsio_t));
    if(!fsio)
    {
        //命令行初始化失败
        err_print("fsio: fsio_init: init fail\n");
        return 1;
    }
    //初始化
    memset(fsio,0,sizeof(fsio_t));
    fsio->path=NULL;
    if(fsio_open(ROOT_PATH))
    {
        //命令行初始化失败
        err_print("fsio: fsio_init: init fail\n");
        return 1;
    }
    //命令行初始化成功
    ui_print("fsio: fsio_init: init ok\n");
    return 0;
}

//判断目标类型
static uint8_t data_type(char*path)
{
    //同时使用两种方式打开
    DIR*dir=opendir(path);
    FILE*fl=fopen(path,"r");
    //是目录
    if(dir!=NULL)
    {
        closedir(dir);
        fclose(fl);
        return DIR_TYPE;
    }else
    //是文件
    if(fl!=NULL)
    {
        closedir(dir);
        fclose(fl);
        return FILE_TYPE;
    }else
    //无效路径
    {
        closedir(dir);
        fclose(fl);
        return NULL_TYPE;
    }
}

//FSIO打开目标
uint8_t fsio_open(char*path)
{
    //路径为空
    if(!path)
    {
        err_print("fsio: fsio_init: invaild path\n");
        return 1;
    }
    //补全完整路径
    char*full_path=fill_path(path);
    //判断目标类型
    uint8_t type=data_type(full_path);
    switch(type)
    {
        //如果是目录
        case DIR_TYPE:
            //释放上一路径资源
            free(fsio->path);
            //更新当前路径
            fsio->path=full_path;
            //列出当前目录
            dir_list();
        break;
        //如果是文件
        case FILE_TYPE:
            //释放上一路径资源
            free(fsio->path);
            //更新当前路径
            fsio->path=full_path;
            //打印当前文件
            file_print();
        break;
        //路径无效
        default:
            //释放路径资源
            free(full_path);
            err_print("fsio: fsio_init: invaild type\n");
            return 1;
        break;
    }
    return 0;
}

//补全路径
static char*fill_path(char*path)
{
    char*full_path=malloc(MAX_PATH_LEN);
    memset(full_path,0,MAX_PATH_LEN);
    //已经提供了完整路径
    if(path[0]=='/')
    {
        //检查路径长度
        uint16_t len=strlen(path);
        if(len<MAX_PATH_LEN)
        {
            //拷贝完整路径
            memcpy(full_path,path,len);
            //如果非根目录结尾有斜杠去掉
            if(full_path[len-1]=='/'&&len!=1)
            {
                full_path[len-1]=0;
            }
        }else
        {
            //超出最大路径长度
            err_print("fsio: fill_path: out of length\n");
        }
    }else
    //未提供完整路径
    {
        //检查路径长度
        uint16_t len_1=strlen(fsio->path);
        uint16_t len_2=strlen(path);
        if(len_1+len_2<MAX_PATH_LEN-1)
        {
            //如果是保持路径
            if(strcmp(path,".")==0)
            {
                memcpy(full_path,fsio->path,len_1);
            }else
            //如果是返回路径
            if(strcmp(path,"..")==0)
            {
                memcpy(full_path,fsio->path,len_1);
                uint16_t num=0;
                uint16_t f=0;
                //定位最后一个斜杠
                for(f=0;f<len_1;++f)
                {
                    if(full_path[f]=='/')
                    {
                        num=f;
                    }
                }
                //如果不是根目录
                if(num!=0)
                {
                    memset(&full_path[num],0,len_1-num);
                }
            }else
            {
                //拼接完整路径
                memcpy(full_path,fsio->path,len_1);
                //如果目录为空或处在根目录不添加斜杠
                if(path[0]==0||len_1==1)
                {
                    memcpy(&full_path[len_1],path,len_2);
                }else
                {
                    full_path[len_1]='/';
                    memcpy(&full_path[len_1+1],path,len_2);
                } 
            }
        }else
        {
            //超出最大路径长度
            err_print("fsio: fill_path: out of length\n");
        }
    }
    return full_path;
}

//列出当前目录
static uint8_t dir_list()
{
    DIR*dir=opendir(fsio->path);
    ui_print("%s:\n",fsio->path);
    struct dirent *entry;
    while((entry=readdir(dir))!=NULL)
    {
        ui_print("%s\n",entry->d_name);
    }
    closedir(dir);
    return 0;
}

//打印当前文件
static uint8_t file_print()
{
    FILE*fl=fopen(fsio->path,"r");
    ui_print("%s:\n",fsio->path);
    char c=0;
    while((c=fgetc(fl))!=EOF)
    {
        ui_print("%c",c);
    }
    ui_print("\n");
    fclose(fl);
    return 0;
}

#endif//#ifdef FSIO_H
