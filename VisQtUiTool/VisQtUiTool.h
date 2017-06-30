#ifndef VISQTUITOOL_H
#define VISQTUITOOL_H

#include "visqtuitool_global.h"
#include <QStringList>

class QWidget;
class QString;

class VISQTUITOOL_EXPORT VisQtUiTool
{
public:
	VisQtUiTool();
	~VisQtUiTool();

	static QWidget * CreateUI(const QString &sFileName, QStringList &lCustomUI = QStringList(), QWidget *parent = 0);
	static QWidget * CreateUIForPath(const QString &sFileName, QStringList &lCustomUI = QStringList(), QWidget *parent = 0);

private:

};

#endif // VISQTUITOOL_H
