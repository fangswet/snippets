#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

typedef int item;

struct Link
{
    item data;
    Link* next = nullptr;
};

struct LinkedList
{
    Link* head = nullptr;
    
    bool is_empty()
    {
        return head == nullptr;
    }
    
    void add(item data)
    {
        auto link = new Link();
        link->data = data;
        link->next = head;
        head = link;
    }
    
    void remove(Link* p)
    {
        for (auto c = &head; *c != nullptr; c = &(*c)->next)
        {
            if (*c == p)
            {
                auto next = (*c)->next;
                delete *c;
                *c = next;
                return;
            }
        }
    }
    
    void display_list()
    {
        if (is_empty()) return;
        auto c = head;

        while (true)
        {
            cout << c->data;
            if (c->next == nullptr) break;
            cout << "->";
            c = c->next;
        }
        
        cout << endl;
    }
};

struct ListStack
{
    LinkedList list;
    
    bool is_empty()
    {
        return list.is_empty();
    }
    
    void push(item data)
    {
        return list.add(data);
    }
    
    item peek()
    {
        if (!is_empty()) return list.head->data;
        
        exit(-1);
    }
    
    item pop()
    {
        if (!is_empty())
        {
            auto i = list.head->data;
            list.remove(list.head);
            return i;   
        }
        
        exit(-1);
    }
};

enum class Sign { plus = 999999, minus, star, slash }; 

int main()
{
    constexpr int sz = 10;
    int arr[sz] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    auto ls = ListStack();
    
    for (int i = 0; i < sz; i++) ls.push(arr[i]);
    for (int i = 0; i < sz; i++) arr[i] = ls.pop();
    
    string line;
    getline(cin, line);
    istringstream iss(line);
    vector<string> v;
    
    for (string token; getline(iss, token, ' ');) v.push_back(move(token));

    for (string i : v)
    {
        if (i == "+") ls.push(ls.pop() + ls.pop());
        else if (i == "-")
        {
            auto t = ls.pop();
            ls.push(ls.pop() - t);
        }
        else if (i == "*") ls.push(ls.pop() * ls.pop());
        else if (i == "/")
        {
            auto t = ls.pop();
            ls.push(ls.pop()/ t);
        }
        else ls.push(stoi(i));
    }
    
    cout << ls.pop();

    return 0;
}




