#ifndef PARSER_INST_H
#define PARSER_INST_H

#include <fstream>
#include <stdio.h>
#include <vector>
#include "mesage.h"

class parser_inst
{
    private:
       string filename;
       string new_line;
       ifstream read;
       int message_count;

    public:
        vector<Mesage *> * arr;
        parser_inst();
        int getMessage_count() const {return message_count;}
        void pars_message(string pa_filename);
        inline virtual ~parser_inst()
        {
            /*for (std::vector<Mesage *>::iterator it = arr->begin() ; it != arr->end(); ++it)
                it.operator*()->getS_body();*/
            if(this->arr != nullptr){
                for(size_t i =0;i<this->arr->size();i++){
                    delete this->arr->operator[](i);
                }
                this->arr->clear();
            }

        }

};

//extern parser_inst parser_base_inst;

#endif // PARSER_INST_H
