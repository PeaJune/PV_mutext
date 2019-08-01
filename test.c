#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

pthread_mutex_t mutex_b = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond_b = PTHREAD_COND_INITIALIZER;
int b_cnt = 0;

pthread_mutex_t mutex_c = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond_c = PTHREAD_COND_INITIALIZER;
int c_cnt = 0;

pthread_mutex_t mutex_d = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond_d = PTHREAD_COND_INITIALIZER;
int d_cnt = 0;



void *thread_a(void *);
void *thread_b(void *);
void *thread_c(void *);
void *thread_d(void *);

void *thread_a(void *arg)
{
	while(1)
	{
		;;		
	}
}

void *thread_b(void *arg)
{
	while(1)
	{
		pthread_mutex_lock(&mutex_b);
		if(b_cnt == 1)
		{
			pthread_mutex_unlock(&mutex_b);
			continue;
		}
		printf("read b\n");
		b_cnt = 1;
		pthread_cond_signal(&cond_c);	
		pthread_mutex_unlock(&mutex_b);
	}
}

void *thread_c(void *arg)
{
	while(1)
	{
		pthread_mutex_lock(&mutex_c);
		if(c_cnt == 1)
		{
			pthread_mutex_unlock(&mutex_c);
			continue;
		}
		printf("read c\n");
		c_cnt = 1;
		pthread_cond_signal(&cond_c);	
		pthread_mutex_unlock(&mutex_c);
	}
}

void *thread_d(void *arg)
{
	while(1)
	{
		pthread_mutex_lock(&mutex_c);
		if(d_cnt == 1)
		{
			pthread_mutex_unlock(&mutex_c);
			continue;
		}
		printf("read d\n");
		d_cnt = 1;
		pthread_cond_signal(&cond_d);	
		pthread_mutex_unlock(&mutex_c);
	}
}

int main(void)
{
    pthread_t t_a;
    pthread_t t_b;
    pthread_t t_c;
    pthread_t t_d;

    pthread_create(&t_a,NULL,thread_a,(void *)NULL);
    pthread_create(&t_b,NULL,thread_b,(void *)NULL);
    pthread_create(&t_c,NULL,thread_c,(void *)NULL);
    pthread_create(&t_d,NULL,thread_d,(void *)NULL);
    pthread_join(t_b, NULL);
    pthread_mutex_destroy(&mutex_b);
    pthread_mutex_destroy(&mutex_c);
    pthread_mutex_destroy(&mutex_d);
    pthread_cond_destroy(&cond_b);
    pthread_cond_destroy(&cond_c);
    pthread_cond_destroy(&cond_d);
    exit(0);
}


