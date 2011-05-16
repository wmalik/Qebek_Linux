/*
 * 
 *
 * Copyright (C) 2010 Paulo Ricardo Motta Gomes
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 */

#include "qemu-common.h"
#include "qebek-common.h"
#include "qebek-bp.h"

target_ulong LinuxRead;
target_ulong LinuxWrite;

void preLinuxRead(CPUX86State *env, void* user_data)
{
	uint32_t FileDescriptor, ReadBuffer, ReadSize;
	target_ulong ret_addr;
	PLinuxReadWriteData pReadData;

	// get file handle, buffer & buffer size from stack
    qebek_read_ulong(env, env->regs[R_ESP] + 4, &FileDescriptor); //WASIF:Q what does this do?
    qebek_read_ulong(env, env->regs[R_ESP] + 8, &ReadBuffer);
    qebek_read_ulong(env, env->regs[R_ESP] + 12, &ReadSize);

	//fprintf(stderr, "preLinuxRead: FileDescriptor %08x, Buffer %08x, Size %08x\n", FileDescriptor, ReadBuffer, ReadSize);

	if(FileDescriptor == 0x00){
		pReadData = (PLinuxReadWriteData)qemu_malloc(sizeof(LinuxReadWriteData));
		if(pReadData != NULL)
		{
			pReadData->FileDescriptor = FileDescriptor;
			pReadData->BufferAddr = ReadBuffer;
			pReadData->BufferSize = ReadSize;
		}

		// set return address, so the VM will break when returned
		qebek_read_ulong(env, env->regs[R_ESP], &ret_addr);
		if(!qebek_bp_add(ret_addr, env->cr[3], env->regs[R_EBP], postLinuxRead, pReadData))
		{
			fprintf(stderr, "preNtReadFile: failed to add postcall interception.\n");
		}
	}
}

void postLinuxRead(CPUX86State *env, void* user_data)
{
	//fprintf(stderr, "postLinuxRead: ENTERED HERE.\n");
	PLinuxReadWriteData data = (PLinuxReadWriteData)user_data;

	//fprintf(stderr, "postLinuxRead: FileDescriptor %08x, Buffer %08x, Size %08x\n", data->FileDescriptor, data->BufferAddr, data->BufferSize);
	ReadBufferAndPrint(env, data->BufferAddr, data->BufferSize, "stdinp-");

	// remove return address
	target_ulong bp_addr = env->eip;
	if(!qebek_bp_remove(bp_addr, env->cr[3], env->regs[R_EBP]))
	{
		fprintf(stderr, "postNtReadFile: failed to remove postcall interception.\n");
	}

	qemu_free(data);
}

void preLinuxWrite(CPUX86State *env, void* user_data)
{
	uint32_t FileDescriptor, BufferAddr, BufferSize;

	// get file handle, buffer & buffer size from stack
    qebek_read_ulong(env, env->regs[R_ESP] + 4, &FileDescriptor); //previous EBX
    qebek_read_ulong(env, env->regs[R_ESP] + 8, &BufferAddr); //previous ECX
    qebek_read_ulong(env, env->regs[R_ESP] + 12, &BufferSize); //previous EDX

    //fprintf(stderr, "Read values from stack: fd=%d buffer=%x size=%d\n", FileDescriptor, BufferAddr, BufferSize);

	if(BufferSize > 0){
		if(FileDescriptor == 0x01){
			ReadBufferAndPrint(env, BufferAddr, BufferSize, "stdout-");
		} else if(FileDescriptor == 0x02){
			ReadBufferAndPrint(env, BufferAddr, BufferSize, "stderr-");
		}
	} //end buffsize > 0
}

void ReadBufferAndPrint(CPUX86State *env, uint32_t BufferAddr, uint32_t BufferSize, char* prefix){
	uint8_t *buffer = qemu_malloc(BufferSize+1);
	if(buffer == NULL ){
		fprintf(stderr, "MWP: failed to alloc buffer in do_interrupt \n");
	}else  {
		if(!qebek_read_raw(env, BufferAddr, buffer, BufferSize))
		{
			fprintf(stderr, "MWP: failed to read buffer:\n ");
		}
		else
		{
			buffer[BufferSize] = '\0';
			fprintf(stderr, "%d\n", 7+BufferSize);
			fprintf(stderr, "%s%s", prefix, (char*)buffer);
			qemu_free(buffer);
		}
	} //end ifbuffer == null
}


