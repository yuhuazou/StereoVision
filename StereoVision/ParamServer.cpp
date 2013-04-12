#include "StdAfx.h"
#include "ParamServer.h"


ParamServer* ParamServer::_instance = NULL;


ParamServer::ParamServer() 
{
	init();
}

ParamServer* ParamServer::instance() {
	if (_instance == NULL) {
		_instance = new ParamServer();
	}
	return _instance;
}


void ParamServer::init()
{
	// 默认打开固定路径中的 yml 文件
	bool isOpened = fs.open("D:\\Projects\\Kinect_NI\\Release\\params.yml", cv::FileStorage::READ);
	if (!isOpened)
	{// 如果打开失败，则打开 release 文件夹中的 yml 文件
		isOpened = fs.open("params.yml", cv::FileStorage::READ);
	}

	if ( isOpened )
	{// 打开 yml 文件成功
		printf("[- Paramater Loading] Loaded data from File params.yml .");

		fs["image_width"]		>> image_width;
		fs["image_height"]		>> image_height;
	} 
	else
	{// 打开 yml 文件失败，则使用默认参数
		printf("[- Paramater Loading] File params.yml does not exist, load default values.");

		image_width		= 640;
		image_height	= 480;
	}
}


