#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

typedef int item;

struct PriorLink
{
    int prior;
    item task;
    PriorLink* next = nullptr;
};

struct PriorQueue
{
    PriorLink* head = nullptr;
    
    bool is_empty()
    {
        return head == nullptr;
    }
    
    void enqueue(item task, int prior)
    {
        auto new_task = new PriorLink();
        new_task->prior = prior;
        new_task->task = task;
        
        if (is_empty() || head->prior < prior)
        {
            new_task->next = head;
            head = new_task;
        }
        else
        {
            auto c = head;
            
            while (true)
            {
                if (c->next == nullptr || c->next->prior < prior)
                {
                    new_task->next = c->next;
                    c->next = new_task;
                    break;
                }
                
                c = c->next;
            }
        }
    }
    
    void display()
    {
        if (is_empty()) return;
        auto c = head;
        
        while (true)
        {
            cout << "(" << c->task << ", " << c->prior << ")";
            if (c->next == nullptr) break;
            cout << " -> ";
            c = c->next;
        }
        
        cout << endl;
    }
    
    item get_front_task()
    {
        if (is_empty()) exit(-1);
        return head->task;
    }
    
    item dequeue()
    {
        auto t = get_front_task();
        auto n = head->next;
        delete head;
        head = n;
        return t;
    }
};

int main()
{
    auto q = PriorQueue();
    constexpr auto add = "dodaj";
    constexpr auto del = "usun";
    constexpr auto dis = "wyswietl";
    constexpr auto gft = "get_front_task";
    
    while (true)
    {
        string line;
        cout << endl << "polecenia:" << endl;
        cout << add << " [element] [priorytet]" << endl;
        cout << del << endl << dis << endl << gft << endl;
    
        getline(cin, line);
        
        if (line == del) q.dequeue();
        else if (line == dis) q.display();
        else if (line == gft) cout << q.get_front_task();
        else
        {
            vector<string> tokens;
            istringstream iss(line);
            for (string token; getline(iss, token, ' ');) tokens.push_back(token);
            
            if (tokens.size() == 3 && tokens[0] == add) q.enqueue(stoi(tokens[1]), stoi(tokens[2]));
        }
    }
    
    return 0;
}
