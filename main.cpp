#include "customwizard.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QStyleFactory>
#include <QLibraryInfo>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QStringList keys = QStyleFactory().keys();
    a.setStyle(keys[2]);
    a.setStyleSheet("QAction:unchecked {background-color:red} QAction:checked {background-color:green}");
#ifndef QT_NO_TRANSLATION
    QString translatorFileName = QLatin1String("qtbase_");
    translatorFileName += QLocale::system().name();
    QTranslator *translator = new QTranslator(&a);
    if (translator->load(translatorFileName, QLibraryInfo::path(QLibraryInfo::TranslationsPath)))
        a.installTranslator(translator);
#endif
    CustomWizard w;
    w.show();
    return a.exec();
}
