#ifndef OPENCV_H
#define OPENCV_H

#include <opencv2/opencv.hpp>
#include <QImage>
#include <QTimer>
#include <chrono>
#include "yolo.h"

using cv::Mat;
using cv::VideoCapture;
using cv::VideoWriter;

class opencv : public QObject
{
    Q_OBJECT
    VideoCapture cap;
    VideoWriter writer;

    Mat mat;
    Mat result;

    std::unique_ptr<yolo> yolo;
    std::vector<string> tips;//返回widget的标签集合

    QImage matToqimage(Mat&);
public:
    bool do_writer;
    struct{
        int width,height,fps;
    }videoInfo;

    std::unique_ptr<QTimer> qtimer;
    opencv();
    ~opencv();
    void set_video(QString s);
    bool dispose();
    QImage get_result();
    std::vector<QString> get_tips();
};

#endif // OPENCV_H
