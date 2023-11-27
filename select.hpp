/*
 * @Author: zanilia
 * @Date: 2022-03-21 15:20:13
 * @LastEditTime: 2022-04-12 16:16:31
 * @Descripttion: 
 */
int findPivot(int *arr,int left,int right);
static inline void swap(int* i1,int* i2){
	int tem = *i1;
	*i1 = *i2;
	*i2 = tem;
}
int partition(int* list,int left,int right,int index,int n){
    int pivot = list[index];
    swap(list+index,list+right);
    int  storeIndex = left;
	for(int i=left;i<right;++i){
		if(list[i]<pivot){
			swap(list+i,list+storeIndex);
			++storeIndex;
		}
	}
    int storeIndexEq = storeIndex;
    for(int i=storeIndex;i<right;++i)
        if(list[i]==pivot)
            swap(list+(storeIndexEq++),list+i);
    swap(list+right,list+storeIndexEq);
    if(n<storeIndex)
        return storeIndex;
    if(n<=storeIndexEq)
        return n;
    return storeIndexEq;
}
int partition5(int *arr,int left,int right){
	for(int i=left+1;i<=right;++i)
		for(int j=i;j>left&&arr[j-1]>arr[j];--j)
			swap(arr+j-1,arr+j);
    return (left+right)/2;
}
int findKth(int* arr,int left,int right,int k){
	while(1){
		if(left==right)
			return left;
		int pivot = findPivot(arr,left,right);
		pivot = partition(arr,left,right,pivot,k);
		if(k==pivot)
			return k;
		else if(k<pivot)
			right = pivot-1;
		else
			left = pivot+1;
	}
}
int findPivot(int *arr,int left,int right){
	if(right-left<5)
		return partition5(arr, left, right);
	for(int i=left;i<=right;i+=5){
		int end = i+4;
		if(end>right)
			end = right;
		int median = partition5(arr,i,end);
		swap(arr+median,arr+left+(i-left)/5);
	}
	int mid = (right-left)/10+left + 1;
    return findKth(arr,left,left+(right-left)/5,mid);
}