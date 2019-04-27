#include "mesage.h"

Mesage::Mesage(string pa_new_line)
{
    new_line = pa_new_line;
    this->parser_execute();
}

void Mesage::set_newline(string pa_new_line)
{
    new_line = pa_new_line;
}

void Mesage::parser_execute() {
    string dBodka = ":";
    size_t poz;
    char c_flag;
    unsigned char c_priority;
    int i_time;

    poz = new_line.find(dBodka);
    i_time = atoi(new_line.c_str());

    c_flag = new_line[poz-1];
    c_priority = (unsigned char)new_line[poz+1];
    body_start = poz + 2;

    set_string_time(i_time,false);
    set_string_flag(c_flag);
    set_string_priority(c_priority);
    set_body(c_priority,new_line[body_start],new_line[body_start+1]);
    poz = 0;
}

void Mesage::set_string_time(int i_time,bool sec_format) {
    int min,hod;
    char buffer[255];
    if(sec_format)  {

    }   else {//min format
        hod = i_time/60;
        min = i_time%60;
        if(hod < 10 && min < 10)    {
            sprintf(buffer,"0%d:0%d:00",hod,min);
        } else if(hod < 10) {
            sprintf(buffer,"0%d:%d:00",hod,min);
        } else if(min < 10) {
            sprintf(buffer,"%d:0%d:00",hod,min);
        } else {
            sprintf(buffer,"%d:%d:00",hod,min);
        }
        s_time = buffer;
    }
}

void Mesage::set_body(unsigned char c_priority,char BH,char BL) {
    int priority = c_priority;
    s_body = "";
    switch (priority)
    {
        case 32:
            parse_system_type(BH, BL);
            break;
        case 33:
            parse_thread_type(BH, BL);
            break;
        case 64:
            parse_device_type(BH, BL);
            break;
        case 65:
            parse_page_type(BH, BL);
            break;
        case 66:
            parse_button_type(BH, BL);
            break;
        case 128:
        break;
        case 129:
        break;
        default:
        break;
    }
}

void Mesage::parse_system_type(char BH,char BL) {
    char buffer[200];
    int pp = 0;
    pp = (BH<<8);
    pp += BL;
    if(pp == S_DEFAULT) {
        sprintf(buffer,"%s parameter s ID: %d  dosiahol hodnotu: %d",msg_system_type[0].c_str(),
                convert_param(new_line[body_start+2],new_line[body_start+3]),
                convert_param(new_line[body_start+4],new_line[body_start+5]));
        s_body = buffer;
    }   else {
        s_body = "NEZNÁME!  ";
    }
}

void Mesage::parse_button_type(char BH,char BL) {
    char buffer[200];
    int pp = 0;
    pp = (BH<<8);
    pp += BL;
    if(pp == B_DEFAULT) {
            sprintf(buffer,"%s chanel port: %d chanel code %d.",msg_button_type[0].c_str(),
                convert_param(new_line[body_start+2],new_line[body_start+3]),
                convert_param(new_line[body_start+4],new_line[body_start+5]));
            s_body = buffer;
    } else {
        s_body = "NEZNÁME";
    }
}

void Mesage::parse_thread_type(char BH,char BL) {
    char buffer[200];
    int pp = 0;
    pp = (BH<<8);
    pp += BL;
    if(pp == PT) {
        sprintf(buffer,"%s s ID: %d %s.",msg_thread_type[0].c_str(),
                convert_param(new_line[body_start+2],new_line[body_start+3]),
                ((new_line[body_start + 5] == 107) ? " sa vynútene stoplo" : ((new_line[body_start + 5] == 48) ? " Štartuje" : " končí­")));
        s_body = buffer;
    } else if(pp == TM) {
        sprintf(buffer,"%s.",msg_thread_type[1].c_str());
    } else {
        s_body = "NEZNÁME";
    }
}

void Mesage::parse_page_type(char BH,char BL)  {
    char buffer[200];
    int pp = 0;
    pp = (BH<<8);
    pp += BL;
    switch (pp) {
        case AP:
            sprintf(buffer,"%s s ID: %d sa %d swapla.",msg_page_type[0].c_str(),
                convert_param(new_line[body_start+2],new_line[body_start+3]),
                new_line[body_start+5]);
            s_body = buffer;
            break;
        case MP:
            sprintf(buffer,"%s s ID: %d %s",msg_page_type[1].c_str(),
                convert_param(new_line[body_start +2],new_line[body_start+3]),
                ((new_line[body_start+ 5] == 48) ? " sa vypla" : " sa zapla"));
            s_body = buffer;
            break;
        case PP:
            sprintf(buffer,"%s s ID: %d %s",msg_page_type[2].c_str(),
                convert_param(new_line[body_start +2],new_line[body_start+3]),
                ((new_line[body_start+ 5] == 48) ? " sa vypla" : " sa zapla"));
            s_body = buffer;
            break;
    }
}

void Mesage::parse_device_type(char BH,char BL) {
    //AMX = 0x3030, CISCO1 = 0x3031, CISCO2 = 0x3032, MATICA1 = 0x3033
    int prior[MSG_DEV_TYPE_COUNT] = {0x3030,0x3031,0x3032,0x3033,0x3034,0x3035,0x3036,0x3037,
                    0x3038,0x3039,0x3130,0x3131,0x3132,0x3133,0x3134,0x3135,
                    0x3136,0x3137,0x3138,0x3139,0x3230,0x3231};
    int pp = 0;
    char buffer[200];
    pp = (BH<<8);
    pp += BL;
    for(int i = 0;i<MSG_DEV_TYPE_COUNT;i++){
        if(pp == prior[i]){
            sprintf(buffer,"%s parameter s ID: %d dosiahol hodnotu: %d.",msg_dev_type[i].c_str(),
                    convert_param(new_line[body_start+2],new_line[body_start+3]),
                    convert_param(new_line[body_start+4],new_line[body_start+5]));
                    s_body = buffer;
        } else {
            s_body = "NEZNÁME";
        }
    }
}

void Mesage::set_string_flag(char c_flag) {
    switch (c_flag)
    {
    case 'I':
        s_flag = " [Informácia]";
        break;
    case 'W':
        s_flag = " [Výstraha]";
        break;
    case 'E':
        s_flag = " [Chyba]";
        break;
    default:
        s_flag = " [N/A]";
        break;
    }
}

void Mesage::set_string_priority(unsigned char c_priority)   {
    if(c_priority < P_LOW)  {
        if(c_priority < P_MEDIUM)   {
            s_priority = msg_type_high[c_priority-32];
            prior = 3;
        }   else {
            s_priority = msg_type_medium[c_priority-64].c_str();
            prior = 2;
        }
    }   else {
        s_priority = msg_type_low[c_priority-128];
        prior = 1;
    }
}

/*bool Mesage::p_openFile()   {
    read.open(fileName);
    return read.is_open();
}

void Mesage::set_FileName(string pa_filename){
    fileName = pa_filename;
}*/

int Mesage::convert_param(char BH, char BL) {
    return ((BL - 32) + ((BH - 32) * 224));
}
