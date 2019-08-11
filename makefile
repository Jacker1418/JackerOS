all: BOOTLOADER KERNEL32 KERNEL64 Disk.img Utility

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

KERNEL64:
	@echo
	@echo ================= Build 64bit Kernel =========================
	@echo

	make -C Kernel64

	@echo
	@echo ================ Build Complete =============================
	@echo

Disk.img: ./Bootloader/Bootloader.bin ./Kernel32/Kernel32.bin Kernel64/Kernel64.bin
	@echo 
	@echo ================== Disk Image Build Start ====================
	@echo

	./Utility/ImageMaker/ImageMaker.exe $^

	@echo
	@echo ================== All Build Complete    =====================
	@echo

Utility:
	@echo
	@echo ================= Build 32bit Kernel =========================
	@echo

	make -C Utility/ImageMaker

	@echo
	@echo ================ Build Complete =============================
	@echo

clean:
	make -C Bootloader clean
	make -C Kernel32 clean
	make -C Kernel64 clean
	rm -f Disk.img

