/*
* written by David Eighmey and Markus Kantarci
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include "computer.h"
#undef mips			/* gcc already has a def for mips */

unsigned int endianSwap(unsigned int);

void PrintInfo (int changedReg, int changedMem);
unsigned int Fetch (int);
void Decode (unsigned int, DecodedInstr*, RegVals*);
int Execute (DecodedInstr*, RegVals*);
int Mem(DecodedInstr*, int, int *);
void RegWrite(DecodedInstr*, int, int *);
void UpdatePC(DecodedInstr*, int);
void PrintInstruction (DecodedInstr*);

/*Globally accessible Computer variable*/
Computer mips;
RegVals rVals;

/*
 *  Return an initialized computer with the stack pointer set to the
 *  address of the end of data memory, the remaining registers initialized
 *  to zero, and the instructions read from the given file.
 *  The other arguments govern how the program interacts with the user.
 */
void InitComputer (FILE* filein, int printingRegisters, int printingMemory,
  int debugging, int interactive) {
    int k;
    unsigned int instr;

    /* Initialize registers and memory */

    for (k=0; k<32; k++) {
        mips.registers[k] = 0;
    }
    
    /* stack pointer - Initialize to highest address of data segment */
    mips.registers[29] = 0x00400000 + (MAXNUMINSTRS+MAXNUMDATA)*4;

    for (k=0; k<MAXNUMINSTRS+MAXNUMDATA; k++) {
        mips.memory[k] = 0;
    }

    k = 0;
    while (fread(&instr, 4, 1, filein)) {
	/*swap to big endian, convert to host byte order. Ignore this.*/
        mips.memory[k] = ntohl(endianSwap(instr));
        k++;
        if (k>MAXNUMINSTRS) {
            fprintf (stderr, "Program too big.\n");
            exit (1);
        }
    }

    mips.printingRegisters = printingRegisters;
    mips.printingMemory = printingMemory;
    mips.interactive = interactive;
    mips.debugging = debugging;
}

unsigned int endianSwap(unsigned int i) {
    return (i>>24)|(i>>8&0x0000ff00)|(i<<8&0x00ff0000)|(i<<24);
}

/*
 *  Run the simulation.
 */
void Simulate () {
    char s[40];  /* used for handling interactive input */
    unsigned int instr;
    int changedReg=-1, changedMem=-1, val;
    DecodedInstr d;
    
    /* Initialize the PC to the start of the code section */
    mips.pc = 0x00400000;
    while (1) {
        if (mips.interactive) {
            printf ("> ");
            fgets (s,sizeof(s),stdin);
            if (s[0] == 'q') {
                return;
            }
        }

        /* Fetch instr at mips.pc, returning it in instr */
        instr = Fetch (mips.pc);

        printf ("Executing instruction at %8.8x: %8.8x\n", mips.pc, instr);

        /* 
	 * Decode instr, putting decoded instr in d
	 * Note that we reuse the d struct for each instruction.
	 */
        Decode (instr, &d, &rVals);

        /*Print decoded instruction*/
        PrintInstruction(&d);

        /* 
	 * Perform computation needed to execute d, returning computed value 
	 * in val 
	 */
        val = Execute(&d, &rVals);

	UpdatePC(&d,val);

        /* 
	 * Perform memory load or store. Place the
	 * address of any updated memory in *changedMem, 
	 * otherwise put -1 in *changedMem. 
	 * Return any memory value that is read, otherwise return -1.
         */
        val = Mem(&d, val, &changedMem);

        /* 
	 * Write back to register. If the instruction modified a register--
	 * (including jal, which modifies $ra) --
         * put the index of the modified register in *changedReg,
         * otherwise put -1 in *changedReg.
         */
        RegWrite(&d, val, &changedReg);

        PrintInfo (changedReg, changedMem);
    }
}

/*
 *  Print relevant information about the state of the computer.
 *  changedReg is the index of the register changed by the instruction
 *  being simulated, otherwise -1.
 *  changedMem is the address of the memory location changed by the
 *  simulated instruction, otherwise -1.
 *  Previously initialized flags indicate whether to print all the
 *  registers or just the one that changed, and whether to print
 *  all the nonzero memory or just the memory location that changed.
 */
void PrintInfo ( int changedReg, int changedMem) {
    int k, addr;
    printf ("New pc = %8.8x\n", mips.pc);
    if (!mips.printingRegisters && changedReg == -1) {
        printf ("No register was updated.\n");
    } else if (!mips.printingRegisters) {
        printf ("Updated r%2.2d to %8.8x\n",
        changedReg, mips.registers[changedReg]);
    } else {
        for (k=0; k<32; k++) {
            printf ("r%2.2d: %8.8x  ", k, mips.registers[k]);
            if ((k+1)%4 == 0) {
                printf ("\n");
            }
        }
    }
    if (!mips.printingMemory && changedMem == -1) {
        printf ("No memory location was updated.\n");
    } else if (!mips.printingMemory) {
        printf ("Updated memory at address %8.8x to %8.8x\n",
        changedMem, Fetch (changedMem));
    } else {
        printf ("Nonzero memory\n");
        printf ("ADDR	  CONTENTS\n");
        for (addr = 0x00400000+4*MAXNUMINSTRS;
             addr < 0x00400000+4*(MAXNUMINSTRS+MAXNUMDATA);
             addr = addr+4) {
            if (Fetch (addr) != 0) {
                printf ("%8.8x  %8.8x\n", addr, Fetch (addr));
            }
        }
    }
}

/*
 *  Return the contents of memory at the given address. Simulates
 *  instruction fetch. 
 */
unsigned int Fetch ( int addr) {
    return mips.memory[(addr-0x00400000)/4];
}

/* Decode instr, returning decoded instruction.
 * this, decodes the instructions and stores them
 */
void Decode ( unsigned int instr, DecodedInstr* d, RegVals* rVals) {
    /* Your code goes here */
	int opCode;
	int rs; 
	int rt; 
	int rd;
	int funct;
	
	int immediateAddress;
	int targetAddress;
	int address;
	int shamt;
	
	


	opCode = instr >> 26;

	if (opCode == 0) 						//R-format
	{
		d->type = R;
		
									
		
		rs = (instr << 6)>> 27;
		
		rt = (instr << 11) >> 27;
		
		rd = (instr << 16)>> 27;
		
		
		shamt = (instr << 21)>> 27;
		
		
		funct = (instr << 26)>> 26;
		
		
		d->regs.r.rs = rs;
		d->regs.r.rt = rt;
		d->regs.r.rd = rd;
		d->regs.r.shamt = shamt;
		d->regs.r.funct = funct;
		
		
		rVals->R_rs = mips.registers[rs];
		rVals->R_rt = mips.registers[rt];
		rVals->R_rd = mips.registers[rd];
	}
	else if (opCode == 2) 			//J format, specifically jumps and links
	{
		d->type = J;
	
		address = (instr << 6) >> 6;
		
		d->regs.j.target = address;
		
		
	}
	else if (opCode == 3) 				
	{
		d->type = J;
		
		
		address = (instr << 6)>>6;
		
		d->regs.j.target = address;
	}
	else 					//I format has unique opcodes
	{
		d->type = I;

		
		rs = (instr << 6) >> 27;
		
		
		rt = (instr << 11) >> 27;
		
		
		
		address = instr << 16;
		address = address >> 16;
		
		d->regs.i.rs = rs;
		d->regs.i.rt = rt;
		d->regs.i.addr_or_immed = address;
		
		rVals->R_rs = mips.registers[rs];	
		rVals->R_rt = mips.registers[rt];
		
	}

	d->op = opCode;
		
}

/*
 *  Print the disassembled version of the given instruction
 *  followed by a newline. 
 */
void PrintInstruction ( DecodedInstr* d) {
    /* Your code goes here */
	int gold = 0;
	int purple;
	
	if (d->type == R)
	{
		purple = d->regs.r.funct;
		switch (purple)
		{
			case 33:
				printf("addu\t");
				break;
			case 36:
				printf("and\t");
				break;
			case 8:
				gold = 1;
				printf("jr\t");
				break;
			case 37:
				printf("or\t");
				break;
			case 42:
				printf("slt\t");
				break;
			case 0:
				gold = 1;
				printf("sll\t");
				break;
			case 2:
				gold = 1;
				printf("srl\t");
				break;
			case 35:
				printf("subu\t");
				break;
			default:
										
										
				exit(0);
				break;
		}
		
		if (gold)
		{
			if (purple == 8)						//jr	Rs
			{
										
				printf("$%d", d->regs.r.rs);
			}
			else if (purple == 0 || purple == 2)			//sll/srl  Rs, Rt, I(shamt)
			{
				printf("$%d, $%d , %d", d->regs.r.rs, d->regs.r.rt, d->regs.r.shamt);
			}
		}
		else
		{
			printf("$%d, $%d, $%d",d->regs.r.rd, d->regs.r.rs, d->regs.r.rt);
		}
		
	}
	else if (d->type == J)
	{
		purple = d->op;
		switch (purple)
		{
			case 2:
				printf("j\t");
				printf("0x%08x", d->regs.j.target);
				break;
			case 3:
				printf("jal\t");
				printf("0x%08x", d->regs.j.target);
				break;
			default:
										
				exit(0);
				break;
		}
	}
	else if (d->type == I)
	{
		
		switch (d->op)
		{
			case 9:
				printf("addiu");
				printf("\t$%d, $%d, %d", d->regs.i.rt, d->regs.i.rs, d->regs.i.addr_or_immed);
				
				break;
			case 12:
				printf("andi");
				printf("\t$%d, $%d, 0x%x", d->regs.i.rt, d->regs.i.rs, d->regs.i.addr_or_immed);
				break;
			case 4:
				printf("beq");
				printf("\t$%d, $%d, 0x%08d", d->regs.i.rs, d->regs.i.rt, d->regs.i.addr_or_immed);
				break;
			case 5:
				printf("bne");
				printf("\t$%d, $%d, 0x%08x", d->regs.i.rt, d->regs.i.rs, d->regs.i.addr_or_immed);
				break;
			case 15:
				printf("lui");
				printf("\t$%d, 0x%x", d->regs.i.rt, d->regs.i.addr_or_immed);
				break;
			case 35:
				printf("lw");
				printf("\t$%d, %d($%d)", d->regs.i.rt, d->regs.i.addr_or_immed, d->regs.i.rs);
				break;
			case 13:
				printf("ori");
				printf("\t$%d, $%d, 0x%x", d->regs.i.rt, d->regs.i.rs, d->regs.i.addr_or_immed);
				break;
			case 43:
				printf("sw");
				printf("\t$%d, %d($%d)", d->regs.i.rt, d->regs.i.addr_or_immed, d->regs.i.rs);
				break;
			default:
											
				exit(0);
				break;
		}
	}
	
	printf("\n");
}


											
											
/* Perform computation needed to execute d, returning computed value */
int Execute ( DecodedInstr* d, RegVals* rVals) {
    /* Your code goes here */
    int frat;
    int result = 0; 						
    
    	if (d->type == R)
	{
		frat = d->regs.r.funct;
		switch (frat)
		{
			case 33:					//addu
				result = rVals->R_rs + rVals->R_rt;
				break;
			case 36:					//and
				result = rVals->R_rs & rVals->R_rt;
				break;
			case 8:						//jr
				result = rVals->R_rs;
				break;
			case 37: 					//or
				result = rVals->R_rs | rVals->R_rt;
				break;
			case 42: 					//slt
				if (rVals->R_rs < rVals->R_rt)
					result = 1;
				else
					result = 0;
				break;
			case 0:						//sll
				result = rVals->R_rt << d->regs.r.shamt;
				break;
			case 2:						//srl
				result = rVals->R_rt >> d->regs.r.shamt;
				break;
			case 35:					//subu
				result = rVals->R_rs - rVals->R_rt;
				break;
		}
		
	}
	else if (d->type == J)
	{
		frat = d->op;
		switch (frat)
		{
			case 2:						//j
				result = 1;
				break;
			case 3:						//jal
				result = mips.pc+4;
				break;
		}
	}
	else if (d->type == I)
	{
	
		switch (d->op)
		{
			case 9: 					//addiu
			
				result = rVals->R_rs + d->regs.i.addr_or_immed;
									
				break;
			case 12: 					//andi
				result = rVals->R_rs & d->regs.i.addr_or_immed;
				break;
			case 4: 					//beq
				if(rVals->R_rs == rVals->R_rt)
					result = 1;
				break;
			case 5: 					//bne
				if(rVals->R_rs != rVals->R_rt)
					result = 1;
				break;
			case 15: 					//lui
				result = d->regs.i.addr_or_immed << 16;
				break;
			case 35: 					//lw
				result = rVals->R_rs + d->regs.i.addr_or_immed;
				break;
			case 13: 					//ori
				result = rVals->R_rs | d->regs.i.addr_or_immed;
				break;
			case 43: 					//sw
				result = rVals->R_rs + d->regs.i.addr_or_immed;
				break;
			default:
				break;
		}
	}	
  return result;
}

/* 
 * Update the program counter based on the current instruction. For
 * instructions other than branches and jumps, for example, the PC
 * increments by 4 (which we have provided).
 */
void UpdatePC ( DecodedInstr* d, int val) {
	
	int boots;
	
	if (d->type == R)
	{
		boots = d->regs.r.funct;
		if(boots == 8) 						//jr
			mips.pc = rVals.R_rs;
		else
			mips.pc+=4;
	}
	else if(d->type == J)
	{
		boots = d->op;
		if(val == 1 && boots == 2) 				//j
			mips.pc = 0000 | d->regs.j.target << 2;
		else if(boots == 3) 					//jal
		{
			mips.registers[31] = mips.pc + 4;
			mips.pc = 0000 | d->regs.j.target << 2; 
		}
		
	}
	else if(d->type == I)
	{
		if(val == 1 && d->op == 4)
			mips.pc = mips.pc + 4 + (d->regs.i.addr_or_immed << 2);
		else if(val == 1 && d->op == 5)
			mips.pc = mips.pc + 4 + (d->regs.i.addr_or_immed << 2);
		else
   			mips.pc+=4;
	}
}

/*
 * Perform memory load or store. Place the address of any updated memory 
 * in *changedMem, otherwise put -1 in *changedMem. Return any memory value 
 * that is read, otherwise return -1. 
 *
 * Remember that we're mapping MIPS addresses to indices in the mips.memory 
 * array. mips.memory[0] corresponds with address 0x00400000, mips.memory[1] 
 * with address 0x00400004, and so forth.
 *
 */
int Mem( DecodedInstr* d, int val, int *changedMem) {
    /* Your code goes here */
	int memoryRead = 0;
	int memToChange = -1;

	if (d->type == R)
	{
		switch (d->regs.r.funct)
		{
			case 8:					//jr, do nothing, just updates pc
				break;
			case 33: 				//addu
			case 36:				//and
			case 37: 				//or
			case 42: 				//slt
			case 0:					//sll
			case 2:					//srl
			case 35:				//subu
			default: 				//just pass val on to next func (regwrite)
				memoryRead = val;
				break;
		}
	}
	else if (d->type == J)
	{
		switch (d->op)
		{
			case 2:					//j will not do anything right here
				break;
			case 3:					//jal, modifies the last register
				memoryRead = val; 		//this is the pc+4 that will go into r31
				break;
		}
	}
	else if (d->type == I)					//I format
	{
		switch (d->op)
		{
			case 35: 				//lw
				memoryRead = mips.memory[(val - 0x00400000)];
				break;
			case 43: 				//sw
				mips.memory[(val - 0x00400000)] = rVals.R_rt;
				memToChange = val;
				break;
				
			case 4: 				//beq will just update the pc and thats it 
				break;
			case 5: 				
				break;
				
			case 9: 				//addiu
			case 12: 				//andi
			case 15: 				//lui
			case 13: 				//ori
			default: 				//memoryRead is in val
				memoryRead = val;
				break;
		}
	}	
	
	*changedMem = memToChange;
  return memoryRead;
}

/* 
 * Write back to register. If the instruction modified a register--
 * (including jal, which modifies $ra) --
 * put the index of the modified register in *changedReg,
 * otherwise put -1 in *changedReg.
 */
void RegWrite( DecodedInstr* d, int val, int *changedReg) {
    /* Your code goes here */
    	int regToChange = -1;
    	
	if (d->type == R)
	{
		switch (d->regs.r.funct)
		{
			case 8:					//jr, no reg write
				break;
			case 33: 				//addu
			case 36:				//and
			case 37: 				//or
			case 42: 				//slt
			case 0:					//sll
			case 2:					//srl
			case 35:				//subu
			default: 				//write to rd
				regToChange = d->regs.r.rd;
				mips.registers[regToChange] = val;
				break;
		}
	}
	else if (d->type == J)
	{
		switch (d->op)
		{
			case 2:					//j, do nothing
				break;
			case 3:					//jal, modify r31 to = val(which is pc + 4)
				regToChange = 31;
				mips.registers[regToChange] = val;
				break;
		}
	}
	else if (d->type == I)
	{
		switch (d->op)
		{
				
			case 43: 				//sw

				break;
			case 4: 				//beq, no writes
				break;
			case 5: 				//bne
				break;
			case 35: 				//lw, write rt into the right register
			case 9: 				//addiu
			case 12: 				//andi
			case 15: 				//lui
			case 13: 				//ori
			default: 				//write to rd
				regToChange = d->regs.r.rt;
				mips.registers[regToChange] = val;
				break;
		}
	}		   

	*changedReg = regToChange;
}
