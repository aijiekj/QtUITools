#include "CVisObjDownloadMgrUI.h"
#include "CVisObjDownloadMgrUIObj.h"

CVisObjDownloadMgrUI* CVisObjDownloadMgrUI::m_pObjDownloadMgrUI = NULL;  

CVisObjDownloadMgrUI::CVisObjDownloadMgrUI(QWidget *parent)
	: QWidget(parent)
{
	m_bMove = false;
	m_nTopHight = 40;

	setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinimizeButtonHint);
	this->setAttribute(Qt::WA_TranslucentBackground, true); 
}

CVisObjDownloadMgrUI::~CVisObjDownloadMgrUI()
{

}

void CVisObjDownloadMgrUI::resizeEvent(QResizeEvent *event)
{
	QSize size = event->size();

	ResizeChildGeometry(size);
}

void CVisObjDownloadMgrUI::ResizeChildGeometry(QSize &size)
{
	for(int i = 0; i < m_lInfo.size(); i++){
		if(m_lInfo.at(i).pLabel != NULL){
			CVisVAnalysisUIXML::SetWidgetGeometry(
				((QWidget*)m_lInfo.at(i).pLabel->parent())->geometry().size(),
				m_lInfo.at(i).size, m_lInfo.at(i).strAlignment,
				m_lInfo.at(i).pLabel);
		}
	}

	for(int i = 0; i < m_lOperBtn.size(); i++){
		if(m_lOperBtn.at(i).pButton != NULL){
			CVisVAnalysisUIXML::SetWidgetGeometry(
				((QWidget*)m_lOperBtn.at(i).pButton->parent())->geometry().size(),
				m_lOperBtn.at(i).size, m_lOperBtn.at(i).strAlignment,
				m_lOperBtn.at(i).pButton);
		}
	}

	if(m_pCustomTblUI != NULL){
		CVisVAnalysisUIXML::SetWidgetGeometry(size, m_customTblUISize,
			m_sCustomTblUIAlgmt, m_pCustomTblUI);
	}
}

void CVisObjDownloadMgrUI::InitPolicyFile(const QString &sFile)
{
	QDomElement domEle;
	QDomNode childNode;
	if(CVisVAnalysisUIXML::InitFristDomNode(domEle, childNode, sFile)){

		CVisVAnalysisUIXML::InitBaseLayoutInfo(domEle, QSize(), QString(), this);

		//设置窗口是否可以拖动
		m_bMove = domEle.attributeNode("WidgetMove").value().toInt();
		//设置标题栏高度
		m_nTopHight = domEle.attributeNode("TitleBarHeigth").value().toInt();

		while(!childNode.isNull()){

			if(childNode.isElement()){
				QString sTageName = childNode.toElement().tagName();
					
				if(sTageName == QString("Label"))
				{
					LabelInfo info;
					info.pLabel = NULL;
					CVisVAnalysisUIXML::AnalysisLabel(childNode, info, this);

					if(info.pLabel != NULL){
						m_lInfo.push_back(info);
					}
				}
				else if(sTageName == QString("Button"))
				{
					ButtonInfo btnInfo;
					btnInfo.pButton = NULL;
					CVisVAnalysisUIXML::AnalysisButton(childNode, btnInfo, this);

					if(btnInfo.pButton != NULL){
						QString sToDo = childNode.toElement().attributeNode("ToDo").value();
						btnInfo.pButton->setProperty("ToDo", sToDo);

						connect(btnInfo.pButton, SIGNAL(clicked()),
							this, SLOT(slot_OperBtn_Clicked()));

						m_lOperBtn.push_back(btnInfo);
					}
				}
				else if(sTageName == QString("CustomTblUI")){
					InitCustomTblUI(childNode);
				}			
			}

			childNode = childNode.nextSibling();
		}

	}
}

void CVisObjDownloadMgrUI::slot_OperBtn_Clicked()
{
	if (QPushButton* pBtn = dynamic_cast<QPushButton*>(sender())){

		QString sToDo = pBtn->property("ToDo").toString();
		if(sToDo == QString("ExitUI")){
			this->hide();
		}
		else{
			emit signal_OperBtn_ToDo(sToDo);
		}
	}
}

CVisCustomTableUI * CVisObjDownloadMgrUI::GetCurCustomTbl()
{
	return m_pCustomTblUI;
}

CVisObjDownloadMgrUI* CVisObjDownloadMgrUI::GetInstance()
{
	if(m_pObjDownloadMgrUI == NULL){
		m_pObjDownloadMgrUI = new CVisObjDownloadMgrUI;
		QString sPolicyFile = QString("/Resources/PatrolObject/Wnd/ObjItemDownloadMgr_UI.xml");
		m_pObjDownloadMgrUI->InitPolicyFile(sPolicyFile);

		CVisObjDownloadMgrUIObj *pBusObj = new CVisObjDownloadMgrUIObj(m_pObjDownloadMgrUI);
		m_pObjDownloadMgrUI->BindingBusObj(pBusObj);
	}

	return m_pObjDownloadMgrUI;
}

void CVisObjDownloadMgrUI::BindingBusObj(QObject *pBusObj)
{
	m_pBusObj = pBusObj;
}

QObject * CVisObjDownloadMgrUI::GetBindingBusObj()
{
	return m_pBusObj;
}

void CVisObjDownloadMgrUI::ShowMsgUI()
{
	if(CVisObjDownloadMgrUI::GetInstance() != NULL){
		CVisObjDownloadMgrUI::GetInstance()->show();
	}
}

//设置下载信息
void CVisObjDownloadMgrUI::SetDownloadInfo(const QStringList &lInfo)
{
	if(m_pCustomTblUI == NULL) return;

	m_pCustomTblUI->setRowCount(lInfo.size()-1);
	for(int i = 1; i < lInfo.size(); i++){
		QString sInfo = lInfo.at(i);

		QFileInfo fileInfo(sInfo);
		QTableWidgetItem *pFileNameItem = new QTableWidgetItem;
		pFileNameItem->setData(Qt::DisplayRole, fileInfo.fileName());
		pFileNameItem->setData(Qt::UserRole+1, sInfo);
		m_pCustomTblUI->setItem(i-1, 0, pFileNameItem);

		m_pCustomTblUI->CreateUIForRow(i-1, 1);

		m_pCustomTblUI->setRowHeight(i-1, m_pCustomTblUI->GetCustomRowHeight());
	}
}

void CVisObjDownloadMgrUI::paintEvent(QPaintEvent *event)
{
	QStyleOption opt; 
	opt.init(this); 
	QPainter p(this); 
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);

	QWidget::paintEvent(event);
}

void CVisObjDownloadMgrUI::InitCustomTblUI(const QDomNode &domNode)
{
	m_pCustomTblUI = new CVisCustomTableUI(this);
	CVisVAnalysisUIXML::InitBaseLayoutInfo(domNode, m_customTblUISize,
		m_sCustomTblUIAlgmt, m_pCustomTblUI);

	QString sPolicFile = domNode.toElement().attributeNode("PolicFile").value();
	m_pCustomTblUI->InitPolicy(sPolicFile);

	m_pCustomTblUI->setEditTriggers(QAbstractItemView::NoEditTriggers);	
	m_pCustomTblUI->setSelectionMode(QAbstractItemView::SingleSelection);
	m_pCustomTblUI->setSelectionBehavior(QAbstractItemView::SelectRows);	

	connect(m_pCustomTblUI, SIGNAL(signal_TblRow_ToDo(int, const QString &)),
		this, SLOT(slot_CustomTbl_OperBtn_ToDo(int, const QString &)));
}

void CVisObjDownloadMgrUI::slot_CustomTbl_OperBtn_ToDo(int nRow, const QString &sToDo)
{
	emit signal_CustomTbl_OperBtn_ToDo(nRow, sToDo);
}

void CVisObjDownloadMgrUI::mousePressEvent( QMouseEvent *event )
{
	//按住左键可以托动窗口  

	if (!m_bMove)
	{
		return;
	}
	QPoint pos = event->pos();
	if(event->button() == Qt::LeftButton)      
	{
		if (m_nTopHight >= pos.ry())
		{
			m_bCurFrameMoveState = true;
		}
		m_CurrentPos = event->globalPos() - frameGeometry().topLeft();      
		event->accept();
	} 
	QWidget::mousePressEvent(event);
}

void CVisObjDownloadMgrUI::mouseMoveEvent( QMouseEvent *event )
{
	if (!m_bMove)
	{
		return;
	}
	QPoint pos = event->pos();
	if (event->buttons() && Qt::LeftButton)      
	{ 
		if (m_bCurFrameMoveState)
		{
			move(event->globalPos() - m_CurrentPos);  
			event->accept(); 
		}   
	}

	QWidget::mouseMoveEvent(event);
}

void CVisObjDownloadMgrUI::mouseReleaseEvent( QMouseEvent *event )
{
	if (!m_bMove)
	{
		return;
	}
	m_bCurFrameMoveState = false;
	QPoint pos = event->pos();
	QPoint CurPos = this->pos();
	int nTop = CurPos.ry();
	int nLeft = CurPos.rx();
	bool bMove = false;
	if (CurPos.ry() < 0)
	{
		bMove = true;
		nTop = 0;
	}
	if (bMove)
	{
		move(nLeft, nTop);
	}

	QWidget::mouseReleaseEvent(event);
}