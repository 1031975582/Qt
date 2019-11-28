#include "Window.h"
#include <QQuickItem>
#include <QPushButton>

namespace
{
    QObject* pSwipeView = nullptr;
    QObject* pRedPage = nullptr;
    QObject* pGreenPage = nullptr;
}

Window::Window(QWidget *parent)
    : QQuickWidget(parent)
{
    setWindowTitle(QStringLiteral("Qt����ʹ��Qml����"));
    // ����qml����Դ
    setSource(QUrl("qrc:/App/SwipeViewQml.qml"));
    // qml�����С���游�����С�仯
    setResizeMode(QQuickWidget::SizeRootObjectToView);
    // ���ܴ����¼� �����õĻ�win7������������Ч
    setAttribute(Qt::WA_AcceptTouchEvents);

    // ��ȡQml����redPage����/ / ���ݶ�����objectName���Ҷ���
    pSwipeView = rootObject()->findChild<QObject*>("swipeView");
    pRedPage = rootObject()->findChild<QObject*>("redPage");
    pGreenPage = rootObject()->findChild<QObject*>("greenPage");

    Q_ASSERT(pSwipeView != nullptr && pRedPage != nullptr && pGreenPage != nullptr);

    // ��qml�����ϵ��ź�
    connect(pSwipeView, SIGNAL(signalPageChanged(int)), this, SLOT(onPageChanged(int))); // ҳ���л��¼�
    connect(pRedPage, SIGNAL(signalClicked(const QString&)), this, SLOT(onQmlClicked(const QString&)));//����¼�
    connect(pGreenPage, SIGNAL(signalClicked(const QString&)), this, SLOT(onQmlClicked(const QString&)));//����¼�

    // �ı�qml���������ֵ���ԣ�// ���һ����ť�ı�redPage��ɫ
    m_pChangeColorBtn = new QPushButton(this); 
    m_pChangeColorBtn->setFixedSize(200, 60);
    m_pChangeColorBtn->setStyleSheet("border:1px solid #888888;");
    m_pChangeColorBtn->setText(QStringLiteral("�ı��ǳ��ɫ"));

    connect(m_pChangeColorBtn, &QPushButton::clicked, [&] 
    {
        pRedPage->setProperty("color", "lightblue"); // ֱ����������ֵ
    });

    // ����qml����󷽷�
    m_pQmlMethodBtn = new QPushButton(this); // ����qml���󷽷�
    m_pQmlMethodBtn->setFixedSize(200, 60);
    m_pQmlMethodBtn->move(230, 0);
    m_pQmlMethodBtn->setStyleSheet("border:1px solid #888888;");
    m_pQmlMethodBtn->setText(QStringLiteral("����qml���ڲ������ĳɻ�ɫ"));

    connect(m_pQmlMethodBtn, &QPushButton::clicked, [&]
    {
        QMetaObject::invokeMethod(pRedPage, "setTheColor", Q_ARG(QVariant, "yellow"));
    });
}

/*
 * @func   Window::onQmlClicked 
 * @brief  �յ�����¼�����Ĵ��ڱ���
 * @param  [in]  const QString & strObjectName  qml�źŲ������ݵ��Ƕ�������
 * @return void  
 */ 
void Window::onQmlClicked(const QString& strObjectName)
{
    if (strObjectName == "redPage")
    {
        setWindowTitle(QStringLiteral("�յ�redPage�ĵ���¼�"));
    }
    else if (strObjectName == "greenPage")
    {
        setWindowTitle(QStringLiteral("�յ�greenPage�ĵ���¼�"));
    }
}

/*
 * @func   Window::onPageChanged 
 * @brief  ҳ���л�
 * @param  [in]  int index  swipeViewҳ��index
 * @return void  
 */ 
void Window::onPageChanged(int index)
{
    // ���ڶ�ҳ������QPushButton�ؼ�
    m_pChangeColorBtn->setVisible(0 == index);
    m_pQmlMethodBtn->setVisible(0 == index);
}
