#ifndef FQtUiTool_H
#define FQtUiTool_H

#include "fqtuitool_global.h"
#include <QStringList>

class QWidget;
class QString;

class FQTUITOOL_EXPORT FQtUiTool
{
public:
	FQtUiTool();
	~FQtUiTool();

	static QWidget * CreateUI(const QString &sFileName, QStringList &lCustomUI = QStringList(), QWidget *parent = 0);
	static QWidget * CreateUIForPath(const QString &sFileName, QStringList &lCustomUI = QStringList(), QWidget *parent = 0);

private:

};

#endif // FQtUiTool_H
