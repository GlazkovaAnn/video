#include <opencv2/opencv.hpp>

#ifdef _MSC_VER
# if CV_MAJOR_VERSION == 2 && CV_MINOR_VERSION == 4 && CV_SUBMINOR_VERSION == 3
// OpenCV 2.3.1
#  if defined(_DEBUG)
#  pragma comment(lib, "opencv_core243d.lib")
#  pragma comment(lib, "opencv_highgui243d.lib")
#  pragma comment(lib, "opencv_imgproc243d.lib")
#  pragma comment(lib, "opencv_video243d.lib")
#  pragma comment(lib, "opencv_ml243d.lib")

#  pragma comment(lib, "opencv_calib3d243d.lib")
#  pragma comment(lib, "opencv_objdetect243d.lib")
#  pragma comment(lib, "opencv_features2d243d.lib")
#  pragma comment(lib, "opencv_contrib243d.lib")
#  pragma comment(lib, "opencv_ts243d.lib")
#  pragma comment(lib, "opencv_legacy243d.lib")
#  pragma comment(lib, "opencv_flann243d.lib")
#  pragma comment(lib, "opencv_gpu243d.lib")
# else
#  pragma comment(lib, "opencv_core243.lib")
#  pragma comment(lib, "opencv_highgui243.lib")
#  pragma comment(lib, "opencv_imgproc243.lib")
#  pragma comment(lib, "opencv_video243.lib")
#  pragma comment(lib, "opencv_ml243.lib")

#  pragma comment(lib, "opencv_calib3d243.lib")
#  pragma comment(lib, "opencv_objdetect243.lib")
#  pragma comment(lib, "opencv_features2d243.lib")
#  pragma comment(lib, "opencv_contrib243.lib")
#  pragma comment(lib, "opencv_ts243.lib")
#  pragma comment(lib, "opencv_legacy243.lib")
#  pragma comment(lib, "opencv_flann243.lib")
#  pragma comment(lib, "opencv_gpu243.lib")
# endif //#  if defined(_DEBUG)

# endif //# if CV_MAJOR_VERSION == 2 && CV_MINOR_VERSION == 3
#endif //#ifdef _MSC_VER
IplImage* frame =0;
IplImage* dst =0;
IplImage* dst2 =0;
IplImage* dst3 =0;
IplImage* gray =0;

int main(int argc, char* argv[])
{
        
        char* filename =  "test1.avi";

        printf("[i] file: %s\n", filename);

        // ���� ��� ����������� ��������
        cvNamedWindow("original",CV_WINDOW_AUTOSIZE);
		cvNamedWindow("copy",CV_WINDOW_AUTOSIZE);
		cvNamedWindow("gray",CV_WINDOW_AUTOSIZE);
        // �������� ���������� � �����-�����
        CvCapture* capture = cvCreateFileCapture( filename );
		float n=0.0;   //���� �������� ��������
		
        while(1){
                // �������� ��������� ����
			if(!cvGrabFrame(capture))
				break;
                frame = cvRetrieveFrame( capture ); 
				
                if( !frame ) {
                        break;
                }
				

        	gray = cvCreateImage( cvGetSize(frame), IPL_DEPTH_8U, 1 );
			dst = cvCreateImage( cvGetSize(frame), IPL_DEPTH_8U, 1 );
			dst2 = cvCreateImage( cvGetSize(frame), IPL_DEPTH_8U, 1 );

				        
			cvCvtColor(frame, gray, CV_RGB2GRAY);//����������� � ����� �����

			cvCanny(gray, dst, 10, 100, 3);//�������

			CvPoint2D32f srcTri[3], dstTri[3];
        
			CvMat* rot_mat = cvCreateMat(2, 3, CV_32FC1);
			CvMat* warp_mat = cvCreateMat(2, 3, CV_32FC1);
			dst2 = cvCloneImage(gray);
        
       #if 1

       //��� ���������
        srcTri[0].x = 0;          //������� ����� ����
        srcTri[0].y = 0;
        srcTri[1].x = frame->width - 1;    //������� ������ ����
        srcTri[1].y = 0;
        srcTri[2].x = 0;          //����� ������
        srcTri[2].y = frame->height - 1;
       
		//��� ��������������
        dstTri[0].x = frame->width*0.0;    //������� �����
        dstTri[0].y = frame->height*0.33;
        dstTri[1].x = frame->width*0.85; //������� ������
        dstTri[1].y = frame->height*0.25;
        dstTri[2].x = frame->width*0.15; //����� ������
        dstTri[2].y = frame->height*0.7;
        // �������� ������� ��������������
        cvGetAffineTransform(srcTri,dstTri,warp_mat);
        // ��������� �������������
        cvWarpAffine(gray,dst2,warp_mat);
#endif

        cvCopy(dst2, gray);

#if 1
        //
        // ������� �����������
        //
		n+=5.0;
		
		
        // ������� ������� ��������
        CvPoint2D32f center = cvPoint2D32f(frame->width/2, frame->height/2);
        double angle = n;   // �� n �������� �� ������� �������
        double scale = 0.75;             // �������
        cv2DRotationMatrix(center,angle,scale,rot_mat);

        cvWarpAffine(gray, dst2, rot_mat);  //�������
#endif



        
        CvPoint2D32f srcQuad[4], dstQuad[4];
        
        CvMat* warp_matrix = cvCreateMat(3,3,CV_32FC1);

      
        dst3 = cvCloneImage(dst);

        // ����� �����
        srcQuad[0].x = 0;           //����� �������
        srcQuad[0].y = 0;
        srcQuad[1].x = dst->width - 1;  //������ �������
        srcQuad[1].y = 0;
        srcQuad[2].x = 0;           //����� ������
        srcQuad[2].y = dst->height - 1;
        srcQuad[3].x = dst->width - 1;  //������ ������
        srcQuad[3].y = dst->height - 1;
        //- - - - - - - - - - - - - -//
        dstQuad[0].x = dst->width*0.3;  //����� �������
        dstQuad[0].y = dst->height*0.1;
        dstQuad[1].x = dst->width*0.7;  //������ �������
        dstQuad[1].y = dst->height*0.3;
        dstQuad[2].x = dst->width*0.05;  //����� ������
        dstQuad[2].y = dst->height*0.85;      
        dstQuad[3].x = dst->width*0.8;  //������ ������
        dstQuad[3].y = dst->height*0.7;

        // �������� ������� ��������������
        cvGetPerspectiveTransform(srcQuad,dstQuad,warp_matrix);
        // �������������� �����������
        cvWarpPerspective(dst,dst3,warp_matrix);


					


									
     
         cvShowImage( "original", frame );
		 cvShowImage( "gray", dst2 );
		 cvShowImage( "copy", dst3 );

         char c = cvWaitKey(33);
             if (c == 27) { // ���� ������ ESC - �������
                      break;
             }
				
        }

        // ����������� �������
        cvReleaseCapture( &capture );
        // ������� ����
		

        cvDestroyWindow("original");
		 cvDestroyWindow("copy");
		 cvDestroyWindow("gray");
        return 0;
}