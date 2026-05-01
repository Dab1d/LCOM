// IMPORTANT: you must include the following line in all your C files
#include <lcom/lcf.h>


#include <lcom/lab5.h>



#include <stdint.h>
#include <stdio.h>
//#include <machine/x86.h> este header já está no lcf


// Any header files included below this line should have been created by you
#include "kbc.h"
#include "video_gr.h"
#undef video_test_rectangle
#undef video_test_init




int main(int argc, char *argv[]) {
   // sets the language of LCF messages (can be either EN-US or PT-PT)
   lcf_set_language("EN-US");


   // enables to log function invocations that are being "wrapped" by LCF
   // [comment this out if you don't want/need it]
   lcf_trace_calls("/home/lcom/labs/lab5/trace.txt");


   // enables to save the output of printf function calls on a file
   // [comment this out if you don't want/need it]
   lcf_log_output("/home/lcom/labs/lab5/output.txt");


   // handles control over to LCF
   // [LCF handles command line arguments and invokes the right function]
   if (lcf_start(argc, argv))
       return 1;


   // LCF clean up tasks
   // [must be the last statement before return]
   lcf_cleanup();


   return 0;
}


int(video_test_init)(uint16_t mode, uint8_t delay) {
   //copied the code from the lab item 25 from here...
   reg86_t reg;
   //memset is used to fill a contiguous block of memory
   //with a specific value; so here we are zeroing out
   memset(&reg, 0, sizeof(reg));
   reg.intno =0x10;
   reg.ah = 0x4F;
   reg.al = 0x02;
   reg.bx = mode | BIT(14); 
   //i tried to include machine/int86.h but it gave error
   //for VBE functions, AX must return 0x004F


   if (sys_int86(&reg) != OK) {
       printf("sys_int86() AKA interrupt failed \n");
       return 1;
   }


   if (reg.ax != 0x004F) {
       printf("VBE function failed\n");
       return 1;
   }  
   //..until here


   sleep(delay); //wait delay seconds


   //return to minixs default text mode
   //vg_exit was already provided by the LCF
   if (vg_exit()!=OK){
       printf("vg_exit() in video_test_init() failed\n");
       return 1;
   }
   return 0;
}





int video_test_rectangle(uint16_t mode, uint16_t x, uint16_t y,
                         uint16_t width, uint16_t height,
                         uint32_t color) {

    if (vg_init(mode) == NULL)
        return 1;

    if (vg_draw_rectangle(x, y, width, height, color) != 0)
        return 1;

    int ipc_status;
    message msg;

    uint8_t irq_set;

    if (kbc_subscribe_int(&irq_set) != 0)
        return 1;

    while (get_current_scancode() != 0x81) {

        if (driver_receive(ANY, &msg, &ipc_status) != 0)
            continue;

        if (is_ipc_notify(ipc_status)) {
            if (msg.m_notify.interrupts & BIT(irq_set)) {
                kbc_ih();
            }
        }
    }

    if (kbc_unsubscribe_int() != 0)
        return 1;

    if (vg_exit() != 0)
        return 1;

    return 0;
}





int(video_test_xpm)(xpm_map_t xpm, uint16_t x, uint16_t y) {
   /* To be completed */
   printf("%s(%8p, %u, %u): under construction\n", __func__, xpm, x, y);


   return 1;
}


