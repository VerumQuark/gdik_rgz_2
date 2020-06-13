#include <QCoreApplication>
#include <QImage>
#include <QString>

#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QString fileName = "../smallSqTest";
    QImage img;

    bool success = img.load(fileName, "PNG" );

    cout << "Image load status: " << boolalpha << success << endl;

    for (int i = 0; i < img.height(); i++){
        for (int j = 0; j < img.width(); j++){
            int pB = img.pixelColor(j,i).value(); // pB = pixel britness

            if (pB > 255){
                cout << '.';
            } else if( pB > 180){
                cout << ',';
            } else if (pB > 125){
                cout << ':';
            } else if (pB > 100){
                cout << ';';
            } else if (pB > 40){
                cout << '%';
            } else if (pB > 20){
                cout << '#';
            }

        }
        cout << endl;
    }

    return a.exec();
}
