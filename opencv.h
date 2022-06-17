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
    std::vector<string> tips;
    QDialog* dialog;

    QImage matToqimage(Mat&);
public:
    QTimer* qtimer;
    opencv();
    ~opencv();
    bool dispose();
    QImage get_result();
    std::vector<QString> get_tips();
    void set_video(QString& s);
};

#endif // OPENCV_H
