#include <stdio.h>
#include "cv.h"
#include "highgui.h"
//#include "BlobResult.h"
//#include <cxtypes.h>

int main()
{
	CvCapture *capture = 0;
	IplImage  *img = 0;
	IplImage  *gray_img = 0;
	IplImage  *thres_img = 0;
	IplImage  *blobs_img = 0;
	int key = 0;
	CvPoint rect1, rect2;

	CBlobResult blobs;
	CBlob *currentBlob;

	int frame_count= 0;


				img = cvLoadImage("image.jpg",1);
				gray_img  = cvCreateImage( cvGetSize(img), img->depth, 1);
				thres_img = cvCreateImage( cvGetSize(img), img->depth, 1);
				blobs_img = cvCreateImage( cvGetSize(img), img->depth, 3);

		/* Convert image from Color to grayscale and then to binary (thresholded at 200) */
		cvCvtColor(img,gray_img,CV_RGB2GRAY);
		//cvThreshold(gray_img,thres_img,150,255,CV_THRESH_BINARY);
		cvCmpS(gray_img,100,thres_img,CV_CMP_GT);

		/* Find Blobs that are White, Hence 'uchar backgroundColor = 0' (Black) */
		blobs = CBlobResult(thres_img, NULL,0);

		/* Remove blobs if it does not cover minimum area specified below */
		blobs.Filter( blobs, B_EXCLUDE, CBlobGetArea(),B_LESS,500,1000);

		/* Number of blobs */
		int j = blobs.GetNumBlobs();
		printf("Number of blobs %d\n",j);

		/* Color the blobs one after the other */
		for (int i = 0; i < blobs.GetNumBlobs(); i++ )
		{
			currentBlob = blobs.GetBlob(i);
			currentBlob->FillBlob( blobs_img, CV_RGB(255,0,0));

			rect1.x = (int)currentBlob->MinX();
			rect1.y = (int)currentBlob->MinY();

			rect2.x = (int)currentBlob->MaxX();
			rect2.y = (int)currentBlob->MaxY();

// 'frame' is the original IplImage image(3 channels).

			cvRectangle( img, rect1, rect2, CV_RGB(0,255, 0),1, 8, 0 );
		}

		//cvShowImage( "Webcam",gray_img);
		cvShowImage( "Blobs",blobs_img);	
		cvShowImage( "Detect ",img);	

		/* Clear image for next iteration */

		key = cvWaitKey();

	/* Clean up memory */
	//cvDestroyWindow( "Webcam" );
	cvDestroyWindow( "Blobs" );
	
	return 0;
}
