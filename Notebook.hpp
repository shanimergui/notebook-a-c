#pragma once
#include <string>
#include "Direction.hpp"

namespace ariel
{
    class Notebook
    {
        public:
            void write(int page,  int row,  int col, ariel::Direction e,const std::string &stringToWrite);
            static std::string read(int page,  int row,  int col, ariel::Direction e, int length);
            void erase(int page,  int row,  int col, ariel::Direction e, int length);
            void show(int page);
    };
}