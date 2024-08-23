#include<bits/stdc++.h>
using namespace std;
#define ll long long

class SymbolInfo
{
public:
    string name;
    string type;
    string sub_type;
    bool is_array;
    int arr_size;
    
    bool is_function;
    bool is_defined_yet;
    string return_type;
    vector<string>parameter_list; 

    string code;
    string name_with_id;

    SymbolInfo *next;
    
    SymbolInfo()
    {
        next = nullptr;
        name = "";
        type = "";
        sub_type = "";
        is_array = 0;
        arr_size = -1;
        is_function = 0;
        is_defined_yet = 0;
        return_type = "";
        code = "";
        name_with_id = "";
    }
    SymbolInfo(string _name,string _type)
    {
        name = _name;
        type = _type;
        sub_type = "";
        next = nullptr;
        is_array = 0;
        arr_size = -1;
        is_function = 0;
        is_defined_yet = 0;
        return_type = "";
        code = "";
        name_with_id = "";
    }
    SymbolInfo(string _name,string _type,string _sub_type)
    {
        name = _name;
        type = _type;
        sub_type = _sub_type;
        next = nullptr;
        is_array = 0;
        arr_size = -1;
        is_function = 0;
        is_defined_yet = 0;
        return_type = "";
        code = "";
        name_with_id = "";
    }

    void set_name(string name)
    {
        this->name = name;
    }
    string get_name()
    {
        return this->name;
    }

    void set_type(string type)
    {
        this->type = type;
    }
    string get_type()
    {
        return this->type;
    }
    void set_sub_type(string type)
    {
        this->sub_type = type;
    }
    string get_sub_type()
    {
        return this->sub_type;
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

            symbol_info[assigned_bucket_no]->sub_type = rhs.sub_type;
            symbol_info[assigned_bucket_no]->is_array = rhs.is_array;
            symbol_info[assigned_bucket_no]->arr_size = rhs.arr_size;
            symbol_info[assigned_bucket_no]->is_function = rhs.is_function;
            symbol_info[assigned_bucket_no]->is_defined_yet = rhs.is_defined_yet;
            symbol_info[assigned_bucket_no]->return_type = rhs.return_type;
            symbol_info[assigned_bucket_no]->parameter_list = rhs.parameter_list; 
            symbol_info[assigned_bucket_no]->code = rhs.code;
            symbol_info[assigned_bucket_no]->name_with_id = rhs.name_with_id; 


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
                   // cout<<"<"<<temp->get_name()<<","<<temp->get_type()<<"> "<<"already exists in current ScopeTable\n";
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
            prev->next->sub_type = rhs.sub_type;
            prev->next->is_array = rhs.is_array;
            prev->next->arr_size = rhs.arr_size;
            prev->next->is_function = rhs.is_function;
            prev->next->is_defined_yet = rhs.is_defined_yet;
            prev->next->return_type = rhs.return_type;
            prev->next->parameter_list = rhs.parameter_list; 
            prev->next->code = rhs.code;
            prev->next->name_with_id = rhs.name_with_id; 


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

    void print(FILE *fp)
    {
        fprintf(fp,"Scope Table # %d\n",id);

	
	//cout<<"ScopeTable # "<<id<<endl;
        for(int i=0; i<number_of_bucket; i++)
        {
            //cout<<i<<" --> ";
            SymbolInfo *temp = symbol_info[i];

            if(temp != nullptr)
            {
            
                fprintf(fp,"%d-->",i);
            
                while(temp != nullptr)
                {
                    fprintf(fp,"<%s : %s>", temp->get_name().c_str(),temp->get_type().c_str());

                    //cout<<"<"<<temp->get_type()<<":"<<temp->get_name()<<"> ";
                    temp = temp->next;
                }
            
                fprintf(fp,"\n");
            }
            //cout<<endl;
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




//int ScopeTable::assign_id = 1;


//**************************************************************************//

class SymbolTable
{
public:
    ScopeTable *current_scope_table;
    SymbolTable()
    {
        current_scope_table = new ScopeTable(101);
    }
    void enter_scope()
    {
        ScopeTable *temp = new ScopeTable(7);
        if(current_scope_table == nullptr)
            current_scope_table = temp;
        else
        {
            temp->set_parent_scope(current_scope_table);
            current_scope_table = temp;
        }

        //cout<<"ScopeTable with id "<<current_scope_table->get_id()<<" created\n";
    }
    void exit_scope()
    {
        ScopeTable *temp = current_scope_table;
        if(temp == nullptr)
            return;

        //cout<<"ScopeTable with id "<<current_scope_table->get_id()<<" removed\n";

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

    int my_look_up_id(string name)
    {
        SymbolInfo* ret = nullptr;
        ScopeTable *temp = current_scope_table;
        while(temp != nullptr)
        {
            ret = temp->my_look_up(name);
            if(ret != nullptr)
                return temp->get_id();
            temp = temp->get_parent_scope();
        }
        return -1;
    }

    SymbolInfo *my_look_up_current(string name)
    {
        SymbolInfo* ret = nullptr;
        ScopeTable *temp = current_scope_table;
        if(temp != nullptr)
        {
            ret = temp->my_look_up(name);
            if(ret != nullptr)
                return ret;
        }
        return nullptr;
    }
    void print_current_scope_table(FILE *fp)
    {
        if(current_scope_table != nullptr)
            current_scope_table->print(fp);
    }

    void print_all_scope_table(FILE *fp)
    {
        ScopeTable *temp = current_scope_table;
        while(temp != nullptr)
        {
            temp->print(fp);
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

