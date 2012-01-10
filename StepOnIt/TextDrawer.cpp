#include "TextDrawer.h"

void TextDrawer::Init()
{
	letters=new Coords[512];
	int f=0;
	int X,Y;X=Y=0;
	string chars="abcdefghijklmnopqrst\nuvwxyzABCDEFGHIJKLMN\nOPQRSTUVWXYZ12345678\n90`-=[]\\;',./~!@#$%^\n&*()_+{}|:\"<>? ";
	chars[chars.length()-1]=3;
	for (unsigned int i=0;i<chars.length();i++){
		char c=chars[i];
		if (c=='\n'){
			X=0;
			Y++;
			continue;
		}
		//Add letter
		//25,40;
		letters[c].sx=X*24.0/512.0;
		letters[c].sy=Y*51.00/512.0;
		letters[c].ex=(X+1)*24.0/512.0;
		letters[c].ey=letters[c].sy+40.0/512.0;
		X++;
	}
}
void TextDrawer::LoadTexture(string path){
	SDL_Surface *temp=IMG_Load(path.c_str());
	
	glGenTextures(1,&texture);
	glBindTexture(GL_TEXTURE_2D,texture);

	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_NEAREST );
	gluBuild2DMipmaps(GL_TEXTURE_2D, 4,temp->w,temp->h, GL_RGBA,GL_UNSIGNED_BYTE, temp->pixels);
}
void TextDrawer::Draw(int x,int y,int size,double r,double g,double b,double a,char *text, ...)
{
	va_list v;
	va_start(v,text);
	char towrite[201]={0};
	vsprintf(towrite,text,v);
	int l=strlen(towrite);
	int X,Y;X=x;Y=y;
	int dx,dy;
	dx=int(26.0*size/24.0);
	dy=int(40*size/24.0);
	for (int i=0;i<l;i++){
		if (towrite[i]==' '){
			X+=dx;
			continue;
		}
		if (towrite[i]=='\n'){
			X=x;
			//24 -> 25
			//24 -> 40
			Y+=dy;
			continue;
		}
		glColor4d(r,g,b,a);
		glBindTexture(GL_TEXTURE_2D,texture);
		glBegin(GL_QUADS);
			glTexCoord2d(letters[towrite[i]].sx,letters[towrite[i]].sy);
				glVertex2i(X,Y);
			glTexCoord2d(letters[towrite[i]].sx,letters[towrite[i]].ey);
				glVertex2i(X,Y+dy);
			glTexCoord2d(letters[towrite[i]].ex,letters[towrite[i]].ey);
				glVertex2i(X+dx,Y+dy);
			glTexCoord2d(letters[towrite[i]].ex,letters[towrite[i]].sy);
				glVertex2i(X+dx,Y);
		glEnd();
		X+=dx;
	}
}

TextDrawer::Coords* TextDrawer::letters=NULL;
unsigned int TextDrawer::texture=0;


