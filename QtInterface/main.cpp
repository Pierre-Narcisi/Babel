#include <QApplication>
#include <iostream>
#include "clientmainwindows.h"
#include "Constant.hpp"
#include "version.h"

int main(int argc, char *argv[])
{
    common::Opts opts(argc, argv);

    opts.setUsage(("Babel client version: " + Version::toString() + "\nUsage").toStdString(),
                  std::string(argv[0]) + " [arguments...]");
    opts.setArgsTitle("Available Arguments");
    opts.setOptions({
        {"help", 'h', common::Opts::noArg(), "Show this help", ""},
        {"host", 'i', common::Opts::makeString(constant::defHost), "Server hostname or ip", ""},
        {"port", 'p', common::Opts::makeInt(constant::defPort), "Server port", ""}
    });
    opts.parse();
    if (opts["help"]->count()) {
        std::cout << opts << std::endl;
    } else {
        QApplication a(argc, argv);

        ClientMainWindows w(nullptr, opts);
        w.show();
        return a.exec();
    }
    return (0);
}
