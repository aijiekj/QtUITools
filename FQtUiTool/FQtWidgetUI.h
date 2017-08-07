/************************************************************************/
/*                        使用Qt布局创建QWidget	                        */
/************************************************************************/
#ifndef FQtWidgetUI_H
#define FQtWidgetUI_H

#include "fqtuitool_global.h"
#include <QWidget>

class QTabBar;
class QComboBox;
class QLineEdit;
class QTextEdit;
class QCheckBox;
class QLabel;
class QTabWidget;
class QAbstractItemView;
class QListView;
class QListWidget;
class QTableView;
class QTableWidget;
class QTreeView;
class QTreeWidget;
class QPushButton;
class QDateTimeEdit;
class QUrl;
class QModelIndex;
class QListWidgetItem;
class QTableWidgetItem;
class QTreeWidgetItem;
class QDate;
class QDateTime;
class QTime;
class QSlider;
class QDateEdit;
class QTimeEdit;
class QDateTimeEdit;
class QSpinBox;
class QDoubleSpinBox;
class QGroupBox;
class QProgressBar;
class QStackedWidget;
class QCalendarWidget;
class QMouseEvent;

class FQTUITOOL_EXPORT FQtWidgetUI : public QWidget
{
	Q_OBJECT

public:
	FQtWidgetUI(QWidget *parent = nullptr);
	~FQtWidgetUI();

	bool InitPolicyFileUI(const QString &sUIFile);	//初始化界面UI
	bool InitUIForFullPath(const QString &sUIFile);	//初始化界面UI

	void BindBusiness(QObject *pObj);	//绑定业务	
	QObject *GetBindBusiness();				//获取业务类

	QStringList GetCustomUI() { return m_lCustomUI; };

	QPushButton*	GetPushButton(const QString &sObjName);		//获取PushButton

	QComboBox*		GetComboBox(const QString &sObjName);		  //获取ComBoBox
	QString			GetCurrComboBoxInfo(const QString &sName);	//获取当前ComboInfo自定义数据
	QString			GetComboBoxCurShowText(const QString &sName); //获取当前ComboBox显示信息
	int				GetComboBoxCurIndex(const QString &sName);	  //获取当前ComboBoxIndex	
	
	QLineEdit*		GetLineEdit(const QString &sObjName);		//获取LineEdit
	QString			GetLineEditInfo(const QString &sName);		//获取当前输入框信息
	void			SetLineEditInfo(const QString &sName, const QString &sInfo);	//设置LineEditInfo	

	QTextEdit*		GetTextBrowser(const QString &sObjName);		//获取TextBrowser
	QString			GetTextBrowserInfo(const QString &sName);	//获取TextBrowserInfo
	void			SetTextBrowserInfo(const QString &sName, const QString &sInfo);	//设置TextBrowserInfo
	  
	QCheckBox*		GetCheckBox(const QString &sObjName);			//获取CheckBox
	bool			GetCheckBoxCheckStatus(const QString &sName);	//获取CheckBox状态	

	QLabel*			GetLable(const QString &sObjName);		//获取Label
	void			SetLableInfo(const QString &sName, const QString &sInfo);	//设置Label信息
	void			SetLabelImgInfo(const QString &sName, const QString &sImgInfo);	//设置Label图像信息	

	QTabBar*		GetTabBar(const QString &sObjName);				//获取TabBar(相对于主窗口)
	QTabBar*		GetTabWidgetTabBar(const QString &sObjName);	//获取TabWidget的TabBar
	QTabWidget*		GetTabWidgetUI(const QString &sObjName);		//获取TabWidget

	QListView*		GetListView(const QString &sObjName);			//获取QListView
	QTableView*		GetTblView(const QString &sObjName);			//获取QTableView
	QTreeView*		GetTreeView(const QString &sObjName);			//获取QTreeView

	QListWidget*	GetListWidget(const QString &sObjName);			//获取QListWidget
	QTableWidget*	GetTblWidget(const QString &sObjName);			//获取QTableWidget
	QTreeWidget*	GetTreeWidget(const QString &sObjName);			//获取QTreeWidget

	QSlider*		GetSlider(const QString &sObjName);				//获取QSlider

	QDateEdit*		GetDateEditor(const QString &sObjName);			//获取QDateEdit
	QTimeEdit*		GetTimeEditor(const QString &sObjName);			//获取QTimeEdit
	QDateTimeEdit*	GetDateTimeEditor(const QString &sObjName);		//获取QDateTimeEdit

	QSpinBox*		GetSpinBox(const QString &sObjName);			//获取QSpinBox
	QDoubleSpinBox*	GetDoubleSpinBox(const QString &sObjName);		//获取QDoubleSpinBox

	QGroupBox*		GetGroupBox(const QString &sObjName);			//获取QGroupBox

	QProgressBar*	GetProgressBar(const QString &sObjName);		//获取QProgressBar

	QStackedWidget*	GetStackedWgt(const QString &sObjName);			//获取QStackedWidget
	
	QCalendarWidget*	GetCalendarWidget(const QString &sObjName);	//获取QCalendarWidget

	//设置窗口移动相关信息
	void SetWindMoveFlg(bool bMoveFlg);
	bool GetWindMoveFlg();
	void SetWindTitleHeight(int nHeight);
	int  GetWindTitleHeight();

signals:
	void signal_OperBtn_ToDo(const QString &sToDo);
	void signal_TabBar_CurrentChanged(int index);
	void signal_TabBar_TabBarClicked(int index);
	void signal_TabBar_TabBarDoubleClicked(int index);
	void signal_TabBar_TabCloseRequested(int index);
	void signal_View_Clicked(const QModelIndex &index);
	void signal_View_DoubleClicked(const QModelIndex &index);
	void signal_View_Pressed(const QModelIndex &index);
	void signal_TreeView_Collapsed(const QModelIndex &index);
	void signal_TreeView_Expanded(const QModelIndex &index);
	
	//QListWidget
	void signal_ListWgt_ItemClicked(QListWidgetItem *item);
	void signal_ListWgt_ItemDoubleClicked(QListWidgetItem *item);
	void signal_ListWgt_ItemPressed(QListWidgetItem *item);

	//QTableWidget
	void signal_TblWgt_ItemClicked(QTableWidgetItem *item);
	void signal_TblWgt_ItemDoubleClicked(QTableWidgetItem *item);
	void signal_TblWgt_ItemPressed(QTableWidgetItem *item);
	void signal_TblWgt_CellClicked(int row, int column);
	void signal_TblWgt_CellDoubleClicked(int row, int column);
	void gignal_TblWgt_CellPressed(int row, int column);

	//QTreeWidget
	void signal_TreeWgt_ItemClicked(QTreeWidgetItem *item, int column);
	void signal_TreeWgt_ItemDoubleClicked(QTreeWidgetItem *item, int column);
	void signal_TreeWgt_ItemPressed(QTreeWidgetItem *item, int column);
	void signal_TreeWgt_ItemEntered(QTreeWidgetItem *item, int column);
	void signal_TreeWgt_ItemExpanded(QTreeWidgetItem *item);
	void signal_TreeWgt_ItemCollapsed(QTreeWidgetItem *item);

	//QLineEdit
	void signal_LineEdit_EditingFinished();
	void signal_LineEdit_ReturnPressed();
	void signal_LineEdit_TextChanged(const QString &text);

	//QChekBox
	void signal_ChekBox_StateChanged(int state);

	//QSlider
	void signal_Slider_ActionTriggered(int action);
	void signal_Slider_RangeChanged(int min, int max);
	void signal_Slider_SliderMoved(int value);
	void signal_Slider_SliderPressed();
	void signal_Slider_SliderReleased();
	void signal_Slider_ValueChanged(int value);

	//QDateTimeEditor
	void signal_DateTimeEdtor_DateChanged(const QDate &date);
	void signal_DateTimeEdtor_DateTimeChanged(const QDateTime &datetime);
	void signal_DateTimeEdtor_TimeChanged(const QTime &time);
	void signal_DateTimeEdotr_EditingFinished();

	//QSipinBox QDoubleSpinBox
	void signal_SpinBox_EditingFinished();
	void signal_SpinBox_ValueChanged(const QString &text);
	void signal_SpinBox_ValueChanged(int value);
	void signal_SpinBox_ValueChanged(double value);

	//QGroupBox
	void signal_GroupBox_Clicked(bool checked = false);
	void signal_GroupBox_Toggled(bool on);

	//QProgressBar
	void signal_ProgressBar_ValueChanged(int value);

	//QWebView QWebEngineView
	void signal_WebView_LoadFinished(bool ok);
	void signal_WebView_LoadProgress(int progress);
	void signal_WebView_LoadStarted();
	void signal_WebView_UrlChanged(const QUrl &url);

	//QStackedWidget
	void signal_StackWgt_CurrentChanged(int index);
	void signal_StackWgt_WidgetRemoved(int index);

	//QCalendarWidget
	void signal_CalendarWgt_Activated(const QDate &date);
	void signal_CalendarWgt_Clicked(const QDate &date);
	void signal_CalendarWgt_CurrentPageChanged(int year, int month);
	void signal_CalendarWgt_SelectionChanged();

private slots:
	void slot_ItemUi_OperBtn_Clicked();

private:
	//初始化ItemUI基础控件
	void InitItemUIInfo(QWidget	*pItemUI);
	void InitUIBaseInfo(QWidget *pItemUI);
	void InitOperBtnSignal(QWidget *pItemUI);			//初始化Btn
	void InitComboBoxInfo(QWidget *pUI);				//初始化ComBoBx信息
	void InitTabBarInfo(QWidget *pItemUI);				//初始化TabBar信息	
	void InitTabWidgetInfo(QWidget *pItemUI);			//初始化TabWidget信息
	void InitLineEdit(QWidget *pItemUI);				//初始化QLineEdit
	void InitCheckBox(QWidget *pItemUI);				//初始化CheckBox
	void InitRadioButton(QWidget *pItemUI);				//初始化RadioBtn
	void InitSlider(QWidget*pItemUI);					//初始化Slider
	void InitDateEditor(QWidget *pItemUI);				//初始化DateEdtor
	void InitTimeEditor(QWidget *pItemUI);				//初始化TimeEdtor
	void InitDateTimeEdtor(QWidget *pItemUI);			//初始化DateTimeEdtor
	void InitDatetimeEditor(QDateTimeEdit *pEdtor);		//初始化QDateTimeEdit
	void InitDoubleSpinBox(QWidget *pItemUI);			//初始化DoubleSpBx
	void InitSpinBox(QWidget *pItemUI);					//初始化SpinBox
	void InitGroupBox(QWidget *pItemUI);				//初始化GroupBox
	void InitProgressBar(QWidget *pItemUI);				//初始化ProgressBar
	void InitWebView(QWidget *pItemUI);					//初始化WebView
	void InitStackedWidgt(QWidget *pItemUI);			//初始化StackedWgt
	void InitScrollArea(QWidget *pItemUI);				//初始化ScrollArea
	void InitCalendarWidget(QWidget *pItemUI);			//初始化CalendarWgt

	//表格相关
	void InitTableViewInfo(QWidget *pItemUI);			//初始化QTableView信息
	void InitListViewInfo(QWidget *pItemUI);			//初始化QListView
	void InitTreeViewInfo(QWidget *pItemUI);			//初始化QTreeView
	void InitTableWidgetInfo(QWidget *pItemUI);			//初始化QTableWidget
	void InitListWidgetInfo(QWidget *pItemUI);			//初始化QListWidget
	void InitTreeWidgetInfo(QWidget *pItemUI);			//初始化QTreeWidget
	void InitAbstractItemViewInfo(QAbstractItemView *pView);	//初始化QAbstractItemView

	void InitCustomUI();								//初始化自定义控件
	void SetCustomUI(QWidget *pItmeUI, const QString &sObjName);

protected:
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);

private:
	QWidget				*m_pUI;
	QObject				*m_pBusObj;	

	QStringList			m_lCustomUI;

	bool				m_bCurFrameType;
	bool				m_bMove;					
	bool				m_bCurFrameMoveState;		
	int					m_nTopHight;				
	QPoint				m_CurrentPos;			

};

#endif // FQtWidgetUI_H
