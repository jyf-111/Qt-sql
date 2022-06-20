#ifndef OPENCV_H
#define OPENCV_H

#include <opencv2/opencv.hpp>
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

    std::unique_ptr<yolo> yolo;
    std::vector<string> tips;//返回widget的标签集合

    QImage matToqimage(Mat&);
public:
    struct{
        int width,height,frame;
    }videoInfo;
    std::unique_ptr<QTimer> qtimer;
    opencv();
    ~opencv();
    bool dispose();
    QImage get_result();
    std::vector<QString> get_tips();
    void set_video(QString s);
};

#endif // OPENCV_H
