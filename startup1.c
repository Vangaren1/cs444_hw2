/* C startup file, called from startup0.s-- */
void startupc(void);
void clr_bss(void);
void init_devio(void);
void k_init(void);

void startupc()
{
  clr_bss();                    /* clear BSS area (uninitialized data) */
  init_devio();                 /* latch onto Tutor-supplied info, code */
  k_init();				        /* execute kernel initialization routine */
}
