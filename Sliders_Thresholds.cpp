#include <opencv2/opencv.hpp>

using namespace cv;

int value =0;
int type =3;
Mat gray;

void ThresholdDemo(int , void*){
    Mat destino;
    threshold(gray,destino,value,255,type);
    imshow("Threshold",destino);
}

int main(){
    Mat src; //= imread("imagensTeste/tigre.jpg");
    cvtColor(src,gray,CV_BGR2GRAY);
    namedWindow("Threshold",CV_WINDOW_NORMAL);
    createTrackbar("Tipo","Threshold",&type,4, ThresholdDemo);
    createTrackbar("Valor","Threshold",&value,255,ThresholdDemo);
    ThresholdDemo(0,0);

    while(true){
        if(waitKey(1)==27){
            break;
        }
    }
    destroyAllWindows();
    return 0;
}