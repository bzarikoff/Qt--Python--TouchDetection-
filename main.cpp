///****************************************************************************
//**
//** Copyright (C) 2016 The Qt Company Ltd.
//** Contact: https://www.qt.io/licensing/
//**
//** This file is part of the Qt Data Visualization module of the Qt Toolkit.
//**
//** $QT_BEGIN_LICENSE:GPL$
//** Commercial License Usage
//** Licensees holding valid commercial Qt licenses may use this file in
//** accordance with the commercial license agreement provided with the
//** Software or, alternatively, in accordance with the terms contained in
//** a written agreement between you and The Qt Company. For licensing terms
//** and conditions see https://www.qt.io/terms-conditions. For further
//** information use the contact form at https://www.qt.io/contact-us.
//**
//** GNU General Public License Usage
//** Alternatively, this file may be used under the terms of the GNU
//** General Public License version 3 or (at your option) any later version
//** approved by the KDE Free Qt Foundation. The licenses are as published by
//** the Free Software Foundation and appearing in the file LICENSE.GPL3
//** included in the packaging of this file. Please review the following
//** information to ensure the GNU General Public License requirements will
//** be met: https://www.gnu.org/licenses/gpl-3.0.html.
//**
//** $QT_END_LICENSE$
//**
//****************************************************************************/





/*
 *This code is for receiving raw data and touch data from python over a socket connection
 *The data is then displayed in two graphs simultaneously
 */





#include "surfacegraph.h"
#include "chartview.h"

#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMessageBox>
#include <QtGui/QPainter>
#include <QtGui/QScreen>


#include <QtSerialPort/QSerialPort>

#include <QTextStream>
#include <QCoreApplication>
#include <QFile>
#include <QStringList>
#include <QtDebug>
#include <QObject>
#include <QString>
#include <iostream>
#include <stdlib.h>
#include <bits/stdc++.h>
#include <string.h>
#include <stdio.h>
#include <QTimer>

#include <QSerialPortInfo>
#include <QComboBox>
#include <QWindow>

#include <winsock.h>
#include <winsock2.h>
#include <sys/types.h>
#include <iostream>
#include <stdio.h>
#include <io.h>
#include <ws2tcpip.h>
#include <string.h>
#include <qstring.h>
#include <sstream>

#include <QtWidgets/QMainWindow>

#define PORT "5555"//27015//5555
#define DEFAULT_BUFLEN 2048

ChartView *chartView;// = new ChartView();


//int integertest[16][24];

QT_USE_NAMESPACE
QT_CHARTS_USE_NAMESPACE


//ChartView *chartView = new ChartView();


int main(int argc, char **argv)
{


//connects to socket in python


    printf("\nInitialising Winsock...");
    if (WSAStartup(MAKEWORD(2,2),&wsa)!=0)
    {
        printf("Failed. Error Code : %d",WSAGetLastError());
        return 1;
    }

    printf("Initialised.\n");



    // ///////////////////////////////////////////////////////


    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

   //Resolve the local address and port to be used by the server
    iResult = getaddrinfo(NULL, PORT, &hints, &result);
    if(iResult != 0){
        printf("getaddrinfo failed: %d\n", iResult);
        WSACleanup();
        return 1;
    }



    // ////////////////////////////////////////////////////////

    //Create Socket
    //if((s = socket(AF_INET , SOCK_STREAM , 0)) == INVALID_SOCKET)
    if((s = socket(result->ai_family , result->ai_socktype , result->ai_protocol)) == INVALID_SOCKET)
    {
        printf("Could not create socket : %d" , WSAGetLastError());
    }

    printf("Socket created.\n");



    //if(setsocketopt(s, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)))


    //Prepare the sockaddr_in structure
    //server.sin_family = AF_INET;
   // server.sin_addr.s_addr = INADDR_ANY;
   // server.sin_port = htons( PORT );

    //Bind
    if(bind(s, result->ai_addr, (int)result->ai_addrlen) == SOCKET_ERROR)                                       //bind(s ,(struct sockaddr *)&server , sizeof(server)) == SOCKET_ERROR);
    {
        printf("Bind failed with error code : %d " , WSAGetLastError());
    }

    puts("Bind done");

    //Listen to incoming connections
    listen(s , SOMAXCONN);//3);

    //Accept and incoming connections
    puts("Waiting for incoming connections...");

    c = sizeof(struct sockaddr_in);
    new_socket = accept(s, NULL, NULL);//(struct sockaddr *)&client, &c);
    if(new_socket == INVALID_SOCKET)
    {
        printf("accept failed with error code : %d", WSAGetLastError());
    }

    puts("Connection accepted");

// ////////////////////////////////////////
//  Creates Main Window for graphs
// ///////////////////////////////////////

    //note that start, stop and com port are not used for this codes function
    //as all the data is received over the socket from the beginning

    QTextStream standardOutput(stdout);
    QApplication app(argc, argv);


chartView = new ChartView();

Q3DSurface *graph = new Q3DSurface();
//Q3DSurface *graph2 = new Q3DSurface();
QWidget *container = QWidget::createWindowContainer(graph);
//QWidget *container2 = QWidget::createWindowContainer(graph2);
//QWidget *container2 = QWidget::createWindowContainer(chartView);

if (!graph->hasContext()) {
    QMessageBox msgBox;
    msgBox.setText("Couldn't initialize the OpenGL context.");
    msgBox.exec();
    return -1;
}



QSize screenSize = graph->screen()->size();
container->setMinimumSize(QSize(screenSize.width() / 2, screenSize.height() / 4));//1.6
container->setMaximumSize(screenSize);
container->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
container->setFocusPolicy(Qt::StrongFocus);



//formatting layout
//! [1]
QWidget *widget = new QWidget;
QHBoxLayout *hLayout = new QHBoxLayout(widget);
QVBoxLayout *vLayout = new QVBoxLayout();
QVBoxLayout *testLayout = new QVBoxLayout(widget);
testLayout->addWidget(container,1);
testLayout->addWidget(chartView, 1);
hLayout->addLayout(testLayout, 1);//container addWidget
//   vLayout->addWidget(container2, 1);
hLayout->addLayout(vLayout);
vLayout->setAlignment(Qt::AlignTop);
//! [1]

//sets up various buttons and controls

widget->setWindowTitle(QStringLiteral("Surface example"));

QGroupBox *modelGroupBox = new QGroupBox(QStringLiteral("Model"));

QRadioButton *sqrtSinModelRB = new QRadioButton(widget);
sqrtSinModelRB->setText(QStringLiteral("Raw Data"));
sqrtSinModelRB->setChecked(false);

QRadioButton *heightMapModelRB = new QRadioButton(widget);
heightMapModelRB->setText(QStringLiteral("Touch Data"));
heightMapModelRB->setChecked(false);

QVBoxLayout *modelVBox = new QVBoxLayout;
modelVBox->addWidget(sqrtSinModelRB);
modelVBox->addWidget(heightMapModelRB);
modelGroupBox->setLayout(modelVBox);

QGroupBox *selectionGroupBox = new QGroupBox(QStringLiteral("Selection Mode"));

QRadioButton *modeNoneRB = new QRadioButton(widget);
modeNoneRB->setText(QStringLiteral("No selection"));
modeNoneRB->setChecked(false);

QRadioButton *modeItemRB = new QRadioButton(widget);
modeItemRB->setText(QStringLiteral("Item"));
modeItemRB->setChecked(false);

QRadioButton *modeSliceRowRB = new QRadioButton(widget);
modeSliceRowRB->setText(QStringLiteral("Row Slice"));
modeSliceRowRB->setChecked(false);

QRadioButton *modeSliceColumnRB = new QRadioButton(widget);
modeSliceColumnRB->setText(QStringLiteral("Column Slice"));
modeSliceColumnRB->setChecked(false);

QVBoxLayout *selectionVBox = new QVBoxLayout;
selectionVBox->addWidget(modeNoneRB);
selectionVBox->addWidget(modeItemRB);
selectionVBox->addWidget(modeSliceRowRB);
selectionVBox->addWidget(modeSliceColumnRB);
selectionGroupBox->setLayout(selectionVBox);

QSlider *axisMinSliderX = new QSlider(Qt::Horizontal, widget);
axisMinSliderX->setMinimum(0);
axisMinSliderX->setTickInterval(1);
axisMinSliderX->setEnabled(true);
QSlider *axisMaxSliderX = new QSlider(Qt::Horizontal, widget);
axisMaxSliderX->setMinimum(1);
axisMaxSliderX->setTickInterval(1);
axisMaxSliderX->setEnabled(true);
QSlider *axisMinSliderZ = new QSlider(Qt::Horizontal, widget);
axisMinSliderZ->setMinimum(0);
axisMinSliderZ->setTickInterval(1);
axisMinSliderZ->setEnabled(true);
QSlider *axisMaxSliderZ = new QSlider(Qt::Horizontal, widget);
axisMaxSliderZ->setMinimum(1);
axisMaxSliderZ->setTickInterval(1);
axisMaxSliderZ->setEnabled(true);


QSlider *axisMinSliderY = new QSlider(Qt::Horizontal, widget);
axisMinSliderY->setMinimum(0);
axisMinSliderY->setTickInterval(1);
axisMinSliderY->setEnabled(true);
QSlider *axisMaxSliderY = new QSlider(Qt::Horizontal, widget);
axisMaxSliderY->setMinimum(1);
axisMaxSliderY->setTickInterval(1);
axisMaxSliderY->setEnabled(true);








QComboBox *themeList = new QComboBox(widget);
themeList->addItem(QStringLiteral("Qt"));
themeList->addItem(QStringLiteral("Primary Colors"));
themeList->addItem(QStringLiteral("Digia"));
themeList->addItem(QStringLiteral("Stone Moss"));
themeList->addItem(QStringLiteral("Army Blue"));
themeList->addItem(QStringLiteral("Retro"));
themeList->addItem(QStringLiteral("Ebony"));
themeList->addItem(QStringLiteral("Isabelle"));




    QGroupBox *Sensitivity = new QGroupBox(QStringLiteral("Sensitivity"));




QGroupBox *com = new QGroupBox(QStringLiteral("Port"));

QComboBox *box = new QComboBox;
   Q_FOREACH(QSerialPortInfo port, QSerialPortInfo::availablePorts()) {
       box->addItem(port.portName());
   }
   //box->move(100 - box->width() / 2,100 - box->height() / 2);
   box->show();




   QPushButton *start = new QPushButton(widget);
  // start->setIcon(QIcon(pm));
   start->setText("Start");
//       Q_FOREACH(QSerialPortInfo port, QSerialPortInfo::availablePorts()) {
//           start->addItem(port.portName());
//       }

   start->setIconSize(QSize(24, 24));




   QPushButton *stop = new QPushButton(widget);
  // start->setIcon(QIcon(pm));
   stop->setText("Stop");


   stop->setIconSize(QSize(24, 24));


//standardOutput << box->currentText() << endl;



QGroupBox *colorGroupBox = new QGroupBox(QStringLiteral("Custom gradient"));

QLinearGradient grBtoY(0, 0, 1, 100);
grBtoY.setColorAt(1.0, Qt::black);
grBtoY.setColorAt(0.67, Qt::blue);
grBtoY.setColorAt(0.33, Qt::red);
grBtoY.setColorAt(0.0, Qt::yellow);
QPixmap pm(24, 100);
QPainter pmp(&pm);
pmp.setBrush(QBrush(grBtoY));
pmp.setPen(Qt::NoPen);
pmp.drawRect(0, 0, 24, 100);
QPushButton *gradientBtoYPB = new QPushButton(widget);
gradientBtoYPB->setIcon(QIcon(pm));
gradientBtoYPB->setIconSize(QSize(24, 100));

QLinearGradient grGtoR(0, 0, 1, 100);
grGtoR.setColorAt(1.0, Qt::darkGreen);
grGtoR.setColorAt(0.5, Qt::yellow);
grGtoR.setColorAt(0.2, Qt::red);
grGtoR.setColorAt(0.0, Qt::darkRed);
pmp.setBrush(QBrush(grGtoR));
pmp.drawRect(0, 0, 24, 100);
QPushButton *gradientGtoRPB = new QPushButton(widget);
gradientGtoRPB->setIcon(QIcon(pm));
gradientGtoRPB->setIconSize(QSize(24, 100));

QHBoxLayout *colorHBox = new QHBoxLayout;
colorHBox->addWidget(gradientBtoYPB);
colorHBox->addWidget(gradientGtoRPB);
colorGroupBox->setLayout(colorHBox);

vLayout->addWidget(modelGroupBox);
vLayout->addWidget(selectionGroupBox);
vLayout->addWidget(new QLabel(QStringLiteral("Column range")));
vLayout->addWidget(axisMinSliderX);
vLayout->addWidget(axisMaxSliderX);
vLayout->addWidget(new QLabel(QStringLiteral("Row range")));
vLayout->addWidget(axisMinSliderZ);
vLayout->addWidget(axisMaxSliderZ);
vLayout->addWidget(new QLabel(QStringLiteral("Theme")));
vLayout->addWidget(themeList);
vLayout->addWidget(colorGroupBox);
vLayout->addWidget(Sensitivity);
// vLayout->addWidget(SensitivitySlider);

vLayout->addWidget(axisMinSliderY);
vLayout->addWidget(axisMaxSliderY);

// vLayout->addWidget(onetimes);
//   vLayout->addWidget(tentimes);
//  vLayout->addWidget(less);
vLayout->addWidget(com);
vLayout->addWidget(box);
vLayout->addWidget(start);
vLayout->addWidget(stop);


widget->show();



SurfaceGraph *modifier = new SurfaceGraph(graph);

//SurfaceGraph *modifier2 = new SurfaceGraph(graph2);


// SurfaceGraph *modifier2 = new SurfaceGraph(graph2);

QObject::connect(heightMapModelRB, &QRadioButton::toggled,
                 modifier, &SurfaceGraph::enableHeightMapModel);
QObject::connect(sqrtSinModelRB, &QRadioButton::toggled,
                 modifier, &SurfaceGraph::enableSqrtSinModel);




QObject::connect(box, SIGNAL(currentTextChanged(QString)),
                 modifier, SLOT(test2(QString)));





QObject::connect(start, &QPushButton::pressed,                    //currentTextChanged(QString)),
                 modifier, &SurfaceGraph::begin);


QObject::connect(stop, &QPushButton::pressed,                    //currentTextChanged(QString)),
                 modifier, &SurfaceGraph::stop);




QObject::connect(modeNoneRB, &QRadioButton::toggled,
                 modifier, &SurfaceGraph::toggleModeNone);
QObject::connect(modeItemRB,  &QRadioButton::toggled,
                 modifier, &SurfaceGraph::toggleModeItem);
QObject::connect(modeSliceRowRB,  &QRadioButton::toggled,
                 modifier, &SurfaceGraph::toggleModeSliceRow);
QObject::connect(modeSliceColumnRB,  &QRadioButton::toggled,
                 modifier, &SurfaceGraph::toggleModeSliceColumn);
QObject::connect(axisMinSliderX, &QSlider::valueChanged,
                 modifier, &SurfaceGraph::adjustXMin);
QObject::connect(axisMaxSliderX, &QSlider::valueChanged,
                 modifier, &SurfaceGraph::adjustXMax);
QObject::connect(axisMinSliderZ, &QSlider::valueChanged,
                 modifier, &SurfaceGraph::adjustZMin);
QObject::connect(axisMaxSliderZ, &QSlider::valueChanged,
                 modifier, &SurfaceGraph::adjustZMax);


QObject::connect(axisMinSliderY, &QSlider::valueChanged,
                 modifier, &SurfaceGraph::adjustYMin);
QObject::connect(axisMaxSliderY, &QSlider::valueChanged,
                 modifier, &SurfaceGraph::adjustYMax);

QObject::connect(themeList, SIGNAL(currentIndexChanged(int)),
                 modifier, SLOT(changeTheme(int)));
QObject::connect(gradientBtoYPB, &QPushButton::pressed,
                 modifier, &SurfaceGraph::setBlackToYellowGradient);
QObject::connect(gradientGtoRPB, &QPushButton::pressed,
                 modifier, &SurfaceGraph::setGreenToRedGradient);



modifier->setAxisMinSliderY(axisMinSliderY);
modifier->setAxisMaxSliderY(axisMaxSliderY);

modifier->setAxisMinSliderX(axisMinSliderX);
modifier->setAxisMaxSliderX(axisMaxSliderX);
modifier->setAxisMinSliderZ(axisMinSliderZ);
modifier->setAxisMaxSliderZ(axisMaxSliderZ);


sqrtSinModelRB->setChecked(true);
modeItemRB->setChecked(true);
themeList->setCurrentIndex(2);








standardOutput << "loop 1" << endl;



//}///////////////////////////////
return app.exec();











}

