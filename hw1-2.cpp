#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
using namespace std;
struct point{
	int x;
	int y;
	int xy;
};
bool comp_x (point p1,point p2){
	return p1.x < p2.x;
}
bool comp_y (point p1,point p2){
	return p1.y < p2.y;
}
unsigned long long bruteForce(vector<point> &p,int start,int end){
	unsigned long long sum=0;
	for (int i=start;i<=end;i++){
		for (int j=i+1;j<=end;j++){
			int len=abs(p[i].x-p[j].x);
			int wid=abs(p[i].y-p[j].y);
			sum+=len*wid;			
		}
	}
	return sum;
}

unsigned long long crossRectangle(vector<point> &p,int start,int cross,int end){
	unsigned long long sum1_x=0,sum1_y=0,sum1_xy=0,sum2_x=0,sum2_y=0,sum2_xy=0,sum=0,area,one=1;
	vector<point>::iterator iter;
	sort(p.begin()+start,p.begin()+cross+1,comp_y);//ending+1(not included)
	sort(p.begin()+cross+1,p.begin()+end+1,comp_y);
	iter=upper_bound(p.begin()+cross+1,p.begin()+end+1,p[cross],comp_y);//ending+1
	int edge=iter-p.begin();	
	for (int i=cross+1;i<edge;i++){
		sum1_x+=p[i].x;
		sum1_y+=p[i].y;
		sum1_xy+=p[i].xy;
	}	
	for (int i=edge;i<=end;i++){
		sum2_x+=p[i].x;
		sum2_y+=p[i].y;
		sum2_xy+=p[i].xy; 
	}
	sum=0;
	int j=edge-1,n1,n2;
	for (int i=cross;i>=start;i--){		
		while(p[i].y<p[j].y and j>=cross+1){
			sum1_x-=p[j].x;sum2_x+=p[j].x;
			sum1_y-=p[j].y;sum2_y+=p[j].y;
			sum1_xy-=p[j].xy;sum2_xy+=p[j].xy;
			j-=1;
		}
		n1=j-cross;
		n2=end-j;
		area=one*n2*p[i].xy+sum2_xy-p[i].y*sum2_x-p[i].x*sum2_y;
		area-=one*n1*p[i].xy+sum1_xy-p[i].y*sum1_x-p[i].x*sum1_y;
		sum+=area;
	}
	return sum;	
}
unsigned long long Rectangle(vector<point> &p,int start,int end){
	int n=end-start+1;
	if (n<=3){
		return bruteForce(p,start,end);
	}
	int mid=start+n/2;
	unsigned long long leftSum=Rectangle(p,start,mid-1);
	unsigned long long rightSum=Rectangle(p,mid,end);
	unsigned long long crossSum=crossRectangle(p,start,mid-1,end);
	unsigned long long sum=leftSum+rightSum+crossSum;
	return sum;
}
int main(){
	int s;
	struct point a;
	vector<point> v;
	cin>>s;
	for (int i=0;i<s;i++){
		scanf("%d",&a.x);
		scanf("%d",&a.y);
		a.xy=a.x*a.y;
		v.push_back(a);
	}
	sort(v.begin(),v.end(),comp_x);
	printf("%llu",Rectangle(v,0,s-1));
	return 0;
}
