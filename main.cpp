/*
    Developed by Regson Jaques
    https://www.youtube.com/user/tictacKode/playlists   Canal no You Tube
    https://github.com/tictackode                       GitHub
*/

#include <allegro.h>
#include "classe7.h"

int main()
{
    init();

    set_window_title("TictacKode - Projeto Mode 7 #5");

    loadAll();

    init_desenha7(sprite,sprite2);

    timerStuff();
    cronometroInit();
    init_desenha7(spriteAux,spriteAux2);

    openingLogo();
    highcolor_fade_out(8);

    mode7_buffer_only();
    highcolor_fade_in(buffer,8);

    tics=0;
    while (!key[KEY_ESC])
    {

        controle();
        cronometroAux();
        if(tics>1) {  mode7(); tics=0; }
    }

    liberaMemoria();
    deinit();
    return 0;
}

END_OF_MAIN()
