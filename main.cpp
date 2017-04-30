#include <stdio.h>
#include <stdint.h>
#include <vector>
#include "MachO.hpp"


void print_header(MachHeader header)
{
        if (header.getMagic() == MAGIC_32)
                printf("MACH-O 32\n");
        else
                printf("MACH-O 64\n");

        printf("cputype:%d\n subtype:%x\nfiletype:%x\nncmds:%d\nsize:%d\nflags:%x\n", header.getCpuType(),
                        header.getCpuSubType(), header.getFileType(), header.getNumberCmds(), header.getSizeOfCmds(), header.getFlags());

        if (header.getMagic() == MAGIC_64)
                printf("reserved:%x\n", header.getReserved());
}
void print_section(Section *section)
{
        printf("Segment name: %s\nSection name %s\n",
        section->getSegmentName(), section->getSectionName());

        printf("virtual address: %lld\nsize: %lld\n",
        section->getVirtualAddress(), section->getSize());

        printf("offset: %d\nnumber of relocations: %d\nalign: %d\n" ,
        section->getOffset(), section->getNumberRelocations(), section->getAlign());

        printf("relocation offset: %d\nflags: %u\n",
        section->getRelocationOffset(), section->getFlags());

        printf("reserved1: %d\nreserved2: %d\n",
        section->getReserved1(), section->getReserved2());
}

void print_segment(Segment *segment)
{
        printf("Segment Name: %s\n", segment->getName());

        printf("virtual address: %lld\nvirtual size: %lld\n",
                segment->getVirtualAddress(), segment->getVirtualSize());

        printf("file offset: %lld\nfile size: %lld\n",
                segment->getFileOffset(), segment->getFileSize() );

        printf("init prot: 0x%x\nmax prot: %x\n",
                segment->getInitProtection(), segment->getMaxProtection());

        printf("flags: %x\nnumber of sections: %d\n",
                segment->getFlags(), segment->getNumberSections());

        std::vector<Section *> sections = segment->getSections();
        for(int i = 0; i < segment->getNumberSections(); i++)
                print_section(sections[i]);
}


/*listing of segments and sections*/
int main(int argc, char *argv[])
{
        FILE *file;

        if (argc != 2) {
                printf("Usage: %s <binary>\n", argv[0]);
                return -1;
        }
        MachO bin(argv[1]);
        MachHeader header = bin.getHeader();
        print_header(header);

        std::vector<Segment *> segments = bin.getSegments();

        for(int i = 0; i < segments.size(); i++) {
                print_segment(segments[i]);
        }
        return 0;
}