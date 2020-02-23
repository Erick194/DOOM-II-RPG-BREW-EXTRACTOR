
#include <windows.h>
#include <conio.h>
#include <stdio.h>

#include "funciones.h"
#include "zip.h"
#include "unzip.h"
#include "midis.h"
#include <png.h>

using namespace std;

HZIP hz; DWORD writ;


char string[64] = { 0 };

byte QCPDATA[174] =
{
0x51,0x4c,0x43,0x4d,0x66,0x6d,0x74,0x20,0x96,0x00,0x00,0x00,0x01,0x00,0x41,0x6d,0x7f,0x5e,0x15,0xb1,0xd0,0x11,0xba,0x91,
0x00,0x80,0x5f,0xb4,0xb9,0x7e,0x02,0x00,0x51,0x63,0x65,0x6c,0x70,0x20,0x31,0x33,0x4b,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x40,0x38,0x23,0x00,0xa0,0x00,0x40,0x1f,
0x10,0x00,0x04,0x00,0x00,0x00,0x03,0x01,0x07,0x02,0x10,0x03,0x22,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x76,0x72,0x61,0x74,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
};

char *names[145]=
{
"Arachnotron_active",
"Arachnotron_death",
"Arachnotron_sight",
"Arachnotron_walk",
"Archvile_active",
"Archvile_attack",
"Archvile_death",
"Archvile_pain",
"Archvile_sight",
"BFG",
"block_drop",
"block_pick",
"Cacodemon_death",
"Cacodemon_sight",
"chaingun",
"chainsaw",
"ChainsawGoblin_attack",
"ChainsawGoblin_death",
"ChainsawGoblin_pain",
"ChainsawGoblin_sight",
"chime",
"claw",
"Cyberdemon_death",
"Cyberdemon_sight",
"demon_active",
"demon_pain",
"demon_small_active",
"dialog_help",
"door_close",
"door_close_slow",
"door_open",
"door_open_slow",
"explosion",
"fireball",
"fireball_impact",
"footstep1",
"footstep2",
"gib",
"glass",
"hack_clear",
"hack_fail",
"hack_failed",
"hack_submit",
"hack_success",
"hack_successful",
"HolyWaterPistol",
"HolyWaterPistol_refill",
"hoof",
"impClaw",
"Imp_active",
"Imp_death1",
"Imp_death2",
"Imp_sight1",
"Imp_sight2",
"item_pickup",
"loot",
"LostSoul_attack",
"Maglev_arrive",
"Maglev_depart",
"malfunction",
"Mancubus_attack",
"Mancubus_death",
"Mancubus_pain",
"Mancubus_sight",
"menu_open",
"menu_scroll",//65
"monster_pain",
"Music_Boss",//67
"Music_General",//68
"Music_Levelup",//69
"Music_Level_End",//70
"Music_Title",//71
"no_use",
"no_use2",
"Pinkinator_attack",
"Pinkinator_death",
"Pinkinator_pain",
"Pinkinator_sight",
"Pinkinator_spawn",
"Pinky_attack",
"Pinky_death",
"Pinky_sight",
"Pinky_small_attack",
"Pinky_small_death",
"Pinky_small_pain",
"Pinky_small_sight",
"pistol",
"plasma",
"platform_start",
"platform_stop",
"player_death1",
"player_death2",
"player_death3",
"player_pain1",
"player_pain2",
"Revenant_active",
"Revenant_attack",
"Revenant_death",
"Revenant_punch",
"Revenant_sight",
"Revenant_swing",
"rocketLauncher",
"rocket_explode",
"secret",
"Sentinel_attack",
"Sentinel_death",
"Sentinel_pain",
"Sentinel_sight",
"SentryBot_activate",
"SentryBot_death",
"SentryBot_discard",
"SentryBot_pain",
"SentryBot_return",
"slider",
"Soulcube",
"SpiderMastermind_death",
"SpiderMastermind_sight",
"supershotgun",
"supershotgun_close",
"supershotgun_load",
"supershotgun_open",
"switch",
"switch_exit",
"teleport",
"use_item",
"vending_sale",
"vent",
"VIOS_attack1",
"VIOS_attack2",
"VIOS_death",
"VIOS_pain",
"VIOS_sight",
"weapon_pickup",
"Weapon_Sniper_Scope",
"Weapon_Toilet_Pull",
"Weapon_Toilet_Smash",
"Weapon_Toilet_Throw",
"Weapon_Toilet_Throw2",
"zombie_active",
"zombie_death1",
"zombie_death2",
"zombie_death3",
"zombie_sight1",
"zombie_sight2",
"zombie_sight3"
};

typedef byte*  cache;
static cache writeData;
static unsigned int current = 0;

//**************************************************************
//**************************************************************
//  Png_WriteData
//
//  Work with data writing through memory
//**************************************************************
//**************************************************************

static void Png_WriteData(png_structp png_ptr, cache data, size_t length) {
    writeData = (byte*)realloc(writeData, current + length);
    memcpy(writeData + current, data, length);
    current += length;
}

//**************************************************************
//**************************************************************
//  Png_Create
//
//  Create a PNG image through memory
//**************************************************************
//**************************************************************

static int TablesOffsets[20] = {0};
cache Png_Create(cache data, int* size, int width, int height, int paloffset, int offsetx = 0, int offsety = 0, bool sky = false)
{
    int i, j;
    cache image;
    cache out;
    cache* row_pointers;
    png_structp png_ptr;
    png_infop info_ptr;
    png_colorp palette;
    
    int bit_depth = 8;
    // setup png pointer
    png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, 0, 0, 0);
    if(png_ptr == NULL) {
        error("Png_Create: Failed getting png_ptr");
        return NULL;
    }

    // setup info pointer
    info_ptr = png_create_info_struct(png_ptr);
    if(info_ptr == NULL) {
        png_destroy_write_struct(&png_ptr, NULL);
        error("Png_Create: Failed getting info_ptr");
        return NULL;
    }

    // what does this do again?
    if(setjmp(png_jmpbuf(png_ptr))) {
        png_destroy_write_struct(&png_ptr, &info_ptr);
        error("Png_Create: Failed on setjmp");
        return NULL;
    }

    // setup custom data writing procedure
    png_set_write_fn(png_ptr, NULL, Png_WriteData, NULL);

    // setup image
    png_set_IHDR(
        png_ptr,
        info_ptr,
        width,
        height,
        bit_depth,
        PNG_COLOR_TYPE_PALETTE,
        PNG_INTERLACE_NONE,
        PNG_COMPRESSION_TYPE_DEFAULT,
        PNG_FILTER_TYPE_DEFAULT);

    // setup palette
    FILE *fpal = fopen ("Datos/newPalettes.bin","rb");
    if(!fpal)
    {
       error("No puede abrir newPalettes.bin");
    }

    if(sky)
    {
       fclose(fpal);
       
       fpal = fopen ("Datos/tables.bin","rb");
       if(!fpal)
          error("No puede abrir tables.bin");
          
       fseek(fpal, TablesOffsets[paloffset],SEEK_SET);
       int size = ReadUint(fpal);
       
       //printf("%d\n",TablesOffsets[paloffset]);
       //printf("%d\n",size);
    }
    else
        fseek(fpal,(paloffset),SEEK_SET);
        
    palette = (png_colorp) malloc((256*3)*png_sizeof(png_color));
     
    int gettrans = -1;
    for(int x = 0;x < 256;x++)
    {
       int Palbit = ReadWord(fpal);
       int B = (B = Palbit & 0x1F) << 3 | B >> 2;
       int G = (G = Palbit >> 5 & 0x3F) << 2 | G >> 4;
       int R = (R = Palbit >> 11 & 0x1F) << 3 | R >> 2;
 
       palette[x].red = R;
       palette[x].green = G;
       palette[x].blue = B;
       
       if(gettrans == -1)
       {
          if(palette[x].red==255 && palette[x].green==0 && palette[x].blue==255)
             gettrans = x;
          else if(palette[x].red==255 && palette[x].green==4 && palette[x].blue==255)
             gettrans = x;
       }
    }
    fclose(fpal);
    
    png_set_PLTE(png_ptr, info_ptr,palette,256);
    
    if(gettrans != -1)
    {
        png_byte trans[gettrans+1]; 
        for(int tr =0;tr < gettrans+1; tr++)
        {
          if(tr==gettrans){trans[tr]=0;}
          else {trans[tr]=255;}
        }
        png_set_tRNS(png_ptr, info_ptr,trans,gettrans+1,NULL);
    }

    // add png info to data
    png_write_info(png_ptr, info_ptr);

    if(offsetx !=0 || offsety !=0)
    {
       int offs[2];
    
       offs[0] = Swap32(offsetx);
       offs[1] = Swap32(offsety);
    
       png_write_chunk(png_ptr, (png_byte*)"grAb", (byte*)offs, 8);
    }

    // setup packing if needed
    png_set_packing(png_ptr);
    png_set_packswap(png_ptr);

    // copy data over
    byte inputdata;
    image = data;
    row_pointers = (cache*)malloc(sizeof(byte*) * height);
    for(i = 0; i < height; i++)
    {
        row_pointers[i] = (cache)malloc(width);
        for(j = 0; j < width; j++)
        {
            inputdata = *image;
            //if(inputdata == 0x7f){inputdata = (byte)gettrans;}
            row_pointers[i][j] = inputdata;
            image++;
        }
    }

    // cleanup
    png_write_image(png_ptr, row_pointers);
    png_write_end(png_ptr, info_ptr);
    free((void**)&palette);
    free((void**)row_pointers);
    palette = NULL;
    row_pointers = NULL;
    png_destroy_write_struct(&png_ptr, &info_ptr);

    // allocate output
    out = (cache)malloc(current);
    memcpy(out, writeData, current);
    *size = current;

    free(writeData);
    writeData = NULL;
    current = 0;

    return out;
}

//--------Flip--------//
static void flip(byte *input, byte *output, int width, int height)
{
    int i;
    int length = (width*height);
    //printf("sizeof(input) %d\n",length);
    
    byte pixel;
    int count = 0;
    int offset = 1;
    for(int i=0; i < height; i++)
    {
        for(int j=0; j < width; j++)
        {
            pixel = (byte)input[count];
            output[(length-width*offset)+j] = (byte)pixel;
            count++;
        }
        offset+=1;
    }
}

//--------Rotar 90º Y Flip--------//
static void rotate90andflip(byte *input, byte *output, int width, int height)
{
    int i;
    int length = (width*height);
    int height0 = height;//width
    int width0 = length / height;//height
    //printf("sizeof(input) %d\n",length);
    
    int bit1 = width0;
    int bit2 = 1;
    int bit3 = 0;
    
    int offset = length;
    
    byte pixel;
    for(i = 0; i < length; i++)
    {
    pixel = (byte)input[i];
    output[length - offset + bit3] = (byte)pixel;
    
    if(bit2 == height0){offset = length;}
    else{offset = length - bit1;}
    
    if(bit2 == height0){bit2 = 0; bit3 += 1;}
    bit2 +=1;
    bit1 = width0 * bit2;
    }
}

static int pngcount2 = 0;
void Create_Walls(int file, int startoff,int count,int paloffset, int x0, int x1, int y0, int y1)
{
     char string2[64] = { 0 };
    //printf("x0 %d x1 %d y0 %d y1 %d\n",x0,x1,y0,y1);
    
    int width = x1-x0;
    int width2 = 256;
    if(width <= 256){width2 = 256;}
    if(width <= 128){width2 = 128;}
    if(width <= 64){width2 = 64;}
    if(width <= 32){width2 = 32;}
    if(width <= 16){width2 = 16;}
    if(width <= 8){width2 = 8;}
    if(width <= 4){width2 = 4;}
    if(width <= 0){width2 = 256;}
    width += (width2-width);
    int height = count/width;
    
    int mode;

    //printf("width %d height %d\n",width,height);
    
    sprintf(string2,"Datos/newTexels%3.3d.bin",file);
    
    FILE *in;
    in = fopen(string2,"rb");
    if(!in)
    {
     error("No puede abrir %s", string2);
    }
    //printf("%s\n", string2);
    //FILE *out = fopen("tex.raw","wb");

    cache input;
    cache output;
    cache pngout;
    
    input = (byte*)malloc(count);
    output = (byte*)malloc(count);
    
    for(int a = 0; a < (width*height); a++)
    {
       input[a] = 0x00;
    }
    //printf("startoff %d\n", startoff);
    fseek(in, startoff,SEEK_SET);
    //printf("mode %d\n", mode);getch();
    
    byte pixel = 0;
    for(int a = 0; a < count; a++)
    {
       pixel = ReadByte(in);
       input[a] = pixel;
    }
    
    flip(input, output, width, height);

    int pngsize = 0;
    pngout = Png_Create(output, &pngsize,width,height, paloffset);

    sprintf(string,"WTEX/WTEX%03d",pngcount2);
    ZipAdd(hz, string, pngout, pngsize);
    pngcount2++;

    fclose(in);
    free(input);
    free(output);
    free(pngout);
    //getch();
}

static int pngcount = 0;
void Create_Sprites(int file, int startoff,int count,int paloffset, int x0, int x1, int y0, int y1)
{
    //printf("x0 %d x1 %d y0 %d y1 %d\n",x0,x1,y0,y1);
    
    int width = x1-x0;
    int height = y1-y0;
    char string2[64] = { 0 };
    int endoffset, shapeoffset;
    
    //printf("width %d height %d\n",width,height);//getch();
    
    sprintf(string2,"Datos/newTexels%3.3d.bin",file);
    
    FILE *in;
    in = fopen(string2,"rb");
    if(!in)
    {
     error("No puede abrir %s", string2);
    }
    
    endoffset = (startoff+count)-2;
    fseek(in, endoffset,SEEK_SET);
    
    shapeoffset = endoffset - ReadWord(in);
    fseek(in, shapeoffset,SEEK_SET);
    //printf("endoffset %d\n",endoffset);
    //printf("shapeoffset %d\n",shapeoffset);
    
    int i = 0;
    int j = 0;
    int k = 0;
    int linecount = 0;
    int shapetype[256] = {0};
    byte shape;
    byte shapeBit;
    for(i = 0; i < width; i++)
    {
       if(!(i & 1))
          shape = ReadByte(in);
          
          
       if(!(i & 1))
          shapeBit = (byte)(shape & 0xF);
       else 
          shapeBit = (byte)(shape >> 4 & 0xF);
     
       shapetype[i] = shapeBit;
    }
    
    linecount = i;
    //printf("linecount %d\n",linecount);
    
    byte* input;
    byte* output;
    byte* pngout;
    
    //height = 88;//con y offset puesto
    input = (byte*)malloc(width*height);
    output = (byte*)malloc(width*height);
    memset(input, 0 , width*height); 
    memset(output, 0 , width*height); 
    
    /*for(int a = 0; a < (width*height); a++)
    {
       input[a] = 0x00;
    }*/
    
    //printf("pos %d\n",ftell(in));
    
    int pos = 0;
    int cnt = 0;
    for(i = 0; i < linecount; i++)
    {
       if(shapetype[i] != 0)
       {
           for(j = 0; j < shapetype[i]; j++)
           {
               //pos = ReadByte(in);//con y offset puesto
               pos = (ReadByte(in) - y0)+1;
               cnt = ReadByte(in);
               for(k = 0; k < cnt; k++)
               {
           	      input[((i*height)+ pos)+k] = 0xff;
               }
           }
       }
       /*else
       {
           pos = 0;//con y offset puesto
           cnt = 88;
           for(k = 0; k < cnt; k++)
           {
       	      input[((i*height)+ pos)+k] = 0x00;
           }
       }*/
    }
    
    fseek(in, startoff,SEEK_SET);
    byte pixel = 0;
    for(int a = 0; a < (width*height); a++)
    {
       if(input[a] == 0xff)
       {
          pixel = ReadByte(in);
          input[a] = pixel;
       }
    }
    
    rotate90andflip(input, output, width, height);

    int offsetx = (44-x0);
    int offsety = (88-y0)+1;
    int pngsize = 0;
    pngout = Png_Create(output, &pngsize,width,height, paloffset, offsetx, offsety);

    sprintf(string,"STEX/STEX%03d",pngcount);
    ZipAdd(hz, string, pngout, pngsize);
    pngcount++;
    
    fclose(in);
    free(input);
    free(output);
    free(pngout);
}

sword Unk01[512];
byte Unk02[1024];
byte Sizes[4096];//x1x2y1y2
sword Pals[1024];
sword Tex[1024];

static void initflags(int paramInt)
{
    int pos, cnt;
    cnt = Unk01[paramInt];
    paramInt = Unk01[(paramInt + 1)];
    //printf("cnt %d paramInt %d\n",cnt,paramInt);
    while (cnt < paramInt)
    {
      pos = cnt;
      if (Pals[pos] & 0x8000)
      {
        pos = Pals[pos] & 0x3FF;
      }
      Pals[pos] |= 0x4000;
      //printf("pos %d Pal %d\n",pos ,Pals[pos]);
      
      pos = cnt;
      if (Tex[pos] & 0x8000)
      {
        pos = Tex[pos] & 0x3FF;
      }
      Tex[pos] |= 0x4000; 
      
      //printf("pos %d Tex %d\n",pos ,Tex[pos]);
      cnt++;
    }
}

static int Texels[4096] = {0};
static int SpriteOffset[4096][3] = {0,0,0};
static int TextureOffset[4096][3] = {0,0,0};
static int PalsOffset[4096] = {0};


static int Grapics[4096][4] = {0,0,0,0};

static void inittex()
{
    int u = 0;
    int v = 0;
    int i5 = 0;
    int i6 = 1;
    int i4 = 0;
    int i8 = 0;
    int i9 = 0;
    int i10 = 0;
    int i11 = 0;
    int i12 = 0;
    int i7 = 0;
    for (i7 = 0; i7 < 1024; i7++)
    {
      /*if((Tex[i7] >> 14) & 1)
      {
          //v8 = (Tex[i7] & 0x3FFF) + 1;
          //Tex[i7] = 0x2000u;
          //printf("Tex size %d\n", (Tex[i7] & 0x3FFF) + 1);
      }
      
      if((Pals[i7] >> 14) & 1)
      {
          //v8 = (Pals[i7] & 0x3FFF) + 1;
          //printf("Pal size %d\n", (Pals[i7] & 0x3FFF));
      }*/
      
      i8 = (Tex[i7] & 0x4000) != 0 ? 1 : 0;
      i9 = (Pals[i7] & 0x4000) != 0 ? 1 : 0;
      
      //printf("i7 %d\n",i7);
      //printf("i8 %d\n",i8);//tex
      //printf("i9 %d\n",i9);//Pals
      if (i8 != 0)
      {
        if ((((i8 = i10 = (Tex[i7] & 0x3FFF) + 1) - 1 & i8) == 0 ? 1 : 0) != 0)
        {
          //printf("i6 %d i10 %d\n",i6,i10+4);//Tex
         // printf("v8 %d\n",(Tex[i7] & 0x3FFF) + 1);//Tex
          //getch();
          //Tex[i7] |= 0x1000;
        }
        else
        {
          i4 += i10;
        }
      }
      if (i9 != 0)
      {
        if ((i10 = Pals[i7] & 0x3FFF) < 256) {
          i10 = 256;
        }
        //printf("i5 %d i10 %d\n",i6,i10);//Pals
        i5++;
      }
      //getch();
    }
    
    //printf("\n\n\n");
    i5 = 0;
    int paloffs = 0;
    for (i7 = 0; i7 < 1024; i7++)
    {
      i8 = (Pals[i7] & 0x4000) != 0 ? 1 : 0;
      i9 = (Pals[i7] & 0x8000) != 0 ? 1 : 0;
      i10 = Pals[i7] & 0x3FFF;
      
      //printf("i8 %d i9 %d i10 %d\n",i8,i9,i10);//Pals
      if ((i8 != 0) && (i9 == 0))
      {
        //printf("paloffs %d i5 %d\n",paloffs,i5);//Pals
        PalsOffset[i5] = paloffs;
        i11 = (short)(i7 | 0x8000);
        for (i12 = i7 + 1; i12 < 1024; i12++) {
          if (Pals[i12] == i11) {
            Pals[i12] = ((short)(0xC000 | i5));
          }
        }
        Pals[i7] = ((short)(0x4000 | i5));
        i5++;
        paloffs += (i10 << 1)+4;
      }
      else if (i9 == 0)
      {
        //printf("i9 Pals i10 %d\n",i10);//Pals
       
      }
      //getch();
    }
    
    i6 = 0;
    i7 = -1;
    i8 = 0;
    i9 = 0;
    i10 = 0;
    i11 = 0;
    i12 = 0;
    i5 = 0;
    
    int i15 = 0;
    //printf("\n\n\n");
    int v29, v32, t1, t2;
    for (int i1 = 0; i1 < 1024; i1++)
    {
      int i13 = (Tex[i1] & 0x3FFF) + 1;
      if(!(Tex[i1] & 0x4000) || (Tex[i1] & 0x8000))
      {
         if (!(Tex[i1] & 0x8000))
            i9 += i13 + 4;
      }
      else
      {
          if (i10 != i7)
          {
             i7 = i10;
             i8 = 0;
             //printf("i7 %d\n",i7);//tex
          }
          
          if (i8 != i9)
          {
             //printf("i9 - i8 %d\n",i9 - i8);//tex
          }

          if ((((t1 = t2 = (Tex[i1] & 0x3FFF) + 1) - 1 & t1) == 0 ? 1 : 0) != 0)
          {
              //printf("i5 %d v8 %d fl %x\n",i5, (Tex[i1] & 0x3FFF) + 1, Tex[i1]);//Tex
              if(i5 > 210)
              {
                    Tex[i1] |= 0x2000;
              }
              //getch();
          }
          
          Grapics[i5][0] = Tex[i1] & (0x2000);
          Grapics[i5][1] = i7;
          Grapics[i5][2] = i8;
          Grapics[i5][3] = (i13);
          
          //printf("i5 %d Mode [%x] || File [%d] || Start [%d] || Size [%d]\n",i5, Grapics[i5][0],Grapics[i5][1],Grapics[i5][2],Grapics[i5][3]);
          //getch();
          //printf("i5 %d i13 %d\n",i5, i13);
          
          
          for (v32 = i1 + 1; v32 < 1024; v32++)
          {
              if (Tex[v32] == (short)(i1 | 0x8000))
              {
                Tex[v32] = ((short)(i5 | 0xC000));
              }
          }
          
          Tex[i1] = i5++ | 0x4000;
          
          i9 += i13 + 4;
          i8 = i9;
      }
      if ( i9 > 0x10000 )
      {
          i10++;
          i9 = 0;
      }
    }
}

static void extraer(int paramInt1)
{
    //system("CLS");
    int i1 = paramInt1;
    //printf("i1 %d\n",i1);

    int file = 0;
    int startoff = 0;
    int count = 0;
    int paramInt, x0, x1, y0, y1;

    bool sprite = false;

    paramInt1 = Tex[i1] & 0x1FFF;
    //printf("paramInt1 %d\n",paramInt1);
    
    //printf("Grapics[%d][0] %X\n",paramInt1, Grapics[paramInt1][0]);

    if(Grapics[paramInt1][0] & 0x2000)
    {
        file = Grapics[paramInt1][1];
        startoff = Grapics[paramInt1][2];
        count = Grapics[paramInt1][3];
        //printf("File %d\n",file);
        //printf("OffsetS %d\n",startoff);
        //printf("OffsetE %d\n",count);
        sprite = false;
        //getch();
    }
    else
    {
        file = Grapics[paramInt1][1];
        startoff = Grapics[paramInt1][2];
        count = Grapics[paramInt1][3];
        //printf("File %d\n",file);
        //printf("OffsetS %d\n",startoff);
        //printf("OffsetE %d\n",count);
        sprite = true;
    }
    
    
    paramInt = Pals[i1] & 0x3FF;
    //printf("pal %d\n",paramInt);//arrayOfInt1[(Pals[i1] & 0x3FF)]);
    //printf("PalsOffset %d\n",PalsOffset[paramInt]);
    x0 = (Sizes[(i1 << 2)] & 0xFF);
    x1  = (Sizes[((i1 << 2) + 1)] & 0xFF);
    y0  = (Sizes[((i1 << 2) + 2)] & 0xFF);
    y1  = (Sizes[((i1 << 2) + 3)] & 0xFF);
    //printf("x0 %d x1 %d y0 %d y1 %d\n",x0,x1,y0,y1);
  
    if (sprite)
    {
        Create_Sprites(file,startoff,count,PalsOffset[paramInt], x0, x1, y0, y1);
    }
    else
    {
        Create_Walls(file,startoff,count,PalsOffset[paramInt], x0, x1, y0, y1);
    }
}

void ReadTablesOffset()
{
    FILE *fp = fopen("Datos/tables.bin","rb");
    if(!fp)
    {
     error("No puede abrir tables.bin");
    }
    
    int LastOffset = 0;
    int NextOffset = 0;
    for(int i = 0; i < 24; i++)
    {
       NextOffset = ReadUint(fp);
       TablesOffsets[i] = LastOffset+96;
       LastOffset = NextOffset;
    }
    fclose(fp);
}

void ExtraerSKYS(int idx, int num)
{
    FILE *fp = fopen("Datos/tables.bin","rb");
    if(!fp)
    {
     error("No puede abrir tables.bin");
    }
    
    PrintfPorcentaje(1,1,true, 12+num,"Extrayendo SKY%02d......",num);
    
    fseek(fp, TablesOffsets[idx],SEEK_SET);
    int size = ReadUint(fp);
    //printf("%d\n",TablesOffsets[idx]);
    //printf("%d\n",size);
    
    cache input = (byte*)malloc(size);
    for(int a = 0; a < size; a++)
       input[a] = ReadByte(fp);
       
    int pngsize = 0;
    cache pngout = Png_Create(input, &pngsize, 256, 256, idx-1, 0, 0, true);

    /*
    //DEBUG
    sprintf(string,"SKY%02d.png",num);
    FILE *f2 = fopen(string,"wb");
    for(int i = 0; i < pngsize; i++)
    fputc(pngout[i], f2);
    fclose(f2);
    */

    sprintf(string,"SKYS/SKY%02d", num);
    ZipAdd(hz, string, pngout, pngsize);
    pngcount++;
    
    fclose(fp);
    free(input);
    free(pngout);
}

void ShowInfo()
{
    setcolor(0x07);printf("     ############");
    setcolor(0x0A);printf("(ERICK194)");
    setcolor(0x07);printf("#############\n"); 
    printf("     #  DOOM II RPG (BREW) EXTRACTOR   #\n");
    printf("     # CREADO POR ERICK VASQUEZ GARCIA #\n");
    printf("     #    ES PARA DOOM II RPG (BREW)   #\n");
    printf("     #          VERSION 1.0            #\n");
    printf("     #          MODO DE USO:           #\n");
    printf("     #   LEER EL LEEME.TXT/README.TXT  #\n");
    printf("     ###################################\n");
    printf("\n");
}

void ExtraerDatos()
{
    /*hz = OpenZip(("DOOM_II_RPG_1.0.ipa"),0);
    if(hz == NULL){error("No encuentra DOOM_II_RPG_1.0.ipa");}
    SetUnzipBaseDir(hz,("Datos"));
    ZIPENTRY ze; GetZipItem(hz,-1,&ze); int numitems=ze.index;
    
    int i;
    FindZipItem(hz,("Payload/Doom2rpg.app/Packages/newMappings.bin"),true,&i,&ze);
    UnzipItem(hz,i,ze.name+30);
    FindZipItem(hz,("Payload/Doom2rpg.app/Packages/newPalettes.bin"),true,&i,&ze);
    UnzipItem(hz,i,ze.name+30);
    FindZipItem(hz,("Payload/Doom2rpg.app/Packages/tables.bin"),true,&i,&ze);
    UnzipItem(hz,i,ze.name+30);
    
    for(int j = 0; j <= 38; j++)
    {
        PrintfPorcentaje(j,38-1,true, 10,"Extrayendo Datos......");
        sprintf(string,"Payload/Doom2rpg.app/Packages/newTexels%3.3d.bin",j);
        FindZipItem(hz,string,true,&i,&ze);
        UnzipItem(hz,i,ze.name+30);
    }
    
    CloseZip(hz);*/
}

int main(int argc, char *argv[])
{
    ShowInfo();

    FILE *f1, *f2;
    
    f1 = fopen("Datos/newMappings.bin","rb");
    if(!f1)
    {
     ExtraerDatos();
    }
    fclose(f1);

    f1 = fopen("Datos/newMappings.bin","rb");
    if(!f1)
    {
     error("No puede abrir newMappings.bin");
    }
    
    hz = CreateZip("DoomIIRpgBrew.pk3",0);
 
    int i = 0;
    
    for(i = 0; i < 512; i++)
    {
        Unk01[i] = ReadSword(f1);
    }
    for(i = 0; i < 1024; i++)
    {
        Unk02[i] = ReadByte(f1);
    }
    for(i = 0; i < 4096; i++)
    {
        Sizes[i] = ReadByte(f1);
    }
    for(i = 0; i < 1024; i++)
    {
        Pals[i] = ReadSword(f1);
    }
    for(i = 0; i < 1024; i++)
    {
        Tex[i] = ReadSword(f1);
    }
    
    fclose(f1);
    
    for(i = 0; i < 512; i++)
    {
      if(Unk01[i] != -1)
      {
       if(Unk01[i+1] == -1) continue;
       initflags(i);
      }
    }
    
    inittex();

    //system("CLS");
    for(i = 0; i < 512; i++)
    {
      PrintfPorcentaje(i,512-1,true, 11,"Extrayendo Sprites Y Texturas......");
      //printf("i %d\n",i);
      if(Unk01[i] != -1)
      {
       if(Unk01[i+1] == -1) continue;
       //printf("\ni %4.4X\n",i);
       
       int i1 = Unk01[i];
       int paramInt = Unk01[(i + 1)];
       
       while (i1 < paramInt)
       {
         extraer(i1);
         //getch();
         i1++;
       }
      }
    }

    ReadTablesOffset();
    ExtraerSKYS(17, 0);
    ExtraerSKYS(19, 1);

    //-----------------------//
    int cmid_name;
    int file_size;
    int header_size;
    int offset;
    int trac_name;
    int buffer_size;
    char name[256];

    for(int k = 0; k < 145; k++)
    {
        byte *buffer;
        
        PrintfPorcentaje(k, (145)-1,true, 12,"Extrayendo Sonidos.......");
        
        if(k == 65 || k == 67 || k == 68 || k == 69 || k == 70 || k == 71)//MIDI FILES
        {
             Printf(true, 13, "%s\t\t\t ", names[k]);

             if(k == 65) {buffer = menu_scroll; file_size = 55;}
             if(k == 67) {buffer = Music_Boss; file_size = 4529;}
             if(k == 68) {buffer = Music_General; file_size = 7200;}
             if(k == 69) {buffer = Music_Levelup; file_size = 558;}
             if(k == 70) {buffer = Music_Level_End; file_size = 7824;}
             if(k == 71) {buffer = Music_Title; file_size = 8677;}
             
             sprintf(name,"SOUND/%s.mid", names[k]);
             ZipAdd(hz, name, buffer, file_size);
             
             continue;
        }
            
        sprintf(name,"Datos/%s.pmd",names[k]);
        Printf(true, 13, "%s\t\t\t ", names[k]);
        //printf("%s\n", name);
        f1 = fopen(name,"rb");
        if(!f1)
            error("%s no found", name);
        
        //printf("cmid %d\n", cmid);
        
        cmid_name = ReadUint(f1);
        if(cmid_name != 0x64696D63)//cmid
           error("No es un archivo (.pmd)\n");
           
        file_size = Swap32(ReadUint(f1));
        //printf("file_size %d\n", file_size);
        
        header_size = Swap16(ReadWord(f1));
        //printf("header_size %d\n", header_size);
        
        offset = ftell(f1)+header_size;
        //printf("offset %d\n", offset);
        
        //Skip init definitions
        fseek(f1, offset, SEEK_SET);
    
        trac_name = ReadUint(f1);
        if(trac_name != 0x63617274)//trac
           error("No conside el nombre [trac] offset %d\n", ftell(f1)-4);
           
        buffer_size = Swap32(ReadUint(f1));
        //printf("buffer_size %d\n", buffer_size);
        
        //aling 2
        ReadByte(f1); //unk pad
        /*offset = ftell(f1);
        offset += (unsigned int)offset & 1;
        fseek(f1, offset, SEEK_SET);
        printf("offset %d\n", offset);*/
        
        // Set buffer malloc
        buffer = (byte *)malloc(buffer_size);
        
        //copy data to buffer
        int cnt = 0;
        int data_size = 0;
        int data_offset = 0;
        while(cnt < buffer_size-1)
        {
           int code = ReadWord(f1);
           //printf("code %X, cnt %d\n", code, cnt);
           cnt += 2; 
           
           switch (code)
           {
              case 0xC3FF://unk
                   ReadWord(f1); cnt += 2; 
                   break;
              case 0xDEFF://unk
                   ReadWord(f1); cnt += 2; 
                   break;
              case 0xDFFF://unk
                   ReadByte(f1); cnt += 1; //unk
                   break;
              case 0xE8FF://unk
                   ReadWord(f1); cnt += 2; 
                   break;
              default:
                   error("code desconocido [%x] offset [%d]\n", code, ftell(f1)-2);
                   break;
              case 0xF1FF://block datasize
                   data_size = Swap16(ReadWord(f1))-7;  cnt += 2; 
                   //printf("data_size %d\n", data_size);
                   
                   int type = Swap16(ReadWord(f1));  cnt += 2; 
                   if(type != 0x44)
                        error("formato de tipo desconocido [%x] offset [%d]\n", type, ftell(f1)-2);
                        
                   int size = Swap32(ReadUint(f1));  cnt += 4; 
                   //printf("size %d\n", size);
                   
                   ReadByte(f1); cnt += 1; //unk
                   
                   for(int i = 0; i < data_size; i++)
                   {
                        buffer[data_offset] = ReadByte(f1);
                        cnt += 1;
                        data_offset++;
                   }
                   
                   ReadByte(f1); cnt += 1; //unk
                   
                   //printf("offset %d\n", ftell(f1));
                   //getch();
                   break;
              
           }
           
           //getch();
        }
        fclose(f1);
        
        //Write All QCP data
        f2 = fopen("PureVoice/tmp.qcp","wb");
        int RIFF = 0x46464952;
        int f_size = data_offset+186;
        fwrite (&RIFF, sizeof(uint), 1, f2);
        fwrite (&f_size, sizeof(uint), 1, f2);//file size
        fwrite (&QCPDATA, sizeof(QCPDATA), 1, f2);
        
        int data = 0x61746164;
        int b_size = data_offset/0x23;
        fwrite (&b_size, sizeof(uint), 1, f2);//block_data size
        fwrite (&data, sizeof(uint), 1, f2);
        fwrite (&data_offset, sizeof(uint), 1, f2);//data size
    
        for(int i = 0; i < data_offset; i++)
        {
           fputc(buffer[i], f2);
        }
        fclose(f2);
        
        free(buffer);
        
        //Convertir qcp a wav con PureVoice tool
        
        SHELLEXECUTEINFO ShExecInfo = {0};
        ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
        ShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
        ShExecInfo.hwnd = NULL;
        ShExecInfo.lpVerb = NULL;
        ShExecInfo.lpFile = "QCP2WAV.bat";		
        ShExecInfo.lpParameters = "";	
        ShExecInfo.lpDirectory = "PureVoice";
        ShExecInfo.nShow = SW_HIDE;
        ShExecInfo.hInstApp = NULL;	
        ShellExecuteEx(&ShExecInfo);
        WaitForSingleObject(ShExecInfo.hProcess,INFINITE);
        
        //Read Wav file
        f2 = fopen("PureVoice/tmp.wav","rb");
        
        fseek(f2, 0, SEEK_END);
        file_size = ftell(f2);
        fseek(f2, 0, SEEK_SET);
        
        // Set buffer malloc
        buffer = (byte *)malloc(file_size);
        
        for(int i = 0; i < file_size; i++)
        {
           buffer[i] = ReadByte(f2);
        }
        
        sprintf(name,"SOUND/%s.wav", names[k]);
        ZipAdd(hz, name, buffer, file_size);
        
        fclose(f2);
        free(buffer);
    }
    
    CloseZip(hz);
    system("PAUSE");
    return EXIT_SUCCESS;
}
