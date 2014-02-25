
#include <QApplication>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <QtCore/QFile>
#include <QtCore/QTranslator>

#include "mainwindow.h"

void printHelpMessage()
{
    qDebug()<<"Find My Way - simple graphics program\n"
              ;
}

void printVersion()
{
    qDebug()<<"0.1.1";
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("FindMyWay");
    a.setApplicationVersion("0.1.1");

    QStringList args = a.arguments();

    QRegExp rxArgHelp("--help");
    QRegExp rxArgH("-h");
    QRegExp rxArgVersion("--version");
    QRegExp rxArgV("-v");

    bool isHelp(false), isVer(false);
    QStringList filePaths;

    for(int i(1); i < args.size(); ++i)
    {
        if (rxArgHelp.indexIn(args.at(i)) != -1  ||
                rxArgH.indexIn(args.at(i)) != -1)
        {
            isHelp = true;
        }
        else if (rxArgVersion.indexIn(args.at(i)) != -1  ||
                 rxArgV.indexIn(args.at(i)) != -1)
        {
            isVer = true;
        }
        else
        {
            if(QFile::exists(args.at(i)))
            {
                filePaths.append(args.at(i));
            }
            else
            {
                qDebug()<<QString("File %1 not found").arg(args.at(i));
            }
        }

    }

    if(isHelp)
    {
        printHelpMessage();
        return 0;
    }
    else if(isVer)
    {
        printVersion();
        return 0;
    }



    MainWindow w(filePaths);
    w.show();

    return a.exec();
}
