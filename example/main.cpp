#include <opencv2/opencv.hpp>
#include <chrono>

#include "../VirtualDeviceWriter.hpp"

constexpr int DEVICE_ID_IN = 1;
constexpr int WIDTH = 640;
constexpr int HEIGHT = 480;

constexpr int DEVICE_ID_OUT = 34;

int main (int argc, char* argv[])
{
  //cv::VideoCapture cap (DEVICE_ID_IN, cv::CAP_V4L);
  cv::VideoCapture cap (DEVICE_ID_IN);
  cap.set (cv::CAP_PROP_FRAME_WIDTH, WIDTH);
  cap.set (cv::CAP_PROP_FRAME_HEIGHT, HEIGHT);

  if (!cap.isOpened ()) {
    std::cout << "ERROR: input device was not opened" << std::endl;
    return -1;
  }

  cv::Mat frame;
//  EventFrequency freq;
  VirtualDeviceWriter pub (DEVICE_ID_OUT, WIDTH, HEIGHT);

  while (cap.read (frame))
  {
    //freq.event ();
    //std::cout << freq.time () << std::endl;

    cv::imshow ("Web Camera", frame);

    cv::Mat processed = frame;

    //cv::cvtColor (frame, processed, CV_8S);
    //pub.write (frame);
    pub.write (processed);

    const int key = cv::waitKey (1);
    if (key == 'q') {
      break;
    } else if (key == 's') {
      cv::imwrite ("img.image", frame);
    }
  }
  cv::destroyAllWindows ();
  return 0;
}
