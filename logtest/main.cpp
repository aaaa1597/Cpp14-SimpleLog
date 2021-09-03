// logtest.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
#include <iostream>
#include "MyLog.hpp"

int main()
{
    std::cout << "Hello World!\n";

    aaalog(__FILE__, __LINE__, __FUNCTION__ , "最初のログ {} {}" , "aa", 32);
    AAALOG("最初のログ {} {} {} {} {} {}", __FILE__, __LINE__, __FUNCTION__, "最初のログ", "aa", 32);

    return 0;
}
