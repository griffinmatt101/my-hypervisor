# my-hypervisor

## Step 0: Create Makefile and test kernel module

## Step 1: Check support for VMX
- uses inline assembly
- call `cpuid` with `eax=1`
- bit 5 in `eax` will show support


## Support
- https://nixhacker.com/developing-hypervisor-from-scratch-part-2/
- https://www.intel.in/content/www/in/en/architecture-and-technology/64-ia-32-architectures-software-developer-system-programming-manual-325384.html