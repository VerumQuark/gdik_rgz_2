#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // QScrollBar* bar = ui->textEdit->horizontalScrollBar();
    //bar->setValue(bar->minimum());
}

MainWindow::~MainWindow() {
    delete ui;
}

QString boolStr(bool b) {
    return b ? "true" : "false";
}

void MainWindow::on_pushButton_clicked() {
    QString fileName = QFileDialog::getOpenFileName(this, tr("Upload Image"), "", "*.jpg");

    //QString fileName = "../rgz2/img/tree";        // OLD FILE NAME
    QImage img;
    bool success = img.load(fileName, "JPG" );    //file format
    int step;

    QFont font("MyFont");
    font.setPointSize(2);
    font.setStyleHint(QFont::TypeWriter);
    font.setLetterSpacing (QFont::AbsoluteSpacing,1);

    QString art;

    if (img.height() < 512 || img.width() < 512)
        step = 1;
    else if (img.height() <= 1024 || img.width() < 1024)
        step = 4;
    else if (img.height() <= 2048 || img.width() <= 2048)
        step = 6;
    else
        step = 8;
    for (int i = 0; i < img.height(); i += step) {
        for (int j = 0; j < img.width(); j += step) {

            int sumPB = 0;  // sumPB = sum of area pixel brightness
            for(int y = i; y < i+step; y++){
                for(int x = j; x < j+step; x++){
                    sumPB += img.pixelColor(x,y).value();
                }
            }
            sumPB /= step * step;

            if (sumPB >= 255)
                art+=' ';         // space
            else if( sumPB > 230)
                art+=':';         //:
            else if( sumPB > 220) 
                art+=';';         //;
            else if( sumPB > 190) 
                art+='/';         // /
            else if( sumPB > 160)
                art+='[';         // [
            else if (sumPB > 140)
                art+='=';         // =
            else if (sumPB > 125)
                art+='a';         // a
            else if (sumPB > 80)
                art+='$';         // $
            else if (sumPB > 60)
                art+='&';         // &
            else if (sumPB > 40)
                art+='%';         // %
            else if (sumPB >= 0)
                art+='@';         // @
        }
        art+='\n';
    }

        QLabel* label = ui->label;
        label->setFont(font);
        label->setText(art);

}
