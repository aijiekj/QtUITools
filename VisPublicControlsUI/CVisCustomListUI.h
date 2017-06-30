/************************************************************************/
/*		         自定义列表UI                                           */
/************************************************************************/
#ifndef CVISCUSTOMLISTUI_H
#define CVISCUSTOMLISTUI_H

#include "vispubliccontrolsui_global.h"
#include <QWidget>
#include <QMap>

class QListWidget;
class CVisPageTurningUI;
class QDomNode;
class QListWidgetItem;
class QLabel;

class VISPUBLICCONTROLSUI_EXPORT CVisCustomListUI : public QWidget
{
	Q_OBJECT

public:
	CVisCustomListUI(QWidget *parent = 0, bool bLoadDefault = true);
	~CVisCustomListUI();

	//初始化样式文件
	void InitPolicyFile(const QString &sFileName);
	//添加子项信息
	QListWidgetItem * AppChildItemInfo(const QString &sItemID);
	//获取子项对应的Widget
	QWidget * GetChildItemWidget(QListWidgetItem *pItem);
	//删除指定ItemUI
	void DelItemUI(const QString &sItemID);
	//删除当前ItemUI
	void DelCurrentItemUI();
	//清空列表数据
	void ClearCustomListInfo();
	//设置Item数据提示
	void SetItemCountTip(int nCount);
	//设置项目页个数
	void SetItemPageCount(int nCurPage, int nTotal);	


signals:
	void signal_OperBtn_ToDo(const QString &sItemID, const QString &sToDo);
	void signal_PageTurningUI_PageChanged(int nPage);
	void signal_Item_Clicked(const QString &sItemID);
	void signal_Item_DoubleClicked(const QString &sItemID);

protected:
	void paintEvent(QPaintEvent *event);

private:
	void InitLayout();	//初始化布局
	void InitListSettings();	//初始化表格设置
	void InitOperBtnSignal(QWidget *pItemUI);	//初始化ItemUI操作按钮信号
	void InitPageTurningUI(const QDomNode &node);	//初始化翻页界面
	void InitTopTipUI(const QDomNode &node);		//初始化顶端提示界面

	void InitTestInfo();

private slots:
	void slot_ListWidget_ItemClicked(QListWidgetItem *item);		//列表项单击处理
	void slot_ListWidget_ItemDoubleClicked(QListWidgetItem *item);	//列表项双击处理
	void slot_ItemUi_OperBtn_Clicked();								//列表项UI按钮单击处理事件

	void slot_OperBtn_ToDo(const QString &sItemID, const QString &sToDo);	//测试按钮

private:
	QListWidget					*m_pListUI;			//列表	
	QSize						m_itemSize;			//item大小
	QSize						m_GridSize;			//
	int							m_nSpacing;			//子项间隔与GridSize有冲突
	int							m_nLayoutMode;		//显示布防方式
	int							m_nViewMode;		//子项显示方式
	QString						m_sChildUIFile;		//itemUI文件
	QMap<QString, QWidget*>		m_index2ItemUI;		//ID与itemUI对照表

	QMap<QWidget*, QListWidgetItem*>		m_ui2Item;	//itemUi与Item对照表

	CVisPageTurningUI			*m_pCustomPageTurningUI;	//翻页
	QLabel						*m_pItemInfoCountLbl;		//项个数提示
	QString						 m_sItemCountText;			//项个数提示字符串

};

#endif // CVISCUSTOMLISTUI_H
