#include <stdlib.h>
#include<bits/stdc++.h>
using namespace std;
struct table
{
    string *column_name;
    int column;
    int entries;
    int entry_size;
    string **column_data;
};
void add_column(table *cur,string s)
{
    int i=0,j=0,n=s.length();
    cur->column=0;
    string temp;
    while(j<n)
    {
        temp="";
        while(j<n&&s[j]==' ')
            ++j;
        while(j<n&&s[j]!=',')
            temp+=s[j++];
        if(temp!="")
        {
            ++(cur->column);
        }
        ++j;
    }
    cur->column_name=new string[cur->column];
    j=0;
    while(j<n)
    {
        temp="";
        while(j<n&&s[j]==' ')
            ++j;
        while(j<n&&s[j]!=',')
            temp+=s[j++];
        if(temp!="")
            cur->column_name[i++]=temp;
            ++j;
    }
    cur->entries=0;
    cur->entry_size=1;
    cur->column_data=new string*[cur->column];
    for(i=0;i<(cur->column);++i)
            cur->column_data[i]=new string[1];
}
void add_entry(table *cur,string s)
{
    if((cur->entries)==(cur->entry_size))//vector implementation
    {
        (cur->entry_size)<<=1;
        for(int i=0;i<(cur->column);++i)
        {
            string *temp=new string[cur->entry_size];
            for(int j=0;j<(cur->entries);++j)
            {
                temp[j]=cur->column_data[i][j];
            }
            cur->column_data[i]=temp;
        }
    }
    int i=0,j=0,n=s.length();
    string temp;
    while(j<n)
    {
        temp="";
        while(j<n&&s[j]==' ')
            ++j;
        while(j<n&&s[j]!=',')
            temp+=s[j++];
        if(temp!="")
            cur->column_data[i++][cur->entries]=temp;
            ++j;
    }
    ++(cur->entries);
}
struct sort_help
{
    string s;
    int index;
};
void merge_sort(sort_help *cur,int l,int r)
{
    if(l==r)
        return;
    int mid=(l+r)>>1;
    merge_sort(cur,l,mid);
    merge_sort(cur,mid+1,r);
    sort_help *temp=new sort_help[r-l+1];
    int k=0,i=l,j=mid+1;
    while((i<=mid)&&(j<=r))
    {
        if(cur[i].s<cur[j].s)
            temp[k++]=cur[i++];
        else
            temp[k++]=cur[j++];
    }
    while((i<=mid))
        temp[k++]=cur[i++];
    while((j<=r))
        temp[k++]=cur[j++];
    for(i=l,j=0;j<k;++i,++j)
        cur[i]=temp[j];
}
void sort_column(table *cur,int index)
{
    sort_help *temp=new sort_help[cur->entries];
    for(int i=0;i<(cur->entries);++i)
    {
        temp[i].s=cur->column_data[index][i];
        temp[i].index=i;
    }
    merge_sort(temp,0,(cur->entries)-1);
    table *t=new table;
    t->column_data=new string*[cur->column];
    for(int i=0;i<(cur->column);++i)
        t->column_data[i]=new string[cur->entries];
    for(int i=0;i<(cur->entries);++i)
    {
        for(int j=0;j<(cur->column);++j)
        {
            t->column_data[j][i]=cur->column_data[j][temp[i].index];
        }
    }
    for(int i=0;i<(cur->entries);++i)
    {
        for(int j=0;j<(cur->column);++j)
        {
            cur->column_data[j][i]=t->column_data[j][i];
        }
    }
}
int find_columindex(table *cur,string s)
{
    for(int i=0;i<(cur->column);++i)
        if((cur->column_name[i])==s)
            return i;
    return -1;
}
int binary_sl(table *cur,string s,int index)
{
    int l=0,r=(cur->entries)-1,f=-1;
    while(l<=r)
    {
        int mid=(l+r)>>1;
        if((cur->column_data[index][mid])==s)
        {
            f=mid;
            r=mid-1;
        }
        else if((cur->column_data[index][mid])>s)
            r=mid-1;
        else
            l=mid+1;
    }
    return f;
}
int binary_sh(table *cur,string s,int index)
{
    int l=0,r=(cur->entries)-1,f=-1;
    while(l<=r)
    {
        int mid=(l+r)>>1;
        if((cur->column_data[index][mid])==s)
        {
            f=mid;
            l=mid+1;
        }
        else if((cur->column_data[index][mid])>s)
            r=mid-1;
        else
            l=mid+1;
    }
    return f;
}
void getfile(table *cur,string s)
{
  std::ifstream file(s);
  std::string str;
  bool ch=0;
  while (std::getline(file, str))
  {
    if(ch)
        add_entry(cur,str);
    else
    {
        add_column(cur,str);
        ch=1;
    }
  }
}
int main()
{
    while(1)
    {
        string s;
        getline(cin,s);
        if(s[int(s.length())-1]!=';')
        {
            cout<<"Invalid command\n";
            continue;
        }
        else
        {
            s.pop_back();
        }
        if(s=="QUIT")
            exit(0);
        if(s=="CLEAR")
        {
            system("cls");
            continue;
        }
        else
        {
            string temp="";
            int i,n=s.length();
            for(i=0;i<n;++i)
            {
                if(s[i]==' ')
                    break;
                temp+=s[i];
            }
            if(temp!="SHOW")
            {
                cout<<"INVALID COMMAND\n";
                continue;
            }
            ++i;
            temp="";
            if(i>=n)
            {
                cout<<"INVALID COMMAND\n";
                continue;
            }
            bool ch=0;
            for(;i<n;++i)
            {
                if(s[i]==' ')
                    break;
                if(s[i]=='=')
                {
                    ch=1;
                    break;
                }
                temp+=s[i];
            }
            ++i;
            if(ch)
            {
                if((i>=n)||(temp!="CourseID"))
                {
                    cout<<"INVALID COMMAND\n";
                    continue;
                }
                temp="";
                for(;i<n;++i)
                {
                    if(s[i]==' ')
                        break;
                    temp+=s[i];
                }
                while((i<n)&&(s[i]==' '))
                    ++i;
                if(i<n)
                {
                    cout<<"INVALID COMMAND\n";
                    continue;
                }
                table *t1=new table;
                table *t2=new table;
                getfile(t1,"grades.txt");
                sort_column(t1,1);
                int l=binary_sl(t1,temp,1);
                if(l==-1)
                {
                    cout<<"No student exists with given course id\n";
                    continue;
                }
                int r=binary_sh(t1,temp,1);
                getfile(t2,"csestudents.txt");
                sort_column(t2,0);
                cout<<setw(5)<<""<<setw(35)<<left<<"RollNo"<<setw(35)<<left<<"StudentName"<<setw(35)<<left<<"Grade"<<"\n";
                for(int u=l;u<=r;++u)
                {
                    cout<<setw(5)<<""<<setw(35)<<left<<t1->column_data[0][u];
                    cout<<setw(35)<<left<<t2->column_data[1][binary_sl(t2,t1->column_data[0][u],0)];
                    cout<<setw(35)<<left<<t1->column_data[2][u]<<"\n";
                }
            }
            else
            {
                if((temp!="csestudents")&&(temp!="courses")&&(temp!="grades"))
                {
                    cout<<"Entered file does not exist\n";
                    continue;
                }
                table *t=new table;
                getfile(t,temp+".txt");
                while((i<n)&&s[i]==' ')
                    ++i;
                if(i>=n)
                {
                    for(int o=0;o<(t->column);++o)
                    {
                        if(o)
                            cout<<setw(35)<<left<<(t->column_name[o]);
                        else
                            cout<<setw(5)<<""<<setw(35)<<left<<(t->column_name[o]);
                    }
                    cout<<"\n";
                    for(int o=0;o<(t->entries);++o)
                    {
                        for(int j=0;j<(t->column);++j)
                        {
                            if(j)
                                cout<<setw(35)<<left<<(t->column_data[j][o]);
                            else
                                cout<<setw(5)<<""<<setw(35)<<left<<(t->column_data[j][o]);
                        }
                        cout<<"\n";
                    }
                }
                else
                {
                    temp="";
                    for(;i<n;++i)
                    {
                        if(s[i]==' ')
                            break;
                        temp+=s[i];
                    }
                    if((temp!="WHERE")&&(temp!="SORTBY"))
                    {
                        cout<<"Invalid command\n";
                        continue;
                    }
                    if(temp=="SORTBY")
                    {
                        temp="";
                        while((i<n)&&s[i]==' ')
                            ++i;
                        if(i>=n)
                        {
                            cout<<"No key entered\n";
                            continue;
                        }
                        for(;i<n;++i)
                        {
                            if(s[i]==' ')
                                break;
                            temp+=s[i];
                        }
                        while((i<n)&&s[i]==' ')
                            ++i;
                        if(i<n)
                        {
                            cout<<"Invalid command\n";
                            continue;
                        }
                        int e=find_columindex(t,temp);
                        if(e==-1)
                        {
                            cout<<"No such column exists\n";
                            continue;
                        }
                        sort_column(t,e);
                        for(int o=0;o<(t->column);++o)
                        {
                            if(o)
                                cout<<setw(35)<<left<<(t->column_name[o]);
                            else
                                cout<<setw(5)<<""<<setw(35)<<left<<(t->column_name[o]);
                        }
                        cout<<"\n";
                        for(int o=0;o<(t->entries);++o)
                        {
                            for(int j=0;j<(t->column);++j)
                            {
                                if(j)
                                    cout<<setw(35)<<left<<(t->column_data[j][o]);
                                else
                                    cout<<setw(5)<<""<<setw(35)<<left<<(t->column_data[j][o]);
                            }
                            cout<<"\n";
                        }
                    }
                    else
                    {
                        temp="";
                        while((i<n)&&s[i]==' ')
                            ++i;
                        if(i>=n)
                        {
                            cout<<"No key entered\n";
                            continue;
                        }
                        bool p=1;
                        for(;i<n;++i)
                        {
                            if(s[i]==' ')
                                break;
                            if(s[i]=='=')
                            {
                                p=0;
                                break;
                            }
                            temp+=s[i];
                        }
                        if(p)
                        {
                            cout<<"Invalid syntax\n";
                            continue;
                        }
                        int e=find_columindex(t,temp);
                        if(e==-1)
                        {
                            cout<<"No such column exists\n";
                            continue;
                        }
                        sort_column(t,e);
                        ++i;
                        temp="";
                        for(;i<n;++i)
                        {
                            temp+=s[i];
                        }
                        int l=binary_sl(t,temp,e);
                        if(l==-1)
                        {
                            cout<<"No such entries exist\n";
                            continue;
                        }
                        int r=binary_sh(t,temp,e);
                        for(int o=0;o<(t->column);++o)
                        {
                            if(o)
                                cout<<setw(35)<<left<<(t->column_name[o]);
                            else
                                cout<<setw(5)<<""<<setw(35)<<left<<(t->column_name[o]);
                        }
                        cout<<"\n";
                        for(int o=l;o<=r;++o)
                        {
                            for(int j=0;j<(t->column);++j)
                            {
                                if(j)
                                    cout<<setw(35)<<left<<(t->column_data[j][o]);
                                else
                                    cout<<setw(5)<<""<<setw(35)<<left<<(t->column_data[j][o]);
                            }
                            cout<<"\n";
                        }
                    }
                }
            }
        }
    }
    return 0;
}
