#include    <iostream>

#include    <opencv2/calib3d.hpp>
#include    <opencv2/highgui.hpp>
#include    <opencv2/imgproc.hpp>

#include	<CameraCalibration.hpp>

using namespace cv;
using namespace std;


vector<String> CameraCalibration::getFnImages() {
	return this-> fnImages_;
}

String CameraCalibration::getFnRef() {
	return this-> fnRef_;
}

vector<Mat> CameraCalibration::getImages4calib() {
	return this-> images4calib_;
}

Mat	CameraCalibration::getImageRef(){
	return this-> imageRef_;
}

void CameraCalibration::calibrate (Size bsz, bool debug) {
	this->imagesPts_.clear();
	
	if (debug) {
		cout << "\n<input images> : " << endl;
     	namedWindow("corners",WINDOW_NORMAL);
		namedWindow("no corners",WINDOW_NORMAL);
	} 
	for (size_t k=0; k< this->fnImages_.size(); ++k)
	{
		Mat im = imread(this->fnImages_[k]);
		
		if (im.empty()) {
			cout << "can not read image \"" << this->fnImages_[k] << "\"" << endl;
			continue;
		} 
		if (findChessboardCorners(im, bsz, this-> ptvec_)) {	
			this->images4calib_.push_back(im);
			this->imagesPts_.push_back(this-> ptvec_);
		
			if (debug) {
				cout << "\"" << this->fnImages_[k] << "\"" << endl		
				 << bsz << " chessboard corners found " << endl;
				Mat imConrners;
   	        	im.copyTo(imConrners);
				drawChessboardCorners(imConrners, bsz ,this-> ptvec_ , true);
            	imshow("corners", imConrners);
            	waitKey(0);
			}
		} else {
			cout << "\"" << this->fnImages_[k] << "\"" << endl		
				 << "!!! no chessboard corners found " << endl;
			if (debug) {
				imshow("no corners", im);
            	waitKey(0);
			}
		}		
	}

	this->imageRef_ = imread(fnRef_);
	if (findChessboardCorners(this->imageRef_, bsz, this-> ptvecRef_)) {			
		if (debug) {
			cout << "\n<reference image>: \"" << this->fnRef_ << "\"" << endl		
				 << bsz << " chessboard corners found " << endl;
			Mat imConrners;
        	this->imageRef_.copyTo(imConrners);
			drawChessboardCorners(imConrners, bsz ,this-> ptvecRef_ , true);
			namedWindow("reference image",WINDOW_NORMAL);
			imshow("reference image",imConrners);
			waitKey(0);
		}
	} else {
		cerr << "!!! no chessboard corners found in reference image" << endl;
	}
}

static double computeReprojectionErrors( const vector<vector<Point3f> >& objectPoints,
                                         const vector<vector<Point2f> >& imagePoints,
                                         const vector<Mat>& rvecs, const vector<Mat>& tvecs,
                                         const Mat& cameraMatrix , const Mat& distCoeffs,
                                         vector<float>& perViewErrors, bool fisheye)
{
    vector<Point2f> imagePoints2;
    size_t totalPoints = 0;
    double totalErr = 0, err;
    perViewErrors.resize(objectPoints.size());
    for(size_t i = 0; i < objectPoints.size(); ++i )
    {
        if (fisheye)
        {
            fisheye::projectPoints(objectPoints[i], imagePoints2, rvecs[i], tvecs[i], cameraMatrix,
                                   distCoeffs);
        }
        else
        {
            projectPoints(objectPoints[i], rvecs[i], tvecs[i], cameraMatrix, distCoeffs, imagePoints2);
        }
        err = norm(imagePoints[i], imagePoints2, NORM_L2);
        size_t n = objectPoints[i].size();
        perViewErrors[i] = (float) sqrt(err*err/n);
        totalErr        += err*err;
        totalPoints     += n;
    }
    return sqrt(totalErr/totalPoints);
}


