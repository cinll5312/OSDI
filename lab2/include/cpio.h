#ifndef CPIO_H
#define CPIO_H

#define INITRAMFS  ((volatile unsigned int*)(0x20000000))
// #define INITRAMFS  ((volatile unsigned int*)(0x8000000))//qemu

typedef struct{
	char	   c_magic[6];
	char	   c_ino[8];
	char	   c_mode[8];
	char	   c_uid[8];
	char	   c_gid[8];
	char	   c_nlink[8];
	char	   c_mtime[8];
	char	   c_filesize[8];//8
	char	   c_devmajor[8];
	char	   c_devminor[8];
	char	   c_rdevmajor[8];
	char	   c_rdevminor[8];
	char	   c_namesize[8];//13
	char	   c_check[8];
}__attribute__((packed)) cpio_t;


void lsfile(char* buf);
void catfile(char* buf, char* target);
#endif