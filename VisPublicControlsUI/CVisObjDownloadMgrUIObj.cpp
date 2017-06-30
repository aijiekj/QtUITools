#include "CVisObjDownloadMgrUIObj.h"
#include "CVisObjDownloadMgrUI.h"
#include <QTableWidgetItem>
#include <QDesktopServices>
#include <QUrl>

CVisObjDownloadMgrUIObj::CVisObjDownloadMgrUIObj(QObject *parent)
	: QObject(parent)
{
	m_pBindFrame = (CVisObjDownloadMgrUI*)parent;

	if(m_pBindFrame != NULL){
		connect(m_pBindFrame, SIGNAL(signal_OperBtn_ToDo(const QString &)),
			this, SLOT(slot_OperBtn_ToDo(const QString &)));
		connect(m_pBindFrame, SIGNAL(signal_CustomTbl_OperBtn_ToDo(int, const QString &)),
			this, SLOT(slot_CustomTbl_OperBtn_ToDo(int, const QString &)));


		m_pDownloadTbl = m_pBindFrame->GetCurCustomTbl();
		if(m_pDownloadTbl != NULL){
			connect(m_pDownloadTbl, SIGNAL(itemDoubleClicked(QTableWidgetItem *)),
				this, SLOT(slot_CustomTbl_ItemDoubleClicked(QTableWidgetItem *)));
		}
	}
}

CVisObjDownloadMgrUIObj::~CVisObjDownloadMgrUIObj()
{

}

void CVisObjDownloadMgrUIObj::slot_OperBtn_ToDo(const QString &sToDo)
{

}

void CVisObjDownloadMgrUIObj::slot_CustomTbl_OperBtn_ToDo(int nRow, const QString &sToDo)
{
	if(nRow < 0) return ;

	if(m_pDownloadTbl == NULL || m_pBindFrame == NULL) return;

	if(sToDo == QString("OpenFolder")){
		QTableWidgetItem *pItem = m_pDownloadTbl->item(nRow, 0);
		if(pItem != NULL){
			QString sFile = pItem->data(Qt::UserRole+1).toString();
			QFileInfo fileInfo(sFile);
			if(fileInfo.exists()){
				QString sFileDir = fileInfo.absolutePath();
				QDesktopServices::openUrl(QUrl(sFileDir, QUrl::TolerantMode));	
			}
			else{
				//文件不存在
			   	//QtCustomMsgBoxDLL::information(NULL, QStringLiteral("提示"), sFile);
			//	QtCustomMsgBoxDLL::information(NULL, QStringLiteral("提示"), QStringLiteral("该文件不存在！"));
			}		
		}		
	}
	else if(sToDo == QString("DelRow")){
		m_pDownloadTbl->removeRow(nRow);
	}
}

void CVisObjDownloadMgrUIObj::slot_CustomTbl_ItemDoubleClicked(QTableWidgetItem *pItem)
{
	if(pItem == NULL || m_pDownloadTbl == NULL) return;

	int nRow = pItem->row();
	QTableWidgetItem *pFileItem = m_pDownloadTbl->item(nRow, 0);

	if(pFileItem != NULL){
		QString sFile = pFileItem->data(Qt::UserRole +1).toString();
		QFileInfo fileInfo(sFile);
		if(fileInfo.exists()){
			QString sFileDir = fileInfo.absoluteFilePath();
			QDesktopServices::openUrl(QUrl(sFileDir, QUrl::TolerantMode));	
		}
		else{
			//QtCustomMsgBoxDLL::information(NULL, QStringLiteral("提示"), QStringLiteral("该文件不存在！"));
		}
	}
}
