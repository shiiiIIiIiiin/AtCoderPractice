#include<bits/stdc++.h>
using namespace std;

using ll=long long;
ll INF=LLONG_MAX/2;

ll N,L,T,K;

void produce(pair<int,int> pt,const vector<ll> &A,const vector<vector<ll>> &C,ll &score,vector<vector<ll>> &B,vector<vector<ll>> &P){
    //購入
    int lv=pt.first;
    int j=pt.second;
    if(lv!=-1){
        ll cost=C[lv][j]*(P[lv][j]+1);
        score-=cost;
        P[lv][j]++;
    }

    //生産
    for(int i=0;i<L;i++){
        if(i==0){
            for(int k=0;k<N;k++)
                score+=A[k]*B[i][k]*P[i][k];
        }
        else{
            for(int k=0;k<N;k++)
                B[i-1][k]+=B[i][k]*P[i][k];
        }
    }
}

double compare(ll A,ll B,ll cost,double s,double t){
    return pow((double)A,(double)s)*B/pow((double)cost,(double)t);
}

ll simulate_strategy(vector<pair<int,int>> &pts,const vector<ll> &A,const vector<vector<ll>> &C,double &pow_a,double &pow_cost,ll &seisan){
    //戦略:各ターンで購入可能な一番高レベルなものを買う
    vector<vector<ll>> P(L,vector<ll>(N,0)),B(L,vector<ll>(N,1));

    random_device rd;
    mt19937 mt(rd());
    uniform_real_distribution<double> randa(1.0,2.0),randc(4.0,10.0);
    uniform_int_distribution<ll> randt(0,T/5);

    ll score=K;
    pow_a=randa(mt);
    pow_cost=randc(mt);
    seisan=randt(mt);

    for(int t=0;t<T-seisan;t++){
        int best_lv=-1,best_select=-1;
        double best_eff=-1.0;
        for(int lv=L-1;lv>=0;lv--){
            for(int j=0;j<N;j++){
                ll cost=C[lv][j]*(P[lv][j]+1);

                if(cost>score)continue;
                double eff=compare(A[j],B[lv][j],cost,pow_a,pow_cost);
                if(eff>best_eff){
                    best_eff=eff;
                    best_lv=lv;
                    best_select=j;
                }
            }

            if(best_lv!=-1){
                pts[t]={best_lv,best_select};
                break;
            }
        }

        if(best_lv==-1)pts[t]={-1,-1};
        
        //生産
        produce(pts[t],A,C,score,B,P);
    }

    // 残りの seisan ターンは生産のみ（-1,-1）を詰めてシミュレート
    for(int t=T-seisan;t<T;t++){
        pts[t]={-1,-1};
        produce(pts[t],A,C,score,B,P);
    }

    return score;
}

int main(){
    cin>>N>>L>>T>>K;
    vector<ll> A(N);
    for(int i=0;i<N;i++)cin>>A[i];
    vector<vector<ll>> C(L,vector<ll>(N));
    for(int i=0;i<L;i++)for(int j=0;j<N;j++)cin>>C[i][j];

    ll best_score=-INF;
    vector<pair<int,int>> best_pts(T);
    double bast_a=-1,best_c=-1;
    ll best_T=-1;

    auto start=chrono::steady_clock::now();
    do{
        vector<pair<int,int>> pts(T);
        double pow_a,pow_cost;
        ll seisan;
        ll score=simulate_strategy(pts,A,C,pow_a,pow_cost,seisan);

        if(score>=best_score){
            best_score=score;
            best_pts=pts;
            bast_a=pow_a;
            best_c=pow_cost;
            best_T=seisan;
        }
    }while(chrono::duration<double>(chrono::steady_clock::now()-start).count()<1.9);

    for(int t=0;t<T;t++){
        if(best_pts[t].first==-1)cout<<-1<<endl;
        else cout<<best_pts[t].first<<" "<<best_pts[t].second<<endl;
    }

    cout<<"# Best Score: "<<best_score<<", pow_a: "<<bast_a<<", pow_cost: "<<best_c<<", seisan_turns: "<<best_T<<endl;
}