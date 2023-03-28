#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qdatejalali.h"
#include "numberformatdelegate.h"
#include "num2str.h"

#include "helpdialog.h"
#include "aboutdialog.h"
#include "chequeprintdialog.h"

#include "xlsxdocument.h"
#include "xlsxchartsheet.h"
#include "xlsxcellrange.h"
#include "xlsxchart.h"
#include "xlsxrichstring.h"
#include "xlsxworkbook.h"
using namespace QXlsx;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Shamsi Calender
    QDateJalali Jalali;
    ui->TarixShamsi->setText("تاریخ امروز: "+Jalali.JalaliTarix());

    ui->ErsalSeri->setValidator( new QIntValidator);
    ui->ErsalSheba->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9]*")));
    ui->Sheba->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9]*")));
    ui->Shenaseh->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9]*")));

    QDir *datadir = new QDir();
    if (!datadir->exists("BmiPaya_data")){
        datadir->mkdir("BmiPaya_data");
            }
    if (!QFile::exists("BmiPaya_data/bmipaya.db")){
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName("BmiPaya_data/bmipaya.db");
        if (db.open()){
            QSqlQuery query;
            query.exec("create table paya (id INTEGER PRIMARY KEY AUTOINCREMENT, sheba TEXT, shenaseh TEXT, name TEXT, mablagh TEXT, sharh TEXT)");
            query.exec("create table payaersal (id INTEGER PRIMARY KEY, sheba TEXT, seri TEXT, name TEXT, sharh TEXT)");
            query.exec("INSERT INTO payaersal (id, sheba, seri, name, sharh) VALUES (1,'','','','')");
            db.close();
            db.removeDatabase(QSqlDatabase::defaultConnection);
        }
    }

    if (!dbopen()){
        QMessageBox msgBox; msgBox.setText("Database Error."); msgBox.exec();
    }
    ErsalReload();
    TableReload();
    SumTedad();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_Sheba_returnPressed()
{
    QWidget::focusNextChild();
}


void MainWindow::on_Name_returnPressed()
{
    QWidget::focusNextChild();
}


void MainWindow::on_Mablagh_returnPressed()
{
    QWidget::focusNextChild();
}


void MainWindow::on_Sharh_returnPressed()
{
    QWidget::focusNextChild();
}


void MainWindow::on_ErsalSheba_returnPressed()
{
    QWidget::focusNextChild();
}


void MainWindow::on_ErsalName_returnPressed()
{
    QWidget::focusNextChild();
}


void MainWindow::on_ErsalSeri_returnPressed()
{
    QWidget::focusNextChild();
}


void MainWindow::on_ErsalSharh_returnPressed()
{
    ui->Sheba->setFocus();
}


void MainWindow::on_SabtButton_clicked()
{
    if (sehv()){
    QSqlQuery query;
    if (virayesh){
        query.exec("UPDATE paya SET sheba = '"+ui->Sheba->text()+"', shenaseh = '"+ui->Shenaseh->text()+"', name = '"+ui->Name->text()+"', mablagh = '"+ui->Mablagh->text().replace(",","")+"', sharh = '"+ui->Sharh->text()+"' WHERE id ="+ QString::number(id));
    }
    else{
        query.exec("INSERT INTO paya (sheba,shenaseh,name,mablagh,sharh) VALUES ('"+ui->Sheba->text()+"','"+ui->Shenaseh->text()+"','"+ui->Name->text()+"','"+ui->Mablagh->text().replace(",","")+"','"+ui->Sharh->text()+"')");
    }

    ui->Sheba->setFocus();
    ui->Sheba->setText("");
    ui->Shenaseh->setText("");
    ui->Name->setText("");
    ui->Mablagh->setText("");
    ui->SearchEdit->setText("");
    TableReload();
    SumTedad();
    ui->tableView->scrollToBottom();
    virayesh = false;
    }
}


void MainWindow::on_Shenaseh_returnPressed()
{
    QWidget::focusNextChild();
}


void MainWindow::on_RemoveButton_clicked()
{
    QSqlQuery query;
    query.exec("DELETE FROM paya");
    query.exec("DELETE FROM sqlite_sequence");
    TableReload();
    SumTedad();
}
void MainWindow::TableReload(){
   QSqlQueryModel *model = new QSqlQueryModel;
   if (ui->SearchEdit->text()==""){
       model->setQuery("SELECT * FROM paya");
   }
   else  {
       model->setQuery("SELECT * FROM paya WHERE sheba LIKE '%"+ui->SearchEdit->text()+"%' OR name LIKE '%"+ui->SearchEdit->text()+"%'");
   }

   model->setHeaderData(0, Qt::Horizontal, tr("ردیف"));
   model->setHeaderData(1, Qt::Horizontal, tr("شماره شبا"));
   model->setHeaderData(2, Qt::Horizontal, tr("شناسه واریز"));
   model->setHeaderData(3, Qt::Horizontal, tr("نام و نام خانوادگی"));
   model->setHeaderData(4, Qt::Horizontal, tr("مبلغ"));
   model->setHeaderData(5, Qt::Horizontal, tr("شرح"));
   ui->tableView->verticalHeader()->setVisible(false);
   ui->tableView->setModel(model);
   ui->tableView->setItemDelegateForColumn(4, new NumberFormatDelegate(this));
   ui->tableView->resizeColumnsToContents();
   ui->tableView->resizeRowsToContents();
}

void MainWindow::ErsalReload(){
    QSqlQuery query;
    query.exec("SELECT * FROM payaersal WHERE id =1");
    while (query.next()) {
            ui->ErsalSheba->setText(query.value(1).toString());
            ui->ErsalSeri->setText(query.value(2).toString());
            ui->ErsalName->setText(query.value(3).toString());
            ui->ErsalSharh->setText(query.value(4).toString());
    }
}

void MainWindow::SumTedad(){
    QSqlQuery query;
    tedad = 0;
    query.exec("SELECT id FROM paya");
    while (query.next()) {
        tedad ++;
    }
    query.exec("SELECT SUM(mablagh) FROM paya");
    while (query.next()) {
        sum = query.value(0).toString();
    }
    if (sum == ""){
        sum = "0";
    }
    ui->TedadLabel->setText("تعداد کل: "+QString::number(tedad));
    /*
    QLocale::setDefault(QLocale::English);
    QLocale ss;
    QString str;
    str = ss.toString(123456789);
    QMessageBox msgBox; msgBox.setText(str); msgBox.exec();*/

    ui->SumLabel->setText("جمع کل: "+ InsertComma(sum));
}

bool MainWindow::ShebaCheck(QString s){
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

QString MainWindow::InsertZero(QString s, int k){
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

QString MainWindow::InsertComma(QString s){
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

bool MainWindow::sehv(){
    bool xata=true;
    if(ui->Sharh->text() == ""){
        xata = false;
        QMessageBox msgBox; msgBox.setText("شرح الزامی می‌باشد! "); msgBox.exec();
        ui->Sharh->setFocus();
    }
    if (ui->Mablagh->text() == ""){
        xata = false;
        QMessageBox msgBox; msgBox.setText("مبلغ الزامی می‌باشد! "); msgBox.exec();
        ui->Mablagh->setFocus();
    }
    if (ui->Name->text() == ""){
        xata = false;
        QMessageBox msgBox; msgBox.setText("نام و نام خانوادگی الزامی می‌باشد! "); msgBox.exec();
        ui->Name->setFocus();
    }
    if (!ShebaCheck(ui->Sheba->text())){
        xata = false;
        QMessageBox msgBox; msgBox.setText("شماره شبا نادرست می‌باشد! "); msgBox.exec();
        ui->Sheba->setFocus();
    }
    quint64 qi = ui->Mablagh->text().replace(",","").toLong();
    if (qi>1000000000){
        xata = false;
        QMessageBox msgBox; msgBox.setText("حد اکثر مبلغ برای حواله پایا یک میلیارد ریال می‌باشد! "); msgBox.exec();
        ui->Mablagh->setFocus();
    }
    return xata;
}

bool MainWindow::ErsalSehv(){
    bool xata=true;
    if(ui->ErsalSheba->text() == "" || ui->ErsalSeri->text() == "" || ui->ErsalName->text() == "" || ui->ErsalSharh->text() == ""){
        xata = false;
        QMessageBox msgBox; msgBox.setText("تمامی فیلدهای ارسال کننده حواله را پر کنید! "); msgBox.exec();
        ui->ErsalSheba->setFocus();
    }
    if (!ShebaCheck(ui->ErsalSheba->text())){
        xata = false;
        QMessageBox msgBox; msgBox.setText("شماره شبای ارسال کننده حواله نادرست می‌باشد! "); msgBox.exec();
        ui->ErsalSheba->setFocus();
    }
    int qi = ui->ErsalSeri->text().toInt();
    if (qi<1){
        xata = false;
        QMessageBox msgBox; msgBox.setText("شماره سری به ترتیب از یک شروع شده و در هر ایجاد فایل باید یک واحد افزایش یابد! "); msgBox.exec();
        ui->ErsalSeri->setFocus();
    }
    if (tedad < 1){
        xata = false;
        QMessageBox msgBox; msgBox.setText("لیست واریزی خالی می‌باشد! "); msgBox.exec();
    }
    return xata;
}

void MainWindow::on_ErsalSheba_textChanged(const QString &arg1)
{
    QSqlQuery query;
    query.exec("UPDATE payaersal SET sheba = '"+ui->ErsalSheba->text()+"' WHERE id =1");
}


void MainWindow::on_ErsalSeri_textChanged(const QString &arg1)
{
    QSqlQuery query;
    query.exec("UPDATE payaersal SET seri = '"+ui->ErsalSeri->text()+"' WHERE id =1");
}


void MainWindow::on_ErsalName_textChanged(const QString &arg1)
{
    QSqlQuery query;
    query.exec("UPDATE payaersal SET name = '"+ui->ErsalName->text()+"' WHERE id =1");
}


void MainWindow::on_ErsalSharh_textChanged(const QString &arg1)
{
    QSqlQuery query;
    query.exec("UPDATE payaersal SET sharh = '"+ui->ErsalSharh->text()+"' WHERE id =1");
}


void MainWindow::on_PrintdButton_clicked()
{
    if (ErsalSehv()){
        QPrinter *printer = new QPrinter();
        printer->setFullPage(true);
        QPageSize pageSize(QPageSize::A4);
        printer->setPageSize(pageSize);
        QPrintPreviewDialog *printPreview = new QPrintPreviewDialog(printer);
        connect(printPreview, SIGNAL(paintRequested(QPrinter*)), this, SLOT(printD(QPrinter*)));
        printPreview->setWindowTitle("Preview Dialog");
        printPreview->exec();
    }
}


void MainWindow::on_EditButton_clicked()
{
    bool ok;
    id = QInputDialog::getInt(this, tr("ویرایش رکورد موجود در لیست"), tr("شماره ردیف را وارد کنید:"), 1, 1, 100000, 1, &ok);
    if (ok){
    QSqlQuery query;
    query.exec("SELECT * FROM paya WHERE id =" + QString::number(id));
    while (query.next()) {
            ui->Sheba->setText(query.value(1).toString());
            ui->Shenaseh->setText(query.value(2).toString());
            ui->Name->setText(query.value(3).toString());
            ui->Mablagh->setText(InsertComma(query.value(4).toString()));
            ui->Sharh->setText(query.value(5).toString());
            ui->Sheba->setFocus();
    }
    virayesh = true;
    }
}

void MainWindow::on_PrintButton_clicked()
{
    if (ErsalSehv()){
        QPrinter *printer = new QPrinter();
        //printer.setPageOrientation(QPageLayout::Landscape);
        //printer.setPageSize(QPageSize::A4);
        QPageSize pageSize(QPageSize::A4);
        printer->setPageSize(pageSize);
        //printer.setOutputFormat(QPrinter::PdfFormat);
        //printer.setOutputFileName("nonwritable.pdf");
        QPrintPreviewDialog *printPreview = new QPrintPreviewDialog(printer);
        connect(printPreview, SIGNAL(paintRequested(QPrinter*)), this, SLOT(print(QPrinter*)));
        printPreview->setWindowTitle("Preview Dialog");
        //Qt::WindowFlags flags(Qt::WindowTitleHint);
        //printPreview->setWindowFlags(flags);
        //printPreview->setContentsMargins(1,1,1,1);
        printPreview->exec();
    }
}

void MainWindow::on_Mablagh_textEdited(const QString &arg1)
{
    QString str;
    /*
    QLocale::setDefault(QLocale::English);
    QLocale ss;
    str = ss.toString(ui->Mablagh->text().replace(",","").toLong());*/

    str = InsertComma(ui->Mablagh->text().replace(",",""));
    ui->Mablagh->setText(str);
}


void MainWindow::on_MakeButton_clicked()
{
    if (ErsalSehv()){
        QDateJalali tarix;
        QString xmlfile;
        xmlfile = InsertZero(ui->ErsalSeri->text(),9);
        xmlfile = "IR" + ui->ErsalSheba->text() + xmlfile + ".ccti";
        QFile file(xmlfile);
            if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
                return;

            QTextStream out(&file);
            out.setCodec("UTF-8");
            out << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
            out << "<Document xmlns=\"urn:iso:std:iso:20022:tech:xsd:pain.001.001.03\">\n";
            out << "<CstmrCdtTrfInitn>\n";
            out << "<GrpHdr>\n";
            out << "<MsgId>" << xmlfile.replace(".ccti","") << "</MsgId>\n";
            out << "<CreDtTm>" << tarix.JalaliDate() << "T08:00:00</CreDtTm>\n";
            out << "<NbOfTxs>" << QString::number(tedad) << "</NbOfTxs>\n";
            out << "<CtrlSum>" << sum << "</CtrlSum>\n";
            out << "<InitgPty>\n";
            out << "<Nm>" << ui->ErsalName->text() << "</Nm>\n";
            out << "</InitgPty>\n";
            out << "</GrpHdr>\n";
            out << "<PmtInf>\n";
            out << "<PmtInfId>1</PmtInfId>\n";
            out << "<PmtMtd>TRF</PmtMtd>\n";
            out << "<NbOfTxs>" << QString::number(tedad) << "</NbOfTxs>\n";
            out << "<CtrlSum>" << sum << "</CtrlSum>\n";
            out << "<ReqdExctnDt>" << tarix.JalaliDate() << "</ReqdExctnDt>\n";
            out << "<Dbtr>\n";
            out << "<Nm>" << ui->ErsalName->text() << "</Nm>\n";
            out << "</Dbtr>\n";
            out << "<DbtrAcct>\n";
            out << "<Id>\n";
            out << "<IBAN>IR" << ui->ErsalSheba->text() << "</IBAN>\n";
            out << "</Id>\n";
            out << "</DbtrAcct>\n";
            out << "<DbtrAgt>\n";
            out << "<FinInstnId>\n";
            out << "<BIC>BMJIIRTHXXX</BIC>\n";
            out << "</FinInstnId>\n";
            out << "</DbtrAgt>\n";

            QSqlQuery query;
            QString shenase;
            query.exec("SELECT * FROM paya");
            while (query.next()) {
                    out << "<CdtTrfTxInf>\n";
                    out << "<PmtId>\n";
                    shenase = (query.value(2).toString()!="") ? query.value(2).toString() : "EMPTY";
                    out << "<InstrId>" << shenase << "</InstrId>\n";
                    out << "<EndToEndId>EMPTY</EndToEndId>\n";
                    out << "</PmtId>\n";
                    out << "<Amt>\n";
                    out << "<InstdAmt Ccy=\"IRR\">" << query.value(4).toString() << "</InstdAmt>\n";
                    out << "</Amt>\n";
                    out << "<Cdtr>\n";
                    out << "<Nm>" << query.value(3).toString() << "</Nm>\n";
                    out << "</Cdtr>\n";
                    out << "<CdtrAcct>\n";
                    out << "<Id>\n";
                    out << "<IBAN>IR" << query.value(1).toString() << "</IBAN>\n";
                    out << "</Id>\n";
                    out << "</CdtrAcct>\n";
                    out << "<RmtInf>\n";
                    out << "<Ustrd>" << query.value(5).toString() << "</Ustrd>\n";
                    out << "</RmtInf>\n";
                    out << "</CdtTrfTxInf>\n";
            }

            out << "</PmtInf>\n";
            out << "</CstmrCdtTrfInitn>\n";
            out << "</Document>\n";

            QMessageBox msgBox; msgBox.setText(xmlfile + " File Created!"); msgBox.exec();
    }
}

void MainWindow::print(QPrinter *printer)
{
    QString txt;
    QSqlQuery query;
    QDateJalali Jalali;

    query.exec("SELECT * FROM paya");

    txt="<html width=\"100%\"><head><style>body {direction: rtl; font-family: \"B Nazanin\", \"Times New Roman\", Tahoma; }table, td {border: 1px solid black; border-collapse: collapse;}</style></head>"
         "<body><div dir=\"rtl\"><div align=\"left\"> :تاریخ "+Jalali.JalaliTarix()+"</div><h3 align=\"center\"> لیست واریزی پایای گروهی "+ui->ErsalName->text()+" بابت "+ui->ErsalSharh->text()+"</h3>"
         "<table border=\"1\" width=\"100%\" cellspacing=\"0\" cellpadding=\"3\">"
         "<tr><td>شرح</td><td>مبلغ</td><td>نام و نام خانوادگی</td><td>شناسه واریز</td><td>شماره شبا</td><td>ردیف</td></tr>";
    while (query.next()) {
        txt += "<tr><td>"+query.value(5).toString()+"</td><td>"+InsertComma(query.value(4).toString())+"</td><td>"+query.value(3).toString()+"</td><td>"+query.value(2).toString()+"</td><td>IR"+query.value(1).toString()+"</td><td>"+query.value(0).toString()+"</td></tr>";
    }
    txt += "<tr><td colspan=\"2\">"+InsertComma(sum)+"</td><td colspan=\"3\">&nbsp;</td><td>جمع</td></tr></table>";
    txt += "<table width=\"100%\" style = \"border: 0px solid black; border-collapse: collapse;\"><tr align=\"left\"><th>مهر و امضاء بانک</th><th>مهر و امضاء امضاداران مجاز</th><tr></table></div></body></html>";
    QTextDocument document;
    //document.setDocumentMargin(0.1);
        document.setHtml(txt);
        document.print(printer);
}
void MainWindow::printD(QPrinter *printer)
{
    QString xmlfile;
    xmlfile = InsertZero(ui->ErsalSeri->text(),9);
    xmlfile = "IR" + ui->ErsalSheba->text() + xmlfile + ".ccti";

    Num2Str s;
    QString h;
    h = s.Adad2Huruf(sum);

    QString txt;
    QSqlQuery query;

    QDateJalali Jalali;

    xmlfile = InsertZero(ui->ErsalSeri->text(),9);
    xmlfile = "IR" + ui->ErsalSheba->text() + xmlfile + ".ccti";
    QFile file(xmlfile);
    QString size = QString::number(file.size());

    query.exec("SELECT * FROM paya");

    txt="<html width=\"100%\"><head><style>body {direction: rtl; font-family: \"B Nazanin\", \"Times New Roman\", Tahoma; font-size: 16px;}</style></head>"
                 "<body><div dir=\"rtl\"><div> :تاریخ "+Jalali.JalaliTarix()+"</div><div dir=\"rtl\"> :شماره</div>"
                 "<h3 align = \"center\">‫دستور‬‫پرداخت‬ ‫سامانه‬ ‫پایاپای‬ ‫الکترونیکی - پایا‬</h3>"
                    "<div align = \"center\">‫بانک ملی ایران شعبه &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; کد شعبه ‪‬‬</div>"
                    "<br><div>اینجانب /شرکت <b>"+ui->ErsalName->text()+"</b> دارنده حساب شماره <b>"+ui->ErsalSheba->text().mid(11,13)+"</b> </div>"
                    "<div>آدرس و تلفن </div><br>"
                    "<div> بدینوسیله از بانک درخواست می‌کنیم که در تاریخ <b>"+Jalali.JalaliTarix()+"</b> جمعا مبلغ به عدد <b>"+InsertComma(sum)+"</b> ریال و به حروف <b>"+h+
        "</b> .ریال مطابق با جزئیات مندرج در فایل پیوست از محل حساب مبداء به حسابهای مقصد انتقال دهد </div>"
                 "<br><table width=\"100%\" cellspacing=\"1\" cellpadding=\"2\"  bgcolor=\"#000000\"><tr bgcolor=\"#ffffff\"><td> :نام فایل"+xmlfile+"<br> طول فایل به بایت --"+size+" --</td><td>مشخصات فایل پیوست</td></tr></table>"
                    "<p>‫و‬‫بدینوسیله‬ ‫تائید‬ ‫می‬ ‫نمایم‬ ‫که‬ ‫با‬ ‫ارائه‬ ‫این ‬‫دستور‬ ‫پرداخت‬ ‫و‬ ‫فایل پیوست‬‫ آن‬ ‫به‬ ‫بانک‬ ‫مسئولیت‬‫ صحت‬ ‫مندرجات ‬‫آن‬ ‫بر‬ ‫عهده‬ ‫اینجانب‬‫‪ /‬‬‫این‬ ‫شرکت‬ ‫بوده‬ ‫و‬ ‫کلیه شرایط ‬‫مندرج‬ ‫در‬ ‫ظهر‬ ‫دستور‬ ‫پرداخت‬ ‫و‬ ‫همچنین‬ ‫پرداخت‬‫ کارمزد‬ ‫به‬ ‫مبلغ‬ &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;‬ ‫ریال ‬‫به‬ ‫بانک‬ ‫را‬ ‫می پذیرم‬‫‪.‬‬</p>"
                    "<br><br><br><table width=\"100%\"><tr align=\"left\"><th>مهر و امضاء بانک</th><th>مهر و امضاء امضاداران مجاز</th><tr></table>"
                    "</div></body></html>";
    QTextDocument document;
    document.setDocumentMargin(0.1);
        document.setHtml(txt);
        document.print(printer);
}


void MainWindow::on_ExcelExport_triggered()
{
    QSqlQuery query;
    query.exec("SELECT * FROM paya");

    QString excelfile;
    excelfile = InsertZero(ui->ErsalSeri->text(),9);
    excelfile = "IR" + ui->ErsalSheba->text() + excelfile + ".xlsx";
    // [1]  Writing excel file(*.xlsx)
    QXlsx::Document xlsxW;
    QVariant writeValue;
    writeValue = QString("شماره شبا"); xlsxW.write(1, 1, writeValue);
    writeValue = QString("شناسه واریز"); xlsxW.write(1, 2, writeValue);
    writeValue = QString("نام و نام خانوادگی"); xlsxW.write(1, 3, writeValue);
    writeValue = QString("مبلغ"); xlsxW.write(1, 4, writeValue);
    writeValue = QString("شرح"); xlsxW.write(1, 5, writeValue);
    int i=1;
    while (query.next()) {
        i++;
        writeValue = "IR"+query.value(1).toString(); xlsxW.write(i, 1, writeValue);
        writeValue = query.value(2).toString(); xlsxW.write(i, 2, writeValue);
        writeValue = query.value(3).toString(); xlsxW.write(i, 3, writeValue);
        writeValue = query.value(4).toString(); xlsxW.write(i, 4, writeValue);
        writeValue = query.value(5).toString(); xlsxW.write(i, 5, writeValue);
    }
    xlsxW.saveAs(excelfile); // save the document as 'Test.xlsx'
    QMessageBox msgBox; msgBox.setText(excelfile + " File Created!"); msgBox.exec();
}


void MainWindow::on_Excelmport_triggered()
{
    QString fileName;
    fileName = QFileDialog::getOpenFileName(this, tr("Open Excel"), "", tr("Excel Files (*.xlsx)"));
    QXlsx::Document xlsxW;
    Document xlsxR(fileName);
    bool emptyCell = true, cellError; int i = 2;
    if (xlsxR.load()) // load excel file
        {
        QSqlQuery query;
        query.exec("DELETE FROM paya");
        query.exec("DELETE FROM sqlite_sequence");

        QString row[5];
        QVariant var;
        Cell* cell;

        while (emptyCell) {
            cellError = false;
            cell = xlsxR.cellAt(i, 1); // get cell pointer.
            if ( cell != NULL )
            {
                var = cell->readValue();  row[0] = var.toString().replace(" ","").replace("IR",""); if (!ShebaCheck(row[0])) { cellError = true; }
                cell = xlsxR.cellAt(i, 2); if ( cell != NULL ) { var = cell->readValue();  row[1] = var.toString().replace(" ","");}
                cell = xlsxR.cellAt(i, 3); if ( cell != NULL ) { var = cell->readValue();  row[2] = var.toString().trimmed(); } else { cellError = true; }
                cell = xlsxR.cellAt(i, 4); if ( cell != NULL ) { var = cell->readValue();  row[3] = var.toString().trimmed(); } else { cellError = true; }
                cell = xlsxR.cellAt(i, 5); if ( cell != NULL ) { var = cell->readValue();  row[4] = var.toString().trimmed(); } else { cellError = true; }
                if (!cellError){
                    query.exec("INSERT INTO paya (sheba,shenaseh,name,mablagh,sharh) VALUES ('"+row[0]+"','"+row[1]+"','"+row[2]+"','"+row[3]+"','"+row[4]+"')");
                }
                else {
                    QMessageBox msgBox; msgBox.setText("خطا در سطر شماره " + QString::number(i)); msgBox.exec();
                }
            }
            else { emptyCell = false;}
            i++;
        }
        ui->Sheba->setFocus();
        ui->Sheba->setText("");
        ui->Shenaseh->setText("");
        ui->Name->setText("");
        ui->Mablagh->setText("");
        TableReload();
        SumTedad();
        ui->tableView->scrollToBottom();
        }
}


void MainWindow::on_HelpAction_triggered()
{
    HelpDialog *helpdialog = new HelpDialog();
    helpdialog->show();
}


void MainWindow::on_AboutAction_triggered()
{
    AboutDialog * aboutdialog = new AboutDialog();
    aboutdialog->show();
}


void MainWindow::on_ExitAction_triggered()
{
    QApplication::exit();
}

void MainWindow::on_RestoerAction_triggered()
{
    QString fileName;
    fileName = QFileDialog::getOpenFileName(this, tr("Open CCTI File"), "", tr("CCTI Files (*.ccti)"));
    QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
            return;

    QTextStream in(&file);
    in.setCodec("UTF-8");
    QString someXML="", row[5];
    int i=0;
    bool ok2Insert = false;
    QSqlQuery query;
    query.exec("DELETE FROM paya");
    query.exec("DELETE FROM sqlite_sequence");

    while (!in.atEnd()){
        someXML = in.readLine().trimmed();

        if (i>30){
            if (someXML.contains("<InstrId>", Qt::CaseInsensitive)){
                row[1] = someXML.remove(QRegularExpression("<[^>]*>")).replace("EMPTY","");
            }
            if (someXML.contains("<InstdAmt", Qt::CaseInsensitive)){
                row[3] = someXML.remove(QRegularExpression("<[^>]*>"));
            }
            if (someXML.contains("<Nm>", Qt::CaseInsensitive)){
                row[2] = someXML.remove(QRegularExpression("<[^>]*>"));
            }
            if (someXML.contains("<IBAN>", Qt::CaseInsensitive)){
                row[0] = someXML.remove(QRegularExpression("<[^>]*>")).replace("IR","");
            }
            if (someXML.contains("<Ustrd", Qt::CaseInsensitive)){
                row[4] = someXML.remove(QRegularExpression("<[^>]*>"));
                ok2Insert = true;
            }
            if (ok2Insert){
                query.exec("INSERT INTO paya (sheba,shenaseh,name,mablagh,sharh) VALUES ('"+row[0]+"','"+row[1]+"','"+row[2]+"','"+row[3]+"','"+row[4]+"')");
            }
            ok2Insert = false;
        }
        i++;
    }
    file.close();
    TableReload();
    SumTedad();
    ui->tableView->scrollToBottom();
}


void MainWindow::on_SearchEdit_textChanged(const QString &arg1)
{
    TableReload();
}


void MainWindow::on_PrintCheque_triggered()
{
    ChequePrintDialog *chequeprint = new ChequePrintDialog(ui->ErsalName->text(),ui->ErsalSharh->text());
    chequeprint->show();
}

