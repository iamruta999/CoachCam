#include<iostream>
#include"opencv2/highgui/highgui.hpp"
#include"opencv2/imgproc/imgproc.hpp"
#include<iostream>
#include"opencv2/highgui/highgui.hpp"
#include"opencv2/imgproc/imgproc.hpp"
#include"opencv2/core/core.hpp"

using namespace std;
using namespace cv;

//Initialize threshold level and mask size
const static int THRESHOLD = 18;
const static int MASK = 37;
//Initialize the player positions
int player_1[2] = {0,0};
int player_2[2] = {0,0};
int player_3[2] = {0,0};
int player_4[2] = {0,0};
//bounding rectangle of the object i.e. player
Rect boundingRectangle_1 = Rect(0,0,0,0);
Rect boundingRectangle_2 = Rect(0,0,0,0);
Rect boundingRectangle_3 = Rect(0,0,0,0);
Rect boundingRectangle_4 = Rect(0,0,0,0);

//int to string function
string intToString(int number)
{
    //this function has a number input and string output
    std::stringstream ss;
    ss << number;
    return ss.str();
}

void searchForMovement(Mat thresholdImage, Mat &cameraFeed)
{
    bool objectDetected=false;
    Mat temp;
    thresholdImage.copyTo(temp);
    //vectors for output of findContours
    vector< vector<Point> > contours;
    vector<Vec4i> hierarchy;
    //find contours of filtered image using openCV findContours function
    findContours(temp,contours,hierarchy,CV_RETR_EXTERNAL,CV_CHAIN_APPROX_SIMPLE );
    
    //if contours vector is not empty, we have found some objects
    if(contours.size()>0)objectDetected=true;
    else objectDetected = false;
    if(objectDetected)
    {   // retain the largest and the second largest contours
        int largest = contours.size()-1;
        boundingRectangle_1 = boundingRect(contours[largest]);
        int xpos = boundingRectangle_1.x+boundingRectangle_1.width/2;
        int ypos = boundingRectangle_1.y+boundingRectangle_1.height/2;
        //update the objects positions
        player_1[0] = xpos , player_1[1] = ypos;
        
        int second = contours.size()-2;
        if (second > 0) //check if the second player is present
        {
            boundingRectangle_2 = boundingRect(contours[second]);
            int xpos2 = boundingRectangle_2.x+boundingRectangle_2.width/2;
            int ypos2 = boundingRectangle_2.y+boundingRectangle_2.height/2;
            player_2[0] = xpos2 , player_2[1] = ypos2;
        }
        
        int third = contours.size()-3;
        if (third > 0) //check if the third player is present
        {
            boundingRectangle_3 = boundingRect(contours[third]);
            int xpos3 = boundingRectangle_3.x+boundingRectangle_3.width/2;
            int ypos3 = boundingRectangle_3.y+boundingRectangle_3.height/2;
            player_3[0] = xpos3 , player_3[1] = ypos3;
        }
        
        int fourth = contours.size()-4;
        if (fourth > 0) //check if the fourth player is present
        {
            boundingRectangle_4 = boundingRect(contours[fourth]);
            int xpos4 = boundingRectangle_4.x+boundingRectangle_4.width/2;
            int ypos4 = boundingRectangle_4.y+boundingRectangle_4.height/2;
            player_4[0] = xpos4 , player_4[1] = ypos4;
        }
        
    }
    int x = player_1[0];
    int y = player_1[1];
    
    int x2 = player_2[0];
    int y2 = player_2[1];
    
    int x3 = player_3[0];
    int y3 = player_3[1];
    
    int x4 = player_4[0];
    int y4 = player_4[1];
    
    //display a rectangle with cross hair around object 1
    rectangle(cameraFeed, boundingRectangle_1, Scalar(255,0,0),1,8,0);
    line(cameraFeed,Point(x,y),Point(x,y-5),Scalar(0,255,0),1);
    line(cameraFeed,Point(x,y),Point(x,y+5),Scalar(0,255,0),1);
    line(cameraFeed,Point(x,y),Point(x-5,y),Scalar(0,255,0),1);
    line(cameraFeed,Point(x,y),Point(x+5,y),Scalar(0,255,0),1);
    putText(cameraFeed,"Tracking player 1 at (" + intToString(x)+","+intToString(y)+")",Point(40,15),1,1,Scalar(0,0,255),2);
    
    //display a rectangle with cross hair around object 2
    rectangle(cameraFeed, boundingRectangle_2, Scalar(255,0,0),1,8,0);
    line(cameraFeed,Point(x2,y2),Point(x2,y2-5),Scalar(0,255,0),1);
    line(cameraFeed,Point(x2,y2),Point(x2,y2+5),Scalar(0,255,0),1);
    line(cameraFeed,Point(x2,y2),Point(x2-5,y2),Scalar(0,255,0),1);
    line(cameraFeed,Point(x2,y2),Point(x2+5,y2),Scalar(0,255,0),1);
    putText(cameraFeed,"Tracking player 2 at (" + intToString(x2)+","+intToString(y2)+")",Point(40,40),1,1,Scalar(0,0,255),2);
    
    //display a rectangle with cross hair around object 2
    rectangle(cameraFeed, boundingRectangle_3, Scalar(255,0,0),1,8,0);
    line(cameraFeed,Point(x3,y3),Point(x3,y3-5),Scalar(0,255,0),1);
    line(cameraFeed,Point(x3,y3),Point(x3,y3+5),Scalar(0,255,0),1);
    line(cameraFeed,Point(x3,y3),Point(x3-5,y3),Scalar(0,255,0),1);
    line(cameraFeed,Point(x3,y3),Point(x3+5,y3),Scalar(0,255,0),1);
    putText(cameraFeed,"Tracking player 3 at (" + intToString(x3)+","+intToString(y3)+")",Point(350,15),1,1,Scalar(0,0,255),2);
    
    //display a rectangle with cross hair around object 2
    rectangle(cameraFeed, boundingRectangle_4, Scalar(255,0,0),1,8,0);
    line(cameraFeed,Point(x4,y4),Point(x4,y4-5),Scalar(0,255,0),1);
    line(cameraFeed,Point(x4,y4),Point(x4,y4+5),Scalar(0,255,0),1);
    line(cameraFeed,Point(x4,y4),Point(x4-5,y4),Scalar(0,255,0),1);
    line(cameraFeed,Point(x4,y4),Point(x4+5,y4),Scalar(0,255,0),1);
    putText(cameraFeed,"Tracking player 4 at (" + intToString(x4)+","+intToString(y4)+")",Point(350,40),1,1,Scalar(0,0,255),2);
    
}
int main()
{
    bool trackingEnabled = true;
    //Initialize matrices to hold the 2 current frames
    Mat frame1,frame2;
    //Initialize matrices to hold their grayscale images
    Mat grayImage1,grayImage2;
    //Initialize matrix to hold resulting difference image
    Mat differenceImage;
    //Initialize matrix to hold thresholded difference image
    Mat thresholdImage;
    //video capture object.
    VideoCapture capture;
    while(1)
    {
        capture.open("v4.mp4");
        if(!capture.isOpened()){
            cout<<"ERROR ACQUIRING VIDEO FEED\n";
            getchar();
            return -1;
        }
        //check if the video has reach its last frame.
        //we add '-1' because we are reading two frames from the video at a time.
        while(capture.get(CV_CAP_PROP_POS_FRAMES)<capture.get(CV_CAP_PROP_FRAME_COUNT)-1)
        {
            //read first frame
            capture.read(frame1);
            //convert frame1 to gray scale for frame differencing
            cv::cvtColor(frame1, grayImage1, COLOR_BGR2GRAY);
            //copy second frame
            capture.read(frame2);
            //convert frame2 to gray scale for frame differencing
            cv::cvtColor(frame2, grayImage2, COLOR_BGR2GRAY);
            //perform frame differencing with the sequential images which will output an intensity image
            differenceImage = abs(grayImage1 - grayImage2);
            //threshold intensity image at a given threshold value
            cv::threshold(differenceImage, thresholdImage, THRESHOLD, 255, THRESH_BINARY);
            //use blur() to smooth the image and remove noise
            cv::blur(thresholdImage, thresholdImage, cv::Size(MASK,MASK));
            //threshold again to obtain binary image from blur output
            cv::threshold(thresholdImage, thresholdImage, THRESHOLD, 255, THRESH_BINARY);
            //if tracking enabled, search for contours in our thresholded image
            if(trackingEnabled)
            {
                searchForMovement(thresholdImage, frame1);
            }
            //show the captured frame
            imshow("Frame1",frame1);
            //the 10ms delay is necessary for proper operation of this program
            switch(waitKey(10))
            {
                case 27: //'esc' key has been pressed, exit program.
                    return 0;
                case 116: //'t' has been pressed. this will toggle tracking
                    trackingEnabled = !trackingEnabled;
                    if(trackingEnabled == false) cout<<"Tracking disabled."<<endl;
                    else cout<<"Tracking enabled."<<endl;
                    break;
            }
        }
        //release the capture before re-opening and looping again.
        capture.release();
    }
    return 0;
}

