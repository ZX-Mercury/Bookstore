//
// Created by laohu on 2023/12/23.
//

#ifndef BOOKSTORE_BOOKDATA_H
#define BOOKSTORE_BOOKDATA_H

class bookdata{
private:
    std::fstream file;
public:
    struct book{
        std::string ISBN;
        std::string bookname, author;
        std::vector<std::string> keyword;
        int quantity=0,price=0;
    };
    bookdata()=default;
    void initialise(){
        file.open("bookdata",std::ios::out);
        file.close();
    }

};
#endif //BOOKSTORE_BOOKDATA_H
