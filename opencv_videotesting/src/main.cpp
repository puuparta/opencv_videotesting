#include "videotest.h"


int main() {
	
	// basic video recording test with default fps:20 and DIVX3 codec.
	// Press ESC to end recording.
	VideoTest video(0);
	video.createvideorec("output.avi");
	
	cv::namedWindow("window",cv::WINDOW_AUTOSIZE);
	cv::Mat frame;
	while(1)
	{
		frame = video.currentframe();
		cv::imshow("window",frame);
		video.writeframe(frame);
		
		switch(cv::waitKey(33)) {
		case 27:
			return 0;
		}
	}
}