#ifndef WRITE_EXCEL_H
#define WRITE_EXCEL_H

#include <conio.h>
#include "libxl.h"
#include <windows.h>
#include "statistic_msg_parser.h"

using namespace libxl;

#define MONTH_SHEET 23
#define GRAF_SHEET 24

class write_excel
{
    public:
    int tele_row[22] = {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3};
    Book* book;
    Sheet* sheet[25];
    Font *black_font;
    Format* blackBlodFormat;
    Format* blascNormal;
    Format* timeFormat;

    bool month_stat = false;

    void createExcel_file(bool monthMSG);
    void saveExcel_file(wchar_t* pa_filename);
    void write_data(vector<statictic_msg*>& msg_vector);
    write_excel();

private:
    void formatHead(Sheet& pa_sheet);
    void formatHeadMonth(Sheet* pa_sheet);
};

#endif // WRITE_EXCEL_H
