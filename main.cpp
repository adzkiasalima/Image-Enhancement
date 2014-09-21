#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdlib.h>
#include "opencv\cv.h"
#include "opencv\highgui.h"

using namespace std;
using namespace cv;

int main(int argc, char *argv[])
{
    //Memasukan Gambar dan mangubah menjadi grayscale
    IplImage* imgAsli = cvLoadImage("SAM_0261.jpg", CV_LOAD_IMAGE_COLOR);
    IplImage* img = cvCreateImage(cvGetSize(imgAsli), IPL_DEPTH_8U, 1);
    cvCvtColor(imgAsli, img, CV_RGB2GRAY);
    cvShowImage("Original", img);

    // Mengambil informasi image
    int height,width,step,channels;
    uchar *data;
    int i,j,k;
    height    = img->height;
    width     = img->width;
    step      = img->widthStep;
    channels  = img->nChannels;
    data      = (uchar *)img->imageData;
    printf("Processing a %dx%d image with %d channels\n",height,width,channels);

    // contrast stretching
    int x, r1=70, r2=140, s1=0, s2=255;
    for(i=0;i<height;i++)
        for(j=0;j<width;j++)
           // for(k=0;k<channels;k++)
           {
                   // data[i*step+j*channels+k]= (data[i*step+j*channels+k])^4;
                   x=data[i*step+j];
                if(0 <= x && x <= r1) x= s1/r1 * x;
                else if(r1 < x && x <= r2)x=((s2 - s1)/(r2 - r1)) * (x - r1) + s1;
                else if(r2 < x && x <= 255) x= ((255 - s2)/(255 - r2)) * (x - r2) + s2;
                data[i*step+j] = x;
       }
    cvShowImage("Contrast Stretching", img );


    //flipping
    cvFlip(imgAsli, 1, 0);
    cvShowImage("Flip", imgAsli );

   /* Mat(const IplImage* img, bool copyData=false);;
    CvScalar s;
    s=cvGet2D(img,i,j);
    cvSet2D(img,i,j,s);
    int space;
    for(i=0;i<height/2;i++)
        for(j=0;j<width;j++){
            space= img[j][i];
            img[j][i]=img[j][height-1-i];
            img[j][height-1-i]=space;
        }

    cvShowImage("Flipping", img );*/

    // thresholding
        int thres=60;
        for(i=0;i<height;i++)
        for(j=0;j<width;j++)
            for(k=0;k<channels;k++){
                if(data[i*step+j*channels+k] <= thres) data[i*step+j*channels+k] = 0;
               else  data[i*step+j*channels+k]= 255;

       }
    cvShowImage("Thresholding", img );
    cvWaitKey(0);
    return 0;

}
