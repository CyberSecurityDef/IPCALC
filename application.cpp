#include "application.h"

Application::Application(int &argc, char **argv) : QApplication(argc, argv){
    setApplicationName(tr("IPCalc"));
    setApplicationDisplayName(tr("IPCalc"));
    setWindowIcon(QIcon(":/ico/title.ico"));
}


