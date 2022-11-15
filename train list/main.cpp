#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

typedef int wagon;

struct Car
{
    Car(wagon n) : number(n) { }
    
    wagon number;
    Car* next = nullptr;
    Car* prev = nullptr;
};

struct Train
{
    Car* first = nullptr;
    Car* last = nullptr;
    
    bool is_empty()
    {
        return first == nullptr;
    }
    
    void join(wagon w)
    {
        auto c = new Car(w);
        
        if (!is_empty())
        {
            c->prev = last;
            last->next = c;
            last = c;
        }
        else first = last = c;
    }
    
    void detach()
    {
        if (is_empty()) return;
        
        auto l = last;
        last = last->prev;
        if (last == nullptr) first = nullptr;
        else last->next = nullptr;
        delete l;
    }
    
    void reverse()
    {
        auto c = first;

        for (auto c = first; c != nullptr; c = c->prev) 
            swap(c->next, c->prev);
        
        swap(first, last);
    }
    
    void concatenate(Train t)
    {
        if (t.is_empty()) return;
        
        last->next = t.first;
        t.first->prev = last;
        last = t.last;
    }
    
    void display()
    {
        for (auto c = first; c != nullptr; c = c->next) 
            cout << c->number << "->";
            
        cout << endl;
    }
};

int main()
{
    Train trains[100];
    
    while (true)
    {
        string line;
        vector<string> tokens;
        getline(cin, line);
        istringstream iss(line);
        
        for (string token; getline(iss, token, ' ');) tokens.push_back(token);
        
        if (tokens.size() < 2) continue;
        Train& train = trains[stoi(tokens[1])];
        
        if (tokens[0] == "p") train.display();
        else if (tokens[0] == "r") train.reverse();
        else if (tokens[0] == "d") train.detach();
        if (tokens.size() < 3) continue;
        
        if (tokens[0] == "j") train.join(stoi(tokens[2]));
        else if (tokens[0] == "c") train.concatenate(trains[stoi(tokens[2])]);
    }

    return 0;
}

