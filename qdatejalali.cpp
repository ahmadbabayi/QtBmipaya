#include "qdatejalali.h"

QDateJalali::QDateJalali(QObject *parent)
    : QObject{parent}
{
    /*******************************************How to use:***********************************************\
#include "qdatejalali.h"
QDateJalali Jalali;
QDateTime date =QDateTime::currentDateTime();
QStringList shamsi=  Jalali.ToShamsi(  date.toString("yyyy"), date.toString("MM"),date.toString("dd"));
QString JalailDate =shamsi.at(0)+"/"+shamsi.at(1)+"/"+shamsi.at(2);
      \*****************************************************************************************************/
}

QString QDateJalali::JalaliDate(){
    //Shamsi Calender
    QDateJalali Jalali;
    long gy = QDate::currentDate().year(); long gm = QDate::currentDate().month(); long gd = QDate::currentDate().day();
    QStringList shamsi=  Jalali.gregorian_to_jalali(gy,gm,gd);
    QString JalailDate =shamsi.at(0)+"-"+InsertZero(shamsi.at(1),2)+"-"+InsertZero(shamsi.at(2),2);
    return JalailDate;
}

QString QDateJalali::JalaliTarix(){
    //Shamsi Calender
    QDateJalali Jalali;
    long gy = QDate::currentDate().year(); long gm = QDate::currentDate().month(); long gd = QDate::currentDate().day();
    QStringList shamsi=  Jalali.gregorian_to_jalali(gy,gm,gd);
    QString JalailDate =shamsi.at(0)+"/"+InsertZero(shamsi.at(1),2)+"/"+InsertZero(shamsi.at(2),2);
    return JalailDate;
}

QString QDateJalali::InsertZero(QString s, int k){
      int h = 0;
      QString d;
      h = s.length();
      d = "0";
      if ( h < k )
      {
        while ( h < k )
        {
          s = d + s;
          h = h + 1;
        }
      }
      return s;
}

/**  Gregorian & Jalali (Hijri_Shamsi,Solar) Date Converter Functions
Author: JDF.SCR.IR =>> Download Full Version :  http://jdf.scr.ir/jdf
License: GNU/LGPL _ Open Source & Free :: Version: 2.80 : [2020=1399]
---------------------------------------------------------------------
355746=361590-5844 & 361590=(30*33*365)+(30*8) & 5844=(16*365)+(16/4)
355666=355746-79-1 & 355668=355746-79+1 &  1595=605+990 &  605=621-16
990=30*33 & 12053=(365*33)+(32/4) & 36524=(365*100)+(100/4)-(100/100)
1461=(365*4)+(4/4) & 146097=(365*400)+(400/4)-(400/100)+(400/400)  */

QStringList QDateJalali::gregorian_to_jalali(long gy, long gm, long gd) {
  long out[3];
  long days;
  {
    long gy2 = (gm > 2) ? (gy + 1) : gy;
    long g_d_m[12] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};
    days = 355666 + (365 * gy) + ((int)((gy2 + 3) / 4)) - ((int)((gy2 + 99) / 100)) + ((int)((gy2 + 399) / 400)) + gd + g_d_m[gm - 1];
  }
  long jy = -1595 + (33 * ((int)(days / 12053)));
  days %= 12053;
  jy += 4 * ((int)(days / 1461));
  days %= 1461;
  if (days > 365) {
    jy += (int)((days - 1) / 365);
    days = (days - 1) % 365;
  }
  out[0] = jy;
  if (days < 186) {
    out[1]/*jm*/ = 1 + (int)(days / 31);
    out[2]/*jd*/ = 1 + (days % 31);
  } else {
    out[1]/*jm*/ = 7 + (int)((days - 186) / 30);
    out[2]/*jd*/ = 1 + ((days - 186) % 30);
  }
  QStringList shamsi;
  shamsi << QString::number(out[0]) << QString::number(out[1])<< QString::number(out[2]) ;
  return shamsi;
}
