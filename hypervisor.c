#include <linux/init.h>
#include <linux/module.h>
   
/* Basic kernel module */
// static int my_init(void)
// {
//     printk(KERN_INFO "Hello world.\n");
//     return  0;
// }
   
// static void my_exit(void)
// {
//     printk(KERN_INFO "Goodbye world.\n");

//     return;
// }
   
/* STEP 1: Check vmx support
// looking for CPUID.1:ECX.VMX[bit 5] = 1
*/
bool vmx_support(void)
{
    int get_vmx_support, vmx_bit; //integers for storing 5th bit
    /* INLINE ASSEMBLY */
    __asm__("mov $1, %rax"); //rax - 64 bit register
    __asm__("cpuid");
    

}


module_init(my_init);
module_exit(my_exit);

MODULE_LICENSE("GPL");