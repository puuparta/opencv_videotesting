// The MIT License (MIT)

// Copyright (c) 2015 Pasi Heinonen

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#ifndef __LITECV_LIB_FILTERS_HPP__
#define __LITECV_LIB_FILTERS_HPP__

#include <opencv2\opencv.hpp>

namespace filters 
{
		
	typedef enum 
	{ 
		COLOR_R = 4,
		COLOR_G = 2,
		COLOR_B = 1
	} COLOR;

	cv::Mat binaryFilterColorChannelFromBGR(cv::Mat frame, COLOR color)
	{
		cv::Mat thresh_frame;
		std::vector<cv::Mat> channels;
		cv::split(frame, channels);
		cv::Mat red = channels[2];
		cv::Mat green = channels[1];
		cv::Mat blue = channels[0];
		cv::Mat roi;
		cv::Mat sub1;
		cv::Mat sub2;
		if(color==COLOR_R)
		{
			roi=red;
			sub1=green;
			sub2=blue;
		}
		else if(color==COLOR_G)
		{
			roi=green;
			sub1=blue;
			sub2=red;
		}
		else if(color==COLOR_B)
		{
			roi=blue;
			sub1=red;
			sub2=green;
		}

		// add two filtered out channels together sub2=sub1+sub2
		cv::add(sub1, sub2, sub2);
	
		// remove combined not interest channels from the ROI channel roi = roi-sub2
		cv::subtract(roi, sub2, roi);
    
		// binarize and blur the ROI channel
		cv::threshold(roi, frame, 5, 255, cv::THRESH_BINARY);
		cv::medianBlur(frame, thresh_frame, 5);
		return thresh_frame;

		//cv::imshow("binarized",thresh_frame);
	}

	cv::Mat binaryFilterBlueChannel(cv::Mat frame)
	{
		return binaryFilterColorChannelFromBGR(frame, COLOR::COLOR_B);
	}

	cv::Mat binaryFilterGreenChannel(cv::Mat frame)
	{
		return binaryFilterColorChannelFromBGR(frame, COLOR::COLOR_G);
	}

	cv::Mat binaryFilterRedChannel(cv::Mat frame)
	{
		return binaryFilterColorChannelFromBGR(frame, COLOR::COLOR_R);
	}

	void showColorChannels(const cv::Mat& frame)
	{
		std::vector<cv::Mat> channels;
		cv::split(frame, channels);
		cv::imshow("Red", channels[2]);
		cv::imshow("Green", channels[1]);
		cv::imshow("Blue", channels[0]);
	}
}

#endif