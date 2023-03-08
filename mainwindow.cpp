#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qdatejalali.h"
#include "numberformatdelegate.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Shamsi Calender
    QDateJalali Jalali;
    QDateTime date =QDateTime::currentDateTime();
    QStringList shamsi=  Jalali.ToShamsi(  date.toString("yyyy"), date.toString("MM"),date.toString("dd"));
    QString JalailDate =shamsi.at(0)+"/"+shamsi.at(1)+"/"+shamsi.at(2);
    ui->TarixShamsi->setText("تاریخ امروز: "+JalailDate);

    ui->ErsalSeri->setValidator( new QIntValidator);
    ui->ErsalSheba->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9]*")));
    ui->Sheba->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9]*")));
    ui->Shenaseh->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9]*")));

    QDir *datadir = new QDir();
    if (!datadir->exists("data")){
        datadir->mkdir("data");
            }
    if (!QFile::exists("data/bmipaya.db")){
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName("data/bmipaya.db");
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
   model->setQuery("SELECT sheba, shenaseh, name, mablagh, sharh FROM paya");
   model->setHeaderData(0, Qt::Horizontal, tr("شماره شبا"));
   model->setHeaderData(1, Qt::Horizontal, tr("شناسه واریز"));
   model->setHeaderData(2, Qt::Horizontal, tr("نام و نام خانوادگی"));
   model->setHeaderData(3, Qt::Horizontal, tr("مبلغ"));
   model->setHeaderData(4, Qt::Horizontal, tr("شرح"));
   ui->tableView->setModel(model);
   ui->tableView->setItemDelegateForColumn(3, new NumberFormatDelegate(this));
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


void MainWindow::on_RestoreButton_clicked()
{
    if (ShebaCheck(ui->ErsalSheba->text())){
        QMessageBox msgBox; msgBox.setText("Sheba ok."); msgBox.exec();
    }
    else{
        QMessageBox msgBox; msgBox.setText("Sheba Error."); msgBox.exec();
    }
}


void MainWindow::on_PrintdButton_clicked()
{
    if (ErsalSehv()){
        QPrinter printer;
        //printer.setPageOrientation(QPageLayout::Landscape);
        printer.setPageSize(QPageSize::A4);
        printer.setFullPage(true);
        //printer.setOutputFormat(QPrinter::PdfFormat);
        //printer.setOutputFileName("nonwritable.pdf");
        QPrintPreviewDialog *printPreview = new QPrintPreviewDialog(&printer);
        connect(printPreview, SIGNAL(paintRequested(QPrinter*)), this, SLOT(printD(QPrinter*)));
        printPreview->setWindowTitle("Preview Dialog");
        Qt::WindowFlags flags(Qt::WindowTitleHint);
        printPreview->setWindowFlags(flags);
        //printPreview->setContentsMargins(10,10,10,10);
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
        QPrinter printer;
        printer.setPageOrientation(QPageLayout::Landscape);
        printer.setPageSize(QPageSize::A4);
        printer.setFullPage(true);
        //printer.setOutputFormat(QPrinter::PdfFormat);
        //printer.setOutputFileName("nonwritable.pdf");
        QPrintPreviewDialog *printPreview = new QPrintPreviewDialog(&printer);
        connect(printPreview, SIGNAL(paintRequested(QPrinter*)), this, SLOT(print(QPrinter*)));
        printPreview->setWindowTitle("Preview Dialog");
        Qt::WindowFlags flags(Qt::WindowTitleHint);
        printPreview->setWindowFlags(flags);
        //printPreview->setContentsMargins(10,10,10,10);
        printPreview->exec();
    }
}

void MainWindow::on_Mablagh_textEdited(const QString &arg1)
{
    QLocale::setDefault(QLocale::English);
    QLocale ss;
    QString str;
    str = ss.toString(ui->Mablagh->text().replace(",","").toLong());
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
                    ui->ErsalSheba->setText(query.value(1).toString());
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
    query.exec("SELECT * FROM paya");

    txt="<html width=\"100%\"><head><style>body {direction: rtl;} table, td {border: 1px solid black; padding: 5px; border-collapse: collapse;}</style></head>"
         "<body><div dir=\"rtl\"><h3 align=\"center\"> لیست واریزی پایای گروهی "+ui->ErsalName->text()+" بابت "+ui->ErsalSharh->text()+"</h3>"
         "<table width=\"100%\"><tr><td>شرح</td><td>مبلغ</td><td>نام و نام خانوادگی</td><td>شناسه واریز</td><td>شماره شبا</td><td>ردیف</td></tr>";
    while (query.next()) {
        txt += "<tr><td>"+query.value(5).toString()+"</td><td>"+InsertComma(query.value(4).toString())+"</td><td>"+query.value(3).toString()+"</td><td>"+query.value(2).toString()+"</td><td>IR"+query.value(1).toString()+"</td><td>"+query.value(0).toString()+"</td></tr>";
    }
    txt += "<tr><td colspan=\"2\">"+InsertComma(sum)+"</td><td colspan=\"3\">&nbsp;</td><td>جمع</td></tr>";
    txt += "</table><table width=\"100%\"><tr align=\"left\"><th>مهر و امضاء بانک</th><th>مهر و امضاء امضاداران مجاز</th><tr></table></div></body></html>";
    QTextDocument document;
    document.setDocumentMargin(0.1);
        document.setHtml(txt);
        document.print(printer);
}
void MainWindow::printD(QPrinter *printer)
{
    QString xmlfile;
    xmlfile = InsertZero(ui->ErsalSeri->text(),9);
    xmlfile = "IR" + ui->ErsalSheba->text() + xmlfile + ".ccti";

    QString txt;
    QSqlQuery query;
    QDateJalali Jalali;
    QDateTime date =QDateTime::currentDateTime();
    QStringList shamsi=  Jalali.ToShamsi(  date.toString("yyyy"), date.toString("MM"),date.toString("dd"));
    QString JalailDate =shamsi.at(0)+"/"+shamsi.at(1)+"/"+shamsi.at(2);

    query.exec("SELECT * FROM paya");

    txt="<html width=\"100%\"><head><style>body {direction: rtl;} table, td {border: 1px solid black; padding: 5px; border-collapse: collapse;}</style></head>"
         "<body><div dir=\"rtl\"><div>تاریخ: "+JalailDate+"</div><div>شماره: </div>"
         "<h3 align = \"center\">‫دستور‬‫پرداخت‬ ‫سامانه‬ ‫پایاپای‬ ‫الکترونیکی - پایا‬</h3>"
            "<div align = \"center\">‫بانک ملی ایران شعبه &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; کد شعبه ‪‬‬</div>"
            "<br><div>اینجانب /شرکت <b>aaaaaa</b> به شماره ملی /شناسه ملی <b>aaaaaaaaa</b> </div>"
            "<div>آدرس و تلفن: </div><br>"
            "<div>بدینوسیله از بانک درخواست می‌کنیم که در تاریخ <b>"+JalailDate+"</b> جمعا مبلغ به عدد <b>"+InsertComma(sum)+"</b> و به حروف <b>22222222222</b> مطابق با جزئیات مندرج در فایل پیوست از محل حساب مبداء به حسابهای مقصد انتقال دهد.</div>"
         "<br><table width=\"100%\"><tr><td>نام فایل: "+xmlfile+"<br>طول فایل به بایت: </td><td>مشخصات فایل پیوست</td></tr></table>"
            "<p>‫و‬‫بدینوسیله‬ ‫تائید‬ ‫می‬ ‫نمایم‬ ‫که‬ ‫با‬ ‫ارائه‬ ‫ای‬‫ن ‬‫دستور‬ ‫پرداخت‬ ‫و‬ ‫فا‫ی‬‫ل‬‫ پ‬‫ی‬‫وست‬‫ آن‬ ‫به‬ ‫بانک‬ ‫مسئول‬‫ی‬‫ت‬‫ صحت‬ ‫مندرجات ‬‫آن‬ ‫بر‬ ‫عهده‬ ‫ای‬‫نجانب‬‫‪/‬‬‫این‬ ‫شرکت‬ ‫بوده‬ ‫و‬ ‫کل‬‫ی‬‫ه‬‫ شرا‫ی‬‫ط ‬‫مندرج‬ ‫در‬ ‫ظهر‬ ‫دستور‬ ‫پرداخت‬ ‫و‬ ‫همچن‬‫ی‬‫ن‬ ‫پرداخت‬‫ کارمزد‬ ‫به‬ ‫مبلغ‬ &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;‬ ‫ر‬‫ی‬‫ال ‬‫به‬ ‫بانک‬ ‫را‬ ‫م‬‫ی‬‫‌پذ‬‫ی‬‫رم‬‫‪.‬‬</p>"
            "<br><br><br><table width=\"100%\"><tr align=\"left\"><th>مهر و امضاء بانک</th><th>مهر و امضاء امضاداران مجاز</th><tr></table>"
            "</div></body></html>";
    QTextDocument document;
    document.setDocumentMargin(0.1);
        document.setHtml(txt);
        document.print(printer);
}

