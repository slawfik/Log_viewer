#ifndef DEFINITION_H
#define DEFINITION_H
#include <string>

#define MAX_COUNT_LOG_MESSAGE 500

enum stlpce { NULA = 0, JEDEN=1, DVA = 2, TRI = 3 };

const std::string msg_type_high[2] = { "Systém", "Vlákno" };
const std::string msg_type_low[2] = {"Špeciálne", "Použivateľské" };
const std::string msg_type_medium[3] = {"Zariadenie", "UI stránka", "Tlačidlo"};

enum msg_proirity { P_HIGH = 32, P_MEDIUM = 64, P_LOW = 128 };
//prior HIGH
const std::string msg_system_type[1] = { "Systém repot" };
const std::string msg_thread_type[2] = { "Proto vlákno", "Time line" };
//prior MEDIUM
const std::string msg_button_type[1] = { "Stlačené tlačidlo" };
const std::string msg_page_type[3] = { "Hlavná stránka", "Popup stranka", "Správa" };
const std::string msg_dev_type[] = { "AMX", "Cisco 1", "Cisco 2", "Matica 1", "Matica 2", "PC stream", "PC prezent", "Projektor 1", "Projektor 2",
"PDU", "AUDIO", "SMTP", "TV vsetky", "TV 1", "TV 2", "TV 3", "TV 4", "Monitor vsetky", "Monitor 1", "Monitor 2" , "Platno 1", "Platno 2"};// TODO
#define MSG_DEV_TYPE_COUNT 22
//prior LOW
const std::string msg_custom_type[] = { "Cisco hovor start", "Cisco hovor stop" };
const std::string msg_special_type[] = { "SYS reboot", "SYS start" };

enum msg_system_type_BH_BL { S_DEFAULT = 12336 };
enum msg_thread_type_BH_BL { PT = 28788, TM = 29805 };
enum msg_buton_type_BH_BL { B_DEFAULT = 12336 };
enum msg_page_type_BH_BL { AP = 0x6170, MP = 0x6D70, PP = 0x7070 };
enum msg_device_type_BH_BL { AMX = 0x3030, CISCO1 = 0x3031, CISCO2 = 0x3032 ,MATICA1 = 0x3033, MATICA2 = 0x3033 }; // TODO //30 -39 cisla v hexa dat do kalk
#endif // DEFINITION_H
