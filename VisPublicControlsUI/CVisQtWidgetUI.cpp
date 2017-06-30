#include "CVisQtWidgetUI.h"
#include <QVBoxLayout>
#include <QTextEdit>
#include <QComboBox>
#include <QPushButton>
#include <QLabel>
#include <QCheckBox>
#include <QStyledItemDelegate>
#include <QLineEdit>
#include <QAbstractItemView>
#include <QTabBar>
#include <QTabWidget>
#include <QTableView>
#include <QTableWidget>
#include <QListView>
#include <QListWidget>
#include <QTreeView>
#include <QTreeWidget>
#include <QAbstractItemView>
#include <QScrollBar>
#include <QStyledItemDelegate>
#include <QRadioButton> 
#include <QDateEdit>
#include <QTimeEdit>
#include <QDateTimeEdit>
#include <QDate>
#include <QTime>
#include <QDateTime>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QGroupBox>
#include <QProgressBar>
//#include <QWebEngineView>
//#include <QWebView>
#include <QStackedWidget>
#include <QScrollArea>
#include <QCalendarWidget> 

#include "VisQtUiTool.h"
#include <QDebug>

CVisQtWidgetUI::CVisQtWidgetUI(QWidget *parent)
	: QWidget(parent)
{
	m_pUI = nullptr;
	m_pBusObj = nullptr;

	setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinimizeButtonHint);
	setAttribute(Qt::WA_TranslucentBackground, true); 
}

CVisQtWidgetUI::~CVisQtWidgetUI()
{

}

//初始化界面UI
bool CVisQtWidgetUI::InitUIForFullPath(const QString &sUIFile)
{
	m_pUI = VisQtUiTool::CreateUIForPath(sUIFile, m_lCustomUI, this);
	if(m_pUI == nullptr) return false;

	qDebug() << "Custom UI List" << m_lCustomUI;

	//初始化界面信息
	InitItemUIInfo(m_pUI);

	QVBoxLayout *pMainLyt = new QVBoxLayout;
	pMainLyt->setMargin(0);
	pMainLyt->setSpacing(0);
	pMainLyt->addWidget(m_pUI);

	this->setLayout(pMainLyt);

	return true;
}

bool CVisQtWidgetUI::InitPolicyFileUI(const QString &sUIFile)
{
	m_pUI = VisQtUiTool::CreateUI(sUIFile, m_lCustomUI, this);
	if(m_pUI == nullptr) return false;

	InitItemUIInfo(m_pUI);

	QVBoxLayout *pMainLyt = new QVBoxLayout;
	pMainLyt->setMargin(0);
	pMainLyt->setSpacing(0);
	pMainLyt->addWidget(m_pUI);

	this->setLayout(pMainLyt);

	return true;
}

//初始化ItemUI基础控件
void CVisQtWidgetUI::InitItemUIInfo(QWidget * pItemUI)
{
	InitOperBtnSignal(pItemUI);			//初始化Btn
	InitComboBoxInfo(pItemUI);				//初始化ComBoBx信息
	InitTabBarInfo(pItemUI);				//初始化TabBar信息	
	InitTabWidgetInfo(pItemUI);			//初始化TabWidget信息
	InitLineEdit(pItemUI);				//初始化QLineEdit
	InitCheckBox(pItemUI);				//初始化CheckBox
	InitRadioButton(pItemUI);				//初始化RadioBtn
	InitSlider(pItemUI);					//初始化Slider
	InitDateEditor(pItemUI);				//初始化DateEdtor
	InitTimeEditor(pItemUI);				//初始化TimeEdtor
	InitDateTimeEdtor(pItemUI);			//初始化DateTimeEdtor
	InitDoubleSpinBox(pItemUI);			//初始化DoubleSpBx
	InitSpinBox(pItemUI);					//初始化SpinBox
	InitGroupBox(pItemUI);				//初始化GroupBox
	InitProgressBar(pItemUI);				//初始化ProgressBar
	InitWebView(pItemUI);					//初始化WebView
	InitStackedWidgt(pItemUI);			//初始化StackedWgt
	InitScrollArea(pItemUI);				//初始化ScrollArea
	InitCalendarWidget(pItemUI);			//初始化CalendarWgt

	//表格相关
	InitTableViewInfo(pItemUI);			//初始化QTableView信息
	InitListViewInfo(pItemUI);			//初始化QListView
	InitTreeViewInfo(pItemUI);			//初始化QTreeView
	InitTableWidgetInfo(pItemUI);			//初始化QTableWidget
	InitListWidgetInfo(pItemUI);			//初始化QListWidget
	InitTreeWidgetInfo(pItemUI);			//初始化QTreeWidget

	//自定义控件
	InitCustomUI();
}

void CVisQtWidgetUI::InitOperBtnSignal(QWidget *pItemUI)
{
	if(pItemUI == NULL) return;

	QList<QPushButton *> lOperBtn = pItemUI->findChildren<QPushButton *>();

	for(int i = 0; i < lOperBtn.size(); i++){
		if(lOperBtn.at(i) == NULL) continue;
		connect(lOperBtn.at(i), SIGNAL(clicked()),
			this, SLOT(slot_ItemUi_OperBtn_Clicked()));
	}
}

void CVisQtWidgetUI::slot_ItemUi_OperBtn_Clicked()
{
	if (QPushButton* pBtn = dynamic_cast<QPushButton*>(sender())){
		QString sToDo = pBtn->property("ToDo").toString();
		emit signal_OperBtn_ToDo(sToDo);
	}
}

void CVisQtWidgetUI::InitComboBoxInfo(QWidget *pUI)
{
	if(pUI == NULL) return;

	QList<QComboBox *> lComboBx = pUI->findChildren<QComboBox *>();

	for(int i = 0; i < lComboBx.size(); i++){
		QComboBox *pItemComBox = lComboBx.at(i);
		if(pItemComBox == NULL) continue;

		QAbstractItemView *pItemView = pItemComBox->view();
		if(pItemView != nullptr){
			pItemView->setFocusPolicy(Qt::NoFocus);
			pItemView->viewport()->setFocusPolicy(Qt::NoFocus);
		}

		QStyledItemDelegate *delegate = new QStyledItemDelegate();
		pItemComBox->setItemDelegate(delegate);

		QStringList lItemInfo = pItemComBox->property("Item").toStringList();
		for(int j = 0; j < lItemInfo.size(); j++){
			QString sInfo = lItemInfo.at(j);
			QStringList lTmp = sInfo.split("=");
			if(lTmp.size() >= 2){
				pItemComBox->addItem(lTmp.at(0), lTmp.at(1));
			}
			else{
				pItemComBox->addItem(sInfo);
			}			
		}		
	}
}

void CVisQtWidgetUI::InitTabBarInfo(QWidget * pItemUI)
{
	if (pItemUI == NULL) return;

	QList<QTabBar *> lTabBar = pItemUI->findChildren<QTabBar *>();

	for (int i = 0; i < lTabBar.size(); i++) {
		if (lTabBar.at(i) == NULL) continue;
		connect(lTabBar.at(i), SIGNAL(currentChanged(int)),
			this, SIGNAL(signal_TabBar_CurrentChanged(int)));
		connect(lTabBar.at(i), SIGNAL(tabBarClicked(int)),
			this, SIGNAL(signal_TabBar_TabBarClicked(int)));
		connect(lTabBar.at(i), SIGNAL(tabBarDoubleClicked(int)),
			this, SIGNAL(signal_TabBar_TabBarDoubleClicked(int)));
		connect(lTabBar.at(i), SIGNAL(tabCloseRequested(int)),
			this, SIGNAL(signal_TabBar_TabCloseRequested(int)));
	}
}

//初始化TabWidget信息
void CVisQtWidgetUI::InitTabWidgetInfo(QWidget * pItemUI)
{
	if (pItemUI == NULL) return;

	QList<QTabWidget *> lTabWgtUI = pItemUI->findChildren<QTabWidget *>();

	for (int i = 0; i < lTabWgtUI.size(); i++) {
		if (lTabWgtUI.at(i) == NULL) continue;
		connect(lTabWgtUI.at(i), SIGNAL(currentChanged(int)),
			this, SIGNAL(signal_TabBar_CurrentChanged(int)));
		connect(lTabWgtUI.at(i), SIGNAL(tabBarClicked(int)),
			this, SIGNAL(signal_TabBar_TabBarClicked(int)));
		connect(lTabWgtUI.at(i), SIGNAL(tabBarDoubleClicked(int)),
			this, SIGNAL(signal_TabBar_TabBarDoubleClicked(int)));
		connect(lTabWgtUI.at(i), SIGNAL(tabCloseRequested(int)),
			this, SIGNAL(signal_TabBar_TabCloseRequested(int)));
	}
}

//初始化QLineEdit
void CVisQtWidgetUI::InitLineEdit(QWidget * pItemUI)
{
	if (pItemUI == NULL) return;

	QList<QLineEdit *> lEditor = pItemUI->findChildren<QLineEdit *>();

	for (int i = 0; i < lEditor.size(); i++) {
		if (lEditor.at(i) == NULL) continue;

		connect(lEditor.at(i), SIGNAL(editingFinished()),
			this, SIGNAL(signal_LineEdit_EditingFinished()));
		connect(lEditor.at(i), SIGNAL(returnPressed()),
			this, SIGNAL(signal_LineEdit_ReturnPressed()));
		connect(lEditor.at(i), SIGNAL(textChanged(const QString &)),
			this, SIGNAL(signal_LineEdit_TextChanged(const QString &)));
	}
}

//初始化CheckBox
void CVisQtWidgetUI::InitCheckBox(QWidget * pItemUI)
{
	if (pItemUI == NULL) return;

	QList<QCheckBox *> lCheckBx = pItemUI->findChildren<QCheckBox *>();

	for (int i = 0; i < lCheckBx.size(); i++) {
		if (lCheckBx.at(i) == NULL) continue;

		connect(lCheckBx.at(i), SIGNAL(stateChanged(int)),
			this, SIGNAL(signal_ChekBox_StateChanged(int)));
	}
}

//初始化RadioBtn
void CVisQtWidgetUI::InitRadioButton(QWidget * pItemUI)
{
	if (pItemUI == NULL) return;

	QList<QRadioButton *> lRdBtn = pItemUI->findChildren<QRadioButton *>();

	for (int i = 0; i < lRdBtn.size(); i++) {
		if (lRdBtn.at(i) == NULL) continue;

		connect(lRdBtn.at(i), SIGNAL(clicked()),
			this, SLOT(slot_ItemUi_OperBtn_Clicked()));
	}
}

//初始化Slider
void CVisQtWidgetUI::InitSlider(QWidget * pItemUI)
{
	if (pItemUI == NULL) return;

	QList<QSlider *> lSlider = pItemUI->findChildren<QSlider *>();

	for (int i = 0; i < lSlider.size(); i++) {
		if (lSlider.at(i) == NULL) continue;

		connect(lSlider.at(i), SIGNAL(actionTriggered(int)),
			this, SIGNAL(signal_Slider_ActionTriggered(int)));
		connect(lSlider.at(i), SIGNAL(rangeChanged(int, int)),
			this, SIGNAL(signal_Slider_RangeChanged(int, int)));
		connect(lSlider.at(i), SIGNAL(sliderMoved(int)),
			this, SIGNAL(signal_Slider_SliderMoved(int)));
		connect(lSlider.at(i), SIGNAL(sliderPressed()),
			this, SIGNAL(signal_Slider_SliderPressed()));
		connect(lSlider.at(i), SIGNAL(sliderReleased()),
			this, SIGNAL(signal_Slider_SliderReleased()));
		connect(lSlider.at(i), SIGNAL(valueChanged(int)),
			this, SIGNAL(signal_Slider_ValueChanged(int)));		
	}
}

//初始化DateEdtor
void CVisQtWidgetUI::InitDateEditor(QWidget * pItemUI)
{
	if (pItemUI == NULL) return;

	QList<QDateEdit *> lDateEdtor = pItemUI->findChildren<QDateEdit *>();

	for (int i = 0; i < lDateEdtor.size(); i++) {
		if (lDateEdtor.at(i) == NULL) continue;

		InitDatetimeEditor(lDateEdtor.at(i));
	}
}

//初始化TimeEdtor
void CVisQtWidgetUI::InitTimeEditor(QWidget * pItemUI)
{
	if (pItemUI == NULL) return;

	QList<QTimeEdit *> lTimeEdtor = pItemUI->findChildren<QTimeEdit *>();

	for (int i = 0; i < lTimeEdtor.size(); i++) {
		if (lTimeEdtor.at(i) == NULL) continue;

		InitDatetimeEditor(lTimeEdtor.at(i));
	}
}

//初始化DateTimeEdtor
void CVisQtWidgetUI::InitDateTimeEdtor(QWidget * pItemUI)
{
	QList<QDateTimeEdit *> lDateTimeEdtor = pItemUI->findChildren<QDateTimeEdit *>();

	for (int i = 0; i < lDateTimeEdtor.size(); i++) {
		if (lDateTimeEdtor.at(i) == NULL) continue;

		InitDatetimeEditor(lDateTimeEdtor.at(i));
	}
}

//初始化QDateTimeEdit
void CVisQtWidgetUI::InitDatetimeEditor(QDateTimeEdit * pEdtor)
{
	if (pEdtor == nullptr) return;

	connect(pEdtor, SIGNAL(dateChanged(const QDate &)),
		this, SIGNAL(signal_DateTimeEdtor_DateChanged(const QDate &)));
	connect(pEdtor, SIGNAL(dateTimeChanged(const QDateTime &)),
		this, SIGNAL(signal_DateTimeEdtor_DateTimeChanged(const QDateTime &)));
	connect(pEdtor, SIGNAL(timeChanged(const QTime &)),
		this, SIGNAL(signal_DateTimeEdtor_TimeChanged(const QTime &)));
	connect(pEdtor, SIGNAL(editingFinished()),
		this, SIGNAL(signal_DateTimeEdotr_EditingFinished()));	
}

//初始化DoubleSpBx
void CVisQtWidgetUI::InitDoubleSpinBox(QWidget * pItemUI)
{
	if (pItemUI == NULL) return;

	QList<QDoubleSpinBox *> lDoubleSpinBx = pItemUI->findChildren<QDoubleSpinBox *>();

	for (int i = 0; i < lDoubleSpinBx.size(); i++) {
		if (lDoubleSpinBx.at(i) == NULL) continue;
		connect(lDoubleSpinBx.at(i), SIGNAL(editingFinished()),
			this, SIGNAL(signal_SpinBox_EditingFinished()));
		connect(lDoubleSpinBx.at(i), SIGNAL(valueChanged(const QString &)),
			this, SIGNAL(signal_SpinBox_ValueChanged(const QString &)));
		connect(lDoubleSpinBx.at(i), SIGNAL(valueChanged(double)),
			this, SIGNAL(signal_SpinBox_ValueChanged(double)));
	}
}

//初始化SpinBox
void CVisQtWidgetUI::InitSpinBox(QWidget * pItemUI)
{
	if (pItemUI == NULL) return;

	QList<QSpinBox *> lSpinBx = pItemUI->findChildren<QSpinBox *>();

	for (int i = 0; i < lSpinBx.size(); i++) {
		if (lSpinBx.at(i) == NULL) continue;
		connect(lSpinBx.at(i), SIGNAL(editingFinished()),
			this, SIGNAL(signal_SpinBox_EditingFinished()));
		connect(lSpinBx.at(i), SIGNAL(valueChanged(const QString &)),
			this, SIGNAL(signal_SpinBox_ValueChanged(const QString &)));
		connect(lSpinBx.at(i), SIGNAL(valueChanged(int)),
			this, SIGNAL(signal_SpinBox_ValueChanged(int)));
	}
}

//初始化GroupBox
void CVisQtWidgetUI::InitGroupBox(QWidget * pItemUI)
{
	if (pItemUI == NULL) return;

	QList<QGroupBox *> lGroupBx = pItemUI->findChildren<QGroupBox *>();

	for (int i = 0; i < lGroupBx.size(); i++) {
		if (lGroupBx.at(i) == NULL) continue;
		connect(lGroupBx.at(i), SIGNAL(clicked(bool)),
			this, SIGNAL(signal_GroupBox_Clicked(bool)));
		connect(lGroupBx.at(i), SIGNAL(toggled(bool)),
			this, SIGNAL(signal_GroupBox_Toggled(bool)));
	}
}

//初始化ProgressBar
void CVisQtWidgetUI::InitProgressBar(QWidget * pItemUI)
{
	if (pItemUI == NULL) return;

	QList<QProgressBar *> lProGressBar = pItemUI->findChildren<QProgressBar *>();

	for (int i = 0; i < lProGressBar.size(); i++) {
		if (lProGressBar.at(i) == NULL) continue;
		connect(lProGressBar.at(i), SIGNAL(valueChanged(int)),
			this, SIGNAL(signal_ProgressBar_ValueChanged(int)));
	}
}

//初始化WebView
void CVisQtWidgetUI::InitWebView(QWidget * pItemUI)
{
	if (pItemUI == NULL) return;
//
//#if (QT_VERSION >= QT_VERSION_CHECK(5, 5, 1))
//	QList<QWebEngineView *> lWebEngVew = pItemUI->findChildren<QWebEngineView *>();
//
//	for (int i = 0; i < lWebEngVew.size(); i++) {
//		if (lWebEngVew.at(i) == NULL) continue;
//		connect(lWebEngVew.at(i), SIGNAL(loadFinished(bool)),
//			this, SIGNAL(signal_WebView_LoadFinished(bool)));
//		connect(lWebEngVew.at(i), SIGNAL(loadProgress(int)),
//			this, SIGNAL(signal_WebView_LoadProgress(int)));
//		connect(lWebEngVew.at(i), SIGNAL(loadStarted()),
//			this, SIGNAL(signal_WebView_LoadStarted()));
//		connect(lWebEngVew.at(i), SIGNAL(urlChanged(const QUrl &)),
//			this, SIGNAL(signal_WebView_UrlChanged(const QUrl &)));
//	}
//
//#else
//	QList<QWebView *> lWebView = pItemUI->findChildren<QWebView *>();
//
//	for (int i = 0; i < lWebView.size(); i++) {
//		if (lWebView.at(i) == NULL) continue;
//		connect(lWebView.at(i), SIGNAL(loadFinished(bool)),
//			this, SIGNAL(signal_WebView_LoadFinished(bool)));
//		connect(lWebView.at(i), SIGNAL(loadProgress(int)),
//			this, SIGNAL(signal_WebView_LoadProgress(int)));
//		connect(lWebView.at(i), SIGNAL(loadStarted()),
//			this, SIGNAL(signal_WebView_LoadStarted()));
//		connect(lWebView.at(i), SIGNAL(urlChanged(const QUrl &)),
//			this, SIGNAL(signal_WebView_UrlChanged(const QUrl &)));
//	}
//
//#endif
}

//初始化StackedWgt
void CVisQtWidgetUI::InitStackedWidgt(QWidget * pItemUI)
{
	if (pItemUI == NULL) return;

	QList<QStackedWidget *> lStackWgt = pItemUI->findChildren<QStackedWidget *>();

	for (int i = 0; i < lStackWgt.size(); i++) {
		if (lStackWgt.at(i) == NULL) continue;

		connect(lStackWgt.at(i), SIGNAL(currentChanged(int)),
			this, SIGNAL(signal_StackWgt_CurrentChanged(int)));
		connect(lStackWgt.at(i), SIGNAL(widgetRemoved(int)),
			this, SIGNAL(signal_StackWgt_WidgetRemoved(int)));
	}
}

//初始化ScrollArea
void CVisQtWidgetUI::InitScrollArea(QWidget * pItemUI)
{
	if (pItemUI == NULL) return;

	QList<QScrollArea *> lScrollArea = pItemUI->findChildren<QScrollArea *>();

	for (int i = 0; i < lScrollArea.size(); i++) {
		if (lScrollArea.at(i) == NULL) continue;

		lScrollArea.at(i)->horizontalScrollBar()->setContextMenuPolicy(Qt::NoContextMenu);
		lScrollArea.at(i)->verticalScrollBar()->setContextMenuPolicy(Qt::NoContextMenu);
	}
}

//初始化CalendarWgt
void CVisQtWidgetUI::InitCalendarWidget(QWidget * pItemUI)
{
	if (pItemUI == NULL) return;

	QList<QCalendarWidget *> lCalendarWgt = pItemUI->findChildren<QCalendarWidget *>();

	for (int i = 0; i < lCalendarWgt.size(); i++) {
		if (lCalendarWgt.at(i) == NULL) continue;

		connect(lCalendarWgt.at(i), SIGNAL(activated(const QDate &)),
			this, SIGNAL(signal_CalendarWgt_Activated(const QDate &)));
		connect(lCalendarWgt.at(i), SIGNAL(clicked(const QDate &)),
			this, SIGNAL(signal_CalendarWgt_Clicked(const QDate &)));
		connect(lCalendarWgt.at(i), SIGNAL(currentPageChanged(int, int)),
			this, SIGNAL(signal_CalendarWgt_CurrentPageChanged(int, int)));
		connect(lCalendarWgt.at(i), SIGNAL(selectionChanged()),
			this, SIGNAL(signal_CalendarWgt_SelectionChanged()));
	}
}

//初始化QTableView信息
void CVisQtWidgetUI::InitTableViewInfo(QWidget * pItemUI)
{
	if (pItemUI == NULL) return;

	QList<QTableView *> lTablView = pItemUI->findChildren<QTableView *>();

	for (int i = 0; i < lTablView.size(); i++) {
		if (lTablView.at(i) == NULL) continue;
		
		InitAbstractItemViewInfo(lTablView.at(i));		
	}
}

//初始化QListView
void CVisQtWidgetUI::InitListViewInfo(QWidget * pItemUI)
{
	if (pItemUI == NULL) return;

	QList<QListView *> lView = pItemUI->findChildren<QListView *>();

	for (int i = 0; i < lView.size(); i++) {
		if (lView.at(i) == NULL) continue;

		InitAbstractItemViewInfo(lView.at(i));
	}
}

//初始化QTreeView
void CVisQtWidgetUI::InitTreeViewInfo(QWidget * pItemUI)
{
	if (pItemUI == NULL) return;

	QList<QTreeView *> lView = pItemUI->findChildren<QTreeView *>();

	for (int i = 0; i < lView.size(); i++) {
		if (lView.at(i) == NULL) continue;

		InitAbstractItemViewInfo(lView.at(i));
		connect(lView.at(i), SIGNAL(collapsed(const QModelIndex &)),
			this, SIGNAL(signal_TreeView_Collapsed(const QModelIndex &)));
		connect(lView.at(i), SIGNAL(expanded(const QModelIndex &)),
			this, SIGNAL(signal_TreeView_Expanded(const QModelIndex &)));
	}
}

//初始化QTableWidget
void CVisQtWidgetUI::InitTableWidgetInfo(QWidget * pItemUI)
{
	if (pItemUI == NULL) return;

	QList<QTableWidget *> lView = pItemUI->findChildren<QTableWidget *>();

	for (int i = 0; i < lView.size(); i++) {
		if (lView.at(i) == NULL) continue;

		InitAbstractItemViewInfo(lView.at(i));

		connect(lView.at(i), SIGNAL(itemClicked(QTableWidgetItem *)),
			this, SIGNAL(signal_TblWgt_ItemClicked(QTableWidgetItem *)));
		connect(lView.at(i), SIGNAL(itemDoubleClicked(QTableWidgetItem *)),
			this, SIGNAL(signal_TblWgt_ItemDoubleClicked(QTableWidgetItem *)));
		connect(lView.at(i), SIGNAL(itemPressed(QTableWidgetItem *)),
			this, SIGNAL(signal_TblWgt_ItemPressed(QTableWidgetItem *)));
		connect(lView.at(i), SIGNAL(cellClicked(int, int)),
			this, SIGNAL(signal_TblWgt_CellClicked(int, int)));
		connect(lView.at(i), SIGNAL(cellDoubleClicked(int, int)),
			this, SIGNAL(signal_TblWgt_CellDoubleClicked(int, int)));
		connect(lView.at(i), SIGNAL(cellPressed(int, int)),
			this, SIGNAL(gignal_TblWgt_CellPressed(int, int)));
	}
}

//初始化QListWidget
void CVisQtWidgetUI::InitListWidgetInfo(QWidget * pItemUI)
{
	if (pItemUI == NULL) return;

	QList<QListWidget *> lView = pItemUI->findChildren<QListWidget *>();

	for (int i = 0; i < lView.size(); i++) {
		if (lView.at(i) == NULL) continue;

		InitAbstractItemViewInfo(lView.at(i));

		connect(lView.at(i), SIGNAL(itemClicked(QListWidgetItem *)),
			this, SIGNAL(signal_ListWgt_ItemClicked(QListWidgetItem *)));
		connect(lView.at(i), SIGNAL(itemDoubleClicked(QListWidgetItem *)),
			this, SIGNAL(signal_ListWgt_ItemDoubleClicked(QListWidgetItem *)));
		connect(lView.at(i), SIGNAL(itemPressed(QListWidgetItem *)),
			this, SIGNAL(signal_ListWgt_ItemPressed(QListWidgetItem *)));
	}
}

//初始化QTreeWidget
void CVisQtWidgetUI::InitTreeWidgetInfo(QWidget * pItemUI)
{
	if (pItemUI == NULL) return;

	QList<QTreeWidget *> lView = pItemUI->findChildren<QTreeWidget *>();

	for (int i = 0; i < lView.size(); i++) {
		if (lView.at(i) == NULL) continue;

		InitAbstractItemViewInfo(lView.at(i));

		connect(lView.at(i), SIGNAL(itemClicked(QTreeWidgetItem *, int)),
			this, SIGNAL(signal_TreeWgt_ItemClicked(QTreeWidgetItem *, int)));
		connect(lView.at(i), SIGNAL(itemDoubleClicked(QTreeWidgetItem *, int)),
			this, SIGNAL(signal_TreeWgt_ItemDoubleClicked(QTreeWidgetItem *, int)));
		connect(lView.at(i), SIGNAL(itemPressed(QTreeWidgetItem *, int)),
			this, SIGNAL(signal_TreeWgt_ItemPressed(QTreeWidgetItem *, int)));
		connect(lView.at(i), SIGNAL(itemEntered(QTreeWidgetItem *, int)),
			this, SIGNAL(signal_TreeWgt_ItemEntered(QTreeWidgetItem *, int)));
		connect(lView.at(i), SIGNAL(itemExpanded(QTreeWidgetItem *)),
			this, SIGNAL(signal_TreeWgt_ItemExpanded(QTreeWidgetItem *)));
		connect(lView.at(i), SIGNAL(itemCollapsed(QTreeWidgetItem *)),
			this, SIGNAL(signal_TreeWgt_ItemCollapsed(QTreeWidgetItem *)));
	}
}

//初始化QAbstractItemView
void CVisQtWidgetUI::InitAbstractItemViewInfo(QAbstractItemView * pView)
{
	if (pView == nullptr) return;

	pView->horizontalScrollBar()->setContextMenuPolicy(Qt::NoContextMenu);
	pView->verticalScrollBar()->setContextMenuPolicy(Qt::NoContextMenu);
	//屏蔽子项的虚线
	pView->viewport()->setFocusPolicy(Qt::NoFocus);

	QStyledItemDelegate *delegate = new QStyledItemDelegate();
	pView->setItemDelegate(delegate);

	connect(pView, SIGNAL(clicked(const QModelIndex &)),
		this, SIGNAL(signal_View_Clicked(const QModelIndex &)));
	connect(pView, SIGNAL(doubleClicked(const QModelIndex &)),
		this, SIGNAL(signal_View_DoubleClicked(const QModelIndex &)));
	connect(pView, SIGNAL(pressed(const QModelIndex &)),
		this, SIGNAL(signal_View_Pressed(const QModelIndex &)));
}

//初始化自定义控件
void CVisQtWidgetUI::InitCustomUI()
{
	for (int i = 0; i < m_lCustomUI.size(); i++) {
		QString sCustomUI = m_lCustomUI.at(i);
		QStringList lCustomUIInfo = sCustomUI.split(":");
		if (lCustomUIInfo.size() == 2) {
			QString sClassName = lCustomUIInfo.at(0);
			QString sObjName = lCustomUIInfo.at(1);

			if (sClassName == "VisCustomTbl") {
				QCalendarWidget *pItemUI = new QCalendarWidget;
				SetCustomUI(pItemUI, sObjName);
			}
		}
	}
}

void CVisQtWidgetUI::SetCustomUI(QWidget * pItmeUI, const QString & sObjName)
{
	if (pItmeUI == nullptr || sObjName.isEmpty()) return;
	if (m_pUI == nullptr) return;

	QWidget *pCustomUI = m_pUI->findChild<QWidget*>(sObjName);
	if (pCustomUI == nullptr) return;

	pItmeUI->setParent(pCustomUI);
	
	QVBoxLayout *pCustomUILyt = new QVBoxLayout;
	pCustomUILyt->setSpacing(0);
	pCustomUILyt->setMargin(0);
	pCustomUILyt->addWidget(pItmeUI);

	pCustomUI->setLayout(pCustomUILyt);
}

void CVisQtWidgetUI::BindBusiness(QObject *pObj)
{
	m_pBusObj = pObj;
}

QObject * CVisQtWidgetUI::GetBindBusiness()
{
	return m_pBusObj;
}

//获取PushButton
QPushButton * CVisQtWidgetUI::GetPushButton(const QString &sObjName)
{
	if (m_pUI == nullptr) return nullptr;

	QPushButton *pBtn = m_pUI->findChild<QPushButton *>(sObjName);
	if (pBtn == nullptr) return nullptr;

	return pBtn;
}

//获取当前ComboBox显示信息
QString CVisQtWidgetUI::GetComboBoxCurShowText(const QString &sName)
{
	QString sReustInfo = QString();

	if(m_pUI == nullptr) return sReustInfo;

	QComboBox *pCmBx = m_pUI->findChild<QComboBox *>(sName);
	if(pCmBx == nullptr) return sReustInfo;

	sReustInfo = pCmBx->currentText();

	return sReustInfo;
}

//获取ComBoBox
QComboBox * CVisQtWidgetUI::GetComboBox(const QString & sObjName)
{
	if (m_pUI == nullptr) return nullptr;

	QComboBox *pComboBox = m_pUI->findChild<QComboBox *>(sObjName);
	if (pComboBox == nullptr) return nullptr;

	return pComboBox;
}

QString CVisQtWidgetUI::GetCurrComboBoxInfo(const QString &sName)
{
	QString sReustInfo = QString();

	if(m_pUI == nullptr) return sReustInfo;

	QComboBox *pCmBx = m_pUI->findChild<QComboBox *>(sName);
	if(pCmBx == nullptr) return sReustInfo;

	sReustInfo = pCmBx->currentData().toString();

	return sReustInfo;
}

//获取当前ComboBoxIndex
int CVisQtWidgetUI::GetComboBoxCurIndex(const QString &sName)
{
	int nIndex = -1;

	if(m_pUI == nullptr) return -1;

	QComboBox *pCmBx = m_pUI->findChild<QComboBox *>(sName);
	if(pCmBx == nullptr) return -1;

	nIndex = pCmBx->currentIndex();

	return nIndex;
}

//获取LineEdit
QLineEdit * CVisQtWidgetUI::GetLineEdit(const QString & sObjName)
{
	if (m_pUI == nullptr) return nullptr;

	QLineEdit *pLineEdit = m_pUI->findChild<QLineEdit *>(sObjName);
	if (pLineEdit == nullptr) return nullptr;

	return pLineEdit;
}

QString CVisQtWidgetUI::GetLineEditInfo(const QString &sName)
{
	QString sReustInfo = QString();

	if(m_pUI == nullptr) return sReustInfo;

	QLineEdit *pEditor = m_pUI->findChild<QLineEdit *>(sName);
	if(pEditor == nullptr) return sReustInfo;

	sReustInfo = pEditor->text();

	return sReustInfo;
}

void CVisQtWidgetUI::SetLineEditInfo(const QString &sName, const QString &sInfo)
{
	if(m_pUI == nullptr) return ;

	QLineEdit *pEditor = m_pUI->findChild<QLineEdit *>(sName);
	if(pEditor == nullptr) return;

	pEditor->setText(sInfo);
}

//获取TextBrowser
QTextEdit * CVisQtWidgetUI::GetTextBrowser(const QString & sObjName)
{
	if (m_pUI == nullptr) return nullptr;

	QTextEdit *pTextEdit = m_pUI->findChild<QTextEdit *>(sObjName);
	if (pTextEdit == nullptr) return nullptr;

	return pTextEdit;
}

//获取TextBrowserInfo
QString CVisQtWidgetUI::GetTextBrowserInfo(const QString &sName)
{
	QString sReustInfo = QString();

	if(m_pUI == nullptr) return sReustInfo;

	QTextEdit *pTextBrowser = m_pUI->findChild<QTextEdit *>(sName);
	if(pTextBrowser == nullptr) return sReustInfo;

	sReustInfo = pTextBrowser->toPlainText();

	return sReustInfo;
}

//设置TextBrowserInfo
void CVisQtWidgetUI::SetTextBrowserInfo(const QString &sName, const QString &sInfo)
{
	if(m_pUI == nullptr) return;

	QTextEdit *pTextBrowser = m_pUI->findChild<QTextEdit *>(sName);
	if(pTextBrowser == nullptr) return;

	pTextBrowser->setPlainText(sInfo);
}

//获取CheckBox
QCheckBox * CVisQtWidgetUI::GetCheckBox(const QString & sObjName)
{
	if (m_pUI == nullptr) return nullptr;

	QCheckBox *pChekBox = m_pUI->findChild<QCheckBox *>(sObjName);
	if (pChekBox == nullptr) return nullptr;

	return pChekBox;
}

//获取CheckBox状态
bool CVisQtWidgetUI::GetCheckBoxCheckStatus(const QString &sName)
{
	bool bCheckFlg = false;

	if(m_pUI == nullptr) return bCheckFlg;

	QCheckBox *pCheckBox = m_pUI->findChild<QCheckBox *>(sName);
	if(pCheckBox == nullptr) return bCheckFlg;

	bCheckFlg = pCheckBox->isChecked();

	return bCheckFlg;
}

//获取Label
QLabel * CVisQtWidgetUI::GetLable(const QString & sObjName)
{
	if (m_pUI == nullptr) return nullptr;

	QLabel *pLablInfo = m_pUI->findChild<QLabel *>(sObjName);
	if (pLablInfo == nullptr) return nullptr;

	return pLablInfo;
}

//设置Label信息
void CVisQtWidgetUI::SetLableInfo(const QString &sName, const QString &sInfo)
{
	if(m_pUI == nullptr) return;

	QLabel *pLabelInfo = m_pUI->findChild<QLabel *>(sName);
	if(pLabelInfo == nullptr) return;

	pLabelInfo->setText(sInfo);
}

//设置Label图像信息
void CVisQtWidgetUI::SetLabelImgInfo(const QString &sName, const QString &sImgInfo)
{
	if(sImgInfo.isEmpty()) return;
	if(m_pUI == nullptr) return;

	QLabel *pLabelInfo = m_pUI->findChild<QLabel *>(sName);
	if(pLabelInfo == nullptr) return;

	QString sImgStyle = sImgInfo;
	sImgStyle.replace("\\","/");
	QString sStyle = QString(QStringLiteral("QLabel{border: 1px solid rgb(0, 170, 255);border-image:url(%1);}")).arg(sImgStyle);
	pLabelInfo->setStyleSheet(sStyle);
}

//获取TabBar(相对于主窗口)
QTabBar * CVisQtWidgetUI::GetTabBar(const QString & sObjName)
{
	QTabBar *pTabBar = nullptr;

	if (m_pUI == nullptr) return pTabBar;

	pTabBar = m_pUI->findChild<QTabBar *>(sObjName);
	if (pTabBar == nullptr) return nullptr;

	return pTabBar;
}

//获取TabWidget的TabBar
QTabBar * CVisQtWidgetUI::GetTabWidgetTabBar(const QString & sObjName)
{
	QTabBar *pTabBar = nullptr;

	if (m_pUI == nullptr) return pTabBar;

	QTabWidget *pTabWgtUI = m_pUI->findChild<QTabWidget *>(sObjName);
	if (pTabWgtUI == nullptr) return nullptr;

	pTabBar = pTabWgtUI->tabBar();

	return pTabBar;
}

//获取TabWidget
QTabWidget * CVisQtWidgetUI::GetTabWidgetUI(const QString & sObjName)
{
	if (m_pUI == nullptr) return nullptr;

	QTabWidget *pTabWgtUI = m_pUI->findChild<QTabWidget *>(sObjName);
	if (pTabWgtUI == nullptr) return nullptr;

	return pTabWgtUI;
}

//获取QListView
QListView * CVisQtWidgetUI::GetListView(const QString & sObjName)
{
	if (m_pUI == nullptr) return nullptr;

	QListView *pListVw = m_pUI->findChild<QListView *>(sObjName);
	if (pListVw == nullptr) return nullptr;

	return pListVw;
}

//获取QTableView
QTableView * CVisQtWidgetUI::GetTblView(const QString & sObjName)
{
	if (m_pUI == nullptr) return nullptr;

	QTableView *pTblVw = m_pUI->findChild<QTableView *>(sObjName);
	if (pTblVw == nullptr) return nullptr;

	return pTblVw;
}

//获取QTreeView
QTreeView * CVisQtWidgetUI::GetTreeView(const QString & sObjName)
{
	if (m_pUI == nullptr) return nullptr;

	QTreeView *pTreeVw = m_pUI->findChild<QTreeView *>(sObjName);
	if (pTreeVw == nullptr) return nullptr;

	return pTreeVw;
}

//获取QListWidget
QListWidget * CVisQtWidgetUI::GetListWidget(const QString & sObjName)
{
	if (m_pUI == nullptr) return nullptr;

	QListWidget *pListWgt = m_pUI->findChild<QListWidget *>(sObjName);
	if (pListWgt == nullptr) return nullptr;

	return pListWgt;
}

//获取QTableWidget
QTableWidget * CVisQtWidgetUI::GetTblWidget(const QString & sObjName)
{
	if (m_pUI == nullptr) return nullptr;

	QTableWidget *pTblWgt = m_pUI->findChild<QTableWidget *>(sObjName);
	if (pTblWgt == nullptr) return nullptr;

	return pTblWgt;
}

//获取QTreeWidget
QTreeWidget * CVisQtWidgetUI::GetTreeWidget(const QString & sObjName)
{
	if (m_pUI == nullptr) return nullptr;

	QTreeWidget *pTreeWgt = m_pUI->findChild<QTreeWidget *>(sObjName);
	if (pTreeWgt == nullptr) return nullptr;

	return pTreeWgt;
}

//获取QSlider
QSlider * CVisQtWidgetUI::GetSlider(const QString & sObjName)
{
	if (m_pUI == nullptr) return nullptr;

	QSlider *pSlider = m_pUI->findChild<QSlider *>(sObjName);
	if (pSlider == nullptr) return nullptr;

	return pSlider;
}

//获取QDateEdit
QDateEdit * CVisQtWidgetUI::GetDateEditor(const QString & sObjName)
{
	if (m_pUI == nullptr) return nullptr;

	QDateEdit *pDateEdtor = m_pUI->findChild<QDateEdit *>(sObjName);
	if (pDateEdtor == nullptr) return nullptr;

	return pDateEdtor;
}

//获取QTimeEdit
QTimeEdit * CVisQtWidgetUI::GetTimeEditor(const QString & sObjName)
{
	if (m_pUI == nullptr) return nullptr;

	QTimeEdit *pEdtor = m_pUI->findChild<QTimeEdit *>(sObjName);
	if (pEdtor == nullptr) return nullptr;

	return pEdtor;
}

//获取QDateTimeEdit
QDateTimeEdit * CVisQtWidgetUI::GetDateTimeEditor(const QString & sObjName)
{
	if (m_pUI == nullptr) return nullptr;

	QDateTimeEdit *pEdtor = m_pUI->findChild<QDateTimeEdit *>(sObjName);
	if (pEdtor == nullptr) return nullptr;

	return pEdtor;
}

//获取QSpinBox
QSpinBox * CVisQtWidgetUI::GetSpinBox(const QString & sObjName)
{
	if (m_pUI == nullptr) return nullptr;

	QSpinBox *pEdtor = m_pUI->findChild<QSpinBox *>(sObjName);
	if (pEdtor == nullptr) return nullptr;

	return pEdtor;
}

//获取QDoubleSpinBox
QDoubleSpinBox * CVisQtWidgetUI::GetDoubleSpinBox(const QString & sObjName)
{
	if (m_pUI == nullptr) return nullptr;

	QDoubleSpinBox *pEdtor = m_pUI->findChild<QDoubleSpinBox *>(sObjName);
	if (pEdtor == nullptr) return nullptr;

	return pEdtor;
}

//获取QGroupBox
QGroupBox * CVisQtWidgetUI::GetGroupBox(const QString & sObjName)
{
	if (m_pUI == nullptr) return nullptr;

	QGroupBox *pEdtor = m_pUI->findChild<QGroupBox *>(sObjName);
	if (pEdtor == nullptr) return nullptr;

	return pEdtor;
}

//获取QProgressBar
QProgressBar * CVisQtWidgetUI::GetProgressBar(const QString & sObjName)
{
	if (m_pUI == nullptr) return nullptr;

	QProgressBar *pEdtor = m_pUI->findChild<QProgressBar *>(sObjName);
	if (pEdtor == nullptr) return nullptr;

	return pEdtor;
}

//获取QStackedWidget
QStackedWidget * CVisQtWidgetUI::GetStackedWgt(const QString & sObjName)
{
	if (m_pUI == nullptr) return nullptr;

	QStackedWidget *pEdtor = m_pUI->findChild<QStackedWidget *>(sObjName);
	if (pEdtor == nullptr) return nullptr;

	return pEdtor;
}

//获取QCalendarWidget
QCalendarWidget * CVisQtWidgetUI::GetCalendarWidget(const QString & sObjName)
{
	if (m_pUI == nullptr) return nullptr;

	QCalendarWidget *pEdtor = m_pUI->findChild<QCalendarWidget *>(sObjName);
	if (pEdtor == nullptr) return nullptr;

	return pEdtor;
}

