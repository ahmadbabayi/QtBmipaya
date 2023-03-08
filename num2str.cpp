#include "num2str.h"

Num2Str::Num2Str()
{

}

QString Num2Str::Adad2Huruf(QString s){
    QString a,b,c,d,q,w,e,r;
    s = InsertZero(s,12);

    a = s.mid(9,3);
    b = s.mid(6,3);
    c = s.mid(3,3);
    d = s.mid(0,3);
    q = Sadqan(a);
    w = Sadqan(b);
    e = Sadqan(c);
    r = Sadqan(d);

    if (r != ""){
        if ((e != "") || (w != "") || (q != "")){
            r = r + " میلیارد و ";
        }
        else {
            r = r + " میلیارد ";
        }
    }

    if (e != ""){
        if ((w != "") || (q != "")){
            e = e + " میلیون و ";
        }
        else {
            e = e + " میلیون ";
        }
    }

    if (w != ""){
        if (q != ""){
            w = w + " هزار و ";
        }
        else {
            w = w + " هزار ";
        }
    }
    s = r+e+w+q;
    return s;
}

QString Num2Str::Sadqan(QString s){
    QString a,b,c,d,g;
    s = InsertZero(s,3);
    g = s;
    if (g == "000"){
        s = "";
    }
    else {
    a = s.mid(1,2);
    b = s.mid(2,1);
    c = s.mid(1,1);
    d = s.mid(0,1);
    if (a.toInt() <20){
        switch (a.toInt()) {
        case 1: a ="یک"; break;
        case 2: a ="دو"; break;
        case 3: a ="سه"; break;
        case 4: a ="چهار"; break;
        case 5: a ="پنج"; break;
        case 6: a ="شش"; break;
        case 7: a ="هفت"; break;
        case 8: a ="هشت"; break;
        case 9: a ="نه"; break;
        case 10: a ="ده"; break;
        case 11: a ="یازده"; break;
        case 12: a ="دوازده"; break;
        case 13: a ="سیزده"; break;
        case 14: a ="چهارده"; break;
        case 15: a ="پانزده"; break;
        case 16: a ="شانزده"; break;
        case 17: a ="هفده"; break;
        case 18: a ="هجده"; break;
        case 19: a ="نوزده"; break;
        default: a = "";
        }
    }
    else {
        a = "";
        switch (b.toInt()) {
        case 1: b ="یک"; break;
        case 2: b ="دو"; break;
        case 3: b ="سه"; break;
        case 4: b ="چهار"; break;
        case 5: b ="پنج"; break;
        case 6: b ="شش"; break;
        case 7: b ="هفت"; break;
        case 8: b ="هشت"; break;
        case 9: b ="نه"; break;
        default: b = "";
        }
        switch (c.toInt()) {
        case 2: c ="بیست"; break;
        case 3: c ="سی"; break;
        case 4: c ="چهل"; break;
        case 5: c ="پنجاه"; break;
        case 6: c ="شصت"; break;
        case 7: c ="هفتاد"; break;
        case 8: c ="هشتاد"; break;
        case 9: c ="نود"; break;
        default: c = "";
        }
    }
    switch (d.toInt()) {
    case 1: d ="یکصد"; break;
    case 2: d ="دویست"; break;
    case 3: d ="سیصد"; break;
    case 4: d ="چهارصد"; break;
    case 5: d ="پانصد"; break;
    case 6: d ="ششصد"; break;
    case 7: d ="هفتصد"; break;
    case 8: d ="هشتصد"; break;
    case 9: d ="نهصد"; break;
    default: d = "";
    }
    if (a !=""){
        if (d !=""){
            d = d+ " و ";
        }
        s = d+a;
    }
    else{
        if ((d!="") && ((c!="") || (b!=""))){
            d = d+ " و ";
        }
        if ((c!="") && (b!="")){
            c = c + " و ";
        }
        s = d+c+b;
    }
    switch (g.toInt()) {
    case 100: s ="یکصد"; break;
    case 200: s ="دویست"; break;
    case 300: s ="سیصد"; break;
    case 400: s ="چهارصد"; break;
    case 500: s ="پانصد"; break;
    case 600: s ="ششصد"; break;
    case 700: s ="هفتصد"; break;
    case 800: s ="هشتصد"; break;
    case 900: s ="نهصد"; break;
    }
    }
    return s;
}


QString Num2Str::InsertZero(QString s, int k){
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
