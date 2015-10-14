#include <omp.h>
#include <stdio.h>
#define NUM_THREADS 2
static long steps=1000000;
double step_size;

int main ()
{
	
	int i;

	double sum[NUM_THREADS],pi,start_time,final_time;

	start_time=omp_get_wtime();
	step_size=1.0/(double)steps;


	#pragma omp parallel
	{
		int id,i;
		double x;
		id=omp_get_thread_num();

		for(i=id,sum[id]=0.0;i<steps;i=i+NUM_THREADS)
		{
			x=(i+0.5)*step_size;
			sum[id]+=4.0/(1.0+x*x);
		}
	}

	for(i=0,pi=0.0;i<NUM_THREADS;i++)	pi+=sum[i]*step_size; 

	final_time=omp_get_wtime()-start_time;

	printf("Value of pi =%lf\n",pi);
	printf("Time taken =%lf\n",final_time);
	printf("Number of threads %d\n",NUM_THREADS);

}