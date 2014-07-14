#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define LEN  1000000
/**
 *
 * check the subString is a palindrom
 *
**/
bool isPali(char * str, int start, int end){
	int i = start ,j = end;
	if( end < start)
		return true;
	while(i<j){
		if(str[i]!=str[j])
			return false;
		i++;
		j--;
	}
	return true;
}
/**
 *
 * using brute forse method
 * GOT TLE , time complexity is O(n^3);
 *
**/
int method1(char * str, int n){
	int sz = 0;
	int start = 0; //start index
	int end = 0; //end index
	int ret = 1;

	for(sz = n; sz>=2; sz--){
		for(start = 0; start <= n-sz; start ++){
			end = start + sz - 1;
			if(isPali(str, start, end)){
				return sz;
			}
		}
	}
	return 1;
}
/**
 *
 * using space for saving time
 * time complexity is O(n^2), space complexity is O(n^2)
 * GOT TLE, space complexity is 67M
 *
**/
int method2(char * str, int n){
	bool **dp = NULL;
	int ret = 1;
	int sz = 1;
	int start = 0; //start index
	int end = 0; // end index

	dp = (bool**)malloc(n*sizeof(bool*));
	for(sz = 0;sz<n;sz++){
		*(dp+sz) = (bool*)malloc(sizeof(bool) * n);
	}
	for(sz=1;sz<=n;sz++){
		for(start = 0; start<= n-sz; start ++){
			if(sz == 1) //a character is palindom
				dp[start][start] = true;
			else{
				end = start + sz - 1;
				if(str[start] == str[end])//the start and the end element are the same
				{
					//the middle part is the pali
					if(end-1>start+1 && dp[start+1][end-1] == true){ 
						ret = sz>ret? sz:ret;
						dp[start][end] = true;
					}else if(end-1 <= start+1){
						ret = sz>ret? sz:ret;
						dp[start][end] = true;
					}else
						dp[start][end] = false;
				}else
					dp[start][end] = false;
			}
		}
	}
	return ret;
}
/**
 *
 * using DP solution:
 * f[i] means center str[i], and its longest palindome
 * f[i] >= min{f[2*j-i], f[j] - 2*(i-j)}, where j = max{j'+f[j']/2}, where j'<i
 *
**/
int method3(char * str, int n){
	int *f = (int*)malloc(sizeof(int) * n);
	int j=1; //mark the center the element j, whose the right bound is the furthest
	int i=0;
	int k1=0;
	int k2=0;
	int ret = 1; //the return result
	int tmp = 0;

	if(n == 1)
		return 1;
	//the first two spacial cases
	f[0] = 1;
	f[1] = str[0] == str[2]? 3:1;
	for(i=2;i<n;i++){
		//first we can get the minimum length of the palindome centered at i
		f[i] = f[2*j-i] <=f[j]-2*(i-j) ? f[2*j-i] : f[j]-2*(i-j);
		//if the f[i] < 0, we should change it into 1
		f[i] = f[i] > 0 ? f[i] : 1;
		//by expending from two sides, we try to find the completet palindome centered at i
 		k1 = i-f[i]/2-1;
		k2 = i+f[i]/2+1;
		while(k1>=0 && k2<n && str[k1] == str[k2]){
			f[i] = f[i]+2;
			k1--;
			k2++;
		}
		// update j if necessary
		if(i+f[i]/2>j+f[j]/2)
			j=i;
	}
	//find the longest palindome, watch out the special character
	for(i=1;i<n;i++){
		if(i%2 == 0){
			if((f[i]/2)%2 == 0){ // a oushu
				tmp = f[i]-f[i]/2;
			}else { // a jishu
				tmp = f[i] - f[i]/2 -1;
			}
		}else {
			if((f[i]/2)%2 == 0){ // * oushu
				tmp = f[i]-f[i]/2 - 1;
			}else { // * jishu
				tmp = f[i] - f[i]/2;
			}
		}
		if(tmp > ret)
			ret = tmp;
	}
	free(f);
	return ret;
}
int main(){
	int N = 0;
	int i = 0;
	int j=0,k=0;
	char str[LEN];
	int ln = 0;

	//read the total number of strings
	scanf("%d",&N);
	
	while(i<N){
		scanf("%s",str);
		ln = strlen(str);
		//insert a '*', to make all even palindome into odd palindome
		char * ctr = (char *) malloc(sizeof(char) * (ln+ln-1));
		ctr[0] = str[0];
		for(j=1,k=1;j<ln;j++){
			ctr[k++] = '*';
			ctr[k++] = str[j];
		}
		printf("%d\n",method3(ctr, 2*ln-1));
		//remember to free the pointer , otherwise Got MLE
		free(ctr);	
		i++;
	}
	return 0;
}