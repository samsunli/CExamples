#include <stdio.h>
 enum { SIZE = 32 };

int main(void){
        void *p;
        int a = 14322;
        char c  = 'A';
        p = &a;
        //p = &c;
        //强制类型转换(int*)p 把变量指针p强制转换成指向int类型的指针
        printf("a=%d\n", *(int*)p);
        p = &c;
        printf("c=%c\n", *(int*)p);
        printf("pointer=%d\n", (int*)p);

    int nums[SIZE] = {0};
    int *next_num_ptr = nums;
    size_t free_elements;
 
    int *tail_ptr = &(nums[SIZE]);
    /* Increment next_num_ptr as array fills */
 
    free_elements = &(nums[SIZE]) - next_num_ptr;
    

    printf("free_elements=%d\n", free_elements);
    printf("head ptr =%d\n", nums);
    printf("tail_ptr =%d\n", tail_ptr);
    printf("nums 31 =%d\n", nums[31]);
    printf("nums 32 =%d\n", nums[32]);
        
        return 0;      
}