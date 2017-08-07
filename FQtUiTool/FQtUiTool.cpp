#include "FQtUiTool.h"

#include <QWidget>
#include <QString>
#include <QFile>
#include <QCoreApplication>
#include <QStringList>

#include "FUILoader.h"

FQtUiTool::FQtUiTool()
{

}

FQtUiTool::~FQtUiTool()
{

}

QWidget * FQtUiTool::CreateUI(const QString &sFileName, QStringList &lCustomUI, QWidget *parent /*= 0*/)
{
	if(sFileName.isEmpty()) return NULL;

	QString sAppPath = QCoreApplication::applicationDirPath();
	sAppPath.append(sFileName);

	QFile file(sAppPath);
	if(!file.open(QFile::ReadOnly)) return NULL;

	FUILoader loader;
	QWidget *pWdgtUI = loader.load(&file, parent);
	file.close();

	lCustomUI = loader.GetCustomUI();

	return pWdgtUI;
}

QWidget * FQtUiTool::CreateUIForPath(const QString &sFileName, QStringList &lCustomUI, QWidget *parent /*= 0*/)
{
	if(sFileName.isEmpty()) return NULL;

	QFile file(sFileName);
	if(!file.open(QFile::ReadOnly)) return NULL;

	FUILoader loader;
	QWidget *pWdgtUI = loader.load(&file, parent);
	file.close();
	lCustomUI = loader.GetCustomUI();

	return pWdgtUI;
}
