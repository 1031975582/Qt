#include "MainScene.h"
#include <QDebug>
#include <QPrinter>
#include "QPainter"

MainScene::MainScene(QObject *parent)
	: QGraphicsScene(parent)
{
	QColor borderColor("#979797");
	QPen outlinePen;
	outlinePen.setColor(borderColor);
	outlinePen.setWidth(1);

	// �������
	QRectF frontCabineRect(231, -600, 88, 130);
	setFrontCabinet(frontCabineRect);

	// LED��Ԫ ��
	QRectF ledRectHeng(0, 0, 12 * 47, 30);
	setLEDUnit(ledRectHeng, 12, false);
	
	// LED��Ԫ ��
	QRectF ledRectShu(0, 30, 47, 12 * 30);
	setLEDUnit(ledRectShu, 12, true);

	QRectF arect(m_LEDUnit->rect().x(), m_LEDUnit->rect().y() + m_LEDUnit->rect().height(), 12 * 47, 30);
	setLEDUnit(arect, 12, false);

	QRectF brect(m_LEDUnit->rect().x() + m_LEDUnit->rect().width(), m_LEDUnit->rect().y() - m_LEDUnit->rect().height()*12, 47, 12 * 30);
	setLEDUnit(brect, 12, true);

	// LCD����
	qreal lcdPosX = 0;		// LCD���Ͻ���ʼ��λ��
	qreal lcdPosY = 0;		// LCD���Ͻ���ʼ��yλ��
	qreal lcdUnitWidth = 221;   // LCD��Ԫ���
	qreal lcdUnitHeight = 90;   // LCD��Ԫ���
	int   lcdRows = 18;			// LCD����
	int   lcdColumns = 12;		// LCD����
	int   leftLEDColumns = 5;	// ���LED����
	int   rightLEDColumns = 7;	// �ұ�LED����
	int   topLEDRows = 3;		// ����LED����
	qreal ledUnitWidth = 80;	// LED���
	qreal ledUnitHeight = 49;	// LED�߶�
	qreal boardThick = 15;	    // �����

	QRectF lcdRect(lcdPosX, lcdPosY, lcdUnitWidth, lcdUnitHeight);
	QGraphicsItem* lcdPart = addLCDPart(lcdRect, lcdRows, lcdColumns);
	lcdPart->setFlag(QGraphicsItem::ItemIsMovable);

	qreal verticalLCDRectHeight = lcdPart->childrenBoundingRect().height();
	qreal verticalLCDRectWidth = lcdPart->childrenBoundingRect().width();   // LED��ȣ�
	QRectF verticalLeftLEDRect(lcdPosX - (ledUnitWidth*leftLEDColumns + 2 * boardThick), lcdPosY, ledUnitWidth*leftLEDColumns + 2 * boardThick, verticalLCDRectHeight);
	// ���LED ÿ��LED�� ��
	QGraphicsItem* verticalLeftLEDWithBoard = addVerticalLEDWithBoard(verticalLeftLEDRect, leftLEDColumns, ledUnitWidth, ledUnitHeight); // ���LED ÿ��LED��60 ��40
	verticalLeftLEDWithBoard->setParentItem(lcdPart);

	// �ұ�LED ÿ��LED�� ��
	QRectF verticalRightLEDRect(lcdPosX + verticalLCDRectWidth, lcdPosY, ledUnitWidth*rightLEDColumns + 2*boardThick, verticalLCDRectHeight);
	QGraphicsItem* verticalRightLEDWithBoard = addVerticalLEDWithBoard(verticalRightLEDRect, rightLEDColumns, ledUnitWidth, ledUnitHeight);
	verticalRightLEDWithBoard->setParentItem(lcdPart);

	// ���� ÿ��LED�� ��
	qreal topLEDPartXPos = lcdPosX - (ledUnitWidth*leftLEDColumns + 2 * boardThick);
	qreal topLEDPartYPos = lcdPosY - ledUnitHeight*topLEDRows - 2 * boardThick;
	qreal topLEDPartWidth = verticalLCDRectWidth + ledUnitWidth*(leftLEDColumns + rightLEDColumns) + 4 * boardThick;
	qreal topLEDPartHeight = ledUnitHeight*topLEDRows + 2 * boardThick;
	QRectF horizontalLEDRectf(topLEDPartXPos, topLEDPartYPos, topLEDPartWidth, topLEDPartHeight);
	QGraphicsItem* horizontalRightLEDWithBoard = addHorizontalLEDWithBoard(horizontalLEDRectf, topLEDRows, ledUnitWidth, ledUnitHeight);
	horizontalRightLEDWithBoard->setParentItem(lcdPart);

	// --------------------------------------------��һ��
	
	//qreal cabinetUnitWidth = lcdUnitWidth-2*boardThick;	// �����м䵥Ԫ���
	//qreal cabinetUnitHeight = lcdUnitHeight-2*boardThick;// �����м䵥Ԫ�߶�

	qreal cabinetUnitWidth = 250;	// �����м䵥Ԫ���
	qreal cabinetUnitHeight = 180.8;// �����м䵥Ԫ�߶�

	qreal cabinetXPos = lcdPosX - (ledUnitWidth*leftLEDColumns + 2 * boardThick);
	qreal cabinetYPos = lcdPosY+lcdUnitHeight*lcdRows;
	QRectF cabinetPartRect(cabinetXPos, cabinetYPos, verticalLCDRectWidth + ledUnitWidth*(leftLEDColumns + rightLEDColumns) + 4 * boardThick, cabinetUnitHeight+2 * boardThick);
	addCabinet(cabinetPartRect, cabinetUnitWidth, cabinetUnitHeight, boardThick)->setParentItem(lcdPart);
	

	QPrinter printer(QPrinter::HighResolution);
	printer.setPaperSize(QPrinter::A4);

	QPainter painter(&printer);
	this->render(&painter);
}

MainScene::~MainScene()
{
	qDebug() << QString("%1  %2 ").arg(this->width()).arg(this->height());
}


/** @fn     void MainScene::setFrontCabinet()
 *  @brief  ������ʽ �����������Ÿ߶ȡ����
 *  @return void
 */
void MainScene::setFrontCabinet(QRectF rect)
{
	// ǰ�й���ʽ
	QRectF cabinetRect(rect);
	m_frontCabinet = this->addRect(rect);
	m_frontCabinet->setFlag(QGraphicsItem::ItemIsMovable);
	const qreal frontCabinetWidth = cabinetRect.width()/2;
	const qreal frontCabinetHeight = cabinetRect.height();
	const qreal frontCabinetX = cabinetRect.x();
	const qreal frontCabinetY = cabinetRect.y();

	QColor borderColor("#979797");
	QBrush whiteBrush(Qt::white);
	QPen outlinePen;
	outlinePen.setColor(borderColor);
	outlinePen.setWidth(0);

	// ����
	QGraphicsRectItem* leftFrontCabinet;
	leftFrontCabinet = this->addRect(frontCabinetX, frontCabinetY, frontCabinetWidth, frontCabinetHeight, outlinePen, whiteBrush);
	leftFrontCabinet->setParentItem(m_frontCabinet);

	// ����
	QGraphicsRectItem* rightFrontCabinet;
	rightFrontCabinet = this->addRect(frontCabinetX + frontCabinetWidth, frontCabinetY, frontCabinetWidth, frontCabinetHeight, outlinePen, whiteBrush);
	qreal rightFrontCabinetXPos = rightFrontCabinet->rect().x();
	qreal rightFrontCabinetYPos = rightFrontCabinet->rect().y();
	rightFrontCabinet->setParentItem(m_frontCabinet);

	// ������״
	QPen bashouPen("#000000");
	bashouPen.setWidth(1);
	QBrush bashouBrush("#F1F1F1");
	QGraphicsItem* lashouItem;
	QRectF lashouItemRect(rightFrontCabinetXPos + 4.7, rightFrontCabinetYPos + rightFrontCabinet->rect().height()/2 - 4.5, 4.8, 9);
	lashouItem = this->addRect(lashouItemRect, outlinePen, bashouBrush);
	lashouItem->setParentItem(rightFrontCabinet);
}




/** @fn     void MainScene::setLEDUnit(QRectF rect, int number, bool isVertical)
 *  @brief  
 *  @param  QRectF rect
 *  @param  int number
 *  @param  bool isVertical
 *  @return void
 */
void MainScene::setLEDUnit(QRectF rect, int number, bool isVertical)
{
	m_LEDUnit = this->addRect(rect);
	m_LEDUnit->setFlag(QGraphicsItem::ItemIsMovable);
	for (size_t i = 0; i < number; ++i)
	{
		QPen pen("#979797");
		pen.setWidth(0);
		QBrush brush("#F1F1F1");
		QGraphicsItem* LEDUnit = NULL;
		
		if (!isVertical)
		{
			QRectF tempRectf(rect.x() + rect.width() / number*i, rect.y(), rect.width()/number, rect.height());
			LEDUnit = this->addRect(tempRectf, pen, brush);
			LEDUnit->setParentItem(m_LEDUnit);
		}
		else
		{
			QRectF tempRectf(rect.x(), rect.y() + rect.height() / number*i, rect.width() , rect.height()/ number);
			LEDUnit = this->addRect(tempRectf, pen, brush);
			LEDUnit->setParentItem(m_LEDUnit);
		}
	}
}




/** @fn     void MainScene::setLCDUnit(QRectF rect, int rows, int columns)
 *  @brief  ����LCD������ ����rows��columns��
 *  @param  QRectF rect ��ʼλ��
 *  @param  int rows ��
 *  @param  int columns��
 *  @return void
 */
QGraphicsItem* MainScene::addLCDPart(QRectF rect, int rows, int columns)
{
	QRectF lcdRectf(rect.x(), rect.y(), rect.width()*columns, rect.height()*rows);
	QGraphicsItem* LCDPartItem = this->addRect(lcdRectf);
	LCDPartItem->setFlag(QGraphicsItem::ItemIsMovable);
	

	QPen pen("#979797");
	pen.setWidth(0);
	QBrush brush("#F1F1F1");
	QGraphicsItem* LEDUnit;
	for (size_t i = 0; i < rows; ++i)
	{
		for (size_t j = 0; j < columns; ++j)
		{
			QRectF tempRectf(rect.x() + rect.width()*j, rect.y() + rect.height()*i, rect.width(), rect.height());
			LEDUnit = this->addRect(tempRectf, pen, brush);
			LEDUnit->setParentItem(LCDPartItem);
		}
	}

	return LCDPartItem;
}


/** @fn     QGraphicsItem* MainScene::setVerticalLEDWithBoard(QRectF rect, int ledWidth, int ledHeight)
 *  @brief  ��ֱLED����
 *  @param  QRectF rect
 *  @param  int ledColumns LED����
 *  @param  int ledWidth  LED�ͺŵĿ��
 *  @param  int ledHeight LED�ͺŵĸ߶�
 *  @return QGraphicsItem*
 */
QGraphicsItem* MainScene::addVerticalLEDWithBoard(QRectF rect, int ledColumns, int ledWidth, int ledHeight)
{
	QPen outLinePen("#979797");
	outLinePen.setWidth(0);
	QBrush mainBrush("#BEBEBE");

	QGraphicsItem* verticalLEDWithBoard = nullptr;
	verticalLEDWithBoard = this->addRect(rect, outLinePen, mainBrush);
	qreal xPos = rect.x();
	qreal yPos = rect.y();
	qreal width = rect.width();		//verticalLEDWithBoard ģ���ܿ��
	qreal height = rect.height();	//verticalLEDWithBoard ģ���ܸ߶�

	// LED
	int ledCount = height / ledHeight; //LED����

	qreal ledXPos = xPos + (width - ledWidth*ledColumns) / 2; // ��ʼLEDλ��
	for (size_t j = 0; j < ledColumns; ++j)
	{
		for (size_t i = 0; i < ledCount; ++i)
		{
			QRectF ledRectf(ledXPos + ledWidth*j, yPos + i*ledHeight, ledWidth, ledHeight);
			QBrush ledBrush("#D8D8D8");
			QGraphicsItem* ledUnit = this->addRect(ledRectf, outLinePen, ledBrush);
			ledUnit->setParentItem(verticalLEDWithBoard);
		}

		qreal margin = height - ledCount*ledHeight; // ����
		QGraphicsItem* marginItem;		//������
		QRectF marginRectf(ledXPos + ledWidth*j, yPos + ledCount*ledHeight, ledWidth, margin);
		marginItem = this->addRect(marginRectf, outLinePen, mainBrush);
		marginItem->setParentItem(verticalLEDWithBoard);
	}
	return verticalLEDWithBoard;
}


/** @fn     QGraphicsItem* MainScene::addHorizontalLEDWithBoard(QRectF rect, int ledWidth, int ledHeight)
 *  @brief  ���LED����
 *  @param  QRectF rect
 *  @param  int ledWidth
 *  @param  int ledHeight
 *  @return QGraphicsItem*
 */
QGraphicsItem* MainScene::addHorizontalLEDWithBoard(QRectF rect, int topRows, int ledWidth, int ledHeight)
{
	QPen outLinePen("#979797");
	outLinePen.setWidth(1);
	QBrush mainBrush("#BEBEBE");

	QGraphicsItem* horizontalLEDWithBoard = nullptr;
	horizontalLEDWithBoard = this->addRect(rect, outLinePen, mainBrush);
	qreal xPos = rect.x();
	qreal yPos = rect.y();
	qreal width = rect.width();		//verticalLEDWithBoard ģ���ܿ��
	qreal height = rect.height();	//verticalLEDWithBoard ģ���ܸ߶�

	// LED
	int ledCount = width / ledWidth; //ÿ�к��LED����
	qreal widthMargin = width - ledCount*ledWidth; // �������
	qreal ledXPos = xPos + widthMargin / 2;
	qreal ledYPos = yPos + (height-ledHeight*topRows)/2;

	for (size_t j = 0; j < topRows; ++j)
	{
		for (size_t i = 0; i < ledCount; ++i)
		{
			QRectF ledRectf(ledXPos + i*ledWidth, ledYPos+j*ledHeight, ledWidth, ledHeight);
			QBrush ledBrush("#D8D8D8");
			QGraphicsItem* ledUnit = this->addRect(ledRectf, outLinePen, ledBrush);
			ledUnit->setParentItem(horizontalLEDWithBoard);
		}

		QGraphicsItem* leftMarginItem;		//��������
		QRectF leftMarginRectf(xPos, ledYPos + j*ledHeight, widthMargin / 2, ledHeight);
		leftMarginItem = this->addRect(leftMarginRectf, outLinePen, mainBrush);
		leftMarginItem->setParentItem(horizontalLEDWithBoard);

		QGraphicsItem* rightMarginItem;		//��������
		QRectF rightMarginRectf(xPos + width - widthMargin / 2, ledYPos + j*ledHeight, widthMargin / 2, ledHeight);
		rightMarginItem = this->addRect(rightMarginRectf, outLinePen, mainBrush);
		rightMarginItem->setParentItem(horizontalLEDWithBoard);
	}

	return horizontalLEDWithBoard;
}

QGraphicsItem* MainScene::addCabinet(QRectF rect, int cabinetUnitWidth, int cabinetUnitHeight, int boardThick)
{
	QPen outLinePen("#979797");
	outLinePen.setWidth(1);
	QBrush mainBrush("#BEBEBE");
	QGraphicsItem* cabinetPart = this->addRect(rect, outLinePen, mainBrush);

	qreal xPos = rect.x();
	qreal yPos = rect.y();
	qreal width = rect.width();
	qreal height = rect.height();

	int cabinetCount = width / (cabinetUnitWidth+2*boardThick);   // �ܷ��µĹ��Ӹ���
	int margin = width - cabinetCount*(cabinetUnitWidth + 2 * boardThick);// ���� �ֳ����ҹ���

	qreal startXPos = xPos + margin / 2 + boardThick;
	for (size_t i = 0; i < cabinetCount; ++i)
	{
		QRectF cabinetRectf(startXPos + i*(cabinetUnitWidth+2*boardThick), yPos + (height - cabinetUnitHeight) / 2, cabinetUnitWidth, cabinetUnitHeight);
		QBrush cabinetBrush("#FFFFFF");
		QGraphicsItem* cabinetUnit = this->addRect(cabinetRectf, outLinePen, cabinetBrush);
		cabinetUnit->setParentItem(cabinetPart);

		qreal lineX1 = cabinetUnit->boundingRect().x() + cabinetUnitWidth / 2;
		qreal lineY1 = cabinetUnit->boundingRect().y();
		qreal lineX2 = cabinetUnit->boundingRect().x() + cabinetUnitWidth / 2;
		qreal lineY2 = cabinetUnit->boundingRect().y() + cabinetUnitHeight;
		// ����
		QPen linePen("#979797");
		linePen.setWidth(1);
		QGraphicsItem* doorLineItem = this->addLine(lineX1, lineY1, lineX2, lineY2, linePen);
		doorLineItem->setParentItem(cabinetUnit);

		// �Ű�����״
		qreal bashouXPos = cabinetUnit->boundingRect().x() + cabinetUnitWidth / 2 + 5;
		qreal bashouYPos = cabinetUnit->boundingRect().y() + cabinetUnitHeight/2-4.5;
		qreal bashouWidth = 4.8;
		qreal bashouHeight = 9;

		QPen bashouPen("#000000");
		bashouPen.setWidth(1);
		QBrush bashouBrush("#FFFFEE");
		QGraphicsItem* lashouItem;
		QRectF lashouItemRect(bashouXPos, bashouYPos, bashouWidth, bashouHeight);
		lashouItem = this->addRect(lashouItemRect, linePen, bashouBrush);
		lashouItem->setParentItem(cabinetUnit);
	}

	return cabinetPart;
}
