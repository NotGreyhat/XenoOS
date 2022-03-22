bits 64
extern kwrite
extern write_red
extern hex2str
extern dec2str

global div0_handler
global debug_excp_handler
global breakpoint_handler
global overflow_handler
global bre_handler          ; Bound range exceeded
global invld_opcode_handler
global device_not_avail_handler
global double_fault_handler
global cso_handler                  ; Copressesor overrun.
global invalid_tss_handler
global snp_handler                  ; Segment not present.
global ssf_handler
global gpf_handler
global gpf_handler
global page_fault_handler
global fpe_handler 

%macro write_reg 0
    pop rdi
    call hex2str
    mov rdi, rax
    call kwrite
    mov rdi, newline
    call kwrite
%endmacro

%macro panic 1
    call write_red

    mov rdi, panic_msg1
    call kwrite

    mov rdi, %1
    call hex2str
    
    mov rdi, rax
    call kwrite

    mov rdi, newline
    call kwrite

    mov rdi, panic_msg2
    call kwrite

    ; Write RIP.
    mov rdi, __rip
    call kwrite
    write_reg

    ; Write CS.
    mov rdi, __cs
    call kwrite
    write_reg

    ; Write RFLAGS.
    mov rdi, __rflags
    call kwrite
    write_reg

    ; Write
    mov rdi, __rsp
    call kwrite
    write_reg

    ; Write SS.
    mov rdi, __ss
    call kwrite
    write_reg

    cli
    hlt
%endmacro

div0_handler:
    panic 0x0

debug_excp_handler:
    panic 0x1

breakpoint_handler:
    panic 0x3

overflow_handler:
    panic 0x4

bre_handler:
    panic 0x5

invld_opcode_handler:
    panic 0x6

device_not_avail_handler:
    panic 0x7

double_fault_handler:
    panic 0x7

cso_handler:
    panic 0x9

invalid_tss_handler:
    panic 0xA

snp_handler:
    panic 0xB

ssf_handler:
    panic 0xC

gpf_handler:
    panic 0xD

page_fault_handler:
    panic 0xE

fpe_handler:
    panic 0xF


__rip: db "RIP: ", 0
__cs: db "CS: ", 0
__rflags: db "RFLAGS: ", 0
__rsp: db "RSP: ", 0
__ss: db "SS: ", 0
panic_msg1: db "FATAL CPU EXCEPTION: ", 0
panic_msg2: db "** KERNEL PANIC **", 0xD, 0xA, 0
newline: db 0xD, 0xA, 0
