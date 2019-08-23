#ifndef STATICTIC_MSG_H
#define STATICTIC_MSG_H

#include <QDate>
#include <QTextStream>
#include <QFile>
#include <QtDebug>

#define LITLE15BUFF 15

enum CodeMSG
{
    E2=6950,
    EA=6965,
    EB=6966,
    A0=6548,
    A2=6550,
    AA=6565,
    D2=6850,
    DA=6865,
    CA=6765,
    F2=7050,
    FA=7065
};

enum Type_Message
{
    BAD_MSG,
    DAY_MSG,
    MONTH_MSG,
    ACTION_MSG,
    DAY_MSG_NEW,
};

class statictic_msg
{
public:
    Type_Message type;

    statictic_msg();
    statictic_msg(const QString subject);
    void set_dateTime(const QString timeDate);
    void set_emailBody(const QString body);
    //void calc_modus(int &array,const int size);
    void calc_AritPriemer(const int pocet);
    void set_Min(const int index,const int vall);
    void set_Max(const int index,const int vall);

    int get_teleNumber()        {return tele_number;}
    QString get_popisCodu()     {return popis_codu;}
    QDateTime get_dateTime()    {return date_time;}
    int getTolat_time(const int i)    {return total_Time[i];}
    int getMax_time(const int i)      {return max_Time[i];}
    int getMin_time(const int i)      {return min_Time[i];}
    int getArit_Priemer(const int i)  {return arit_Priemer[i];}
    int getCouter(const int i)        {return couter[i];}
    int getModus(const int i)         {return modus[i];}
    int getBoot_Ernno(const int i)    {return boot_Ernno[i];}
    void sum_Boot_Erno(const int index,const int vall)  {boot_Ernno[index] += vall;}
    void set_Tele(const int tele)                       {tele_number = tele;}
    void sum_Total(const int index,const int vall)      {total_Time[index] += vall;}
    void sum_Count(const int index,const int vall)      {couter[index] += vall;}
    void set_AritPriem(const int index,const int vall)  {arit_Priemer[index] = vall;}
    void set_Modus(const int index,const int vall)      {modus[index] = vall;}
private:
    QDateTime date_time;
    QString email_body;
    int tele_number;
    int cod;
    QChar code[2];
    QString popis_codu;

    int total_Time[5];      //0
    int max_Time[5];        //1
    int min_Time[5];        //2
    int arit_Priemer[5];    //3
    int couter[5];          //4
    int modus[5];           //5
    int boot_Ernno[2];

    void parse_27a28_day_statistic(const int coma_num);
    void parse_13_day_statistic();
    void parse_1_day_statistic();
    void parseCode_actionMSG();
    int get_Month_Number(const QString mont);
    QTime getTimeFromSec();
};

#endif // STATICTIC_MSG_H
