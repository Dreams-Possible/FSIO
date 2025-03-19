#include"fsio.h"
#include"cmd.h"

void main()
{
	//FSIO初始化
	fsio_init();
	
	//命令行初始化
	cmd_init();

	//命令行保持运行
	cmd_run();

	return;
}