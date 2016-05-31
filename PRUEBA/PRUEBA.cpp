#include "stdafx.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <iostream>
#include <string>
#include <sstream>

using namespace cv;
using namespace std;

int main(int argc, char* argv[])
{
    char key = 0;
    int contador = 0;
    string fotoFilename = "0";
    Mat frame;
	VideoCapture vcap;
    Mat image;
	CascadeClassifier face_cascade;
	CascadeClassifier eye_cascade;

	String face_cascade_name = "D:/opencv/build/share/OpenCV/haarcascades/haarcascade_frontalface_alt2.xml";
	String eye_cascade_name = "D:/opencv/build/share/OpenCV/haarcascades/haarcascade_eye.xml";

    //face_cascade.load( "D:\opencv\build\share\OpenCV\haarcascades\haarcascade_frontalface_alt2.xml" );
	if (!face_cascade.load(face_cascade_name))
        printf("--(!)Error loading\n");

    const std::string videoStreamAddress = "rtsp://biometria:1234$Bio@10.0.0.150/video.h264"; 

    if(!vcap.open(videoStreamAddress)) {
        std::cout << "Error opening video stream or file" << std::endl;
        return -1;
    }
	
    
	
	cv::namedWindow("Detectar Rostros");
	
    std::vector<Rect> faces;
    std::vector<Rect> eyes;
    
    Mat image_small;
    Mat face;
    Mat processedFace;
	Mat frame_gray;
	Size size(480,480); 
    for(;;) {
        vcap.read(image);
		resize(image,image_small,size);
		
        cvtColor(image_small, frame_gray, CV_BGR2GRAY);
        equalizeHist(frame_gray, frame_gray);
        face_cascade.detectMultiScale(frame_gray, faces, 1.5, 0, 0 | CASCADE_SCALE_IMAGE, Size(100, 100));

		   for (Rect rec : faces)
             {
                    /*rectangle(image_small,
                          Point(rec.x, rec.y),
                          Point(rec.x + rec.width, rec.y + rec.height),
                          CV_RGB(255, 0, 0), 2);*/
					
					eye_cascade.detectMultiScale(frame_gray(rec), eyes, 1.5, 0, 0 | CASCADE_SCALE_IMAGE, Size(200, 200));
					for (Rect rece : eyes)
					{
						rectangle(image_small,
                          Point(rece.x, rece.y),
                          Point(rece.x + rece.width, rece.y + rece.height),
                          CV_RGB(0, 255, 0), 2);
					}
					imshow ( "Recortada" , image_small(rec));
			 }
       /* if (faces.size() > 0){
			rectangle(image_small, faces[0], Scalar(0, 0, 255), 2, 8, 0);
			imshow("Cara", faces);
		}*/
        namedWindow("Detectar Rostros", CV_WINDOW_AUTOSIZE);
        imshow("Detectar Rostros", image_small);
        

        if (waitKey(30) == 27)
            break;
	}
}

