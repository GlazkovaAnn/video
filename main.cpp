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
IplImage* image = 0;
IplImage* dst = 0;
IplImage* dst2 = 0;

int main(int argc, char* argv[])
{
        // имя картинки задаётся первым параметром
        char* filename = argc >= 2 ? argv[1] : "cat.jpg";
        // получаем картинку
        image = cvLoadImage(filename, 1);
        // создаём картинки
        dst = cvCreateImage( cvGetSize(image), IPL_DEPTH_16S, image->nChannels);
        dst2 = cvCreateImage( cvGetSize(image), image->depth, image->nChannels);

        printf("[i] image: %s\n", filename);
        assert( image != 0 );

        // окно для отображения картинки
        cvNamedWindow("original", CV_WINDOW_AUTOSIZE);
        cvNamedWindow("cvLaplace", CV_WINDOW_AUTOSIZE);

        int aperture = argc == 3 ? atoi(argv[2]) : 3;

        // применяем оператор Лапласа
        cvLaplace(image, dst, aperture);

        // преобразуем изображение к 8-битному
        cvConvertScale(dst, dst2);

        // показываем картинку
        cvShowImage("original", image);
        cvShowImage("cvLaplace", dst2);

        cvWaitKey(0);

        // освобождаем ресурсы
        cvReleaseImage(& image);
        cvReleaseImage(&dst);
        cvReleaseImage(&dst2);
        // удаляем окна
        cvDestroyAllWindows();
        return 0;
}
