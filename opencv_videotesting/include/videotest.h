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

#ifndef __LITECV_LIB_VIDEOTEST_HPP__
#define __LITECV_LIB_VIDEOTEST_HPP__

#ifndef __cplusplus
#  error videotest.hpp header must be compiled as C++
#endif

#include <opencv2\opencv.hpp>


/** @brief OpenCV video capture class wrapper.

This class encapsulates basic capture and VideoWriter functionality.
Tested with OpenCV 3.0.
 */
class CV_EXPORTS VideoTest
{
public:
	
	/** @brief constructor

	These are VideoTest constructors.
     */
	VideoTest(void);
	
	/** @overload
	@param device 32-bit value used to initialize video.
    */
	VideoTest(int device);
	
	/** @overload
	@param filename string value used to initialize video 
	       with url/video filename.
    */
	VideoTest(const std::string& filename);
	
	/** @brief VideoTEst destructor
	*/
	virtual ~VideoTest(void);
	
	/** @brief Pauses video.
    */
	CV_WRAP void pause(void);
	
	/** @brief Opens the video stream.
    
	@param filename url to video stream / path to video file.
	*/
	CV_WRAP bool open(const std::string& filename);
	
	/** @brief Opens the video stream.
    
	@param 32-bit int video device index.
	*/
	CV_WRAP bool open(int device);
	
	/** @brief Wraps VideoWriter and creates video recording.
    
	@param filename Name of video file.
	@param ask Ask user to select codec from system codec list. True shows dialog.
	@param 
	@param filename Name of video file.
	*/
	CV_WRAP bool createvideorec(const std::string& filename, bool ask);
	
	/** @overload
    
	@param filename Name of video file.
	@param fps Frames per second.
	@param ask Ask user to select codec from system codec list. True shows dialog.
	*/
	CV_WRAP bool createvideorec(const std::string& filename, int fps, bool ask);
	
	/** @overload
    
	@param filename Name of video file.
	@param fps Frames per second.
	@param ch1 fourcc first character.
	@param ch2 fourcc second character.
	@param ch3 fourcc third character.
	@param ch4 fourcc fourth character.
	@param ask Ask user to select codec from system codec list. True shows dialog.
	*/
	CV_WRAP bool createvideorec(const std::string& filename, int fps, char c1, char c2, char c3, char c4, bool ask);
	
	/** @brief Return underlying Capture class.
	*/
	CV_WRAP cv::VideoCapture Player();
	
	/** @brief Return underlying VideoWriter class.
	*/
	CV_WRAP cv::VideoWriter Recorder();
	
	/** @brief Decodes and returns the grabbed video frame.
    
	The methods/functions decode and return the just grabbed frame. If no frames has been grabbed
    (camera has been disconnected, or there are no more frames in video file), the methods return false
    and the functions return NULL pointer.
    */
	virtual VideoTest& operator >> (cv::Mat& image);
	cv::Mat currentframe();

	/** @brief Writes the next video frame
    
	@param image The written frame
    The functions/methods write the specified image to video file. It must have the same size as has
    been specified when opening the video writer.
     */
	virtual VideoTest& operator << (const cv::Mat& image);
	CV_WRAP void writeframe(const cv::Mat &frame);

	/** @brief todo: .
	*/
	int algorithm1();

protected:
	
	/** @brief convert integer to string.

	@param i integer to convert.
	*/
    static std::string to_string(unsigned int i)
    {
        std::stringstream stream(std::ios::out);
        stream << i;
        return stream.str();
    }

private:
	cv::VideoCapture player;
	cv::VideoWriter writer;
	cv::Mat frame;
};
#endif

