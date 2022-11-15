#include <iostream>
#include <sstream>
#include <vector>
#include <utility>

typedef int item;
const int MAX_ELEMENTS = 10;

using namespace std;

struct ArrayStack 
{
    bool is_empty() 
    {
        return top == -1;
    }
    
    bool is_full() 
    {
        return top == MAX_ELEMENTS - 1;
    }
    
    void push(item item) 
    {
        array[is_full() ? top : ++top] = item;
    }
    
    item pop()
    {
        auto item = peek();
        top--;
        return item;
    }
    
    item peek() 
    {
        if (is_empty()) exit(-1);
        return array[top];
    }
    
    void display_array()
    {
        for (int i = 0; i <= top; i++)
        {
            cout << array[i] << " ";
        }
        
        cout << endl;
    }

private:
    item array[MAX_ELEMENTS];
    int top = -1;
};

struct Queue 
{
    bool is_empty() 
    {
        return length == 0;
    }
    
    bool is_full() 
    {
        return length == MAX_ELEMENTS;
    }
    
    void enqueue(item data) 
    {
        if (is_full()) dequeue();
        length++;
        array[rear] = data;
        cout << "inserted " << data << " at " << rear << endl;
        rear = rear < MAX_ELEMENTS - 1 ? rear + 1 : 0;
        cout << "front is now " << front << " rear " << rear << " length " << length << endl;
    }
    
    item dequeue() 
    {
        item item = get_front();
        length--;
        cout << "removed " << item << " from " << front << endl;
        front = front < MAX_ELEMENTS - 1 ? front + 1 : 0;
        cout << "front is now " << front << " rear " << rear << " length " << length << endl;
        return item;
    }
    
    item get_front() 
    {
        if (is_empty()) exit(-1);
        return array[front];
    }
    
    void display_array() 
    {
        for (int i = 0; i < MAX_ELEMENTS; i++)
        {
            cout << " | ";
            if (front < rear)
            {
                if (front <= i && i < rear) cout << array[i];
                else cout << "X";
            }
            else
            {
                if (i < rear || front <= i) cout << array[i];
                else cout << "X";
            }
        }
        
        cout << " | " << endl;
    }

private:
    item array[MAX_ELEMENTS];
    int front = 0;
    int rear = 0;
    int length = 0;
};

int main()
{
    ArrayStack* stacks[MAX_ELEMENTS];
    Queue* queues[MAX_ELEMENTS];
    
    for (string line; getline(cin, line);)
    {
        vector<string> tokens;
        istringstream iss(line);
        string cmd;
        int p1, p2;
        
        for (string token; getline(iss, token, ' ');)
        {
            tokens.push_back(move(token));
        }
        
        if (tokens.size() < 2) continue;
        
        cmd = tokens[0];
        try
        {
            p1 = stoi(tokens[1]);
        }
        catch (...) { continue; }
        
        
        if (tokens.size() == 2)
        {
            if (cmd == "print_s")
            {
                if (stacks[p1]->is_empty())
                    cout << "empty" << endl;
                else stacks[p1]->display_array();
            }
            else if (cmd == "pop")
            {
                if (stacks[p1]->is_empty())
                    cout << "error: stack is empty" << endl;
                else stacks[p1]->pop();
            }
            else if (cmd == "new_s")
                stacks[p1] = new ArrayStack();
            else if (cmd == "delete_s")
                delete stacks[p1];
            else if (cmd == "new_q")
                queues[p1] = new Queue();
            else if (cmd == "dequeue")
            {
                if (queues[p1]->is_empty())
                    cout << "error: queue is empty" << endl;
                else queues[p1]->dequeue();
            }
            else if (cmd == "delete_q")
                delete queues[p1];
            else if (cmd == "print_q")
            {
                if (queues[p1]->is_empty())
                    cout << "empty" << endl;
                else queues[p1]->display_array();
            }
        }
        else if (tokens.size() == 3)
        {
            try
            {
                p2 = stoi(tokens[2]);
            }
            catch (...) { continue; }
            
            if (cmd == "push")
            {
                if (stacks[p1]->is_full())
                    cout << "error: stack is full" << endl;
                else stacks[p1]->push(p2);   
            }
            else if (cmd == "stack->stack")
                stacks[p2]->push(stacks[p1]->pop());
            else if (cmd == "enqueue")
            {
                if (queues[p1]->is_full())
                    cout << "error: queue is full" << endl;
                else queues[p1]->enqueue(p2);
            }
                        else if (cmd == "stack->queue")
            {
                if (stacks[p1]->is_empty() || queues[p2]->is_full())
                    cout << "error: wrong command" << endl;
                else queues[p2]->enqueue(stacks[p1]->pop());
            }
            else if (cmd == "queue->queue")
            {
                if (queues[p1]->is_empty() || queues[p2]->is_full())
                    cout << "error: wrong command" << endl;
                else queues[p2]->enqueue(queues[p1]->dequeue());
            }
            else if (cmd == "queue->stack")
            {
                if (stacks[p2]->is_full() || queues[p1]->is_empty())
                    cout << "error: wrong command" << endl;
                else stacks[p2]->push(queues[p1]->dequeue());
            }
        }
    }
    
    return 0;
}



