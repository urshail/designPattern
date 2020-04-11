//Singelton Design Pattern

#include<iostream>
#include<pthread.h>
#include<time.h>
#include<unistd.h>

#include<chrono>
#include<ctime>

using namespace std;

class hardware
{
	int bladeV;
	static hardware *so;
	static pthread_mutex_t ml;
	hardware()
	{
		if(pthread_mutex_init(&ml,NULL)!=0)
		{
			cout<<"pthread init failed"<<endl;
		}
		bladeV = 4;
		cout<<"hardware cons"<<endl;
	}
	~hardware()
	{
		pthread_mutex_destroy(&ml);
	}
    public:
	static hardware* getInstance()
	{
		if(so == NULL) //save CPU cycles. Locking and unlocking is heavy system resources. if 1000 threads are there, each have to lock and unlock. 
                   // Simple null check will avoid it. If instance is already created, no need to enter into any of object creation step.
		{
		  pthread_mutex_lock(&ml); //Lock is required to avoid multithreading problem where two threads can be executed at same time.
		  cout<<"lock taken"<<endl;	
		  if(so==NULL)
		     so = new hardware;
		  cout<<"lock released"<<endl;	
		  pthread_mutex_unlock(&ml);	
		  cout<<"get instance :"<<so<<endl;
		}
		return so;
	}
        void blade()
        {
                cout<<"got blades "<<bladeV<<endl;
        }
};
//static has be initialzed before use.
hardware *hardware::so = NULL;
pthread_mutex_t hardware::ml;

//Created this function just to execute it with threads.  
void* hIns(void *varg)
{
	hardware::getInstance()->blade();
}

int main()
{
	pthread_t th1,th2,th3;
	clock_t stime,etime;
	stime=clock();
	std::clock_t c_start = std::clock();
	for(int i=0;i<2000;i++)
	{
	  pthread_create(&th1,NULL,hIns,NULL);
	  pthread_create(&th2,NULL,hIns,NULL);
	  pthread_create(&th3,NULL,hIns,NULL);
	  pthread_join(th1,NULL);
	  pthread_join(th2,NULL);
	  pthread_join(th3,NULL);
	  usleep(300);
	}
  
  //Clock functions to compare time if locking/unlocking takes more time and it can be avoided with object NULL check.
  	std::clock_t c_end = std::clock();
	cout<<1.0 * (c_end-c_start) / CLOCKS_PER_SEC<< "time diff"<<endl;
	etime=clock();

	cout<<"stime "<<stime<<"  etime "<<etime<<endl;
	etime=float (etime-stime)/CLOCKS_PER_SEC;
	cout<<"total time taken is :"<<etime<<endl;
	return 0;
}
