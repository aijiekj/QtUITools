#include "CVisPageTurningUI.h"
#include <QVBoxLayout>
#include <QSpinBox>
#include <QLabel>
#include <QPushButton>

#include "VisQtUiTool.h"

CVisPageTurningUI::CVisPageTurningUI(QWidget *parent, bool bLoadDefault)
	: QWidget(parent)
{
	m_pUI = NULL;
	m_nCurPageIndex = -1;
	m_nTotalPage = -1;

	m_sCurPageLblText = QStringLiteral("当前页%1/%2");

	if(bLoadDefault){
		QString sUIFile = QString("/Resources/TestUI/custom_page_turning.ui");
		InitUIFile(sUIFile);
	}
}

CVisPageTurningUI::~CVisPageTurningUI()
{

}

//初始化UI文件
void CVisPageTurningUI::InitUIFile(const QString &sFile)
{
	m_pUI = VisQtUiTool::CreateUI(sFile);
	if(m_pUI == nullptr) return;
	InitOperBtnSignal(m_pUI);

	QLabel *pCurPageLbl = m_pUI->findChild<QLabel*>("CurPageInfoLbl");
	if(pCurPageLbl != NULL) {
		m_sCurPageLblText = pCurPageLbl->text();
	}

	QVBoxLayout *pMainLyt = new QVBoxLayout;
	pMainLyt->setMargin(0);
	pMainLyt->setSpacing(0);
	pMainLyt->addWidget(m_pUI);

	this->setLayout(pMainLyt);
}

//更新页码信息
void CVisPageTurningUI::UpdatePageInfo(int nCurPage, int nTotalPage)
{
	m_nTotalPage = nTotalPage;
	m_nCurPageIndex = nCurPage;
	if(nTotalPage > 0 && nCurPage <=0){
		m_nCurPageIndex = 1;
	}	

	//设置显示转到功能与否
	bool bGoVisible = nTotalPage > 10 ? true : false;
	SetGoOperUIVisible(bGoVisible);
	//设置数字按钮显示
	SetNumPageBtnVisible(m_nTotalPage);

	UpatePageInfoLbl(m_nCurPageIndex, m_nTotalPage);
	SetCurrentPageBtn(m_nCurPageIndex);
}

void CVisPageTurningUI::InitOperBtnSignal(QWidget *pItemUI)
{
	if(pItemUI == NULL) return;

	QList<QPushButton *> lOperBtn = pItemUI->findChildren<QPushButton *>();
	for(int i = 0; i < lOperBtn.size(); i++){
		if(lOperBtn.at(i) == NULL) continue;
		connect(lOperBtn.at(i), SIGNAL(clicked()),
			this, SLOT(slot_OperBtn_Clicked()));
	}
}

//按钮处理
void CVisPageTurningUI::PageTurningUI_OperBtn_ToDo(const QString &sToDo)
{
	if(sToDo.contains("PageNum_")){//数字数按钮
		QStringList lTmp = sToDo.split("_");
		if(lTmp.size() == 2){
			int nTmp = lTmp.at(1).toInt();	

			if(nTmp == m_nCurPageIndex){
				return;
			}
			else{
				m_nCurPageIndex = nTmp;
			}
		}
	}
	else if(sToDo == QString("HomePage")){	//首页
		if(m_nTotalPage > 0){
			if(m_nCurPageIndex == 1) return;
			m_nCurPageIndex = 1;
		}
	}
	else if(sToDo == QString("UpPage")){	//上一页
		m_nCurPageIndex--;
		if(m_nCurPageIndex <= 0 && m_nTotalPage > 1){
			m_nCurPageIndex = m_nTotalPage;
		}
	}
	else if(sToDo == QString("NextPage")){	//下一页
		m_nCurPageIndex++;
		if(m_nCurPageIndex > m_nTotalPage && m_nTotalPage > 1){
			m_nCurPageIndex = 1;
		}
	}
	else if(sToDo == QString("EndPage")){	//末页
		m_nCurPageIndex = m_nTotalPage;
	}
	else if(sToDo == QString("GoPage")){	//转到
		QSpinBox *pNumberSpBx = m_pUI->findChild<QSpinBox*>("NumberSpnBx");
		if(pNumberSpBx){
			int nTmp = pNumberSpBx->value();
			if(nTmp > 0 && nTmp <= m_nTotalPage){
				m_nCurPageIndex = nTmp;
			}
			else{
				return;
			}
		}
	}

	UpatePageInfoLbl(m_nCurPageIndex, m_nTotalPage);
	SetCurrentPageBtn(m_nCurPageIndex);

	emit signal_PageNumber(m_nCurPageIndex);
}

//更新页签信息
void CVisPageTurningUI::UpatePageInfoLbl(int nCurPage, int nTotal)
{
	if(m_pUI == NULL) return;
	bool bVisiable = true;
	if(nCurPage < 0 || nTotal <= 0){
		bVisiable = false;
	}

	QLabel *pCurInfoLbl = m_pUI->findChild<QLabel*>("CurPageInfoLbl");
	if(pCurInfoLbl == nullptr) return;
	pCurInfoLbl->setVisible(bVisiable);
	QString sText = m_sCurPageLblText;
	pCurInfoLbl->setText(sText.arg(nCurPage).arg(nTotal));

	QSpinBox *pNumberSpnBx = m_pUI->findChild<QSpinBox*>("NumberSpnBx");
	if(pNumberSpnBx != nullptr){
		pNumberSpnBx->setValue(nCurPage);
	}
}

//设置转到页功能可现
void CVisPageTurningUI::SetGoOperUIVisible(bool bVisible)
{
	if (m_pUI == nullptr) return;

	QPushButton *pHomePageBtn = m_pUI->findChild<QPushButton*>("HomePageBtn");
	if(pHomePageBtn != nullptr){
		pHomePageBtn->setVisible(bVisible);
	}

	QPushButton *pUpPageBtn = m_pUI->findChild<QPushButton*>("UpPageBtn");
	if(pUpPageBtn != nullptr){
		pUpPageBtn->setVisible(bVisible);
	}

	QPushButton *pNextPageBtn = m_pUI->findChild<QPushButton*>("NextPageBtn");
	if(pNextPageBtn != nullptr){
		pNextPageBtn->setVisible(bVisible);
	}

	QPushButton *pEndPageBtn = m_pUI->findChild<QPushButton*>("EndPageBtn");
	if(pEndPageBtn != nullptr){
		pEndPageBtn->setVisible(bVisible);
	}

	QSpinBox *pNumberSpnBx = m_pUI->findChild<QSpinBox*>("NumberSpnBx");
	if(pNumberSpnBx != nullptr){
		pNumberSpnBx->setVisible(bVisible);
	}

	QPushButton *pGoPageBtn = m_pUI->findChild<QPushButton*>("GoPageBtn");
	if(pGoPageBtn != nullptr){
		pGoPageBtn->setVisible(bVisible);
	}
}

//设置数字页按钮显示
void CVisPageTurningUI::SetNumPageBtnVisible(int nTotalPage)
{
	if(m_pUI == NULL) return;

	int nShowPage = 10;
	if(nShowPage > nTotalPage){
		nShowPage = nTotalPage;
	}
	
	QList<QPushButton *> lNumBtn;
	GetNumberPageBtn(lNumBtn);
	for(int i = 0; i < lNumBtn.size(); i++){
		QPushButton *pNumBtn = lNumBtn.at(i);
		if(pNumBtn != NULL){
			QString sObjName = pNumBtn->objectName();
			QStringList lTmp = sObjName.split("_");
			if(lTmp.size() == 2){
				int nTmp = lTmp.at(1).toInt();
				bool bIsVisible = nTotalPage >= nTmp ? true: false;
				pNumBtn->setVisible(bIsVisible);
			}			
		}
	}
}

//获取数字按钮
void CVisPageTurningUI::GetNumberPageBtn(QList<QPushButton*> &lNumberBtn)
{
	if(m_pUI == NULL) return;
	lNumberBtn = m_pUI->findChildren<QPushButton*>(QRegExp(QString("PageNumBtn_*")));
}

//设置当前页码按钮
void CVisPageTurningUI::SetCurrentPageBtn(int nCurPage)
{
	if(nCurPage > 10) return;

	QList<QPushButton*> lNumberBtn;
	GetNumberPageBtn(lNumberBtn);

	for(int i = 0; i < lNumberBtn.size(); i++){
		QPushButton *pNumBtn = lNumberBtn.at(i);
		if(pNumBtn != NULL){
			if(CheckNumberPageBtn(pNumBtn, nCurPage)){
				pNumBtn->setChecked(true);
				break;
			}
		}
	}
}

//检测页码按钮
bool CVisPageTurningUI::CheckNumberPageBtn(QPushButton *pNumPageBtn, int nCampare)
{
	bool bRsult = false;
	if(pNumPageBtn == NULL) return bRsult;

	QString sObjName = pNumPageBtn->objectName();
	QStringList lTmp = sObjName.split("_");
	if(lTmp.size() == 2){
		int nTmp = lTmp.at(1).toInt();
		bRsult = nCampare == nTmp ? true: false;
	}
	else{
		bRsult = false;
	}
	
	return bRsult;
}

void CVisPageTurningUI::slot_OperBtn_Clicked()
{
	if (QPushButton* pBtn = dynamic_cast<QPushButton*>(sender())){		
		QString sToDo = pBtn->property("ToDo").toString();		
		PageTurningUI_OperBtn_ToDo(sToDo);
	}
}
