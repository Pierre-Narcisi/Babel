#ifndef GAMELAUNCHER_H
#define GAMELAUNCHER_H

#include <QString>

class GameLauncher
{
public:
    static void start(QString const &path, QString const &binaryName);
private:
    explicit GameLauncher() = default;
};

#endif // GAMELAUNCHER_H
