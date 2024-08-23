#include<bits/stdc++.h>
using namespace std;
#define ll long long

//***************************************************************************//

class SymbolInfo
{
private:
    string name;
    string type;
public:
    SymbolInfo *next;
    SymbolInfo()
    {
        next = nullptr;
    }
    void set_name(string name)
    {
        this->name = name;
    }
    string get_name()const
    {
        return this->name;
    }

    void set_type(string type)
    {
        this->type = type;
    }
    string get_type()const
    {
        return this->type;
    }
    ~SymbolInfo()
    {

    }
};

//****************************************************************//

class ScopeTable
{
    ll base = 259;
    ll MOD;
    static int assign_id;
    int number_of_bucket,id,bucket_number,position_in_bucket;
    SymbolInfo **symbol_info;
    ScopeTable *parentScope;


public:


    ScopeTable(int n)
    {
        number_of_bucket = n;
        MOD = n;
        id = assign_id++;
        parentScope = nullptr;
        symbol_info = new SymbolInfo*[n];
        for(int i=0; i<n; i++)
            symbol_info[i] = nullptr;
    }

    bool my_insert(SymbolInfo rhs)
    {
        int assigned_bucket_no = hash_function(rhs.get_name());

        bucket_number = assigned_bucket_no;

        if(symbol_info[assigned_bucket_no] == nullptr)
        {
            symbol_info[assigned_bucket_no] = new SymbolInfo();
            symbol_info[assigned_bucket_no]->set_name(rhs.get_name());
            symbol_info[assigned_bucket_no]->set_type(rhs.get_type());

            position_in_bucket = 0;

            return true;
        }
        else
        {
            SymbolInfo *temp = symbol_info[assigned_bucket_no];
            SymbolInfo *prev = nullptr;
            int position = 0;
            while(temp != nullptr)
            {
                if(temp->get_name() == rhs.get_name())
                {
                    cout<<"<"<<temp->get_name()<<","<<temp->get_type()<<"> "<<"already exists in current ScopeTable\n";
                    return false;
                }
                else
                {
                    prev = temp;
                    temp = temp->next;
                }

                position++;
            }
            prev->next = new SymbolInfo();
            prev->next->set_name(rhs.get_name());
            prev->next->set_type(rhs.get_type());

            position_in_bucket = position;

            return true;
        }

    }

    SymbolInfo* my_look_up(string name)
    {
        int assigned_bucket_no = hash_function(name);

        bucket_number = assigned_bucket_no;

        if(symbol_info[assigned_bucket_no] == nullptr)
        {
            return nullptr;
        }
        else
        {
            SymbolInfo *temp = symbol_info[assigned_bucket_no];

            int position = 0;

            while(temp != nullptr)
            {
                if(temp->get_name() == name)
                {
                    position_in_bucket = position;
                    return temp;
                }
                else
                {
                    temp = temp->next;
                }
                position++;
            }

            return nullptr;
        }
    }

    bool my_delete(string name)
    {
        int assigned_bucket_no = hash_function(name);

        bucket_number = assigned_bucket_no;

        if(symbol_info[assigned_bucket_no] == nullptr)
        {
            return false;
        }
        else
        {
            SymbolInfo *temp = symbol_info[assigned_bucket_no];
            SymbolInfo *prev = nullptr;

            int position = 0;

            while(temp != nullptr)
            {
                if(temp->get_name() == name)
                {
                    break;
                }
                else
                {
                    prev = temp;
                    temp = temp->next;
                }
                position++;
            }

            if(temp == nullptr)
                return false;

            if(prev == nullptr)
            {
                symbol_info[assigned_bucket_no] = temp->next;
            }
            else
            {
                prev->next = temp->next;
            }

            position_in_bucket = position;

            delete temp;
            return true;

        }

    }

    void print()
    {
        cout<<"ScopeTable # "<<id<<endl;

        for(int i=0; i<number_of_bucket; i++)
        {
            cout<<i<<" --> ";
            SymbolInfo *temp = symbol_info[i];
            while(temp != nullptr)
            {
                cout<<"<"<<temp->get_name()<<":"<<temp->get_type()<<"> ";
                temp = temp->next;
            }
            cout<<endl;
        }
    }

    void print_info()
    {
        cout<<id<<" at position "<<bucket_number<<","<<position_in_bucket<<"\n";
    }
    void partial_print()
    {
        cout<<bucket_number<<","<<position_in_bucket;
    }

    ScopeTable* get_parent_scope()
    {
        return parentScope;
    }

    void set_parent_scope(ScopeTable *rhs)
    {
        parentScope = rhs;
    }

    int get_id()
    {
        return id;
    }

    int hash_function(string s)
    {
        ll hash_value = 0;
        ll pwr = 1LL;

        for(int i=0; i<s.size(); i++)
        {
            hash_value = (hash_value + (ll)(s[i])*pwr)%MOD;
            pwr = (pwr%MOD*base%MOD)%MOD;
        }
        return (int)hash_value;
    }
    ~ScopeTable()
    {
        for(int i=0;i<number_of_bucket;i++)
        {
            SymbolInfo *curr = symbol_info[i];
            SymbolInfo *temp;

            while(curr != nullptr)
            {
                temp = curr->next;
                delete curr;
                curr = temp;
            }
        }

        delete []symbol_info;

    }
};




int ScopeTable::assign_id = 1;


//**************************************************************************//

class SymbolTable
{
public:
    ScopeTable *current_scope_table;
    SymbolTable()
    {
        current_scope_table = nullptr;
    }
    void enter_scope(int n)
    {
        ScopeTable *temp = new ScopeTable(n);
        if(current_scope_table == nullptr)
            current_scope_table = temp;
        else
        {
            temp->set_parent_scope(current_scope_table);
            current_scope_table = temp;
        }

        cout<<"ScopeTable with id "<<current_scope_table->get_id()<<" created\n";
    }
    void exit_scope()
    {
        ScopeTable *temp = current_scope_table;
        if(temp == nullptr)
            return;

        cout<<"ScopeTable with id "<<current_scope_table->get_id()<<" removed\n";

        current_scope_table = current_scope_table->get_parent_scope();
        delete temp;
    }
    bool my_insert(SymbolInfo rhs)
    {
        bool check = current_scope_table->my_insert(rhs);
        return check;
    }
    bool my_remove(string name)
    {
        bool check = current_scope_table->my_delete(name);
        return check;
    }
    SymbolInfo *my_look_up(string name)
    {
        SymbolInfo* ret = nullptr;
        ScopeTable *temp = current_scope_table;
        while(temp != nullptr)
        {
            ret = temp->my_look_up(name);
            if(ret != nullptr)
                return ret;
            temp = temp->get_parent_scope();
        }
        return nullptr;
    }
    void print_current_scope_table()
    {
        if(current_scope_table != nullptr)
            current_scope_table->print();
    }

    void print_all_scope_table()
    {
        ScopeTable *temp = current_scope_table;
        while(temp != nullptr)
        {
            temp->print();
            temp = temp->get_parent_scope();
        }
    }
    void print_info()
    {
        current_scope_table->print_info();
    }
    void partial_print()
    {
        current_scope_table->partial_print();
    }
    ~SymbolTable()
    {
        ScopeTable *curr = current_scope_table,*temp;
        while(curr != nullptr)
        {
            temp = curr->get_parent_scope();
            delete curr;
            curr = temp;
        }

    }
};



//********************************************************************//



int main()
{
    freopen("input.txt","r",stdin);
    freopen("out.txt","w",stdout);

    int n;
    cin>>n;
    char c;
    string name,type;

    SymbolTable symbol_table;
    symbol_table.current_scope_table = new ScopeTable(n);

    while(cin>>c)
    {
        if(c == 'I')
        {
            cin>>name>>type;
            SymbolInfo rhs;
            rhs.set_name(name);
            rhs.set_type(type);

            bool check = symbol_table.my_insert(rhs);

            if(check)
            {
                cout<<"I "<<name<<" "<<type<<endl;
                cout<<"Inserted in ScopeTable# ";
                symbol_table.print_info();

            }

        }
        else if(c == 'L')
        {
            cin>>name;
            SymbolInfo *check = symbol_table.my_look_up(name);

            cout<<"L "<<name<<endl;

            if(check == nullptr)
            {
                cout<<"not found\n";
            }
            else
            {
                cout<<"Found in ScopeTable# ";
                symbol_table.print_info();
            }
        }
        else if(c == 'D')
        {
            cin>>name;
            bool check = symbol_table.my_remove(name);
            cout<<"D "<<name<<endl;
            if(check)
            {
                cout<<"Found in ScopeTable# ";
                symbol_table.print_info();
                cout<<"Deleted entry at ";
                symbol_table.partial_print();
                cout<<" from current ScopeTable\n";
            }
            else
            {
                cout<<"not found\n";
                cout<<name<<" not found\n";
            }
        }
        else if(c == 'P')
        {
            char ch;
            cin>>ch;
            if(ch == 'A')
            {
                cout<<"P A"<<endl;
                symbol_table.print_all_scope_table();
            }
            else
            {
                cout<<"P C"<<endl;
                symbol_table.print_current_scope_table();
            }
        }
        else if(c == 'S')
        {
            cout<<"S"<<endl;
            symbol_table.enter_scope(n);
        }
        else if(c == 'E')
        {
            cout<<"E"<<endl;
            symbol_table.exit_scope();
        }

    }

    return 0;
}
