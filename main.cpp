#include<vector>
#include<cmath>
#include"user.h"
#include"keyword.h"
#include "author.h"
#include "bookname.h"
#include "book.h"

struct logging {
    user_node userr;
    std::string selecting;
};

int main() {
    user_store user;
    key_store key;
    author_store author;
    bookname_store bookname;
    book_store book;
    std::vector<logging> online;
    std::string order;
    std::cin >> order;
    while (!std::cin.eof()) {
        if (order == "su") {
            std::string userid, password;
            std::cin >> userid;
            user_node temp = user.find(userid);
            User_id tem("root");
            if (temp.id == tem) {
                std::cin >> password;
                std::cin >> order;
                continue;
            } else {
                logging now;
                now = online.back();
                if (now.userr.Privilege > temp.Privilege) {
                    logging p;
                    p.userr = temp;
                    p.selecting = "";
                    online.push_back(p);
                    std::cin >> order;
                    continue;
                }
                std::cin >> password;
                User_id pass(password);
                if (pass == temp.password) {
                    logging pp;
                    pp.userr = temp;
                    pp.selecting = "";
                    online.push_back(pp);
                }
                std::cin >> order;
                continue;
            }
        }
        if (order == "lgout") {
            if (!online.empty()) {
                online.pop_back();
            }
            std::cin >> order;
            continue;
        }
        if (order == "register") {
            std::string userid, password, username;
            std::cin >> userid >> password >> username;
            user_node temp = user.find(userid);
            User_id tem("root");
            if (temp.id == tem) {
                User_id k(userid);
                user_node t(k, password, 1);
                user.insert(t);
            }
            std::cin >> order;
            continue;
        }
        if (order == "passwd") {
            std::string userid, password, uword;
            std::cin >> userid;
            user_node temp = user.find(userid);
            User_id tem("root");
            if (temp.id == tem) {
                std::cin >> password >> uword;
                std::cin >> order;
                continue;
            } else {
                logging now;
                now = online.back();
                if (now.userr.Privilege > temp.Privilege) {
                    std::cin >> password;
                    user.del(temp.id);
                    temp.password = password;
                    user.insert(temp);
                } else {
                    std::cin >> uword >> password;
                    User_id pass(uword);
                    if (pass == temp.password) {
                        user.del(temp.id);
                        temp.password = password;
                        user.insert(temp);
                    }
                }
                std::cin >> order;
                continue;
            }
        }
        if (order == "useradd") {
            int k;
            std::string userid, password, username;
            std::cin >> userid >> password >> k >> username;
            logging now;
            now = online.back();
            if (now.userr.Privilege >= k) {
                user_node temp = user.find(userid);
                User_id tem("root");
                if (temp.id == tem) {
                    User_id m(userid);
                    user_node t(m, password, k);
                    user.insert(t);
                }
            }
            std::cin >> order;
            continue;
        }
        if (order == "delete") {
            std::string userid;
            std::cin >> userid;
            bool has = 0;
            User_id t(userid);
            for (auto itea = online.begin(); itea != online.end(); itea++) {
                if ((itea->userr).id == t) has = 1;
            }
            if (!has) {
                user.del(userid);
            }
            std::cin >> order;
            continue;
        }
        if (order == "show") {
            std::cin >> order;
            if (order == "finance") {

            }
            if (order[0] == '-') {

            } else {

            }
        }
        if (order == "buy") {
            std::string is, qu;
            std::cin >> is >> qu;
            bookbook x(is);
            book_node k = book.find(x);
            int Quan = 0;
            bool sign = 1;
            for (int j = 0; j < qu.size(); j++) {
                if (qu[j] >= '0' && qu[j] <= '9') Quan = Quan * 10 + qu[j] - '0';
                else {
                    sign = 0;
                    break;
                }
            }
            if (sign) {
                k.Quantity -= Quan;
                std::cout << Quan * k.Price << std::endl;
                book.del(is);
                book.insert(k);
            }
        }
        if (order == "select") {
            std::string is;
            std::cin >> is;
            bookbook x(is);
            book_node k = book.find(x);
            if (k.Bookname == "" && k.Author == "") {
                book.del(is);
                book.insert(k);
                logging t = online.back();
                online.pop_back();
                t.selecting = is;
                online.push_back(t);
            }
        }
        if (order == "modify") {
            std::cin >> order;
            if (order[0] == '-') {
                if (!online.empty()) {
                    logging t;
                    t = online.back();
                    if (t.selecting != "") {
                        bookbook x(t.selecting);
                        book_node k = book.find(x);
                        book.del(k.index);
                        while (order[0] == '-') {
                            int j;
                            if (order[1] == 'I') j = 6;
                            if (order[1] == 'n') j = 7;
                            if (order[1] == 'a') j = 10;
                            if (order[1] == 'k') j = 11;
                            if (order[1] == 'p') {
                                int Quan = 0;
                                int count = 0;
                                bool sign = 1;
                                for (int g = 7; g < order.size(); g++) {
                                    if (order[g] >= '0' && order[g] <= '9') {
                                        Quan = Quan * 10 + order[g] - '0';
                                        if (count != 0) count++;
                                    } else if (order[g] == '.') {
                                        count = 1;
                                    } else {
                                        sign = 0;
                                        break;
                                    }
                                }
                                if (sign) {
                                    double kk = Quan / pow(10, count - 1);
                                    k.Price = kk;
                                }
                            } else {
                                std::string nn = "";
                                for (int g = j; g < order.size(); g++) {
                                    if (order[g] != '"')
                                        nn += order[g];
                                }
                                if(j==6) {
                                    bookbook tt(nn);
                                    if(!(k.index==tt)) {
                                        k.index=tt;
                                    }
                                }
                                if(j==7) {
                                    std::string gg=k.index.name_;
                                    bookname_node tt(k.Bookname,gg);
                                    bookname.del(tt);
                                    k.Bookname=nn;
                                    tt.index=nn;
                                    bookname.insert(tt);
                                }
                                if(j==10) {
                                    std::string gg=k.index.name_;
                                    author_node tt(k.Author,gg);
                                    author.del(tt);
                                    k.Author=nn;
                                    tt.index=nn;
                                    author.insert(tt);
                                }
                                if(j==11) {

                                }
                            }
                            std::cin>>order;
                        }
                        book.insert(k);
                    }
                }

            }
        }
        if (order == "import") {
            if (!online.empty()) {
                logging t;
                t = online.back();
                if (t.selecting != "") {
                    bookbook x(t.selecting);
                    book_node k = book.find(x);
                    std::string quan;
                    std::cin >> quan;
                    if (quan[0] != '-') {
                        int Quan = 0;
                        bool sign = 1;
                        for (int j = 0; j < quan.size(); j++) {
                            if (quan[j] >= '0' && quan[j] <= '9') Quan = Quan * 10 + quan[j] - '0';
                            else {
                                sign = 0;
                                break;
                            }
                        }
                        double cost;
                        std::cin >> cost;
                        if (sign && cost > 0) {
                            k.Quantity += Quan;
                            book.del(x);
                            book.insert(k);
                        }
                    }
                }
            }
            std::cin >> order;
            continue;
        }
        if (order == "quit") {
            online.clear();
        }
        if (order == "exit") {
            online.clear();
        }
        if (order == "log") {

        }
    }
}

