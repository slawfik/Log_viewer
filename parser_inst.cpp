#include "parser_inst.h"

parser_inst::parser_inst()
{
    message_count = 0;
}

void parser_inst::pars_message(string pa_filename)
{
    filename = pa_filename;
    read.open(filename);
    if(read.is_open())  {
        aloc_instance = message_count;
        message_count = 0;
        while (!read.eof()) {
            getline(read,new_line);
            if(new_line.length() && message_count < MAX_COUNT_LOG_MESSAGE)   {
                if(message_count < aloc_instance) {
                    _message[message_count]->set_newline(new_line);
                    _message[message_count]->parser_execute();
                    message_count++;
                } else  {
                    _message[message_count] = new Mesage(new_line);
                    message_count++;
                }
            }
        }
        read.close();
    }
}

