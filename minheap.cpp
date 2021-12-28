#include <iostream>
#include <bits/stdc++.h>
#include <fstream>
using namespace std;
int ** location;
class Node{
    friend class Min_heap;
    public :
        int position[2];
        int value=2147483647;
        int from[2]={0,0};
        Node();
        Node(int x,int y);
};
Node::Node(){

}
Node::Node(int x,int y){
    position[0]=x;
    position[1]=y;
}

class Min_heap{
    public:
    vector<Node> heap;
    int number_of_nodes=0;
    Min_heap();
    Min_heap(int val);
    void swap(int key_a,int key_b);
    void insertion(Node a);
    void Min_heapify(int i);
    Node extract_min();
    void decrease(int x,int y,int val);
    void decrease(int x,int y,int val,int from_x,int from_y);
};
Min_heap::Min_heap(){
    
}
void Min_heap::swap(int key_a,int key_b){
    int x1=heap[key_a].position[0];
    int y1=heap[key_a].position[1];
    int x2=heap[key_b].position[0];
    int y2=heap[key_b].position[1];
    Node temp=heap[key_a];
    heap[key_a]=heap[key_b];
    heap[key_b]=temp;
    int temp_loc=location[x1-1][y1-1];
    location[x1-1][y1-1]=location[x2-1][y2-1];
    location[x2-1][y2-1]=temp_loc;
}

void Min_heap::insertion(Node a){
    heap.push_back(a);
    number_of_nodes++;
    location[a.position[0]-1][a.position[1]-1]=number_of_nodes;
    int parent_key=number_of_nodes/2;
    int last_parent_key=number_of_nodes;
    if(number_of_nodes==1){
        return;
    }else{
        while(heap[last_parent_key-1].value<heap[parent_key-1].value and parent_key!=0){
            swap(last_parent_key-1,parent_key-1);
            last_parent_key=parent_key;
            parent_key=parent_key/2;
        }
    }
}
void Min_heap::Min_heapify(int i){
        if(2*i>number_of_nodes){
            return;
        }else if(2*i<=number_of_nodes and 2*i+1>number_of_nodes){
            if(heap[i-1].value<=heap[2*i-1].value){
                return;
            }else if(heap[2*i-1].value<heap[i-1].value){
                swap(i-1,2*i-1);
                return;
            }
        }else{
            if(heap[i-1].value<=heap[2*i-1].value and heap[i-1].value<=heap[2*i+1-1].value){
                return;
            }else if(heap[2*i-1].value<=heap[i-1].value and heap[2*i-1].value<=heap[2*i+1-1].value){
                swap(i-1,2*i-1);
                Min_heapify(2*i);
            }else if(heap[2*i+1-1].value<=heap[i-1].value and heap[2*i+1-1].value<=heap[2*i-1].value){
                swap(i-1,2*i+1-1);
                Min_heapify(2*i+1);
            }
        }
    }
Node Min_heap::extract_min(){
    swap(1-1,number_of_nodes-1);
    Node output=heap[number_of_nodes-1];
    heap.pop_back();
    number_of_nodes--;
    Min_heapify(1);
    return output;
}
void Min_heap::decrease(int x,int y,int val){
    int loc=location[x-1][y-1];
    if(heap[loc-1].value<=val){
        return;
    }else{
        if(loc==1){
            heap[loc-1].value=val;
        }else{
            heap[loc-1].value=val;
            int last_parent_key=loc;
            int parent_key=loc/2;
            while(heap[last_parent_key-1].value<heap[parent_key-1].value and parent_key!=0){
                swap(last_parent_key-1,parent_key-1);
                last_parent_key=parent_key;
                parent_key=parent_key/2;
            }
        }
    }
}
void Min_heap::decrease(int x,int y,int val,int from_x,int from_y){
    int loc=location[x-1][y-1];
    if(heap[loc-1].value<=val){
        return;
    }else{
        if(loc==1){
            heap[loc-1].value=val;
        }else{
            heap[loc-1].value=val;
            int last_parent_key=loc;
            int parent_key=loc/2;
            while(heap[last_parent_key-1].value<heap[parent_key-1].value and parent_key!=0){
                swap(last_parent_key-1,parent_key-1);
                last_parent_key=parent_key;
                parent_key=parent_key/2;
            }
            
        }
        heap[location[x-1][y-1]-1].from[0]=from_x;
        heap[location[x-1][y-1]-1].from[1]=from_y;
        
    }
}
int main(){
    ////////////////////////file reading////////////////////////
    char filename[7]="input1";
    ifstream ifs;
    int N;
    int **damage;
    Node **mapping;

    ifs.open(filename);
    if (!ifs.is_open()){
        cout << "Failed to open file.\n";
    }else{
        ifs>>N;
        damage=new int *[N];     
        for(int i=0;i<N;i++){   
            damage[i] = new int[N];
        }
        for(int i=0;i<N;i++){
            for(int j=0;j<N;j++){
                ifs>>damage[i][j];
            }
        }
        ifs.close();
    }
    ///////////////////////////////////////////////////////////
    location=new int *[N];     
    for(int i=0;i<N;i++){   
        location[i] = new int[N];
    }
    Min_heap H;
    mapping=new Node *[N];     
    for(int i=0;i<N;i++){   
        mapping[i] = new Node[N];
    }
    for(int i=1;i<=N;i++){
        for(int j=1;j<=N;j++){
            Node temp(i,j);
            H.insertion(temp);
        }
    }
    H.decrease(1,1,damage[1-1][1-1]);

    Node min=H.extract_min();
    mapping[min.position[0]-1][min.position[1]-1]=min;
    int cur_x=min.position[0];
    int cur_y=min.position[1];
    location[0][0]=-1;
    H.decrease(cur_x,cur_y+1,min.value+damage[cur_x-1][cur_y+1-1],cur_x,cur_y);
    H.decrease(cur_x+1,cur_y,min.value+damage[cur_x+1-1][cur_y-1],cur_x,cur_y);

    min=H.extract_min();
    mapping[min.position[0]-1][min.position[1]-1]=min;
    while(min.position[0] != N or min.position[1] != N){
        int cur_x=min.position[0];
        int cur_y=min.position[1];
        location[cur_x-1][cur_y-1]=-1;
        if(cur_x==1 and cur_y!=N){
            if(location[cur_x+1-1][cur_y-1]!=-1){
                H.decrease(cur_x+1,cur_y,min.value+damage[cur_x+1-1][cur_y-1],cur_x,cur_y);
            }
            if(location[cur_x-1][cur_y+1-1]!=-1){
                H.decrease(cur_x,cur_y+1,min.value+damage[cur_x-1][cur_y+1-1],cur_x,cur_y);
            }
            if(location[cur_x-1][cur_y-1-1]!=-1){
                H.decrease(cur_x,cur_y-1,min.value+damage[cur_x-1][cur_y-1-1],cur_x,cur_y);
            }
        }else if(cur_x==1 and cur_y==N){
            if(location[cur_x+1-1][cur_y-1]!=-1){
                H.decrease(cur_x+1,cur_y,min.value+damage[cur_x+1-1][cur_y-1],cur_x,cur_y);
            }
            if(location[cur_x-1][cur_y-1-1]!=-1){
                H.decrease(cur_x,cur_y-1,min.value+damage[cur_x-1][cur_y-1-1],cur_x,cur_y);
            }
        }else if(cur_x==N and cur_y!=1){
            if(location[cur_x-1-1][cur_y-1]!=-1){
                H.decrease(cur_x-1,cur_y,min.value+damage[cur_x-1-1][cur_y-1],cur_x,cur_y);
            }
            if(location[cur_x-1][cur_y+1-1]!=-1){
                H.decrease(cur_x,cur_y+1,min.value+damage[cur_x-1][cur_y+1-1],cur_x,cur_y);
            }
            if(location[cur_x-1][cur_y-1-1]!=-1){
                H.decrease(cur_x,cur_y-1,min.value+damage[cur_x-1][cur_y-1-1],cur_x,cur_y);
            }
        }else if(cur_x==N and cur_y==1){
            if(location[cur_x-1-1][cur_y-1]!=-1){
                H.decrease(cur_x-1,cur_y,min.value+damage[cur_x-1-1][cur_y-1],cur_x,cur_y);
            }
            if(location[cur_x-1][cur_y+1-1]!=-1){
                H.decrease(cur_x,cur_y+1,min.value+damage[cur_x-1][cur_y+1-1],cur_x,cur_y);
            }
        }else if(cur_x!=N and cur_y==1){
            if(location[cur_x+1-1][cur_y-1]!=-1){
                H.decrease(cur_x+1,cur_y,min.value+damage[cur_x+1-1][cur_y-1],cur_x,cur_y);
            }
            if(location[cur_x-1-1][cur_y-1]!=-1){
                H.decrease(cur_x-1,cur_y,min.value+damage[cur_x-1-1][cur_y-1],cur_x,cur_y);
            }
            if(location[cur_x-1][cur_y+1-1]!=-1){
                H.decrease(cur_x,cur_y+1,min.value+damage[cur_x-1][cur_y+1-1],cur_x,cur_y);
            }
        }else if(cur_x!=1 and cur_y==N){
            if(location[cur_x+1-1][cur_y-1]!=-1){
                H.decrease(cur_x+1,cur_y,min.value+damage[cur_x+1-1][cur_y-1],cur_x,cur_y);
            }
            if(location[cur_x-1-1][cur_y-1]!=-1){
                H.decrease(cur_x-1,cur_y,min.value+damage[cur_x-1-1][cur_y-1],cur_x,cur_y);
            }
            if(location[cur_x-1][cur_y-1-1]!=-1){
                H.decrease(cur_x,cur_y-1,min.value+damage[cur_x-1][cur_y-1-1],cur_x,cur_y);
            }
        }else{
            if(location[cur_x+1-1][cur_y-1]!=-1){
                H.decrease(cur_x+1,cur_y,min.value+damage[cur_x+1-1][cur_y-1],cur_x,cur_y);
            }
            if(location[cur_x-1-1][cur_y-1]!=-1){
                H.decrease(cur_x-1,cur_y,min.value+damage[cur_x-1-1][cur_y-1],cur_x,cur_y);
            }
            if(location[cur_x-1][cur_y+1-1]!=-1){
                H.decrease(cur_x,cur_y+1,min.value+damage[cur_x-1][cur_y+1-1],cur_x,cur_y);
            }
            if(location[cur_x-1][cur_y-1-1]!=-1){
                H.decrease(cur_x,cur_y-1,min.value+damage[cur_x-1][cur_y-1-1],cur_x,cur_y);
            }
        }
        min=H.extract_min();
        mapping[min.position[0]-1][min.position[1]-1]=min;
    }
    vector<Node> path;
    int x=N,y=N;

    while(x!=1 or y!=1){
        path.push_back(mapping[x-1][y-1]);
        int o_x=x,o_y=y;
        x=mapping[o_x-1][o_y-1].from[0];
        y=mapping[o_x-1][o_y-1].from[1];
    }
    path.push_back(mapping[0][0]);
    reverse(path.begin(),path.end());

    cout<<min.value<<" "<<path.size()<<endl;
    for(auto iter=path.begin();iter!=path.end()-1;iter++){
        if((iter+1)->position[0]>(iter)->position[0]){
            cout<<"D ";
        }else if((iter+1)->position[0]<(iter)->position[0]){
            cout<<"U ";
        }else if((iter+1)->position[1]>(iter)->position[1]){
            cout<<"R ";
        }else if((iter+1)->position[1]<(iter)->position[1]){
            cout<<"L ";
        }
    }
    ///////////////////////////////////////////////////////////
    for(int i=0;i<N;i++) {   
        delete [] location[i];
    }
    delete [] location; 
    for(int i=0;i<N;i++) {   
        delete [] damage[i];
    }
    delete [] damage; 
    for(int i=0;i<N;i++) {   
        delete [] mapping[i];
    }
    delete [] mapping; 
    system("PAUSE");
    return 0;
}