#ifndef FUILOADER_H
#define FUILOADER_H

#include <QUiLoader>

class FUILoader : public QUiLoader
{
	Q_OBJECT

public:
	FUILoader(QObject *parent = Q_NULLPTR);
	~FUILoader();

	virtual QWidget *createWidget(const QString &className, QWidget *parent = Q_NULLPTR, const QString &name = QString());	
	QStringList GetCustomUI() { return m_lCustomUI; };


private:
	/*QWidget *createCustomWidget(const QString &className, QWidget *parent = Q_NULLPTR, const QString &name = QString());

	QWidget *create_QCustomDateTimeEdit(QWidget *parent = Q_NULLPTR, const QString &name = QString());
	QWidget *create_QCustomTableViewDlg(QWidget *parent = Q_NULLPTR, const QString &name = QString());
	void Init_QCustomTableViewDlg(QWidget *pUI);*/

private:
	QStringList				m_lCustomUI;
};

#endif // FUILOADER_H
