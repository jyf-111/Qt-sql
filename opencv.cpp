#include "opencv.h"

opencv::opencv():
    cap("DCS.flv"),
    yolo(new class yolo),
    qtimer(new QTimer)
{
    qtimer->setInterval(30);
    qtimer->start();
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

void opencv::dispose(){
    cap >> mat;
    cv::resize(mat,mat,cv::Size(1920/2,1080/2));
    result = yolo->detect(mat);
}

QImage opencv::get_result(){
    if(result.empty()){
        qDebug() << "error";
        exit(0);
    }else
    return matToqimage(result);
}
