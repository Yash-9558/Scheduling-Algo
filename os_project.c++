#include<bits/stdc++.h>
#define f        first
#define s        second
#define sz(x)  (int)x.size()
using namespace std;
bool cmp(const pair<string,pair<int,int>> &a,const pair<string,pair<int,int>> &b){
    return a.s.f<b.s.f;
}
class Myclass{
public:
    bool operator()(const pair<string,int>&a,const pair<string,int>&b){
        return a.s>b.s;
    }
};
class Myclass1{
public:
    bool operator()(const pair<string,pair<int,int>>&a,const pair<string,pair<int,int>>&b){
        // a.s.s <-- service time same then check arrival time (a.s.f)
        if(a.s.s == b.s.s){
            return a.s.f > b.s.f;
        }
        else{
            return a.s.s > b.s.s;
        }
    }
};

void srtn(vector<pair<string,pair<int,int>>>v,int n){
    cout<<"\n\n";
    string pattern(36,'-'); 
    cout<<pattern<<endl;
    cout<<"\t\tSRTN\n";
    cout<<pattern<<endl;
    vector<pair<string,pair<int,int>>>copy=v;
    sort(v.begin(),v.end(),cmp);

    int k=0; //running time
    priority_queue<pair<string,pair<int,int>>,vector<pair<string,pair<int,int>>>,Myclass1>pq;
    bool flag=false;
    int for_at=0;
    pair<string,pair<int,int>>ans;
    int pfinal=0;
    vector<pair<int,string>>srtn;
    bool p;
    while(true){
        p=false;
        while(k == v[for_at].s.f){
            pq.push({v[for_at].f,{v[for_at].s.f,v[for_at].s.s}});
            for_at++;
            p=true;
        }

        if(flag == false || p == true){

            if(p == true && ans.s.s!=0){
                pq.push({ans.f,{ans.s.f,ans.s.s}});
            }

            if(!pq.empty()){
                ans=pq.top();
                pq.pop();

                srtn.push_back(make_pair(k,ans.f));
                // cout<<ans.f<<endl;

                ans.s.s--;
                flag=true;

                if(ans.s.s == 0){
                    flag=false;
                    pfinal++;
                    if(pfinal == n){
                        break;
                    }
                }
            }
            else{
                // cout<<"IDLE\n";
                srtn.push_back(make_pair(k,"IDLE"));
            }
        }
        else if(flag == true){
            ans.s.s--;
            if(ans.s.s == 0){
                flag=false;
                pfinal++;
                if(pfinal == n){
                    break;
                }
            }
        }
        k++;
    }
    k++;

    vector<int>checkpoints;

    for(int i=0;i<sz(srtn);i++){
        checkpoints.push_back(srtn[i].f);
    }
    checkpoints.push_back(k);

    cout<<"\n\nGANTT CHART : \n\n"; 
    for(auto it:checkpoints){
        cout<<setw(2)<<it<<"      ";
    }cout<<endl;

    for(int i=0;i<sz(srtn);i++){
        cout<<setw(2)<<"|";
        cout<<setw(6)<<srtn[i].s;
    }
    cout<<setw(2)<<"|";
    cout<<endl;

    map<int,int>FT;
    for(int i=sz(srtn)-1;i>=0;i--){
        if(srtn[i].s != "IDLE" && FT[(srtn[i].s)[1]-'0'] == 0){
            FT[(srtn[i].s)[1]-'0'] = checkpoints[i+1];
        }

        if(sz(FT) == n){
            break;
        }
    }

    cout<<"\n\nTABLE : \n\n";
    cout<<pattern<<endl;
    cout<<setw(6)<<"PNAME"<<setw(6)<<"AT"<<setw(6)<<"ST"<<setw(6)<<"FT"<<setw(6)<<"TAT"<<setw(6)<<"WT"<<endl;
    cout<<pattern<<endl;

    int PN=-1;
    float ATAT=0;
    float AWT=0;
    for(int i=0;i<n;i++){
        PN=((copy[i].f)[1]-'0');
        cout<<setw(6)<<copy[i].f<<setw(6)<<copy[i].s.f<<setw(6)<<copy[i].s.s<<setw(6)<<FT[PN]<<setw(6)<<FT[PN]-copy[i].s.f<<setw(6)<<FT[PN]-copy[i].s.f-copy[i].s.s<<endl;
        ATAT += FT[PN]-copy[i].s.f;
        AWT += FT[PN]-copy[i].s.f-copy[i].s.s;
    }
    cout<<pattern<<endl;

    cout<<" AWT  : "<<AWT/n<<endl;
    cout<<"\n";
    cout<<" ATAT : "<<ATAT/n<<endl;
}

int main(){
    //sjf

    int n;
    cout<<"ENTER NUMBER OF PROCESS : ";
    cin>>n;

    vector<pair<string,pair<int,int>>>v(n);
              //pname       at  st

    cout<<"\n";
    cout<<"ENTER ARRIVAL TIME OF EACH PROCESS\n";
    cout<<"\n";
    for(int i=0;i<n;i++){
      v[i].f="P"+to_string(i+1);
      cout<<"ENTER FOR PROCEES P("<<(i+1)<<") : ";
      cin>>v[i].s.f;
    }

    cout<<"\n";
    cout<<"ENTER SERVICE TIME OF EACH PROCESS\n";
    cout<<"\n";
    int tst=0;
    for(int i=0;i<n;i++){
      cout<<"ENTER FOR PROCEES P("<<(i+1)<<") : ";
      cin>>v[i].s.s;
      // tst+=v[i].s.s;
    }
    vector<pair<string,pair<int,int>>>copy=v;
    vector<pair<string,pair<int,int>>>v1=v;

    sort(v.begin(),v.end(),cmp);

    int k=0; //running time
    priority_queue<pair<string,int>,vector<pair<string,int>>,Myclass>pq;

    bool flag=false;
    int for_at=0;
    pair<string,int>ans;
    int pfinal=0;
    vector<pair<int,string>>sjf;

    while(true){
        while(k == v[for_at].s.f){
            pq.push({v[for_at].f,v[for_at].s.s});
            for_at++;
        }

        if(flag == false){
            if(!pq.empty()){
                ans=pq.top();
                pq.pop();

                sjf.push_back(make_pair(k,ans.f));
                // cout<<ans.f<<endl;

                ans.s--;
                flag=true;

                if(ans.s == 0){
                    flag=false;
                    pfinal++;
                    if(pfinal == n){
                        break;
                    }
                }
            }
            else{
                // cout<<"IDLE\n";
                sjf.push_back(make_pair(k,"IDLE"));
            }
        }
        else if(flag == true){
            ans.s--;
            if(ans.s == 0){
                flag=false;
                pfinal++;
                if(pfinal == n){
                    break;
                }
            }
        }
        k++;
    }
    string pattern(36,'-');

    cout<<"\n\n";
    cout<<pattern<<endl;
    cout<<"\t\tSJF\n";
    cout<<pattern<<endl;
    vector<int>ft(n,0);
    vector<int>checkpoints;
    vector<string>p;
    checkpoints.push_back(0);
    p.push_back(sjf[0].s);
    for(int i=1;i<sz(sjf);i++){
        if(sjf[i-1].s != sjf[i].s){
            checkpoints.push_back(sjf[i].f);
            p.push_back(sjf[i].s);
        }
    }

    checkpoints.push_back(sjf.back().f+copy[(sjf.back().s)[1]-'0'-1].s.s);

    cout<<"\n\nGANTT CHART : \n\n";
    for(auto it:checkpoints){
        cout<<setw(2)<<it<<"      ";
    }cout<<endl;
    for(int i=0;i<sz(p);i++){
        cout<<setw(2)<<"|";
        cout<<setw(6)<<p[i];
    }


    cout<<setw(2)<<"|";
    cout<<endl;

    cout<<"\n\nTABLE : \n\n";
    
    cout<<pattern<<endl;
    cout<<setw(6)<<"PNAME"<<setw(6)<<"AT"<<setw(6)<<"ST"<<setw(6)<<"FT"<<setw(6)<<"TAT"<<setw(6)<<"WT"<<endl;
    cout<<pattern<<endl;

    for(int i=1;i<sz(checkpoints);i++){
        if(p[i-1] != "IDLE"){
            ft[p[i-1][1]-'0'-1] = checkpoints[i];
        }
    }

    float ATAT=0;
    float AWT=0;
    for(int i=0;i<n;i++){
        cout<<setw(6)<<copy[i].f<<setw(6)<<copy[i].s.f<<setw(6)<<copy[i].s.s<<setw(6)<<ft[i]<<setw(6)<<ft[i]-copy[i].s.f<<setw(6)<<ft[i]-copy[i].s.f-copy[i].s.s<<endl;
        ATAT += ft[i]-copy[i].s.f;
        AWT += ft[i]-copy[i].s.f-copy[i].s.s;
    }
    cout<<pattern<<endl;

    cout<<" AWT  : "<<AWT/n<<endl;
    cout<<"\n";
    cout<<" ATAT : "<<ATAT/n<<endl;

    //srtn
    srtn(v1,n);
    
    return 0;
}
