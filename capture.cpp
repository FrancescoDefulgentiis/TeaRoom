#include "lib.h"

#define MAX_BUFFER_SIZE 10 // Define the maximum number of frames to store in the buffer

int Mic_capture()
{
  /*
  this function capture 1024 bytes from the mic and puts it in a buffer, hopefully, these are goin to be sent before another
  gets fully captured, so we can have a real time communication
  */
  return 0;
}
/*
int Cam_capture(cv::Mat **frame_buffer, int *frame_count)
{
  // Initialize the webcam
  cv::VideoCapture cap(0); // 0 for the system default webcam,

  // Check if the webcam is opened successfully
  if (!cap.isOpened()){
    fprintf(stderr, "Error: Unable to open the webcam.\n");
    return -1;
  }

  // Allocate memory for the frame buffer
  *frame_buffer = (cv::Mat *)malloc(MAX_BUFFER_SIZE * sizeof(cv::Mat));//cv::mat is a matrix of pixels, resolution of the webcam
  if (*frame_buffer == NULL)
  {
    fprintf(stderr, "Error: Memory allocation failed for the frame buffer.\n");
    return -1;
  }

  *frame_count = 0;

  while (*frame_count < MAX_BUFFER_SIZE){
    cv::Mat frame;
    cap >> frame; // Capture a frame from the webcam

    if (frame.empty())
    {
      fprintf(stderr, "Error: Unable to capture a frame from the webcam.\n");
      break;
    }

    // Store the captured frame in the buffer
    (*frame_buffer)[*frame_count] = frame.clone();
    (*frame_count)++;
  }

  // Release the webcam and return
  cap.release();
  return 0;
}

int main()
{
  cv::Mat *frame_buffer;
  int frame_count;

  if (Cam_capture(&frame_buffer, &frame_count) == 0)
  {
    printf("Captured %d frames.\n", frame_count);

    // Process or save frames as needed here

    // Free the frame buffer
    for (int i = 0; i < frame_count; i++)
    {
      frame_buffer[i].release();
    }
    free(frame_buffer);
  }
  else
  {
    printf("Failed to capture frames from the webcam.\n");
  }

  return 0;
}
*/
