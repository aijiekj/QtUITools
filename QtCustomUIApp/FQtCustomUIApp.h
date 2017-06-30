#ifndef FQTCUSTOMUIAPP_H
#define FQTCUSTOMUIAPP_H

#include <QtWidgets/QMainWindow>
#include "ui_FQtCustomUIApp.h"

class FQtCustomUIApp : public QMainWindow
{
	Q_OBJECT

public:
	FQtCustomUIApp(QWidget *parent = 0);
	~FQtCustomUIApp();

private slots:
	void slot_OpenFileAct_Clicked();
	void slot_PreViewAct_Clicked();
	void slot_QtWidgetAct_Clicked();
	void slot_QtDialogAct_Clicked();

private:
	void InitSignalSlots();

private:
	Ui::FQtCustomUIAppClass ui;

	QString				m_sCurOpenFile;

	QWidget				*m_pCurPreViewUI;
};

#endif // FQTCUSTOMUIAPP_H
