#include "opencv2/highgui/highgui.hpp"
#include "opencv2/video/tracking.hpp"
#include <Windows.h>
#include <iostream>
/*
 * MY DOCUMENTATION
 KalmanFilter::KalmanFilter(int dynamParams, int measureParams, int controlParams=0, int type=CV_32F)
Parameters:

    dynamParams – Dimensionality of the state.
    measureParams – Dimensionality of the measurement.
    controlParams – Dimensionality of the control vector.
    type – Type of the created matrices that should be CV_32F or CV_64F.

const Mat& KalmanFilter::predict(const Mat& control=Mat())
   - Computes a predicted state
const Mat& KalmanFilter::correct(const Mat& measurement)
  - Updates the predicted state from the measurement.

  -
Mat cv::KalmanFilter::statePost
    corrected state (x(k)): x(k)=x'(k)+K(k)*(z(k)-H*x'(k))

Mat cv::KalmanFilter::statePre
    predicted state (x'(k)): x(k)=A*x(k-1)+B*u(k)

*/

#define drawCross( center, color, d )                                 \
    line( img, Point( center.x - d, center.y - d ), Point( center.x + d, center.y + d ), color, 2, CV_AA, 0); \
    line( img, Point( center.x + d, center.y - d ), Point( center.x - d, center.y + d ), color, 2, CV_AA, 0 )

using namespace cv;
using namespace std;

int main( ) {

    KalmanFilter KF(4, 2, 0);
    POINT mousePos;
    GetCursorPos(&mousePos);

    // intialization of KF...
    KF.transitionMatrix = *(Mat_<float>(4, 4) << 1,0,1,0,   0,1,0,1,  0,0,1,0,  0,0,0,1);
    Mat_<float> measurement(2,1);
    measurement.setTo(Scalar(0));

    //    KF.statePre.at<float>(0) = mousePos.x;
    //    KF.statePre.at<float>(1) = mousePos.y;
    //    KF.statePre.at<float>(2) = 0;
    //    KF.statePre.at<float>(3) = 0;
    setIdentity(KF.measurementMatrix);  // measurement matrix
    setIdentity(KF.processNoiseCov, Scalar::all(1e-4)); // process noise covariance matrix
    setIdentity(KF.measurementNoiseCov, Scalar::all(10)); // measurement noise covariance matrix
    setIdentity(KF.errorCovPost, Scalar::all(.1));
    // Image to show mouse tracking
    Mat img(600, 800, CV_8UC3);
    vector<Point> mousev,kalmanv;
    mousev.clear();
    kalmanv.clear();

    while(1) {
        // First predict, to update the internal statePre variable
        Mat prediction = KF.predict(); // predict korar jonno
        // cout<<prediction.at<float>(0)<<" "<<prediction.at<float>(1)<<endl;
        Point predictPt(prediction.at<float>(0),prediction.at<float>(1));  // predicted point to float point

        // Get mouse point
        GetCursorPos(&mousePos);      // mouse er position
        measurement(0) = mousePos.x;
        measurement(1) = mousePos.y;

        // The update phase
        Mat estimated = KF.correct(measurement);   // Updates the predicted state from the measurement.

        Point statePt(estimated.at<float>(0),estimated.at<float>(1));  // estimated int point to float
        Point measPt(measurement(0),measurement(1));
        // plot points
        imshow("mouse kalman", img);
        img = Scalar::all(0);

        mousev.push_back(measPt);
        kalmanv.push_back(statePt);
        // Drawing cursor Cross and state cross
        drawCross( statePt, Scalar(255,255,255), 3 );
        drawCross( measPt, Scalar(0,0,255), 5 );

        // drawing cursor line and kalman line
        for (int i = 0; i <(int) mousev.size()-1; i++)
            line(img, mousev[i], mousev[i+1], Scalar(255,255,0), 1);

        for (int i = 0; i <(int) kalmanv.size()-1; i++)
            line(img, kalmanv[i], kalmanv[i+1], Scalar(0,155,255), 1);

        waitKey(10);
    }

    return 0;
}
