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

bool        debug = false ;
//const string folderImages = 

int     main(int argc, char **argv)
{	
    const string inputSettingsFile = argc > 2 ? argv[2] : "settings.json";
	Settings s1(inputSettingsFile);
	Settings s2("settings_old.json");

//calibrationMatrixValues or calibrateCamera


	Json::Value newJson = s1.getJsonValue();
	Json::Value oldJson = s2.getJsonValue();
	updateJson(newJson,oldJson);


	char cwd[256];		
    if (getcwd(cwd, sizeof(cwd)) == NULL)
    {
        cerr << "Could not retrieve current path directory." << endl;
        return (EXIT_FAILURE);
    }

	string pathImages(string(cwd) + "/" + argv[1]); 
	string pathRefImage(pathImages + "refImage/");

	vector<String> fnImages, fnRef;
	vector<Mat> images4calib;

	glob(pathImages + "*.jpg",fnImages,false); // read jpg format image, recurse if "true"
	glob(pathRefImage + "*.jpg",fnRef,false);
	Mat refImage = imread(fnRef[0]);
	for (size_t k=0; k<fnImages.size(); ++k)
	{
		cout << fnImages[k] << endl;
		Mat im = imread(fnImages[k]);
		if (im.empty()) continue; 
		images4calib.push_back(im);
	}
	cout << refImage.size() << endl;

	imshow("test",refImage);
	waitKey(0); 
	
/*
	cout << newJson << endl;
	string encoding = settings.get("encoding","UTF-8").asString();
	cout << encoding << endl;
	cout << settings["camera"]["videoControls"]["deviceID"] << endl;
*/
    return (EXIT_SUCCESS);
}


