#include <lcom/lcf.h>

#include <lcom/lab3.h>

#include <stdbool.h>
#include <stdint.h>

uint8_t status; //vai ser para guardar o que vou ler do status register
//no interrupt handler

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  lcf_trace_calls("/home/lcom/labs/lab3/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab3/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}


//interrupt handler. every time a byte from the keyboard is received
//kbd_test_scan() should try to assemble a scancode
void kbc_ih(){
  util_sys_inb(0x64,&status); //isto lê da porta 0x64 e guarda em status


  
}
//se nao houver erros no kbc
//chamo a funçao kbd_print_scancode que vem definida na biblioteca

//esta função não lê o teclado diretamente
//espera que a kbc_ih lhe entregue os bytes
int(kbd_test_scan)() {
  sys_irqsetpolicy(IRQ1, IRQ_REENABLE | IRQ_EXCLUSIVE, &hook_id);
  sys_irqrmpolicy(&hook_id);
  return 0;
}

//tenho de avisar p sistema que quero receber as interrupções do IRQ1 de forma
//exclusiva, para que o driver padrão do MINIX não "roube" os bytes antes de mim


int(kbd_test_poll)() {
  /* To be completed by the students */
  printf("%s is not yet implemented!\n", __func__);

  return 1;
}

int(kbd_test_timed_scan)(uint8_t n) {
  /* To be completed by the students */
  printf("%s is not yet implemented!\n", __func__);

  return 1;
}