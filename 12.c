#include <stdio.h>
// Declaring functions used
void bubbleSort(int *arr,int n);
void printArray(int *arr,int n);

int main(void){
// Initializing the array of weights of fruits
    int fruits[]={250,150,350,200,300};
// finding no of elements in the array;
    int n=sizeof(fruits)/sizeof(fruits[0]);

    printf("Sorting Fruits based on weight\n");
// Array before bubble sort
    printf("Intial array:\n");
    printArray(fruits,n);
// Bubble sort
    bubbleSort(fruits,n);
    printf("\n");
// Array after bubble sort
    printf("Sorted array:\n");
    printArray(fruits,n);

    return 0;
}
// Function used to perform bubble sort
void bubbleSort(int *arr,int n){
    int temp=0;
    for(int i=0;i<n;i++){
        for(int j=i+1;j<n;j++){
            if(arr[i]>arr[j]){
                temp=arr[i];
                arr[i]=arr[j];
                arr[j]=temp;
            }
        }
    }
}
// Function to print array
void printArray(int *arr,int n){
    for(int i=0;i<n;i++){
        printf("\t%d",arr[i]);
    }
}
