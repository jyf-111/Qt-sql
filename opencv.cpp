#include "opencv.h"

opencv::opencv():
    cap(),
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
    qDebug() << "frame get and send to yolo";
    int width = mat.cols;
    int height = mat.rows;
    qDebug() << "width" << width;
    qDebug() << "height" << height;
    cv::resize(mat,mat,cv::Size(width>1920/2?1920/2:width,height>1080/2?1080/2:width));
    qDebug() << "resize down start detect";
    auto temp = yolo->detect(mat);
    result = temp.first;
    tips = temp.second;
    qDebug() << "yolo return result frame";
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

void opencv::set_video(QString s){
    try{
        if(s=="0")
            cap.open(0);
        else
            cap.open(s.toStdString());
    }catch(cv::Exception &e){
        qDebug() << e.what();
    }
    videoInfo.width = cap.get(cv::CAP_PROP_FRAME_WIDTH);
    videoInfo.height = cap.get(cv::CAP_PROP_FRAME_HEIGHT);
    videoInfo.frame = cap.get(cv::CAP_PROP_FRAME_COUNT);
}
