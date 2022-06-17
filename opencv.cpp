#include "opencv.h"

opencv::opencv():
    cap(0),
    yolo(new class yolo),
    qtimer(new QTimer)
{
    qtimer->setInterval(25);
//    qtimer->start();
}

opencv::~opencv(){
    qtimer->stop();
}

QImage opencv::matToqimage(Mat& mat){
    cvtColor(mat, mat, cv::COLOR_BGR2RGB);
        QImage qimage((const unsigned char*)mat.data, mat.cols, mat.rows, mat.step,
                   QImage::Format_RGB888);
        return qimage;
}

bool opencv::dispose(){
    if(!cap.isOpened()) return false;
    cap >> mat;
    if(mat.empty()) return false;
    cv::resize(mat,mat,cv::Size(1920/2,1080/2));
    auto temp = yolo->detect(mat);
    result = temp.first;
    tips = temp.second;
    return true;
}

QImage opencv::get_result(){
    if(result.empty()){
        qDebug() << "error";
        exit(0);
    }else
        return matToqimage(result);
}

std::vector<QString> opencv::get_tips(){
    std::vector<QString> tmp;
    for(auto &i:tips){
        tmp.push_back(QString::fromStdString(i));
    }
    tips.clear();
    std::vector<string>().swap(tips);
    return tmp;
}

void opencv::set_video(QString& s){
    cap.open(s.toStdString());
}
