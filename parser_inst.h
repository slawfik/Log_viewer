#ifndef PARSER_INST_H
#define PARSER_INST_H

#include <fstream>
#include <stdio.h>
#include "mesage.h"

class parser_inst
{
private:
   string filename;
   string new_line;
   ifstream read;
   int aloc_instance;
   int message_count;

public:
   Mesage* _message[MAX_COUNT_LOG_MESSAGE];

    parser_inst();
    int getMessage_count() const {return message_count;}
    void pars_message(string pa_filename);
};

//extern parser_inst parser_base_inst;

#endif // PARSER_INST_H
