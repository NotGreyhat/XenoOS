#ifndef __XOS_EXCEPTIONS_H__
#define __XOS_EXCEPTIONS_H__

#include <interrupts/IDT.h>
#include <drivers/video/Framebuffer.h>

void write_red();
void panic();

void div0_handler(int_frame_t* frame);
void debug_excp_handler(int_frame_t* frame);
void breakpoint_handler(int_frame_t* frame);
void overflow_handler(int_frame_t* frame);
void bre_handler(int_frame_t* frame);                    // Bound range exceeded.
void invld_opcode_handler(int_frame_t* frame);
void device_not_avail_handler(int_frame_t* frame);
void double_fault_handler(int_frame_t* frame);
void cso_handler(int_frame_t* frame);                    // Copressesor overrun.
void invalid_tss_handler(int_frame_t* frame);
void snp_handler(int_frame_t* frame);                    // Segment not present.
void ssf_handler(int_frame_t* frame);                    // Stack segment fault.
void gpf_handler(int_frame_t* frame);
void page_fault_handler(int_frame_t* frame);
void fpe_handler(int_frame_t* frame);

#endif 
