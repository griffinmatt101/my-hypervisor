# INTRODUCTION TO VIRTUAL MACHINE EXTENSIONS

## Virtual Machine Architecture
- Virtual-machine Monitors (VMM):
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
## Introduction to VMX Operation
- Two kinds of VMX operations:
    - VMX root operation: VMM will run in this
    - VMX non-root operation: guest software runs in this
- Two kinds of VMX transitions:
    - transitions into non-root are called VMX entries
    - transitions from non-root to root are called VMX exits
## Life cycle of VMM Software
- software enters VMX operation by executing a `VMXON` instruction (Step 1 above)
- VMM can enter guests into virtual machines (one at a time)
    - The VMM effects a VM entry using instructions `VMLAUNCH` and `VMRESUME`
    - regains control using VM exits
- VM exits transfer control to an entry point specified by the VMM
    - VMM takes action based on VM exit and can return to the virtual machine using a VM entry
- VMM may decide to shut down and leave VMX operation
    - this can be done by executing the `VMXOFF` instruction
## Virtual-Machine Control structure
- VMX non-root operations and VMX transitions are controlled by a data structure called a virtual machine control structure (VMCS)
- access to VMCS is managed through a component of processor state called the VMCS pointer
    - one per logical processor
    - value of the VMCS pointer is the 64-bit address of the VMCS
## Enabling and entering VMX operation (Step 1)
- before system software can enter VMX operation, it enables VMX by setting `CR4.VMXE[bit 13] = 1`
- VMX operation is entered by executing `VMXON` instruction
- system software leaves VMX operation by executing `VMXOFF` instruction
- VMXON is also controlled by the IA32_FEATURE_CONTROL MSR (MSR address 3AH)
- This MSR is cleared to 0 when a logical processor is reset
- Relevant MSR bits:
    - Bit 0 is the lock bit
        - if cleared, VMXON causes a `general-protection` exception.
        - if set, WRMSR to this MSR causes `general-protection` exception
            - MSR cannot be modified until a power-up reset condition
        - system BIOS can use this bit to provide a setup option for BIOS to disable support for VMX
        - to enable VMX support in a platform, BIOS must set bit 1, bit 2, or both, as well as the lock bit
    - Bit 1 enables VMXON in SMX operation
        - if cleared, execution of VMXON in Safe Mode Extensions (SMX) operation causes a `general-protection` exception
        - attempts to set this bit on logical processors that do not support both VMX operation and SMX operation will cause a `general-protection` exception
    - Bit 2 enables VMXON outside of SMX operation
        - if cleared, execution of VMX outside of SMX operation causes a `general-protection` exception
        - attempts to set this bit on logical processors that do not support VMX operation will cause a `general-protection` exception