#include "FQtCustomUIApp.h"
#include <QFileDialog>
#include "FQtWidgetUI.h"
#include "FQtDialogUI.h"
#include "FQtUiTool.h"


FQtCustomUIApp::FQtCustomUIApp(QWidget *parent)
	: QMainWindow(parent)
{
	m_pCurPreViewUI = nullptr;
	ui.setupUi(this);

	InitUI();
	InitSignalSlots();
}

FQtCustomUIApp::~FQtCustomUIApp()
{

}

void FQtCustomUIApp::InitSignalSlots()
{
	connect(ui.actionOpen_O, SIGNAL(triggered()),
		this, SLOT(slot_OpenFileAct_Clicked()));
	connect(ui.actionPreView, SIGNAL(triggered()),
		this, SLOT(slot_PreViewAct_Clicked()));
	connect(ui.actionQt_Widget, SIGNAL(triggered()),
		this, SLOT(slot_QtWidgetAct_Clicked()));
	connect(ui.actionQt_Dialog, SIGNAL(triggered()),
		this, SLOT(slot_QtDialogAct_Clicked()));
}

void FQtCustomUIApp::InitUI()
{

}

void FQtCustomUIApp::slot_OpenFileAct_Clicked()
{
	m_sCurOpenFile = QFileDialog::getOpenFileName(this,
		QStringLiteral("打开UI文件"), ".", tr("UI Files (*.ui);; All Files(*.*)"));

	if(!m_sCurOpenFile.isEmpty()){
		QFile file(m_sCurOpenFile);

		if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
			return;

		QString sInfo = file.readAll();

		//ui.textBrowser->setText(sInfo);
	}
}

void FQtCustomUIApp::slot_PreViewAct_Clicked()
{
	if(m_sCurOpenFile.isEmpty()) return;
	m_pCurPreViewUI = FQtUiTool::CreateUIForPath(m_sCurOpenFile);

	if(m_pCurPreViewUI != nullptr){

		m_pCurPreViewUI->setAttribute(Qt::WA_DeleteOnClose, true);
		m_pCurPreViewUI->show();
	}
}

void FQtCustomUIApp::slot_QtWidgetAct_Clicked()
{
	if(m_sCurOpenFile.isEmpty()) return;

	FQtWidgetUI *pCustomWidgetUI = new FQtWidgetUI;
	if(pCustomWidgetUI == nullptr) return;

	if(pCustomWidgetUI->InitUIForFullPath(m_sCurOpenFile)){
		pCustomWidgetUI->setAttribute(Qt::WA_DeleteOnClose, true);
		pCustomWidgetUI->show();
	}
}

void FQtCustomUIApp::slot_QtDialogAct_Clicked()
{
	if(m_sCurOpenFile.isEmpty()) return;

	FQtDialogUI *pCustomDialogUI = new FQtDialogUI;
	if(pCustomDialogUI == nullptr) return;

	if(pCustomDialogUI->InitUIForFullPath(m_sCurOpenFile)){
		pCustomDialogUI->setAttribute(Qt::WA_DeleteOnClose, true);

		if(pCustomDialogUI->exec() == QDialog::Accepted){

		}
	}
}
