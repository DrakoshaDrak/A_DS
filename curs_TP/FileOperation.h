#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <bitset>

const int maxStrLength = 25000;
const std::string N_F = "File not found.";

void writeBitsToFile(const std::wstring& filename, const std::wstring& bits)
{
  std::ofstream file(filename.data(), std::ios::binary);
  if(!file.is_open())
  {
    throw std::runtime_error(N_F);
  }
  std::bitset<8> byte;
  for (size_t i = 0; i < bits.size(); ++i)
  {
    byte[i % 8] = bits[i] == '1';
    if((i + 1) % 8 == 0 || i == bits.size() - 1)
    {
      file.put(static_cast<char>(byte.to_ulong()));
      byte.reset();
    }
  }
  file.close();
}
std::wstring readBitsFromFile(const std::wstring& filename, size_t size)
{
  std::ifstream file(filename.data(), std::ios::binary);
  if(!file.is_open())
  {
    throw std::runtime_error(N_F);
  }
  std::wstring bits;
  char byte;
  size_t bits_read = 0;
  while(file.get(byte) && bits_read < size)
  {
    std::bitset<8> byteBits(static_cast<unsigned char>(byte));
    for(int i = 0; i < 8 && bits_read < size; ++i)
    {
      bits += byteBits[i] ? '1' : '0';
      ++bits_read;
    }
  }
  file.close();
  return bits;
}

void writeDataToFile(const std::wstring& filename, const std::wstring& cipher, const std::vector<std::pair<wchar_t, int>>& alphabet)
{
  std::locale ruLoc("ru_RU.UTF-8");
  std::wofstream file(filename.data(), std::ios::binary);
  if(!file.is_open())
  {
    throw std::runtime_error(N_F);
  }
  file.imbue(ruLoc);
  file << cipher.data() << std::endl;
  for(const auto& pair : alphabet)
  {
    file << pair.first << L" " << pair.second << std::endl;
  }
  file.close();
}

void readDataFromFile(const std::wstring& filename, std::wstring& cipher, std::vector<std::pair<wchar_t, int>>& alphabet)
{
  std::locale ruLoc("ru_RU.UTF-8");
  std::wifstream file(filename.data(), std::ios::binary);
  if(!file.is_open())
  {
    throw std::runtime_error(N_F);
  }
  file.imbue(ruLoc);
  file >> cipher;
  file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  alphabet.clear();
  wchar_t symbol;
  int value;
  while(file.get(symbol) && file >> value)
  {
    alphabet.push_back({symbol, value});
    file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }
  file.close();
}

size_t getFileSize(const std::wstring& filename)
{
  std::ifstream file(filename.data(), std::ios::binary | std::ios::ate);
  if (!file.is_open())
  {
    throw std::runtime_error(N_F);
  }
  size_t fileSize = file.tellg();
  file.close();
  return fileSize;
}

void readSourceDoc(const std::wstring& filename, std::wstring& str)
{
  std::locale ruLoc("ru_RU.UTF-8");
  std::wifstream file(filename.data());
  file.imbue(ruLoc);
  if(!file.is_open())
  {
    throw std::runtime_error(N_F);
  }
  wchar_t tempStr[maxStrLength];
  while(file.getline(tempStr, sizeof(tempStr)/sizeof(wchar_t)))
  {
    if(!str.empty())
    {
      str += L"\n";
    }
    str += tempStr;
  }
  file.close();
}

void writeDataDecode(const std::wstring& filename, const std::wstring& decodeStr)
{
  std::locale ruLoc("ru_RU.UTF-8");
  std::wofstream file(filename.data(), std::ios::binary);
  if(!file.is_open())
  {
    throw std::runtime_error(N_F);
  }
  file.imbue(ruLoc);
  file << decodeStr.data() << std::endl;
  file.close();
}