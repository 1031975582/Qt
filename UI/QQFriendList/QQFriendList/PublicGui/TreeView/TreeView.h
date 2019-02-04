#pragma once

#include <QStandardItemModel>
#include <QTreeView>
#include <QEvent>
#include <QHoverEvent>
#include "StyledDelegate.h"

namespace publicgui
{
	class TreeView : public QTreeView
	{
		Q_OBJECT

	public:
		TreeView(QWidget *parent = Q_NULLPTR);
		~TreeView();

	signals:
		// ���Item�ź�
		void signalClicked(const QModelIndex& iIndex);
		// ���Item�ź� ���嵽�㵽��Role
		void signalClicked(const QModelIndex& iIndex, int role);
		// ˫���ź�
		void signalDoubleClicked(const QModelIndex& iIndex);

	protected:
		virtual bool viewportEvent(QEvent* pEvent);

	private:
		StyledDelegate m_itemDelegate;
		QStandardItemModel m_model;
	};

}
