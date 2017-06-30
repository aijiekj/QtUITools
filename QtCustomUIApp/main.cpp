#include "FQtCustomUIApp.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	FQtCustomUIApp w;
	w.show();
	return a.exec();
}
