#include <stdio.h>
#include <stdlib.h>

void merge(int a[],int l,int mid,int r){
    //归并排序的核心在于递归和归并
    int *temp=(int*)malloc((r-l+1)*sizeof(int));
    int i=l,j=mid+1,k=0;

    while(i<=mid && j<=r){//两个区间均未完全遍历完成时进行循环
        //每次比较左右两个区间最小的数，将更小者放入temp临时数组中
        if(a[i]<=a[j]){
            temp[k++]=a[i++];
        }else{
            temp[k++]=a[j++];
        }
    }

    //一个区间放完后，另一个区间剩余元素放到temp数组剩余位置即可
    while(i<=mid)   temp[k++]=a[i++];
    while(j<=r)     temp[k++]=a[j++];

    //把数据覆盖回原数组
    for(i=l,k=0;i<=r;i++,k++){
        a[i]=temp[k];
    }

    free(temp);
}

void mergesort(int a[],int l,int r){
    if(l<r){//划分得到的区间长度大于1才需要进行处理
        int mid=(l+r)/2;//取中间位置划分左右区间
        mergesort(a,l,mid);//对左区间排序
        mergesort(a,mid+1,r);//对右区间排序
        merge(a,l,mid,r);//归并左右区间
    }
}
//打印数组
void printarray(int arr[],int size){
	int i; 
    for(i=0;i<size;i++){
        printf("%d  ",arr[i]);
    }
    printf("\n");
}

//主函数
int main(){
    // int arr[]={23,41,56,18,76,69,57,18,26,45,30};
    // int n=sizeof(arr)/sizeof(arr[0]);
    int n,arr[100];
    int i;
    printf("要排序数组的规模大小是：");
    scanf("%d",&n);
    for(i=0;i<n;++i){
        printf("输入第%d个数据元素：",i);
        scanf("%d",&arr[i]);
    }
    printf("输入数组是：\n");
    printarray(arr,n);
    mergesort(arr,0,n-1);
    printf("升序排序之后得到数组为：\n");
    printarray(arr,n);
    return 0;
    //可以测试数据：输入6
	//输入： 20 90 40 10 30 50
}


//gcc merge.c -o merge.exe
