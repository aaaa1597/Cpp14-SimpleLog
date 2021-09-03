#pragma once
#include <chrono>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <functional>

#define AAALOG(fmt, ...) aaalog(__FILE__, __LINE__, __FUNCTION__, fmt, __VA_ARGS__)

const std::string logfile = "aaalog.log";

/* パラメータパックが空になったら終了 */
inline std::string makelogstr(const std::string fmt) {
    return fmt;
}

template <class Head, class... Body>
std::string makelogstr(const std::string fmt, const Head head, const Body... body) {

    std::string retstr = fmt;
    size_t spos= fmt.find("{");
    size_t len = fmt.find("}") - spos + 1;

    std::stringstream s;
    s << head;
    if(spos != std::string::npos)
        retstr.replace(spos, len, s.str());

    return makelogstr(retstr, body...);
}

template <class... Args>
std::string makelogstr(const std::string fmt, const Args... args) {
    return makelogstr(fmt, args...);
}


template <class... Args>
void aaalog(const std::string file, const int line, const std::string func, std::string fmt, Args... args) {
	std::ofstream logofs(logfile, std::ios::app);

    /* フルパスからファイル名だけ抜出し */
    std::string filename = file.substr(file.find_last_of("\\") + 1);

    std::function<std::string()> timestr = []() {
        /* 現在時刻取得 */
        std::chrono::system_clock::time_point nowtime = std::chrono::system_clock::now();

        /* std::tmの形式に変換 */
        std::time_t tt = std::chrono::system_clock::to_time_t(nowtime);

        std::tm lt;
        localtime_s(&lt, &tt);

        /* 時刻の小数点値を求める */
        std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds>(nowtime.time_since_epoch());
        std::size_t fractional_seconds = ms.count() % 1000;

        /* 時刻文字列の生成 */
        std::stringstream s;
        s << "20" << lt.tm_year - 100 << "/";
        /* setw(),setfill()で0詰め */
        s << std::setw(2) << std::setfill('0') << lt.tm_mon + 1 << "/";
        s << std::setw(2) << std::setfill('0') << lt.tm_mday << " ";
        s << std::setw(2) << std::setfill('0') << lt.tm_hour << ":";
        s << std::setw(2) << std::setfill('0') << lt.tm_min << ":";
        s << std::setw(2) << std::setfill('0') << lt.tm_sec << ".";
        s << std::setw(3) << std::setfill('0') << fractional_seconds;

        /* 時刻文字列の返却 */
        return s.str();
    };

    std::string newfmt = timestr() + " " + func + "() " + fmt;
    logofs << makelogstr(newfmt, args...) << " " << filename << "("<< line << ")" << std::endl;

    return;
}

