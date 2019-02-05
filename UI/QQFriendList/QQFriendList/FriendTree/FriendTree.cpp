#include "FriendTree.h"
#include "ItemDelegate.h"
#include <QHeaderView>
#include "GlobalDefines.h"

namespace qqfriendlist
{
	FriendTree::FriendTree(QWidget *parent)
		: TreeView(parent)
	{
		initUi();
		initConnection();
	}

	FriendTree::~FriendTree()
	{
	}

	/****************************************!
	 * @brief  ��ֵ�ӿ�
	 * @param  [in]  const std::vector<Group> & groups
	 * @return void
	 ****************************************/
	void FriendTree::setValues(const std::vector<Group>& groups)
	{
		m_model->clear();
		for (const auto& group : groups)
		{
			// ��ӷ���
			QStandardItem* item = new QStandardItem(group.groupName);
			item->setEditable(false);
			item->setData(group.groupName, Qt::ToolTipRole);
			item->setData(true, static_cast<int>(CustomRole::IsGroupRole));
			m_model->appendRow(item);
			for (const auto& contact : group.contactList)
			{
				// �����µ���ϵ��
				QStandardItem* contactItem = new QStandardItem(contact.name);
				contactItem->setEditable(false);
				contactItem->setData(contact.name, Qt::ToolTipRole);

				QVariant value{};
				value.setValue(contact);
				contactItem->setData(value, static_cast<int>(CustomRole::ContactRole));
				item->appendRow(contactItem);
			}
		}
	}

	/****************************************!
	 * @brief  ��ʼ������
	 * @return void  
	 ****************************************/
	void FriendTree::initUi()
	{
		setWindowTitle(tr("QQ Friend List"));
		// basic init
		header()->hide();	// ���ر�ͷ
		setIndentation(0);	// ��߾�����Ϊ0
		//setAnimated(true);  // չ��ʱ����

		m_model = new QStandardItemModel(this);
		setModel(m_model);
		m_delegate = new ItemDelegate(this);
		setItemDelegate(m_delegate);
	}

	/****************************************!
	 * @brief  ��ʼ���źŲ�����
	 * @return void  
	 ****************************************/
	void FriendTree::initConnection()
	{
		// ����¼�
		connect(this, &QTreeView::clicked, [&](const QModelIndex& index)
		{
			if (index.data(static_cast<int>(CustomRole::IsGroupRole)).toBool())
			{
				setExpanded(index, !isExpanded(index)); // ����չ���б�
			}
		});

		// չ��ʱ��������չ��ͼ��
		connect(this, &QTreeView::expanded, [&](const QModelIndex& index)
		{
			m_model->itemFromIndex(index)->setData(true, static_cast<int>(CustomRole::IsExpandedRole));
		});

		// ����ʱ��������չ��ͼ��
		connect(this, &QTreeView::collapsed, [&](const QModelIndex& index)
		{
			m_model->itemFromIndex(index)->setData(false, static_cast<int>(CustomRole::IsExpandedRole));
		});

		// hover�¼�
		connect(this, &TreeView::signalHover, this, &FriendTree::onHoverHandle);
	}

	/****************************************!
	 * @brief  hover�¼�����
	 * @param  [in]  const QModelIndex & index ������
	 * @param  [in]  int role ��ɫ
	 * @return void  
	 ****************************************/
	void FriendTree::onHoverHandle(const QModelIndex& index, int role)
	{
		if (index.data(static_cast<int>(CustomRole::IsGroupRole)).toBool())
		{
			return; // Ⱥ���hover�¼� �˳�
		}
		else
		{
			// ��ͬ������ʾ��ͬtooltip
			auto info = index.data(static_cast<int>(CustomRole::ContactRole)).value<Contact>();
			QString displayName{};
			switch (role)
			{
			case static_cast<int>(CustomRole::VideoRole): // ��Ƶͨ��
			{
				std::string videoToolTip = "��Ƶͨ��";
				displayName = QString::fromLocal8Bit(videoToolTip.c_str());
				break;
			}
			case static_cast<int>(CustomRole::SignatureRole): // ����ǩ��
			{
				displayName = info.signature;
				break;
			}
			default:
			{
				// Ĭ��tooltip��ʾ�û�����+QQ��
				displayName = info.name + "(" + info.nickName + ")" + "(" + info.id + ")";
				break;
			}
			}

			m_model->itemFromIndex(index)->setData(displayName, Qt::ToolTipRole);
		}
	}
}

