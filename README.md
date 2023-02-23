# my-hypervisor

## Step 0: Create Makefile and test kernel module

## Step 1: Check support for VMX
- uses inline assembly
- call `cpuid` with `eax=1`
- bit 5 in `eax` will show support

## Notes
- Chapter 23 of Intel's Software Developer Manual
    - Virtual-machine Monitors (VMM)
        - acts as a host and has full control of the processor(s) and other hardware
        - presents guest software with an abstraction of a virutal processor
            - allows it to execute directly on a logical processor
        - retains a selective control of processor resources, physical memory, interrupt management, and I/O
    - Guest software:
        - each VM is a guest software environment that supports a stack consisting of an OS and application software
        - operates independently of other vms
        - uses the same interface to processor(s), memory, storage, graphics, and I/O provided by a physical platform
        - software stack acts as if it were running on a platform with no VMM
        - reduced privilege
    - Two kinds of VMX operations:
        - VMX root operation: VMM will run in this
        - VMX non-root operation: guest software runs in this
    - Two kinds of VMX transitions:
        - Transitions into non-root are called VMX entries
        - Transitions from non-root to root are called VMX exits
    - Life cycle of VMM Software:
        - software enters VMX operation by executing a `VMXON` instruction (Step 1 above)
        - VMM can enter guests into virtual machines (one at a time)
            - The VMM effects a VM entry using instructions `VMLAUNCH` and `VMRESUME`
            - regains control using VM exits
        - VM exits transfer control to an entry point specified by the VMM
            - VMM takes action based on VM exit and can return to the virtual machine using a VM entry
        - VMM may decide to shut down and leave VMX operation
            - this can be done by executing the `VMXOFF` instruction
    - Control structure:
        - VMX non-root operations and VMX transitions are controlled by a data structure called a virtual machine control structure (VMCS)
        - access to VMCS is managed through a component of processor state called the VMCS pointer
            - one per logical processor
            value of the VMCS pointer is the 64-bit address of the VMCS
    - Enabling and entering VMX operation (Step 1)
        - before system software can enter VMX operation, it enables VMX by setting `CR4.VMXE[bit 13] = 1`
        - VMX operation is entered by executing `VMXON` instruction
        - system software leaves VMX operation by executing `VMXOFF` instruction
## Support
- https://nixhacker.com/developing-hypervisor-from-scratch-part-2/
- https://www.intel.in/content/www/in/en/architecture-and-technology/64-ia-32-architectures-software-developer-system-programming-manual-325384.html