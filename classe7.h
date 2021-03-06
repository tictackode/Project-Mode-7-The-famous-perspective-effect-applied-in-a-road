/*
    Developed by Regson Jaques
    https://www.youtube.com/user/tictacKode/playlists
    https://github.com/tictackode
*/

#include <string>
#include <allegro.h>
#include "Glow.h"

//Char Arrays para ser usados como pista
char pistaConst[266]=("0000bbbb0000bbbb0000bbbb0000bbbb0000bbbb0000bbbb0000bbbb0000bbbb0000bbbb0000bbbb0000bbbb0000bbbb0000bbbb0000bbbb0000bbbb0000bbbb0000bbbb0000bbbb0000bbbb0000bbbb0000bbbb0000bbbb0000bbbb0000bbbb0000bbbb0000bbbb0000bbbb0000bbbb0000bbbb0000bbbb0000bbbb0000bbbb");
char pista2[258]=("0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b");
char star[258]=("sssbsss0sssbsss0sssbsss0sssbsss0sssbsss0sssbsss0sssbsss0sssbsss0sssbsss0sssbsss0sssbsss0sssbsss0sssbsss0sssbsss0sssbsss0sssbsss0sssbsss0sssbsss0sssbsss0sssbsss0sssbsss0sssbsss0sssbsss0sssbsss0sssbsss0sssbsss0sssbsss0sssbsss0sssbsss0sssbsss0sssbsss0sssbsss");
char pista[255]=("000000bbbbbbbb00000000bbbbbbbb00000000bbbbbbbb00000000bbbbbbbb00000000bbbbbbbb00000000bbbbbbbb00000000bbbbbbbb00000000bbbbbbbb00000000bbbbbbbb00000000bbbbbbbb00000000bbbbbtbb00000000bbbbbbbb00000000bbbbbbbb00000000bbbbbbbb00000000bbbbbbbb00000000bbbbbbbb");

    //declaração das Fontes
    FONT* fonte;
    FONT* fixed12;
    FONT* system36;

    //declaração das imagens (BITMAP*)
    BITMAP* buffer;
    BITMAP* buffer2;
    BITMAP* sprite;
    BITMAP* sprite2;
    BITMAP* water;
    BITMAP* water2;
    BITMAP* sand;
    BITMAP* sand2;
    BITMAP* stars1;
    BITMAP* stars2;
    BITMAP* spriteAux;
    BITMAP* spriteAux2;
    BITMAP* tictac;
    BITMAP* rock1;
    BITMAP* rock2;
    //BITMAP* bigLogo;
    BITMAP* opening_image;
    BITMAP* recharge1;
    BITMAP* recharge2;
    BITMAP* terreno1;
    BITMAP* terreno2;
    BITMAP* grass1;
    BITMAP* grass2;

    //declaração de variáveis auxiliares
    int local=0;

    volatile int tics=0;
    int bufferX;
    float total;
    float zoom;
    int h;
    int fontaux;
    bool desceCor;
    int velocidade;
    int ZL,ZR;
    float iniX, iniY;
    char texturas[5][10];
    int texturaAux;
    int scanlines;
    int loop;
    int localAux=0;
    struct cronometro   {   int ms,sec,minutos;   }c;
    float pan;
    float k;
    float i;
    float i_global=0;
    float k_global=0;
    float spriteHeight;
    float supercam;
    float curva=0;
    Glow gl;

inline void init()
{
    allegro_init();
    set_color_depth(32);
    set_gfx_mode(GFX_AUTODETECT_WINDOWED, 800, 600, 0, 0);

    install_timer();
    install_keyboard();
    install_mouse();
}

inline void deinit()
{
    clear_keybuf();
    allegro_exit();
}

void liberaMemoria()
{
    destroy_bitmap(buffer);
    destroy_bitmap(buffer2);
    destroy_bitmap(sprite);
    destroy_bitmap(sprite2);
    destroy_bitmap(water);
    destroy_bitmap(water2);
    destroy_bitmap(sand);
    destroy_bitmap(sand2);
    destroy_bitmap(stars1);
    destroy_bitmap(stars2);
    destroy_bitmap(spriteAux);
    destroy_bitmap(spriteAux2);
    destroy_bitmap(tictac);
    destroy_bitmap(rock1);
    destroy_bitmap(rock2);
    //destroy_bitmap(bigLogo);
    destroy_bitmap(recharge1);
    destroy_bitmap(recharge2);
    destroy_bitmap(terreno1);
    destroy_bitmap(terreno2);
    destroy_bitmap(grass1);
    destroy_bitmap(grass2);
    destroy_bitmap(opening_image);
    //desalocando as fontes da memória
    destroy_font(fonte);
    destroy_font(fixed12);
    destroy_font(system36);

}

//definição de funcões
BITMAP* loadImage(BITMAP* image,int img_width,int img_height,const char* image_path)
{

        image=create_bitmap(img_width,img_height);
        image=load_bitmap(image_path,0);
        std::string buf("error: couldn't find image ESC to exit : ");
        buf.append(image_path);

        if(!image)
        {
            key[KEY_ESC]=false;
            //Função que desenha um fundo em degrade cinza
            for (int i = 0; i <= 64; i++)
            {
                rectfill(screen, 0, i * 10, 640, (i * 10) + 10, makecol(32 + i, 32 + i, 32 + i));
            }
            while(!key[KEY_ESC])
            {
                textprintf_ex(screen, font, 20, 20, makecol(255, 0, 0),-1,buf.c_str());
            }

            readkey(); liberaMemoria(); deinit(); exit(1);
        }

    return image;
}

void highcolor_fade_out(int speed)
{
    BITMAP *bmp_orig, *bmp_buff;

    if ((bmp_orig = create_bitmap(SCREEN_W, SCREEN_H)))
    {
        if ((bmp_buff = create_bitmap(SCREEN_W, SCREEN_H)))
        {
            int a;
            blit(screen, bmp_orig, 0,0, 0,0, SCREEN_W, SCREEN_H);
            if (speed <= 0) speed = 16;

            for (a = 255-speed; a > 0; a-=speed)
            {
                clear(bmp_buff);
                set_trans_blender(0,0,0,a);
                draw_trans_sprite(bmp_buff, bmp_orig, 0, 0);
                vsync();
                blit(bmp_buff, screen, 0,0, 0,0, SCREEN_W, SCREEN_H);
            }
            destroy_bitmap(bmp_buff);
        }
        destroy_bitmap(bmp_orig);
    }

    rectfill(screen, 0,0, SCREEN_W,SCREEN_H, makecol(0,0,0));
}
void highcolor_fade_in(BITMAP *bmp_orig, int speed)
{
   BITMAP *bmp_buff;

    if ((bmp_buff = create_bitmap(SCREEN_W, SCREEN_H)))
    {
        int a;
        if (speed <= 0) speed = 16;

        for (a = 0; a < 256; a+=speed)
        {
            clear(bmp_buff);
            set_trans_blender(0,0,0,a);
            draw_trans_sprite(bmp_buff, bmp_orig, 0, 0);
            vsync();
            blit(bmp_buff, screen, 0,0, 0,0, SCREEN_W, SCREEN_H);
        }
        destroy_bitmap(bmp_buff);
    }

    blit(bmp_orig, screen, 0,0, 0,0, SCREEN_W, SCREEN_H);
}
void balaoFala()
{
        rectfill(buffer, 10,10,90,90,makecol(gl.fontaux,gl.fontaux,255));
        draw_sprite(buffer,tictac,10,10);

        /* char fala1[38]=("Vamos ver se essa lata velha anda!!!");
         for(int i=0;fala[i]!='\0';i++)
         {

            textout_ex(buffer, fonte,fala[i], 180+(i*10), 30,makecol(0, 0, 0), -1);
         }*/

        textout_ex(buffer, fonte, "  Projeto Mode 7: Video #5 ", 110, 15, makecol(gl.fontaux,gl.fontaux,255) , -1);
}
void desenhaCeu()
{
        for(int y=0; y<=800; y+=4)
        {
            rectfill(buffer, 0,y,800,y+10, makecol(24+y/4,24+y/4,255));
        }
        balaoFala();


            rectfill(buffer, 0,300,800,600, makecol(0,0,0));


}

void infoControls()
{
         //textout_ex(buffer, fixed12, "DIRECTION: KEYS LEFT - RIGHT", 10, 100,makecol(gl.fontaux,gl.fontaux,255) , -1);
         textout_ex(buffer, fixed12, "CAMERA:   PAD  8-5, 4-6 ",10, 110,makecol(gl.fontaux,gl.fontaux,255) , -1);
         textout_ex(buffer, fixed12, "SPACEBAR: ", 10, 120,makecol(gl.fontaux,gl.fontaux,255) , -1);
         textout_ex(buffer, fixed12, "CONTROLS:  W-S , Arrow keys", 10, 130,makecol(gl.fontaux,gl.fontaux,255) , -1);
         textprintf_ex(buffer, fixed12,10,140,makecol(gl.fontaux,gl.fontaux,255),-1,"ZL: %d",ZL);
         textprintf_ex(buffer, fixed12,10,150,makecol(gl.fontaux,gl.fontaux,255),-1,"ZR: %d",ZR);
         textprintf_ex(buffer, fixed12,10,160,makecol(gl.fontaux,gl.fontaux,255),-1,"TEXTURE (PAD:1,0,*,END): %s", texturas[texturaAux] );
        // textprintf_ex(buffer, fixed12,10,190,makecol(gl.fontaux,gl.fontaux,255),-1,"%d:",c.minutos);
        // textprintf_ex(buffer, fixed12,50,190,makecol(gl.fontaux,gl.fontaux,255),-1,"%d':",c.sec);
        // textprintf_ex(buffer, fixed12,100,190,makecol(gl.fontaux,gl.fontaux,255),-1,"%d\"" ,c.ms);
}

void init_desenha7(BITMAP* sprite_param,BITMAP* sprite_param2)
{
        //inicializa as variáveis
        gl.reset();
        strcpy(texturas[0],"ROAD");
        strcpy(texturas[1],"WATER");
        strcpy(texturas[2],"SAND");
        strcpy(texturas[3],"ROCK");
        strcpy(texturas[4],"STARS");

        spriteAux=sprite_param;
        spriteAux2=sprite_param2;
        total=1;
        bufferX=0;
        zoom=3;
        i=1;
        fontaux=0;
        desceCor=false;
        fontaux=0;
        local=0;
        velocidade=1;
        ZL=6;
        ZR=8;
        k=1;
        iniX=90;
        iniY=300;
        texturaAux=0;
        scanlines=50;
        loop=256;
        localAux=256;
        pan=2;
        spriteHeight=13;
        supercam=1;
        h=0;

}
    void desenha7(BITMAP* sprite_param,BITMAP* sprite_param2)
    {
        spriteAux=sprite_param;
        spriteAux2=sprite_param2;
    }
    void loadAll()
    {
        //carregando fontes
        fonte=load_font("fonts\\cordia48.pcx",NULL,NULL);
        system36=load_font("fonts\\system36.pcx",NULL,NULL);
        fixed12=load_font("fonts\\fixed12.pcx",NULL,NULL);

        //carregando imagens
        buffer=create_bitmap(800,600);
        buffer2=create_bitmap(800,600);
        sprite=loadImage(sprite,200,10,"sprites\\sprite1.bmp");
        sprite2=loadImage(sprite2,200,10,"sprites\\sprite2.bmp");
        stars1=loadImage(stars1,200 ,10 ,"sprites\\stars1.bmp");
        stars2=loadImage(stars2,200 ,10 ,"sprites\\stars2.bmp");
        water=loadImage(water,240 ,40 ,"sprites\\water1.bmp");
        water2=loadImage(water2,240 ,40 ,"sprites\\water2.bmp");
        rock1=loadImage(rock1,200,10,"sprites\\rock1.bmp");
        rock2=loadImage(rock2,200,10,"sprites\\rock2.bmp");
        sand=loadImage(sand,200,10,"sprites\\sand.bmp");
        sand2=loadImage(sand2,200,10,"sprites\\sand2.bmp");
        terreno1=loadImage(terreno1, 800,10 ,"sprites\\terreno1.bmp");
        terreno2=loadImage(terreno2, 800,10 ,"sprites\\terreno2.bmp");
        grass1=loadImage(grass1, 800,10 ,"sprites\\grass1.bmp");
        grass2=loadImage(grass2, 800,10 ,"sprites\\grass2.bmp");

        tictac=loadImage(tictac,80,80 ,"sprites\\tictactrans_small.bmp");
        opening_image=loadImage(opening_image,800,600 ,"sprites\\opening_image.bmp");

        recharge1=create_bitmap_ex(32, 100, 10);
        recharge2=create_bitmap_ex(32, 100, 10);

    }
    void Background()
    {
        for(int i=0;i<=800;i++)
        {
            rectfill(buffer,0,i*10,800,(i*10)+10,makecol(255,32+i,32+i));
        }
    }
    int zoomAux(int muda)
    {
        switch (muda)
        {

            case 0:     total=((k+i)*pan);   break; //lado direito bem no cantinho
            case 1:     total=400+(k*pan);   break;
            case 2:     total=200+((k*i));   break;
            case 3:     total=((300-k));      break;
            case 4:     total=(300-(k));   break;
            case 5:     total=((300-k));   break;
            case 6:     total=((300-k));   break; //pista gira pra esquerda e move a origem pra esquerda
            case 7:     total= 300-k;      break; //pista gira pra esquerda e nao movimenta a origem case 8:     total=300-(k*2);         break;  // pista para a direita , os controles afundam e levantam um pouco a pista
            case 8:     total=(k*pan);     break;
            case 9:     total=(((k-(i))*pan));      break;
            case 10:    total=(((k+(i))*pan));      break;
            case 11:    total=(((k-(i*2))*pan));    break;
            case 12:    total=(((k+(i*2))*pan));    break;
            case 13:    total=(((k+(i/2))*pan));    break;

        }

        return total;

    }
    int leftOrRight(int aux)
    {
        // ver se essa funcao e realmente necessaria
        int retorno=1;
        if(aux==1) { retorno=  320-k*i;  }
        if(aux==2) { retorno=  320-k;  }
        if(aux==3) { retorno=  320-k*2;  }
        if(aux==4) { retorno=  320+k*2;  }
        return retorno;
    }

    void controle()
    {
        if (key[KEY_ESC]) { liberaMemoria(); deinit(); exit(0);         }

        //camera lateral
        if (key[KEY_4_PAD])  {   pan-=0.02;   key[KEY_4_PAD]=false;  }
        if (key[KEY_6_PAD])  {   pan+=0.02;   key[KEY_6_PAD]=false;  }

        //
        if (key[KEY_C])  {   iniX-=0.02;   key[KEY_C]=false;  }
        if (key[KEY_V])  {   iniX+=0.02;   key[KEY_V]=false;  }

        // controle da aceleração
        if (key[KEY_UP])    {   i_global-=0.05;    key[KEY_UP]=false;  }
        if (key[KEY_DOWN])  {   i_global+=0.05;    key[KEY_DOWN]=false;}

        if (key[KEY_B])    {    k_global-=0.02;    key[KEY_B]=false;     }
        if (key[KEY_N])    {    k_global+=0.02;    key[KEY_N]=false;     }

        if (key[KEY_Y])   {     total+=0.1;        key[KEY_Y]=false;    }
        if (key[KEY_H])   {     total-=0.1;        key[KEY_H]=false;    }

        if (key[KEY_Z])   {      curva+=0.5;   key[KEY_Z]=false;    }
        if (key[KEY_X])   {      curva-=0.5;   key[KEY_X]=false;    }

        if (key[KEY_Q])   {   if(ZL<13)     ZL++;   key[KEY_Q]=false;   }
        if (key[KEY_A])   {   if(ZL>0)      ZL--;   key[KEY_A]=false;   }

        if (key[KEY_W])   {   if(ZR<13)     ZR++;   key[KEY_W]=false;   }
        if (key[KEY_S])   {   if(ZR>0)      ZR--;   key[KEY_S]=false;   }

        if (key[KEY_UP])   {   if(iniY<599)  iniY--;     }
        if (key[KEY_DOWN]) {   if(iniY>1)    iniY++;     }

        if (key[KEY_LEFT])  {   if(iniX>-400) iniX-=2;    }
        if (key[KEY_RIGHT]) {   if(iniX<798)  iniX+=2;    }

        if (key[KEY_R])   {       supercam+=0.1;   key[KEY_R]=false; }
        if (key[KEY_F])   {       supercam-=0.1;   key[KEY_F]=false; }

        //esse controle nao deu muito certo
        if (key[KEY_ALTGR])  { /*if(spriteHeight>0)*/  { spriteHeight-=0.1;   key[KEY_ALTGR]=false;  } }
        if (key[KEY_ALT])    { /*if(spriteHeight<36)*/ { spriteHeight+=0.1;   key[KEY_ALT]=false;    } }

        if (key[KEY_7_PAD])   {   /*if(k>1) */     k-=0.1;  key[KEY_7_PAD]=false;      }
        if (key[KEY_9_PAD])   {  /* if(k<100) */   k+=0.1;  key[KEY_9_PAD]=false;      }

        if (key[KEY_SPACE]) {      init_desenha7(spriteAux,spriteAux2);        }    // reinicia pista
        if (key[KEY_I])     {      if(localAux<255)       {      localAux++;       key[KEY_I]=false;   }   }
        if (key[KEY_K])     {      if(localAux>242)       {      localAux--;       key[KEY_K]=false;   }   }

        if (key[KEY_U])     {      if(localAux<255)       {      localAux++;       key[KEY_U]=false;   }   }
        if (key[KEY_J])     {      if(localAux>242)       {      localAux--;       key[KEY_J]=false;   }   }

        if (key[KEY_Y])   {     { total+=0.8;   key[KEY_Y]=false;   } }
        if (key[KEY_H])   {     { total-=0.8;   key[KEY_H]=false;   } }

        if (key[KEY_8_PAD])
        {
            zoom-=0.04; key[KEY_8_PAD]=false;
            //clear_bitmap(buffer);
        }
        if (key[KEY_5_PAD])
        {
            zoom+=0.04; key[KEY_5_PAD]=false;
            //clear_bitmap(buffer);
        }
        if (key[KEY_1_PAD])
        {
            // correto
            desenha7(water,water2);

            texturaAux=1;
            clear_bitmap(buffer);

        }
        if (key[KEY_0_PAD])
        {
            //correto
            desenha7(sprite,sprite2);

            texturaAux=0;
            clear_bitmap(buffer);

        }
        if (key[KEY_3_PAD])
        {
            //correto
            desenha7(stars1,stars2);

            texturaAux=4;
            clear_bitmap(buffer);

        }
        if (key[KEY_ASTERISK])
        {
            //correto
            desenha7(sand2,sand);

            texturaAux=2;
            clear_bitmap(buffer);

        }
        if (key[KEY_END])
        {
            //correto
            desenha7(rock1,rock2);
            texturaAux=3;
            clear_bitmap(buffer);
        }



       rest(0);
    } //end controle()

    void mode7() // essa é a função que desenha a pista
    {

        desenhaCeu();
        infoControls();
        i=i_global;
        k=0;

     while(i<loop)
     {
            //clear_to_color(recharge1,makecol(fontaux,0,0));
            //clear_to_color(recharge2,makecol(fontaux,32,32));
            k+=((i/6));

            if(pista[local]=='0')
            {
                //void stretch_blit(BITMAP *source, BITMAP *dest, int source_x, source_y, source_width, source_height, int dest_x, dest_y, dest_width, dest_height);
                //rect(BITMAP *bmp, int x1, int y1, int x2, int y2, int color)
               // stretch_blit(grass1,buffer,0,0,800,10, 0  , (iniY+k/zoom)+pan  ,  800 +zoomAux(ZR)+pan ,  zoomAux(spriteHeight));
                //stretch_blit(grass1,buffer,0,0,800,10, 0  , (iniY+k/zoom)+pan  ,  800 +zoomAux(ZR)+pan ,  zoomAux(spriteHeight));
                stretch_blit(spriteAux,buffer,0,0,200,10,  iniX+zoomAux(ZL)  , iniY+k/zoom  ,  50+zoomAux(ZR)+pan  ,  zoomAux(spriteHeight));
                //stretch_blit(recharge1,buffer,0,0,200,10,  iniX+zoomAux(ZL)  , iniY+k/zoom  ,  50+zoomAux(ZR)  ,  zoomAux(spriteHeight));
            }
            else if(pista[local]=='b')
            {
                //stretch_blit(grass1,buffer,0,0,800,10, 0  , (iniY+k/zoom)+pan  ,  800 +zoomAux(ZR)+pan ,  zoomAux(spriteHeight));
                //stretch_blit(grass2,buffer,0,0,800,10,  0  , (iniY+k/zoom)+pan  ,  800 +zoomAux(ZR)+pan ,  zoomAux(spriteHeight));
                stretch_blit(spriteAux2,buffer,0,0,200,10,  iniX+zoomAux(ZL)  , iniY+k/zoom  ,  50+zoomAux(ZR)+pan  ,  zoomAux(spriteHeight));
                //rectfill( buffer, iniX+zoomAux(ZL) , iniY+k/zoom, 50+zoomAux(ZL) ,zoomAux(ZR),makecol(255,fontaux,fontaux) );
                //stretch_blit(recharge2,buffer,0,0,200,10,  iniX+zoomAux(ZL)  , iniY+k/zoom  ,  50+zoomAux(ZR)  ,  zoomAux(spriteHeight));
            }

            local++;
            if (local>localAux)
            {
                local=0;
            }

            i++;


    } //while

    gl.glow();

    //void blit(BITMAP *source, BITMAP *dest, int source_x, int source_y, int dest_x, int dest_y, int width, int height);
    blit(buffer,screen,0,0,0,0,800,600);
    clear_bitmap(buffer);

}// fim mode7()
void mode7_buffer_only()
{

        desenhaCeu();
        infoControls();
        i=0;
        k=0;

     while(i<loop)
     {
            //clear_to_color(recharge1,makecol(fontaux,0,0));
            //clear_to_color(recharge2,makecol(fontaux,32,32));
            k+=((i/6)+supercam);

            if(pista[local]=='0')
            {
                //void stretch_blit(BITMAP *source, BITMAP *dest, int source_x, source_y, source_width, source_height, int dest_x, dest_y, dest_width, dest_height);
                //rect(BITMAP *bmp, int x1, int y1, int x2, int y2, int color)
                //stretch_blit(terreno1,buffer,0,0,200,10, 0  , iniY+k/zoom  ,  800  ,  zoomAux(spriteHeight));
                stretch_blit(spriteAux,buffer,0,0,200,10,  iniX+zoomAux(ZL)  , iniY+k/zoom  , 50+zoomAux(ZR)+pan  ,  zoomAux(spriteHeight));
                //stretch_blit(recharge1,buffer,0,0,200,10,  iniX+zoomAux(ZL)  , iniY+k/zoom  ,  50+zoomAux(ZR)  ,  zoomAux(spriteHeight));
            }
            else if(pista[local]=='b')
            {
                //stretch_blit(terreno2,buffer,0,0,200,10,  0  , iniY+k/zoom  ,  800  ,  zoomAux(spriteHeight));
                stretch_blit(spriteAux2,buffer,0,0,200,10,  iniX+zoomAux(ZL)  , iniY+k/zoom  ,  50+zoomAux(ZR)+pan ,  zoomAux(spriteHeight));
                //rectfill( buffer, iniX+zoomAux(ZL) , iniY+k/zoom, 50+zoomAux(ZL) ,zoomAux(ZR),makecol(255,fontaux,fontaux) );
                //stretch_blit(recharge2,buffer,0,0,200,10,  iniX+zoomAux(ZL)  , iniY+k/zoom  ,  50+zoomAux(ZR)  ,  zoomAux(spriteHeight));
            }

            local++;
            if (local>localAux)
            {
                local=0;
            }

            i++;

    } //while

}// fim mode7()

    void cronometroInit()
    {
        tics=0;
        c.ms=0;
        c.sec=0;
        c.minutos=0;
    }
    void cronometroAux()
    {
        c.ms=tics;

        if(c.ms>=100) { c.ms=0; tics=0; c.sec++; }

        if(c.sec>=60) { c.sec=0; tics=0; c.minutos++; }

    }
void openingLogo()
{

    int cont=800;
    while(cont>1)
    {

        rectfill(buffer,0,0,800,600,makecol(255,cont,255));
        draw_sprite(buffer, opening_image, 0, 0);
        draw_sprite(screen, buffer, cont, 0);
        clear_bitmap(buffer);

        cont-=5;
        rest(4);

    }

    while(!key[KEY_SPACE])
    {
        gl.glow();
        textout_ex(screen, system36,"Press Space - Aperte espaco",20,200,makecol(0,gl.fontaux,0),-1);
        rest(2);
    }
    key[KEY_ESC]=false;

}

    void ticker()
    {
      tics++;
    }


    void timerStuff()
    {
        END_OF_FUNCTION(ticker)
        LOCK_VARIABLE(tics);
        LOCK_FUNCTION(ticker);

        //Finally we can install the timer, using either method.
        install_int(ticker,1);
        install_int_ex(ticker, BPS_TO_TIMER(60));

    }
