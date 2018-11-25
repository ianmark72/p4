# p4

malloc537
  Steps
    Use malloc() to allocate memory.
    Store address and length of malloc
  
  Notes
    Return value is the address
    Use the size parameter for the length
    Its different for memory that was previously freed
    Check for 0 length 

free537
  Steps
    Check if memory can be freed
    Call free()
    Print error or what has been freed
    
  Possible Errors
    Memory not allocated by malloc537
    An address that's not the beginning of a malloc
    Freeing memory that's already free
    
realloc537
  Steps
    Check memory 
    Call realloc()
    Store address and length
    
  Notes
      If ptr is NULL then call malloc537
      If size is 0 and ptr is NULL call free537()
      
memcheck537
  Steps
    Check if the length fits within the space allocated
    Check if the memory was not previously freed by free537
    If error is detected then print an error and exit with -1 status
    
