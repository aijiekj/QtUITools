/************************************************************************/
/*                        翻页界面类                                    */
/************************************************************************/
#ifndef CVISPAGETURNINGUI_H
#define CVISPAGETURNINGUI_H

#include <QWidget>
#include "vispubliccontrolsui_global.h"

class QPushButton;

class VISPUBLICCONTROLSUI_EXPORT CVisPageTurningUI : public QWidget
{
	Q_OBJECT

public:
	CVisPageTurningUI(QWidget *parent = 0, bool bLoadDefault = true);
	~CVisPageTurningUI();

	//初始化UI文件
	void InitUIFile(const QString &sFile);
	void UpdatePageInfo(int nCurPage, int nTotalPage);	//更新页码信息

signals:
	void signal_PageNumber(int nCurPage);

private:
	void InitOperBtnSignal(QWidget *pItemUI);	//初始化ItemUI操作按钮信号
	void PageTurningUI_OperBtn_ToDo(const QString &sToDo);	//按钮处理
	void UpatePageInfoLbl(int nCurPage, int nTotal);		//更新页签信息

	void SetGoOperUIVisible(bool bVisible);	//设置转到页功能可现
	void SetNumPageBtnVisible(int nTotalPage); //设置数字页按钮显示
	void GetNumberPageBtn(QList<QPushButton*> &lNumberBtn);	//获取数字按钮
	void SetCurrentPageBtn(int nCurPage);	//设置当前页码按钮
	bool CheckNumberPageBtn(QPushButton *pNumPageBtn, int nCampare);	//检测页码按钮

private slots:
	void slot_OperBtn_Clicked();

private:
	QWidget				*m_pUI;			//界面UI

	QString				m_sCurPageLblText;	//记录当前页签显示内容
	int					m_nCurPageIndex;	//当前页
	int					m_nTotalPage;		//总页数	
};

#endif // CVISPAGETURNINGUI_H
