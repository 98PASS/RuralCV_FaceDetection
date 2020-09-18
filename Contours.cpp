#include <opencv2/opencv.hpp>
#include <vector>

using namespace cv;
using namespace std;

Mat src_gray;
int thresh = 100;
RNG rng(12345);

void thresh_callback(int, void*)
{
    Mat binary;
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    threshold(src_gray, binary, thresh, 255, THRESH_BINARY);
    findContours(binary.clone(), contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE);

    Mat drawing = Mat::zeros(binary.size(),CV_8UC3);

    for(int i=0; i<contours.size();++i){
        Scalar color = Scalar(rng.uniform(0,255),rng.uniform(0,255),rng.uniform(0,255));
        drawContours(drawing, contours,i,color);
    }
    imshow("Binary",binary);
    imshow("Contours",drawing);

}

int main() {
    src_gray = imread("imagensTeste/tigre.jpg",0);
    imshow("tigre",src_gray);
    namedWindow("Binary",WINDOW_NORMAL);
    namedWindow("Contours",WINDOW_NORMAL);
    createTrackbar("Limiar","Binary",&thresh,255,thresh_callback);
    thresh_callback(0,0);
    waitKey(0);
    return 0;
}