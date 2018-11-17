/**
 * OpenCV SimpleBlobDetector Example
 *
 * Copyright 2015 by Satya Mallick <spmallick@gmail.com>
 *
 */

#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

int main( int argc, char** argv )
{

	// Read image
	Mat im = imread( "3.jpg", IMREAD_GRAYSCALE );
	// Mat im = imread( "3.jpg", CV_LOAD_IMAGE_COLOR );

	threshold(im, im, 200, 255, THRESH_BINARY_INV);

	// Setup SimpleBlobDetector parameters.
	SimpleBlobDetector::Params params;

	// Change thresholds
	params.minThreshold = 0;
	params.maxThreshold = 255;

	// Filter by Area.
	params.filterByArea = true;
	params.minArea = 100;

	// Filter by Circularity
	params.filterByCircularity = true;
	params.minCircularity = 0.5;

	// Filter by Convexity
	params.filterByConvexity = true;
	params.minConvexity = 0.9;

	// Filter by Inertia
	params.filterByInertia = true;
	params.minInertiaRatio = 0.01;


	// Storage for blobs
	vector<KeyPoint> keypoints;


#if CV_MAJOR_VERSION < 3   // If you are using OpenCV 2

	// Set up detector with params
	SimpleBlobDetector detector(params);

	// Detect blobs
	detector.detect( im, keypoints);
#else 

	// Set up detector with params
	Ptr<SimpleBlobDetector> detector = SimpleBlobDetector::create(params);   

	// Detect blobs
	detector->detect( im, keypoints);
#endif 

	// Draw detected blobs as red circles.
	// DrawMatchesFlags::DRAW_RICH_KEYPOINTS flag ensures
	// the size of the circle corresponds to the size of blob

	Mat im_with_keypoints;
	drawKeypoints( im, keypoints, im_with_keypoints, Scalar(0,0,255), DrawMatchesFlags::DRAW_RICH_KEYPOINTS );

	// Show blobs
	namedWindow("Display window", WINDOW_NORMAL);
	imshow("Display window", im_with_keypoints );
	waitKey(0);

}