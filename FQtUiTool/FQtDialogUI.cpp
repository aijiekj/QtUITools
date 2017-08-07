#include "FQtDialogUI.h"
#include <QVBoxLayout>
#include <QMouseEvent>

FQtDialogUI::FQtDialogUI(QWidget *parent)
	: QDialog(parent)
{
	m_pUI = nullptr;
	m_pBusObj = nullptr;

	m_bMove = true;					
	m_bCurFrameMoveState = false;	
	m_nTopHight = 30;				
	m_bCurFrameType = false;

	setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinimizeButtonHint);
	setAttribute(Qt::WA_TranslucentBackground, true); 
}

FQtDialogUI::~FQtDialogUI()
{

}

bool FQtDialogUI::InitUIFile(const QString &sFile)
{
	bool bRet = false;
	m_pUI = new FQtWidgetUI(this);
	if(m_pUI == nullptr) return false;
	
	bRet = m_pUI->InitPolicyFileUI(sFile);
	if(!bRet) return bRet;
	InitUIBaseInfo();
	InitSignalSlots();
	
	QVBoxLayout *pMainLyt = new QVBoxLayout;
	pMainLyt->setMargin(0);
	pMainLyt->setSpacing(0);
	pMainLyt->addWidget(m_pUI);

	this->setLayout(pMainLyt);

	return bRet;
}

bool FQtDialogUI::InitUIForFullPath(const QString &sFile)
{
	m_pUI = new FQtWidgetUI(this);
	if(m_pUI == nullptr) return false;

	bool bRet = m_pUI->InitUIForFullPath(sFile);
	if(!bRet) return bRet;
	InitUIBaseInfo();
	InitSignalSlots();

	QVBoxLayout *pMainLyt = new QVBoxLayout;
	pMainLyt->setMargin(0);
	pMainLyt->setSpacing(0);
	pMainLyt->addWidget(m_pUI);

	this->setLayout(pMainLyt);

	return bRet;
}

void FQtDialogUI::InitSignalSlots()
{
	if(m_pUI == nullptr) return;
	connect(m_pUI, SIGNAL(signal_OperBtn_ToDo(const QString &)),
		this, SIGNAL(signal_OperBtn_ToDo(const QString &)));
}

void FQtDialogUI::mousePressEvent(QMouseEvent * event)
{
	if (!m_bMove) {
		return QDialog::mousePressEvent(event);
	}

	QPoint pos = event->pos();
	if (event->button() == Qt::LeftButton) {
		if (m_nTopHight >= pos.ry()) {
			m_bCurFrameMoveState = true;
		}

		m_CurrentPos = event->globalPos() - frameGeometry().topLeft();
		event->accept();
	}

	QDialog::mousePressEvent(event);
}

void FQtDialogUI::mouseMoveEvent(QMouseEvent * event)
{
	if (!m_bMove) {
		return QDialog::mouseMoveEvent(event);
	}

	QPoint pos = event->pos();
	if (event->buttons() && Qt::LeftButton)
	{
		if (m_bCurFrameMoveState && !m_bCurFrameType)
		{
			move(event->globalPos() - m_CurrentPos);
			event->accept();
		}
	}

	QDialog::mouseMoveEvent(event);
}

void FQtDialogUI::mouseReleaseEvent(QMouseEvent * event)
{
	if (!m_bMove) {
		return QDialog::mouseReleaseEvent(event);
	}

	m_bCurFrameMoveState = false;
	QPoint pos = event->pos();
	QPoint CurPos = this->pos();
	int nTop = CurPos.ry();
	int nLeft = CurPos.rx();
	bool bMove = false;
	if (CurPos.ry() < 0) {
		bMove = true;
		nTop = 0;
	}

	if (bMove) {
		move(nLeft, nTop);
	}

	QDialog::mouseReleaseEvent(event);
}


FQtWidgetUI * FQtDialogUI::GetUI()
{
	return m_pUI;
}

void FQtDialogUI::BindBusObj(QObject *pObj)
{
	m_pBusObj = pObj;
}

QObject * FQtDialogUI::GetBindBusObj()
{
	return m_pBusObj;
}

void FQtDialogUI::InitUIBaseInfo()
{
	if (m_pUI == nullptr) return;

	m_nTopHight = m_pUI->GetWindTitleHeight();
	m_bMove = m_pUI->GetWindMoveFlg();
	m_pUI->SetWindMoveFlg(false);

	//setAutoDefault(false);
}