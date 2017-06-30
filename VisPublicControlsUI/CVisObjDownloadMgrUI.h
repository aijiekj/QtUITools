#ifndef CVISOBJDOWNLOADMGRUI_H
#define CVISOBJDOWNLOADMGRUI_H

#include "vispubliccontrolsui_global.h"
#include <QWidget>

class VISPUBLICCONTROLSUI_EXPORT CVisObjDownloadMgrUI : public QWidget
{
	Q_OBJECT

public:
	static CVisObjDownloadMgrUI* GetInstance();  

	void InitPolicyFile(const QString &sFile);
	void BindingBusObj(QObject *pBusObj);
	QObject *GetBindingBusObj();

	CVisCustomTableUI *GetCurCustomTbl();

	void ShowMsgUI();
	//设置下载信息,目前没有存本地数据
	void SetDownloadInfo(const QStringList &lInfo);


signals:
	void signal_OperBtn_ToDo(const QString &sToDo);
	void signal_CustomTbl_OperBtn_ToDo(int nRow, const QString &sToDo);

protected:
	void resizeEvent(QResizeEvent *event);
	void paintEvent(QPaintEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mousePressEvent(QMouseEvent *event);

private slots:
	void slot_OperBtn_Clicked();
	void slot_CustomTbl_OperBtn_ToDo(int nRow, const QString &sToDo);

private:
	CVisObjDownloadMgrUI(QWidget *parent = 0);
	~CVisObjDownloadMgrUI();
	void ResizeChildGeometry(QSize &size);
	void InitCustomTblUI(const QDomNode &domNode);


private:
	static CVisObjDownloadMgrUI* m_pObjDownloadMgrUI; // CVisObjDownloadMgrUI 全局唯一的变量  
	QObject					*m_pBusObj;

	bool m_bMove;					//是否可移动
	bool m_bCurFrameMoveState;		//当前窗口状态
	int m_nTopHight;				//标题高度
	QPoint m_CurrentPos;			//当前移动状态

	CLabelDeque				m_lInfo;
	CButtonDeque			m_lOperBtn;

	CVisCustomTableUI		*m_pCustomTblUI;
	QSize					m_customTblUISize;
	QString					m_sCustomTblUIAlgmt;		
};

#endif // CVISOBJDOWNLOADMGRUI_H
