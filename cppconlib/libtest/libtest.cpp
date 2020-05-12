// libtest.cpp : Defines the entry point for the console application.
//

#include "..\Includes\conmanip.h"
using namespace conmanip;

#include <iostream>
#include <iomanip>
#include <vector>
#include <assert.h>

template <console_type StdHandle>
void test_title()
{
   console<StdHandle> con;

   auto oldtitle = con.gettitle();

   auto newtitle = "demo console";
   con.settitle(newtitle);
   assert(newtitle == con.gettitle());

   con.settitle(oldtitle);

   auto oldtitlew = con.gettitlew();

   auto newtitlew = L"demo console";
   con.settitle(newtitlew);
   assert(newtitlew == con.gettitlew());

   con.settitle(oldtitle);

}

template <console_type StdHandle>
void test_colors()
{
   console<StdHandle> con;

   con.settextcolor(console_text_colors::red);
   std::cout << "something";
}

void test_color_free()
{
   console_out_context ctxout;

   std::cout << settextcolor(console_text_colors::green) 
             << setbgcolor(console_bg_colors::light_magenta)
             << "username: ";

   std::string username;
   std::cin >> settextcolor(console_text_colors::red)
            >> setbgcolor(console_bg_colors::light_yellow)
            >> username;

   std::cout << setcolors(console_text_colors::blue, console_bg_colors::light_red)
             << "password: ";

   std::string password;
   std::cin >> setcolors(console_text_colors::magenta, console_bg_colors::light_cyan)
            >> password;           
}

void test_mode_free()
{
   console_out_context ctxout;
   console_in_context ctxin;

   console_in conout;
   conout.setmode(console_modes::enable_mouse_selection);

   std::cout << "password: ";

   std::string text;
   std::cin >> clearmode(console_modes::echo)
            >> text
            >> setmode(console_modes::echo);

   std::cout << "overwrite: ";
   std::cin >> setmode(console_modes::overwrite)
            >> text
            >> clearmode(console_modes::overwrite);
}

void test_print_rhomb()
{
   console_out_context ctxout;
   console_out conout(ctxout);

   int depth;
   std::cout << "Depth (1-9)? ";
   std::cin >> depth;

   int middle = conout.getsize().X/2;
   for(int i = 1; i <= depth; ++i)
   {
      std::cout << setposx(middle-i+1);

      for(int j = 1; j<=i; ++j)
      {
         std::cout << i << " ";
      }
      std::cout << "\n";
   }

   for(int i = depth-1; i >=1; --i)
   {
      std::cout << setposx(middle-i+1);

      for(int j = 1; j<=i; ++j)
      {
         std::cout << i << " ";
      }
      std::cout << "\n";
   }
}

void test_read_matrix()
{
   console_out_context ctxout;
   console_out conout(ctxout);

   int rows;
   int cols;

   std::cout << "rows: "; std::cin >> rows;
   std::cout << "cols: "; std::cin >> cols;

   std::vector<int> numbers;
   int posy = conout.getposy();
   for(int i = 0; i < rows; ++i)
   {
      for(int j = 0; j < cols; ++j)
      {
         std::cout << setpos(j*4, posy+i+2) << "[_]";
      }
   }

   int val;
   for(int i = 0; i < rows; ++i)
   {
      for(int j = 0; j < cols; ++j)
      {
         std::cin >> setpos(j*4+1, posy+i+2) >> val;
         numbers.push_back(val);
      }
   }
}

void test_colors()
{
   console_out_context ctxout;

   struct _Entry {
      std::string             text;
      console_text_colors     foreground;
      console_bg_colors       background;
   };

   _Entry entries[] = {
      { "red",          console_text_colors::white,         console_bg_colors::red  },
      { "red",          console_text_colors::red,           console_bg_colors::white },
      { "\n",           console_text_colors::white,         console_bg_colors::black},
      { "blue",         console_text_colors::white,         console_bg_colors::blue },
      { "blue",         console_text_colors::blue,          console_bg_colors::white },
      { "\n",           console_text_colors::white,         console_bg_colors::black},
      { "green",        console_text_colors::white,         console_bg_colors::green },
      { "green",        console_text_colors::green,         console_bg_colors::white },
      { "\n",           console_text_colors::white,         console_bg_colors::black},
      { "yellow",       console_text_colors::yellow,        console_bg_colors::black },
      { "yellow",       console_text_colors::black,         console_bg_colors::yellow },
      { "\n",           console_text_colors::white,         console_bg_colors::black},
      { "cyan",         console_text_colors::blue,          console_bg_colors::cyan },
      { "cyan",         console_text_colors::cyan,          console_bg_colors::blue },
      { "\n",           console_text_colors::white,         console_bg_colors::black},
      { "magenta",      console_text_colors::magenta,       console_bg_colors::white },
      { "magenta",      console_text_colors::white,         console_bg_colors::magenta },
      { "\n",           console_text_colors::white,         console_bg_colors::black},
      { "light red",    console_text_colors::light_white,   console_bg_colors::light_red  },
      { "light red",    console_text_colors::light_red,     console_bg_colors::light_white },
      { "\n",           console_text_colors::white,         console_bg_colors::black},
      { "light blue",   console_text_colors::light_white,   console_bg_colors::light_blue },
      { "light blue",   console_text_colors::light_blue,    console_bg_colors::light_white },
      { "\n",           console_text_colors::white,         console_bg_colors::black},
      { "light green",  console_text_colors::light_white,   console_bg_colors::light_green },
      { "light green",  console_text_colors::light_green,   console_bg_colors::light_white },
      { "\n",           console_text_colors::white,         console_bg_colors::black},
      { "light yellow", console_text_colors::light_yellow,  console_bg_colors::black },
      { "light yellow", console_text_colors::black,         console_bg_colors::light_yellow },
      { "\n",           console_text_colors::white,         console_bg_colors::black},
      { "light cyan",   console_text_colors::light_blue,    console_bg_colors::light_cyan },
      { "light cyan",   console_text_colors::light_cyan,    console_bg_colors::light_blue },
      { "\n",           console_text_colors::white,         console_bg_colors::black},
      { "light magenta",console_text_colors::light_magenta, console_bg_colors::white },
      { "light magenta",console_text_colors::white,         console_bg_colors::light_magenta },
      { "\n",           console_text_colors::white,         console_bg_colors::black},
   };

   for(auto const & entry : entries)
   {
      std::cout 
         << setbgcolor(entry.background) 
         << settextcolor(entry.foreground)
         << entry.text;
   }

   ctxout.restore();
   std::cout << std::endl;

   std::cout << "The following input text is ";      
   std::cout << settextcolor(console_text_colors::light_white);
   std::cout << "highlighted";
   std::cout << restoretextcolor(ctxout);
   std::cout << " in ";
   std::cout << settextcolor(console_text_colors::red);
   std::cout << "red";
   std::cout << restoretextcolor(ctxout);
   std::cout << ": ";

   std::string text;
   std::cin 
      >> setbgcolor(console_bg_colors::red)
      >> text;
   std::cin
      >> restorebgcolor(ctxout);

   std::cout << std::endl;
}

int main()
{
   test_colors();
   test_read_matrix();
   test_print_rhomb();

   test_color_free();
   test_mode_free();
   
   test_title<console_type::out>();
   test_title<console_type::err>();

   test_colors<console_type::out>();
   test_colors<console_type::err>();

   return 0;
}

