
/* auto-generated by gen_syscalls.py, don't edit */
#ifndef Z_INCLUDE_SYSCALLS_KOBJECT_H
#define Z_INCLUDE_SYSCALLS_KOBJECT_H


#include <tracing/tracing_syscall.h>

#ifndef _ASMLANGUAGE

#include <syscall_list.h>
#include <syscall.h>

#include <linker/sections.h>


#if __GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 6)
#pragma GCC diagnostic push
#endif

#ifdef __GNUC__
#pragma GCC diagnostic ignored "-Wstrict-aliasing"
#if !defined(__XCC__)
#pragma GCC diagnostic ignored "-Warray-bounds"
#endif
#endif

#ifdef __cplusplus
extern "C" {
#endif

extern void z_impl_k_object_access_grant(const void * object, struct k_thread * thread);

__pinned_func
static inline void k_object_access_grant(const void * object, struct k_thread * thread)
{
#ifdef CONFIG_USERSPACE
	if (z_syscall_trap()) {
		/* coverity[OVERRUN] */
		arch_syscall_invoke2(*(uintptr_t *)&object, *(uintptr_t *)&thread, K_SYSCALL_K_OBJECT_ACCESS_GRANT);
		return;
	}
#endif
	compiler_barrier();
	z_impl_k_object_access_grant(object, thread);
}

#if (CONFIG_TRACING_SYSCALL == 1)
#ifndef DISABLE_SYSCALL_TRACING

#define k_object_access_grant(object, thread) do { 	sys_port_trace_syscall_enter(K_SYSCALL_K_OBJECT_ACCESS_GRANT, k_object_access_grant, object, thread); 	k_object_access_grant(object, thread); 	sys_port_trace_syscall_exit(K_SYSCALL_K_OBJECT_ACCESS_GRANT, k_object_access_grant, object, thread); } while(false)
#endif
#endif


extern void z_impl_k_object_release(const void * object);

__pinned_func
static inline void k_object_release(const void * object)
{
#ifdef CONFIG_USERSPACE
	if (z_syscall_trap()) {
		/* coverity[OVERRUN] */
		arch_syscall_invoke1(*(uintptr_t *)&object, K_SYSCALL_K_OBJECT_RELEASE);
		return;
	}
#endif
	compiler_barrier();
	z_impl_k_object_release(object);
}

#if (CONFIG_TRACING_SYSCALL == 1)
#ifndef DISABLE_SYSCALL_TRACING

#define k_object_release(object) do { 	sys_port_trace_syscall_enter(K_SYSCALL_K_OBJECT_RELEASE, k_object_release, object); 	k_object_release(object); 	sys_port_trace_syscall_exit(K_SYSCALL_K_OBJECT_RELEASE, k_object_release, object); } while(false)
#endif
#endif


extern void * z_impl_k_object_alloc(enum k_objects otype);

__pinned_func
static inline void * k_object_alloc(enum k_objects otype)
{
#ifdef CONFIG_USERSPACE
	if (z_syscall_trap()) {
		/* coverity[OVERRUN] */
		return (void *) arch_syscall_invoke1(*(uintptr_t *)&otype, K_SYSCALL_K_OBJECT_ALLOC);
	}
#endif
	compiler_barrier();
	return z_impl_k_object_alloc(otype);
}

#if (CONFIG_TRACING_SYSCALL == 1)
#ifndef DISABLE_SYSCALL_TRACING

#define k_object_alloc(otype) ({ 	void * retval; 	sys_port_trace_syscall_enter(K_SYSCALL_K_OBJECT_ALLOC, k_object_alloc, otype); 	retval = k_object_alloc(otype); 	sys_port_trace_syscall_exit(K_SYSCALL_K_OBJECT_ALLOC, k_object_alloc, otype, retval); 	retval; })
#endif
#endif


#ifdef __cplusplus
}
#endif

#if __GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 6)
#pragma GCC diagnostic pop
#endif

#endif
#endif /* include guard */