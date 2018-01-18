/********************************************************************************
** Form generated from reading UI file 'AppMain.ui'
**
** Created by: Qt User Interface Compiler version 5.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_APPMAIN_H
#define UI_APPMAIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AppMainClass
{
public:
    QAction *aExit;
    QAction *aLoadPath;
    QAction *aSavePath;
    QAction *aWorld;
    QAction *aTop;
    QAction *aTrain;
    QAction *aLinear;
    QAction *aCardinal;
    QAction *aCubic;
    QAction *aLine;
    QAction *aTrack;
    QAction *aRoad;
    QAction *atrain;
    QAction *aBox;
    QAction *actionClose_Splash;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *close;
    QPushButton *bPlay;
    QSlider *sSpeed;
    QSpacerItem *horizontalSpacer_3;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *mainLayout;
    QGroupBox *groupBox_5;
    QGroupBox *groupCamera;
    QComboBox *comboCamera;
    QGroupBox *groupCurve;
    QComboBox *comboCurve;
    QGroupBox *groupTrack;
    QComboBox *comboTrack;
    QGroupBox *groupTrain;
    QComboBox *comboTrain;
    QGroupBox *groupCP;
    QPushButton *bAdd;
    QPushButton *bDelete;
    QGroupBox *groupBox;
    QPushButton *rcpxadd;
    QPushButton *rcpxsub;
    QPushButton *rcpzadd;
    QPushButton *rcpzsub;
    QPushButton *rcpysub;
    QPushButton *rcpyadd;
    QGroupBox *groupBox_3;
    QPushButton *rcpBoxadd;
    QPushButton *rcpBoxsub;
    QGroupBox *groupCP_2;
    QPushButton *people;
    QPushButton *cave;
    QPushButton *w;
    QPushButton *pushButton_2;
    QPushButton *GS;
    QPushButton *YS;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuCamera;
    QMenu *menuCurve;
    QMenu *menuTrack;
    QMenu *menuVelocity;
    QStatusBar *statusBar;
    QToolBar *mainToolBar;

    void setupUi(QMainWindow *AppMainClass)
    {
        if (AppMainClass->objectName().isEmpty())
            AppMainClass->setObjectName(QStringLiteral("AppMainClass"));
        AppMainClass->resize(1426, 1175);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(AppMainClass->sizePolicy().hasHeightForWidth());
        AppMainClass->setSizePolicy(sizePolicy);
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\273\237\346\255\243\351\273\221\351\253\224"));
        AppMainClass->setFont(font);
        AppMainClass->setLayoutDirection(Qt::LeftToRight);
        AppMainClass->setAutoFillBackground(true);
        AppMainClass->setStyleSheet(QStringLiteral(""));
        AppMainClass->setDockNestingEnabled(false);
        aExit = new QAction(AppMainClass);
        aExit->setObjectName(QStringLiteral("aExit"));
        aLoadPath = new QAction(AppMainClass);
        aLoadPath->setObjectName(QStringLiteral("aLoadPath"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/AppMain/Resources/Icons/openfile.ico"), QSize(), QIcon::Normal, QIcon::Off);
        aLoadPath->setIcon(icon);
        aLoadPath->setIconVisibleInMenu(true);
        aSavePath = new QAction(AppMainClass);
        aSavePath->setObjectName(QStringLiteral("aSavePath"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/AppMain/Resources/Icons/savefile.ico"), QSize(), QIcon::Normal, QIcon::Off);
        aSavePath->setIcon(icon1);
        aWorld = new QAction(AppMainClass);
        aWorld->setObjectName(QStringLiteral("aWorld"));
        aWorld->setCheckable(false);
        aWorld->setChecked(false);
        aTop = new QAction(AppMainClass);
        aTop->setObjectName(QStringLiteral("aTop"));
        aTop->setCheckable(true);
        aTrain = new QAction(AppMainClass);
        aTrain->setObjectName(QStringLiteral("aTrain"));
        aTrain->setCheckable(true);
        aLinear = new QAction(AppMainClass);
        aLinear->setObjectName(QStringLiteral("aLinear"));
        aLinear->setCheckable(false);
        aLinear->setChecked(false);
        aCardinal = new QAction(AppMainClass);
        aCardinal->setObjectName(QStringLiteral("aCardinal"));
        aCardinal->setCheckable(true);
        aCubic = new QAction(AppMainClass);
        aCubic->setObjectName(QStringLiteral("aCubic"));
        aCubic->setCheckable(true);
        aLine = new QAction(AppMainClass);
        aLine->setObjectName(QStringLiteral("aLine"));
        aLine->setCheckable(false);
        aLine->setChecked(false);
        aTrack = new QAction(AppMainClass);
        aTrack->setObjectName(QStringLiteral("aTrack"));
        aTrack->setCheckable(true);
        aRoad = new QAction(AppMainClass);
        aRoad->setObjectName(QStringLiteral("aRoad"));
        aRoad->setCheckable(true);
        atrain = new QAction(AppMainClass);
        atrain->setObjectName(QStringLiteral("atrain"));
        aBox = new QAction(AppMainClass);
        aBox->setObjectName(QStringLiteral("aBox"));
        actionClose_Splash = new QAction(AppMainClass);
        actionClose_Splash->setObjectName(QStringLiteral("actionClose_Splash"));
        centralWidget = new QWidget(AppMainClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy1);
        centralWidget->setMinimumSize(QSize(0, 0));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer_4 = new QSpacerItem(0, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_4);

        close = new QPushButton(centralWidget);
        close->setObjectName(QStringLiteral("close"));

        horizontalLayout_2->addWidget(close);

        bPlay = new QPushButton(centralWidget);
        bPlay->setObjectName(QStringLiteral("bPlay"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(bPlay->sizePolicy().hasHeightForWidth());
        bPlay->setSizePolicy(sizePolicy2);
        QFont font1;
        font1.setFamily(QStringLiteral("Comic Sans MS"));
        font1.setPointSize(9);
        font1.setBold(true);
        font1.setWeight(75);
        bPlay->setFont(font1);
        bPlay->setStyleSheet(QLatin1String(" QPushButton {\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"}"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/AppMain/mplay.png"), QSize(), QIcon::Normal, QIcon::Off);
        bPlay->setIcon(icon2);
        bPlay->setIconSize(QSize(40, 40));

        horizontalLayout_2->addWidget(bPlay);

        sSpeed = new QSlider(centralWidget);
        sSpeed->setObjectName(QStringLiteral("sSpeed"));
        sSpeed->setMinimumSize(QSize(850, 0));
        sSpeed->setStyleSheet(QLatin1String("QSlider::groove:horizontal {\n"
"	background-color: #505050;\n"
"    height: 3px; \n"
"    margin: 2px 0;\n"
" }\n"
" QSlider::handle:horizontal {\n"
"	image: url(:/AppMain/slider_handle.png);\n"
"	width: 15px;\n"
"	margin: -5px 0;\n"
" }"));
        sSpeed->setSingleStep(1);
        sSpeed->setValue(50);
        sSpeed->setOrientation(Qt::Horizontal);

        horizontalLayout_2->addWidget(sSpeed);

        horizontalSpacer_3 = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        mainLayout = new QVBoxLayout();
        mainLayout->setSpacing(6);
        mainLayout->setObjectName(QStringLiteral("mainLayout"));
        mainLayout->setSizeConstraint(QLayout::SetDefaultConstraint);

        horizontalLayout_3->addLayout(mainLayout);

        groupBox_5 = new QGroupBox(centralWidget);
        groupBox_5->setObjectName(QStringLiteral("groupBox_5"));
        groupBox_5->setMaximumSize(QSize(250, 16777215));
        groupCamera = new QGroupBox(groupBox_5);
        groupCamera->setObjectName(QStringLiteral("groupCamera"));
        groupCamera->setGeometry(QRect(20, 10, 100, 100));
        sizePolicy2.setHeightForWidth(groupCamera->sizePolicy().hasHeightForWidth());
        groupCamera->setSizePolicy(sizePolicy2);
        groupCamera->setMinimumSize(QSize(100, 100));
        groupCamera->setMaximumSize(QSize(100, 100));
        QFont font2;
        font2.setFamily(QStringLiteral("Comic Sans MS"));
        font2.setPointSize(10);
        font2.setBold(true);
        font2.setWeight(75);
        groupCamera->setFont(font2);
        groupCamera->setAutoFillBackground(false);
        groupCamera->setStyleSheet(QLatin1String("background-color: rgb(249, 249, 249);\n"
"border-radius: 5px;"));
        groupCamera->setAlignment(Qt::AlignCenter);
        comboCamera = new QComboBox(groupCamera);
        comboCamera->setObjectName(QStringLiteral("comboCamera"));
        comboCamera->setGeometry(QRect(10, 40, 81, 41));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(comboCamera->sizePolicy().hasHeightForWidth());
        comboCamera->setSizePolicy(sizePolicy3);
        comboCamera->setFont(font1);
        comboCamera->setStyleSheet(QLatin1String(" QComboBox {\n"
"	background-color: rgb(255, 100, 100);\n"
"	color: rgb(240, 240, 240);\n"
"    border-radius: 10px;\n"
"}\n"
"\n"
"QComboBox:on {\n"
"	background-color: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.499001, fy:0.000500999, stop:0 rgba(152, 152, 152, 217), stop:1 rgba(0, 0, 0, 232));\n"
"     padding-top: 3px;\n"
"     padding-left: 4px;\n"
"}\n"
"\n"
"QComboBox::down-arrow {\n"
"	image: url(:/AppMain/down_arrow.ico);\n"
"}\n"
"\n"
"QComboBox::drop-down {\n"
"     border-left-color: rgb(240, 240, 240);\n"
"}\n"
"\n"
"QComboBox QAbstractItemView {\n"
"     selection-background-color: rgb(80, 80, 80);\n"
"}"));
        groupCurve = new QGroupBox(groupBox_5);
        groupCurve->setObjectName(QStringLiteral("groupCurve"));
        groupCurve->setGeometry(QRect(130, 10, 100, 100));
        sizePolicy2.setHeightForWidth(groupCurve->sizePolicy().hasHeightForWidth());
        groupCurve->setSizePolicy(sizePolicy2);
        groupCurve->setMinimumSize(QSize(100, 100));
        groupCurve->setMaximumSize(QSize(100, 100));
        groupCurve->setFont(font2);
        groupCurve->setStyleSheet(QLatin1String("background-color: rgb(249, 249, 249);\n"
"border-radius: 5px;"));
        groupCurve->setAlignment(Qt::AlignCenter);
        comboCurve = new QComboBox(groupCurve);
        comboCurve->setObjectName(QStringLiteral("comboCurve"));
        comboCurve->setGeometry(QRect(10, 40, 81, 41));
        sizePolicy3.setHeightForWidth(comboCurve->sizePolicy().hasHeightForWidth());
        comboCurve->setSizePolicy(sizePolicy3);
        comboCurve->setFont(font1);
        comboCurve->setStyleSheet(QLatin1String(" QComboBox {\n"
"	background-color: rgb(255, 100, 100);\n"
"	color: rgb(240, 240, 240);\n"
"    border-radius: 10px;\n"
"}\n"
"\n"
"QComboBox:on {\n"
"	background-color: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.499001, fy:0.000500999, stop:0 rgba(152, 152, 152, 217), stop:1 rgba(0, 0, 0, 232));\n"
"     padding-top: 3px;\n"
"     padding-left: 4px;\n"
"}\n"
"\n"
"QComboBox::down-arrow {\n"
"	image: url(:/AppMain/down_arrow.ico);\n"
"}\n"
"\n"
"QComboBox::drop-down {\n"
"     border-left-color: rgb(240, 240, 240);\n"
"}\n"
"\n"
"QComboBox QAbstractItemView {\n"
"     selection-background-color: rgb(80, 80, 80);\n"
"}"));
        groupTrack = new QGroupBox(groupBox_5);
        groupTrack->setObjectName(QStringLiteral("groupTrack"));
        groupTrack->setGeometry(QRect(20, 120, 100, 100));
        sizePolicy2.setHeightForWidth(groupTrack->sizePolicy().hasHeightForWidth());
        groupTrack->setSizePolicy(sizePolicy2);
        groupTrack->setMinimumSize(QSize(100, 100));
        groupTrack->setMaximumSize(QSize(100, 100));
        groupTrack->setFont(font2);
        groupTrack->setStyleSheet(QLatin1String("background-color: rgb(249, 249, 249);\n"
"border-radius: 5px;"));
        groupTrack->setAlignment(Qt::AlignCenter);
        comboTrack = new QComboBox(groupTrack);
        comboTrack->setObjectName(QStringLiteral("comboTrack"));
        comboTrack->setGeometry(QRect(10, 40, 81, 41));
        sizePolicy3.setHeightForWidth(comboTrack->sizePolicy().hasHeightForWidth());
        comboTrack->setSizePolicy(sizePolicy3);
        comboTrack->setFont(font1);
        comboTrack->setStyleSheet(QLatin1String(" QComboBox {\n"
"	background-color: rgb(255, 100, 100);\n"
"	color: rgb(240, 240, 240);\n"
"    border-radius: 10px;\n"
"}\n"
"\n"
"QComboBox:on {\n"
"	background-color: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.499001, fy:0.000500999, stop:0 rgba(152, 152, 152, 217), stop:1 rgba(0, 0, 0, 232));\n"
"     padding-top: 3px;\n"
"     padding-left: 4px;\n"
"}\n"
"\n"
"QComboBox::down-arrow {\n"
"	image: url(:/AppMain/down_arrow.ico);\n"
"}\n"
"\n"
"QComboBox::drop-down {\n"
"     border-left-color: rgb(240, 240, 240);\n"
"}\n"
"\n"
"QComboBox QAbstractItemView {\n"
"     selection-background-color: rgb(80, 80, 80);\n"
"}"));
        comboTrack->setSizeAdjustPolicy(QComboBox::AdjustToContentsOnFirstShow);
        groupTrain = new QGroupBox(groupBox_5);
        groupTrain->setObjectName(QStringLiteral("groupTrain"));
        groupTrain->setGeometry(QRect(130, 120, 100, 100));
        sizePolicy2.setHeightForWidth(groupTrain->sizePolicy().hasHeightForWidth());
        groupTrain->setSizePolicy(sizePolicy2);
        groupTrain->setMinimumSize(QSize(100, 100));
        groupTrain->setMaximumSize(QSize(100, 100));
        groupTrain->setFont(font2);
        groupTrain->setStyleSheet(QLatin1String("background-color: rgb(249, 249, 249);\n"
"border-radius: 5px;"));
        groupTrain->setAlignment(Qt::AlignCenter);
        comboTrain = new QComboBox(groupTrain);
        comboTrain->setObjectName(QStringLiteral("comboTrain"));
        comboTrain->setGeometry(QRect(10, 40, 81, 41));
        sizePolicy3.setHeightForWidth(comboTrain->sizePolicy().hasHeightForWidth());
        comboTrain->setSizePolicy(sizePolicy3);
        comboTrain->setFont(font1);
        comboTrain->setStyleSheet(QLatin1String(" QComboBox {\n"
"	background-color: rgb(255, 100, 100);\n"
"	color: rgb(240, 240, 240);\n"
"    border-radius: 10px;\n"
"}\n"
"\n"
"QComboBox:on {\n"
"	background-color: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.499001, fy:0.000500999, stop:0 rgba(152, 152, 152, 217), stop:1 rgba(0, 0, 0, 232));\n"
"     padding-top: 3px;\n"
"     padding-left: 4px;\n"
"}\n"
"\n"
"QComboBox::down-arrow {\n"
"	image: url(:/AppMain/down_arrow.ico);\n"
"}\n"
"\n"
"QComboBox::drop-down {\n"
"     border-left-color: rgb(240, 240, 240);\n"
"}\n"
"\n"
"QComboBox QAbstractItemView {\n"
"     selection-background-color: rgb(80, 80, 80);\n"
"}"));
        comboTrain->setSizeAdjustPolicy(QComboBox::AdjustToContentsOnFirstShow);
        groupCP = new QGroupBox(groupBox_5);
        groupCP->setObjectName(QStringLiteral("groupCP"));
        groupCP->setGeometry(QRect(20, 230, 100, 80));
        sizePolicy2.setHeightForWidth(groupCP->sizePolicy().hasHeightForWidth());
        groupCP->setSizePolicy(sizePolicy2);
        groupCP->setMinimumSize(QSize(100, 80));
        groupCP->setMaximumSize(QSize(100, 80));
        groupCP->setFont(font2);
        groupCP->setMouseTracking(false);
        groupCP->setAutoFillBackground(false);
        groupCP->setStyleSheet(QLatin1String("background-color: rgb(249, 249, 249);\n"
"border-radius: 5px;"));
        groupCP->setAlignment(Qt::AlignCenter);
        groupCP->setFlat(false);
        groupCP->setCheckable(false);
        bAdd = new QPushButton(groupCP);
        bAdd->setObjectName(QStringLiteral("bAdd"));
        bAdd->setGeometry(QRect(10, 30, 31, 31));
        sizePolicy2.setHeightForWidth(bAdd->sizePolicy().hasHeightForWidth());
        bAdd->setSizePolicy(sizePolicy2);
        bAdd->setFont(font1);
        bAdd->setStyleSheet(QLatin1String(" QPushButton {\n"
"	background-color: rgb(150, 150, 255);\n"
"	color: rgb(240, 240, 240);\n"
"    border-radius: 10px;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"	background-color: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, stop:0 rgba(172, 172, 172, 255), stop:1 rgba(0, 0, 0, 203));\n"
"     padding-top: 10px;\n"
"     padding-left: 5px;\n"
"}"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/AppMain/madd.png"), QSize(), QIcon::Normal, QIcon::Off);
        bAdd->setIcon(icon3);
        bAdd->setIconSize(QSize(14, 14));
        bDelete = new QPushButton(groupCP);
        bDelete->setObjectName(QStringLiteral("bDelete"));
        bDelete->setGeometry(QRect(50, 30, 31, 31));
        sizePolicy2.setHeightForWidth(bDelete->sizePolicy().hasHeightForWidth());
        bDelete->setSizePolicy(sizePolicy2);
        bDelete->setFont(font1);
        bDelete->setFocusPolicy(Qt::ClickFocus);
        bDelete->setStyleSheet(QLatin1String(" QPushButton {\n"
"	background-color: rgb(150, 150, 255);\n"
"	color: rgb(240, 240, 240);\n"
"    border-radius: 10px;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"	background-color: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, stop:0 rgba(172, 172, 172, 255), stop:1 rgba(0, 0, 0, 203));\n"
"     padding-top: 10px;\n"
"     padding-left: 5px;\n"
"}"));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/AppMain/mdelete.png"), QSize(), QIcon::Normal, QIcon::Off);
        bDelete->setIcon(icon4);
        bDelete->setIconSize(QSize(12, 12));
        groupBox = new QGroupBox(groupBox_5);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(20, 320, 100, 200));
        sizePolicy2.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy2);
        groupBox->setMinimumSize(QSize(100, 200));
        groupBox->setMaximumSize(QSize(100, 200));
        QPalette palette;
        QBrush brush(QColor(249, 249, 249, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush);
        palette.setBrush(QPalette::Active, QPalette::Base, brush);
        palette.setBrush(QPalette::Active, QPalette::Window, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush);
        groupBox->setPalette(palette);
        groupBox->setFont(font2);
        groupBox->setStyleSheet(QLatin1String("background-color: rgb(249, 249, 249);\n"
"border-radius: 5px;"));
        groupBox->setAlignment(Qt::AlignCenter);
        groupBox->setFlat(false);
        groupBox->setCheckable(false);
        rcpxadd = new QPushButton(groupBox);
        rcpxadd->setObjectName(QStringLiteral("rcpxadd"));
        rcpxadd->setGeometry(QRect(20, 40, 31, 31));
        sizePolicy2.setHeightForWidth(rcpxadd->sizePolicy().hasHeightForWidth());
        rcpxadd->setSizePolicy(sizePolicy2);
        rcpxadd->setStyleSheet(QLatin1String("QPushButton {\n"
"	background-color: rgb(150, 150, 255);\n"
"	color: rgb(240, 240, 240);\n"
"    border-radius: 10px;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"	background-color: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, stop:0 rgba(172, 172, 172, 255), stop:1 rgba(0, 0, 0, 203));\n"
"     padding-top: 10px;\n"
"     padding-left: 5px;\n"
"}"));
        rcpxadd->setIcon(icon3);
        rcpxadd->setIconSize(QSize(14, 14));
        rcpxsub = new QPushButton(groupBox);
        rcpxsub->setObjectName(QStringLiteral("rcpxsub"));
        rcpxsub->setGeometry(QRect(60, 40, 31, 31));
        rcpxsub->setStyleSheet(QLatin1String("QPushButton {\n"
"	background-color: rgb(150, 150, 255);\n"
"	color: rgb(240, 240, 240);\n"
"    border-radius: 10px;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"	background-color: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, stop:0 rgba(172, 172, 172, 255), stop:1 rgba(0, 0, 0, 203));\n"
"     padding-top: 10px;\n"
"     padding-left: 5px;\n"
"}"));
        rcpxsub->setIcon(icon4);
        rcpzadd = new QPushButton(groupBox);
        rcpzadd->setObjectName(QStringLiteral("rcpzadd"));
        rcpzadd->setGeometry(QRect(20, 80, 31, 31));
        sizePolicy2.setHeightForWidth(rcpzadd->sizePolicy().hasHeightForWidth());
        rcpzadd->setSizePolicy(sizePolicy2);
        rcpzadd->setStyleSheet(QLatin1String("QPushButton {\n"
"	background-color: rgb(150, 150, 255);\n"
"	color: rgb(240, 240, 240);\n"
"    border-radius: 10px;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"	background-color: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, stop:0 rgba(172, 172, 172, 255), stop:1 rgba(0, 0, 0, 203));\n"
"     padding-top: 10px;\n"
"     padding-left: 5px;\n"
"}"));
        rcpzadd->setIcon(icon3);
        rcpzsub = new QPushButton(groupBox);
        rcpzsub->setObjectName(QStringLiteral("rcpzsub"));
        rcpzsub->setGeometry(QRect(60, 80, 31, 31));
        rcpzsub->setStyleSheet(QLatin1String("QPushButton {\n"
"	background-color: rgb(150, 150, 255);\n"
"	color: rgb(240, 240, 240);\n"
"    border-radius: 10px;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"	background-color: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, stop:0 rgba(172, 172, 172, 255), stop:1 rgba(0, 0, 0, 203));\n"
"     padding-top: 10px;\n"
"     padding-left: 5px;\n"
"}"));
        rcpzsub->setIcon(icon4);
        rcpysub = new QPushButton(groupBox);
        rcpysub->setObjectName(QStringLiteral("rcpysub"));
        rcpysub->setGeometry(QRect(60, 120, 31, 31));
        rcpysub->setStyleSheet(QLatin1String("QPushButton {\n"
"	background-color: rgb(150, 150, 255);\n"
"	color: rgb(240, 240, 240);\n"
"    border-radius: 10px;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"	background-color: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, stop:0 rgba(172, 172, 172, 255), stop:1 rgba(0, 0, 0, 203));\n"
"     padding-top: 10px;\n"
"     padding-left: 5px;\n"
"}"));
        rcpysub->setIcon(icon4);
        rcpyadd = new QPushButton(groupBox);
        rcpyadd->setObjectName(QStringLiteral("rcpyadd"));
        rcpyadd->setGeometry(QRect(20, 120, 31, 31));
        sizePolicy2.setHeightForWidth(rcpyadd->sizePolicy().hasHeightForWidth());
        rcpyadd->setSizePolicy(sizePolicy2);
        rcpyadd->setStyleSheet(QLatin1String("QPushButton {\n"
"	background-color: rgb(150, 150, 255);\n"
"	color: rgb(240, 240, 240);\n"
"    border-radius: 10px;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"	background-color: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, stop:0 rgba(172, 172, 172, 255), stop:1 rgba(0, 0, 0, 203));\n"
"     padding-top: 10px;\n"
"     padding-left: 5px;\n"
"}"));
        rcpyadd->setIcon(icon3);
        groupBox_3 = new QGroupBox(groupBox_5);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setGeometry(QRect(130, 230, 100, 80));
        groupBox_3->setMinimumSize(QSize(100, 80));
        groupBox_3->setMaximumSize(QSize(100, 80));
        groupBox_3->setFont(font2);
        groupBox_3->setStyleSheet(QLatin1String("background-color: rgb(249, 249, 249);\n"
"border-radius: 5px;"));
        rcpBoxadd = new QPushButton(groupBox_3);
        rcpBoxadd->setObjectName(QStringLiteral("rcpBoxadd"));
        rcpBoxadd->setGeometry(QRect(10, 30, 31, 31));
        sizePolicy2.setHeightForWidth(rcpBoxadd->sizePolicy().hasHeightForWidth());
        rcpBoxadd->setSizePolicy(sizePolicy2);
        rcpBoxadd->setStyleSheet(QLatin1String("QPushButton {\n"
"	background-color: rgb(150, 150, 255);\n"
"	color: rgb(240, 240, 240);\n"
"    border-radius: 10px;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"	background-color: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, stop:0 rgba(172, 172, 172, 255), stop:1 rgba(0, 0, 0, 203));\n"
"     padding-top: 10px;\n"
"     padding-left: 5px;\n"
"}"));
        rcpBoxadd->setIcon(icon3);
        rcpBoxsub = new QPushButton(groupBox_3);
        rcpBoxsub->setObjectName(QStringLiteral("rcpBoxsub"));
        rcpBoxsub->setGeometry(QRect(50, 30, 31, 31));
        rcpBoxsub->setStyleSheet(QLatin1String("QPushButton {\n"
"	background-color: rgb(150, 150, 255);\n"
"	color: rgb(240, 240, 240);\n"
"    border-radius: 10px;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"	background-color: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, stop:0 rgba(172, 172, 172, 255), stop:1 rgba(0, 0, 0, 203));\n"
"     padding-top: 10px;\n"
"     padding-left: 5px;\n"
"}"));
        rcpBoxsub->setIcon(icon4);
        groupCP_2 = new QGroupBox(groupBox_5);
        groupCP_2->setObjectName(QStringLiteral("groupCP_2"));
        groupCP_2->setGeometry(QRect(130, 320, 100, 200));
        sizePolicy2.setHeightForWidth(groupCP_2->sizePolicy().hasHeightForWidth());
        groupCP_2->setSizePolicy(sizePolicy2);
        groupCP_2->setMinimumSize(QSize(100, 200));
        groupCP_2->setMaximumSize(QSize(100, 200));
        groupCP_2->setFont(font2);
        groupCP_2->setMouseTracking(false);
        groupCP_2->setAutoFillBackground(false);
        groupCP_2->setStyleSheet(QLatin1String("background-color: rgb(249, 249, 249);\n"
"border-radius: 5px;"));
        groupCP_2->setAlignment(Qt::AlignCenter);
        groupCP_2->setFlat(false);
        groupCP_2->setCheckable(false);
        people = new QPushButton(groupCP_2);
        people->setObjectName(QStringLiteral("people"));
        people->setGeometry(QRect(20, 40, 31, 31));
        sizePolicy2.setHeightForWidth(people->sizePolicy().hasHeightForWidth());
        people->setSizePolicy(sizePolicy2);
        people->setFont(font1);
        people->setStyleSheet(QLatin1String(" QPushButton {\n"
"	background-color: rgb(150, 150, 255);\n"
"	color: rgb(240, 240, 240);\n"
"    border-radius: 10px;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"	background-color: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, stop:0 rgba(172, 172, 172, 255), stop:1 rgba(0, 0, 0, 203));\n"
"     padding-top: 10px;\n"
"     padding-left: 5px;\n"
"}"));
        people->setIconSize(QSize(14, 14));
        cave = new QPushButton(groupCP_2);
        cave->setObjectName(QStringLiteral("cave"));
        cave->setGeometry(QRect(60, 40, 31, 31));
        sizePolicy2.setHeightForWidth(cave->sizePolicy().hasHeightForWidth());
        cave->setSizePolicy(sizePolicy2);
        cave->setFont(font1);
        cave->setFocusPolicy(Qt::ClickFocus);
        cave->setStyleSheet(QLatin1String(" QPushButton {\n"
"	background-color: rgb(150, 150, 255);\n"
"	color: rgb(240, 240, 240);\n"
"    border-radius: 10px;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"	background-color: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, stop:0 rgba(172, 172, 172, 255), stop:1 rgba(0, 0, 0, 203));\n"
"     padding-top: 10px;\n"
"     padding-left: 5px;\n"
"}"));
        cave->setIconSize(QSize(12, 12));
        w = new QPushButton(groupCP_2);
        w->setObjectName(QStringLiteral("w"));
        w->setGeometry(QRect(20, 80, 31, 31));
        sizePolicy2.setHeightForWidth(w->sizePolicy().hasHeightForWidth());
        w->setSizePolicy(sizePolicy2);
        w->setFont(font1);
        w->setFocusPolicy(Qt::ClickFocus);
        w->setStyleSheet(QLatin1String(" QPushButton {\n"
"	background-color: rgb(150, 150, 255);\n"
"	color: rgb(240, 240, 240);\n"
"    border-radius: 10px;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"	background-color: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, stop:0 rgba(172, 172, 172, 255), stop:1 rgba(0, 0, 0, 203));\n"
"     padding-top: 10px;\n"
"     padding-left: 5px;\n"
"}"));
        w->setIconSize(QSize(12, 12));
        pushButton_2 = new QPushButton(groupCP_2);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(60, 80, 31, 31));
        sizePolicy2.setHeightForWidth(pushButton_2->sizePolicy().hasHeightForWidth());
        pushButton_2->setSizePolicy(sizePolicy2);
        pushButton_2->setFont(font1);
        pushButton_2->setStyleSheet(QLatin1String(" QPushButton {\n"
"	background-color: rgb(150, 150, 255);\n"
"	color: rgb(240, 240, 240);\n"
"    border-radius: 10px;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"	background-color: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, stop:0 rgba(172, 172, 172, 255), stop:1 rgba(0, 0, 0, 203));\n"
"     padding-top: 10px;\n"
"     padding-left: 5px;\n"
"}"));
        pushButton_2->setIconSize(QSize(14, 14));
        GS = new QPushButton(groupCP_2);
        GS->setObjectName(QStringLiteral("GS"));
        GS->setGeometry(QRect(60, 120, 31, 31));
        sizePolicy2.setHeightForWidth(GS->sizePolicy().hasHeightForWidth());
        GS->setSizePolicy(sizePolicy2);
        GS->setFont(font1);
        GS->setFocusPolicy(Qt::ClickFocus);
        GS->setStyleSheet(QLatin1String(" QPushButton {\n"
"	background-color: rgb(150, 150, 255);\n"
"	color: rgb(240, 240, 240);\n"
"    border-radius: 10px;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"	background-color: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, stop:0 rgba(172, 172, 172, 255), stop:1 rgba(0, 0, 0, 203));\n"
"     padding-top: 10px;\n"
"     padding-left: 5px;\n"
"}"));
        GS->setIconSize(QSize(12, 12));
        YS = new QPushButton(groupCP_2);
        YS->setObjectName(QStringLiteral("YS"));
        YS->setGeometry(QRect(20, 120, 31, 31));
        sizePolicy2.setHeightForWidth(YS->sizePolicy().hasHeightForWidth());
        YS->setSizePolicy(sizePolicy2);
        YS->setFont(font1);
        YS->setFocusPolicy(Qt::ClickFocus);
        YS->setStyleSheet(QLatin1String(" QPushButton {\n"
"	background-color: rgb(150, 150, 255);\n"
"	color: rgb(240, 240, 240);\n"
"    border-radius: 10px;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"	background-color: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, stop:0 rgba(172, 172, 172, 255), stop:1 rgba(0, 0, 0, 203));\n"
"     padding-top: 10px;\n"
"     padding-left: 5px;\n"
"}"));
        YS->setIconSize(QSize(12, 12));

        horizontalLayout_3->addWidget(groupBox_5);


        verticalLayout->addLayout(horizontalLayout_3);

        AppMainClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(AppMainClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1426, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuCamera = new QMenu(menuBar);
        menuCamera->setObjectName(QStringLiteral("menuCamera"));
        menuCurve = new QMenu(menuBar);
        menuCurve->setObjectName(QStringLiteral("menuCurve"));
        menuTrack = new QMenu(menuBar);
        menuTrack->setObjectName(QStringLiteral("menuTrack"));
        menuVelocity = new QMenu(menuBar);
        menuVelocity->setObjectName(QStringLiteral("menuVelocity"));
        AppMainClass->setMenuBar(menuBar);
        statusBar = new QStatusBar(AppMainClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        AppMainClass->setStatusBar(statusBar);
        mainToolBar = new QToolBar(AppMainClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        AppMainClass->addToolBar(Qt::TopToolBarArea, mainToolBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuCamera->menuAction());
        menuBar->addAction(menuTrack->menuAction());
        menuBar->addAction(menuCurve->menuAction());
        menuBar->addAction(menuVelocity->menuAction());
        menuFile->addAction(aLoadPath);
        menuFile->addAction(aSavePath);
        menuFile->addSeparator();
        menuFile->addAction(aExit);
        menuCamera->addAction(aWorld);
        menuCamera->addAction(aTop);
        menuCamera->addAction(aTrain);
        menuCurve->addAction(aLinear);
        menuCurve->addAction(aCardinal);
        menuCurve->addAction(aCubic);
        menuTrack->addAction(aLine);
        menuTrack->addAction(aTrack);
        menuTrack->addAction(aRoad);
        menuVelocity->addAction(atrain);
        menuVelocity->addAction(aBox);
        mainToolBar->addAction(aLoadPath);
        mainToolBar->addAction(aSavePath);

        retranslateUi(AppMainClass);

        QMetaObject::connectSlotsByName(AppMainClass);
    } // setupUi

    void retranslateUi(QMainWindow *AppMainClass)
    {
        AppMainClass->setWindowTitle(QApplication::translate("AppMainClass", "AppMain", 0));
        aExit->setText(QApplication::translate("AppMainClass", "Exit", 0));
        aLoadPath->setText(QApplication::translate("AppMainClass", "Load Path", 0));
        aSavePath->setText(QApplication::translate("AppMainClass", "Save Path", 0));
        aWorld->setText(QApplication::translate("AppMainClass", "World", 0));
        aTop->setText(QApplication::translate("AppMainClass", "Top", 0));
        aTrain->setText(QApplication::translate("AppMainClass", "Train", 0));
        aLinear->setText(QApplication::translate("AppMainClass", "Linear", 0));
        aCardinal->setText(QApplication::translate("AppMainClass", "Cardinal", 0));
        aCubic->setText(QApplication::translate("AppMainClass", "Cubic", 0));
        aLine->setText(QApplication::translate("AppMainClass", "Line", 0));
        aTrack->setText(QApplication::translate("AppMainClass", "Track", 0));
        aRoad->setText(QApplication::translate("AppMainClass", "Road", 0));
        atrain->setText(QApplication::translate("AppMainClass", "train", 0));
        aBox->setText(QApplication::translate("AppMainClass", "box", 0));
        actionClose_Splash->setText(QApplication::translate("AppMainClass", "Close Splash", 0));
        close->setText(QApplication::translate("AppMainClass", "Close", 0));
        bPlay->setText(QString());
        groupBox_5->setTitle(QString());
        groupCamera->setTitle(QApplication::translate("AppMainClass", "Camera", 0));
        comboCamera->clear();
        comboCamera->insertItems(0, QStringList()
         << QApplication::translate("AppMainClass", "World", 0)
         << QApplication::translate("AppMainClass", "Top", 0)
         << QApplication::translate("AppMainClass", "Train", 0)
        );
        groupCurve->setTitle(QApplication::translate("AppMainClass", "Curve", 0));
        comboCurve->clear();
        comboCurve->insertItems(0, QStringList()
         << QApplication::translate("AppMainClass", "Linear", 0)
         << QApplication::translate("AppMainClass", "Cardinal", 0)
         << QApplication::translate("AppMainClass", "Cubic", 0)
        );
        groupTrack->setTitle(QApplication::translate("AppMainClass", "Track", 0));
        comboTrack->clear();
        comboTrack->insertItems(0, QStringList()
         << QApplication::translate("AppMainClass", "Line", 0)
         << QApplication::translate("AppMainClass", "Track", 0)
         << QApplication::translate("AppMainClass", "Road", 0)
         << QApplication::translate("AppMainClass", "Points", 0)
        );
        groupTrain->setTitle(QApplication::translate("AppMainClass", "Train", 0));
        comboTrain->clear();
        comboTrain->insertItems(0, QStringList()
         << QApplication::translate("AppMainClass", "train", 0)
         << QApplication::translate("AppMainClass", "box", 0)
         << QApplication::translate("AppMainClass", "bug", 0)
         << QApplication::translate("AppMainClass", "other", 0)
        );
        groupCP->setTitle(QApplication::translate("AppMainClass", "Ctrl Point", 0));
        bAdd->setText(QString());
        bDelete->setText(QString());
        groupBox->setTitle(QApplication::translate("AppMainClass", "Rotate X Y Z", 0));
        rcpxadd->setText(QApplication::translate("AppMainClass", "X", 0));
        rcpxsub->setText(QApplication::translate("AppMainClass", "X", 0));
        rcpzadd->setText(QApplication::translate("AppMainClass", "Z", 0));
        rcpzsub->setText(QApplication::translate("AppMainClass", "Z", 0));
        rcpysub->setText(QApplication::translate("AppMainClass", "Y", 0));
        rcpyadd->setText(QApplication::translate("AppMainClass", "Y", 0));
        groupBox_3->setTitle(QApplication::translate("AppMainClass", "Plus box", 0));
        rcpBoxadd->setText(QString());
        rcpBoxsub->setText(QString());
        groupCP_2->setTitle(QApplication::translate("AppMainClass", "Other", 0));
        people->setText(QApplication::translate("AppMainClass", "Y", 0));
        cave->setText(QApplication::translate("AppMainClass", "C", 0));
        w->setText(QApplication::translate("AppMainClass", "W", 0));
        pushButton_2->setText(QApplication::translate("AppMainClass", "D", 0));
        GS->setText(QApplication::translate("AppMainClass", "GS", 0));
        YS->setText(QApplication::translate("AppMainClass", "YS", 0));
        menuFile->setTitle(QApplication::translate("AppMainClass", "File", 0));
        menuCamera->setTitle(QApplication::translate("AppMainClass", "Camera", 0));
        menuCurve->setTitle(QApplication::translate("AppMainClass", "Curve", 0));
        menuTrack->setTitle(QApplication::translate("AppMainClass", "Track", 0));
        menuVelocity->setTitle(QApplication::translate("AppMainClass", "Velocity", 0));
    } // retranslateUi

};

namespace Ui {
    class AppMainClass: public Ui_AppMainClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_APPMAIN_H
