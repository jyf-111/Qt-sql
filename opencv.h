#ifndef OPENCV_H
#define OPENCV_H

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <QImage>
#include <QTimer>
#include "yolo.h"

using cv::Mat;
using cv::VideoCapture;

class opencv : public QObject
{
    Q_OBJECT
    VideoCapture cap;
    Mat mat;
    Mat result;
    yolo* yolo;
    QImage matToqimage(Mat&);
public:
    QTimer* qtimer;
    opencv();
    ~opencv();
    void dispose();
    QImage get_result();
};

#endif // OPENCV_H
