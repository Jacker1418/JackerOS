NASM32 = nasm
GCC32 = gcc -c -m32 -ffreestanding
LD32 = ld -melf_i386 -T ../elf_i386.x -nostdlib -e Main -Ttext 0x10200
OBJCOPY32 = objcopy -j .text -j .data -j .rodata -j .bss -S -O binary

OBJECT_DIR = Temp
SOURCE_DIR = Source

ALL: PREPARE Kernel32.bin

PREPARE:
	@echo ===== PREPARE Label =======
	mkdir -p $(OBJECT_DIR)

$(OBJECT_DIR)/EntryPoint.bin:$(SOURCE_DIR)/EntryPoint.s
	@echo ===== EntryPoint.bin Label =====
	$(NASM32) -o $@ $<

dep:
	@echo ==== Make Dependancy File ====
	make -C $(OBJECT_DIR) -f ../makefile Internal_Dependency
	@echo === Dependancy Search Complete ===

Excute_Internal_Build: dep
	@echo ===== Excute_Internal_Build Label =====
	make -C $(OBJECT_DIR) -f ../makefile Kernel32.elf

$(OBJECT_DIR)/Kernel32.elf.bin: Excute_Internal_Build
	@echo ====== Kernel32.elf.bin Label =========
	$(OBJCOPY32) $(OBJECT_DIR)/Kernel32.elf $@

Kernel32.bin: $(OBJECT_DIR)/EntryPoint.bin $(OBJECT_DIR)/Kernel32.elf.bin
	@echo ===== Kernel32.bin Label =====
	cat $^ > $@

clean:
	rm -f *.bin
	rm -f $(OBJECT_DIR)/*.*

CENTRY_POINT_OBJECT_FILE = Main.o
CSOURCE_FILES = $(wildcard ../$(SOURCE_DIR)/*.c)
ASSEMBLY_SOURCE_FILES = $(wildcard ../$(SOURCE_DIR)/*.asm)
COBJECT_FILES = $(subst Main.o, ,$(notdir $(patsubst %.c, %.o, $(CSOURCE_FILES))))
ASSEMBLY_OBJECT_FILES = $(notdir $(patsubst %.asm, %.o, $(ASSEMBLY_SOURCE_FILES)))

%.o: ../$(SOURCE_DIR)/%.c
	@echo ===== (.c) Label =====
	$(GCC32) -c $<

%.o: ../$(SOURCE_DIR)/%.asm
	@echo ===== (.asm) Label =====
	$(NASM32) -f elf32 -o $@ $<

Internal_Dependency:
	@echo ===== Internal_Dependency Label =====
	$(GCC32) -MM $(CSOURCE_FILES) > Dependency.dep

Kernel32.elf: $(CENTRY_POINT_OBJECT_FILE) $(COBJECT_FILES) $(ASSEMBLY_OBJECT_FILES)
	@echo ===== Kernel32.elf Label =====
	$(LD32) -o $@ $^

ifeq (Dependency.dep, $(wildcard Dependency.dep))
include Dependency.dep
endif
