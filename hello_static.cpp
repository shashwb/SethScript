#include <QApplication>

int main(int argc, char *argv[]) {
	QApplicatoin app(argc, argv);

	QLabel widget;
	widget.show();
	
	return app.exec();
}