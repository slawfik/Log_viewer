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
    size_t body_start;
    int prior;

    string new_line;

    void set_string_flag(char c_flag);
    void set_string_time(int i_time,bool sec_format);
    void set_string_priority(unsigned char c_priority);
    void set_body(unsigned char c_priority,char BH,char BL);

    void parse_system_type(char BH,char BL);
    void parse_thread_type(char BH,char BL);
    void parse_device_type(char BH,char BL);
    void parse_page_type(char BH,char BL);
    void parse_button_type(char BH,char BL);

    int convert_param(char BH, char BL);

public:
    //ifstream read;

    Mesage(string pa_new_line);
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
};

#endif // MESAGE_H
