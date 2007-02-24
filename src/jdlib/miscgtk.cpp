// ライセンス: GPL2

//#define _DEBUG
#include "jddebug.h"

#include "miscgtk.h"

#include <errno.h> // ERANGE

// char の初期化用
#define CHAR_BUF 256


// Gdk::Color -> 16進数表記の文字列
std::string MISC::color_to_str( const Gdk::Color& color )
{
    // R,G,Bを取得
    int l_rgb[3];
    l_rgb[0] = color.get_red();
    l_rgb[1] = color.get_green();
    l_rgb[2] = color.get_blue();

    return color_to_str( l_rgb );
}

// int[3] -> 16進数表記の文字列
std::string MISC::color_to_str( const int* l_rgb )
{
    // 16進数表記で各色の文字列を連結して格納
    char str_value[ CHAR_BUF ];
    snprintf( str_value, CHAR_BUF, "#%04x%04x%04x", l_rgb[ 0 ], l_rgb[ 1 ], l_rgb[ 2 ] );

#ifdef _DEBUG
    std::cout << "MISC::color_to_str" << std::endl;
    std::cout << l_rgb[0] << ", " << l_rgb[1] << ", " << l_rgb[2] << "->"
              << str_value << std::endl;
#endif

    return str_value;
}