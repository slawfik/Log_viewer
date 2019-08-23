#include "parser_inst.h"
#include "qfile.h"
//#include "QTextCodec"
//#include "QDebug"


parser_inst::parser_inst()
{

    message_count = 0;
    arr = nullptr;
}

void parser_inst::pars_message(string pa_filename)
{
    size_t poz;
    /*//fopen()
    //codecs.open('myfile', 'r', 'iso-8859-1').read()
    QString aa = QString::fromStdString(pa_filename);
    QFile data(aa);
    if (data.open(QFile::ReadOnly | QFile::Truncate)) {
        QTextStream out(&data);
        out.setCodec(QTextCodec::codecForName("Windows-1252"));
        while (!out.atEnd()) {
            QString bb = out.readLine(100);
            QByteArray xx (bb.toLocal8Bit());
            for(int a = 0; a < bb.length(); a++)
            {
                qDebug() <<"data\n"<< xx[a]<<QString::number(xx[a]) << endl;
            }
            qDebug() <<"--------------------------" << endl;
        }
    }*/
    filename = pa_filename;
    if(this->arr != nullptr)
        this->arr->clear();
    arr = new vector<Mesage *>();
    read.open(filename,ios::in | ios::binary);
    //std::basic_ifstream<unsigned char>
    if(read.is_open())  {
        while (!read.eof()) {
            getline(read,new_line);
            //____VALID TEST____
            poz = new_line.find(":");
            if(poz == std::string::npos){
                poz = new_line.find(".");
                if(poz == std::string::npos){
                    //qDebug() << "continue";
                    continue;
                }
            }
            //qDebug() << QString::fromStdString(new_line) << poz+8 << new_line.length();
            if(poz+8 <= new_line.length())   {
                arr->push_back(new Mesage(new_line));
            }
        }
    }
    read.close();

}

