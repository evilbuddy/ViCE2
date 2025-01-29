#include <iostream>
#include <cstring>
#include <chrono>
#include <ctime>
#include <thread>
#include <opencv2/opencv.hpp>

// Get a character depending on the grayscale
const char* getChar(unsigned char grayscale) {
	if (grayscale >= 240)
		return "$";
	else if (grayscale >= 220)
		return "@";
	else if (grayscale >= 200)
		return "B";
	else if (grayscale >= 175)
		return "%";
	else if (grayscale >= 150)
		return "8";
	else if (grayscale >= 125)
		return "o";
	else if (grayscale >= 100)
		return "p";
	else if (grayscale >= 80)
		return "L";
	else if (grayscale >= 55)
		return "{";
	else if (grayscale >= 40)
		return "!";
	else if (grayscale >= 25)
		return "^";
	else if (grayscale >= 10)
		return ".";
	else
		return " ";
}

// Clears the console
void clear() {
#ifdef _WIN32
	// Windows
	std::system("cls");
#else
	// Mac and Linux
	std::system("clear");
#endif
}

// Check if a file exists
bool fileExists (const std::string& name) {
	if(FILE *file = fopen(name.c_str(), "r")) {
		fclose(file);
		return true;
	}
	else {
		return false;
	}   
}

int main(int argc, char* argv[]) {
	// Check the arguments cound
	if (argc < 2 || argc > 5)
	{
		std::cout << "Usage: ViCE <video> (width: 120) (heighht: 45)";
		return -1;
	}

	// Get the video (1st argument)
	std::string video = argv[1];

	// Get the size (2nd and 3rd arguments) if present
	int width = 120;
	int height = 45;
	if(argc > 3) {
		width = std::stoi(argv[2]);
		height = std::stoi(argv[3]);
	}

	// Open the video with OpenCV
	cv::VideoCapture capture(video);
	cv::Mat frame;

	// Initialize variables used for the video processing
	std::chrono::system_clock::time_point lastFrame = std::chrono::system_clock::now();
	std::string screen;
	std::string screenRow;
	cv::Vec3b bgr;
	unsigned char grayscale;

	// Initialize variables used for frame time calculations
	int cframe = 0;
	double cFPS = 0;
	double cFrameTime = 0;
	double frames = capture.get(cv::CAP_PROP_FRAME_COUNT);
	double FPS = capture.get(cv::CAP_PROP_FPS);
	double frameTime = (int)std::round(1 / FPS * 1000);

	// Loop for every frame
	while(capture.read(frame)) {
		cframe++;
		cv::resize(frame, frame, cv::Size(width, height));
		screen = "";
		
		// Loop for every row
		for(int row = 0; row < frame.rows; row++) {
			screenRow = "";

			// Loop for every column
			for(int col = 0; col < frame.cols; col++) {
				// Calculate the grayscale of the current pixel (col x row)
				bgr = frame.at<cv::Vec3b>(row, col);
				grayscale = (bgr[2] * 0.21) + (bgr[1] * 0.72) + (bgr[0] * 0.07);

				// Add the pixel's char to the row's string
				screenRow += getChar(grayscale);
			}

			// Add the row's string to the frame's string
			screen += screenRow + "\n";
		}

		// Wait if the player is going too fast
		cFrameTime = (std::chrono::system_clock::now() - lastFrame).count() / 100000;
		cFPS = 1 / (cFrameTime / 1000);
		if(cFrameTime < frameTime) {
			std::this_thread::sleep_for(std::chrono::milliseconds((int)((frameTime - cFrameTime) * FPS)));
		}
		lastFrame = std::chrono::system_clock::now();

		// Clear the console and draw the frame with additional info
		clear();
		std::cout << screen;
		std::cout << cframe << "/" << frames << " @ " << cFPS << " (" << cFrameTime << "ms) / " << FPS << " (" << frameTime << "ms) FPS" << "\n";
	}

	// Releases the OpenCV video and exists
	capture.release();
	return 0;
}
