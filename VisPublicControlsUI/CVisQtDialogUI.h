/************************************************************************/
/*						 使用Qt布局创建QDilog                           */
/************************************************************************/
#ifndef CVISQTDIALOGUI_H
#define CVISQTDIALOGUI_H

#include "vispubliccontrolsui_global.h"
#include <QDialog>
#include "CVisQtWidgetUI.h"

class VISPUBLICCONTROLSUI_EXPORT CVisQtDialogUI : public QDialog 
{
	Q_OBJECT

public:
	CVisQtDialogUI(QWidget *parent = nullptr);
	~CVisQtDialogUI();

	bool InitUIFile(const QString &sFile);
	bool InitUIForFullPath(const QString &sFile);

	void BindBusObj(QObject *pObj);
	QObject *GetBindBusObj();

	//获取UI
	CVisQtWidgetUI *GetUI();

signals:
	void signal_OperBtn_ToDo(const QString &sToDo);

private:
	void InitSignalSlots();

private:
	CVisQtWidgetUI				*m_pUI;

	QObject						*m_pBusObj;
};

#endif // CVISQTDIALOGUI_H
