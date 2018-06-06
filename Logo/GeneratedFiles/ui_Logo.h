/********************************************************************************
** Form generated from reading UI file 'Logo.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGO_H
#define UI_LOGO_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LogoClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *LogoClass)
    {
        if (LogoClass->objectName().isEmpty())
            LogoClass->setObjectName(QStringLiteral("LogoClass"));
        LogoClass->resize(600, 400);
        menuBar = new QMenuBar(LogoClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        LogoClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(LogoClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        LogoClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(LogoClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        LogoClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(LogoClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        LogoClass->setStatusBar(statusBar);

        retranslateUi(LogoClass);

        QMetaObject::connectSlotsByName(LogoClass);
    } // setupUi

    void retranslateUi(QMainWindow *LogoClass)
    {
        LogoClass->setWindowTitle(QApplication::translate("LogoClass", "Logo", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class LogoClass: public Ui_LogoClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGO_H
