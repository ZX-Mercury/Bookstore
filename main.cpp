#include<iostream>
#include<string>
#include<bits/stdc++.h>
#include "account.h"
#include "bookdata.h"

const std::unordered_map<std::string, std::vector<int>> tokencheck = {
        {"quit", {1}},
        {"exit", {1}},

        {"su", {2, 3}},
        {"logout", {1}},
        {"register", {4}},
        {"passwd", {3, 4}},
        {"useradd", {5}},
        {"delete", {2}},

        //{"show",{1}},
        {"buy", {3}},
        {"select", {2}},
        //{"modify",{1}},
        {"import", {3}},

        {"show", {2, 3}},
        {"log", {1}},
        {"report", {1}}
};

bool checktokens(const std::vector<std::string> &tokens) {
    for (int i: tokencheck.at(tokens[0])) {
        if (tokens.size() == i) {
            return true;
        }
    }
    std::cout << "Invalid\n";
    return false;
}


int main() {
    bookdata Bdata;
    Bdata.initialise();
    accounts acc;
    acc.create(7, "root", "sjtu");
    std::string s;
    short int currentRank;
    std::string currentUser;
    while (getline(std::cin, s)) {
        //初始化当前用户信息
        if (!acc.loginStack.empty()) {
            currentRank = acc.loginStack.back().privilege;
            currentUser = acc.loginStack.back().UserID;
        } else {
            currentRank = 0;
            currentUser = "bucunzai";
        }

        //读入控制台输入
        std::vector<std::string> tokens;
        std::stringstream ss(s);
        std::string token;
        while (ss >> token) {
            tokens.push_back(token);
        }
        if (tokens.empty()) continue;
        //检查操作和长度是否合法
        std::string op = tokens[0];
        if (tokencheck.find(op) != tokencheck.end()) {
            if (!checktokens(tokens))
                continue;
        } else {
            std::cout << "Invalid\n";
            continue;
        }

        //***************
        //账户指令区
        if (op == "su") {
            std::string UserID = tokens[1];
            std::string Pw;
            if (!acc.Isexist(UserID)) {
                std::cout << "Invalid\n";
                continue;
            }
            short int UserRK = acc.findrank(UserID);
            if (tokens.size() == 3) Pw = tokens[2];
            if (!Pw.empty()) {
                if (!acc.logcheck(UserID, tokens[2])) {
                    std::cout << "Invalid\n";
                    continue;
                }
            } else {
                if (currentRank <= UserRK) {
                    std::cout << "Invalid\n";
                    continue;
                }
            }
            acc.login(UserRK, UserID);
        } else if (op == "useradd") {
            if (!(currentRank >= 3)) {
                std::cout << "Invalid\n";
                continue;
            }
            short int Privi = tokens[3][0] - '0';
            std::string UserID = tokens[1];
            if (Privi >= currentRank) {
                std::cout << "Invalid\n";
                continue;
            }
            if (acc.Isexist(UserID)) {
                std::cout << "Invalid\n";
                continue;
            }
            acc.create(Privi, UserID, tokens[2]);
        } else if (op == "logout") {
            if (acc.loginStack.empty()) {
                std::cout << "Invalid\n";
                continue;
            }
            acc.logout();
        } else if (op == "register") {
            if (acc.Isexist(tokens[1])) {
                std::cout << "Invalid\n";
                continue;
            }
            acc.create(1, tokens[1], tokens[2]);
        } else if (op == "delete") {
            std::string UserID = tokens[1];
            if (!(currentRank >= 7)) {
                std::cout << "Invalid\n";
                continue;
            }
            if (!acc.Isexist(UserID)) {
                std::cout << "Invalid\n";
                continue;
            }
            if (acc.Islogin(UserID)) {
                std::cout << "Invalid\n";
                continue;
            }
            acc.del(UserID);
        }else if (op == "passwd") {
            if (!(currentRank >= 1)) {
                std::cout << "Invalid\n";
                continue;
            }
            std::string UserID = tokens[1];
            if (!acc.Isexist(UserID)) {
                std::cout << "Invalid\n";
                continue;
            }

            std::string CurPw, NewPw;
            NewPw = tokens[tokens.size() - 1];
            if (tokens.size() == 4) CurPw = tokens[2];
            if (!CurPw.empty()) {
                if (!acc.logcheck(UserID, CurPw)) {
                    std::cout << "Invalid\n";
                    continue;
                }
            }
            if (currentRank != 7 && CurPw.empty()) {
                std::cout << "Invalid\n";
                continue;
            }
            acc.change(UserID, NewPw);
        }


        //***************
        //图书指令区
        else if (op == "select") {
            if (!(currentRank >= 3)) {
                std::cout << "Invalid\n";
                continue;
            }
            std::string ISBN = tokens[1];
            acc.loginStack.back().ISBN=ISBN;
            if (Bdata.ISindex.find(ISBN)==Bdata.ISindex.end()) {
                Bdata.create(ISBN);
            }
        }
        else if (op == "modify") {
            if (!(currentRank >= 3)) {
                std::cout << "Invalid\n";
                continue;
            }
            if (acc.loginStack.back().ISBN=="bucunzai"){
                std::cout << "Invalid\n";
                continue;
            }
            for (int i = 1; i<=tokens.size();i++){
                std::string require = tokens[1];
                int j = 1;
                std::string reop;
                while (require[j]!='='){
                    reop += require[j];
                    j++;
                }
                j++;
                if (reop == ""){}
                else if (reop == ""){}
            }
        }
        /*else if (op == "") {}
        else if (op == "") {}*/
        else if (op == "exit") { break; }
        else std::cout << "IIIInvalid\n";
        std::cout << "`";
    }
    Bdata.reinitial();
}