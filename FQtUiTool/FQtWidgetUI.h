/************************************************************************/
/*                        ʹ��Qt���ִ���QWidget	                        */
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

	bool InitPolicyFileUI(const QString &sUIFile);	//��ʼ������UI
	bool InitUIForFullPath(const QString &sUIFile);	//��ʼ������UI

	void BindBusiness(QObject *pObj);	//��ҵ��	
	QObject *GetBindBusiness();				//��ȡҵ����

	QStringList GetCustomUI() { return m_lCustomUI; };

	QPushButton*	GetPushButton(const QString &sObjName);		//��ȡPushButton

	QComboBox*		GetComboBox(const QString &sObjName);		  //��ȡComBoBox
	QString			GetCurrComboBoxInfo(const QString &sName);	//��ȡ��ǰComboInfo�Զ�������
	QString			GetComboBoxCurShowText(const QString &sName); //��ȡ��ǰComboBox��ʾ��Ϣ
	int				GetComboBoxCurIndex(const QString &sName);	  //��ȡ��ǰComboBoxIndex	
	
	QLineEdit*		GetLineEdit(const QString &sObjName);		//��ȡLineEdit
	QString			GetLineEditInfo(const QString &sName);		//��ȡ��ǰ�������Ϣ
	void			SetLineEditInfo(const QString &sName, const QString &sInfo);	//����LineEditInfo	

	QTextEdit*		GetTextBrowser(const QString &sObjName);		//��ȡTextBrowser
	QString			GetTextBrowserInfo(const QString &sName);	//��ȡTextBrowserInfo
	void			SetTextBrowserInfo(const QString &sName, const QString &sInfo);	//����TextBrowserInfo
	  
	QCheckBox*		GetCheckBox(const QString &sObjName);			//��ȡCheckBox
	bool			GetCheckBoxCheckStatus(const QString &sName);	//��ȡCheckBox״̬	

	QLabel*			GetLable(const QString &sObjName);		//��ȡLabel
	void			SetLableInfo(const QString &sName, const QString &sInfo);	//����Label��Ϣ
	void			SetLabelImgInfo(const QString &sName, const QString &sImgInfo);	//����Labelͼ����Ϣ	

	QTabBar*		GetTabBar(const QString &sObjName);				//��ȡTabBar(�����������)
	QTabBar*		GetTabWidgetTabBar(const QString &sObjName);	//��ȡTabWidget��TabBar
	QTabWidget*		GetTabWidgetUI(const QString &sObjName);		//��ȡTabWidget

	QListView*		GetListView(const QString &sObjName);			//��ȡQListView
	QTableView*		GetTblView(const QString &sObjName);			//��ȡQTableView
	QTreeView*		GetTreeView(const QString &sObjName);			//��ȡQTreeView

	QListWidget*	GetListWidget(const QString &sObjName);			//��ȡQListWidget
	QTableWidget*	GetTblWidget(const QString &sObjName);			//��ȡQTableWidget
	QTreeWidget*	GetTreeWidget(const QString &sObjName);			//��ȡQTreeWidget

	QSlider*		GetSlider(const QString &sObjName);				//��ȡQSlider

	QDateEdit*		GetDateEditor(const QString &sObjName);			//��ȡQDateEdit
	QTimeEdit*		GetTimeEditor(const QString &sObjName);			//��ȡQTimeEdit
	QDateTimeEdit*	GetDateTimeEditor(const QString &sObjName);		//��ȡQDateTimeEdit

	QSpinBox*		GetSpinBox(const QString &sObjName);			//��ȡQSpinBox
	QDoubleSpinBox*	GetDoubleSpinBox(const QString &sObjName);		//��ȡQDoubleSpinBox

	QGroupBox*		GetGroupBox(const QString &sObjName);			//��ȡQGroupBox

	QProgressBar*	GetProgressBar(const QString &sObjName);		//��ȡQProgressBar

	QStackedWidget*	GetStackedWgt(const QString &sObjName);			//��ȡQStackedWidget
	
	QCalendarWidget*	GetCalendarWidget(const QString &sObjName);	//��ȡQCalendarWidget

	//���ô����ƶ������Ϣ
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
	//��ʼ��ItemUI�����ؼ�
	void InitItemUIInfo(QWidget	*pItemUI);
	void InitUIBaseInfo(QWidget *pItemUI);
	void InitOperBtnSignal(QWidget *pItemUI);			//��ʼ��Btn
	void InitComboBoxInfo(QWidget *pUI);				//��ʼ��ComBoBx��Ϣ
	void InitTabBarInfo(QWidget *pItemUI);				//��ʼ��TabBar��Ϣ	
	void InitTabWidgetInfo(QWidget *pItemUI);			//��ʼ��TabWidget��Ϣ
	void InitLineEdit(QWidget *pItemUI);				//��ʼ��QLineEdit
	void InitCheckBox(QWidget *pItemUI);				//��ʼ��CheckBox
	void InitRadioButton(QWidget *pItemUI);				//��ʼ��RadioBtn
	void InitSlider(QWidget*pItemUI);					//��ʼ��Slider
	void InitDateEditor(QWidget *pItemUI);				//��ʼ��DateEdtor
	void InitTimeEditor(QWidget *pItemUI);				//��ʼ��TimeEdtor
	void InitDateTimeEdtor(QWidget *pItemUI);			//��ʼ��DateTimeEdtor
	void InitDatetimeEditor(QDateTimeEdit *pEdtor);		//��ʼ��QDateTimeEdit
	void InitDoubleSpinBox(QWidget *pItemUI);			//��ʼ��DoubleSpBx
	void InitSpinBox(QWidget *pItemUI);					//��ʼ��SpinBox
	void InitGroupBox(QWidget *pItemUI);				//��ʼ��GroupBox
	void InitProgressBar(QWidget *pItemUI);				//��ʼ��ProgressBar
	void InitWebView(QWidget *pItemUI);					//��ʼ��WebView
	void InitStackedWidgt(QWidget *pItemUI);			//��ʼ��StackedWgt
	void InitScrollArea(QWidget *pItemUI);				//��ʼ��ScrollArea
	void InitCalendarWidget(QWidget *pItemUI);			//��ʼ��CalendarWgt

	//������
	void InitTableViewInfo(QWidget *pItemUI);			//��ʼ��QTableView��Ϣ
	void InitListViewInfo(QWidget *pItemUI);			//��ʼ��QListView
	void InitTreeViewInfo(QWidget *pItemUI);			//��ʼ��QTreeView
	void InitTableWidgetInfo(QWidget *pItemUI);			//��ʼ��QTableWidget
	void InitListWidgetInfo(QWidget *pItemUI);			//��ʼ��QListWidget
	void InitTreeWidgetInfo(QWidget *pItemUI);			//��ʼ��QTreeWidget
	void InitAbstractItemViewInfo(QAbstractItemView *pView);	//��ʼ��QAbstractItemView

	void InitCustomUI();								//��ʼ���Զ���ؼ�
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
