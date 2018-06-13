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
//calibrationMatrixValues or calibrateCamera
	calibration1.calibrate(bsz,debug);



    const string inputSettingsFile = argc > 2 ? argv[2] : "settings.json";
	Settings s1(inputSettingsFile);
	Settings s2("settings_old.json");



	Json::Value newJson = s1.getJsonValue();
	Json::Value oldJson = s2.getJsonValue();
	updateJson(newJson,oldJson);


	
/*
	cout << newJson << endl;
	string encoding = settings.get("encoding","UTF-8").asString();
	cout << encoding << endl;
	cout << settings["camera"]["videoControls"]["deviceID"] << endl;
*/
    return (EXIT_SUCCESS);
}


