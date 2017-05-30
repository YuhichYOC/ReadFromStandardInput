// ReadFromStandardInput.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"

#include <iostream>
#include <regex>
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

vector<string> ReadOneLine()
{
    vector<string> ret;
    bool lineEndFound = false;
    while (!lineEndFound) {
        string item;
        cin >> item;
        ret.push_back(item);
        int c = cin.peek();
        if (c == 10) {
            // 改行文字が見つかった場合読み込み終了
            lineEndFound = true;
        }
    }
    return ret;
}

void OutOneLine(vector<string> arg)
{
    string prompt;
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
    value = ReadOneLine();

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
    firstLine = ReadOneLine();

    if (!EvaluateFirstLine(firstLine)) {
        return;
    }
    int linesCount = stoi(firstLine.at(0));

    vector<vector<string>> value;
    value.push_back(firstLine);
    for (int i = 1; i < linesCount; i++) {
        vector<string> addOne;
        addOne = ReadOneLine();
        value.push_back(addOne);
        addOne.clear();
    }

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

