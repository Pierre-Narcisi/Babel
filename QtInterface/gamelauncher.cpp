#include <QProcess>
#include <QFile>
#include <iostream>
#include "gamelauncher.h"

void    GameLauncher::start(QString const &path, QString const &binaryName)
{
    QFile               programFile(path + "/" + binaryName);

    programFile.setPermissions(programFile.permissions() | QFile::ExeUser);
    bool bSet = qputenv("LD_LIBRARY_PATH", ".");
    if (QProcess::startDetached(programFile.fileName(), {nullptr}, path) == false)
       std::cerr << "failed to start " << (path + "/" + binaryName).toStdString() << std::endl;
}
