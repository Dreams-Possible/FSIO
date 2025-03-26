#include"cmd.h"
//如果启用命令行
#ifdef CMD_H

//配置
#define ui_print printf
#define err_print printf
#define clean() system("cls")
#define MAX_CMD_LEN 1024
#define CMD_INPUT "cmd>>"

//命令行资源
typedef struct cmd_t
{
    char*all;
    char*use;
}cmd_t;
static cmd_t*cmd=NULL;

//命令行初始化
uint8_t cmd_init();
//命令行保持运行
void cmd_run();

//命令行初始化
uint8_t cmd_init()
{
    //申请资源
    cmd=malloc(sizeof(cmd_t));
    if(!cmd)
    {
        //命令行初始化失败
        err_print("cmd: cmd_init: init fail\n");
        return 1;
    }
    cmd->all=NULL;
    cmd->use=NULL;
    cmd->all=malloc(MAX_CMD_LEN);
    if(!cmd)
    {
        //命令行初始化失败
        err_print("cmd: cmd_init: init fail\n");
        return 1;
    }
    memset(cmd->all,0,MAX_CMD_LEN);
    //命令行初始化成功
    ui_print("cmd: cmd_init: init ok\n");
    return 0;
}

//命令行保持运行
void cmd_run()
{
    while(1)
    {
        ui_print(CMD_INPUT);
        //接受指令字符串
        fgets(cmd->all,MAX_CMD_LEN,stdin);
        //删除换行符
        cmd->all[strcspn(cmd->all,"\n")]=0;
        //使用空格分离参数
        cmd->use=strtok(cmd->all," ");
        //如果没有输入
        if(cmd->use==NULL)
        {
            err_print("cmd: cmd_run: no input\n");
        }else
        //清屏
        if(strcmp(cmd->use,"cl")==0)
        {
            clean();
        }else
        //FSIO文件操作
        if(strcmp(cmd->use,"fs")==0)
        {
            cmd->use=strtok(NULL," ");
            //如果有参数
            if(cmd->use!=NULL)
            {
                //显示目标
                if(strcmp(cmd->use,"l")==0)
                {
                    fsio_open("");
                }else
                //打开目标
                if(strcmp(cmd->use,"o")==0)
                {
                    char*path=strtok(NULL," ");
                    fsio_open(path);
                }else
                //创建目标
                if(strcmp(cmd->use,"c")==0)
                {
                    char*type=strtok(NULL," ");
                    char*path=strtok(NULL," ");
                    if(type&&path)
                    {
                        switch(type[0])
                        {
                            case 'd':
                                fsio_creat(FSIO_TYPE_DIR,path);
                            break;
                            case 'f':
                                fsio_creat(FSIO_TYPE_FILE,path);
                            break;
                            default:
                                fsio_creat(FSIO_TYPE_NULL,path);
                            break;
                        }
                    }else
                    {
                        err_print("cmd: cmd_run: can not find cmd\n");
                    }
                }else
                //删除目标
                if(strcmp(cmd->use,"d")==0)
                {
                    char*path=strtok(NULL," ");
                    fsio_delete(path);
                }else
                // //用于测试
                // if(strcmp(cmd->use,"t")==0)
                // {
                //     char*path=strtok(NULL," ");
                //     // fsio_creat(path);
                //     // fsio_delete(path);
                // }else
                {
                    err_print("cmd: cmd_run: can not find cmd\n");
                }
            }else
            {
                err_print("cmd: cmd_run: can not find cmd\n");
            }
        }else
        {
            err_print("cmd: cmd_run: can not find cmd\n");
        }
    }
}

#endif//#ifdef CMD_H
