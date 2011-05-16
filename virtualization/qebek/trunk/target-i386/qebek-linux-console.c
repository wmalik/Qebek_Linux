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
	//fprintf(stderr, "preLinuxRead: ENTERED HERE.\n");
}

void preLinuxWrite(CPUX86State *env, void* user_data)
{
	uint32_t FileDescriptor, BufferAddr, BufferSize;
	uint8_t *buffer;

	// get file handle, buffer & buffer size from stack
    qebek_read_ulong(env, env->regs[R_ESP] + 4, &FileDescriptor); //previous EBX
    qebek_read_ulong(env, env->regs[R_ESP] + 8, &BufferAddr); //previous ECX
    qebek_read_ulong(env, env->regs[R_ESP] + 12, &BufferSize); //previous EDX

    //fprintf(stderr, "Read values from stack: fd=%d buffer=%x size=%d\n", FileDescriptor, BufferAddr, BufferSize);

	if(BufferSize > 0){

		if(FileDescriptor == 0x01 || FileDescriptor == 0x02){ //STDIN OR STDERR

			buffer = qemu_malloc(BufferSize+1);
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
					fprintf(stderr, "%s", (char*)buffer);
					qemu_free(buffer);
				}
			} //end ifbuffer == null

		} //end if stdout or stderr

	} //end buffsize > 0
}
