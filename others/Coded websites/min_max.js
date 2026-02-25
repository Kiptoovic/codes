function reverse(arr){
    left = 0
    right = arr.length -1
    while(left < right){
        temp = arr[left];
        arr[left] = arr[right];
        arr[right] = temp;

        left++;
        right--;
    }
    return 0;
}