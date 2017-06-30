/************************************************************************/
/*                      目标库下载管理界面业务类                        */
/************************************************************************/

#ifndef CVISOBJDOWNLOADMGRUIOBJ_H
#define CVISOBJDOWNLOADMGRUIOBJ_H

#include <QObject>

class CVisObjDownloadMgrUI;
class CVisCustomTableUI;
class QTableWidgetItem;

class CVisObjDownloadMgrUIObj : public QObject
{
	Q_OBJECT

public:
	CVisObjDownloadMgrUIObj(QObject *parent);
	~CVisObjDownloadMgrUIObj();

private slots:
	void slot_OperBtn_ToDo(const QString &sToDo);
	void slot_CustomTbl_OperBtn_ToDo(int nRow, const QString &sToDo);
	void slot_CustomTbl_ItemDoubleClicked(QTableWidgetItem *pItem);

private:
	CVisObjDownloadMgrUI		*m_pBindFrame;

	CVisCustomTableUI			*m_pDownloadTbl;
};

#endif // CVISOBJDOWNLOADMGRUIOBJ_H
