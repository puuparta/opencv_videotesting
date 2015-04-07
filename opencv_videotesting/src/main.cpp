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

#include "videotest.h"
#include "filters.h"
#include "tracking.h"
#include "lines.h"

int main() {
	
	// basic video recording test with default fps:20 and user spesified codec.
	// Press ESC to end recording.
	VideoTest video(0);
	bool supported = video.createvideorec("output.avi",10,true);
	if(!supported)
	{
		std::cout<<"The codec selected is not supported to write."<<std::endl;
		getchar();
		return -1;
	}
	
	// to resizable windows:
	//cv::namedWindow("original",cv::WINDOW_NORMAL);
	//cv::namedWindow("filtered",cv::WINDOW_NORMAL);
	
	cv::Mat frame;
	cv::Mat frame2;
	cv::Mat filtered;

	while(true)
	{
		// grap the frame and second frame for movement seek.
		video >> frame;
		video >> frame2;

		// uncomment to test
		// movement tracking test
		//tracking::seekMovement(frame, frame2, true);
		
		// uncomment to test
		// color channel filter test  
		//filtered = filters::binaryFilterRedChannel(frame);
		//cv::imshow("filtered",filtered);
		
		// detect lines with Hough transform
		lines::detectLines(frame);
		cv::imshow("original",frame);
		
		// save frame to write stream if createvideorec is set
		video << frame;

		switch(cv::waitKey(33)) {
		case 27:
			return 0;
		}
	}
}