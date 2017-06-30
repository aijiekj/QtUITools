#include "CVisQtDialogUI.h"
#include <QVBoxLayout>

CVisQtDialogUI::CVisQtDialogUI(QWidget *parent)
	: QDialog(parent)
{
	m_pUI = nullptr;
	m_pBusObj = nullptr;

	setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinimizeButtonHint);
	setAttribute(Qt::WA_TranslucentBackground, true); 
}

CVisQtDialogUI::~CVisQtDialogUI()
{

}

bool CVisQtDialogUI::InitUIFile(const QString &sFile)
{
	bool bRet = false;
	m_pUI = new CVisQtWidgetUI(this);
	if(m_pUI == nullptr) return false;
	
	bRet = m_pUI->InitPolicyFileUI(sFile);
	if(!bRet) return bRet;
	InitSignalSlots();
	
	QVBoxLayout *pMainLyt = new QVBoxLayout;
	pMainLyt->setMargin(0);
	pMainLyt->setSpacing(0);
	pMainLyt->addWidget(m_pUI);

	this->setLayout(pMainLyt);

	return bRet;
}

bool CVisQtDialogUI::InitUIForFullPath(const QString &sFile)
{
	m_pUI = new CVisQtWidgetUI(this);
	if(m_pUI == nullptr) return false;

	bool bRet = m_pUI->InitUIForFullPath(sFile);
	if(!bRet) return bRet;
	InitSignalSlots();

	QVBoxLayout *pMainLyt = new QVBoxLayout;
	pMainLyt->setMargin(0);
	pMainLyt->setSpacing(0);
	pMainLyt->addWidget(m_pUI);

	this->setLayout(pMainLyt);

	return bRet;
}

void CVisQtDialogUI::InitSignalSlots()
{
	if(m_pUI == nullptr) return;
	connect(m_pUI, SIGNAL(signal_OperBtn_ToDo(const QString &)),
		this, SIGNAL(signal_OperBtn_ToDo(const QString &)));
}


CVisQtWidgetUI * CVisQtDialogUI::GetUI()
{
	return m_pUI;
}

void CVisQtDialogUI::BindBusObj(QObject *pObj)
{
	m_pBusObj = pObj;
}

QObject * CVisQtDialogUI::GetBindBusObj()
{
	return m_pBusObj;
}
