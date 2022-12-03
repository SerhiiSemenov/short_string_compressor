# String compressor
## Short string compression library

It's a simple compression library suitable for compressing very short strings.
The library can compress text by 30-47% in the average case works better with mixed Ukraine and English text and supports only upper case letter.
To compare this with other libraries, think that like zlib will usually not be able to compress text shorter than 100 bytes.

## Compression exampels

|string|results|
| ------ | ------ |
|КОРОТКЕ ПОВІДОМЛЕННЯ |	compressed by 45% string size: (20->11)|
|THIS IS A SHORT MESSAGE| compressed by 44% string size: (23->13)|
|ПРИВІТ. ЦЕ КОРОТКЕ ПОВІДОМЛЕННЯ WITH THE ENGLISH, PART! ДЛЯ ПЕРЕВІРКИ?| compressed by 33% string size: (70->47)|
|ПРИВІТ. ЯК СПРАВИ ТРЕБА НЕВІДКЛАДНО ТВОЯ ДОПОМОГА| compressed by 47% string size: (49->26)|
|ТОЧНЕ ВЛУЧАННЯ| compressed by 43% string size: (14->8)|
|THIS IS A SHORT MESSAGE| compressed by 44% string size: (23->13)|
|THE END| compressed by 43% string size: (7->4)|
|THIS IS A SIMPLE COMPRESSION LIBRARY| compressed by 45% string size: (36->20)|
|NOTHING IS MORE DIFFICULT, AND THEREFORE MORE PRECIOUS, THAT TO BE ABLE TO DECIDE| compressed by 46% string size: (81->44)|
|THIS IS AN EXAMPLE OF WHAT WORKS VERY WELL WITH LIBRARY| compressed by 48% string size: (55->29)|
|1000 NUMBERS 2000 WILL 10 20 30 COMPRESS VERY LITTL| Eenlarged by -7|

## Usage
-----

The lib consists of just two methods:

    int compress(std::string &input_string, std::vector<std::byte> &output_data);

Compress the buffer 'input_string' and put the compressed data into
'output_data'.

    int decompress(std::vector<std::byte> &input_data, std::string &output_string);

Decompress the buffer 'input_data' and put the decompressed data into
'output_string'.

## Build and run test example

```sh
make clean && make
```
```sh
./string_compressor
```