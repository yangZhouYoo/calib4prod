#include    <iostream>

#include    <opencv2/calib3d.hpp>
#include    <opencv2/highgui.hpp>
#include    <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

static double computeReprojectionErrors( const vector<vector<Point3f> >& objectPoints,
                                         const vector<vector<Point2f> >& imagePoints,
                                         const vector<Mat>& rvecs, const vector<Mat>& tvecs,
                                         const Mat& cameraMatrix , const Mat& distCoeffs,
                                         vector<float>& perViewErrors, bool fisheye);

class   CameraCalibration
{
	public:
		explicit CameraCalibration (const string pathImages, const string pathRefImage) : pathImages_(pathImages), pathRefImage_(pathRefImage) {
					
			vector<String> fnRef;
			glob(pathImages + "*.jpg",fnImages_,false); // read jpg format image, recurse if "true"
			glob(pathRefImage + "*.jpg",fnRef,false);
			fnRef_ = fnRef[0];
		}

		vector<String> 			getFnImages() ;
		String 					getFnRef() ;
		vector<Mat> 			getImages4calib();
		Mat			 			getImageRef();
		
		void 					calibrate(Size bsz,bool debug);

		~CameraCalibration() {
			cout << "calibration finished" << endl;
		}

	private:
		string pathImages_, pathRefImage_;
		vector<String> fnImages_;
		String fnRef_;
		vector<Mat> images4calib_;

		vector<Point2f> ptvec_,ptvecRef_;
		vector<vector<Point2f> > imagesPts_;
		Mat imageRef_;
};






