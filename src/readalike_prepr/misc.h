#include <fstream>
#include <string>

#define COMP_INTRO_END_LINE 29
#define COMP_MAIN_END_LINE  13146932
#define COMP_CODA_END_LINE  13147025

#define DECOMP_MAIN_END_LINE  13146902
#define DECOMP_INTRO_END_LINE 13146931
#define DECOMP_CODA_END_LINE  13147025

void split4Comp(char const *enwik9_filename) {
  std::ifstream ifile(enwik9_filename, std::ios::binary); 
  std::ofstream ofile1(".intro", std::ios::binary); 
  std::ofstream ofile2(".main", std::ios::binary); 
  std::ofstream ofile3(".coda", std::ios::binary); 

  int line_count = 0;

  std::string s;
  while (std::getline(ifile, s)) {
    if (line_count < COMP_INTRO_END_LINE) {
      ofile1 << s << std::endl;
    } else if (line_count < COMP_MAIN_END_LINE) {
        ofile2 << s << std::endl;
      } else if (line_count < COMP_CODA_END_LINE) {
          ofile3 << s << std::endl;
          } else {
            ofile3 << s; 
          }
    line_count++;
  }

  ofile1.close();
  ofile2.close();
  ofile3.close();
}

void split4Decomp() {
  std::ifstream ifile(".input_decomp", std::ios::binary); 
  std::ofstream ofile1(".intro_decomp", std::ios::binary); 
  std::ofstream ofile2(".main_decomp", std::ios::binary); 
  std::ofstream ofile3(".coda_decomp", std::ios::binary); 

  int line_count = 0;

  std::string s;
  while (std::getline(ifile, s)) {
    if (line_count < DECOMP_MAIN_END_LINE) {
      ofile2 << s << std::endl;
    } else if (line_count < DECOMP_INTRO_END_LINE) {
        ofile1 << s << std::endl;
      } else if (line_count < DECOMP_CODA_END_LINE) {
          ofile3 << s << std::endl;
          } else {
            ofile3 << s; 
          }
    line_count++;
  }

  ofile1.close();
  ofile2.close();
  ofile3.close();
}
