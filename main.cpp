#include<stack>
#include"user.h"
#include"keyword.h"
int main() {
    user_store user;
    key_store key;
    std::stack<user_node> online;
    std::string order;
    std::cin>>order;
    while(std::cin.eof()) {
        if(order=="su") {
            std::string userid,password;
            std::cin>>userid;
            user_node temp=user.find(userid);
            User_id tem("root");
            if(temp.id==tem) {
                std::cin>>password;
                std::cin>>order;
                continue;
            }
            else {
                user_node now;
                now=online.top();
                if(now.Privilege>temp.Privilege) {
                    online.push(temp);
                    std::cin>>order;
                    continue;
                }
                std::cin>>password;
                User_id pass(password);
                if(pass==temp.password) {
                    online.push(temp);
                }
                std::cin>>order;
                continue;
            }
        }
        if(order=="lgout") {
            if(!online.empty()) {
                online.pop();
            }
            std::cin>>order;
            continue;
        }
        if(order=="register") {
            std::string userid,password,username;
            std::cin>>userid>>password>>username;
            user_node temp=user.find(userid);
            User_id tem("root");
            if(temp.id==tem) {
                User_id k(userid);
                user_node t(k,password,1);
                user.insert(t);
            }
            std::cin>>order;
            continue;
        }
        if(order=="passwd") {
            std::string userid,password,uword;
            std::cin>>userid;
            user_node temp=user.find(userid);
            User_id tem("root");
            if(temp.id==tem) {
                std::cin>>password>>uword;
                std::cin>>order;
                continue;
            }
            else {
                user_node now;
                now=online.top();
                if(now.Privilege>temp.Privilege) {
                    std::cin>>password;
                    user.del(temp.id);
                    temp.password=password;
                    user.insert(temp);
                }
                else {
                    std::cin>>uword>>password;
                    User_id pass(uword);
                    if(pass==temp.password) {
                        user.del(temp.id);
                        temp.password=password;
                        user.insert(temp);
                    }
                }
                std::cin>>order;
                continue;
            }
        }
        if(order=="useradd") {
            int k;
            std::string userid,password,username;
            std::cin>>userid>>password>>k>>username;
            user_node now;
            now=online.top();
            if(now.Privilege>=k) {
                user_node temp=user.find(userid);
                User_id tem("root");
                if(temp.id==tem) {
                    User_id m(userid);
                    user_node t(m,password,k);
                    user.insert(t);
                }
            }
            std::cin>>order;
            continue;
        }
        if(order=="delete") {
            std::string userid;

        }
    }
};
