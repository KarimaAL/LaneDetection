#include <opencv2/opencv.hpp>
#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>


using namespace cv;
using namespace std;

int main(int argc, char* argv[])
{
    cv::VideoCapture cap("C:/Users/nassim/Music/edge-and-circle-detection/Lane detect test data.mp4");
    // if not success, exit program
    if (cap.isOpened() == false)
    {
        cout << "Cannot open the video file" << endl;
        cin.get(); //wait for any key press
        return -1;
    }
   

    //get the frames rate of the video
    double fps = cap.get(CAP_PROP_FPS);
    cout << "Frames per seconds : " << fps << endl;

    String window_name = "My First Video";



    namedWindow(window_name, WINDOW_NORMAL); //create a window
    
    while (true)
    {
        Mat frame;
        bool bSuccess = cap.read(frame); // read a new frame from video 

        //Breaking the while loop at the end of the video
        if (bSuccess == false)
        {
            cout << "Found the end of the video" << endl;
            break;
        }

        //show the frame in the created window
        imshow(window_name, frame);

        //wait for for 10 ms until any key is pressed.  
        //If the 'Esc' key is pressed, break the while loop.
        //If the any other key is pressed, continue the loop 
        //If any key is not pressed withing 10 ms, continue the loop
        if (waitKey(10) == 27)
        {
            cout << "Esc key is pressed by user. Stoppig the video" << endl;
            break;
        }
    


        Mat canny;
        Mat mb;
        Mat gb;
        Mat greyMat;
        cap >> frame; // get a new frame from camera
      // cvtColor(frame, gray, COLOR_BGR2GRAY);

        
        cvtColor(frame, greyMat, COLOR_BGR2GRAY);

          // medianBlur(greyMat, mb, 5);
        GaussianBlur(greyMat, greyMat, Size(7, 7), 1.5, 1.5);

        Canny(greyMat, canny, 0, 30, 3);

        /*namedWindow("Gaussian blur demo", WINDOW_NORMAL);
        imshow("Gaussian blur demo", greyMat);*/

        namedWindow("Canny demo", WINDOW_NORMAL);
        imshow("Canny demo", canny);

         cv::Mat output;
         Mat mask = cv::Mat::zeros(canny.size(), canny.type());
         Point pts[4] = {
         cv::Point(867, 487),
         cv::Point(273, 487),
         cv::Point(11, 667),
         cv::Point(1052, 667) };

  // Create a binary polygon mask
  cv::fillConvexPoly(mask, pts, 4, cv::Scalar(255, 0, 0));
  // Multiply the edges image and the mask to get the output
  cv::bitwise_and(canny, mask, output);

  namedWindow("ROI demo", WINDOW_NORMAL);
  imshow("ROI demo", output);



    }



    return 0;


}