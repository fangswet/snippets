#include <iostream>
#include <limits>

using namespace std;

typedef int item;
struct Link
{
    item data;
    Link* next = nullptr;
};

struct LLIterator
{
    Link* head;
    Link* current;
    int pos = 0;
    
    LLIterator(Link* head)
    {
        this->head = head;
        current = head;
    }
    
    bool has_next()
    {
        return current->next != nullptr;
    }
    
    item get_current()
    {
        return current->data;
    }
    
    item next()
    {
        if (has_next())
        {
            current = current->next;
            pos++;
        }
        
        return get_current();
    }
    
    void reset()
    {
        current = head;
    }
    
    int get_pos()
    {
        return pos;
    }
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
    
    void insert(item data, Link* p)
    {
        for (auto c = &head; *c != nullptr; c = &(*c)->next)
        {
            if (*c == p)
            {
                auto link = new Link();
                link->data = data;
                link->next = (*c)->next;
                delete *c;
                *c = link;
            }
        }
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
    
    Link* locate(item data)
    {
        for (auto c = head; c != nullptr; c = c->next)
            if (c->data == data) return c;
        
        return nullptr;
    }
    
    bool contain(item data)
    {
        return locate(data) != nullptr;
    }
    
    int length()
    {
        auto l = 0;
        for (auto c = head; c != nullptr; c = c->next) l++;
        
        return l;
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

    int pos_to_ind(Link* p)
    {
        int i = 0;
        
        for (auto c = head; c != nullptr; c = c->next)
        {
            if (c == p) return i;
            i++;
        }
        
        return -1;
    }
    
    Link* ind_to_pos(int i)
    {
        Link* l = nullptr;
        
        for (auto c = head; c != nullptr; c = c->next)
        {
            if (i-- == 0)
            {
                l = c;
                break;
            }
        }
        
        return l;
    }
    
    bool is_order()
    {
        if (is_empty()) return false;
        auto i = head->data;
        auto result = true;
        
        for (auto c = head->next; c != nullptr; c = c->next)
        {
            if (c->data < i)
            {
                result = false;
                break;
            }
            
            i = c->data;
        }
        
        if (!result)
        {
            i = head->data;
            result = true;
        
            for (auto c = head->next; c != nullptr; c = c->next)
            {
                if (c->data > i)
                {
                    result = false;
                    break;
                }
                
                i = c->data;
            } 
        }

        return result;
    }
    
    void revers()
    {
        Link* p = nullptr;
        Link* n = nullptr;
        
        for (auto c = head; c != nullptr; c = n)
        {
            n = c->next;
            c->next = p;
            p = c;
        }
        
        head = p;
    }
    
    LinkedList max_sub_list()
    {
        int index = 0;
        int search_index = 0;
        int longest_start = 0;
        int longest_length = 0;
        auto ongoing = false;
        
        if (!is_empty())
        {
            auto previous = head->data;
            for (auto c = head->next; c != nullptr; c = c->next)
            {
                if (c->data >= previous)
                {
                    if (!ongoing)
                    {
                        search_index = index;
                        ongoing = true;
                    }
                }
                else
                {
                    if (ongoing)
                    {
                        ongoing = false;
                        int length = index - search_index + 1;
                        if (length > longest_length)
                        {
                            longest_length = length;
                            longest_start = search_index;
                        }
                    }
                }
                
                index++;
                previous = c->data;
            } 
        }

        auto ll = LinkedList();
        int i = 0;
        for (auto c = head; i < longest_start + longest_length; c = c->next)
        {
            if (i >= longest_start) ll.add(c->data);
            i++;
        }
        
        ll.revers();
        return ll;
    }
    
    LLIterator getiterator()
    {
        return is_empty() ? nullptr : LLIterator(head);
    }
};

int main()
{
    int choice;
    LinkedList list;
    do {
        cout << "[0] Koniec" << endl;
        cout << "[1] Sprawdz czy lista jest pusta" << endl;
        cout << "[2] Dodaj element" << endl;
        cout << "[3] Usuń element" << endl;
        cout << "[4] Obróć listę" << endl;
        
        cin >> choice;
        switch (choice) {
            case 1:
                cout << "Lista jest " 
                    << (list.is_empty() ? "" : "nie") 
                    << "pusta" << endl;
                break;
            case 2:
                int i;
                cin >> i;
                list.add(i);
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            case 3:
                int i;
                cin >> i;
                list.remove(list.locate(i));
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            case 4:
                list.revers();
                break;
        }
        
        list.display_list();
    } while (choice != 0);
    return 0;
}


