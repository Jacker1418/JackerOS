all: BOOTLOADER KERNEL32 Disk.img	

BOOTLOADER:
	@echo
	@echo ================== Build Boot Loader =========================
	@echo

	make -C Bootloader

	@echo
	@echo ================== Build Complete    =========================
	@echo

KERNEL32:
	@echo
	@echo ================= Build 32bit Kernel =========================
	@echo

	make -C Kernel32

	@echo
	@echo ================ Build Complete =============================
	@echo

Disk.img: ./Bootloader/Bootloader.bin ./Kernel32/Kernel32.bin
	@echo 
	@echo ================== Disk Image Build Start ====================
	@echo

	./Utility/ImageMaker/ImageMaker.exe $^

	@echo
	@echo ================== All Build Complete    =====================
	@echo

clean:
	make -C Bootloader clean
	make -C Kernel32 clean
	rm -f Disk.img

