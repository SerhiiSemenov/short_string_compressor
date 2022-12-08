#include <iostream>
#include <string>
#include <vector>
#include <bitset>
#include "string_compressor.h"


static size_t utf8len(const char *s);

int main(void) {
    StringCompressor compressor;
    std::vector<std::byte> compressed_str;
    std::string decompressed_str;

    std::vector<std::string> test_strings = {
        "КОРОТКЕ ПОВІДОМЛЕННЯ",
        "THIS IS A SHORT MESSAGE",
        "ПРИВІТ. ЦЕ КОРОТКЕ ПОВІДОМЛЕННЯ WITH THE ENGLISH, PART! ДЛЯ ПЕРЕВІРКИ?",
        "ПРИВІТ. ЯК СПРАВИ ТРЕБА НЕВІДКЛАДНО ТВОЯ ДОПОМОГА",
        "ТОЧНЕ ВЛУЧАННЯ",
        "HELLO BRANDON, HOW ARE YOU?",
        "THE END",
        "THIS IS A SIMPLE COMPRESSION LIBRARY",
        "NOTHING IS MORE DIFFICULT, AND THEREFORE MORE PRECIOUS, THAT TO BE ABLE TO DECIDE",
        "THIS IS AN EXAMPLE OF WHAT WORKS VERY WELL WITH LIBRARY",
        "1000 NUMBERS 2000 WILL 10 20 30 COMPRESS VERY LITTLE",
    };

    for (auto & element : test_strings) {
        std::cout << element << " size: "<< utf8len(element.c_str()) << std::endl;
        int comprlen = compressor.compress(element, compressed_str);
        int comprlevel = 100 -((100*comprlen)/utf8len(element.c_str()));
        size_t decomplen = compressor.decompress(compressed_str, decompressed_str);

        std::cout << "Out str: " << decompressed_str << std::endl;

        if (element.length() != decomplen ||
            element.compare(decompressed_str))
        {
            std::cout << "BUG: error compressing " << element << " -> " << decompressed_str << std::endl;
            exit(1);
        }
        if (comprlevel < 0) {
            std::cout << " --------------------------" << std::endl;
            std::cout << "| enlarged by " << comprlevel << "           |" << std::endl;
            std::cout << " --------------------------" << std::endl;
        }
        else {
            std::cout << " -----------------------------------------" << std::endl;
            std::cout << "|" << " compressed by " << comprlevel << "% "
                << "string size: (" << utf8len(element.c_str()) << "->" << comprlen << ")"
                << " |" << std::endl;
            std::cout << " -----------------------------------------" << std::endl;
        }
        std::cout << std::endl;
        decompressed_str.clear();
        compressed_str.clear();
    }
}

size_t utf8len(const char *s)
{
    size_t len = 0;
    for (; *s; ++s) if ((*s & 0xC0) != 0x80) ++len;
    return len;
}