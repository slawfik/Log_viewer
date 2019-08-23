#include "statictic_msg.h"

statictic_msg::statictic_msg(){
    memset(total_Time,0,sizeof (int)*5);
    memset(min_Time,0,sizeof (int)*5);
    memset(max_Time,0,sizeof (int)*5);
    memset(modus,0,sizeof (int)*5);
    memset(couter,0,sizeof (int)*5);
    memset(arit_Priemer,0,sizeof (int)*5);
    memset(boot_Ernno,0,sizeof (int)*2);
}

statictic_msg::statictic_msg(const QString subject)
{
    memset(total_Time,0,sizeof (int)*5);
    memset(min_Time,0,sizeof (int)*5);
    memset(max_Time,0,sizeof (int)*5);
    memset(modus,0,sizeof (int)*5);
    memset(couter,0,sizeof (int)*5);
    memset(arit_Priemer,0,sizeof (int)*5);
    try {
        tele_number = subject.split(" ")[1].toInt();
    } catch (...) {
        qDebug() << "Error conwert tele_number!";
    }
}

void statictic_msg::set_dateTime(const QString timeDate){
    int d, m, r ,hod ,min;
    QString time;
    try {
        d = timeDate.split(" ")[1].toInt();
        m = get_Month_Number(timeDate.split(" ")[2]);
        r = timeDate.split(" ")[3].toInt();
        time = timeDate.split(" ")[4];
        hod = time.split(":")[0].toInt();
        min = time.split(":")[1].toInt();
        date_time.setTime(QTime(hod,min,0));
        date_time.setDate(QDate(r,m,d));
    } catch (...) {
        qDebug() << "Error conwert date & time!";
    }
    //qDebug() << "Datum: " << QString::number(d) << " " << QString::number(m) << " " << QString::number(r);
    //qDebug() << "DATETIME_OBJ: " << date_time.toString();
}

void statictic_msg::set_emailBody(const QString body){
    email_body = body;
    int bodky = email_body.count('.');
    qDebug() << "tele-" << QString::number(tele_number) << " bodky: " << QString::number(bodky) << "\nMSG: " << body;
    switch (bodky) {
        case 27:    //jednoriadkova aj 5 riadkov po 4 bodky
            this->parse_27a28_day_statistic(bodky);
            break;

        case 28:    //4 riadkov po 4 a 1 po 5 bodiek
            this->parse_27a28_day_statistic(bodky);
            break;

        case 1:     //tele-3 prazdna denna | akcia | log
            this->parse_1_day_statistic();
            break;

        case 13:     //new tele-3 plna dena
            this->parse_13_day_statistic();
            break;

        default:
            email_body = "NA";
            type = BAD_MSG;
            break;
    }
}

int statictic_msg::get_Month_Number(const QString mont){
    if(mont == "Jan"){
        return 1;
    } else if(mont == "Feb"){
        return  2;
    } else if(mont == "Mar"){
        return 3;
    } else if(mont == "Apr"){
        return 4;
    } else if(mont == "Maj"){
        return 5;
    } else if(mont == "Jun"){
        return 6;
    } else if(mont == "Jul"){
        return 7;
    } else if(mont == "Aug"){
        return 8;
    } else if(mont == "Sep"){
        return 9;
    } else if(mont == "Oct"){
        return 10;
    } else if(mont == "Nov"){
        return 11;
    } else {
        return 12;
    }
}

void statictic_msg::parse_13_day_statistic(){
    try {
        for(int i = 1;i<2;i++){
            total_Time[i] = email_body.split(".")[i].toInt();
            max_Time[i] = email_body.split(".")[i+2].toInt();
            min_Time[i] = (email_body.split(".")[i+4].toInt() == 65535 ? 0 : email_body.split(".")[i+4].toInt());
            arit_Priemer[i] = email_body.split(".")[i+6].toInt();
            couter[i] = email_body.split(".")[i+8].toInt();
            boot_Ernno[i] = email_body.split(".")[i+10].toInt();
        }
        type = DAY_MSG_NEW;
    } catch (...) {
        type = BAD_MSG;
        qDebug() << "Error conwert email_data parse_13_day_statistic!";
    }
}

void statictic_msg::parse_27a28_day_statistic(const int coma_num){
    int i;
    try {
        if (email_body.begin()->toLatin1() == '.' || coma_num == 28){
            for(i = 1;i<6;i++){
                total_Time[i-1] = email_body.split(".")[i].toInt();
                max_Time[i-1] = email_body.split(".")[i+5].toInt();
                min_Time[i-1] = (email_body.split(".")[i+10].toInt() == 65535 ? 0 : email_body.split(".")[i+10].toInt());
                arit_Priemer[i-1] = email_body.split(".")[i+15].toInt();
                couter[i-1] = email_body.split(".")[i+20].toInt();
                if((i-1)<2){
                    boot_Ernno[i-1] = email_body.split(".")[i+25].toInt();
                }
            }
        } else {
            for(i = 0;i<5;i++){
                total_Time[i] = email_body.split(".")[i].toInt();
                max_Time[i] = email_body.split(".")[i+5].toInt();
                min_Time[i] = (email_body.split(".")[i+10].toInt() == 65535 ? 0 : email_body.split(".")[i+10].toInt());
                arit_Priemer[i] = email_body.split(".")[i+15].toInt();
                couter[i] = email_body.split(".")[i+20].toInt();
                if(i<2){
                    boot_Ernno[i] = email_body.split(".")[i+25].toInt();
                }
            }
        }
        type = DAY_MSG;
    } catch (...) {
        type = BAD_MSG;
        qDebug() << "Error conwert email_data parse_27a28_day_statistic section: !" << QString::number(coma_num);
    }
}

void statictic_msg::parse_1_day_statistic(){
    int len = email_body.length();
    if(len < 7)  //tele-3 day msg "PRÁZDNA"
    {
        type = DAY_MSG_NEW;
        for(int i = 1;i<5;i++){
            total_Time[i] = 0;
            max_Time[i] = 0;
            min_Time[i] =0;
            arit_Priemer[i] = 0;
            couter[i] = 0;
            if(i<2){
                boot_Ernno[i] = 0;
            }
        }
        qDebug() << "denná_msg tele03: " <<  email_body;
    } else if (len < 16)
    {
        type = ACTION_MSG;
        date_time.setTime(getTimeFromSec());
        code[0] = email_body.split(".")[1].operator[](0);
        code[1] = email_body.split(".")[1].operator[](1);
        parseCode_actionMSG();
        //qDebug() << "akcia: " <<  email_body << "time" << date_time.time().toString();
    } else
    {
        type = BAD_MSG;
        //qDebug() << "statistika: " <<  email_body;
    }
}

QTime statictic_msg::getTimeFromSec(){
    int min = email_body.split(".")[0].toInt();
    return QTime(min/60,min%60,0);
}

void statictic_msg::parseCode_actionMSG() {
    int cod = code[0].toLatin1() * 100;
    cod += code[1].toLatin1();
    //qDebug() << QString::number(cod) << " ____";
    switch(cod)    {
        case E2:
            popis_codu = "Nastavenia";
            break;
        case  EA:
            popis_codu = "KK";
            break;
        case  EB:
            popis_codu = "Zoznam";
            break;
        case  A0:
            popis_codu = "Boot done";
            break;
        case  A2:
            popis_codu = "System zap.";
            break;
        case  AA:
            popis_codu = "System vyp.";
            break;
        case  D2:
            popis_codu = QString::fromLatin1("Prez. mód");
            break;
        case  DA:
            popis_codu = QString::fromLatin1("Viko mód");
            break;
        case  CA:
            popis_codu = QString::fromLatin1("Menu mód");
            break;
        case  F2:
            popis_codu = "VGA zap.";
            break;
        case FA:
            popis_codu = "VGA vyp.";
            break;
        default:
            popis_codu = "ERRNO_" + QString::fromRawData(code,2) +"\0";
            break;
    }
}

void statictic_msg::calc_AritPriemer(const int pocet){
    for(int i = 0; i<5 ;i++){
        arit_Priemer[i] = total_Time[i]/pocet;
    }
}

void statictic_msg::set_Min(const int index,const int vall)        {
    if(min_Time[index] < vall){
        min_Time[index] = vall;
    }
}
void statictic_msg::set_Max(const int index,const int vall){
    if(max_Time[index] < vall){
        max_Time[index] = vall;
    }
}
