#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QScrollBar* bar = ui->textEdit->horizontalScrollBar();
    //bar->setValue(bar->minimum());
}

MainWindow::~MainWindow() {
    delete ui;
}

QString boolStr(bool b) {
    return b ? "true" : "false";
}

void MainWindow::printStr(QString s) {
    ui->textEdit->insertPlainText(s);
}

void MainWindow::on_pushButton_clicked() {
    QString fileName = QFileDialog::getOpenFileName(this, tr("Upload Image"), "", "*.jpg");

    //QString fileName = "../rgz2/img/tree";        // OLD FILE NAME
    QImage img;
    bool success = img.load(fileName, "JPG" );    //file format
    int step;

    QFont font("MyFont");
    /*if (img.height() <= 512 || img.width() <= 512)
        font.setPointSize(2);
    else font.setPointSize(1); // NICHEGO KROME 2 NE RABOTAET!!!!
    */
    font.setPointSize(2);
    font.setStyleHint(QFont::TypeWriter);
    font.setLetterSpacing (QFont::AbsoluteSpacing,1);
    ui->textEdit->setCurrentFont(font);
    ui->textEdit->insertPlainText("Image load status:"+boolStr(success)+"\n");

    if (img.height() < 512 || img.width() < 512)
        step = 1;
    else if (img.height() >= 512 || img.width() > 512)
        step = 2;
    else if (img.height() <= 2048 || img.width() <= 2048)
        step = 4;
    else
        step = 8;
    for (int i = 0; i < img.height(); i += step) {
        for (int j = 0; j < img.width(); j += step) {
            int pB = img.pixelColor(j,i).value(); // pB = pixel brightness
            if (pB >= 255)
                printStr(" "); // space
            else if( pB > 230)
                printStr(":"); //:
            else if( pB > 220)
                printStr(";"); //;
            else if( pB > 190)
                printStr("/"); // /
            else if( pB > 160)
                printStr("["); // [
            else if (pB > 140)
                printStr("="); // =
            else if (pB > 125)
                printStr("a"); // a
            else if (pB > 80)
                printStr("$"); // $
            else if (pB > 60)
                printStr("&"); // &
            else if (pB > 40)
                printStr("%"); // %
            else if (pB >= 0)
                printStr("@"); // @
        }
        printStr("\n");
    }
}
