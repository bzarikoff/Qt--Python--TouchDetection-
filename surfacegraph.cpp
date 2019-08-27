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

#include "surfacegraph.h"
#include "chartview.h"


#include <QtDataVisualization/QValue3DAxis>
#include <QtDataVisualization/Q3DTheme>
#include <QtGui/QImage>
#include <QtCore/qmath.h>
#include <QtSerialPort/QSerialPort>
#include <QTimer>
#include <QtWidgets/QApplication>
#include <stdlib.h>
#include <sstream>


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
#include <QSerialPortInfo>


#include <QtCharts/QScatterSeries>
#include <QtCharts/QLegendMarker>
#include <QtGui/QImage>
#include <QtGui/QPainter>
#include <QtCore/QtMath>

#define PORT "5555"//27015//5555
#define DEFAULT_BUFLEN 9192


int integertest[24][16];//16,24
QSerialPort serial;


WSADATA wsa;
SOCKET s, new_socket;
struct sockaddr_in server, client;
int c;
char *message;
int opt = 1;
struct addrinfo*result, *ptr, hints;
int iResult;
int recvbuflen = DEFAULT_BUFLEN;
//char recvbuf[DEFAULT_BUFLEN];
int integer_row[24];
int test;

char recvbuf[DEFAULT_BUFLEN];

int touch[20][3];
int force;

int flag;

//ChartView chartupdate;




const int sampleCountX = 24;//50;
const int sampleCountZ = 16;//50;
const int sampleCountY = 1000;
const int heightMapGridStepX = 1;
const int heightMapGridStepZ = 1;
const int heightMapGridStepY = 1;
const float sampleMin = 0.0f;//-24.0f;//-8.0f;
const float sampleMax = 24.0f;//8.0f;

float sensitivity = 1;
int on = 0;


//run initially to instantiate - also starts timer
SurfaceGraph::SurfaceGraph(Q3DSurface *surface)//, Q3DSurface *surface2)
    : m_graph(surface)//, m_graph2(surface2)
{
    m_graph->setAxisX(new QValue3DAxis);
    m_graph->setAxisY(new QValue3DAxis);
    m_graph->setAxisZ(new QValue3DAxis);



//    m_graph2->setAxisX(new QValue3DAxis);
//    m_graph2->setAxisY(new QValue3DAxis);
//    m_graph2->setAxisZ(new QValue3DAxis);



    //! [0]
    m_sqrtSinProxy = new QSurfaceDataProxy();
    m_sqrtSinSeries = new QSurface3DSeries(m_sqrtSinProxy);
//    m_sqrtSinProxy2 = new QSurfaceDataProxy();
//    m_sqrtSinSeries2 = new QSurface3DSeries(m_sqrtSinProxy2);
    //! [0]

//    QScatterSeries *series0 = new QScatterSeries();
//    series0->setMarkerSize(40.0);


//    series0->append(0, 6);
//    series0->append(2, 4);
//    series0->append(3, 8);
//    series0->append(7, 4);
//    series0->append(23, 15);

//    setRenderHint(QPainter::Antialiasing);
   // chart()->addSeries(series0);

   // chart()->createDefaultAxes();

//            QTimer*timer = new QTimer(this);
//            QObject::connect(timer, SIGNAL(timeout()), this, SLOT(fillSqrtSinProxy()));
//            timer->start(100);
    flag = 0;
    //fillSqrtSinProxy();
    timerId = startTimer(100);
   // setGreenToRedGradient();

    //! [2]
    QImage heightMapImage(":/maps/mountain");
    m_heightMapProxy = new QHeightMapSurfaceDataProxy(heightMapImage);
    m_heightMapSeries = new QSurface3DSeries(m_heightMapProxy);
    m_heightMapSeries->setItemLabelFormat(QStringLiteral("(@xLabel, @zLabel): @yLabel"));
    m_heightMapProxy->setValueRanges(34.0f, 40.0f, 18.0f, 24.0f);
    //! [2]
    m_heightMapWidth = heightMapImage.width();
    m_heightMapHeight = heightMapImage.height();

//    QTimer*timer = new QTimer(this);
//    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(fillSqrtSinProxy()));
//    timer->start(100);

    static int preset = Q3DCamera::CameraPresetDirectlyAbove;
         m_graph->scene()->activeCamera()->setCameraPreset((Q3DCamera::CameraPreset)preset);
          //set camera to be directly above


}

SurfaceGraph::~SurfaceGraph()
{
    delete m_graph;
  //  delete m_graph2;
}


//call functions to update each graph at each timer interval
void SurfaceGraph::timerEvent(QTimerEvent *event)
{
    //qDebug() << "Update  1";
  // if(container){
//       fillSqrtSinProxy2();
     QTextStream standardOutput(stdout);

     standardOutput << "before" << endl;

       fillSqrtSinProxy();

       standardOutput << "middle" << endl;

//ChartView chartupdate;
      chartView->UpdateChart();


      standardOutput << "after" << endl;


}

//begin button - not used in python version
void SurfaceGraph::begin()
{
    QTextStream standardOutput(stdout);
    standardOutput << "test" << endl;

    QString portname;
    QString port1;
    int count = 0;



  //  QSerialPortInfo objectconst;

    //portname = objectconst.portName();
if(on == 0){
    Q_FOREACH(QSerialPortInfo objectconst, QSerialPortInfo::availablePorts()) {

        if(count == 0){
       port1 = objectconst.portName();
       standardOutput << portname << endl;
       count = 1;
        }
        else{
            standardOutput << "no" << endl;
             standardOutput << portname << endl;
        }


}

//    Q_FOREACH(QSerialPortInfo port, QSerialPortInfo::availablePorts()) {
//        box->addItem(port.portName());
//    }



//    Q_FOREACH(QSerialPortInfo port, QSerialPortInfo::availablePorts()) {
//        box->addItem(port.portName());
//    }

    test2(port1);
}
on = 1;
}

//stop button - not used in python version
void SurfaceGraph::stop()
{
    QTextStream standardOutput(stdout);
    standardOutput << "test" << endl;

    on = 0;
    killTimer(timerId);
           // startTimer(100);
    //    timerId = startTimer(100);



}

// not used
void SurfaceGraph::test2(QString box)
{

       QTextStream standardOutput(stdout);
       standardOutput << box << endl;

       int flag;
       int enable;






     //  QTextStream standardOutput(stdout);
       QByteArray data, data2;


       serial.setPortName(box);//COM4
       serial.setBaudRate(QSerialPort::Baud9600); /*, QSerialPort::Output*/
       serial.setDataBits(QSerialPort::Data8);
       serial.setParity(QSerialPort::NoParity);
       serial.setStopBits(QSerialPort::TwoStop);
       serial.setFlowControl(QSerialPort::NoFlowControl);
       serial.open(QIODevice::ReadWrite);




       if(!serial.isOpen()){
           standardOutput << "this port is not currently open\r\n" << endl;
           flag = 0;
           enable = 0;

       }
       if(serial.isOpen()){
           standardOutput << "this port is now opennnnnnnnnnnnnnnnnn\r\n" << endl;
           flag = 1;
           enable = 1;
       }

        if(enable == 1){


       //Setup Command
//       serial.write("!sm\r\n");
//       standardOutput << "!SM\r\n" << endl;
//       serial.waitForReadyRead();


//   data = serial.readLine();
//while(data.isNull() == TRUE){
//   data = serial.readLine();
//}
//standardOutput << data << endl;


       //Set Columns Number
       serial.write("!nc24\r\n");
       standardOutput << "!NC24\r\n" << endl;
       serial.waitForReadyRead();
//        data = serial.readLine();
//        if(data != "\n")
//            standardOutput << data << endl;
//        serial.waitForReadyRead();

//        while(data != "Number of col 24"){
//        data = serial.readLine();
//        }
//         standardOutput << data <<


         //   data = serial.readLine();
            data = serial.readLine();

        while(data[0] != 'N'){
          // while(data.isNull() == TRUE ){ // || data[0] == '\n'){
            serial.waitForReadyRead();
            data = serial.readLine();
            // standardOutput << "check" << endl;
        }
         standardOutput << data << endl;
         standardOutput << "above" << endl;



     //Set Rows Number
        serial.write("!nr16\r\n");
        standardOutput << "!NR24\r\n" << endl;
        serial.waitForReadyRead();
//         data = serial.readLine();
//         standardOutput << data << endl;
//         serial.waitForReadyRead();

//         while(data != "Number of row 16"){
//         data = serial.readLine();
//         }
//           standardOutput << data << endl;
            data = serial.readLine();
             while(data[0] != 'N'){
          //while(data.isNull() == TRUE){
                 serial.waitForReadyRead();
              data = serial.readLine();
          }
           standardOutput << data << endl;


         //Set Delay
         serial.write("!sd10\r\n");
         standardOutput << "!SD10\r\n" << endl;
         serial.waitForReadyRead();
//          data = serial.readLine();
//          serial.waitForReadyRead();

//          while(data != "Sampling Delay 10"){
//              data = serial.readLine();
//          }
//          standardOutput << data << endl;
            data = serial.readLine();
            while(data[0] != 'S'){
            serial.waitForReadyRead();
       //  while(data.isNull() == TRUE){
             data = serial.readLine();
         }
          standardOutput << data << endl;




          //Start Sampling
       serial.write("!ss\r\n");
       standardOutput << "!ss\r\n" << endl;
       serial.waitForReadyRead();
//        data = serial.readLine();
//        serial.waitForReadyRead();

//        while(data != "Sampling Matrix"){
//            data = serial.readLine();
//        }
//        standardOutput << data << endl;
       data = serial.readLine();
         while(data[0] != 'S'){
   //    while(data.isNull() == TRUE){
             serial.waitForReadyRead();
           data = serial.readLine();
       }
        standardOutput << data << endl;


        if(flag == 1){
            timerId = startTimer(100);




        }

}

}

/*//void SurfaceGraph::Timer()
{
        QTimer*timer = new QTimer(this);
        QObject::connect(timer, SIGNAL(timeout()), this, SLOT(fillSqrtSinProxy()));
        timer->start(100);
}  */    //added this to header and main to attempt to call fillsqrt every 100 ms
//not used
void SurfaceGraph::fillSqrtSinProxy2()
{


    float stepX = (sampleMax - sampleMin) / float(sampleCountX - 1);
    float stepZ = (sampleMax - sampleMin) / float(sampleCountZ - 1);
    QSurfaceDataArray *dataArray2 = new QSurfaceDataArray;
    dataArray2->reserve(sampleCountZ);

    int j = 0;
    int i = 0;
    int k = 0;
    int p = 0;




    QTextStream standardOutput(stdout);
    QByteArray data;
    const char * point;
   // char recvbuf[DEFAULT_BUFLEN];


    //  while(1){//iResult = recv(new_socket, recvbuf, recvbuflen, 0)>0){
          iResult = recv(new_socket, recvbuf, recvbuflen, 0);
  //    if(iResult>0){
          printf("Bytes received: %d\n", iResult);



     // std::cout << "here" << std::endl;
      std::cout << "second" << std::endl;
      std::cout << recvbuf << std::endl;
      //std::cout << "here" << std::endl;

      int row[100];
   //   int k = 0;
      int d = 0;








            int index = 0;

            while(recvbuf[index] != '[' ){
            index++;
            }


                     while(recvbuf[index]){

                     if(recvbuf[index]=='['){
                     index++;
                     k = 0;
//                     if(recvbuf[index]=='[' && recvbuf[index-1]!='[' && recvbuf[index+1]!='[' ){
//                         d++;
//                        std::cout << "new row" << std::endl;
//                     }
      }
                     else if(recvbuf[index]=='.'){
                     index=index+2;
      }
                     else if(recvbuf[index]==','){
                     index++;
      }
                     else if(recvbuf[index]=='k'){
                         index = index + 10000;
                     }
                     else if(recvbuf[index]==']'){
                   //  index++;
                       //  k=0;
                         if(recvbuf[index+1]==']'){
                             //break;
                             index = index+10000;

                         }
                       index++;

                         if(d<15){
                           // d++;
                        //    std::cout << "rowwwwwwwwwwwwwwwwwwww" << std::endl;
                         }
                    //     else std::cout << "lasttttttttttttttttttt" << std::endl;

      }
                     else if(recvbuf[index]==' '){
                     index++;
      } //three digits
                     else if((recvbuf[index]!=' ' && recvbuf[index] != ',' && recvbuf[index] != '[' && recvbuf[index] != ']' && recvbuf[index] != '.')
                                && (recvbuf[index+1]!=' ' && recvbuf[index+1] != '.' && recvbuf[index+1] != '[' && recvbuf[index+1] != ']' && recvbuf[index+1] != ',')
                             &&(recvbuf[index+2]!=' ' && recvbuf[index+2] != '.' && recvbuf[index+2] != '[' && recvbuf[index+2] != ']' && recvbuf[index+2] != ',')){


                       //  std::cout << recvbuf[index] << std::endl;
                         int digit;
                         std::stringstream strValue;
                         std::stringstream strValue3;
                         strValue << recvbuf[index];
                         strValue >> row[k];
                         std::stringstream strValue2;
                         strValue2 << recvbuf[index+1];
                         strValue2 >> test;
                         strValue3 << recvbuf[index+2];
                         strValue3 >> digit;
                         row[k] = row[k]*100 + test*10 + digit;// + (row[k+1] - '0');
                       //  std::cout << row[k] << std::endl;
                         touch[d][k] = row[k];
                       //  std::cout << touch[d][k] << std::endl;
                        // std::cout << test << std::endl;
                         index = index + 3;
                         k++;
                         if(k==3){
                             k = 0;
                             d++;
                         }
      }
                     else if((recvbuf[index]!=' ' && recvbuf[index] != ',' && recvbuf[index] != '[' && recvbuf[index] != ']' && recvbuf[index] != '.')
                                && (recvbuf[index+1]!=' ' && recvbuf[index+1] != '.' && recvbuf[index+1] != '[' && recvbuf[index+1] != ']' && recvbuf[index+1] != ',')){

                          //std::cout << recvbuf[index] << std::endl;
                     std::stringstream strValue;
                     strValue << recvbuf[index];
                     strValue >> row[k];
                     std::stringstream strValue2;
                     strValue2 << recvbuf[index+1];
                     strValue2 >> test;
                     row[k] = row[k]*10 + test;// + (row[k+1] - '0');
                   //  std::cout << row[k] << std::endl;
                     touch[d][k] = row[k];
                   //  std::cout << touch[d][k] << std::endl;
                    // std::cout << test << std::endl;
                     index = index + 2;
                     k++;
                     if(k==4){
                         k = 0;
                         d++;
                     }
      }
                     else{

 //std::cout << recvbuf[index] << std::endl;
                     std::stringstream strValue;
                     strValue << recvbuf[index];
                     strValue >> row[k];
                  //   std::cout << row[k] << std::endl;
                     touch[d][k] = row[k];
                   //  std::cout << integertest[d][k] << std::endl;
                     index++;
                     k++;
                     if(k==4){
                         k = 0;
                         d++;
                     }

      }


      }




  //std::cout << k << std::endl;

  std::cout << "start" << std::endl;
  std::cout << touch[0][0] << std::endl;
  std::cout << touch[0][1] << std::endl;
  std::cout << touch[0][2] << std::endl;
  std::cout << touch[1][0] << std::endl;
  std::cout << touch[1][1] << std::endl;
  std::cout << touch[1][2] << std::endl;
  std::cout << touch[2][0] << std::endl;
  std::cout << touch[2][1] << std::endl;
  std::cout << touch[2][2] << std::endl;
  std::cout << "end" << std::endl;


 // }





      //Reply to client
      message = "Hello Client , I have received your connection. But I have to go now, bye\n";
      send(new_socket , message , strlen(message) , 0);

     // getchar();

    //  closesocket(s);
     // WSACleanup();





//int t = 0;
//int q = 20;
//for(t = 0; t < 20; t++){
//    if(touch[t][0]==0 && touch[t][1]==0 && touch[t][2]==0){
//        q = t;
//        break;
//    }
//}







//for(int l = 0; l < q; l++){

//    for (int i = 0 ; i < 4 ; i++) {
//        QSurfaceDataRow *newRow = new QSurfaceDataRow(sampleCountX);
//        // Keep values within range bounds, since just adding step can cause minor drift due
//        // to the rounding errors.
//        float z = 4+i;//touch[l][0] - 2 + i;//i;//qMin(sampleMax, (i * stepZ + sampleMin));
//        int index = 0;
//        for (int j = 0; j < 5; j++) {//j<24
//            float x = 4+j;          // touch[l][1] - 2 + j;//j;//qMin(sampleMax, (j * stepX + sampleMin));
//            float y = 2;
////            if(touch[l][2] > 10){
////            y =  4;
////            }
////            else if(touch[l][2] > 50){
////             y = 8;
////            }
////            else if(touch[l][2] > 75){
////              y = 16;
////            }
////            else if(touch[l][2] > 100){
////             y = 32;
////            }
//            (*newRow)[index++].setPosition(QVector3D(x, y, z));
//        }
//        *dataArray2 << newRow;
//    }

//}


//    m_sqrtSinProxy2->resetArray(dataArray2);




}

//updates raw data graph with socket data
void SurfaceGraph::fillSqrtSinProxy()
{


    float stepX = (sampleMax - sampleMin) / float(sampleCountX - 1);
    float stepZ = (sampleMax - sampleMin) / float(sampleCountZ - 1);
    QSurfaceDataArray *dataArray = new QSurfaceDataArray;
    dataArray->reserve(sampleCountZ);

    int j = 0;
    int i = 0;
    int k = 0;
    int p = 0;


//stores raw data in integer_test array
//ignores the first part of socket data up to the k ( which separates the touch and the raw data)

    QTextStream standardOutput(stdout);
    QByteArray data;
    const char * point;
  //  char recvbuf[DEFAULT_BUFLEN];


    //  while(1){//iResult = recv(new_socket, recvbuf, recvbuflen, 0)>0){
          iResult = recv(new_socket, recvbuf, recvbuflen, 0);
    //  if(iResult>0){
    //      printf("Bytes received: %d\n", iResult);



     // std::cout << "here" << std::endl;
      std::cout << "first" << std::endl;
      std::cout << recvbuf << std::endl;
      std::cout << "here" << std::endl;

      int row[150];
     // int k = 0;
      int d = 0;
      int flag = 0;








            int index = 0;

            while(recvbuf[index] != '['){
            index++;
            }


                     while(recvbuf[index]){

                         if(flag==0){
                             if(recvbuf[index]!='k'){
                               //   std::cout << recvbuf[index] << std::endl;
                                 index++;

                             }
                             else {flag = 1;
                                   index = index+3;
                                //   std::cout << "end of touch" << std::endl;
                             }
                         }
                         else{

                     if(recvbuf[index]=='['){
                     index++;

      }
                     else if(recvbuf[index]=='.'){
                     index=index+2;
      }
                     else if(recvbuf[index]==','){
                     index++;
      }
                     else if(recvbuf[index]==']'){
                   //  index++;
                         k=0;
                         if(recvbuf[index+1]==']'){
                             //break;
                             index = index+100;

                         }
                       index++;

                         if(d<23){//15
                            d++;
                         //   std::cout << d << std::endl;
                        //    std::cout << "rowwwwwwwwwwwwwwwwwwww" << std::endl;
                         }
                    //     else std::cout << "lasttttttttttttttttttt" << std::endl;

      }
                     else if(recvbuf[index]==' '){
                     index++;

      }              //four digits
                     else if((recvbuf[index]!=' ' && recvbuf[index] != ',' && recvbuf[index] != '[' && recvbuf[index] != ']' && recvbuf[index] != '.')
                              && (recvbuf[index+1]!=' ' && recvbuf[index+1] != '.' && recvbuf[index+1] != '[' && recvbuf[index+1] != ']' && recvbuf[index+1] != ',')
                           &&(recvbuf[index+2]!=' ' && recvbuf[index+2] != '.' && recvbuf[index+2] != '[' && recvbuf[index+2] != ']' && recvbuf[index+2] != ',')
                           && (recvbuf[index+3]!=' ' && recvbuf[index+3] != '.' && recvbuf[index+3] != '[' && recvbuf[index+3] != ']' && recvbuf[index+3] != ',')){

                   int test2;
                   int test3;
                   std::stringstream strValue;
                   std::stringstream strValue4;
                   strValue << recvbuf[index];
                   strValue >> row[k];
                   std::stringstream strValue2;
                   std::stringstream strValue3;
                   strValue2 << recvbuf[index+1];
                   strValue2 >> test;
                   strValue3 << recvbuf[index+2];
                   strValue3 >> test2;
                   strValue3 << recvbuf[index+3];
                   strValue3 >> test3;
                   row[k] = row[k]*1000 + test*100+ test2*10 + test3;// + (row[k+1] - '0');
                 //  std::cout << row[k] << std::endl;
                   integertest[23-d][k] = row[k];
                //   std::cout << integer_test[d][k] << std::endl;
                  // std::cout << test << std::endl;
                   index = index + 4;
                //   std::cout << k << std::endl;
                //   std::cout <<  integertest[d][k] << std::endl;
                   k++;
    }
                     //three digits
                     else if((recvbuf[index]!=' ' && recvbuf[index] != ',' && recvbuf[index] != '[' && recvbuf[index] != ']' && recvbuf[index] != '.')
                                && (recvbuf[index+1]!=' ' && recvbuf[index+1] != '.' && recvbuf[index+1] != '[' && recvbuf[index+1] != ']' && recvbuf[index+1] != ',')
                             &&(recvbuf[index+2]!=' ' && recvbuf[index+2] != '.' && recvbuf[index+2] != '[' && recvbuf[index+2] != ']' && recvbuf[index+2] != ',')){

                     int test2;
                     std::stringstream strValue;
                     strValue << recvbuf[index];
                     strValue >> row[k];
                     std::stringstream strValue2;
                     std::stringstream strValue3;
                     strValue2 << recvbuf[index+1];
                     strValue2 >> test;
                     strValue3 << recvbuf[index+2];
                     strValue3 >> test2;
                     row[k] = row[k]*100 + test*10+ test2;// + (row[k+1] - '0');
                   //  std::cout << row[k] << std::endl;
                     integertest[23-d][k] = row[k];
                  //   std::cout << integer_test[d][k] << std::endl;
                    // std::cout << test << std::endl;
                     index = index + 3;
                  //   std::cout << k << std::endl;
                  //   std::cout <<  integertest[d][k] << std::endl;
                     k++;
      }                  //two digits
                     else if((recvbuf[index]!=' ' && recvbuf[index] != ',' && recvbuf[index] != '[' && recvbuf[index] != ']' && recvbuf[index] != '.')
                                && (recvbuf[index+1]!=' ' && recvbuf[index+1] != '.' && recvbuf[index+1] != '[' && recvbuf[index+1] != ']' && recvbuf[index+1] != ',')){

                     std::stringstream strValue;
                     strValue << recvbuf[index];
                     strValue >> row[k];
                     std::stringstream strValue2;
                     strValue2 << recvbuf[index+1];
                     strValue2 >> test;
                     row[k] = row[k]*10 + test;// + (row[k+1] - '0');
                   //  std::cout << row[k] << std::endl;
                     integertest[23-d][k] = row[k];
                  //   std::cout << integer_test[d][k] << std::endl;
                    // std::cout << test << std::endl;
                     index = index + 2;
              //       std::cout << k << std::endl;
              //    std::cout <<  integertest[d][k] << std::endl;
                     k++;
      }             //one digit
                     else{


                     std::stringstream strValue;
                     strValue << recvbuf[index];
                     strValue >> row[k];
                  //   std::cout << row[k] << std::endl;
                     integertest[23-d][k] = row[k];
                   //  std::cout << integertest[d][k] << std::endl;
                     index++;
                //    std::cout << k << std::endl;
                //    std::cout <<  integertest[d][k] << std::endl;
                     k++;

      }

}//else flag
      }




  //std::cout << k << std::endl;




  //}





      //Reply to client
      message = "Hello Client , I have received your connection. But I have to go now, bye\n";
      send(new_socket , message , strlen(message) , 0);

     // getchar();

    //  closesocket(s);
     // WSACleanup();













//int integertest[24][16];//16,24


  //  QSurfaceDataArray *dataArray = new QSurfaceDataArray;
  //  dataArray->reserve(sampleCountZ);
    for (int i = 0 ; i < 16/*sampleCountZ*/ ; i++) {//16
        QSurfaceDataRow *newRow = new QSurfaceDataRow(sampleCountX);
        // Keep values within range bounds, since just adding step can cause minor drift due
        // to the rounding errors.
        float x = i;//qMin(sampleMax, (i * stepZ + sampleMin));//z
        int index = 0;
        for (int j = 0; j < 24/*sampleCountX*/; j++) {//24
            float z = j;//qMin(sampleMax, (j * stepX + sampleMin));//x
         //   float R = qSqrt(z * z + x * x) + 0.01f;
            float y =  integertest[(int)z][(int)x];// (qSin(R) / R + 0.24f) * 1.61f;//integertest[(int)z][(int)x];  put matrix data
            (*newRow)[index++].setPosition(QVector3D(z, y, x));//x y z
        }
        *dataArray << newRow;
    }
//  standardOutput << "graph" << endl;
    m_sqrtSinProxy->resetArray(dataArray);
   // m_sqrtSinProxy2->resetArray(dataArray);




}
//! [1]




//keep this selected for socket mode
void SurfaceGraph::enableSqrtSinModel(bool enable)
{
    if (enable) {
        //! [3]
        m_sqrtSinSeries->setDrawMode(QSurface3DSeries::DrawSurfaceAndWireframe);
        m_sqrtSinSeries->setFlatShadingEnabled(false);


//        m_sqrtSinSeries2->setDrawMode(QSurface3DSeries::DrawSurfaceAndWireframe);
//        m_sqrtSinSeries2->setFlatShadingEnabled(true);

        m_graph->axisX()->setLabelFormat("%.2f");
        m_graph->axisZ()->setLabelFormat("%.2f");
        m_graph->axisX()->setRange(sampleMin, sampleMax);
        m_graph->axisY()->setRange(0.0f, 500.0f);//2.0f//50
        m_graph->axisZ()->setRange(sampleMin, sampleMax);
        m_graph->axisX()->setLabelAutoRotation(30);
        m_graph->axisY()->setLabelAutoRotation(90);
        m_graph->axisZ()->setLabelAutoRotation(30);

        m_graph->removeSeries(m_heightMapSeries);
        m_graph->addSeries(m_sqrtSinSeries);


//        m_graph2->axisX()->setLabelFormat("%.2f");
//        m_graph2->axisZ()->setLabelFormat("%.2f");
//        m_graph2->axisX()->setRange(sampleMin, sampleMax);
//        m_graph2->axisY()->setRange(0.0f, 500.0f);//2.0f//50
//        m_graph2->axisZ()->setRange(sampleMin, sampleMax);
//        m_graph2->axisX()->setLabelAutoRotation(30);
//        m_graph2->axisY()->setLabelAutoRotation(90);
//        m_graph2->axisZ()->setLabelAutoRotation(30);

//        m_graph2->removeSeries(m_heightMapSeries);
//        m_graph2->addSeries(m_sqrtSinSeries2);
        //! [3]

        //! [8]
        // Reset range sliders for Sqrt&Sin
        m_rangeMinX = sampleMin;
        m_rangeMinZ = sampleMin;
        m_stepX = (23.0f) / float(sampleCountX - 1);
        m_stepZ = (15.0f) / float(sampleCountZ - 1); //sampleMax - sampleMin
        m_axisMinSliderX->setMaximum(sampleCountX - 2);
        m_axisMinSliderX->setValue(0);
        m_axisMaxSliderX->setMaximum(sampleCountX - 1);
        m_axisMaxSliderX->setValue(sampleCountX - 1);
        m_axisMinSliderZ->setMaximum(sampleCountZ - 2);
        m_axisMinSliderZ->setValue(0);
        m_axisMaxSliderZ->setMaximum(sampleCountZ - 1);
        m_axisMaxSliderZ->setValue(sampleCountZ - 1);






        m_rangeMinY = 0.0f;
        m_stepY = (1000.0f) / float(sampleCountY - 1);
        m_axisMinSliderY->setMaximum(sampleCountY - 2);
        m_axisMinSliderY->setValue(0);
        m_axisMaxSliderY->setMaximum(sampleCountY - 1);
        m_axisMaxSliderY->setValue(sampleCountY - 1);

//        m_stepY = (25.0f);
//        m_axisMinSliderY->setMaximum(22);
//        m_axisMinSliderY->setValue(0);
//       m_axisMaxSliderY->setMaximum(23);
//       m_axisMaxSliderY->setValue(23);




//        m_sense->setMaximum(10);
//        m_sense->setMinimum(0);
//        m_sense->setValue(5);
        //! [8]

//        QTimer*timer = new QTimer(this);
//        QObject::connect(timer, SIGNAL(timeout()), this, SLOT(fillSqrtSinProxy()));
//        timer->start(100);



        fillSqrtSinProxy();


    }
}

void SurfaceGraph::enableHeightMapModel(bool enable)
{
    if (enable) {



        m_sqrtSinSeries->setDrawMode(QSurface3DSeries::DrawSurfaceAndWireframe);
        m_sqrtSinSeries->setFlatShadingEnabled(true);

        m_graph->axisX()->setLabelFormat("%.2f");
        m_graph->axisZ()->setLabelFormat("%.2f");
        m_graph->axisX()->setRange(sampleMin, sampleMax);
        m_graph->axisY()->setRange(0.0f, 500.0f);//2.0f//50
        m_graph->axisZ()->setRange(sampleMin, sampleMax);
        m_graph->axisX()->setLabelAutoRotation(30);
        m_graph->axisY()->setLabelAutoRotation(90);
        m_graph->axisZ()->setLabelAutoRotation(30);

        m_graph->removeSeries(m_sqrtSinSeries);
        m_graph->addSeries(m_sqrtSinSeries);
        //! [3]

        //! [8]
        // Reset range sliders for Sqrt&Sin
        m_rangeMinX = sampleMin;
        m_rangeMinZ = sampleMin;
        m_stepX = (23.0f) / float(sampleCountX - 1);
        m_stepZ = (15.0f) / float(sampleCountZ - 1); //sampleMax - sampleMin
        m_axisMinSliderX->setMaximum(sampleCountX - 2);
        m_axisMinSliderX->setValue(0);
        m_axisMaxSliderX->setMaximum(sampleCountX - 1);
        m_axisMaxSliderX->setValue(sampleCountX - 1);
        m_axisMinSliderZ->setMaximum(sampleCountZ - 2);
        m_axisMinSliderZ->setValue(0);
        m_axisMaxSliderZ->setMaximum(sampleCountZ - 1);
        m_axisMaxSliderZ->setValue(sampleCountZ - 1);






        m_rangeMinY = 0.0f;
        m_stepY = (1000.0f) / float(sampleCountY - 1);
        m_axisMinSliderY->setMaximum(sampleCountY - 2);
        m_axisMinSliderY->setValue(0);
        m_axisMaxSliderY->setMaximum(sampleCountY - 1);
        m_axisMaxSliderY->setValue(sampleCountY - 1);






//        //! [4]
//        m_heightMapSeries->setDrawMode(QSurface3DSeries::DrawSurface);
//        m_heightMapSeries->setFlatShadingEnabled(false);

//        m_graph->axisX()->setLabelFormat("%.1f N");
//        m_graph->axisZ()->setLabelFormat("%.1f E");
//        m_graph->axisX()->setRange(34.0f, 40.0f);
//        m_graph->axisY()->setAutoAdjustRange(true);
//        m_graph->axisZ()->setRange(18.0f, 24.0f);

//        m_graph->axisX()->setTitle(QStringLiteral("Latitude"));
//        m_graph->axisY()->setTitle(QStringLiteral("Height"));
//        m_graph->axisZ()->setTitle(QStringLiteral("Longitude"));

//        m_graph->removeSeries(m_sqrtSinSeries);
//        m_graph->addSeries(m_heightMapSeries);
//        //! [4]

//        // Reset range sliders for height map
//        int mapGridCountX = m_heightMapWidth / heightMapGridStepX;
//        int mapGridCountZ = m_heightMapHeight / heightMapGridStepZ;
//        m_rangeMinX = 34.0f;
//        m_rangeMinZ = 18.0f;
//        m_stepX = 6.0f / float(mapGridCountX - 1);
//        m_stepZ = 6.0f / float(mapGridCountZ - 1);
//        m_axisMinSliderX->setMaximum(mapGridCountX - 2);
//        m_axisMinSliderX->setValue(0);
//        m_axisMaxSliderX->setMaximum(mapGridCountX - 1);
//        m_axisMaxSliderX->setValue(mapGridCountX - 1);
//        m_axisMinSliderZ->setMaximum(mapGridCountZ - 2);
//        m_axisMinSliderZ->setValue(0);
//        m_axisMaxSliderZ->setMaximum(mapGridCountZ - 1);
//        m_axisMaxSliderZ->setValue(mapGridCountZ - 1);
////        m_sense->setMaximum(10);
////        m_sense->setMinimum(0);
////        m_sense->setValue(5);



//        m_rangeMinY = 0.0f;
//        m_stepY = (1000.0f) / float(sampleCountY - 1);
//        m_axisMinSliderY->setMaximum(sampleCountY - 2);
//        m_axisMinSliderY->setValue(0);
//        m_axisMaxSliderY->setMaximum(sampleCountY - 1);
//        m_axisMaxSliderY->setValue(sampleCountY - 1);


    }
}

void SurfaceGraph::adjustXMin(int min)
{
    float minX = m_stepX * float(min) + m_rangeMinX;

    int max = m_axisMaxSliderX->value();
    if (min >= max) {
        max = min + 1;
        m_axisMaxSliderX->setValue(max);
    }
    float maxX = m_stepX * max + m_rangeMinX;

    setAxisXRange(minX, maxX);
}

void SurfaceGraph::adjustXMax(int max)
{
    float maxX = m_stepX * float(max) + m_rangeMinX;

    int min = m_axisMinSliderX->value();
    if (max <= min) {
        min = max - 1;
        m_axisMinSliderX->setValue(min);
    }
    float minX = m_stepX * min + m_rangeMinX;

    setAxisXRange(minX, maxX);
}

void SurfaceGraph::adjustZMin(int min)
{
    float minZ = m_stepZ * float(min) + m_rangeMinZ;

    int max = m_axisMaxSliderZ->value();
    if (min >= max) {
        max = min + 1;
        m_axisMaxSliderZ->setValue(max);
    }
    float maxZ = m_stepZ * max + m_rangeMinZ;

    setAxisZRange(minZ, maxZ);
}

void SurfaceGraph::adjustZMax(int max)
{
    float maxX = m_stepZ * float(max) + m_rangeMinZ;

    int min = m_axisMinSliderZ->value();
    if (max <= min) {
        min = max - 1;
        m_axisMinSliderZ->setValue(min);
    }
    float minX = m_stepZ * min + m_rangeMinZ;

    setAxisZRange(minX, maxX);
}




void SurfaceGraph::adjustYMin(int min)
{
    float minY = m_stepY * float(min) + m_rangeMinY;

    int max = m_axisMaxSliderY->value();
    if (min >= max) {
        max = min + 1;
        m_axisMaxSliderY->setValue(max);
    }
    float maxY = m_stepY * max + m_rangeMinY;

    setAxisYRange(minY, maxY);
}

void SurfaceGraph::adjustYMax(int max)
{
    float maxY = m_stepY * float(max) + m_rangeMinY;

    int min = m_axisMinSliderY->value();
    if (max <= min) {
        min = max - 1;
        m_axisMinSliderY->setValue(min);
    }
    float minY = m_stepY * min + m_rangeMinY;

    setAxisYRange(minY, maxY);
}






//void SurfaceGraph::adjustSensitivity(int value)
//{


//    m_sense->setValue(value);
//    QTextStream standardOutput(stdout);
//    standardOutput << value << endl;


//    float test;
//    test = 0.09765625;//100/156=0.641;, 0.09765625 = 100/1024 for new hardware


//     test = test*value;



//     sensitivity = test;


//}

//! [5]
void SurfaceGraph::setAxisXRange(float min, float max)
{
    m_graph->axisX()->setRange(min, max);
}

void SurfaceGraph::setAxisZRange(float min, float max)
{
    m_graph->axisZ()->setRange(min, max);
}

void SurfaceGraph::setAxisYRange(float min, float max)
{
    m_graph->axisY()->setRange(min, max);
}
//! [5]

//! [6]
void SurfaceGraph::changeTheme(int theme)
{
    m_graph->activeTheme()->setType(Q3DTheme::Theme(theme));
}
//! [6]

void SurfaceGraph::setBlackToYellowGradient()
{
    //! [7]
    QLinearGradient gr;
    gr.setColorAt(0.0, Qt::black);
    gr.setColorAt(0.33, Qt::blue);
    gr.setColorAt(0.67, Qt::red);
    gr.setColorAt(1.0, Qt::yellow);

    m_graph->seriesList().at(0)->setBaseGradient(gr);
    m_graph->seriesList().at(0)->setColorStyle(Q3DTheme::ColorStyleRangeGradient);
    //! [7]
   // fillSqrtSinProxy();


}

void SurfaceGraph::setGreenToRedGradient()
{
    QLinearGradient gr;
    gr.setColorAt(0.0, Qt::darkGreen);
    gr.setColorAt(0.5, Qt::yellow);
    gr.setColorAt(0.8, Qt::red);
    gr.setColorAt(1.0, Qt::darkRed);

    m_graph->seriesList().at(0)->setBaseGradient(gr);
    m_graph->seriesList().at(0)->setColorStyle(Q3DTheme::ColorStyleRangeGradient);
   // fillSqrtSinProxy();

}

