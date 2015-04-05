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

#ifndef __LITECV_LIB_TRACKING_HPP__
#define __LITECV_LIB_TRACKING_HPP__

#include <opencv2\opencv.hpp>
#include "videotest.h"

namespace tracking 
{
	/**
	 Movement tracking simple algorithm which compute 
	 element-wise absolute difference of two frames/images.
	 This absdif image is then binarized and noise reduced to get
	 clean outer contours. Outer contours indicates the location where most
	 intensive movement is spotted.
	 */
	void seekMovement(cv::Mat &frame1, cv::Mat frame2, bool show_image=false)
	{
		cv::Mat grayImage1, grayImage2, diff, thres;

		const static int TRESH_SENSITIVITY = 20;
		const static int BLUR_SIZE = 10;

		// convert frames to grayscale for frame differencing
		// this will remove not needed color information
		cv::cvtColor(frame1,grayImage1,cv::COLOR_BGR2GRAY);
		cv::cvtColor(frame2,grayImage2,cv::COLOR_BGR2GRAY);

		// get the grayscale absolute difference
		// this shows the movement very nicely
		cv::absdiff(grayImage1,grayImage2,diff);

		// binarize+blur+binarize to filter clear movement.
		// with blurring we get rid of noise.
		cv::threshold(diff,thres,TRESH_SENSITIVITY,255,cv::THRESH_BINARY);
		cv::blur(thres,thres,cv::Size(BLUR_SIZE,BLUR_SIZE));
		cv::threshold(thres,thres,TRESH_SENSITIVITY,255,cv::THRESH_BINARY);

		if(show_image)
			cv::imshow("threshold movement", thres);

		// vector of contours. Contour is Point vector itself.
		std::vector<std::vector<cv::Point>> contours;
		std::vector<cv::Vec4i> hierarchy;

		//findContours(temp,contours,hierarchy,CV_RETR_CCOMP,CV_CHAIN_APPROX_SIMPLE );// retrieves all contours
		cv::findContours(thres,contours,hierarchy,cv::RETR_EXTERNAL,cv::CHAIN_APPROX_SIMPLE );

		// if any contours found then we have movement
		if(contours.size()>0)
		{
			// contours are sorted to vector so that largest is at the end.
			// store largest contour to own vector and draw overlay rectangle
			// to indicate region of movement.
			std::vector<std::vector<cv::Point>> romContour;
			romContour.push_back(contours.at(contours.size()-1));
			cv::Rect movementRectangle = cv::boundingRect(romContour.at(0));
			cv::rectangle(frame1,movementRectangle, cv::Scalar(0,255,0),2);
		}
	}

	void seekMovement(VideoTest video, bool show_image=false)
	{
		cv::Mat frame1, frame2;
		video >> frame1;
		video >> frame2;
		seekMovement(frame1,frame2,show_image);
	}
}

#endif