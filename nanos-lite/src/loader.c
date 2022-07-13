#include <proc.h>
#include <elf.h>
#include <fs.h>
#ifdef __LP64__
# define Elf_Ehdr Elf64_Ehdr
# define Elf_Phdr Elf64_Phdr
#else
# define Elf_Ehdr Elf32_Ehdr
# define Elf_Phdr Elf32_Phdr
#endif


int    fs_open(const char *pathname, int flags, int mode);
size_t fs_read(int fd, void *buf, size_t len);
int    fs_close(int fd);
size_t fs_lseek(int fd, size_t offset, int whence);

static uintptr_t loader(PCB *pcb, const char *filename) {
  #if defined(__ISA_AM_NATIVE__)
  # define EXPECT_TYPE EM_X86_64
  #elif defined(__ISA_X86__)
  # define EXPECT_TYPE EM_X86_64
  #elif defined(__ISA_MIPS32__)
  # define EXPECT_TYPE EM_MIPS_X
  #elif defined(__ISA_RISCV32__) || defined(__ISA_RISCV64__)
  # define EXPECT_TYPE EM_RISCV
  #else
  # error Unsupported ISA
  #endif
  int fd = fs_open(filename,0,0);
  Elf_Ehdr elf;
  fs_read(fd,&elf,sizeof(elf));
  assert( *(uint32_t *)elf.e_ident == 0x464c457f);
  assert(elf.e_machine == EXPECT_TYPE);
  int i; 
  for(i=0;i<elf.e_phnum;i++){
    Elf_Phdr ph;
    fs_lseek(fd,elf.e_phoff + i*elf.e_phentsize,SEEK_SET);
    fs_read(fd,&ph,elf.e_phentsize);
    if(ph.p_type==PT_LOAD){
      fs_lseek(fd,ph.p_offset,SEEK_SET);
      fs_read(fd,(void *)ph.p_vaddr,ph.p_memsz);
      memset((void *)(ph.p_vaddr+ph.p_filesz),0,ph.p_memsz-ph.p_filesz);
    }
  }
  //printf("%d\n",elf.e_entry);
  fs_close(fd);
  return elf.e_entry;
}

void naive_uload(PCB *pcb, const char *filename) {
  uintptr_t entry = loader(pcb,filename );
  Log("Jump to entry = %p", entry);
  ((void(*)())entry) ();
}

