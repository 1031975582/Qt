/** @file   Window.h
 *  @brief  Qt������ʹ��Qml
 *  @note
 *  @date   2019/11/28
 */
#pragma once

#include <QQuickWidget>

class QPushButton;

class Window : public QQuickWidget
{
    Q_OBJECT

public:
    Window(QWidget *parent= Q_NULLPTR);

private slots:
void onQmlClicked(const QString& strObjectName);
void onPageChanged(int index);

private:
    QPushButton* m_pChangeColorBtn{ nullptr };
    QPushButton* m_pQmlMethodBtn{ nullptr };
};
