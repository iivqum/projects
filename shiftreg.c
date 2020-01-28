#include <stdio.h>

enum reg_enum{
	/* signals */
	SIG_HI, SIG_LO,
	/* outputs 0-7*/
	OUT0, OUT1, OUT2, OUT3, OUT4, OUT5, OUT6, OUT7,
	/* serial output */
	OUTS
};

typedef enum reg_enum reg_enum;
typedef unsigned char reg_byte;

typedef struct {
	/* storage register */
	reg_byte s;
	/* output register */
	reg_byte o;
} shiftreg;

/* read data signal, shift storage right */
void reg_clock(shiftreg *reg, reg_enum sig)
{	
	switch(sig){
		case SIG_HI: reg->s>>1; reg->s&128; break;
		case SIG_LO: reg->s>>1; break;
	}
}

/* clear storage register */
void reg_reset(shiftreg *reg){reg->s &= 0;}

/* copy storage register into output register */
void reg_latch(shiftreg *reg){reg->o &= reg->s;}

reg_byte reg_read(shiftreg *reg, reg_enum sig)
{
	reg_byte out;
	switch(sig){
		case OUT0: out |= reg->s&1; break;
		case OUT1: out |= reg->s&2; break;
		case OUT2: out |= reg->s&4; break;
		case OUT3: out |= reg->s&8; break;
		case OUT4: out |= reg->s&16; break;
		case OUT5: out |= reg->s&32; break;
		case OUT6: out |= reg->s&64; break;
		
		/* OUT7 and OUTS provide same output */
		case OUT7: out |= reg->s&128; break;
		case OUTS: out |= reg->s&128; break;
	}
	return out?SIG_HI:SIG_LO;
}

int main()
{
	shiftreg s0;
	
	reg_reset(&s0);
	reg_clock(&s0, SIG_HI);
	
	printf("%d\n", reg_read(&s0, OUT0) == SIG_HI);
	
	return 0;
}
