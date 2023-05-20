#ifndef __NIXIE_H__
#define __NIXIE_H__

void Nixie_Scan(unsigned char location, unsigned char num);

void Nixie_Loop(void);

void Nixie_SetBuf(unsigned char location, unsigned char num);

#endif