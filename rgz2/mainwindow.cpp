#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
<<<<<<< Updated upstream
    QScrollBar* bar = ui->textEdit->horizontalScrollBar();
    //bar->setValue(bar->minimum());
=======
>>>>>>> Stashed changes
}

MainWindow::~MainWindow() {
    delete ui;
}

int setStep(int h, int w) {
    if (h < 512 || w < 512)
        return 1;
    else if (h <= 1024 || w < 1024)
        return 4;
    else if (h <= 2048 || w <= 2048)
        return 6;
    else return 8;
}

<<<<<<< Updated upstream
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
=======
char getChar (int pb) {
    if (pb >= 255)
        return ' ';         // space
    if (pb > 230)
        return ':';         //:
    if (pb > 220)
        return ';';         //;
    if (pb > 190)
        return '/';         // /
    if (pb > 160)
        return '[';         // [
    if (pb > 140)
        return '=';         // =
    if (pb > 125)
        return 'a';         // a
    if (pb > 80)
        return '$';         // $
    if (pb > 60)
        return '&';         // &
    if (pb > 40)
        return '%';         // %
    return '@';             // @
}

QString getArt(QImage img) {
    QString art;
    int step=setStep(img.height(),img.width());
    for (int i = 0; i < img.height(); i += step) {
        for (int j = 0; j < img.width(); j += step) {
            int sumPB = 0;  // sumPB = sum of area pixel brightness
            for (int y = i; y < i+step; y++) {
                for (int x = j; x < j+step; x++) {
                    sumPB += img.pixelColor(x,y).value();
                    if(x > img.width())
                        break;
                }
                if (y > img.height())
                    break;
            }
            sumPB /= step * step;
            art+=getChar(sumPB);
>>>>>>> Stashed changes
        }
        printStr("\n");
    }
<<<<<<< Updated upstream
=======
    return art;
}

void MainWindow::on_pushButton_clicked() {
    QString fileName = QFileDialog::getOpenFileName(this, tr("Upload Image"), "", "*.jpg");
    QImage image;
    if (!image.load(fileName, "JPG" ))
        QMessageBox::critical(0,"Error", "Can't upload image");
    QFont font("MyFont");
    font.setPointSize(2);
    font.setStyleHint(QFont::TypeWriter);
    font.setLetterSpacing (QFont::AbsoluteSpacing,1);
    QLabel* label = ui->label;
    label->setAlignment(Qt::AlignLeft);
    label->setFont(font);
    label->setText(getArt(image));
>>>>>>> Stashed changes
}
