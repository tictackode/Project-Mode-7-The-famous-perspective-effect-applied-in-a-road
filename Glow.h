
#include <allegro.h>

class Glow
{
public:
    int fontaux;
    bool desceCor;
    int coloraux;

    Glow()
    {

        this->desceCor=false;
        this->coloraux=0;

    }
    void reset()
    {
        this->fontaux=0;
        this->desceCor=false;
        this->coloraux=0;
    }

     void glow()
    {
         if((this->fontaux<245)&&(this->desceCor==false)) { this->fontaux+=6;  this->coloraux-=6; }
         else { this->desceCor=true;  this->fontaux-=4; this->coloraux+=6;}

        if((this->desceCor==true)&&(this->fontaux>128)) { this->fontaux-=6; this->coloraux+=6; }
        else { this->desceCor=false; this->fontaux+=4; this->coloraux-=6; }


    }
    void glow2()
    {
        // usada na abertura
         if((this->fontaux<254)&&(this->desceCor==false)) { this->fontaux++;  this->coloraux-=6; }
         else { this->desceCor=true;  this->fontaux--; this->coloraux+=6;}

        if((this->desceCor==true)&&(this->fontaux>1)) { this->fontaux--; this->coloraux+=6; }
        else { this->desceCor=false; this->fontaux++; this->coloraux-=6; }

    }

    void fontShading()
    {
        if((fontaux<245)&&(desceCor==false)) { fontaux+=6;  coloraux-=6; }
        else { desceCor=true;  fontaux-=4; coloraux+=6;}

        if((desceCor==true)&&(fontaux>128)) { fontaux-=6; coloraux+=6; }
        else { desceCor=false; fontaux+=4; coloraux-=6; }


    }
    void fontShading2()
    {
        // usada na abertura
        if((fontaux<254)&&(desceCor==false)) { fontaux++;  coloraux-=6; }
        else { desceCor=true;  fontaux--; coloraux+=6;}

        if((desceCor==true)&&(fontaux>1)) { fontaux--; coloraux+=6; }
        else { desceCor=false; fontaux++; coloraux-=6; }

    }

};
