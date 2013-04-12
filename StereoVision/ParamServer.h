
#ifndef _C_PARAM_SERVER_H_
#define _C_PARAM_SERVER_H_

#pragma once

#include "direct.h"
#include "stdio.h"
#include "opencv2/core/core.hpp"

using namespace std;

class ParamServer
{
public:
	static ParamServer* instance();

	int ImageWidth() { return image_width; }
	int ImageHeight() { return image_height; }

private:
	ParamServer();
	void init();

	cv::FileStorage fs;
	static ParamServer* _instance;

	int image_width;
	int image_height;
};


#endif