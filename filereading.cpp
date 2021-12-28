#include <iostream>
#include <fstream>
using namespace std;

int main(){
    char filename[7]="input0";

    ifstream ifs;
    int N;
    int **damage;

    ifs.open(filename);
    if (!ifs.is_open()){
        cout << "Failed to open file.\n";
    }else{
        ifs>>N;
        cout<<N<<endl;
        damage=new int *[N];     
        for(int i=0;i<N;i++){   
            damage[i] = new int[N];
        }
        int number;
        int i,j=1;
        for(int i=0;i<N;i++){
            for(j=0;j<N;j++){
                ifs>>damage[i][j];
            }
        }
        ifs.close();
        for(int i=0;i<N;i++){
            for(j=0;j<N;j++){
                cout<<damage[i][j]<<" ";
            }
            cout<<"\n";
        }
    }
    system("PAUSE");
    return 0;
}