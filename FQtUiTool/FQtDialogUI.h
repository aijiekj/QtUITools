/************************************************************************/
/*						 使用Qt布局创建QDilog                           */
/************************************************************************/
#ifndef FQtDialogUI_H
#define FQtDialogUI_H

#include "fqtuitool_global.h"
#include <QDialog>
#include "FQtWidgetUI.h"

class QMouseEvent;

class FQTUITOOL_EXPORT FQtDialogUI : public QDialog
{
	Q_OBJECT

public:
	FQtDialogUI(QWidget *parent = nullptr);
	~FQtDialogUI();

	bool InitUIFile(const QString &sFile);
	bool InitUIForFullPath(const QString &sFile);

	void BindBusObj(QObject *pObj);
	QObject *GetBindBusObj();

	//获取UI
	FQtWidgetUI *GetUI();

signals:
	void signal_OperBtn_ToDo(const QString &sToDo);

private:
	void InitSignalSlots();
	void InitUIBaseInfo();

protected:
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);

private:
	FQtWidgetUI				*m_pUI;
	bool						m_bCurFrameType;
	bool						m_bMove;					
	bool						m_bCurFrameMoveState;		
	int							m_nTopHight;				
	QPoint						m_CurrentPos;			

	QObject						*m_pBusObj;
};

#endif // FQtDialogUI_H
