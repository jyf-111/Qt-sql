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
    cap.release();
    writer.release();
}

QImage opencv::matToqimage(Mat& mat){
    cvtColor(mat, mat, cv::COLOR_BGR2RGB);
        QImage qimage((const unsigned char*)mat.data, mat.cols, mat.rows, mat.step,
                   QImage::Format_RGB888);
        return qimage;
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
    //video info load
    videoInfo.width = cap.get(cv::CAP_PROP_FRAME_WIDTH);
    videoInfo.height = cap.get(cv::CAP_PROP_FRAME_HEIGHT);
    videoInfo.fps= cap.get(cv::CAP_PROP_FPS);

    //get time
    auto now = std::chrono::system_clock::now();
    std::time_t time = std::chrono::system_clock::to_time_t(now);
    auto tm = std::localtime(&time);
    string month = QString::number(tm->tm_mday).toStdString();
    string day = QString::number(tm->tm_mon).toStdString();
    string hour = QString::number(tm->tm_hour).toStdString();
    string minute = QString::number(tm->tm_min).toStdString();
    string second = QString::number(tm->tm_sec).toStdString();

    string filename("Videos/result/");
    filename.append(month)
            .append("_")
            .append(day)
            .append("_")
            .append(hour)
            .append("_")
            .append(minute)
            .append("_")
            .append(second)
            .append("_");
    //get result name
    auto start = s.toStdString().find_last_of('/');
    auto end = s.toStdString().find_last_of('.');
    string name = s.toStdString().substr(start+1,end-start-1);
    filename += name;
    filename += ".avi";
// if opened before then release
    if(writer.isOpened()){
        writer.release();
    }
    if (writer.open(filename,
                    VideoWriter::fourcc('M','J','P','G'),
                    videoInfo.fps,
                    cv::Size(videoInfo.width, videoInfo.height),
                    true))
        qDebug() << "writer init success";
    else
        qDebug() << "writer init fail";
}

bool opencv::dispose()
{
    if (!cap.isOpened())
        return false;
    cap >> mat;
    if (mat.empty())
        return false;
    qDebug() << "frame get and send to yolo";
    int width = mat.cols;
    int height = mat.rows;
    cv::resize(mat, mat, cv::Size(width > 1920 / 2 ? 1920 / 2 : width, height > 1080 / 2 ? 1080 / 2 : width));
    qDebug() << "resize down start detect";
    auto temp = yolo->detect(mat);
    result = temp.first;
    //writer
    if(do_writer){
        Mat temp;
        cv::resize(result,temp,cv::Size(videoInfo.width,videoInfo.height));
        writer << temp;
    }

    tips = temp.second;
    qDebug() << "yolo return result frame";
    return true;
}

QImage opencv::get_result()
{
    if (result.empty())
    {
        qDebug() << "error";
        exit(0);
    }
    else
        return matToqimage(result);
}

std::vector<QString> opencv::get_tips()
{
    std::vector<QString> tmp;
    for (auto &i : tips)
    {
        tmp.push_back(QString::fromStdString(i));
    }
    tips.clear();
    std::vector<string>().swap(tips);
    return tmp;
}
