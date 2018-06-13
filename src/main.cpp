#include    <unistd.h>
#include    <iostream>

#include    <opencv2/calib3d.hpp>
#include    <opencv2/highgui.hpp>
#include    <opencv2/imgproc.hpp>

#include    <Settings.hpp>
#include	<CameraCalibration.hpp>

#include	<jsoncpp/json/value.h>
#include	<jsoncpp/json/reader.h>
#include	<jsoncpp/json/writer.h>
#include 	<fstream>

using namespace std;
using namespace cv;

bool        debug = true ;
float		ss = 32.3;
Size 		bsz(9,6);
//const string folderImages = 

int     main(int argc, char **argv)
{	
	if (argc == 1)
    {
        cerr << "Path of input images required." << endl;
        return (EXIT_FAILURE);
    }

	char cwd[256];		
    if (getcwd(cwd, sizeof(cwd)) == NULL)
    {
        cerr << "Could not retrieve current path directory." << endl;
        return (EXIT_FAILURE);
    }

	string pathImages(string(cwd) + "/" + argv[1]); 
	string pathRefImage(pathImages + "refImage/");

	CameraCalibration calibration1(pathImages,pathRefImage);

	calibration1.calibrate(bsz,ss,debug);
	
	int scale =30;
	Mat imgUndist,m1,m2,newCameraMat;
	namedWindow("imgUndist",cv::WINDOW_NORMAL);
	resizeWindow("imgUndist",1000, 800);
    createTrackbar("scale", "imgUndist", &scale, 100);
	while (1) {
		newCameraMat = cv::getOptimalNewCameraMatrix(calibration1.getCameraMatrix(), calibration1.getDistCoeffs(), cv::Size(640, 480), scale / 100.0f, cv::Size(640, 480), 0, true);	
		initUndistortRectifyMap(calibration1.getCameraMatrix(), calibration1.getDistCoeffs(), cv::Mat::eye(3, 3, CV_64F), newCameraMat, cv::Size(640, 480), CV_32FC1, m1, m2);	
		remap(calibration1.getImageRef(), imgUndist, m1, m2, cv::INTER_LINEAR);
		imshow("imgUndist",imgUndist);
		waitKey(1);
	}
/*
    const string inputSettingsFile = argc > 2 ? argv[2] : "settings.json";
	Settings s1(inputSettingsFile);
	Settings s2("settings_old.json");



	Json::Value newJson = s1.getJsonValue();
	Json::Value oldJson = s2.getJsonValue();
	updateJson(newJson,oldJson);



	string encoding = settings.get("encoding","UTF-8").asString();

	cout << settings["camera"]["videoControls"]["deviceID"] << endl;
*/
    return (EXIT_SUCCESS);
}


