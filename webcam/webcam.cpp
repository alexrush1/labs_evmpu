#define _CRT_SECURE_NO_WARNINGS

#include <opencv2/opencv.hpp>
#include <iostream>
#include <fstream>
#include <opencv2/highgui/highgui.hpp>


void wcstream(cv::VideoCapture cap) {
	cv::UMat bgr_frame;
	for (;;)
	{
		cap >> bgr_frame;
		if (bgr_frame.empty()) break;

		cv::imshow("webcam stream", bgr_frame);

		double fps = cap.get(cv::CAP_PROP_FPS);
		std::cout << "\b" << "\b" << "\b" << "\b" << "\b" << "\b" << "\b";
		std::cout << "FPS: " << fps;

		if (cv::waitKey(30) == 27)
		{
			std::cout << "esc key is pressed by user" << std::endl;
			break;
		}
	}
}


void shakal(cv::VideoCapture cap) {
	cv::UMat bgr_frame, wc_erode;
	for (;;)
	{
		cap >> bgr_frame;
		if (bgr_frame.empty()) break;

		cv::imshow("webcam stream", bgr_frame);

		cv::dilate(bgr_frame, wc_erode, cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(7, 7)));
		cv::erode(bgr_frame, wc_erode, cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(7, 7)));
		cv::imshow("erode", wc_erode);


		double fps = cap.get(cv::CAP_PROP_FPS);
		std::cout << "\b" << "\b" << "\b" << "\b" << "\b" << "\b" << "\b";
		std::cout << "FPS: " << fps;

		if (cv::waitKey(30) == 27)
		{
			std::cout << "esc key is pressed by user" << std::endl;
			break;
		}
	}
}


void cannyfil(cv::VideoCapture cap) {
	cv::UMat bgr_frame, nulled, gray;
	for (;;)
	{
		cap >> bgr_frame;
		if (bgr_frame.empty()) break;

		cv::imshow("webcam stream", bgr_frame);

		cv::cvtColor(bgr_frame, gray, cv::COLOR_BGR2GRAY);
		cv::dilate(gray, gray, cv::Mat());
		cv::Canny(gray, nulled, 10, 100, 3, true);
		cv::imshow("canny", nulled);

		double fps = cap.get(cv::CAP_PROP_FPS);
		std::cout << "\b" << "\b" << "\b" << "\b" << "\b" << "\b" << "\b";
		std::cout << "FPS: " << fps;

		if (cv::waitKey(30) == 27)
		{
			std::cout << "esc key is pressed by user" << std::endl;
			break;
		}
	}
}


void wcstream_start(int mode) {
	cv::VideoCapture cap;
	cap.open(0);
	freopen(".log", "w", stderr);
	if (!cap.isOpened())
	{
		std::cerr << "Couldn't open capture." << std::endl;
		exit(0);
	}

	cv::UMat bgr_frame;
	std::cout << std::endl;
	switch (mode) {
	case 1:
		wcstream(cap);
	case 2:
		shakal(cap);
	case 3:
		cannyfil(cap);
	}
	cap.release();
}

int main() {
	std::cout << "WebCam stream viewer + filters v0.0.1(alpha) by Ivan T." << std::endl << std::endl;
	std::cout << "Menu:" << std::endl << "1.Only raw stream from webcam" << std::endl << "2.'Shakal' mode" << std::endl << "3.Canny mode" << std::endl << "0.Exit" << std::endl << std::endl;
	std::cout << "Please, choose a program mode: ";
	int mode;
	std::cin >> mode;
	wcstream_start(mode);
	if (mode == 0)
		exit(0);
	return 0;
}
