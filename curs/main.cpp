#include <iostream>
#include <fstream>
#include <iomanip>
#include "Pair.h"
#include "ShannonFano.h"
#include "Vector.h"
#include "Vector.cpp"
#include "QuickSort.h"
#include "QuickSort.cpp"
#include "String.h"
#include "FileOperation.h"

const String outFullFile = L"outFullFile.txt";
const String stockFile = L"encode.txt";
const String decodeOutFile = L"decode.txt";
const char* E_O = "File not found.";

void program1v1();
void program1v2();
void program2();

int main()
{
  std::locale ruLoc("ru_RU.UTF-8");
  std::wcin.imbue(ruLoc);
  std::wcout.imbue(ruLoc);
  try
  {
    int prog = 0;
    std::cout << "Какую программу вы хотите запустить \n 1) Шифрование текста кодом Шеннона-Фано. (консоль) \n 2) Шифрование текста кодом Шеннона-Фано. (файл) \n 3) Расшифровка зашифрованного текста кодом Шеннона-Фано. \nВведите номер программы: ";
    std::cin >> prog;

    switch (prog)
    {
      case 1:
        program1v1();
        break;
      case 2:
        program1v2();
        break;
      case 3:
        program2();
        break;
      default:
        std::cout << "Вы не выбрали ни одного варианта, выход.";
        break;
    }
    return 0;
  }
  catch (const std::runtime_error& k)
  {
    std::cerr << k.what() << "\n";
    return EXIT_FAILURE;
  }
}

void program1v1()
{
  ShannonFano sf;
  String str;
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  std::cout << "Введите строку для шифрования:\n";
  std::wcin >> str;
  double origSize = str.size();
  sf.findUniqChar(str);
  sf.absolutSort();
  sf.treeSet();
  String strCode;
  String tempStr;
  for(wchar_t ch : str)
  {
    tempStr = sf.treeDrowRez(ch);
    strCode += tempStr;
  }
  String rezOpr;
  std::cout << "Хотите увидеть шифр сообщения (y/n)?: ";
  std::wcin >> rezOpr;
  if(rezOpr == L"y" || rezOpr == L"Y")
  {
    std::wcout << strCode << "\n";
  }
  bool flag = true;
  String fileName;
  std::cout << "Введите название файла, куда хотите сохранить шифр в сжатом виде (no - сохранить в файл по умолчанию): ";
  std::wcin >> fileName;
  if(fileName == L"no")
  {
    writeBitsToFile(stockFile, strCode);
    std::wcout << L"Результат сохранен в " << stockFile;
    flag = false;
  }
  else
  {
    writeBitsToFile(fileName, strCode);
    std::wcout << L"Результат сохранен в " << fileName;
  }
  rezOpr.clear();
  std::cout << "\nВывести результат сжатия (Y/n): ";
  std::wcin >> rezOpr;
  if(rezOpr == L"Y" || rezOpr == L"y")
  {
     if(!flag)
     {
       double compresSize = getFileSize(stockFile);
       std::cout << "Результат сжатия: коэффициент сжатия равен " << std::fixed << std::setprecision(2) << (compresSize)/(origSize*sizeof(wchar_t)) << "\n";
     }
     else
     {
       double compresSize = getFileSize(fileName);
       std::cout << "Результат сжатия: коэффициент сжатия равен " << std::fixed << std::setprecision(2) << (compresSize)/(origSize*sizeof(wchar_t)) << "\n";
     }
  }
  Vector<Pair<wchar_t, int>> alp = sf.getFrequ();
  writeDataToFile(outFullFile, strCode, alp);
  std::wcout << L"Шифр с алфавитом сохранены в " << outFullFile << L"\n";
}

void program1v2()
{
  std::locale ruLoc("ru_RU.UTF-8");
  ShannonFano sf;
  String file;
  String str;
  std::wcout << L"Введите название файла .txt: ";
  std::wcin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  std::wcin >> file;
  readSourceDoc(file, str);
  double origSize = getFileSize(file);
  sf.findUniqChar(str);
  sf.absolutSort();
  sf.treeSet();
  String strCode;
  for(wchar_t ch : str)
  {
    strCode += sf.treeDrowRez(ch);
  }
  String rezOpr;
  std::cout << "Хотите увидеть шифр сообщения (y/n)?: ";
  std::wcin >> rezOpr;
  if(rezOpr == L"y" || rezOpr == L"Y")
  {
    std::wcout << strCode << "\n";
  }
  bool flag = true;
  String fileName;
  std::cout << "Введите название файла, куда хотите сохранить шифр в сжатом виде (no - сохранить в файл по умолчанию): ";
  std::wcin >> fileName;
  if(fileName == L"no")
  {
    writeBitsToFile(stockFile, strCode);
    std::wcout << L"Результат сохранен в " << stockFile;
    flag = false;
  }
  else
  {
    writeBitsToFile(fileName, strCode);
    std::wcout << L"Результат сохранен в " << fileName;
  }
  rezOpr.clear();
  std::cout << "\nВывести результат сжатия (Y/n): ";
  std::wcin >> rezOpr;
  if(rezOpr == L"Y" || rezOpr == L"y")
  {
     if(!flag)
     {
       double compresSize = getFileSize(stockFile);
       std::cout << "Результат сжатия: коэффициент сжатия равен " << std::fixed << std::setprecision(2) << (compresSize)/(origSize) << "\n";
     }
     else
     {
       double compresSize = getFileSize(fileName);
       std::cout << "Результат сжатия: коэффициент сжатия равен " << std::setw(2) << (compresSize)/(origSize) << "\n";
     }
  }
  Vector<Pair<wchar_t, int>> alp = sf.getFrequ();
  writeDataToFile(outFullFile, strCode, alp);
  std::wcout << L"Шифр с алфавитом сохранены в " << outFullFile << L"\n";
}

void program2()
{
  ShannonFano sf;
  String str;
  std::cout << "Введите название файла для расшифровки: ";
  std::wcin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  std::wcin >> str;
  String strCode;
  Vector<Pair<wchar_t, int>> vector;
  readDataFromFile(str, strCode, vector);
  sf.alphabetFile(vector);
  sf.absolutSort();
  sf.treeSet();
  std::wcout << L"\nРезультат расшифровки сообщения:\n\n";
  String rezStr = sf.treeDecode(strCode);
  writeDataDecode(decodeOutFile, rezStr);
  std::wcout << L"\n\nРасшифрованное сообщение сохранено в " << decodeOutFile << L"\n";
  std::cout << "\n";
}