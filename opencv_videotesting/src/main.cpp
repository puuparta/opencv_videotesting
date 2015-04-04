#include "videotest.h"
#include "filters.h"


int main() {
	
	// basic video recording test with default fps:20 and DIVX3 codec.
	// Press ESC to end recording.
	VideoTest video(0);
	bool supported = video.createvideorec("output.avi",10, true);
	if(!supported)
	{
		std::cout<<"The codec selected is not supported."<<std::endl;
		getchar();
		return -1;
	}
	
	// to resizable windows:
	//cv::namedWindow("original",cv::WINDOW_NORMAL);
	//cv::namedWindow("filtered",cv::WINDOW_NORMAL);
	
	cv::Mat frame;
	cv::Mat filtered;

	while(true)
	{
		video >> frame;
		filtered = filters::binaryFilterRedChannel(frame);
		cv::imshow("original",frame);
		cv::imshow("filtered",filtered);
		video << filtered;

		switch(cv::waitKey(33)) {
		case 27:
			return 0;
		}
	}
}