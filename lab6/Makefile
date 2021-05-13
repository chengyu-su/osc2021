all: start.o main.o uart.o allocater.o allocator.o exception_c.o exception_s.o sched_c.o sched_s.o sys_c.o sys_s.o fork.o tmpfs.o vfs.o cpio.o printf.o error.o tools.o kernel8.img 

start.o: start.S
	aarch64-linux-gnu-gcc -c -g -nostdinc -nostdlib -nostartfiles start.S -o start.o

main.o: main.c
	aarch64-linux-gnu-gcc -c -g -nostdinc -nostdlib -nostartfiles main.c -o main.o

uart.o: uart.c
	aarch64-linux-gnu-gcc -c -g -nostdinc -nostdlib -nostartfiles uart.c -o uart.o

allocater.o: allocater.c
	aarch64-linux-gnu-gcc -c -g -nostdinc -nostdlib -nostartfiles allocater.c -o allocater.o

allocator.o: allocator.c
	aarch64-linux-gnu-gcc -c -g -nostdinc -nostdlib -nostartfiles allocator.c -o allocator.o

exception_s.o: exception.S
	aarch64-linux-gnu-gcc -c -g -nostdinc -nostdlib -nostartfiles exception.S -o exception_s.o

exception_c.o: exception.c
	aarch64-linux-gnu-gcc -c -g -nostdinc -nostdlib -nostartfiles exception.c -o exception_c.o

sched_s.o: sched.S
	aarch64-linux-gnu-gcc -c -g -nostdinc -nostdlib -nostartfiles sched.S -o sched_s.o

sched_c.o: sched.c
	aarch64-linux-gnu-gcc -c -g -nostdinc -nostdlib -nostartfiles sched.c -o sched_c.o

fork.o: fork.c
	aarch64-linux-gnu-gcc -c -g -nostdinc -nostdlib -nostartfiles fork.c -o fork.o

sys_s.o: sys.S
	aarch64-linux-gnu-gcc -c -g -nostdinc -nostdlib -nostartfiles sys.S -o sys_s.o

sys_c.o: sys.c
	aarch64-linux-gnu-gcc -c -g -nostdinc -nostdlib -nostartfiles sys.c -o sys_c.o

tmpfs.o: tmpfs.c
	aarch64-linux-gnu-gcc -c -g -nostdinc -nostdlib -nostartfiles tmpfs.c -o tmpfs.o

vfs.o: vfs.c
	aarch64-linux-gnu-gcc -c -g -nostdinc -nostdlib -nostartfiles vfs.c -o vfs.o

cpio.o: cpio.c
	aarch64-linux-gnu-gcc -c -g -nostdinc -nostdlib -nostartfiles cpio.c -o cpio.o

printf.o: printf.c
	aarch64-linux-gnu-gcc -c -g -nostdinc -nostdlib -nostartfiles printf.c -o printf.o

error.o: error.c
	aarch64-linux-gnu-gcc -c -g -nostdinc -nostdlib -nostartfiles error.c -o error.o

tools.o: tools.c
	aarch64-linux-gnu-gcc -c -g -nostdinc -nostdlib -nostartfiles tools.c -o tools.o


kernel8.img: start.o main.o uart.o allocater.o allocator.o exception_s.o exception_c.o sched_c.o sched_s.o fork.o sys_c.o sys_s.o tmpfs.o vfs.o cpio.o printf.o error.o tools.o
	aarch64-linux-gnu-ld -T linker.ld -o kernel8.elf start.o main.o uart.o allocater.o allocator.o exception_c.o exception_s.o sched_c.o sched_s.o fork.o sys_c.o sys_s.o tmpfs.o vfs.o cpio.o printf.o error.o tools.o
	aarch64-linux-gnu-objcopy -O binary kernel8.elf kernel8.img
	aarch64-linux-gnu-objdump -D kernel8.elf > kernel.objdump

clean:
	rm -rf kernel8.elf
	rm -rf *.o

run:
	qemu-system-aarch64 -M raspi3 -kernel kernel8.img -display none -serial null -serial stdio -initrd initramfs.cpio 

runpty:
	qemu-system-aarch64 -M raspi3 -kernel kernel8.img -display none -serial null -serial pty -initrd initramfs.cpio 

runasm:
	qemu-system-aarch64 -M raspi3 -kernel kernel8.img -display none -d in_asm -serial null -serial stdio -initrd initramfs.cpio

rundis:
	qemu-system-aarch64 -M raspi3 -kernel kernel8.img -serial null -serial stdio -initrd initramfs.cpio

debug:
	qemu-system-aarch64 -M raspi3 -kernel kernel8.img -display none -serial null -serial stdio -S -s -initrd initramfs.cpio 

gdb:
	gdb-multiarch -x ./debug.gdb