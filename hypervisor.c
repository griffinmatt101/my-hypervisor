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

looking for CPUID.1:ECX.VMX[bit 5] = 1
Encoding for VMXON (Enter VMX Operation):
Enter VMX. 11110011 000011111 11000111: mod 110 r/m

*/
bool vmx_support(void)
{
    int get_vmx_support, vmx_bit; //integers for storing 5th bit
    /* INLINE ASSEMBLY */
    __asm__("mov $1, %rax"); //rax - 64 bit register
    __asm__("cpuid");
    __asm__("mov %%ecx , % 0\n\t":"=r" (get_vmx_support));
    vmx_bit = (get_vmx_support >> 5) & 1;

    if(vmx_bit == 1)
    {
        return true;
    }
    else
    {
        return false;
    }
    

}

//MSR - Mode Specific Register
//WRMSR - Write to Mode Specific Register
#define X86_CR4_VMXE_BIT    13 /* enables VMX virtualization */
#define X86_CR4_VMXE        _BITUL(X86_CR4_VMXE_BIT)
#define FEATURE_CONTROL_VMXON_ENABLES_OUTSIDE_SMX   (1<<2) /* bit 2 */
#define FEATURE_CONTROL_LOCKED  (1<<0) /* bit 0 */
#define MSR_IA32_FEATURE_CONTROL    0x0000003a
bool getVmxOperation(void)
{
    unsigned long cr4;
    // set CR4.VMXE[bit 13] = 1
    __asm__ __volatile__("mov %%cr4, %0" : "=r"(cr4) : : "memory");
    cr4 |= X86_CR4_VMXE;
    __asm__ __volatile__("mov %0, %%cr4" : : "r"(cr4) : "memory");

    //configure IA32_FEATURE_CONTROL MSR to allow VMXON
    required = FEATURE_CONTROL_VMXON_ENABLES_OUTSIDE_SMX;
    required |= FEATURE_CONTROL_LOCKED;
    feature_control = __rdmsr1(MSR_IA32_FEATURE_CONTROL);
    printk(KERN_INFO "RDMS output is %ld", (long)feature_control);

    if ((feature_control & required != required))
    {
        wrmsr(MSR_IA32_FEATURE_CONTROL, feature_control | required, low1);
    }
    //TODO: import wrmsr from asm/msr.h
    //TODO: write __rdmsr1 function
}


module_init(my_init);
module_exit(my_exit);

MODULE_LICENSE("GPL");