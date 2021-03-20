#include <iostream>
#include <string.h>
#include <fstream>
#include <ctime>
#include <vector>

using namespace std;

int main(int argc, char* argv[])
{
    time_t now = time(0);
    tm *l =localtime(&now);

    ofstream todo,done;

    if(argc==1||strcmp(argv[1],"help")==0)
    {
        const char *s=R"(Usage :-
$ ./todo add "todo item"  # Add a new todo
$ ./todo ls               # Show remaining todos
$ ./todo del NUMBER       # Delete a todo
$ ./todo done NUMBER      # Complete a todo
$ ./todo help             # Show usage
$ ./todo report           # Statistics)";
        cout<<s;
    }
    else if(strcmp(argv[1],"add")==0)
    {
        
        todo.open("todo.txt",ios_base::app);
        todo<<argv[2]<<"\n";
        if(argc==2)
        cout<<"Error: Missing todo string. Nothing added!";
        else
        cout<<"Added todo: \""<<argv[2]<<"\"";
    }
    else if(strcmp(argv[1],"del")==0)
    {
        ifstream todo("todo.txt");  
        ofstream ofs; 
        ofs.open("temp.txt", ofstream::out); 

        char *p;
        string str; 
        long n=strtol(argv[2],&p,10);
        int line_no = 0; 
        while (getline(todo,str)) 
        {  
            line_no++; 
            if (line_no != n) 
            ofs << str<<"\n"; 
                           
        } 
        ofs.close(); 
        todo.close();  
        remove("todo.txt");  
        rename("temp.txt","todo.txt"); 
        if(argc==2)
        cout<<"Error: Missing NUMBER for deleting todo.";
        else
        {
            if(n<=line_no && n>0)
            cout<<"Deleted todo #"<<argv[2];
            else
            cout<<"Error: todo #"<<argv[2]<<" does not exist. Nothing deleted.";
        }
    }
    else if(strcmp(argv[1],"ls")==0)
    {
        ifstream todo("todo.txt");
        string str;
        vector<string> lines;
        while (getline(todo,str)) 
        {  
            lines.push_back(str);
        }
        if(lines.size()==0)
        {
            cout<<"There are no pending todos!";
        }
        else
        {
        for(int i=lines.size()-1;i>=0;i--)
        {
            cout<<"["<<i+1<<"] "<<lines.at(i)<<"\n";
        }
        }
        todo.close(); 
    }
    else if(strcmp(argv[1],"done")==0)
    {
        ifstream todo("todo.txt");  
        ofstream ofs,done; 
        ofs.open("temp.txt", ofstream::out);
        done.open("done.txt",ios_base::app); 

        char *p; 
        string str;
        long n=strtol(argv[2],&p,10);
        int line_no = 0; 
        while (getline(todo,str)) 
        {  
            line_no++; 
            if(line_no==n)
            done<<"x "<<l->tm_year+1900<<"-"<<l->tm_mon+1<<"-"<<l->tm_mday<<" "<<str<<"\n";
            if (line_no != n) 
            ofs << str<<"\n";
        } 
  
        ofs.close(); 
        todo.close();  
        remove("todo.txt");  
        rename("temp.txt","todo.txt");
        if(argc==2)
        cout<<"Error: Missing NUMBER for marking todo as done.";
        else
        {
            if(n<=line_no && n>0)
            {
                cout<<"Marked todo #"<<argv[2]<<" as done.";
            }
            else
            {
                cout<<"Error: todo #"<<argv[2]<<" does not exist.";
            }
        }
        
    }
    else if(strcmp(argv[1],"report")==0)
    {
        ifstream todo("todo.txt"),done("done.txt");
        string str;
        int to=0,don;
        while(getline(todo,str))
        to++;
        while(getline(done,str))
        don++;

        cout<<l->tm_year+1900<<"-"<<l->tm_mon+1<<"-"<<l->tm_mday<<" "<<"Pending : "<<to<<" Completed : "<<don;
    }
}
