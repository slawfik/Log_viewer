#ifndef STATISTIC_MSG_PARSER_H
#define STATISTIC_MSG_PARSER_H

#include "statictic_msg.h"
#include <vector>

using namespace std;

class statistic_msg_parser
{
public:
    bool msgVector_is_full();
    bool run_parser(QString filepath);
    bool setup_calc_month_MSG();
    vector<statictic_msg*>& get_msg_vector();

    statistic_msg_parser();
    ~statistic_msg_parser(){
        clear_vector();
        qDebug() << "~statistic_msg_parser";
    }

private:
     vector<statictic_msg*> msg_vector;
     QFile read_file;
     int modus_data[5][24];

     void set_modus_data(const unsigned int mod_index,int vall);
     void calc_modus(int* modus);
     void clear_vector();
};

#endif // STATISTIC_MSG_PARSER_H
