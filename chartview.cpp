/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Charts module of the Qt Toolkit.
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

#include "chartview.h"
#include <QtCharts/QScatterSeries>
#include <QtCharts/QLegendMarker>
#include <QtGui/QImage>
#include <QtGui/QPainter>
#include <QtCore/QtMath>

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

#include <QtCharts/QScatterSeries>
#include <QtCharts/QLegendMarker>
#include <QtGui/QImage>
#include <QtGui/QPainter>
#include <QtCore/QtMath>

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


#define PORT "5555"//27015//5555
#define DEFAULT_BUFLEN 9192




//WSADATA wsa;
//SOCKET s, new_socket;
//struct sockaddr_in server, client;
//int c;
//char *message;
//int opt = 1;

//int iResult;
int recvbuflen2 = DEFAULT_BUFLEN;


//char recvbuf[DEFAULT_BUFLEN];

int touch2[20][3];
int force2;


QScatterSeries *series0 = new QScatterSeries();
QScatterSeries *series1 = new QScatterSeries();
QScatterSeries *series2 = new QScatterSeries();
QScatterSeries *series3 = new QScatterSeries();
QScatterSeries *series4 = new QScatterSeries();
QScatterSeries *series5 = new QScatterSeries();
QScatterSeries *series6 = new QScatterSeries();
QScatterSeries *series7 = new QScatterSeries();
QScatterSeries *series8 = new QScatterSeries();
QScatterSeries *series9 = new QScatterSeries();
QScatterSeries *series10 = new QScatterSeries();
QScatterSeries *series11 = new QScatterSeries();
QScatterSeries *series12 = new QScatterSeries();
QScatterSeries *series13 = new QScatterSeries();
QScatterSeries *series14 = new QScatterSeries();


ChartView::ChartView(QWidget *parent) :
    QChartView(new QChart(), parent)
{
    //![1]
   // QScatterSeries *series0 = new QScatterSeries();
   // series0->setName("touch data");
    series0->setMarkerShape(QScatterSeries::MarkerShapeCircle);
    series0->setMarkerSize(0.1);

//    QScatterSeries *series1 = new QScatterSeries();
//    series1->setName("scatter2");
//    series1->setMarkerShape(QScatterSeries::MarkerShapeRectangle);
//    series1->setMarkerSize(20.0);

//    QScatterSeries *series2 = new QScatterSeries();
//    series2->setName("scatter3");
//    series2->setMarkerShape(QScatterSeries::MarkerShapeRectangle);
//    series2->setMarkerSize(30.0);
    //![1]

    //![2]
    series0->append(0, 0);
    series0->append(0, 15);
    series0->append(23, 0);
    series0->append(23, 15);

//    *series1 << QPointF(1, 1) << QPointF(3, 3) << QPointF(7, 6) << QPointF(8, 3) << QPointF(10, 2);
//    *series2 << QPointF(1, 5) << QPointF(4, 6) << QPointF(6, 3) << QPointF(9, 5);
//    //![2]

    //![3]
//    QPainterPath starPath;
//    starPath.moveTo(28, 15);
//    for (int i = 1; i < 5; ++i) {
//        starPath.lineTo(14 + 14 * qCos(0.8 * i * M_PI),
//                        15 + 14 * qSin(0.8 * i * M_PI));
//    }
//    starPath.closeSubpath();

//    QImage star(30, 30, QImage::Format_ARGB32);
//    star.fill(Qt::transparent);

//    QPainter painter(&star);
//    painter.setRenderHint(QPainter::Antialiasing);
//    painter.setPen(QRgb(0xf6a625));
//    painter.setBrush(painter.pen().color());
//    painter.drawPath(starPath);

//    series2->setBrush(star);
//    series2->setPen(QColor(Qt::transparent));
    //![3]

    //![4]
    //setRenderHint(QPainter::Antialiasing);
    chart()->addSeries(series0);
    chart()->addSeries(series1);
    chart()->addSeries(series2);
    chart()->addSeries(series3);
    chart()->addSeries(series4);
    chart()->addSeries(series5);
    chart()->addSeries(series6);
    chart()->addSeries(series7);
    chart()->addSeries(series8);
    chart()->addSeries(series9);
    chart()->addSeries(series10);
    chart()->addSeries(series11);
    chart()->addSeries(series12);
    chart()->addSeries(series13);
    chart()->addSeries(series14);
 //   chart()->addSeries(series1);
 //   chart()->addSeries(series2);

 //   chart()->setTitle("Simple scatterchart example");
    chart()->createDefaultAxes();
    chart()->setDropShadowEnabled(false);
    //![4]
   //   timerId = startTimer(150);
    //![5]
 //   chart()->legend()->setMarkerShape(QLegend::MarkerShapeFromSeries);
    //![5]
}
void ChartView::timerEvent(QTimerEvent *event)
{
  //  UpdateChart();
}

void ChartView::UpdateChart()
{

    int j = 0;
    int i = 0;
    int k = 0;
    int p = 0;




    QTextStream standardOutput(stdout);
    QByteArray data;
    const char * point;
   // char recvbuf[DEFAULT_BUFLEN];

  printf("Here");
    //  while(1){//iResult = recv(new_socket, recvbuf, recvbuflen, 0)>0){
       //   iResult = recv(new_socket, recvbuf, recvbuflen2, 0);
      //if(iResult>0){
      //    printf("Bytes received: %d\n", iResult);
//}
  printf("Here2");

//     // std::cout << "here" << std::endl;
//      std::cout << "second" << std::endl;
//      std::cout << recvbuf << std::endl;
//      //std::cout << "here" << std::endl;

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
      }
                     else if((recvbuf[index]!=' ' && recvbuf[index] != ',' && recvbuf[index] != '[' && recvbuf[index] != ']' && recvbuf[index] != '.')
                                && (recvbuf[index+1]!=' ' && recvbuf[index+1] != '.' && recvbuf[index+1] != '[' && recvbuf[index+1] != ']' && recvbuf[index+1] != ',')
                             &&(recvbuf[index+2]!=' ' && recvbuf[index+2] != '.' && recvbuf[index+2] != '[' && recvbuf[index+2] != ']' && recvbuf[index+2] != ',')
                             &&(recvbuf[index+3]!=' ' && recvbuf[index+3] != '.' && recvbuf[index+3] != '[' && recvbuf[index+3] != ']' && recvbuf[index+3] != ',')){


                       //  std::cout << recvbuf[index] << std::endl;
                         int digit;
                         int digit2;
                         std::stringstream strValue;
                          std::stringstream strValue4;
                         std::stringstream strValue3;
                         strValue << recvbuf[index];
                         strValue >> row[k];
                         std::stringstream strValue2;
                         strValue2 << recvbuf[index+1];
                         strValue2 >> test;
                         strValue3 << recvbuf[index+2];
                         strValue3 >> digit;
                          strValue3 << recvbuf[index+3];
                          strValue3 >> digit2;
                         row[k] = row[k]*1000 + test*100 + digit*10+digit2;// + (row[k+1] - '0');
                       //  std::cout << row[k] << std::endl;
                         touch2[d][k] = row[k];
                       //  std::cout << touch[d][k] << std::endl;
                        // std::cout << test << std::endl;
                         index = index + 4;
                         k++;
                         if(k==3){
                             k = 0;
                             d++;
                         }
      }


                     //three digits
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
                         touch2[d][k] = row[k];
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
                     touch2[d][k] = row[k];
                   //  std::cout << touch[d][k] << std::endl;
                    // std::cout << test << std::endl;
                     index = index + 2;
                     k++;
                     if(k==3){
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
                     touch2[d][k] = row[k];
                   //  std::cout << integertest[d][k] << std::endl;
                     index++;
                     k++;
                     if(k==3){
                         k = 0;
                         d++;
                     }

      }


      }



  std::cout << "start" << std::endl;
  std::cout << touch2[0][0] << std::endl;
  std::cout << touch2[0][1] << std::endl;
  std::cout << touch2[0][2] << std::endl;
  std::cout << touch2[1][0] << std::endl;
  std::cout << touch2[1][1] << std::endl;
  std::cout << touch2[1][2] << std::endl;
  std::cout << touch2[2][0] << std::endl;
  std::cout << touch2[2][1] << std::endl;
  std::cout << touch2[2][2] << std::endl;
  std::cout << touch2[3][0] << std::endl;
  std::cout << touch2[3][1] << std::endl;
  std::cout << touch2[3][2] << std::endl;
  std::cout << touch2[4][0] << std::endl;
  std::cout << touch2[4][1] << std::endl;
  std::cout << touch2[4][2] << std::endl;
  std::cout << touch2[5][0] << std::endl;
  std::cout << touch2[5][1] << std::endl;
  std::cout << touch2[5][2] << std::endl;
  std::cout << "end" << std::endl;


 // series0->setMarkerSize(10);
  series0->clear();
  series1->clear();
  series2->clear();
  series3->clear();
  series4->clear();
  series5->clear();
  series6->clear();
  series7->clear();
  series8->clear();
  series9->clear();
  series10->clear();
  series11->clear();
  series12->clear();
  series13->clear();
  series14->clear();

if(1){//organizing

  if(touch2[0][2] > 5 && touch2[0][2] <= 30){
    series0->setMarkerSize(20);
  }
  else if(touch2[0][2] > 30 && touch2[0][2] <= 70){
    series0->setMarkerSize(30);
  }
  else if(touch2[0][2] > 70 && touch2[0][2] <= 100 ){
  series0->setMarkerSize(40);
  }
  else if(touch2[0][2] > 100 ){
  series0->setMarkerSize(50);
  }
  else {
     series0->setMarkerSize(0);
  }



  if(touch2[1][2] > 5 && touch2[1][2] <= 30){
    series1->setMarkerSize(20);
  }
  else if(touch2[1][2] > 30 && touch2[1][2] <= 70){
    series1->setMarkerSize(30);
  }
  else if(touch2[1][2] > 70 && touch2[1][2] <= 100 ){
  series1->setMarkerSize(40);
  }
  else if(touch2[1][2] > 100 ){
  series1->setMarkerSize(50);
  }
  else {
     series1->setMarkerSize(0);
  }


  if(touch2[2][2] > 5 && touch2[2][2] <= 30){
    series2->setMarkerSize(20);
  }
  else if(touch2[2][2] > 30 && touch2[2][2] <= 70){
    series2->setMarkerSize(30);
  }
  else if(touch2[2][2] > 70 && touch2[2][2] <= 100 ){
  series2->setMarkerSize(40);
  }
  else if(touch2[2][2] > 100 ){
  series2->setMarkerSize(50);
  }
  else {
     series2->setMarkerSize(0);
  }



  if(touch2[3][2] > 5 && touch2[3][2] <= 30){
    series3->setMarkerSize(20);
  }
  else if(touch2[3][2] > 30 && touch2[3][2] <= 70){
    series3->setMarkerSize(30);
  }
  else if(touch2[3][2] > 70 && touch2[3][2] <= 100 ){
  series3->setMarkerSize(40);
  }
  else if(touch2[3][2] > 100 ){
  series3->setMarkerSize(50);
  }
  else {
     series3->setMarkerSize(0);
  }


  if(touch2[4][2] > 5 && touch2[4][2] <= 30){
    series4->setMarkerSize(20);
  }
  else if(touch2[4][2] > 30 && touch2[4][2] <= 70){
    series4->setMarkerSize(30);
  }
  else if(touch2[4][2] > 70 && touch2[4][2] <= 100 ){
  series4->setMarkerSize(40);
  }
  else if(touch2[4][2] > 100 ){
  series4->setMarkerSize(50);
  }
  else {
     series4->setMarkerSize(0);
  }


  if(touch2[5][2] > 5 && touch2[5][2] <= 30){
    series5->setMarkerSize(20);
  }
  else if(touch2[5][2] > 30 && touch2[5][2] <= 70){
    series5->setMarkerSize(30);
  }
  else if(touch2[5][2] > 70 && touch2[5][2] <= 100 ){
  series5->setMarkerSize(40);
  }
  else if(touch2[5][2] > 100 ){
  series5->setMarkerSize(50);
  }
  else {
     series5->setMarkerSize(0);
  }


  if(touch2[6][2] > 5 && touch2[6][2] <= 30){
    series6->setMarkerSize(20);
  }
  else if(touch2[6][2] > 30 && touch2[6][2] <= 70){
    series6->setMarkerSize(30);
  }
  else if(touch2[6][2] > 70 && touch2[6][2] <= 100 ){
  series6->setMarkerSize(40);
  }
  else if(touch2[6][2] > 100 ){
  series6->setMarkerSize(50);
  }
  else {
     series6->setMarkerSize(0);
  }



  if(touch2[7][2] > 5 && touch2[7][2] <= 30){
    series7->setMarkerSize(20);
  }
  else if(touch2[7][2] > 30 && touch2[7][2] <= 70){
    series7->setMarkerSize(30);
  }
  else if(touch2[7][2] > 70 && touch2[7][2] <= 100 ){
  series7->setMarkerSize(40);
  }
  else if(touch2[7][2] > 100 ){
  series7->setMarkerSize(50);
  }
  else {
     series7->setMarkerSize(0);
  }



  if(touch2[8][2] > 5 && touch2[8][2] <= 30){
    series8->setMarkerSize(20);
  }
  else if(touch2[8][2] > 30 && touch2[8][2] <= 70){
    series8->setMarkerSize(30);
  }
  else if(touch2[8][2] > 70 && touch2[8][2] <= 100 ){
  series8->setMarkerSize(40);
  }
  else if(touch2[8][2] > 100 ){
  series8->setMarkerSize(50);
  }
  else {
     series8->setMarkerSize(0);
  }



  if(touch2[9][2] > 5 && touch2[9][2] <= 30){
    series9->setMarkerSize(20);
  }
  else if(touch2[9][2] > 30 && touch2[9][2] <= 70){
    series9->setMarkerSize(30);
  }
  else if(touch2[9][2] > 70 && touch2[9][2] <= 100 ){
  series9->setMarkerSize(40);
  }
  else if(touch2[9][2] > 100 ){
  series9->setMarkerSize(50);
  }
  else {
     series9->setMarkerSize(0);
  }



  if(touch2[10][2] > 5 && touch2[10][2] <= 30){
    series10->setMarkerSize(20);
  }
  else if(touch2[10][2] > 30 && touch2[10][2] <= 70){
    series10->setMarkerSize(30);
  }
  else if(touch2[10][2] > 70 && touch2[10][2] <= 100 ){
  series10->setMarkerSize(40);
  }
  else if(touch2[10][2] > 100 ){
  series10->setMarkerSize(50);
  }
  else {
     series10->setMarkerSize(0);
  }


  if(touch2[11][2] > 5 && touch2[11][2] <= 30){
    series11->setMarkerSize(20);
  }
  else if(touch2[11][2] > 30 && touch2[11][2] <= 70){
    series11->setMarkerSize(30);
  }
  else if(touch2[11][2] > 70 && touch2[11][2] <= 100 ){
  series11->setMarkerSize(40);
  }
  else if(touch2[11][2] > 100 ){
  series11->setMarkerSize(50);
  }
  else {
     series11->setMarkerSize(0);
  }


  if(touch2[12][2] > 5 && touch2[12][2] <= 30){
    series12->setMarkerSize(20);
  }
  else if(touch2[12][2] > 30 && touch2[12][2] <= 70){
    series12->setMarkerSize(30);
  }
  else if(touch2[12][2] > 70 && touch2[12][2] <= 100 ){
  series12->setMarkerSize(40);
  }
  else if(touch2[12][2] > 100 ){
  series12->setMarkerSize(50);
  }
  else {
     series12->setMarkerSize(0);
  }



  if(touch2[13][2] > 5 && touch2[13][2] <= 30){
    series13->setMarkerSize(20);
  }
  else if(touch2[13][2] > 30 && touch2[13][2] <= 70){
    series13->setMarkerSize(30);
  }
  else if(touch2[13][2] > 70 && touch2[13][2] <= 100 ){
  series13->setMarkerSize(40);
  }
  else if(touch2[13][2] > 100 ){
  series13->setMarkerSize(50);
  }
  else {
     series13->setMarkerSize(0);
  }



  if(touch2[14][2] > 5 && touch2[14][2] <= 30){
    series14->setMarkerSize(20);
  }
  else if(touch2[14][2] > 30 && touch2[14][2] <= 70){
    series14->setMarkerSize(30);
  }
  else if(touch2[14][2] > 70 && touch2[14][2] <= 100 ){
  series14->setMarkerSize(40);
  }
  else if(touch2[14][2] > 100 ){
  series14->setMarkerSize(50);
  }
  else {
     series14->setMarkerSize(0);
  }







}//organizing


  series0->append(23-touch2[0][1], touch2[0][0]);
  series1->append(23-touch2[1][1], touch2[1][0]);
  series2->append(23-touch2[2][1], touch2[2][0]);
  series3->append(23-touch2[3][1], touch2[3][0]);
  series4->append(23-touch2[4][1], touch2[4][0]);
  series5->append(23-touch2[5][1], touch2[5][0]);
  series6->append(23-touch2[6][1], touch2[6][0]);
  series7->append(23-touch2[7][1], touch2[7][0]);
  series8->append(23-touch2[8][1], touch2[8][0]);
  series9->append(23-touch2[9][1], touch2[9][0]);
  series10->append(23-touch2[10][1], touch2[10][0]);
  series11->append(23-touch2[11][1], touch2[11][0]);
  series12->append(23-touch2[12][1], touch2[12][0]);
  series13->append(23-touch2[13][1], touch2[13][0]);
  series14->append(23-touch2[14][1], touch2[14][0]);











}
