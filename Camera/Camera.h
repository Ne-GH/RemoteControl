/*******************************************************************************
 * Author : yongheng
 * Data   : 2023/10/22 00:55
*******************************************************************************/


#pragma once
#include <QScreen>

#include <QCamera>
#include <QMediaDevices>
#include <QMediaCaptureSession>
#include <QMediaRecorder>
#include <QImageCapture>
#include <QVideoWidget>
#include <QVideoSink>

class Camera {
    QCamera *camera = nullptr;
    QVideoWidget *video_widget = nullptr;
    QMediaCaptureSession *media_capture_session = nullptr;
public:

    explicit Camera(QWidget *parent = nullptr);
    void Show();

    ~Camera();
};
