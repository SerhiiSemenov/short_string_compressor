#include <bitset>
#include <vector>
#include <string>
#include <unordered_map>

class StringCompressor {

public:
  StringCompressor();
  ~StringCompressor() = default;
  StringCompressor(const StringCompressor&) = delete;
  StringCompressor(StringCompressor&&) = delete;
  StringCompressor operator=(const StringCompressor&) = delete;

  size_t compress(std::string &input_string, std::vector<std::byte> &output_data);
  size_t decompress(std::vector<std::byte> &input_data, std::string &output_string);

private:
  std::unordered_map<std::string, unsigned char> englist_table;
  std::unordered_map<std::string, unsigned char> ukraine_table;
  std::unordered_map<std::string, unsigned char> symbols_table;
};
