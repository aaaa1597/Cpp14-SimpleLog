# C-14SimpleLog
C++14以降で動く簡易ログのサンプルです。
C++らしく、templeteやら、iostreamやらで作っています。

c形式の書式指定子は、使っておらず、pythonチックに、"{}"を置換する形にしています。

Visual Studio 2019で作っています。

# 使い方
このプロジェクト一式をcloneして、logtest.slnを、Visual Studio 2019で開いて、実行して下さい。
それで動くはずです。

ログの使い方は、main.cppが参考になりますが、一応、記述しておきます。

```C++:
aaalog(__FILE__, __LINE__, __FUNCTION__ , "最初のログ {} {}" , "aa", 32);
AAALOG("最初のログ {} {} {} {} {} {}", __FILE__, __LINE__, __FUNCTION__, "最初のログ", "aa", 32);
```
最初の文字列の中の"{}"を、2番目以降の引数の文字列に変換しています。

出力は以下になります。
```prompt:
2021/09/03 13:21:37.477 main() 最初のログ aa 32 logtest.cpp(9)
2021/09/03 13:21:37.479 main() 最初のログ D:\logtest\logtest\logtest.cpp 10 main 最初のログ aa 32 logtest.cpp(10)
```

日付文字列 関数名 ログ文字列 ファイル名(行数)の形式で出力されます。
