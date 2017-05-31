// ReadFromStandardInput.cpp : コンソール アプリケーションのエントリ ポイントを定義します。 ☣
//

#include "stdafx.h"

#include <algorithm>
#include <iostream>
#include <iterator>
#include <regex>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

void Test01()
{
    // 一行 & 一列 読み込みのテスト
    string value;
    cin >> value;

    string prompt = value;
    cout << prompt << endl;
}

// 一行読み込み & 半角ブランクによる分割
vector<string> ReadOneLine()
{
    string in;
    getline(cin, in);

    istringstream iss(in);
    vector<string> ret{ istream_iterator<string>{iss}, istream_iterator<string>{} };

    return ret;
}

// 一行読み込み & 引数のデリミタによる分割
vector<string> ReadOneLine(char delimiter)
{
    string in;
    getline(cin, in);

    vector<string> ret;
    stringstream ss;
    ss.str(in);
    string item;
    while (getline(ss, item, delimiter)) {
        *(back_inserter(ret)++) = item;
    }

    return ret;
}

// 一行読み込み & 引数のデリミタによる分割
vector<string> ReadOneLine(char delimiter, bool skipblank)
{
    string in;
    getline(cin, in);

    vector<string> ret;
    stringstream ss;
    ss.str(in);
    string item;
    while (getline(ss, item, delimiter)) {
        if (item.length() == 0 && skipblank) {
            continue;
        }
        *(back_inserter(ret)++) = item;
    }
    return ret;
}

void OutOneLine(vector<string> arg)
{
    string prompt;
    // for (string v : arg) { // Clang 用 拡張 for ループ
    for each (string v in arg) {
        if (prompt.length() != 0) prompt.append(" ");
        prompt.append(v);
    }
    cout << prompt << endl;
}

void Test02()
{
    // 一行 & 複数列 読み込みのテスト
    // 列のデリミタは半角ブランクであること前提
    vector<string> value;
    value = ReadOneLine((char)32, true);

    OutOneLine(value);
}

bool EvaluateFirstLine(vector<string> arg)
{
    // 行数の判断
    // テスト用なので最大入力は 10 行までに制限する
    if (arg.size() < 1) {
        cout << "入力行数が不正です" << endl;
        return false;
    }
    regex re("([a-z]+|[A-Z]+)");
    smatch mc;
    if (regex_match(arg.at(0), mc, re)) {
        // 行数フィールドに英字が入っている
        cout << "入力行数が不正です" << endl;
        return false;
    }
    return true;
}

void Test03()
{
    // 複数行 & 複数列 読み込みのテスト
    // 列のデリミタは半角ブランク
    // 最初の行 第 1 トークンに行数
    // 最初の行 第 2 トークンに列数がセットされている前提
    // 1 行目
    vector<string> firstLine;
    firstLine = ReadOneLine((char)32);

    if (!EvaluateFirstLine(firstLine)) {
        return;
    }
    int linesCount = stoi(firstLine.at(0));

    vector<vector<string>> value;
    value.push_back(firstLine);
    for (int i = 1; i < linesCount; i++) {
        vector<string> addOne;
        addOne = ReadOneLine((char)32);
        value.push_back(addOne);
        addOne.clear();
    }

    // for (vector<string> outLine : value) { // Clang 用 拡張 for ループ
    for each (vector<string> outLine in value) {
        OutOneLine(outLine);
    }
}

void TestEnd()
{
    // テスト終了前にユーザーからの入力を待機する
    string prompt = "終了するには文字を入力してください";
    cout << prompt << endl;
    cin >> prompt;
}

int main()
{
    Test01();
    Test02();
    Test03();
    TestEnd();
    return 0;
}