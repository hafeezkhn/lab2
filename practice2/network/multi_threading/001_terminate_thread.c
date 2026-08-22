#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>


void thread_fn_callback(void* p)
{
   char* local_p = (char*)p;
   int count;
  while(1)
  {
     printf("%s\n",local_p);
     sleep(1);
     if(count == 5)
     {
      pthread_exit(0);
     }
    count++;
  }
}

void thread_create(void)
{
 pthread_t pthread1;
 static char *param="in thread1\n";
 pthread_create(&pthread1,
		 NULL,
		 thread_fn_callback,
		 (void*)param);

}



int main(int argc,char **argv)
{
 thread_create();
 printf("main thread Paused\n");
 pause();
 

return 0;
}
