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
    const string dBodka = ":";
    const string bodka = ".";
    bool time_format_sec = false;
    size_t poz;
    char c_flag;
    int i_time;

    poz = new_line.find(dBodka);
    if (poz == std::string::npos){  //logov· spr·va z mailu s bodkou a bez flagu
        poz = new_line.find(bodka);
        time_format_sec = true;
        set_string_date(poz+LEN_LOG_BODY);
        set_string_tele(poz+LEN_LOG_BODY+LEN_LOG_DATE);
    }

    i_time = atoi(new_line.c_str());

    c_flag = new_line[poz-1];
    body_start = poz + 2;

    set_string_time(i_time,time_format_sec);
    set_string_flag(c_flag);
    set_string_priority(static_cast<unsigned char>(new_line[poz+1]));
    set_body(static_cast<unsigned char>(new_line[poz+1]),new_line[body_start],new_line[body_start+1]);
    poz = 0;
}

void Mesage::set_string_date(size_t start_date_poz){
    char buffer[50];
    char datum[9];
    if(new_line.length() > start_date_poz+7){
        new_line.copy(datum,8,start_date_poz);
        date = atoi(datum);
        sprintf(buffer,"%c%c.%c%c.%c%c%c%c",new_line[start_date_poz+6],
                new_line[start_date_poz+7],
                new_line[start_date_poz+4],
                new_line[start_date_poz+5],
                new_line[start_date_poz],
                new_line[start_date_poz+1],
                new_line[start_date_poz+2],
                new_line[start_date_poz+3]);
        s_date = buffer;
    } else{
        s_date = "Bad len log_mesg!";
    }

}

void Mesage::set_string_tele(size_t start_tele_poz){
    char buff[4];
    if(start_tele_poz+3 == new_line.length()){
        new_line.copy(buff,3,start_tele_poz);
        buff[3] = '\0';
        s_tele = buff;
    }   else {
        s_tele = "Bad len log_mesg!";
    }

}

void Mesage::set_string_time(int i_time,bool sec_format) {
    int min,hod,sec;
    int pom;
    char buffer[255];
    char smin[5],shod[5],ssec[5];
    if(sec_format)  {//sec format
        pom = i_time/60;
        hod = pom/60;
        min = pom%60;
        sec = i_time%60;
        sprintf(shod,hod<10 ? "0%d" : "%d",hod);
        sprintf(smin,min<10 ? "0%d" : "%d",min);
        sprintf(ssec,sec<10 ? "0%d" : "%d",sec);
        sprintf(buffer,"%s:%s:%s",shod,smin,ssec);
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
    }
    s_time = buffer;
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
                convert_param(static_cast<unsigned char>(new_line[body_start+2]),static_cast<unsigned char>(new_line[body_start+3])),
                convert_param(static_cast<unsigned char>(new_line[body_start+4]),static_cast<unsigned char>(new_line[body_start+5])));
        s_body = buffer;
    }   else {
        s_body = "NEZNAÅME!  ";
    }
}

void Mesage::parse_button_type(char BH,char BL) {
    char buffer[200];
    int pp = 0;
    pp = (BH<<8);
    pp += BL;
    if(pp == B_DEFAULT) {
            sprintf(buffer,"%s chanel port: %d chanel code %d.",msg_button_type[0].c_str(),
                convert_param(static_cast<unsigned char>(new_line[body_start+2]),static_cast<unsigned char>(new_line[body_start+3])),
                convert_param(static_cast<unsigned char>(new_line[body_start+4]),static_cast<unsigned char>(new_line[body_start+5])));
            s_body = buffer;
    } else {
        s_body = "NEZN√ÅME";
    }
}

void Mesage::parse_thread_type(char BH,char BL) {
    char buffer[200];
    int pp = 0;
    pp = (BH<<8);
    pp += BL;
    if(pp == PT) {
        sprintf(buffer,"%s s ID: %d %s.",msg_thread_type[0].c_str(),
                convert_param(static_cast<unsigned char>(new_line[body_start+2]),static_cast<unsigned char>(new_line[body_start+3])),
                ((new_line[body_start + 5] == 107) ? " sa vynutene stoplo" : ((new_line[body_start + 5] == 48) ? " ≈ tartuje" : " konƒç√≠¬≠")));
        s_body = buffer;
    } else if(pp == TM) {
        sprintf(buffer,"%s.",msg_thread_type[1].c_str());
        
    } else {
        s_body = "NEZNAÅME";
    }
}

void Mesage::parse_page_type(char BH,char BL)  {
    char buffer[200];
    int pp = 0;
    pp = (BH<<8);
    pp += BL;
    int ID_stranky = convert_param(static_cast<unsigned char>(new_line[body_start+2]),static_cast<unsigned char>(new_line[body_start+3]));

    switch (pp) {
        case AP:
            sprintf(buffer,"%s s ID: %d %s sa swapla.",msg_page_type[0].c_str(),
                ID_stranky,get_page_name(ID_stranky).c_str());
            s_body = buffer;
            break;
        case MP:
            sprintf(buffer,"%s s ID: %d %s %s",msg_page_type[1].c_str(),
                ID_stranky,
                get_page_name(ID_stranky).c_str(),
                ((new_line[body_start+ 5] == 48) ? " sa vypla" : " sa zapla"));
            s_body = buffer;
            break;
        case PP:
            sprintf(buffer,"%s s ID: %d %s %s",msg_page_type[2].c_str(),
                ID_stranky,
                get_page_name(ID_stranky).c_str(),
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
    int flag=0;

    for(int i = 0;i<MSG_DEV_TYPE_COUNT;i++){
        if(pp == prior[i]){
            flag =1;
            sprintf(buffer,"%s parameter s ID: %d dosiahol hodnotu: %d.",msg_dev_type[i].c_str(),
                    convert_param(static_cast<unsigned char>(new_line[body_start+2]),static_cast<unsigned char>(new_line[body_start+3])),
                    convert_param(static_cast<unsigned char>(new_line[body_start+4]),static_cast<unsigned char>(new_line[body_start+5])));
                    s_body = buffer;
        }
    }
    if (!flag) {
        s_body = "NEZNAÅME";
    }
}

void Mesage::set_string_flag(char c_flag) {
    switch (c_flag)
    {
    case 'I':
        s_flag = " [Informacia]";
        break;
    case 'W':
        s_flag = " [Vystraha]";
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

string Mesage::get_page_name(const int page_ID){
    string stranka;
    switch(page_ID){
        case 1:
            stranka = "(Page boot)";
            break;
        case 2:
            stranka = "(Page system off)";
            break;
        case 3:
            stranka = "(Page main menu)";
            break;
        case 4:
            stranka = "(Page mode settings)";
            break;
        case 8:
            stranka = "(Page reboot)";
            break;
        case 10:
            stranka = "(Page loading)";
            break;
        default:
            stranka = "(N/A page)";
            break;
    }
    return stranka;
}

int Mesage::convert_param(unsigned char BH,unsigned char BL) {
    return ((BL - 32) + ((BH - 32) * 224));
}

Mesage::~Mesage() {
    Mesage::prior = 0;
}

