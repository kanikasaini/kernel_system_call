SYSCALL_DEFINE2(sh_task_info, pid_t, my_pid , char* , fname )
{		
	struct task_struct *process;
	struct pid *pid_struct;
	struct file *file;
	pid_struct=find_get_pid(my_pid);
	if(pid_struct==NULL)
		return -ESRCH;
	process=pid_task(pid_struct, PIDTYPE_PID);
	char data[1001]; 
	int len; 
	if(process->parent)
	{
		len=sprintf(data, "Process: %s\nPID: %ld\nProcess State: %ld\nPriority: %ld\nParent Process: %s\nParent PID: %ld\n", process->comm, (long)task_pid_nr(process), (long)process->state, (long)process->prio, process->parent->comm, (long)task_pid_nr(process->parent));
	}
	else
    	{
	len=sprintf(data, "Process: %s\nPID_Number: %ld\nProcess State: %ld\nPriiority: %ld\n ", process->comm, (long)task_pid_nr(process), (long)process->state, (long)process->prio);
	}
	loff_t pos=0;
	mm_segment_t old_fs = get_fs();
  	int fd; 
	set_fs(KERNEL_DS);
	fd = sys_open(fname, O_WRONLY|O_CREAT|O_EXCL, 0644);
	if(fd==-EEXIST)
		return -EEXIST;
	if (fd >= 0) {
	  sys_write(fd, data, strlen(data));
	  file = fget(fd);
	  if (file) {
	    vfs_write(file, data, strlen(data), &pos);
	    fput(file);
	  }
	  sys_close(fd);
	}
	set_fs(old_fs);
	printk( KERN_EMERG "fd= %d\ntask_struct fields corresponding to the pid:\n%s\n",fd, data);		
  	return 0;
}
/
