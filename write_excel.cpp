#include "write_excel.h"
#include "wchar.h"

write_excel::write_excel()
{
    book = xlCreateBook();
    black_font = book->addFont();
    black_font->setColor(COLOR_BLACK);
    black_font->setBold(true);

    blackBlodFormat = book->addFormat();
    blackBlodFormat->setFont(black_font);
    blackBlodFormat->setAlignH(ALIGNH_CENTER);
    blackBlodFormat->setAlignV(ALIGNV_CENTER);
    blackBlodFormat->setBorder(BORDERSTYLE_MEDIUM);

    blascNormal = book->addFormat();
    blascNormal->setAlignH(ALIGNH_CENTER);
    blascNormal->setAlignV(ALIGNV_CENTER);
    blascNormal->setBorder(BORDERSTYLE_MEDIUM);

    timeFormat = book->addFormat();
    timeFormat->setNumFormat(NUMFORMAT_CUSTOM_HMM);
}

void write_excel::saveExcel_file(wchar_t* pa_filename)   {
    book->delSheet(4);  //tele-5 don't exist
    book->delSheet(14); //tele-16 don't exist
    book->save(pa_filename);
    book->release();
}

void write_excel::createExcel_file(bool monthMSG) {
    wchar_t buff[25];

    for(int i = 0;i<22;i++)  {//tele 22 je este miestnos?!!!
        swprintf(buff,25,L"tele-%d",i+1);
        sheet[i] = book->addSheet(buff);
        formatHead(*sheet[i]);
    }
    if(monthMSG)    {
         sheet[MONTH_SHEET] = book->addSheet(L"Month_Stat");
         formatHeadMonth(sheet[MONTH_SHEET]);
    }
    //ADD graf sheet
    sheet[GRAF_SHEET] = book->addSheet(L"Grafy");
}

void write_excel::write_data(vector<statictic_msg*>& msg_vector){
    const QString formath = "dd.MM.yyyy";
    int coll ,tele_num ,row_M = 0;
    wchar_t buffer[40] = {L'0'};

    for(size_t i = 0; i<msg_vector.size();i++){
        tele_num = msg_vector.operator[](i)->get_teleNumber()-1;
        memset(buffer,0,80);

        switch(msg_vector.operator[](i)->type){
            case DAY_MSG:
                coll = 0;
                msg_vector.operator[](i)->get_dateTime().date().toString(formath).toWCharArray(buffer);
                sheet[tele_num]->writeStr(tele_row[tele_num], coll++,buffer, blackBlodFormat);
                memset(buffer,0,80);    //wchar_t zaberá 2 bajty
                msg_vector.operator[](i)->get_dateTime().time().toString().toWCharArray(buffer);
                sheet[tele_num]->writeStr(tele_row[tele_num], coll++,buffer, blackBlodFormat);
                sheet[tele_num]->writeStr(tele_row[tele_num], coll++,L"--",blascNormal);
                for(int j = 0;j<5;j++)  {
                    sheet[tele_num]->writeNum(tele_row[tele_num],coll,msg_vector.operator[](i)->getTolat_time(j),blascNormal);
                    sheet[tele_num]->writeNum(tele_row[tele_num],coll+5,msg_vector.operator[](i)->getMin_time(j),blascNormal);
                    sheet[tele_num]->writeNum(tele_row[tele_num],coll+10,msg_vector.operator[](i)->getMax_time(j),blascNormal);
                    sheet[tele_num]->writeNum(tele_row[tele_num],coll+15,msg_vector.operator[](i)->getArit_Priemer(j),blascNormal);
                    sheet[tele_num]->writeNum(tele_row[tele_num],coll+20,msg_vector.operator[](i)->getCouter(j),blascNormal);
                    coll++;
                }
                coll = coll+20;
                sheet[tele_num]->writeNum(tele_row[tele_num],coll++,msg_vector.operator[](i)->getBoot_Ernno(0),blascNormal);
                sheet[tele_num]->writeNum(tele_row[tele_num],coll,msg_vector.operator[](i)->getBoot_Ernno(1),blascNormal);
                tele_row[tele_num]++; //inc row in this tele room
                 break;
            case MONTH_MSG:
                coll = 0;
                row_M = tele_num+3;
                swprintf(buffer,L"tele-%d",tele_num+1);
                sheet[MONTH_SHEET]->writeStr(row_M, coll++,buffer, blackBlodFormat); //nie je potrebne nulova?
                //msg_vector.operator[](i)->get_dateTime().date().toString(formath).toWCharArray(buffer);
                sheet[MONTH_SHEET]->writeStr(row_M, coll++,L"--", blackBlodFormat);
                //memset(buffer,0,80);    //wchar_t zaberá 2 bajty
                //msg_vector.operator[](i)->get_dateTime().time().toString().toWCharArray(buffer);
                sheet[MONTH_SHEET]->writeStr(row_M, coll++,L"--", blackBlodFormat);
                sheet[MONTH_SHEET]->writeStr(row_M, coll++,L"--",blascNormal);
                for(int j = 0;j<5;j++)  {
                    sheet[MONTH_SHEET]->writeNum(row_M,coll,msg_vector.operator[](i)->getTolat_time(j),blascNormal);
                    sheet[MONTH_SHEET]->writeNum(row_M,coll+5,msg_vector.operator[](i)->getMin_time(j),blascNormal);
                    sheet[MONTH_SHEET]->writeNum(row_M,coll+10,msg_vector.operator[](i)->getMax_time(j),blascNormal);
                    sheet[MONTH_SHEET]->writeNum(row_M,coll+15,msg_vector.operator[](i)->getArit_Priemer(j),blascNormal);
                    sheet[MONTH_SHEET]->writeNum(row_M,coll+20,msg_vector.operator[](i)->getCouter(j),blascNormal);
                    sheet[MONTH_SHEET]->writeNum(row_M,coll+25,msg_vector.operator[](i)->getModus(j),blascNormal);
                    coll++;
                }
                coll = coll+25;
                sheet[MONTH_SHEET]->writeNum(row_M,coll++,msg_vector.operator[](i)->getBoot_Ernno(0),blascNormal);
                sheet[MONTH_SHEET]->writeNum(row_M,coll,msg_vector.operator[](i)->getBoot_Ernno(1),blascNormal);
                break;

            case ACTION_MSG:
                coll = 0;
                msg_vector.operator[](i)->get_dateTime().date().toString(formath).toWCharArray(buffer);
                sheet[tele_num]->writeStr(tele_row[tele_num], coll++,buffer, blackBlodFormat);
                memset(buffer,0,80);    //wchar_t zaberá 2 bajty
                msg_vector.operator[](i)->get_dateTime().time().toString().toWCharArray(buffer);
                sheet[tele_num]->writeStr(tele_row[tele_num], coll++,buffer, blackBlodFormat);
                memset(buffer,0,80);
                msg_vector.operator[](i)->get_popisCodu().toWCharArray(buffer);
                sheet[tele_num]->writeStr(tele_row[tele_num], coll++,buffer, blackBlodFormat);    //inc row
                tele_row[tele_num]++; //inc row in this tele room

                break;
            case BAD_MSG:
                break;

            case DAY_MSG_NEW:
                coll = 0;
                msg_vector.operator[](i)->get_dateTime().date().toString(formath).toWCharArray(buffer);
                sheet[tele_num]->writeStr(tele_row[tele_num], coll++,buffer, blackBlodFormat);
                memset(buffer,0,80);    //wchar_t zaberá 2 bajty
                msg_vector.operator[](i)->get_dateTime().time().toString().toWCharArray(buffer);
                sheet[tele_num]->writeStr(tele_row[tele_num], coll++,buffer, blackBlodFormat);
                sheet[tele_num]->writeStr(tele_row[tele_num], coll++,L"--",blascNormal);
                for(int j = 0;j<2;j++)  {
                    sheet[tele_num]->writeNum(tele_row[tele_num],coll,msg_vector.operator[](i)->getTolat_time(j),blascNormal);
                    sheet[tele_num]->writeNum(tele_row[tele_num],coll+5,msg_vector.operator[](i)->getMin_time(j),blascNormal);
                    sheet[tele_num]->writeNum(tele_row[tele_num],coll+10,msg_vector.operator[](i)->getMax_time(j),blascNormal);
                    sheet[tele_num]->writeNum(tele_row[tele_num],coll+15,msg_vector.operator[](i)->getArit_Priemer(j),blascNormal);
                    sheet[tele_num]->writeNum(tele_row[tele_num],coll+20,msg_vector.operator[](i)->getCouter(j),blascNormal);
                    coll++;
                }
                coll = coll+23;
                sheet[tele_num]->writeNum(tele_row[tele_num],coll++,msg_vector.operator[](i)->getBoot_Ernno(0),blascNormal);
                sheet[tele_num]->writeNum(tele_row[tele_num],coll,msg_vector.operator[](i)->getBoot_Ernno(1),blascNormal);
                tele_row[tele_num]++; //inc row in this tele room
                break;
        }
    }
}

void write_excel::formatHead(Sheet& pa_sheet)    {
    int coll = 0;
    pa_sheet.setCol(0,0,11.1);
    pa_sheet.setCol(2,2,13.1);
    pa_sheet.writeStr(2,coll++,L"Datum",blackBlodFormat);
    pa_sheet.writeStr(2,coll++,L"Cas",blackBlodFormat);
    pa_sheet.writeStr(2,coll++,L"Code",blackBlodFormat);

    pa_sheet.setCol(3,28,6.1);

    pa_sheet.setMerge(1,1,3,7);
    pa_sheet.writeStr(1,3,L"Total Time",blackBlodFormat);
    pa_sheet.writeStr(2,coll++,L"Total",blackBlodFormat);
    pa_sheet.writeStr(2,coll++,L"VGA",blackBlodFormat);
    pa_sheet.writeStr(2,coll++,L"Menu",blackBlodFormat);
    pa_sheet.writeStr(2,coll++,L"Prezent",blackBlodFormat);
    pa_sheet.writeStr(2,coll++,L"Viko",blackBlodFormat);

    pa_sheet.setMerge(1,1,8,12);
    pa_sheet.writeStr(1,8,L"Min Time",blackBlodFormat);
    pa_sheet.writeStr(2,coll++,L"Total",blackBlodFormat);
    pa_sheet.writeStr(2,coll++,L"VGA",blackBlodFormat);
    pa_sheet.writeStr(2,coll++,L"Menu",blackBlodFormat);
    pa_sheet.writeStr(2,coll++,L"Prezent",blackBlodFormat);
    pa_sheet.writeStr(2,coll++,L"Viko",blackBlodFormat);

    pa_sheet.setMerge(1,1,13,17);
    pa_sheet.writeStr(1,13,L"Max Time",blackBlodFormat);
    pa_sheet.writeStr(2,coll++,L"Total",blackBlodFormat);
    pa_sheet.writeStr(2,coll++,L"VGA",blackBlodFormat);
    pa_sheet.writeStr(2,coll++,L"Menu",blackBlodFormat);
    pa_sheet.writeStr(2,coll++,L"Prezent",blackBlodFormat);
    pa_sheet.writeStr(2,coll++,L"Viko",blackBlodFormat);

    pa_sheet.setMerge(1,1,18,22);
    pa_sheet.writeStr(1,18,L"Arit. priemer",blackBlodFormat);
    pa_sheet.writeStr(2,coll++,L"Total",blackBlodFormat);
    pa_sheet.writeStr(2,coll++,L"VGA",blackBlodFormat);
    pa_sheet.writeStr(2,coll++,L"Menu",blackBlodFormat);
    pa_sheet.writeStr(2,coll++,L"Prezent",blackBlodFormat);
    pa_sheet.writeStr(2,coll++,L"Viko",blackBlodFormat);

    pa_sheet.setMerge(1,1,23,27);
    pa_sheet.writeStr(1,23,L"Counter",blackBlodFormat);
    pa_sheet.writeStr(2,coll++,L"Total",blackBlodFormat);
    pa_sheet.writeStr(2,coll++,L"VGA",blackBlodFormat);
    pa_sheet.writeStr(2,coll++,L"Menu",blackBlodFormat);
    pa_sheet.writeStr(2,coll++,L"Prezent",blackBlodFormat);
    pa_sheet.writeStr(2,coll++,L"Viko",blackBlodFormat);

    pa_sheet.writeStr(2,coll++,L"Boot",blackBlodFormat);
    pa_sheet.writeStr(2,coll++,L"Errno",blackBlodFormat);
}

void write_excel::formatHeadMonth(Sheet* pa_sheet)  {
    int coll = 0;
    pa_sheet->setCol(1,1,11.1);
    pa_sheet->setCol(2,2,13.1);
    pa_sheet->writeStr(2,coll++,L"Tele",blackBlodFormat);
    pa_sheet->writeStr(2,coll++,L"Datum",blackBlodFormat);
    pa_sheet->writeStr(2,coll++,L"Cas",blackBlodFormat);
    pa_sheet->writeStr(2,coll++,L"Code",blackBlodFormat);

    pa_sheet->setCol(3,35,6.1);
    pa_sheet->setMerge(1,1,coll,coll+4);
    pa_sheet->writeStr(1,coll,L"Total Time",blackBlodFormat);
    pa_sheet->writeStr(2,coll++,L"Total",blackBlodFormat);
    pa_sheet->writeStr(2,coll++,L"VGA",blackBlodFormat);
    pa_sheet->writeStr(2,coll++,L"Menu",blackBlodFormat);
    pa_sheet->writeStr(2,coll++,L"Prezent",blackBlodFormat);
    pa_sheet->writeStr(2,coll++,L"Viko",blackBlodFormat);

    pa_sheet->setMerge(1,1,coll,coll+4);
    pa_sheet->writeStr(1,coll,L"Min Time",blackBlodFormat);
    pa_sheet->writeStr(2,coll++,L"Total",blackBlodFormat);
    pa_sheet->writeStr(2,coll++,L"VGA",blackBlodFormat);
    pa_sheet->writeStr(2,coll++,L"Menu",blackBlodFormat);
    pa_sheet->writeStr(2,coll++,L"Prezent",blackBlodFormat);
    pa_sheet->writeStr(2,coll++,L"Viko",blackBlodFormat);

    pa_sheet->setMerge(1,1,coll,coll+4);
    pa_sheet->writeStr(1,coll,L"Max Time",blackBlodFormat);
    pa_sheet->writeStr(2,coll++,L"Total",blackBlodFormat);
    pa_sheet->writeStr(2,coll++,L"VGA",blackBlodFormat);
    pa_sheet->writeStr(2,coll++,L"Menu",blackBlodFormat);
    pa_sheet->writeStr(2,coll++,L"Prezent",blackBlodFormat);
    pa_sheet->writeStr(2,coll++,L"Viko",blackBlodFormat);

    pa_sheet->setMerge(1,1,coll,coll+4);
    pa_sheet->writeStr(1,coll,L"Arit. priemer",blackBlodFormat);
    pa_sheet->writeStr(2,coll++,L"Total",blackBlodFormat);
    pa_sheet->writeStr(2,coll++,L"VGA",blackBlodFormat);
    pa_sheet->writeStr(2,coll++,L"Menu",blackBlodFormat);
    pa_sheet->writeStr(2,coll++,L"Prezent",blackBlodFormat);
    pa_sheet->writeStr(2,coll++,L"Viko",blackBlodFormat);

    pa_sheet->setMerge(1,1,coll,coll+4);
    pa_sheet->writeStr(1,coll,L"Counter",blackBlodFormat);
    pa_sheet->writeStr(2,coll++,L"Total",blackBlodFormat);
    pa_sheet->writeStr(2,coll++,L"VGA",blackBlodFormat);
    pa_sheet->writeStr(2,coll++,L"Menu",blackBlodFormat);
    pa_sheet->writeStr(2,coll++,L"Prezent",blackBlodFormat);
    pa_sheet->writeStr(2,coll++,L"Viko",blackBlodFormat);

    pa_sheet->setMerge(1,1,coll,coll+4);
    pa_sheet->writeStr(1,coll,L"Modus",blackBlodFormat);
    pa_sheet->writeStr(2,coll++,L"Total",blackBlodFormat);
    pa_sheet->writeStr(2,coll++,L"VGA",blackBlodFormat);
    pa_sheet->writeStr(2,coll++,L"Menu",blackBlodFormat);
    pa_sheet->writeStr(2,coll++,L"Prezent",blackBlodFormat);
    pa_sheet->writeStr(2,coll++,L"Viko",blackBlodFormat);

    pa_sheet->writeStr(2,coll++,L"Boot",blackBlodFormat);
    pa_sheet->writeStr(2,coll++,L"Errno",blackBlodFormat);
}
