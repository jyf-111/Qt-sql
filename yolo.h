#ifndef YOLO_H
#define YOLO_H
#define OPENCV
#define GPU

#include <vector>
#include <fstream>
#include <QImage>
#include <QTimer>
#include "yolo_v2_class.hpp"
#include <QDebug>

using std::string;
using std::vector;
using std::ifstream;
using std::shared_ptr;
using std::max;
using cv::Mat;
using cv::Point;
using cv::format;
using cv::Scalar;
using cv::Size;
using cv::putText;

class yolo
{
    const string classesFile = "coco.names";
    const string modelConfig = "yolov4.cfg";
    const string modelWeights = "yolov4.weights";

    Detector detector;
    vector<string> classes;
    vector<string> tips; //返回的标签集合
    //画出检测结果
    void Drawer(cv::Mat& frame, vector<bbox_t>& outs, vector<string>& classes);
    //画出检测框和相关信息
    void DrawBoxes(cv::Mat& frame, vector<string>& classes, int classId, float conf, int left, int top, int right, int bottom);
public:
    yolo();
    ~yolo();
    std::pair<cv::Mat,std::vector<string>> detect(cv::Mat& );
};

#endif // YOLO_H
