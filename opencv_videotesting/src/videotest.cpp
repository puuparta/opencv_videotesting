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


/**
 * Constructor with deviceid
 */
VideoTest::VideoTest(int device)
{
	this->player.open(device);
}

/**
 * Constructor with filename / url
 */
VideoTest::VideoTest(const std::string& name)
{
	this->player.open(name);
}

/**
 * Constructor default
 */
VideoTest::VideoTest(void)
{

}

/**
 * Destructor to release palyer and writer.
 */
VideoTest::~VideoTest()
{
	this->player.release();
	this->writer.release();
}

/**
 * Opens the video capturing with selected device
 */
CV_WRAP bool VideoTest::open(int device)
{
	return this->player.open(device);
}

/**
 * Opens the video capturing with selected device
 */
CV_WRAP bool VideoTest::open(const std::string& name)
{
	return this->player.open(name);
}

/**
 * Create video recorder with output filename, fps and fourcc.
 */
CV_WRAP bool VideoTest::createvideorec(const std::string& filename,int fps, char c1, char c2, char c3, char c4, bool ask)
{
	#if CV_VERSION_MAJOR == 3
		int fcc = cv::VideoWriter::fourcc(c1,c2,c3,c4);
		int propFrameWidth = cv::CAP_PROP_FRAME_WIDTH;
		int propFrameHeight = cv::CAP_PROP_FRAME_HEIGHT;
	#else 
		int fcc = CV:FOURCC(c1,c2,c3,c4);
		int propFrameWidth = CV_CAP_PROP_FRAME_WIDTH;
		int propFrameHeight = CV_CAP_PROP_FRAME_HEIGHT;
	#endif
	
	if(ask)
		fcc=-1;

	cv::Size frameSize(this->player.get(propFrameWidth), this->player.get(propFrameHeight));
	return this->writer.open(filename,fcc,fps,frameSize,true);
}

/**
 * Create video recorder with output filename, fps.
 * Default fourcc is DIV3.
 */
CV_WRAP bool VideoTest::createvideorec(const std::string& filename, int fps, bool ask)
{
	return this->createvideorec(filename, fps, 'D','I','V','3', ask);
}

/**
 * Create video recorder with output filename.
 * Default fps taken from source stream, default fourcc is DIV3.
 */
CV_WRAP bool VideoTest::createvideorec(const std::string& filename, bool ask)
{
	int fps = 20; //this->player.get(cv::CAP_PROP_FPS);
	return this->createvideorec(filename, fps, ask);
}

/**
 * Algorithm under test.
 * Todo: implementation coming.
 */
int VideoTest::algorithm1()
{
	return 42;
}

/**
 * Return the underlying VideoCapture object
 */
CV_WRAP cv::VideoCapture VideoTest::Player()
{
	return this->player;
}

/**
 * Return the underlying VideoWriter object
 */
CV_WRAP cv::VideoWriter VideoTest::Recorder()
{
	return this->writer;
}

/**
 * Returns frame of Video stream.
 * Will be called inside loop.
 */
cv::Mat VideoTest::currentframe()
{
	this->player.read(this->frame);
	return this->frame;
}

/**
 * Writes frame to VideoWriter input stream.
 */
CV_WRAP void VideoTest::writeframe(const cv::Mat &frame)
{
	this->writer.write(frame);
}


VideoTest& VideoTest::operator >> (cv::Mat& image)
{
	this->player.read(image);
    return *this;
}

VideoTest& VideoTest::operator << (const cv::Mat& image)
{
	this->writer.write(image);
    return *this;
}