#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <cctype>
#include <algorithm>

using namespace std;

class A
{
public:
  int shift;
  int likelihood;

  bool operator< (const A lh) const
  {

    if (likelihood < lh.likelihood)
      return true;

    return false;
  } // operator <
}; // class A

int character_count(const char c, string &s);
vector<int> read_normal();
vector<int> read_message(string &s);
vector<A> shift_likelihood(vector<int> fre_normal, vector<int> fre_mes);
void print(string &s, const int shift);
void help(const int shift, char c);
bool judge(string &str, const int shift);
char wrap(char c, const int shift);
void read_word(string &str);

int main(int argc, char** argv)
{
  ifstream file1(argv[1]);
  vector<int> fre_normal_english(read_normal());
  stringstream ss;
  ss << file1.rdbuf();
  string str = ss.str();
  vector<int> fre_message(read_message(str));
  vector<A> lh = shift_likelihood(fre_normal_english, fre_message);
  sort(lh.begin(), lh.end());

  for (int version = 0; version < 26; version++)
  {
    vector<A>::iterator itr = lh.end();

    if (judge(str, (itr - 1 - version)->shift))
    {
      cout << "Deciphered message version #" << version + 1 << endl;
      print(str, (itr - 1 - version)->shift);
      cout << endl;
    } // if string has meaning
  } // print out the deciphered message

  file1.close();
  return 0;
} // main()

vector<int> read_normal()
{
  ifstream f("frequencies");
  vector<int> fre_normal_english(26);

  for (vector<int>::iterator it = fre_normal_english.begin();
          it != fre_normal_english.end(); it++) // initialize
    f >> *it;

  f.close();
  return fre_normal_english;
} // read_normal()

vector<int> read_message(string &s)
{
  vector<int> fre_message(26);
  int count = 0;

  for (vector<int>::iterator it = fre_message.begin();
          it != fre_message.end(); it++)
  {
    char c = 'a' + count;
    *it = character_count(c, s);
    count++;
  } // initialize

  return fre_message;
} // read_message()

int character_count(const char c, string &s)
{
  char ch;
  int count = 0;

  for (string::iterator itstr = s.begin(); itstr != s.end(); itstr++)
  {
    ch = *itstr;

    if (isupper(ch))
      ch += 32;

    if (ch == c)
      count++;
  } // for loop

  return count;
} // character_count()

vector<A> shift_likelihood(vector<int> fre_normal, vector<int> fre_mes)
{
  int count1 = 0, likelihood;
  vector<A> lh(26);
  vector<int>::iterator itA;
  vector<int>::iterator itB;

  for (vector<A>::iterator it = lh.begin(); it != lh.end(); it++)
  {
    it->shift = count1;
    likelihood = 0;

    for (itA = fre_normal.begin(), itB = fre_mes.begin();
            itA != fre_normal.end() && itB != fre_mes.end(); itA++, itB++)
    {
      if (itB - fre_mes.begin() + count1 >= 26) // wrap from 'a'
        likelihood += *itA * (*(itB + count1 - 26));
      else // not wrap
        likelihood += *itA * (*(itB + count1));
    } // calculate the likelihood for a certain shift

    it->likelihood = likelihood;
    count1++;
  } // for loop

  return lh;
} // shift_likelihood()

void help(const int shift, char c)
{
  if (isupper(c))
  {
    if (c - 'A' < shift)
    {
      c = c + 26 - shift;
      cout << c;
    } // if c needs wrap
    else // if not need wrap
    {
      c = c - shift;
      cout << c;
    } // else
  } // if c is uppercase
  else // if c is lowercase
  {
    if (c - 'a' < shift)
    {
      c = c + 26 - shift;
      cout << c;
    } // if need wrap
    else // if not need wrap
    {
      c = c - shift;
      cout << c;
    } // else
  } // else
} // help

char wrap(char c, const int shift)
{
  if (isupper(c))
  {
    if (c - 'A' < shift)
      c = c + 26 -shift + 32;
    else // if not wrap
      c = c - shift + 32;
  } // if uppercase
  else // if lowercase
  {
    if (c - 'a' < shift)
      c = c + 26 -shift;
    else // if not wrap
      c = c - shift;
  } // if lowercase

  return c;
} // wrap()

void read_word(string &str)
{
  ifstream fstr("words");
  stringstream ss;
  ss << fstr.rdbuf();
  str = ss.str();
  str = ' ' + str + ' ';

  for (string::iterator it = str.begin(); it != str.end(); it++)
  {
    char ch = *it;

    if (ch == '\n')
      *it = ' ';
  } // change \n to space
} // read_word()

bool judge(string &str, const int shift)
{
  string str_word;
  read_word(str_word);
  string temp = "";
  temp += ' ';

  for (string::iterator itstr = str.begin(); itstr != str.end(); itstr++)
  {
    if (!isspace(*itstr) && !ispunct(*itstr) && *itstr != '\n')
    {
      char c = *itstr;
      c = wrap(c, shift);
      temp += c;
    } // if alpha
    else // if not alpha
    {
      temp += ' ';

      if (str_word.find(temp) == string::npos) // not find
        return false;

      temp = "";
      temp += ' ';
    } // if not alpha
  } // for loop

  return true;
} // judge()

void print(string &s, const int shift)
{
  char c;

  for (string::iterator itstr = s.begin(); itstr != s.end(); itstr++)
  {
    c = *itstr;

    if (!isalpha(c))  // if not alpha
      cout << c;
    else // if c needs wrap
      help(shift, c);
  } // for loop
} // print()
