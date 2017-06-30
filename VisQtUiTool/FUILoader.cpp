#include "FUILoader.h"
#include <QDebug>

FUILoader::FUILoader(QObject *parent)
	: QUiLoader(parent)
{

}

FUILoader::~FUILoader()
{

}

QWidget * FUILoader::createWidget(const QString &className, QWidget *parent /*= Q_NULLPTR*/, const QString &name /*= QString()*/)
{
	QStringList lBaseClass = this->availableWidgets();
	QStringList lPluginPath = pluginPaths();

	qDebug() << "lPluginPath" << lPluginPath;

	if(lBaseClass.contains(className)){
		return QUiLoader::createWidget(className, parent, name);
	}
	else{
		QString sCustomUI = QString("%1:%2").arg(className).arg(name);
		if (!m_lCustomUI.contains(sCustomUI)){
			m_lCustomUI.push_back(sCustomUI);
		}
		return QUiLoader::createWidget(QString("QWidget"), parent, name);
	}
}
//
//QWidget * FUILoader::createCustomWidget(const QString &className, QWidget *parent /*= Q_NULLPTR*/, const QString &name /*= QString()*/)
//{
//	QWidget *pUI =  QUiLoader::createWidget(className, parent, name);
//	
//	if(className.compare(QString("QCustomDateTimeEdit")) == 0){
//		//create_QCustomDateTimeEdit(parent, name);
//	}
//	else if(className.compare(QString("QCustomTableViewDlg")) == 0){
//		//pUI create_QCustomTableViewDlg(parent, name);
//		Init_QCustomTableViewDlg(pUI);
//	}
//
//	return pUI;
//}
//
//QWidget * FUILoader::create_QCustomDateTimeEdit(QWidget *parent /*= Q_NULLPTR*/, const QString &name /*= QString()*/)
//{
//	QCustomDateTimeEdit *ui_ = new QCustomDateTimeEdit(parent);
//	ui_->setObjectName(name);
//
//	return ui_;
//}
//
//QWidget * FUILoader::create_QCustomTableViewDlg(QWidget *parent /*= Q_NULLPTR*/, const QString &name /*= QString()*/)
//{
//	QCustomTableViewDlg *ui_ = new QCustomTableViewDlg(parent);
//	ui_->setObjectName(name);
//
//	return ui_;
//}
//
//void FUILoader::Init_QCustomTableViewDlg(QWidget *pUI)
//{
//	if(pUI != NULL){
//		QString sPolicy = pUI->property("LayoutPolicy").toString();
//
//		QCustomTableViewDlg *pTblVew = qobject_cast<QCustomTableViewDlg*>(pUI);
//		if(pTblVew != NULL){
//
//			sPolicy = sPolicy.replace("_", "/");
//			QString strPolicyPath = QCoreApplication::applicationDirPath();
//			strPolicyPath.append(sPolicy);
//
//			QFile file(strPolicyPath);  
//			if(!file.open(QFile::ReadOnly | QFile::Text))
//			{  
//				
//				return ;
//			} 
//			QString strPolicy = QString(file.readAll());
//			file.close();
//			
//
//			pTblVew->InitLayoutPolicy(strPolicy);
//		}
//	}
//}
