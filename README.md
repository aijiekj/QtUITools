# QtUITools
使用QtUI文件动态创建控件

2017-08-07 合并规整原有代码内容

1、把原有的代码内容VisQtUiTool和VisPublicControlsUI里内容都整合到FQtUiTool项目中，
移除目前不需要的代码内容
2、调整类的命名以F替换CVis或者Vis
3、给窗口添加移动功能


2017-06-26 初始化代码

Qt版本：5.7
编译使用的Vs2015

FanPublicControlsUI.sln  vs2015解决方案

1、VisQtUiTool
这个目录是存放解析UI文件的库,你可以直接使用下面的方式来加载你的UI文件
  1.1 VisQtUiTool::CreateUI()
    这里默认是加载当前工作目录下的UI文件不创建控件的
    
  1.2 VisQtUiTool::CreateUIForPath()
    这个可以使用全路径来加载UI文件创建控件
   
  参数说明：
  const QString &sFileName                    //UI文件路径,使用1.1中的方式这里是相对路径即可,另一种方式是全路径
  QStringList &lCustomUI = QStringList()      //这里是返回的自定义控件(就是Qt设计器中提升来的)类列表
  QWidget *parent = 0                         //父窗口
  
  
2、VisPublicControlsUI
  这个目录下存放的是封装类,如：CVisQtWidgetUI、CVisQtDialogUI
  CVisQtWidgetUI是使用上VisQtUiTool来创建一个无边框的QWidget窗口  
  CVisQtDialogUI在CVisQtWidgetUI基础上封装的一个无边框的QDialog窗口
  
  CVisQtWidgetUI中封装了一些基础的使用函数即方法,对于内容的一些控件的操作大部分都是使用控件的Property属性值动态控制的
  目前还在扩展中
  
  CVisQtDialogUI是封装了一个QDialog,内容使用的Qt布局把CVisQtWidgetUI作为内部的成员来使用，
  目前的为操作方式还只是使用GetUI()来控制CVisQtWidgetUI成员信息
  
3、 QtCustomUIApp
  这个是一个简单的Demo
  
  
