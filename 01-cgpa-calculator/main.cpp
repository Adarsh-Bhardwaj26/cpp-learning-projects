#include <iostream>
#include <bits/stdc++.h>
#include <ctime>
using namespace std;
float cgpaCalculator(int credits[],int n,char grade[]){
    float totalGradepoint=0;
    int totalCredit=0;
    for(int i=0;i<n;i++){

        totalCredit+=credits[i];
        float gradePoint=0;
        if(grade[i]>='A' && grade[i]<='F'){
            if (grade[i] == 'F')
                gradePoint += 0;
            else
                gradePoint += 9 - (grade[i] - 'A');
        }
        else if(grade[i]=='S'){
            gradePoint+=10;
        }
        else{
            cout<<"Invalid Grade"<<endl;
            return -1;
        }
        totalGradepoint+=gradePoint*credits[i];
    }
    return totalGradepoint/totalCredit;
}

int main(){
   fstream OutputFile("Output.txt",ios::app);
   if(OutputFile.is_open()){
        int n;
        int a;
        cout<<"Enter 0 to close the program:"<<endl;
        while(true){
             cout<<"Enter the no of subject: "<<endl;
             cin>>n;
            int credit[n]={0};
            char Grade[n];
            cout<<"Enter the credits of each Course: in a line : "<<endl;
            for(int i=0;i<n;i++){
                cin>>credit[i];
            }
            cout<<"Enter the grade obtained in each course Range (S to F)"<<endl;
            for(int i=0;i<n;i++){
                cin>>Grade[i];
            }
            float cgpa=cgpaCalculator(credit,n,Grade);
            if (cgpa == -1) {
                cout << "CGPA calculation failed." << endl;
                continue;
            }
            cout<<"Your Grade is: "<<cgpa<<endl;
            time_t now= time(0);
            tm *localTime = localtime(&now);
            OutputFile<<"Date: "
                <<localTime->tm_mday<<"/"
                << localTime->tm_mon + 1 << "/"
                << localTime->tm_year + 1900 <<" Cgpa:"<<cgpa<< '\n';
            cout<<"succesfully Saved in file"<<endl;
            cout<<"Enter 0 to close the program: "<<endl;
            cout<<"enter 1 to recalculate: "<<endl;
            cin>>a;
            if (a == 0) {
                cout << "Closing program...";
                return 0;
            }
            }
        }
    else{
        cout<<"unable to open file:";
    }
}