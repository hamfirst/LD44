/********************************************************************************
** Form generated from reading UI file 'EditorContainer.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITORCONTAINER_H
#define UI_EDITORCONTAINER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EditorContainerClass
{
public:
    QAction *action_Open;
    QAction *action_Save;
    QAction *action_Quit;
    QAction *action_Sprite;
    QAction *action_Undo;
    QAction *action_Redo;
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QMenu *menu_File;
    QMenu *menu_New;
    QMenu *menuEdit;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *EditorContainerClass)
    {
        if (EditorContainerClass->objectName().isEmpty())
            EditorContainerClass->setObjectName(QStringLiteral("EditorContainerClass"));
        EditorContainerClass->resize(475, 352);
        action_Open = new QAction(EditorContainerClass);
        action_Open->setObjectName(QStringLiteral("action_Open"));
        action_Save = new QAction(EditorContainerClass);
        action_Save->setObjectName(QStringLiteral("action_Save"));
        action_Quit = new QAction(EditorContainerClass);
        action_Quit->setObjectName(QStringLiteral("action_Quit"));
        action_Sprite = new QAction(EditorContainerClass);
        action_Sprite->setObjectName(QStringLiteral("action_Sprite"));
        action_Undo = new QAction(EditorContainerClass);
        action_Undo->setObjectName(QStringLiteral("action_Undo"));
        action_Redo = new QAction(EditorContainerClass);
        action_Redo->setObjectName(QStringLiteral("action_Redo"));
        centralWidget = new QWidget(EditorContainerClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        EditorContainerClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(EditorContainerClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 475, 21));
        menu_File = new QMenu(menuBar);
        menu_File->setObjectName(QStringLiteral("menu_File"));
        menu_New = new QMenu(menu_File);
        menu_New->setObjectName(QStringLiteral("menu_New"));
        menuEdit = new QMenu(menuBar);
        menuEdit->setObjectName(QStringLiteral("menuEdit"));
        EditorContainerClass->setMenuBar(menuBar);
        statusBar = new QStatusBar(EditorContainerClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        EditorContainerClass->setStatusBar(statusBar);

        menuBar->addAction(menu_File->menuAction());
        menuBar->addAction(menuEdit->menuAction());
        menu_File->addAction(menu_New->menuAction());
        menu_File->addAction(action_Open);
        menu_File->addAction(action_Save);
        menu_File->addSeparator();
        menu_File->addAction(action_Quit);
        menuEdit->addAction(action_Undo);
        menuEdit->addAction(action_Redo);

        retranslateUi(EditorContainerClass);

        QMetaObject::connectSlotsByName(EditorContainerClass);
    } // setupUi

    void retranslateUi(QMainWindow *EditorContainerClass)
    {
        EditorContainerClass->setWindowTitle(QApplication::translate("EditorContainerClass", "StormBrewer Engine", Q_NULLPTR));
        action_Open->setText(QApplication::translate("EditorContainerClass", "&Open", Q_NULLPTR));
        action_Save->setText(QApplication::translate("EditorContainerClass", "Save", Q_NULLPTR));
        action_Quit->setText(QApplication::translate("EditorContainerClass", "&Quit", Q_NULLPTR));
        action_Sprite->setText(QApplication::translate("EditorContainerClass", "Sprite", Q_NULLPTR));
        action_Undo->setText(QApplication::translate("EditorContainerClass", "Undo", Q_NULLPTR));
        action_Redo->setText(QApplication::translate("EditorContainerClass", "Redo", Q_NULLPTR));
        menu_File->setTitle(QApplication::translate("EditorContainerClass", "&File", Q_NULLPTR));
        menu_New->setTitle(QApplication::translate("EditorContainerClass", "&New", Q_NULLPTR));
        menuEdit->setTitle(QApplication::translate("EditorContainerClass", "Edit", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class EditorContainerClass: public Ui_EditorContainerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITORCONTAINER_H