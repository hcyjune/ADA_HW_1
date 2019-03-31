#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;
vector<unsigned long long> Product(vector<unsigned long long> &p){
	int n=p.size();
	vector<unsigned long long> result;
	if (n<=4){
		if (n==4){
			result.resize(7,0);
			result[0]=p[0]*p[0];
			result[1]=2*p[0]*p[1];
			result[2]=2*p[0]*p[2]+p[1]*p[1];
			result[3]=2*p[0]*p[3]+2*p[1]*p[2];
			result[4]=2*p[1]*p[3]+p[2]*p[2];
			result[5]=2*p[2]*p[3];
			result[6]=p[3]*p[3];
		}
		else if (n==3){
			result.resize(5,0);
			result[0]=p[0]*p[0];
			result[1]=2*p[0]*p[1];
			result[2]=2*p[0]*p[2]+p[1]*p[1];
			result[3]=2*p[1]*p[2];
			result[4]=p[2]*p[2];
		}
		else if (n==2){
			result.resize(3,0);
			result[0]=p[0]*p[0];
			result[1]=2*p[0]*p[1];
			result[2]=p[1]*p[1];
		}
		else if (n==1){
			result.push_back(p[0]*p[0]);
		}
	}
	else{
		int m=ceil(n/2.0);//m>=n-m
		vector<unsigned long long> b(p.begin(),p.begin()+m);
		vector<unsigned long long> a(p.begin()+m,p.end());
		vector<unsigned long long> ab(p.begin(),p.begin()+m);
		for (int i=m;i<n;i++){//n-m
			ab[i-m]+=p[i];
		}
		vector<unsigned long long> high=Product(a);
		vector<unsigned long long> low=Product(b);
		vector<unsigned long long> all=Product(ab);	
		result.resize(high.size()+2*m,0);
		for (int i=0;i<low.size();i++){
			result[i]=low[i];
		}
		for (int i=0;i<all.size();i++){
			if(i<high.size()){
				result[i+m]+=all[i]-high[i]-low[i];
				result[i+2*m]+=high[i];
			}
			else{
				result[i+m]+=all[i]-low[i];
			}
		}
	}
	return result;
}
int main(){
	int n,m,k,largest=0,tmp;
	vector<int> a;
	vector<unsigned long long> v,v_ans;
	scanf("%d",&n);
	a.reserve(n);
	for (int i=0;i<n;i++){
		scanf("%d",&tmp);
		a[i]=tmp;
		if (tmp>largest){
			largest=tmp;
		}
	}
	v.resize(largest+1,0);
	for (int i=0;i<n;i++){
		v[a[i]]+=1;
	}
	v_ans=Product(v);	
	/*for (int i=0;i<v_ans.size();i++){
		cout<<v_ans[i]<<' ';
	}
	cout<<endl;*/
	
	scanf("%d",&m);
	for (int i=0;i<m;i++){
		scanf("%d",&k);
		if (k>2*largest){
			printf("0");
		}
		else{
			if (k%2==0){
				printf("%llu",(v_ans[k]-v[k/2])/2);
			}
			else{
				printf("%llu",v_ans[k]/2);
			}	
		}
		if (i!=m-1){
			printf(" ");
		}
	}
	return 0;
}
