#include<bits/stdc++.h>
#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,fast-math")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")
using namespace std;
const int N=122994+5;
int n,lc[N],rc[N];
int label[N];
const int K=429;//维度 
int clb[100];
struct Node{
	double x[K];
}s[N];
double lb[K][N],ub[K][N];
double avg[K],var[K];
typedef pair<double,int> pdi;
priority_queue<pdi> q; 
double dist(int a,int b){
	double ret=0;
	for(int i=0;i<K;++i){
		double t=s[a].x[i]-s[b].x[i];
		ret+=t*t;
	}
	return ret;
}
int fg;
struct cmp{
	bool operator () (const Node &a,const Node &b){
		return a.x[fg]<b.x[fg];
	}
};
void maintain(int x){
	for(int i=0;i<K;++i){
		lb[i][x]=ub[i][x]=s[x].x[i];
	}
	if(lc[x]){
		for(int i=0;i<K;++i){
			lb[i][x]=min(lb[i][x],lb[i][lc[x]]);
			ub[i][x]=max(ub[i][x],ub[i][lc[x]]);
		}
	}
	if(rc[x]){
		for(int i=0;i<K;++i){
			lb[i][x]=min(lb[i][x],lb[i][rc[x]]);
			ub[i][x]=max(ub[i][x],ub[i][rc[x]]);
		}
	}
}
int build(int l,int r){
	if(l>=r) return 0;
	int mid=l+r>>1;
	memset(avg,0,sizeof avg);
	for(int i=l;i<=r;++i){
		for(int j=0;j<K;++j){
			avg[j]+=s[i].x[j];
		}
	}
	int len=(r-l+1);
	for(int i=0;i<K;++i){
		avg[i]/=len;
	}
	for(int i=l;i<=r;++i){
		for(int j=0;j<K;++j){
			double t=s[i].x[j]-avg[j];
			var[j]+=t*t;
		}
	}
	fg=-1;//全局变量，要比较的第几个元素 
	double mx=0;
	for(int i=0;i<K;++i){
		if(var[i]>mx){
			mx=var[i];
			fg=i;
		}
	}
	printf("%d : %d\n",mid,fg);
	nth_element(s+l,s+mid,s+r+1,cmp());
	lc[mid]=build(l,mid-1);
	rc[mid]=build(mid+1,r);
	maintain(mid);
	return mid;
}
double f(int a,int b){
	double ret=0;
	for(int i=0;i<K;++i){
		if(lb[i][b]>s[a].x[i]){
			double t=lb[i][b]-s[a].x[i];
			ret+=t*t;
		}
		if(ub[i][b]<s[a].x[i]){
			double t=s[a].x[i]-ub[i][b];
			ret+=t*t;
		}
	}
	return ret;
}
void query(int l,int r,int x){
	if(l>r) return;
	int mid=l+r>>1;
	double t=dist(x,mid);
	if(t<q.top().first){
		q.pop();
		q.push(pdi(t,mid));
	}
	if(l==r) return;
	double d1=f(x,lc[mid]),d2=f(x,rc[mid]);
	if(d1<q.top().first&&d2<q.top().first){
		if(d1<d2){
			query(l,mid-1,x);
			if(d2<q.top().first) query(mid+1,r,x);
		}else{
			query(mid+1,r,x);
			if(d1<q.top().first) query(l,mid-1,x);
		}
	}else{
		if(d1<q.top().first) query(l,mid-1,x);
		if(d2<q.top().first) query(mid+1,r,x);
	}
}
int main(){
	FILE *fptr=fopen("train11.txt","r");
	n=122994;//train set size
	for(int i=1;i<=n;++i){
		for(int j=0;j<K;++j){
			fscanf(fptr,"%lf",&s[i].x[j]);
		}
	}
	fclose(fptr);
	puts("==========TRAIN SET READ OK==========");
	
	build(1,n);
	puts("==========BUILT TREE==========");
	
	FILE *fplb=fopen("label11.txt","r");
	for(int i=1;i<=n;++i){
		fscanf(fplb,"%d",&label[i]);
		++clb[label[i]];
	}
	for(int i=0;i<=38;++i){
		printf("%d : %d\n",i,clb[i]);
	}
	fclose(fplb);
	puts("==========LABEL READ OK==========");
	
	int m=150517;//test set size 
	FILE *fp=fopen("test150517.txt","r");
	FILE *out=fopen("res1st.csv","w");
	fprintf(out,"Id,Class\n");
	const int kk=50;//k nearest
	for(int i=1;i<=m;++i){
		for(int j=1;j<=kk;++j){
			q.push(pdi(2e18,-1));
		}
		for(int j=0;j<K;++j){
			fscanf(fp,"%lf",&s[n+1].x[j]);
		}
		map<int,int> cnt;
		query(1,n,n+1);
		while(!q.empty()){
			int now=label[q.top().second];
			++cnt[now];
			//printf("%d %.4lf %d\n",now,q.top().first,q.top().second);
			q.pop();
		}
		int ans=-1;
		double mx=0;
		for(auto t:cnt){
			if((double)t.second/clb[t.first]>mx){
				mx=(double)t.second/clb[t.first];
				ans=t.first;
			}
		}
		//puts("");
		printf("%d,%d\n",i-1,ans);
		fprintf(out,"%d,%d\n",i-1,ans);
	}
	return 0;
}

