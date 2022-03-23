#include "doctest.h"
#include "Notebook.hpp"
#include <string>

using namespace std;
using namespace ariel;

TEST_CASE("test horizontal and verticl")
{
    string ans;
    Notebook notebook; 

    //page 100 

    notebook.write(/*page=*/100, /*row=*/100, /*column=*/202, Direction::Horizontal, "ab");
    ans = notebook.read(/*page=*/100, /*row=*/100, /*column=*/202, Direction::Horizontal, /*length=*/2);
    CHECK(ans == "ab");

    
    notebook.write(/*page=*/100, /*row=*/100, /*column=*/205, Direction::Horizontal, "cd");
    ans = notebook.read(/*page=*/100, /*row=*/100, /*column=*/205, Direction::Horizontal, /*length=*/2);
    CHECK(ans == "cd"); 

	notebook.write(/*page=*/100, /*row=*/99, /*column=*/204, Direction::Vertical, "xyz");
	ans = notebook.read(/*page=*/100, /*row=*/100, /*column=*/203, Direction::Horizontal, /*length=*/5);
    CHECK(ans == "abycd");

    ans = notebook.read(/*page=*/100, /*row=*/100, /*column=*/203, Direction::Vertical, /*length=*/3);
    CHECK(ans == "xyz");


    ans = notebook.read(/*page=*/100, /*row=*/100, /*column=*/205, Direction::Vertical, /*length=*/3);
    CHECK(ans == "_c_"); 

    ans = notebook.read(100,100,202, Direction::Vertical,5);
    CHECK(ans == "a____"); 

	notebook.erase(/*page=*/100, /*row=*/99, /*column=*/204, Direction::Vertical, /*length=*/3);
    CHECK(ans == "~~~");

    ans = notebook.read(100,100,203, Direction::Vertical,4);
    CHECK(ans == "b___");

    ans = notebook.read(100,100,204, Direction::Vertical,5);
    CHECK(ans == "yz___");

    ans = notebook.read(100,100,205, Direction::Vertical,5);
    CHECK(ans == "c____");

    ans = notebook.read(100,98,202, Direction::Vertical,5);
    CHECK(ans == "__a__"); 

    notebook.erase(100, 100, 202, Direction::Horizontal, 5);
    CHECK(ans == "~~~~~");


    //page 99
    notebook.write(/*page=*/99, /*row=*/99, /*column=*/204, Direction::Horizontal, "???d");
    ans = notebook.read(99,99,204, Direction::Horizontal,5);
    CHECK(ans == "???d_");

    ans = notebook.read(99,98,207, Direction::Vertical,5);
    CHECK(ans == "_d___");

    notebook.write(/*page=*/99, /*row=*/98, /*column=*/200, Direction::Horizontal, "shanimergui");
    ans = notebook.read(99,98,200, Direction::Horizontal,11);
    CHECK(ans == "shanimergui");

    ans = notebook.read(99,98,200, Direction::Horizontal,5);
    CHECK(ans == "shani");

    ans = notebook.read(99,98,206, Direction::Horizontal,6);
    CHECK(ans == "mergui");

    notebook.erase(/*page=*/99, /*row=*/98, /*column=*/205, Direction::Vertical,3);
    CHECK(ans == "~~~");

    ans = notebook.read(99,98,200, Direction::Horizontal,11);
    CHECK(ans == "shani~ergui");

    ans = notebook.read(99,99,203, Direction::Horizontal,6);
    CHECK(ans == "_?~?d");

    ans = notebook.read(99,98,207, Direction::Horizontal,4);
    CHECK(ans == "ed__");

    notebook.write(/*page=*/99, /*row=*/99, /*column=*/211, Direction::Vertical, "chai");
    ans = notebook.read(99,98,211, Direction::Vertical,5);
    CHECK(ans == "ichai");

    ans = notebook.read(99,99,204, Direction::Horizontal,8);
    CHECK(ans == "?~?d___c");

    ans = notebook.read(99,100,204, Direction::Horizontal,8);
    CHECK(ans == "_~_____h");
}


/**
 * @brief random sized string 
 * coin = 1 : 100 chars string
 * else : 25 chars string
 * @return string 
 */
string stringGenerator(int coin)
{
    int length = 0;
    string st = "";
    coin == 1 ? length = 100 : length = 25;
    for (size_t i = 0; i <= length; i++) //length = 101
    {
        st += (char)(65+ ( rand() % 57) );
    }
    return st;

}


/**
 * @brief randomize a number between given numbers
 * 
 * @param min 
 * @param max 
 * @return int 
 */

int random(int min, int max) //range : [min, max]
{
   static bool first = true;
   if (first) 
   {  
      srand( time(NULL) ); //seeding for the first time only!
      first = false;
   }
   return min + rand() % (( max + 1 ) - min);
}

  TEST_CASE("random test")
 {
    string ans;
    Notebook notebook;
    
    // because the string is more than 100
    string st = stringGenerator(1);
    CHECK_THROWS(notebook.write(99,99,99,Direction::Horizontal,st)); 
    CHECK_THROWS(notebook.write(1,3,9,Direction::Horizontal,st));
    
    //adds 26 each time to the string
    st = stringGenerator(0);
    CHECK_NOTHROW(notebook.write(99,99,99,Direction::Horizontal,st)); //string value 26
    CHECK_NOTHROW(notebook.write(99,99,99,Direction::Horizontal,st)); //string value 26+26 =52
    CHECK_NOTHROW(notebook.write(99,99,99,Direction::Horizontal,st)); //string value 26 +26+26=78

    //erroe because the string is now 104 and it is biggers than 100
    CHECK_THROWS(notebook.write(99,99,99,Direction::Horizontal,st));

    int page = random (1,20);
    int col = random (1,20);
    int row = random (1,20);
    st = stringGenerator(0);
    CHECK_NOTHROW(notebook.write(page,col,row,Direction::Horizontal,st));


    
     notebook.write(/*page=*/101, /*row=*/100, /*column=*/202, Direction::Horizontal, "shani");
     ans = notebook.read(/*page=*/101, /*row=*/100, /*column=*/203, Direction::Vertical, /*length=*/4);
     CHECK(ans == "hani");
     CHECK_THROWS(notebook.write(/*page=*/101, /*row=*/100, /*column=*/202, Direction::Horizontal, "ab ef"));

     notebook.erase(/*page=*/101, /*row=*/100, /*column=*/202, Direction::Horizontal, 5); 
     CHECK_THROWS(notebook.write(/*page=*/101, /*row=*/100, /*column=*/202, Direction::Horizontal, "ab ef"));



}

TEST_CASE("check negative number")
 {

     Notebook notebook;
     CHECK_THROWS(notebook.write(-100,10,10,Direction::Horizontal,"shani"));
     CHECK_THROWS(notebook.write(100,-10,10,Direction::Horizontal,"shani"));
     CHECK_THROWS(notebook.write(100,10,-10,Direction::Horizontal,"shani"));
     CHECK_THROWS(notebook.write(-100,-10,-10,Direction::Horizontal,"shani"));
 }


