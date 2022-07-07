#include <proc.h>
#include <elf.h>
#ifdef __LP64__
# define Elf_Ehdr Elf64_Ehdr
# define Elf_Phdr Elf64_Phdr
#else
# define Elf_Ehdr Elf32_Ehdr
# define Elf_Phdr Elf32_Phdr
#endif


extern size_t ramdisk_read(void *buf, size_t offset, size_t len);
static uintptr_t loader(PCB *pcb, const char *filename) {
  Elf_Ehdr elf;
  ramdisk_read(&elf, 0, sizeof(Elf_Ehdr));
  assert( *(uint32_t *)elf.e_ident == 0x464c457f);
  int i; 
  for(i=0;i<elf.e_phnum;i++){
    Elf_Phdr pro_h;
    ramdisk_read(&pro_h,elf.e_phoff+i*elf.e_phentsize,elf.e_phentsize);
    if(pro_h.p_type==PT_LOAD){
      ramdisk_read((void *)pro_h.p_vaddr,pro_h.p_offset,pro_h.p_memsz);
      memset((void *)(pro_h.p_vaddr+pro_h.p_filesz),0,pro_h.p_memsz-pro_h.p_filesz);
    }
  }
  return (uintptr_t)elf.e_entry;
}

void naive_uload(PCB *pcb, const char *filename) {
  uintptr_t entry = loader(pcb, filename);
  Log("Jump to entry = %p", entry);
  ((void(*)())entry) ();
}

