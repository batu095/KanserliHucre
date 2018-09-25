#include <iostream>
#include <thread>
#include <mutex>
#include <fstream>
#include <vector>
#include <tgmath.h>
using namespace std;


class person{
public:
    int age,year,bad_cells_number,alive;
    void read_data(int sended){
        int a=0;
        string s;
        char get_number;
        int s_length,number=0,counter=0;
        ifstream read("haberman.txt",ios::app);
        for(a=0;a<=sended;a++)
        //read>>s;
        getline(read,s);
        //cout<<s<<"    ";
        s_length=s.length();
       // cout<<s_length<<"    ";
        get_number=s[0]-48;
       // cout<<s;
        while(s[counter]!=','){
            number=number*10+get_number;
            counter++;
            get_number=s[counter]-48;
        }
        age=number;
        counter++;
        get_number=s[counter]-48;
        number=0;
        while(s[counter]!=','){
            number=number*10+get_number;
            counter++;
            get_number=s[counter]-48;
        }
        year=number;
        counter++;
        get_number=s[counter]-48;
        number=0;
        while(s[counter]!=','){
            number=number*10+get_number;
            counter++;
            get_number=s[counter]-48;
        }
        bad_cells_number=number;
        counter++;
        get_number=s[counter]-48;
        number=0;
        while(s[counter]!=',' && counter<s_length){
            number=number*10+get_number;
            counter++;
            get_number=s[counter]-48;
        }
        alive=number;
    }
};

void optimum_age(int separate, person patient[306],double entropy[9],int index){
    double entropy_temp=0;
    double separate_less=0, separate_more=0;
    int counter=0;
    for(counter=0;counter<306;counter++){
        if(patient[counter].age<separate){
            separate_less++;
        }
        else{
            separate_more++;
        }
    }

    entropy_temp=(separate_more/306)*log2(separate_more/306) + (separate_less/306)*log2(separate_less/306);
    entropy[index]=entropy_temp*(-1);
}

void optimum_year(int separate, person patient[306],double entropy[9],int index){
    double entropy_temp=0;
    int counter=0;
    double separate_less=0, separate_more=0;
    for(counter=0;counter<306;counter++){
        if(patient[counter].year<separate){
            separate_less++;
        }
        else{
            separate_more++;
        }
    }
    entropy_temp=(separate_more/306)*log2(separate_more/306) + (separate_less/306)*log2(separate_less/306);
    entropy[index]=entropy_temp*(-1);
}

void optimum_cells(int separate, person patient[306],double entropy[9],int index){
    double entropy_temp=0;
    double separate_less=0, separate_more=0;
    int counter=0;
    for(counter=0;counter<306;counter++){
        if(patient[counter].bad_cells_number<separate){
            separate_less++;
        }
        else{
            separate_more++;
        }
    }
    entropy_temp=(separate_more/306)*log2(separate_more/306) + (separate_less/306)*log2(separate_less/306);
    entropy[index]=entropy_temp*(-1);

}

main(){
    int index;
    person patient[306];
    for(index=0;index<306;index++)
        patient[index].read_data(index);
    double entropy[9],biggest=0;
    thread t1(optimum_age,50,patient,entropy,0);
    thread t2(optimum_age,60,patient,entropy,1);
    thread t3(optimum_age,70,patient,entropy,2);
    thread t4(optimum_year,62,patient,entropy,3);
    thread t5(optimum_year,63,patient,entropy,4);
    thread t6(optimum_year,64,patient,entropy,5);
    thread t7(optimum_cells,5,patient,entropy,6);
    thread t8(optimum_cells,10,patient,entropy,7);
    thread t9(optimum_cells,19,patient,entropy,8);

    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
    t6.join();
    t7.join();
    t8.join();
    t9.join();

    for(index=0;index<9;index++)
        if(entropy[index]>biggest)
            biggest=entropy[index];


}
