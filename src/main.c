#include "../include/main.h"

int main(int argc, char* argv[])
{
    FILE* in = fopen(argv[1],"r");
    FILE* out = fopen(argv[2],"w");
    convert(in,out);
    return 0;
}

void convert(FILE* infile, FILE* outfile)
{
    uint8_t notes[4096];
    uint8_t head;
    struct MThd hd;
    fread(&hd,sizeof(hd),1,infile);
    printf("//---  Header  ---\\\\\n");
    printf("  Magic : %X\n",hd.magic);
    printf("  Size : %i\n",hd.size);
    printf("  SMF : %hi\n",hd.SMF);
    printf("  Tracks : %hi\n",hd.tracks);
    printf("  BPM : %hi\n",hd.bpm);
    printf("\\\\---  Header  ---//\n");
}