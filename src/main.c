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
    bool delayMode = true;
    fread(&hd,sizeof(hd),1,infile);
    printf("//---  Header  ---\\\\\n");
    printf("  Magic : %X\n",hd.magic);
    printf("  Size : %i\n",hd.size);
    printf("  SMF : %hi\n",hd.SMF);
    printf("  Tracks : %hi\n",hd.tracks);
    printf("  BPM : %hi\n",hd.bpm);
    printf("\\\\---  Header  ---//\n");
    for(int i = 0; i < hd.tracks; i++)
    {
        struct MTrk trk;
        fread(&trk,sizeof(trk),1,infile);
        printf("//--  Track %i  --\\\\\n", i);
        printf("  Magic : %X\n",trk.magic);
        printf("  Size : %i\n",trk.size);
        uint32_t delay = 0;
        uint8_t status = 0;
        uint32_t ignore = 0;
        for(int j = 0; j < trk.size-ignore-3; j++)
        { 
            head = getc(infile);
            if(delayMode) 
            {
                if(head > 127)
                {
                    delay = delay * 128 + (head-128);
                }
                else
                {
                    delay = delay * 128 + head;
                    delayMode = false;
                }
            }
            else
            {
                if(head > 127)
                {
                    status = head;
                }
                
                uint8_t function = status & 0xF0;
                uint8_t channel = status & 0x0F;
                uint8_t note = 0;
                uint8_t velo = 0;
                switch(function)
                {
                    case 0x90 : 
                        note = getc(infile);
                        velo = getc(infile);
                        printf("Note %hhX ON, delay : %i, channel : %hhi \n",note, delay, channel);
                        ignore += 2;
                        break;
                    case 0x80 : 
                        note = getc(infile);
                        velo = getc(infile);
                        printf("Note %hhX OFF, delay : %i, channel : %hhi \n",note, delay, channel);
                        ignore += 2;
                        break;
                    case 0xC0 : 
                        printf("Event not known, delay : %i \n",delay);
                        ignore += 1;
                        break;
                    case 0xD0 : 
                        printf("Event not known, delay : %i \n",delay);
                        ignore += 1;
                        break;
                    default:
                        printf("Event not known %hhX, delay : %i \n",function, delay);
                        getc(infile);
                        getc(infile);
                        ignore += 2;
                        break;
                } 
                delayMode = true;
            }
        }
        printf("%hhX %hhX %hhX \n",getc(infile),getc(infile),getc(infile));
        printf("\\\\--  Track %i  --//\n", i);
    }
}