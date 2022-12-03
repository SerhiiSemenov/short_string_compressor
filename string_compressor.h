#include <bitset>
#include <vector>
#include <string>
#include <unordered_map>

class StringCompressor {

public:
  StringCompressor();
  ~StringCompressor();

  int compress(std::string &input_string, std::vector<std::byte> &output_data);
  int decompress(std::vector<std::byte> &input_data, std::string &output_string);

private:
  std::unordered_map<std::string, unsigned char> englist_table;
  std::unordered_map<std::string, unsigned char> ukraine_table;
  std::unordered_map<std::string, unsigned char> symbols_table;
};