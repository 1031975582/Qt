#ifndef MAINSCENE_H
#define MAINSCENE_H

#include <QGraphicsScene>
#include <QGraphicsEllipseItem>

class MainScene : public QGraphicsScene
{
	Q_OBJECT

	// ֧�ܻ�������

public:
	MainScene(QObject *parent = nullptr);
	~MainScene();
	// ����ģ��
	void setFrontCabinet(QRectF rect);
	// LED��Ԫ
	void setLEDUnit(QRectF rect, int number, bool isVertical);
	// LCD������
	QGraphicsItem* addLCDPart(QRectF rect, int rows, int columns);
	// LED����� ���� ��
	QGraphicsItem* addVerticalLEDWithBoard(QRectF rect, int ledColumns, int ledWidth, int ledHeight);

	// LED����� ����
	QGraphicsItem* addHorizontalLEDWithBoard(QRectF rect, int topRows, int ledWidth, int ledHeight);

	QGraphicsItem* addCabinet(QRectF rect, int cabinetUnitWidth, int cabinetUnitHeight, int boardThick);
private:
	QGraphicsEllipseItem* m_ellipse;

	QGraphicsRectItem* m_LEDUnit;   // LED��Ԫ
	QGraphicsRectItem* m_LCDUnit;   // LCD��Ԫ
	QGraphicsRectItem* m_frontCabinet; // ����ģ��


	// ����ͼ��LED��LCD����
	QGraphicsRectItem* m_frontViewLEDAndLCDPart;

	qreal m_bashouHeight = 9;			// �Ű��ָ߶�
	qreal m_bashouWidth = 4.8;		// �Ű��ֿ��
};

#endif // MAINSCENE_H
