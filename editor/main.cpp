#include <QApplication>
#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QWidget>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    
    QCoreApplication::setOrganizationName("QtProject");
    QCoreApplication::setApplicationName("Application Example");
    QCoreApplication::setApplicationVersion(QT_VERSION_STR);

    QMainWindow mainWin;
    mainWin.resize(800, 600);

    QMenuBar* menuBar = mainWin.menuBar();

    QMenu* menu = new QMenu("File");
    menu->addAction("New Project");

    menuBar->addMenu(menu);
    mainWin.show();

    return app.exec();
}
