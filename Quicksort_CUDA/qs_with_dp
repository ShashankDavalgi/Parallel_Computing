_global_ void quicksort(int *data, int left, int right)
{
  int nleft,nright;
  cudaStream_t s1,s2;
  
  partition(data+left, data+right, data[left], nleft, nright);
  
  if(left < nright) {
    cudaStreamCreateWithFlags(&s1, cudaStreamNonBlocking);
    quicksort<<< ..., s2 >>>(data, left, nright);
    }
    
  if(nleft < right) {
    cudaStreamCreateWithFlags(&s1, cudaStreamNonBlocking);
    quicksort<<< ..., s2 >>>(data, nleft, right);
    }
}

_host_ void launch_quicksort(int *data, int count)
{
  quicksort<<< ... >>>(data, 0, count-1);
}
