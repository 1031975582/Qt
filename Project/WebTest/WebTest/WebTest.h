/** @file   WebTest.h
  * @note   HangZhou Hikvision Digital Technology Co., Ltd. All Right Reserved.
  * 
  * @brief  Qt ʹ��web���濪��Demo
  * @author yulei10
  * @date   2018/11/30
  */
#pragma once

#include <QtWidgets/QWidget>
#include <QWebEngineView>
#include <QWebChannel>
#include "ui_WebTest.h"

class WebTest : public QWidget
{
    Q_OBJECT

public:
    WebTest(QWidget *parent = Q_NULLPTR);

signals:
    // JS���н���
    void signalRunJsOver();

private:
    void initUi();
    void initConncetion();
    // ����html�ļ�
    void loadHtml();
    // ��ȡjs��������ֵ
    QString getJsRetString();

public slots:
    void recieveJsMessage(const QString& jsMsg);

private:
    Ui::WebTestClass ui;

    QWebEngineView *m_pWebView{ nullptr };
    QWebChannel* m_pWebChannel{ nullptr };
};
