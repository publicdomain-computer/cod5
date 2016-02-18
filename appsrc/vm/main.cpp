#include <iostream>

struct cpu {
	uint32_t r[16];
	uint32_t flags;
	uint16_t *mem;
	bool brk;
};

uint16_t mmu_get16(cpu *c, uint32_t addr)
{
	return c->mem[addr >> 1];
}

uint32_t mmu_get32(cpu *c, uint32_t addr)
{
	return c->mem[addr >> 1] | ((uint32_t)c->mem[addr >> 1 + 1] << 16);
}

void mmu_set32(cpu *c, uint32_t addr, uint32_t value)
{
	c->mem[addr >> 1] = value & 0xFFFF;
	c->mem[addr >> 1 + 1] = (value >> 16) & 0xFFFF;
}

void step(cpu *c)
{
	uint32_t instr;
	uint32_t rd;
	uint32_t rn;
	uint32_t rm;
	uint32_t ip;
	uint32_t imm6;
	uint32_t imm8;
	uint32_t imm12;
	uint32_t flags;
	uint32_t d;
	uint32_t n;
	uint32_t m;

	flags = c->flags;
	ip = c->r[15];
	instr = mmu_get16(c, ip);
	d = (instr >> 8) & 0x0F;
	n = (instr >> 4) & 0x0F;
	m = instr & 0x0F;
	rd = c->r[d];
	rn = c->r[n];
	rm = c->r[m];
	imm6 = (instr >> 4) & 0x3F;
	imm8 = (instr >> 4) & 0xFF;
	imm12 = instr & 0x0FFF;

	switch ((instr >> 12) & 0x0F) {
	case 0x0:
		// add <Rd>, <Rn>, <Rm>
		rd = rn + rm;
		break;
	case 0x1:
		// and <Rd>, <Rn>, <Rm>
		rd = rn & rm;
		break;
	case 0x2:
		// or <Rd>, <Rn>, <Rm>
		rd = rn | rm;
		break;
	case 0x3:
		// xor <Rd>, <Rn>, <Rm>
		rd = rn ^ rm;
		break;
	case 0x4:	
		// sub <Rd>, <Rn>, <Rm>
		rd = rn - rm;
		break;
	case 0x5:
		// sw <Rd>, <Rn>, +<Rm>
		mmu_set32(c, rn + rm, rd);
		break;
	case 0x6:
		// lw <Rd>, <Rn>, +<Rm>	
		rd = mmu_get32(c, rn + rm);
		break;
	case 0x7:
		// addi <Rd>, #immediate8 ;
		rd = rd + imm8;
	case 0x8:
		switch ((n >> 2) & 0x3) {
		case 0:
			// sll <Rd>, #immediate6 ;logical shift left
			rd = rd << imm6;
			break;
		case 1:
			break;
		case 2:
			// srl <Rd>, #immediate6 ; logical shift right
			rd = rd >> imm6;
			break;
		case 3:
			// sra <Rd>, #immediate6 ; arithmetic shift right
			if (rd & 0x80000000) {
				rd = rd >> imm6;
				rd = rd | (0xFFFFFFFF << (32 - imm6));
			} else {
				rd = rd >> imm6;
			}
			break;	
		}
		break;	
	case 0x9:
		// jmp <target_address> ;
		if (imm12 & 0x0800) {
			ip = ip + ((imm12 | 0xFFFFF000));
		} else {
			ip = ip + (imm12);
		}
		break;
	case 0xA:
		// li.0 r0, #immediate12
	case 0xB:
		// li.12 r0, #immediate12
		break;
	case 0xC:
		// li.24 r0, #immediate12
		break;
	case 0xD:
	case 0xE:
	case 0xF:
		switch (m) {
		case 0x0:
			// cmp <Rd>, <Rn> ; compare (Rd - Rn -> flags);
			
			break;
		case 0x1:
			// tst <Rd>, <Rn> ; test (Rd & Rn -> flags);
			break;
		case 0x2:
			// inv <Rd>, <Rn> ;
			rd = ~rn;
			break;
		case 0x3:
			// mul <Rd>, <Rn>
			rd = rd * rn;
			break;

		case 0xF:
			switch (n) {
			case 0x0:
				break;
			case 0x1:
				break;
			case 0x2:
				break;
			case 0xD:
			case 0xE:
				switch (d) {
				case 0:
					//S.CC ; skip if Carry clear (C==0)
					//S.LO ; skip if unsigned lower
				case 1:
					//S.CS ; skip if Carry set (C==1)
					//S.HS ; skip if unsigned higher or same

				case 2:
					//S.EQ ; skip next instruction if Equal (Z==1)
				case 3:
					//S.GE ; skip if signed greater than or equal (N==V)

				case 4:
					//S.GT ; skip if signed greater than (Z==0 and N==V)

				case 5:
					//S.HI ; skip if unsigned higher (C==1 and Z==0)

				case 6:
					//S.LE ; skip if signed less than or equal (Z==1 or N!=V)

				case 7:
					//S.LS ; skip if unsigned lower or same (C==0 or Z==1)

				case 8:
					//S.LT ; skip if signed less than (N!=V)

				case 9:
					//S.MI ; skip if negative (N==1)

				case 0xA:
					//S.NE ; skip if Not equal (Z==0)

				case 0xB:
					//S.PL ; skip if positive or zero (N==0)

				case 0xC:
					//S.VC ; skip if No overflow (V==0)

				case 0xD:
					//S.VS ; skip if Overflow (V==1)
					break;
				}
				break;
			case 0xF:
				switch (d) {
				case 0:
					// ret
					break;
				case 1:
					// reti
					break;
				case 2:
					// brk
					break;
				case 3:
					// sys
					break;
				case 0xF:
					// nop
					break;
				}
				break;
			}
			break;
		}
		break;
		
	}
	c->flags = flags;
	c->r[15] = ip + 2;
	c->r[d] = rd;
}

void run(cpu *c)
{
	while (!c->brk) {
		step(c);
	}
}

int main(int argc, char *argv[])
{
	cpu c = {0};
	run(&c);
	return 0;
}
