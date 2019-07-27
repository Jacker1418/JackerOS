#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/io.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>

#define BYTES_OF_SECTOR 512

int Adjust_In_Sector_Size(int in_fd, int in_source_size);
void Write_Kernel_Info(int in_target_fd, int in_kernel_sector_count);
int Copy_File(int in_source_fd, int in_target_fd);

int main(int argc, char* argv[]){

	int fdSource;
	int fdTarget;
	int sizeBootloader;
	int countKernel32_Sector;
	int sizeSource;

	if(argc < 3){
		fprintf(stderr, "[ERROR] ImageMaker.exe Bootloader.bin Kernel32.bin\n");
		exit(-1);
	}

	if( (fdTarget = open( "Disk.img", O_RDWR | O_CREAT | O_TRUNC, S_IREAD | S_IWRITE))  == -1 ) {
		fprintf( stderr, "[ERROR] Disk.img open fail\n");
		exit(-1);
	}

	printf("[INFO] Copy bootloader to image file\n");

	if((fdSource = open ( argv[1], O_RDONLY )) == -1){
		fprintf(stderr, "[ERROR] %s open fail\n", argv[1]);
		exit(-1);
	}

	sizeSource = Copy_File(fdSource, fdTarget);
	close(fdSource);

	sizeBootloader = Adjust_In_Sector_Size(fdTarget, sizeSource);
	printf("[INFO] %s size = [%d] and sector count = [%d]\n", argv[1], sizeSource, sizeBootloader);

	printf("[INFO] Copy protected mode kernel to image file\n");

	if(( fdSource = open(argv[2], O_RDONLY )) == -1){
		fprintf(stderr, "[ERROR] %s open fail\n", argv[2]);
		exit(-1);
	}

	sizeSource = Copy_File(fdSource, fdTarget);
	close(fdSource);

	countKernel32_Sector = Adjust_In_Sector_Size(fdTarget, sizeSource);
	printf("[INFO] %s size = [%d] and sector count = [%d]\n", argv[2], sizeSource, countKernel32_Sector);

	printf("[INFO] Start to write kernel information\n");

	Write_Kernel_Info(fdTarget, countKernel32_Sector);
	printf("[INFO] Image file create complete\n");

	close(fdTarget);
	return 0;

}

int Adjust_In_Sector_Size(int in_fd, int in_size_source){

	int i;
	int size_AdjustSector;
	char ch;
	int countSector;

	size_AdjustSector = in_size_source % BYTES_OF_SECTOR;
	ch = 0x00;

	if( size_AdjustSector != 0 ){

		size_AdjustSector = 512 - size_AdjustSector;
		printf("[INFO] File size [%lu] and fill [%u] byte\n", in_size_source, size_AdjustSector);
		for( i = 0; i < size_AdjustSector; i++){
			write(in_fd, &ch, 1);
		}
	}else{
		printf("[INFO] File size is aligned 512 byte\n");
	}

	countSector = (in_size_source + size_AdjustSector ) / BYTES_OF_SECTOR;

	return countSector;
}

void Write_Kernel_Info(int in_target_fd, int in_kernel_sector_count){
	
	unsigned short usData;
	long position;

	position = lseek(in_target_fd, (off_t)5, SEEK_SET );
	if(position == -1){
		fprintf(stderr, "lseek fail, Return value = %d, errno = %d, %d\n", position, errno, SEEK_SET);
		exit(-1);
	}

	usData = (unsigned short)in_kernel_sector_count;
	write( in_target_fd, &usData, 2);

	printf("[INFO] Total sector count except boot loader [%d]\n", in_kernel_sector_count);
}

int Copy_File(int in_source_fd, int in_target_fd){

	int size_SourceFile;
	int Read;
	int Write;
	char vcBuffer[BYTES_OF_SECTOR];

	size_SourceFile = 0;

	while(1){
	
		Read = read(in_source_fd, vcBuffer, sizeof(vcBuffer));
		Write = write(in_target_fd, vcBuffer, Read);

		if(Read != Write){
			fprintf( stderr, "[ERROR] Read != Write..\n");
			exit(-1);
		}

		size_SourceFile += Read;

		if(Read != sizeof(vcBuffer)){
			break;
		}
	}

	return size_SourceFile;
}
