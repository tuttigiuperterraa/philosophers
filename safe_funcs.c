#include "philosophers.h"

void *safe_malloc(size_t bytes)
{
    void *out;

    out = malloc(bytes);
    if (!out)
        error_exit("Malloc: malloc returned NULL!");
    return(out);
}

void    handle_mutex_error(int status, t_code opc)
{
    if (status == 0)
        return;
    if (status == EINVAL && (opc == LOCK || opc == UNLOCK))
        error_exit("The value specified by mutex is invalid.");
    else if (status == EDEADLK)
        exit_error("A deadlock would occur if the thread blocked waiting for mutex.");
    else if (status == EPERM)
        error_exit("The current thread does not hold a lock on mutex.");
    else if (status == ENOMEM)
        error_exit("The process cannot allocate enough memory to create another mutex.");
    else if (status == EBUSY)
        error_exit("Mutex is locked.");
    
}

void safe_mutex(pthread_mutex_t *mutex, t_code opc)
{
    if (opc == LOCK)
        handle_mutex_error(pthread_mutex_lock(mutex), opc);
    else if (opc == UNLOCK)
        handle_mutex_error(pthread_mutex_unlock(mutex), opc);
    else if (opc == INIT)
        handle_mutex_error(pthread_mutex_init(mutex, NULL), opc);
    else if (opc == DESTROY)
        handle_mutex_error(pthread_mutex_destroy(mutex), opc);
    else
        handle_mutex_error(error_ext("MUTEX: Wrong opc CODE"), opc);   
}

static void	handle_thread_error(int status, t_code opc)
{
	if (0 == status)
		return ;
	if (EAGAIN == status)
		error_exit("No resources to create another thread");
	else if (EPERM == status)
		error_exit("The caller does not have appropriate permission\n");
	else if (EINVAL == status && CREATE == opc)
		error_exit("The value specified by attr is invalid.");
	else if (EINVAL == status && (JOIN == opc || DETACH == opc))
		error_exit("The value specified by thread is not joinable\n");
	else if (ESRCH == status)
		error_exit("No thread could be found corresponding to that"
			"specified by the given thread ID, thread.");
	else if (EDEADLK == status)
		error_exit("A deadlock was detected or the value of"
			"thread specifies the calling thread.");
}

void	safe_thread(pthread_t *thread, void *(*foo)(void *),
		void *data, t_code opc)
{
	if (CREATE == opc)
		handle_thread_error(pthread_create(thread, NULL, foo, data), opc);
	else if (JOIN == opc)
		handle_thread_error(pthread_join(*thread, NULL), opc);
	else if (DETACH == opc)
		handle_thread_error(pthread_detach(*thread), opc);
	else
		error_exit("Wrong opc for thread_handle:"
			" use <CREATE> <JOIN> <DETACH>");
}
