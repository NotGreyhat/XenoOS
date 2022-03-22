#include <stdint.h>
#include <stddef.h>
#include <util/stivale2.h>
#include <util/string.h>

static uint8_t stack[4000];


void* get_tag(struct stivale2_struct* stivale2_struct, uint64_t id) {
    struct stivale2_tag* curTag = (void*)stivale2_struct->tags;

    while (1) {
        if (!(curTag)) {
            // End.
            return NULL;
        }

        if (curTag->identifier == id) {
            return curTag;
        }

        curTag = (void*)curTag->next;
    }
}


static struct stivale2_header_tag_terminal terminal_hdr_tag = {
    .tag = {
        .identifier = STIVALE2_HEADER_TAG_TERMINAL_ID,
        .next = 0
    },

    .flags = 0
};


static struct stivale2_header_tag_framebuffer framebuffer_hdr_tag = {
    .tag = {
        .identifier = STIVALE2_HEADER_TAG_FRAMEBUFFER_ID,
        .next = (uint64_t)&terminal_hdr_tag
    },

    .framebuffer_width = 0,
    .framebuffer_height = 0,
    .framebuffer_bpp = 0
};




__attribute__((section(".stivale2hdr"), used)) static struct stivale2_header stivale_hdr = {
    .entry_point = 0,
    .stack = (uintptr_t)stack,
     .flags = (1 << 1) | (1 << 2) | (1 << 3) | (1 << 4),
     .tags = (uintptr_t)&framebuffer_hdr_tag
};


void(*kwrite_master)(const char* str, size_t length);


void kwrite(const char* str) {
    kwrite_master(str, strlen(str));
}



void _start(struct stivale2_struct* ss) {
    struct stivale2_struct_tag_terminal* term_tag = get_tag(ss, STIVALE2_STRUCT_TAG_TERMINAL_ID);

    if (!(term_tag)) {
        __asm__ __volatile__("cli; hlt");
    }

    void* termwrite_master = (void*)term_tag->term_write;
    kwrite_master = termwrite_master;

    while (1) {
        __asm__ __volatile__("hlt");
    }
}
