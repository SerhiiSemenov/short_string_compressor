#include <string>
#include <iostream>

#include "string_compressor.h"

enum class SymbolTables { UA_TABLE, EN_TABLE, SYMBOLS_TABLE, END_OF_LIST };
using IntType = typename std::underlying_type<SymbolTables>::type;

SymbolTables& operator++( SymbolTables &c ) {
  c = static_cast<SymbolTables>( static_cast<IntType>(c) + 1 );
  if ( c == SymbolTables::END_OF_LIST )
    c = static_cast<SymbolTables>(0);
  return c;
}

static const char *englist_decode_table[] = {
    /*16*/  "ua_table", "WERE", "symbols_table", "WHICH", "THIS", "THAT", "WITH", "FROM", "HAVE", "MEM", "THERE", "ASS", "WHI", "AND", "THEIR", "THEY", "THE", ".COM",
    /*32*/  "WAS", "THE", " MA", "EN ", "E A", "S A", "E C", "S, ", "D T", "AT ", "ALL", "HAT", "E T", "F T", "E S", "TIO",
    /*48*/ "ATI", "HAD", "ONE", "ARE", "HER", "HIS", "THA", "TER", "DIV", "ERE", "ENT", " OF", "ION", "FOR", "ING", "BUT",
    /*64*/ "OUT", "WHO", "ITS", "ATE", "VER", "E, IT", "NOT", "OF ", "N ", "OR", "AS", "IT", "IS", "AT", "RE", "T ",
    /*80*/ "ER", "EN", "  ", " W", "ES", " AN", " I", "F ", "ND", " S", "ND ", "ED ", "ED", "HTTP://",  "TE", "Y ",
    /*96*/  "D ", " C", "TI", "R ",  "ST", " IN", "AR", "NT", "OF", " TO",  "NG", " H", "LE", "AL", "TO ", "OU",
    /*112*/ "BE", " O", " B", "SE", "O ",  "HA", "NG ", " TH",  "HI",  " F", "IN ", "DE",  "ME", "VE", "RE ", "RI",
    /*128*/ "RO", "IS ", "CO", "EA", " M", "ER ", " P", "ES ", "BY", "DI", "RA", "IC", "CE", "LA", "H ", "NE",
    /*144*/ "AS ",  "ON ", "N T", "IO", "WE", " A ", "OM", ", A", "S O", "UR", "LI", "LL", "CH", "G ", "E\r\n", " WH",
    /*160*/ " CO", "E O", "A ", "US", " D", "SS", " BE", " E", "MA", "ON", "T T", "OR ",  "EL", "SO", "L ",  "S,",
    /*176*/ "NO", " WA", "IV", "HO", " R",  "S T", "NS", "CH ", "WH", "TR", "UT", "LY ", "TA", " HA", " ON", " L",
    /*192*/ "PE", " RE",  "SI", " FO", "WA", "EC",  "FO", "RS", "OT", "UN", "IM", "TH ", "NC", "AD", " WE", "LY",
    /*208*/ "EE", " GE", "ID", " CL", "AC", "IL", "RT", " WI", " T", "IN", "HE", "TH", "HE ", "TO", "AN", "H",
    /*224*/  "O", " A", "Y", "G", "P", "B", "Z", "E", "T", "A", "I", "N", "S", "E ", "R", "L",
    /*240*/  "S ", "D", "C", "F", "M", "U", "W", "V", "N", "X", "K", " ", " ", " ", " ", " ",
    /*256*/  " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ",
};

//res 40-43%
static const char *ukraine_decode_table[] = {
    /*16*/ " П", "en_table", "symbols_table", "О ", " В", " З", "А ", "И ", "НО", "СТ", " Д", " Н", "НА", ", ", "Я ", "РО",
    /*32*/ "У ", "І ", "ЕН", "ОВ", "Е ", "ТА", "ПР", "ПО", "НЯ", "НИ", "АН", " Т", " С", "ОР", "ВА", "КО",
    /*48*/ "ТИ", "ГО", "ЕР", "ІД", "РА", "ВІ", "ЛЬ", "ДО", " Р", "ОГ", "ВИ", "ЗА", "МЕ", " О", "АТ", "НЕ",
    /*64*/ "АВ", "ТО", "ЕМ", "В ", "РЕ", "РИ", "НІ", "ОМ", "ОС", "ОД", " М", "ДА", ". ", "ІЛ", "ВО", "ТЬ",
    /*80*/ "ЛЯ", "ДІ", "КА", "ОБ", "Ь ", " К", "ЗЕ", "АС", "Ї ", "ТР", "АД", "ЦІ", "Х ", "ЛА", " І", "ИС",
    /*96*/ "ЬН", "АЛ", "ЛЕ", "ИТ", "М ", "ЕЛ", " Б", "КУ", "ДЕ", "КИ", "АК", " У", "МО", "ІН", "ЯК", "МІ",
    /*112*/ "ИХ", "МА", " А", "РІ", "Й ", "ІВ", "ОН", "ОК", "ЩО", " Я", "ТІ", "ВН", "ОЇ", "ТЕ", "НК", "БУ",
    /*128*/ "ТУ", "УВ", "З ", "ЛИ", "ДН", "Ю ", "ЯН", "ІС", "СЬ", "КТ", "ВЛ", "ИМ", "К ", " Щ", "АР", "ДИ",
    /*144*/ "СЯ", " Ч", "ЖЕ", "ИК", "АМ", "ОЗ", "С", "МУ", "МИ", "УД", "ПЕ", "ИН", "Є ", "ИЙ", " Ц", "НУ",
    /*160*/ "ВЕ", "ЕК", "ЛІ", "СП", "АЦ", "ПІ", "ОТ", "ЛО", "ЧИ", "РУ", "ЬС", "ПИ", "АЧ", " Г", "ЗН", "СА",
    /*176*/ "ИВ", "ОЖ", "ЧЕ", "ІЙ", "ЬК", "МЛ", "НТ", "ЕД", "УМ", "ТВ", "ЧА", "КІ", "ГА", "СЕ", "ДУ", "СУ",
    /*192*/ "ОЮ", "ІЇ", "ЖА", "ВС", "АЗ", "ОЛ", "ЦЕ", "СІ", "УТ", "АЄ", "Д ", "И,", "Т ", "БО", "КР", "ЧН",
    /*208*/ "ЕЖ", "РЖ", "ХО", "ШЕ", "АБ", "ПА", "ИЗ", "ОП", "РМ", "АХ", "ІТ", "ГР", "ДП", "СО", "АЙ", "ЕС",
    /*224*/ "ПЛ", "СК", "ІЗ", "ДЛ", " Л", "УК", "УС", "ЕЗ", "ЮТ", "ЕТ", "БА", "ИЛ", "ЬО", "КЛ", "НД", " Ф",
    /*240*/ "А", "Б", "В", "Г", "Д", "Е", "Ж", "З", "И", "Ї", "К", "Л", "М", "Н", "О", "П",
    /*256*/ "Р", "С", "Т", "У", "Ф", "Х", "Ц", "Ч", "Ш", "Щ", "І", "Ь", "Є", "Ю", "Я", " "
};

static const char *symbols_decode_table[] = {
    /*16*/ "ua_table", "en_table", ".", "?", "!", ", ", ":", ";", "\"", "#", "$", "%", "&", "\'", "(", ")",
    /*32*/ "*", "+", "-",  "<", "=", ">", "/", ", ", "\n\r\n", "\r\n\r", "=\"", "><", "\r\n", "\n", "\r", "0",
    /*48*/ "1", "2", "3", "4", "5", "6", "7", "8", "9"
    /*64*/
};

StringCompressor::StringCompressor() {
    //make hash table for the english character
    for (int arr_position = 0; arr_position < static_cast<int>(sizeof(englist_decode_table)/sizeof(englist_decode_table[0])); arr_position++) {
        this->englist_table[englist_decode_table[arr_position]] = arr_position;
    }
    //make hash table for the ukraine character
    for (int arr_position = 0; arr_position < static_cast<int>(sizeof(ukraine_decode_table)/sizeof(ukraine_decode_table[0])); arr_position++) {
        this->ukraine_table[ukraine_decode_table[arr_position]] = arr_position;
    }
    //make hash table for the symbols
    for (int arr_position = 0; arr_position < static_cast<int>(sizeof(symbols_decode_table)/sizeof(symbols_decode_table[0])); arr_position++) {
        this->symbols_table[symbols_decode_table[arr_position]] = arr_position;
    }
}

StringCompressor::~StringCompressor() {
}

size_t StringCompressor::compress(std::string &input_string, std::vector<std::byte> &output_data) {
    int retry = 0;
    SymbolTables table_id = SymbolTables::UA_TABLE;
    std::unordered_map<std::string, unsigned char> *table_list[] = {&ukraine_table, &englist_table, &symbols_table};
    std::unordered_map<std::string, unsigned char> *table_ptr = &ukraine_table;

    for (std::string::size_type in_str_iter = 0; in_str_iter < input_string.size(); ) {
        retry = 0;
        do {
            if (auto res = table_ptr->find(input_string.substr(in_str_iter, 4)); res != table_ptr->end()) {
                output_data.push_back(static_cast<std::byte>(res->second));
                in_str_iter+=4;
                break;
            }
            else if (auto res = table_ptr->find(input_string.substr(in_str_iter, 3)); res != table_ptr->end()) {
                output_data.push_back(static_cast<std::byte>(res->second));
                in_str_iter+=3;
                break;
            }
            else if (auto res = table_ptr->find(input_string.substr(in_str_iter, 2)); res != table_ptr->end()) {
                output_data.push_back(static_cast<std::byte>(res->second));
                in_str_iter+=2;
                break;
            }
            else if (auto res = table_ptr->find(input_string.substr(in_str_iter, 1)); res != table_ptr->end()) {
                output_data.push_back(static_cast<std::byte>(res->second));
                in_str_iter+=1;
                break;
            }
            else {
                retry++;
                ++table_id;
                table_ptr = table_list[static_cast<int>(table_id)];
                output_data.push_back(static_cast<std::byte>(table_id));
            }
        } while (retry <= 2);//retry
        if (retry >= 3) {
            std::cout << "ERROR: Charecter not found" << std::endl;
            break;
        }
    }
    return output_data.size();
}

size_t StringCompressor::decompress(std::vector<std::byte> &input_data, std::string &output_string){
    const char **table_ptr = ukraine_decode_table;

    for (auto &input_item : input_data) {
        if (static_cast<int>(input_item) == static_cast<IntType>(SymbolTables::UA_TABLE) && table_ptr != ukraine_decode_table) {
            table_ptr = ukraine_decode_table;
            continue;
        }
        else if(static_cast<int>(input_item) == static_cast<IntType>(SymbolTables::EN_TABLE) && table_ptr != englist_decode_table) {
            table_ptr = englist_decode_table;
            continue;
        }
        else if (static_cast<int>(input_item) == static_cast<IntType>(SymbolTables::SYMBOLS_TABLE) && table_ptr != symbols_decode_table) {
            table_ptr = symbols_decode_table;
            continue;
        }
        output_string += table_ptr[static_cast<int>(input_item)];
    }
    return output_string.length();
}