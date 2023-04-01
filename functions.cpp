#include "functions.h"

Functions::Functions(QObject *parent)
    : QObject{parent}
{

}

QString Functions::InsertZero(QString s, int k){
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

QString Functions::InsertComma(QString s){
      int f = 0, h = 0, k = 0;
      k = s.length();
      h = trunc( double( k ) / 3 );
      for (f = 1; f <= h; f++)
      {
        if ( ( k - 3 ) != 0 ){
            s.insert(k-3,",");
        }
        k = k - 3;
      }
      return s;
}

bool Functions::ShebaCheck(QString s){
    bool result = true;
      QString a, d, f;
      int i = 0, j = 0, sum = 0;
      if ( s.length() != 24 )
      {
        result = false;
        return result;
      }
      a = s.mid( 0, 2 );
      s = s.mid( 2, 22 ) + "1827" + a;
      d = s.mid( 0, 13 );
      f = s.mid( 13, 15 );
      quint64 qi = d.toLongLong();
      i = qi % 97;
      qi = f.toLongLong();
      j = qi %97;
      sum = ( i * 45 ) + j;
      i = sum % 97;
      if ( i != 1 )
        result = false;
      return result;
}
