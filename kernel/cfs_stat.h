struct cfs_stat { // struct of cfs statistics, will be used with get_cfs_stats system call
  int priority;     
  long long runtime;    
  long long sleeptime;  
  long long retime; 
};