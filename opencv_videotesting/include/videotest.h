#ifndef __LITECV_LIB_VIDEOTEST_HPP__
#define __LITECV_LIB_VIDEOTEST_HPP__

#include <opencv2\opencv.hpp>

class CV_EXPORTS VideoTest;
typedef int (VideoTest::*algo_ptr)();


// OpenCV video capture class wrapper with basic capture and VideoWriter functionality. 
// Currently tested under OpenCV 3.0.
class CV_EXPORTS VideoTest
{
public:
	VideoTest(void);
	VideoTest(int device);
	VideoTest(const std::string& filename);
	virtual ~VideoTest(void);
	CV_WRAP void pause(void);
	CV_WRAP bool open(const std::string& filename);
    CV_WRAP bool open(int device);
	CV_WRAP void createvideorec(const std::string& filename);
	CV_WRAP void createvideorec(const std::string& filename, int fps);
	CV_WRAP void createvideorec(const std::string& filename, int fps, char c1, char c2, char c3, char c4);
	CV_WRAP cv::VideoCapture Player();
	CV_WRAP cv::VideoWriter Recorder();
	CV_WRAP void writeframe(const cv::Mat &frame);

	cv::Mat currentframe();
	
	int algorithm1();

protected:
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

