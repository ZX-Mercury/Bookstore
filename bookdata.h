//
// Created by laohu on 2023/12/23.
//

#ifndef BOOKSTORE_BOOKDATA_H
#define BOOKSTORE_BOOKDATA_H

class bookdata {
private:
    std::fstream file;
    int num = 0;
    const std::string NU = "bucunzai";
public:
    struct book {
        std::string ISBN;
        std::string bookname, author;
        std::vector<std::string> keyword;
        int quantity = 0, price = 0;
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

    std::unordered_map<std::string, int> cut (std::string ){
        x
    };

    void initialise() {
        file.open("num", std::ios::in | std::ios::out);
        if(!file.is_open()) {
            file.open("num", std::ios::out);
        }
        else {
            std::string nums;
            getline(file,nums);
            num=std::stoi(nums);
            std::cout<<nums;
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
};

#endif //BOOKSTORE_BOOKDATA_H
