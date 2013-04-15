/********************************************************************
	创建 :	2012/10/28
	文件 :	.\StereoVision\StereoVision\PointCloudAnalyzer.cpp
	类名 :	PointCloudAnalyzer
	作者 :	邹宇华 chenyusiyuan AT 126 DOT com
	
	功能 :	点云分析与最近物体检测类实现代码
*********************************************************************/

#include "StdAfx.h"
#include "PointCloudAnalyzer.h"


PointCloudAnalyzer::PointCloudAnalyzer(void)
{
}


PointCloudAnalyzer::~PointCloudAnalyzer(void)
{
}


/*----------------------------
 * 功能 : 检测近距目标，输出目标信息序列
 *----------------------------
 * 函数 : PointCloudAnalyzer::detectNearObject
 * 访问 : public 
 * 返回 : void
 *
 * 参数 : image			[io]	左摄像机视图，会进行原位操作，绘制目标尺寸位置
 * 参数 : pointCloud		[in]	三维点云
 * 参数 : objectInfos	[out]	目标信息序列
 */
void PointCloudAnalyzer::detectNearObject(cv::Mat& image, cv::Mat& pointCloud, vector<ObjectInfo>& objectInfos)
{
	if (image.empty() || pointCloud.empty())
	{
		return;
	}

	// 提取深度图像
	vector<cv::Mat> xyzSet;
	split(pointCloud, xyzSet);
	cv::Mat depth;
	xyzSet[2].copyTo(depth);

	// 根据深度阈值进行二值化处理
	double maxVal = 0, minVal = 0;
	cv::Mat depthThresh = cv::Mat::zeros(depth.rows, depth.cols, CV_8UC1);
	cv::minMaxLoc(depth, &minVal, &maxVal);
	double thrVal = minVal * 1.5;
	threshold(depth, depthThresh, thrVal, 255, CV_THRESH_BINARY_INV);
	depthThresh.convertTo(depthThresh, CV_8UC1);
	imageDenoising(depthThresh, 3);

	// 获取离摄像头较近的物体信息
	parseCandidates(depthThresh, depth, objectInfos);

	// 绘制物体分布
	showObjectInfo(objectInfos, image);
}


/*----------------------------
 * 功能 : 图像去噪
 *----------------------------
 * 函数 : PointCloudAnalyzer::imageDenoising
 * 访问 : private 
 * 返回 : void
 *
 * 参数 : img	[in]	待处理图像，原位操作
 * 参数 : iters	[in]	形态学处理次数
 */
void PointCloudAnalyzer::imageDenoising( cv::Mat& img, int iters )
{
	cv::Mat pyr = cv::Mat(img.cols/2, img.rows/2, img.type());

	IplImage iplImg = img;
	cvSmooth(&iplImg, &iplImg, CV_GAUSSIAN, 3, 3);	// 平滑滤波

	pyrDown(img, pyr);	// 对平滑后的图像进行二次缩放
	pyrUp(pyr, img);

	erode(img, img, 0, cv::Point(-1,-1), iters);	// 图像腐蚀
	dilate(img, img, 0, cv::Point(-1,-1), iters);	// 图像膨胀
}


/*----------------------------
 * 功能 : 生成近距物体信息序列
 *----------------------------
 * 函数 : PointCloudAnalyzer::parseCandidates
 * 访问 : private 
 * 返回 : void
 *
 * 参数 : objects		[in]	深度阈值化后的二值图像，显示了近距物体的分布
 * 参数 : depthMap		[in]	从三维点云矩阵中抽取的深度数据矩阵
 * 参数 : objectInfos	[out]	目标信息序列
 */
void PointCloudAnalyzer::parseCandidates(cv::Mat& objects, cv::Mat& depthMap, vector<ObjectInfo>& objectInfos)
{
	// 提取物体轮廓
	vector<vector<cv::Point> > contours;	// 物体轮廓点链
	findContours(objects, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);

	// 分析轮廓
	double areaThresh = 0.005 * depthMap.rows * depthMap.cols;
	cv::Mat mask = cv::Mat::zeros(objects.size(), CV_8UC1);
	bool useMeanDepth = false;

	for( UINT objID = 0; objID < contours.size(); objID++ )
	{
		cv::Mat contour = cv::Mat( contours[objID] );
		double area = contourArea( contour );
		if ( area > areaThresh ) // 面积大于 100 像素时，才有效
		{
			ObjectInfo object;

			// 填充物体内部轮廓作为掩码区域
			mask = cv::Scalar(0);
			drawContours(mask, contours, objID, cv::Scalar(255), -1);

			// 计算轮廓矩形
			object.boundRect = boundingRect( contour );
			object.minRect = minAreaRect( contour );
			object.center = object.minRect.center;

			// 计算物体深度
			if (useMeanDepth) //取平均深度
			{
				cv::Scalar meanVal = cv::mean(depthMap, mask);
				object.distance = meanVal[0];
                object.nearest = object.center;
			} 
			else	//取最近深度
			{
				double minVal = 0, maxVal = 0;
				cv::Point minPos;
                cv::minMaxLoc(depthMap, &minVal, &maxVal, &minPos, NULL, mask);
                object.nearest = minPos;
				object.distance = depthMap.at<float>(minPos.y, minPos.x);
			}

			// 保存物体轮廓信息
			objectInfos.push_back( object );
		}
	}

	// 按物体距离重新排序
	std::sort( objectInfos.begin(), objectInfos.end(), std::less<ObjectInfo>() );
}


/*----------------------------
 * 功能 : 绘制近距物体尺寸和位置
 *----------------------------
 * 函数 : PointCloudAnalyzer::showObjectInfo
 * 访问 : private 
 * 返回 : void
 *
 * 参数 : objectInfos	[in]	近距物体信息序列
 * 参数 : outImage		[io]	左摄像头图像，在该图像上绘制近距物体信息
 */
void PointCloudAnalyzer::showObjectInfo(vector<ObjectInfo>& objectInfos, cv::Mat& outImage)
{
	int showCount = objectInfos.size() < 5 ? objectInfos.size() : 5;
	
	// 画出所有靠近的物体
	for (int i = 0; i < showCount; i++)
	{
		//物体中心
		circle(outImage, objectInfos[i].center, 3, CV_RGB(0,0,255), 2);
		
		//物体最小矩形
		cv::Point2f rect_points[4]; 
		objectInfos[i].minRect.points( rect_points );
		if (i==0)
		{
			for( int j = 0; j < 4; j++ )
				line( outImage, rect_points[j], rect_points[(j+1)%4], CV_RGB(255,0,0), 4 );
		} 
		else
		{
			for( int j = 0; j < 4; j++ )
				line( outImage, rect_points[j], rect_points[(j+1)%4], CV_RGB(255-i*40,i*40,0), 2 );
		}
	}
}

