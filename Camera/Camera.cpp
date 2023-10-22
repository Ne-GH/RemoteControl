/*******************************************************************************
 * Author : yongheng
 * Data   : 2023/10/22 00:55
*******************************************************************************/

#include "Camera.h"
#include <QCamera>
#include <QDebug>
#include <QCameraFormat>

Camera::Camera(QWidget *parent) {

    camera = new QCamera(QMediaDevices::defaultVideoInput());
    video_widget = new QVideoWidget(parent);
    media_capture_session = new QMediaCaptureSession();
    video_widget->resize(640, 480);
    camera->start();

    media_capture_session->setCamera(camera);
    media_capture_session->setVideoOutput(video_widget);

    auto format = camera->cameraFormat();
    qDebug() << format.resolution();



}




Camera::~Camera() {



    delete camera;
    camera = nullptr;
    delete video_widget;
    video_widget = nullptr;
    delete media_capture_session;
    media_capture_session = nullptr;
}

void Camera::Show() {
    video_widget->show();

}

