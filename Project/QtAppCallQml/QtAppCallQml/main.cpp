#include <QQuickWidget>
#include <QQuickItem>
#include <QWidget>
#include <QPushButton>
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QQuickWidget w;
    w.setSource(QUrl(QStringLiteral("qrc:/QtAppCallQml/Resources/main.qml")));
    w.setResizeMode(QQuickWidget::SizeRootObjectToView);
    w.show();

    QPushButton btn(&w);
    btn.setText("Change Page 1 Color to lightblue");
    btn.show();
    auto swipeView = w.rootObject()->findChild<QObject*>("swipeViewObj");

    if (swipeView != nullptr)
    {
        auto page1 = swipeView->findChild<QObject*>("page1Obj"); // �����ť����page1����ɫlightblue
        if (page1 != nullptr)
        {
            QObject::connect(&btn, &QPushButton::clicked, [&]
            {
                QMetaObject::invokeMethod(page1, "setColor", Q_ARG(QVariant, "lightblue"));
                // ���� 			page1->setProperty("color", "lightblue");
            });
        }

        // qml��swipeViewҳ���л�ʱ�������ʾ
        QObject::connect(swipeView, SIGNAL(currentIndexChanged()), &w, SLOT(showMaximized()));
    }


    return a.exec();
}