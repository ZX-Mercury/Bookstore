//
// Created by laohu on 2023/12/19.
//

#ifndef BOOKSTORE_ACCOUNT_H
#define BOOKSTORE_ACCOUNT_H
#include<bits/stdc++.h>
//#include<unordered_map>
//#include<vector>
class accounts {
public:
    struct account1 {
        short int privilege;
        std::string UserID, Password;
        int logcnt = 0;
    };
    struct account2 {
        short int privilege;
        std::string UserID;
    };
    std::unordered_map<std::string, account1> acs;//用户信息
    std::vector<account2> loginStack;
    static bool check(short int pri, const std::string &UserID, const std::string &Password) {
        if (pri != 0 && pri != 1 && pri != 3 && pri != 7) return false;
        if (UserID.length() > 30 || Password.length() > 30) return false;
        for (char i: UserID) if (!isalnum(i) && i != '_') return false;
        for (char i: Password) if (!isalnum(i) && i != '_') return false;
        return true;
    }
    void login(short int pri, const std::string &UserID){
        account2 tmp;
        tmp.privilege=pri;
        tmp.UserID=UserID;
        loginStack.push_back(tmp);
        acs[UserID].logcnt++;
    }
    void logout(){
        acs[loginStack.back().UserID].logcnt--;
        loginStack.pop_back();
    }
    short int findrank(const std::string& UserID){
        return acs[UserID].privilege;
    }
    void create(short int privilege, const std::string &UserID, const std::string &Password) {
        if (check(privilege, UserID, Password)) {
            account1 tmp;
            tmp.privilege = privilege;
            tmp.UserID = UserID;
            tmp.Password = Password;
            acs[UserID] = tmp;
        }
    }

    bool Isexist(const std::string& UserID){
        return (acs.find(UserID)!=acs.end());
    }
    bool Islogin(const std::string& UserID){
        return (acs[UserID].logcnt>0);
    }
    void change(const std::string& UserID, const std::string& Newpw){
        acs[UserID].Password=Newpw;
    }
    void del(const std::string& UserID){
        if (acs[UserID].logcnt>0){//还在登录状态

        }
        else{
            acs.erase(UserID);
        }
    }
    bool logcheck(const std::string& U, const std::string& P){
        return (P==acs[U].Password);
    }
};

#endif //BOOKSTORE_ACCOUNT_H
