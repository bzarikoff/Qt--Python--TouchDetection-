/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Data Visualization module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:GPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 or (at your option) any later version
** approved by the KDE Free Qt Foundation. The licenses are as published by
** the Free Software Foundation and appearing in the file LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef SURFACEGRAPH_H
#define SURFACEGRAPH_H

#include <QtDataVisualization/Q3DSurface>
#include <QtDataVisualization/QSurfaceDataProxy>
#include <QtDataVisualization/QHeightMapSurfaceDataProxy>
#include <QtDataVisualization/QSurface3DSeries>
#include <QtWidgets/QSlider>
#include <QtSerialPort/QSerialPort>
#include <QtCharts/QChartView>

#include "chartview.h"




extern QSerialPort serial;
extern int integertest[24][16];

#define PORT "5555"//27015//5555
#define DEFAULT_BUFLEN 9192


extern int flag;


extern WSADATA wsa;
extern SOCKET s, new_socket;
extern struct sockaddr_in server, client;
extern int c;
extern char *message;
extern int opt; //= 1;
extern struct addrinfo*result, *ptr, hints;
extern int iResult;
extern char recvbuf[DEFAULT_BUFLEN];
//extern int recvbuflen ;//= DEFAULT_BUFLEN;
extern char recvbuf[DEFAULT_BUFLEN];
extern int integer_row[24];
extern int test;
extern int integertest[24][16];
extern ChartView *chartView;// = new ChartView();
//extern QWidget *container;

//extern SurfaceGraph *modifier = new SurfaceGraph(graph);

//extern SurfaceGraph *modifier2 = new SurfaceGraph(graph2);



using namespace QtDataVisualization;




class SurfaceGraph : public QObject
{
    Q_OBJECT
public:
    explicit SurfaceGraph(Q3DSurface *surface);//, Q3DSurface *surface2);
    ~SurfaceGraph();


    void enableHeightMapModel(bool enable);
    void enableSqrtSinModel(bool enable);
 //   void smaller(bool enable);
//    void same(bool enable);
  //  void bigger(bool enable);
    void testfunction();

    //! [0]
    void toggleModeNone() { m_graph->setSelectionMode(QAbstract3DGraph::SelectionNone); }
    void toggleModeItem() { m_graph->setSelectionMode(QAbstract3DGraph::SelectionItem); }
    void toggleModeSliceRow() { m_graph->setSelectionMode(QAbstract3DGraph::SelectionItemAndRow
                                                          | QAbstract3DGraph::SelectionSlice); }
    void toggleModeSliceColumn() { m_graph->setSelectionMode(QAbstract3DGraph::SelectionItemAndColumn
                                                             | QAbstract3DGraph::SelectionSlice); }
    //! [0]

    void setBlackToYellowGradient();
    void setGreenToRedGradient();

    void setAxisMinSliderX(QSlider *slider) { m_axisMinSliderX = slider; }
    void setAxisMaxSliderX(QSlider *slider) { m_axisMaxSliderX = slider; }
    void setAxisMinSliderZ(QSlider *slider) { m_axisMinSliderZ = slider; }
    void setAxisMaxSliderZ(QSlider *slider) { m_axisMaxSliderZ = slider; }


    void setAxisMinSliderY(QSlider *slider) { m_axisMinSliderY = slider; }
    void setAxisMaxSliderY(QSlider *slider) { m_axisMaxSliderY = slider; }

 //   void setSense(QSlider *slider) { m_sense = slider; }

    void adjustXMin(int min);
    void adjustXMax(int max);
    void adjustZMin(int min);
    void adjustZMax(int max);
    void fillSqrtSinProxy();
     void fillSqrtSinProxy2();
    void Timer();
//    void adjustSensitivity(int value);

    void adjustYMin(int min);
    void adjustYMax(int max);

private:
    int timerId;


protected:
    void timerEvent(QTimerEvent *event);


public Q_SLOTS:
    void changeTheme(int theme);
      void test2(QString box);
    //  void begin(QString box);
       void begin();
        void stop();

private:
    Q3DSurface *m_graph;
    Q3DSurface *m_graph2;
    QHeightMapSurfaceDataProxy *m_heightMapProxy;
    QSurfaceDataProxy *m_sqrtSinProxy;
    QSurfaceDataProxy *m_sqrtSinProxy2;
    QSurface3DSeries *m_heightMapSeries;
    QSurface3DSeries *m_sqrtSinSeries;
    QSurface3DSeries *m_sqrtSinSeries2;

    QSlider *m_axisMinSliderX;
    QSlider *m_axisMaxSliderX;
    QSlider *m_axisMinSliderZ;
    QSlider *m_axisMaxSliderZ;
    QSlider *m_axisMinSliderY;
    QSlider *m_axisMaxSliderY;

   // QSlider *m_sense;


    float m_rangeMinY;
    float m_stepY;

    float m_rangeMinX;
    float m_rangeMinZ;
    float m_stepX;
    float m_stepZ;
    int m_heightMapWidth;
    int m_heightMapHeight;

    void setAxisXRange(float min, float max);
    void setAxisZRange(float min, float max);
    void setAxisYRange(float min, float max);
  //  void fillSqrtSinProxy();
};



#endif // SURFACEGRAPH_H





