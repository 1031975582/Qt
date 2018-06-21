#pragma once

#include <QWidget>
#include <QGraphicsScene>
#include <QLineEdit>
#include "Square.h"
namespace Ui { class MainWindow; };

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = Q_NULLPTR);
    ~MainWindow();

private:
    Ui::MainWindow* ui;

    QGraphicsScene* m_scene;
    Square *m_square;         // We declare the square, which will transmit the callback function
    static QLineEdit *line1;    // We declare a static QLineEdit, which will run the callback function
    static QLineEdit *line2;    // We declare a static QLineEdit, which will run the callback function

private:
    // ����һ���ص�����
    static void getPosition(QPointF point);
};
