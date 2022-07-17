
#include "parse.h"
#include<iostream>


std::string mkUpper(std::string str)
{
  for(int i = 0; i != str.size(); i++)
  {
    str[i] = toupper(str[i]);    
  }

return str;
}

void parse(std::string str, std::vector<std::string>* words)
{ 
  std::string temp = "";
  int space;

  if(!str.empty())
  {
    prepareStr( &str );

    while((space = str.find(' ')) != std::string::npos)
    {
      temp = str.substr(0, space);

      words->push_back(temp);

      str.erase(0, (space + 1));
      temp.clear();
    }

    temp = str.substr(0, (str.size()));
    words->push_back(temp);
  }
  else
  {
    std::cout<<"\n\tNo string given...\n";
  }
}


void prepareStr(std::string *str)
{

  int strsize = int(str->size());
      

  for(int i = 0; i < strsize; i++)
  {
    if(i != (strsize - 1))
    {
      if (!isValid(str->at(i)))
      {
        str->replace(i, 1, " ");
      }
    }
    else if(!isValid(str->at(i)))
    {
      strsize -= 1;
      str->resize( (strsize) );
    }


  //  std::cout << str->at(i) << std::endl;
  }
}

bool isValid(char chr)
{
  bool result = false;

  if((chr >= 65 && chr <= 90))
  {
    result = true;
  }

return result;
}