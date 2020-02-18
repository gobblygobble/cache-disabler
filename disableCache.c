#include <linux/init.h>
#include <linux/module.h>
//#include <linux/kernel.h>

MODULE_LICENSE("Dual BSD/GPL");
static int disableCache_init(void)
{
#ifdef __x86_64__
	u64 cr0;
	printk(KERN_ALERT "Disabling caches for x86_64...\n");
	// disable cache
	__asm__(
		".intel_syntax noprefix\n\t"
		"mov	rax, cr0\n\t"
		"or	rax, (1 << 30)\n\t"
		"mov	cr0, rax\n\t"
		"wbinvd\n\t"
		".att_syntax noprefix\n\t"
	: : : "rax" );
	// print value of CR0
	__asm__ __volatile__ (
		"mov	%%cr0, %%rax\n\t"
		"mov	%%eax, %0\n\t"
	: "=m" (cr0)
	: /* no input */
	: "%rax"
	);
#elif defined(__i386__)
	u32 cr0;
	printk(KERN_ALERT "Disabling caches for x86_32...\n");
	// disable cache
	__asm__(
		".intel_syntax noprefix\n\t"
		"mov	eax, cr0\n\t"
		"or	eax, (1 << 30)\n\t"
		"mov	cr0, eax\n\t"
		"wbinvd\n\t"
		".att_syntax noprefix\n\t"
	: : : "eax" );
	// print value of CR0
	__asm__ __volatile__ (
		"mov	%%cr0, %%eax\n\t"
		"mov	%%eax, %0\n\t"
	: "=m" (cr0)
	: /* no input */
	: "%eax"
	);
#endif
	printk(KERN_INFO "cr0 = 0x%8.8X\n", cr0);
	return 0;
}

static void disableCache_exit(void)
{
#ifdef __x86_64__
	u64 cr0;
	printk(KERN_ALERT "Enabling caches for x86_64...\n");
	// enable cache
	__asm__(
		".intel_syntax noprefix\n\t"
		"mov	rax, cr0\n\t"
		"and	rax, ~(1 << 30)\n\t"
		"mov	cr0, rax\n\t"
		"wbinvd\n\t"
		".att_syntax noprefix\n\t"
	: : : "rax" );
	// print value of CR0
	__asm__ __volatile__ (
		"mov	%%cr0, %%rax\n\t"
		"mov	%%eax, %0\n\t"
	: "=m" (cr0)
	: /* no input */
	: "%rax"
	);
#elif defined(__i386__)
	u32 cr0;
	printk(KERN_ALERT "Enabling caches for x86_32...\n");
	// enable cache
	__asm__(
		".intel_syntax noprefix\n\t"
		"mov	eax, cr0\n\t"
		"and	eax, ~(1 << 30)\n\t"
		"mov	cr0, eax\n\t"
		"wbinvd\n\t"
		".att_syntax noprefix\n\t"
	: : : "eax" );
	// print value of CR0
	__asm__ __volatile__ (
		"mov	%%cr0, %%eax\n\t"
		"mov	%%eax, %0\n\t"
	: "=m" (cr0)
	: /* no input */
	: "%eax"
	);
#endif
	printk(KERN_INFO "cr0 = 0x%8.8X\n", cr0);
	return;
}
module_init(disableCache_init);
module_exit(disableCache_exit);
