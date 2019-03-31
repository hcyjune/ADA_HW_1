#include <iostream>
#include <algorithm>
using namespace std;
int GetCrossMax(int arr[],int start,int mid,int end){
	long long leftMax=arr[mid],leftSum=0;
	long long rightMax=arr[mid+1],rightSum=0;
	for (int i=mid;i>=start;i--){
		leftSum+=arr[i];
		if (leftSum>leftMax){
			leftMax=leftSum;	
		}
	}
	for (int i=mid+1;i<=end;i++){
		rightSum+=arr[i];
		if (rightSum>rightMax){
			rightMax=rightSum;	
		}
	}
	return (max(max(leftMax,rightMax),leftMax+rightMax));
}
int GetMax(int arr[],int start,int end){
	if (start==end){
		return arr[start];
	}
	int mid=(start+end)/2;
	long long leftMax=GetMax(arr,start,mid);
	long long rightMax=GetMax(arr,mid+1,end);
	long long crossMax=GetCrossMax(arr,start,mid,end);
	return (max(max(leftMax,rightMax),crossMax));
}
int main(){
	int n,a[200000];
	cin>>n;
	for (int i=0;i<n;i++){
		cin>>a[i];
	}
	cout<<GetMax(a,0,n-1);
	return 0;	
} 
