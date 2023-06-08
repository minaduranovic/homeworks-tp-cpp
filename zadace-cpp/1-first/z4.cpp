// TP 2022/2023: Zadaća 1, Zadatak 4
#include <cctype>
#include <cmath>
#include <cstring>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

std::string tolowerString(std::string trenutna){
std::string temp="";
for (char c: trenutna){
    temp+=tolower(c);
}
return temp;
}
bool slovo(char c) {
  if (c < 'A' || c > 'z')
    return false;
  return true;
}
std::string Cenzura(std::string recenica, std::vector<std::string> zabranjene) {

  std::string trenutna;

  for (std::string rijec : zabranjene) {
    for (int i = 0; i < rijec.length(); i++) {
      if (slovo(rijec.at(i)) == false) {
        throw std::logic_error("Neispravna riječ");
      }
      rijec.at(i) = tolower(rijec.at(i));
    }
  }
  std::string cenzurisana = "";
  int i = 0;
  while (i < recenica.length()) {
    if (!slovo(recenica.at(i))) {
      cenzurisana += recenica.at(i);
      i++;
      continue;
    }
    int j = i;
    while (j < recenica.length() && slovo(recenica.at(j))) {
      j++;
    }
    trenutna = recenica.substr(i, j - i);
    // if (trenutna.length() > 0) {
    //   for (int k = 0; k < trenutna.length(); k++) {
    //     trenutna.at(k) = tolower(trenutna.at(k));
    //   }
    // }
    bool cenz = false;
    for (auto zabr : zabranjene) {
      if (tolowerString(zabr)== tolowerString(trenutna)) {
        cenz = true;
        break;
      }
    }
    if (cenz) {
      cenzurisana += std::string(trenutna.length(), '*');
    } else {
      cenzurisana += trenutna;
    }
    i = j;
  }
  return cenzurisana;
}
int main() {
  std::string recenica, rijec, trenutna;
  std::cout << "Unesite recenicu: "<<std::endl;

  std::getline(std::cin, recenica, '\n');
 
  std::cout << "Unesite zabranjene rijeci (. za kraj): "<<std::endl;
//    std::cin.ignore();
  std::vector<std::string> zabranjene;
  std::getline(std::cin, trenutna, '.');
//    std::cin.ignore();
  rijec = "";
  for (char c : trenutna) {
    if (c == ' ') {
      if (rijec.length() != 0) {
        zabranjene.push_back(rijec);
        rijec = "";
      }
    } else if (c == '.') {
      if (rijec.length() != 0) {
        zabranjene.push_back(rijec);
      }
      break;
    } else {
      rijec += c;
    }
  }
  if (rijec.length() != 0) {
    zabranjene.push_back(rijec);
  }
//   for (std::string s: zabranjene){
//       std::cout<<s<<" ";
//   }
try{
std::string s=Cenzura(recenica,  zabranjene);
std::cout<<"Cenzurisana recenica: " << s;
}
catch(std::logic_error &e){
    std::cout<<"GRESKA:  Nelegalne zabranjene rijeci!";
}
  return 0;
}
