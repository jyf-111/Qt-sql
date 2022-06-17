#include "yolo.h"
#include <iostream>

yolo::yolo() :
    detector(modelConfig, modelWeights, 0)
{
    ifstream ifs(classesFile.c_str());
    string line;
    while (getline(ifs, line)) classes.push_back(line);
}

yolo::~yolo(){}

void yolo::DrawBoxes(Mat& frame, vector<string>& classes, int classId, float conf, int left, int top, int right, int bottom){
    //画检测框
    rectangle(frame, Point(left, top), Point(right, bottom), Scalar(255, 178, 50), 3);
    //该检测框对应的类别和置信度
    string label = format("%.2f", conf);
    if (!classes.empty())
    {
        CV_Assert(classId < (int)classes.size());
        label = classes[classId] + ":" + label;
        tips.push_back(classes[classId]);
    }
    //将标签显示在检测框顶部
    int baseLine;
    Size labelSize = getTextSize(label, cv::FONT_HERSHEY_SIMPLEX, 0.5, 1, &baseLine);
    top = max(top, labelSize.height);
    rectangle(frame, Point(left, top - round(1.5 * labelSize.height)), Point(left + round(1.5 * labelSize.width), top + baseLine), Scalar(255, 255, 255), cv::FILLED);
    putText(frame, label, Point(left, top), cv::FONT_HERSHEY_SIMPLEX, 0.75, Scalar(0, 0, 0), 1);
}

void yolo::Drawer(Mat& frame, vector<bbox_t>& outs, vector<string>& classes){
    //获取所有最佳检测框信息
    for (int i = 0; i < outs.size(); i++)
    {
        DrawBoxes(frame, classes, outs[i].obj_id, outs[i].prob, outs[i].x, outs[i].y,
                  outs[i].x + outs[i].w, outs[i].y + outs[i].h);
    }
}

std::pair<Mat,std::vector<string>> yolo::detect(Mat& frame){
        //Mat图像转为yolo输入格式
        if (frame.empty()) {
            std::cout << "empty picture" << std::endl;
            exit(0);
        }

        shared_ptr<image_t> detImg = detector.mat_to_image_resize(frame);
        //前向预测
        vector<bbox_t> outs = detector.detect_resized(*detImg, frame.cols, frame.rows, 0.25);

        //画图
        Drawer(frame, outs, classes);
        auto tmp = tips;
        tips.clear();
        std::vector<string>().swap(tips);
        return std::make_pair(frame,tmp);
}
