#ifndef MESAGE_H
#define MESAGE_H

#include <iostream>
#include "definition.h"

using namespace std;

class Mesage
{
private:
    string s_time;
    string s_flag;
    string s_priority;
    string s_body;
    string s_date;
    size_t body_start;
    int prior;
    int date;           //do buducna pre sort
    string s_tele;
    string new_line;

    string get_page_name(const int page_ID);
    void set_string_date(size_t start_date_poz);
    void set_string_tele(size_t start_tele_poz);
    void set_string_flag(char c_flag);
    void set_string_time(int i_time,bool sec_format);
    void set_string_priority(unsigned char c_priority);
    void set_body(unsigned char c_priority,char BH,char BL);

    void parse_system_type(char BH,char BL);
    void parse_thread_type(char BH,char BL);
    void parse_device_type(char BH,char BL);
    void parse_page_type(char BH,char BL);
    void parse_button_type(char BH,char BL);

    int convert_param(unsigned char BH,unsigned char BL);

public:
    //ifstream read;

    Mesage(string pa_new_line);
    string getS_tele()  {return s_tele;}
    string getS_date()  {return s_date;}
    string getS_time()  {return s_time;}
    string getS_flag()  {return s_flag;}
    string getS_priority()  {return s_priority;}
    string getS_body()  {return s_body;}
    int getPriority()   {return prior;}
    bool p_openFile();
    void set_FileName(string pa_filename);
    void set_newline(string pa_new_line);
    void pars_flag();
    void parser_execute();
    virtual ~Mesage();
};

#endif // MESAGE_H
