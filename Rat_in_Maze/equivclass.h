#ifndef EQUIVCLASS_H
#define EQUIVCLASS_H


//在线等价类
class EquivClass
{
private:
    int *parent;
public:
    void initialize(int n){
        parent = new int[n+1];
        for(int e = 0;e<n;e++){
            parent[e] = -1;
        }
    }
    int find(int e){
        while(parent[e]!=-1){
            e = parent[e];
        }
        return e;
    }
    void unite(int i,int j){
        parent[j]=i;
    }
    void combine(int i,int j){
        int ip = find(i);
        int jp = find(j);
        if(ip!=jp){
            unite(ip,jp);
        }
    }
};
#endif // EQUIVCLASS_H
