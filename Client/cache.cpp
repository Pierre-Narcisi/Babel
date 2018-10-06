#include <QCryptographicHash>
#include <QStandardPaths>
#include <QFileInfo>
#include <QFile>
#include <QDir>
#include <fstream>
#include "cache.h"

QString &Cache::getScrollBarStyle(void)
{
    static QString  style(  "QScrollBar:vertical {"
                                "background: rgb(230, 230, 230);"
                                "width: 8px;"
                            "}"

                            "QScrollBar::handle:vertical {"
                                "background: rgb(180, 180, 180);"
                                "min-height: 15px;"
                            "}"

                            "QScrollBar::handle:hover {"
                                "background: rgb(110, 155, 203);"
                            "}"

                            "QScrollBar::add-line {"
                                "background: none;"
                            "}"

                            "QScrollBar::sub-line {"
                                "background: none;"
                            "}");

    return style;
}
