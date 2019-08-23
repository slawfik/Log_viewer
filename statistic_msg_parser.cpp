#include "statistic_msg_parser.h"

statistic_msg_parser::statistic_msg_parser()
{

}

void statistic_msg_parser::clear_vector(){
    if(msg_vector.size() != 0){
        qDebug() << "clear_vector";
        for(size_t i = 0; i<msg_vector.size();i++){
            delete msg_vector.operator[](i);
        }
        msg_vector.clear();
    }
}

bool statistic_msg_parser::run_parser(QString filepath){
    QString line ,part_line;
    statictic_msg *msg;

    if(msg_vector.size() != 0){
        clear_vector();
    }
    read_file.setFileName(filepath);
    read_file.open(QIODevice::ReadOnly);
    if(read_file.isOpen()){
        QTextStream read(&read_file);
        while (!read.atEnd()) {
            line = read.readLine();
            if(line.operator==("-----------")){
                line = read.readLine();         //subject
                msg = new statictic_msg(line);
                line = read.readLine();         //date
                msg->set_dateTime(line);
                line = read.readLine();         //body "Sm:"
                if(line == "Sm:"){
                    line = "";
                    while(true) {
                        part_line = read.readLine();
                        if (part_line == "Em."){
                            break;
                        } else{
                            int coma = part_line.count('.');
                            if( coma == 4 || coma == 5){
                                part_line += ".";
                            }
                            line += part_line;
                        }
                    }
                    msg->set_emailBody(line);   //end set body
                }
                msg_vector.push_back(msg);
            }
        }

    } else{
        read_file.close();
        return false;
    }
    read_file.close();
    return true;
}

bool statistic_msg_parser::setup_calc_month_MSG(){
    statictic_msg *new_msg[22];
    int count_message;

    for(int i = 0;i<22;i++)
        new_msg[i] = new statictic_msg();

    for(int miestnost = 0;miestnost<22;miestnost++){
        memset(modus_data,0,5*24*sizeof (int));
        new_msg[miestnost]->set_Tele(miestnost+1);
        new_msg[miestnost]->type = MONTH_MSG;
        count_message = 0;

        //iterator cez v?etký správy
        for (vector<statictic_msg*>::iterator it = msg_vector.begin() ; it != msg_vector.end(); ++it){
            //ak je správa denná tak updatuj mesa?nú
            if(it.operator*()->get_teleNumber() == (miestnost+1) && (it.operator*()->type == DAY_MSG || it.operator*()->type == DAY_MSG_NEW)){
                count_message++;
                for(int i = 0; i < 5 ;i++){
                    new_msg[miestnost]->sum_Total(i,it.operator*()->getTolat_time(i));
                    new_msg[miestnost]->set_Max(i,it.operator*()->getMax_time(i));
                    new_msg[miestnost]->set_Min(i,it.operator*()->getMin_time(i));
                    new_msg[miestnost]->sum_Count(i,it.operator*()->getCouter(i));
                    set_modus_data(static_cast<unsigned int>(i),it.operator*()->getTolat_time(i));
                    if(i<2)
                        new_msg[miestnost]->sum_Boot_Erno(i,it.operator*()->getBoot_Ernno(i));
                }
            }
        }
        if(count_message > 0){
            int modus[5] = {0};
            //end ITERATOR dopo?ítaj modus a arit priemer z nahromadených dát!
            new_msg[miestnost]->calc_AritPriemer(count_message);
            calc_modus(modus);
            for(int i =0;i<5;i++)
                new_msg[miestnost]->set_Modus(i,modus[i]);
        }
        //zapísem správu do vectora
        msg_vector.push_back(new_msg[miestnost]);
    }
    return true;
}

void statistic_msg_parser::calc_modus(int* modus){
    int max;
    int index;
    //int duplicita = 0;
    //cez vsetky módy
    for(int i =0;i<5;i++){
        max = 0;
        index = -1;
        for(int j =0;j<24;j++){
            if(modus_data[i][j] > max){
                index = j;
                //duplicita = 0;
            }/* else if(modus_data[i][j] == max){
                duplicita++;
            }*/
        }
        if(index != -1){
            modus[i] = (index+1) * 60;
        } else{
            modus[i] = 0;
        }
    }
}

bool statistic_msg_parser::msgVector_is_full(){
    if(msg_vector.size() > 0){
        return true;
    } else{
        return false;
    }
}

void statistic_msg_parser::set_modus_data(const unsigned int mod_index,int vall){
    if(vall > 1440)
        vall=1439;
    if(!vall)
        return;

    int modulo = vall%60;
    int index = (vall/60);
    if(!modulo){
        modus_data[mod_index][index]++;
    } else {
        modus_data[mod_index][index]++;
    }
}

vector<statictic_msg*>& statistic_msg_parser::get_msg_vector(){
    return msg_vector;
}
