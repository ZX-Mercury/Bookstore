//
// Created by laohu on 2023/12/23.
//

#ifndef BOOKSTORE_BOOKDATA_H
#define BOOKSTORE_BOOKDATA_H

class bookdata {
private:
    std::fstream file;
    int num = 0, namenum = 0;
    const std::string NU = "bucunzai";
    const int ONELINE = 240;
    const int lenISBN = 20, lenname=60, lenauthor=60;
    const int namessize = sizeof(names);
public:
    std::map<std::string,int> nametoindex;
    struct book {
        std::string ISBN;
        std::string bookname, author;
        std::vector<std::string> keyword;
        int quantity = 0, price = 0;
    };
    struct names{
        char name[60];
        short int indx[10000];
        int next =-1;
    };
    std::unordered_map<std::string, int> ISindex;

    bookdata() = default;

    void init2(const std::string& filename){
        file.open(filename, std::ios::in | std::ios::out);
        if(!file.is_open()) {
            file.open(filename, std::ios::out);
        }
        file.close();
    }

    /*std::unordered_map<std::string, int> cut (std::string ){
        x
    };*/

    void initialise() {
        file.open("num", std::ios::in | std::ios::out);
        if(!file.is_open()) {
            file.open("num", std::ios::out);
        }
        else {
            std::string nums;
            getline(file,nums);
            num=std::stoi(nums);
        }
        file.close();
        init2("bookdata");
        file.open("ISBN", std::ios::in | std::ios::out);
        {//ISBN
            if (!file.is_open()) {
                file.open("ISBN", std::ios::out);
            } else {
                std::string tmp;
                while (getline(file, tmp)) {
                    std::istringstream iss(tmp);
                    std::string ISBN, index;
                    iss >> ISBN >> index;
                    ISindex[ISBN] = stoi(index);
                }

            }
            file.close();
        }
        init2("author");
        init2("bookname");
        init2("keyword");
    }

    std::string change(std::string s, int l) {
        int k = l-s.length();
        for (int i = 1; i <= k; i++) {
            s += " ";
        }
        return s;
    }

    void create(const std::string &ISBN) {
        //book tmp;
        //tmp.ISBN=ISBN;
        ISindex[ISBN]=num;
        std::string nums = std::to_string(num);
        nums = change(nums, 10);
        file.open("bookdata", std::ios::in | std::ios::out | std::ios::app);
        //索引，ISBN，书名，作者，关键词，单价，库存
        file << nums << " " << change(ISBN, 20) << " " << change(NU,60)<<" "<<change(NU,60)
        <<" "<<change(NU,60)<<" "<<change("0.00",13)<<" "<<change("0",10)<<std::endl;
        file.close();
        num++;
    }
    void reinitial(){
        {//num更新
            file.open("num", std::ios::in | std::ios::out);
            file.seekp(0);
            file<<num;
            file.close();
        }
    }
    bool checkkw(const std::string& kw0){
        //int i = 0;
        std::string kw = kw0+"|";
        std::set<std::string> set;
        std::string tmp;
        for (auto i : kw){
            if (i!='|') tmp += i;
            else {
                if(tmp.empty()||set.count(tmp))
                    return false;
                set.insert(tmp);
                tmp="";
            }
        }
        return true;
    }
    void changeISBN(const std::string &be, const std::string &af){
        int index = ISindex[be];
        file.open("bookdata", std::ios::in | std::ios::out);
        file.seekp(index*ONELINE+11);
        file<<change(af,lenISBN);
        file.close();
    }
    void changename(const std::string &isbn, const std::string &name){
        int index = ISindex[isbn];
        file.open("bookdata", std::ios::in | std::ios::out);
        file.seekp(index*ONELINE+11);
        file<<change(name,lenname);
        file.close();
        file.open("bookname");

    }
};

#endif //BOOKSTORE_BOOKDATA_H
