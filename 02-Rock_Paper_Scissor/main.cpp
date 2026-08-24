#include <bits/stdc++.h>
#include <random>
using namespace std;
random_device rd;
mt19937 gen(rd());
char getComputerInput(){
    int a=gen()%3;
    if(a==0){
        return 'r';
    }
    else if(a==1){
        return 'p';
    }
    else {
        return 's';
    }
}
int checkWinner(char user,char comp){
    char win;
    if(user==comp){
        return 0;
    }
  if((user=='r' && comp=='s') || (comp=='r' && user=='s')){
    win='r';
  }
  else if((user=='p' && comp=='s')||(comp=='p' && user=='s') ){
    win='s';
  }
  else{
    win='p';
  }
  if(win==user){
    return 1;
  }
  else 
    return -1;
}

int main(){
    while(true){
        cout<<"----Enter----\n0 to close --OR-- 1 to play"<<endl;
        int a;
        cin>>a;
        if(a==0){
            return -1;
        }
        cout<<"----Enter----\nr for rock\np for paper\ns for scissors"<<endl;
        char user;
        cin>>user;
        if(user=='r' || user=='p' ||user=='s'){
            char comp=getComputerInput();
            int result=checkWinner(user,comp);
            if(result==0){
                cout<<"\nDraw\n"<<endl;
            }
            else if(result==1){
                cout<<"\nWinner\n"<<endl;
            }
            else{
                cout<<"\nLoser\n"<<endl;
            }
            cout<<"your move was:"<<user<<"\ncomputer move was:"<<comp<<endl;
        }
        else{
            cout<<"Invalid input "<<endl;
            continue;
        }
    }
}