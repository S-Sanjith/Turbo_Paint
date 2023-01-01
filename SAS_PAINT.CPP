#include <iostream.h>
#include <stdio.h>
#include <string.h>
#include <dos.h>
#include <graphics.h>
#include <stdlib.h>
#include <conio.h>
#include <fstream.h>

short int x, y, z, x1, y1, x2, y2, b = 1, i1, j1, sd = 2, kl = 0, j, k = 0, l = 0, ip = 0, fd = -1;
int size, kgf = 1, kgf1 = 0;
int size1, size2, size3, size4, size5, size6;
char d, ch[20], oi[20];
void *buf, *bu, *buf1, *buf2, *buf3, *buf4, *buf5, *buf6;
struct rectangle {
 short unsigned int x1, x2, y1, y2, col, style;
};

struct ellipse {
 short unsigned int x, y, rx, ry, col, style;
};

union shape{
 struct rectangle obj;
 struct ellipse obj1;
}uobj;

struct pic
{
int col;
int x;
int y;
}objd;


void bmp_to_dat(char* a,int x1=0,int y1=0,int x2=getmaxx(),int y2=getmaxy())
{

 pic obj;
 for(int i=0;i<strlen(a);i++)
 {
  if(a[i]=='.')
  {
   a[i+1]='d';
   a[i+2]='a';
   a[i+3]='t';
  }
 }
 ofstream fout(a,ios::out|ios::binary);


 for(int x=x1;x<=x2;x++)
 {
  for(int y=y1;y<=y2;y++)
  {
   obj.x=x;
   obj.y=y;
   obj.col=getpixel(x,y);
   fout.write((char*)&obj,sizeof(obj));
  }
 }

 fout.close();
}

void dat(int x,int y, char *ch)
{
      pic obj1;
      ifstream fin(ch,ios::in|ios::binary);
      while(fin.read((char*)&obj1,sizeof(obj1)))
      putpixel(x+obj1.x,y+obj1.y,obj1.col);
      if(*ch == 'S' && *(ch+1) == 'N') delay(3);
      fin.close();
}

void copy_file(char *c, char *d, char ch) { //Copying contents from file to file
 if(ch == 'r' || ch == 's') {     //rectangle and square
  ifstream fin(c, ios::in|ios::binary);
  ofstream fout(d, ios::out|ios::binary);
  while(fin.read((char*)&uobj.obj, sizeof(uobj.obj)))
   fout.write((char*)&uobj.obj, sizeof(uobj.obj));
 }
 else if(ch == 'l' || ch == 't' || ch == 'R' || ch == 'e' || ch == 'c') {
  ifstream fin(c, ios::in|ios::binary);
  ofstream fout(d, ios::out|ios::binary);
  while(fin.read((char*)&uobj.obj1, sizeof(uobj.obj1)))   //other shapes
   fout.write((char*)&uobj.obj1, sizeof(uobj.obj1));
 }
 else if(ch == 'a') {                                    //for all shapes
  ifstream fin("rect.txt", ios::in|ios::binary);
  ofstream fout("rect_undo.txt", ios::out|ios::binary);
  while(fin.read((char*)&uobj.obj, sizeof(uobj.obj)))
   fout.write((char*)&uobj.obj, sizeof(uobj.obj));
  fin.close();
  fout.close();
  fin.open("line.txt", ios::in|ios::binary);
  fout.open("line_undo.txt", ios::out|ios::binary);
  while(fin.read((char*)&uobj.obj, sizeof(uobj.obj)))
   fout.write((char*)&uobj.obj, sizeof(uobj.obj));
  fin.close();
  fout.close();
  fin.open("ell.txt", ios::in|ios::binary);
  fout.open("ell_undo.txt", ios::out|ios::binary);
  while(fin.read((char*)&uobj.obj, sizeof(uobj.obj)))
   fout.write((char*)&uobj.obj, sizeof(uobj.obj));
  fin.close();
  fout.close();
 }
 else {                                      //for dat files
  ifstream fin(c, ios::in|ios::binary);
  ofstream fout(d, ios::out|ios::binary);
  while(fin.read((char*)&objd, sizeof(objd)))
   fout.write((char*)&objd, sizeof(objd));
  fin.close();
  fout.close();
 }
}

void del_files() {
  ofstream fout;
  fout.open("rect.txt", ios::out|ios::binary);
  fout.close();
  fout.open("rect_undo.txt", ios::out|ios::binary);
  fout.close();
  fout.open("rect_redo.txt", ios::out|ios::binary);
  fout.close();
  fout.open("ell.txt", ios::out|ios::binary);
  fout.close();
  fout.open("ell_undo.txt", ios::out|ios::binary);
  fout.close();
  fout.open("ell_redo.txt", ios::out|ios::binary);
  fout.close();
  fout.open("line.txt", ios::out|ios::binary);
  fout.close();
  fout.open("line_undo.txt", ios::out|ios::binary);
  fout.close();
  fout.open("line_redo.txt", ios::out|ios::binary);
  fout.close();
  fout.open("eras.txt", ios::out|ios::binary);
  fout.close();
  fout.open("undo.dat", ios::out|ios::binary);
  fout.close();
  fout.open("redo.dat", ios::out|ios::binary);
  fout.close();
  fout.open("current.dat", ios::out|ios::binary);
  fout.close();
}

      //Printing rectangle:-
void rect_out(short unsigned int x1, short unsigned int y1, short unsigned int x2, short unsigned int y2, short int col, short unsigned int style) {
 ofstream fout("rect.txt", ios::app|ios::binary);
 uobj.obj.x1 = x1;
 uobj.obj.x2 = x2;
 uobj.obj.y1 = y1;
 uobj.obj.y2 = y2;
 uobj.obj.col = col;
 uobj.obj.style = style;
 fout.write((char*)&uobj.obj, sizeof(uobj.obj));
 fout.close();
}
	    //Printing ellipse and circle:-
void ell_out(short unsigned int x, short unsigned int y, short unsigned int rx, short unsigned int ry, short unsigned int col, short unsigned int style) {
 ofstream fout("ell.txt", ios::app|ios::binary);
 uobj.obj1.x = x;
 uobj.obj1.y = y;
 uobj.obj1.rx = rx;
 uobj.obj1.ry = ry;
 uobj.obj1.col = col;
 uobj.obj1.style = style;
 fout.write((char*)&uobj.obj1, sizeof(uobj.obj1));
 fout.close();
}
       //Printing lines, rhombus, triangles and free hand drawing
void line_out(short unsigned int x1, short unsigned int y1,short unsigned int x2, short unsigned int y2, short unsigned int col, short unsigned int style) {
 ofstream fout("line.txt", ios::app|ios::binary);
 uobj.obj1.x = x1;
 uobj.obj1.y = y1;
 uobj.obj1.rx = x2;
 uobj.obj1.ry = y2;
 uobj.obj1.col = col;
 uobj.obj1.style = style;
 fout.write((char*)&uobj.obj1, sizeof(uobj.obj1));
 fout.close();
}

void rect_in(short unsigned int x, short unsigned int y, short unsigned int co) {
 setlinestyle(SOLID_LINE, 1, 1);
 ifstream fin("rect.txt", ios::in|ios::binary);

 setcolor(8);
 while(fin.read((char*)&uobj.obj, sizeof(uobj.obj))) { //rectangle and square
  rectangle(uobj.obj.x1, uobj.obj.y1, uobj.obj.x2, uobj.obj.y2);
 }
 fin.close();
 fin.open("ell.txt", ios::in|ios::binary);
 setcolor(8);
 while(fin.read((char*)&uobj.obj1, sizeof(uobj.obj1))) { //ellipse and circle
  ellipse(uobj.obj1.x, uobj.obj1.y, 0, 360, uobj.obj1.rx, uobj.obj1.ry);
 }
 fin.close();
 fin.open("line.txt", ios::in|ios::binary);
 setcolor(8);
 while(fin.read((char*)&uobj.obj1, sizeof(uobj.obj1))) { //line
  line(uobj.obj1.x, uobj.obj1.y, uobj.obj1.rx, uobj.obj1.ry);
 }
 //if (getpixel(162, 43) == WHITE) floodfill(x, y, BLACK);
 fin.close();
 setfillstyle(kgf, co);
 //setlinestyle(kgf1, 1, 1);
 floodfill(x, y, 8);
 fin.open("rect.txt", ios::in|ios::binary);
 while(fin.read((char*)&uobj.obj, sizeof(uobj.obj))) { //rectangle and square
  setcolor(BLACK);
  setlinestyle(SOLID_LINE, 1, 1);
  rectangle(uobj.obj.x1, uobj.obj.y1, uobj.obj.x2, uobj.obj.y2);
  setcolor(uobj.obj.col);
  setlinestyle(uobj.obj.style, 1, 1);
  rectangle(uobj.obj.x1, uobj.obj.y1, uobj.obj.x2, uobj.obj.y2);
 }
 fin.close();
 fin.open("ell.txt", ios::in|ios::binary);
 while(fin.read((char*)&uobj.obj1, sizeof(uobj.obj1))) { //ellipse and circle
  setcolor(BLACK);
  setlinestyle(SOLID_LINE, 1, 1);
  ellipse(uobj.obj1.x, uobj.obj1.y, 0, 360, uobj.obj1.rx, uobj.obj1.ry);
  setcolor(uobj.obj1.col);
  setlinestyle(uobj.obj1.style, 1, 1);
  ellipse(uobj.obj1.x, uobj.obj1.y, 0, 360, uobj.obj1.rx, uobj.obj1.ry);
 }
 fin.close();
 fin.open("line.txt", ios::in|ios::binary);
 while(fin.read((char*)&uobj.obj1, sizeof(uobj.obj1))) { //line
  setcolor(BLACK);
  setlinestyle(SOLID_LINE, 1, 1);
  line(uobj.obj1.x, uobj.obj1.y, uobj.obj1.rx, uobj.obj1.ry);
  setcolor(uobj.obj1.col);
  setlinestyle(uobj.obj1.style, 1, 1);
  line(uobj.obj1.x, uobj.obj1.y, uobj.obj1.rx, uobj.obj1.ry);
 }
 fin.close();
 k:
 setlinestyle(SOLID_LINE, 1, 1);
 x1 = getcolor();
 setcolor(WHITE);
 rectangle(159, 40, getmaxx()-49, 250);
 setcolor(x1);
 setlinestyle(kgf1, 1, 1);
}

void ell_in(short unsigned int x, short unsigned int y, short unsigned int co) {
 ifstream fin("ell.txt", ios::in|ios::binary);
 setcolor(WHITE);
 while(fin.read((char*)&uobj.obj1, sizeof(uobj.obj1))) {          //rectangle
  ellipse(uobj.obj1.x, uobj.obj1.y, 0, 360, uobj.obj1.rx, uobj.obj1.ry);
 }
 setfillstyle(SOLID_FILL, co);
 floodfill(x, y, WHITE);
 //if (getpixel(162, 43) == WHITE) floodfill(x, y, BLACK);
 fin.close();
 ifstream fi("ell.txt", ios::in|ios::binary);
 while(fi.read((char*)&uobj.obj1, sizeof(uobj.obj1))) {          //rectangle
  setcolor(uobj.obj1.col);
  ellipse(uobj.obj1.x, uobj.obj1.y, 0, 360, uobj.obj1.rx, uobj.obj1.ry);
 }
 fi.close();
}

void shapes() {
   //floodfill(50, 418, WHITE);
   setfillstyle(SOLID_FILL, WHITE);
   bar(43, 411, 67, 435);
   dat(47, 415, "Fill.dat");		             //fill dat
   bar(67, 435, 46, 432);
   bar(67, 435, 62, 415);
   dat(113, 411, "pen_d.dat");                       //pen dat
   bar(183, 411, 207, 435);
   dat(187, 415, "undo_p.dat");                      //undo
   bar(207, 435, 186, 432);
   bar(207, 435, 202, 415);
   bar(253, 411, 277, 435);
   dat(257, 415, "redo_p.dat");                      //redo
   bar(277, 435, 256, 432);
   bar(277, 435, 272, 415);
   bar(323, 411, 347, 435);
   dat(327, 415, "new.dat");                         //new file
   bar(347, 435, 326, 432);
   bar(347, 435, 342, 415);
   bar(393, 411, 417, 435);
   dat(397, 415, "close.dat");                       //close file
   bar(417, 435, 396, 432);
   bar(417, 435, 412, 415);
   for (i1 = 40, j1 = 1; j1 < 9; j1++, i1+=70) {     //bottom
    rectangle(i1, 328, i1+30, 358);
   }
   for (i1 = 40, j1 = 1; j1 < 7; j1++, i1+=70) {     //bottom
    rectangle(i1, 408, i1+30, 438);
   }
   //////////////// bottom shapes/////////////////
   setcolor(7);
   line(46, 335, 64, 350);                           //line
   setcolor(WHITE);
   rectangle(116, 334, 134, 352);                    //square
   setfillstyle(SOLID_FILL, 7);
   floodfill(117, 335, WHITE);
   rectangle(184, 338, 206, 348);                    //rectangle
   floodfill(185, 339, WHITE);
   circle(265, 343, 10);                             //circle
   floodfill(265, 343, WHITE);
   fillellipse(335, 343, 10, 7);
   setfillstyle(SOLID_FILL, WHITE);		     //ellipse
   line(395, 352, 415, 352);                         //triangle
   line(405, 335, 395, 352);
   line(405, 335, 415, 352);
   setfillstyle(SOLID_FILL, 7);
   floodfill(405, 350, WHITE);
   line(468, 352, 482, 352);                         //right triangle
   line(468, 352, 468, 335);
   line(482, 352, 468, 335);
   floodfill(470, 350, WHITE);
   line(545, 332, 555, 343);                         //rhombus
   line(545, 332, 535, 343);
   line(555, 343, 545, 354);
   line(535, 343, 545, 354);
   floodfill(545, 350, WHITE);
   ///////////////////////////////////////////////
   rectangle(3, 280, getmaxx()-49, 365);             //bottom rectangle (top)
   //rectangle(3, 370, 298, getmaxy()-35);             //bottom rectangle (bottom left)
   rectangle(3, 370, getmaxx()-189, getmaxy()-35);  //bottom rectangle (bottom right)
   line(3, 310, getmaxx()-49, 310);                  //line  bottom(top)
   line(3, 395, getmaxx()-189, 395);                           //line  bottom(bottom left)
   //line(302, 395, getmaxx()-49, 395);                //line  bottom(bottom right)
   rectangle(3, 3, 150, 250);                        //left middle
   rectangle(159, 40, getmaxx()-49, 250);            //draw area(bottom)
   rectangle(159, 3, getmaxx()-49, 40);              //draw area(top)
   settextstyle(0, 0, 2);
   settextjustify(CENTER_TEXT, CENTER_TEXT);
   outtextxy(349, 20, "DRAW AREA");
   settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
   settextjustify(LEFT_TEXT, TOP_TEXT);
   outtextxy(10, 6, "COLOURS");
   outtextxy(235, 290, "SHAPES");
   outtextxy(185, 375, "TOOLS");
   //outtextxy(403, 375, "FILES");
   settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
   rectangle(60, 28, 140, 40);                       //pattern
   line(125, 28, 125, 40);                           //pattern
   for (j1 = 32, i1 = 5; i1 >= 0; j1++, i1--) {      //pattern arrow
    line (132-i1, j1, 132+i1, j1);
   }
   outtextxy(65, 30, "Pattern");
}

void disp_col() {
   for (i1 = 0, j1 = 55; i1 < 8; i1++, j1+=20) {
    setfillstyle(SOLID_FILL, i1);
    bar(17, j1-10, 27, j1);
    setcolor(WHITE);
    rectangle(15, j1-12, 29, j1+2);
   }
   for (i1 = 9, j1 = 55; i1 < 16; i1++, j1+=20) {
    setfillstyle(SOLID_FILL, i1);
    bar(42, j1-10, 52, j1);
    setcolor(WHITE);
    rectangle(40, j1-12, 54, j1+2);
   }
}

void intro() {
 settextstyle(0, 0, 5);
 settextjustify(LEFT_TEXT, CENTER_TEXT);

 setcolor(WHITE);
 outtextxy(185, getmaxy()/2 - 80, "Swastik");
 outtextxy(185, getmaxy()/2, "Anurag");
 outtextxy(185, getmaxy()/2 + 80, "Sanjith");
 delay(1000);

 setcolor(YELLOW);
 outtextxy(185, getmaxy()/2 - 80, "S");
 outtextxy(185, getmaxy()/2, "A");
 outtextxy(185, getmaxy()/2 + 80, "S");
 for(x = 222; x < 476; x++) {
  size = imagesize(x, getmaxy()/2 - 101, 475, getmaxy()/2 + 101);
  buf = malloc(size);
  getimage(x, getmaxy()/2 - 101, 475, getmaxy()/2 + 101, buf);
  putimage(222, getmaxy()/2 - 101, buf, COPY_PUT);
  delete[] buf;
 }
 size = imagesize(180, getmaxy()/2-25, 225, getmaxy()/2+20);
 buf = malloc(size);
 getimage(180, getmaxy()/2-25, 225, getmaxy()/2+20, buf);
 for(x = 1, y = 1, z = 1; x < 120; x++, z++) {
  putimage(180+x, getmaxy()/2-25-y, buf, COPY_PUT);
  delete[] buf;
  size = imagesize(180+x, getmaxy()/2-25-y, 225+x, getmaxy()/2+20-y);
  buf = malloc(size);
  //getimage(180+x, getmaxy()/2-25-y, 225+x, getmaxy()/2+20-y, buf);
  //rectangle(180, getmaxy()/2-25, 225, getmaxy()/2+20);
  if(z%2 == 0) y++;
  if(z%4 == 0) z++;
 }
 delete[] buf;
 //rectangle(180, getmaxy()/2+55, 217, getmaxy()/2+102);
 size = imagesize(180, getmaxy()/2+55, 217, getmaxy()/2+102);
 buf = malloc(size);
 getimage(180, getmaxy()/2+55, 217, getmaxy()/2+102, buf);
 for(x = 1, y = 1, z = 1; x < 240; x++, z++) {
  putimage(180+x, getmaxy()/2+55-y, buf, COPY_PUT);
  delete[] buf;
  size = imagesize(180+x, getmaxy()/2+55-y, 217+x, getmaxy()/2+102-y);
  buf = malloc(size);
  if(z%2 == 0) y++;
  if(z%4 == 0) z++;
 }
 delete[] buf;
 size = imagesize(421, getmaxy()/2-101, 459, getmaxy()/2-62);
 buf = malloc(size);
 getimage(421, getmaxy()/2-101, 459, getmaxy()/2-62, buf);
 size = imagesize(180, getmaxy()/2-101, 218, getmaxy()/2-62);
 bu = malloc(size);
 getimage(180, getmaxy()/2-101, 218, getmaxy()/2-62, bu);
 x = 1;
 while(x < 66) {
  if(x < 61) putimage(421-x, getmaxy()/2-101, buf, COPY_PUT);
  putimage(180+x, getmaxy()/2-101, buf, COPY_PUT);
  x++;
 }
 delete[] buf;
 delete[] bu;
 //ShowBMP(212, 200, "Snapshot.bmp");
 dat(212, 200, "SNAPSHOT.dat");
 //rectangle(220, 130, 420, 240);
 size = imagesize(220, 130, 420, 250);
 buf = malloc(size);
 getimage(220, 130, 420, 250, buf);
 for(x = 0; x < 40; x++) {
  putimage(220, 130-x, buf, COPY_PUT);
 }
 delete[] buf;
 setcolor(GREEN);
 setfillstyle(SOLID_FILL, GREEN);
 settextstyle(0, 0, 2);
 settextjustify(LEFT_TEXT, CENTER_TEXT);
 outtextxy(270, 354, "LOADING...");
 rectangle(200, 300, 439, 340);
 for(x = 202; x < 437; x++) {
  bar(202, 302, x, 338);
  delay(10);
 }
 setcolor(BLACK);
 outtextxy(270, 354, "LOADING...");
 setcolor(WHITE);
 outtextxy(273, 354, "LOADED");
 delay(1000);
 setfillstyle(SOLID_FILL, WHITE);
 setcolor(WHITE);
 cleardevice();
}


int PENCIL[32]= {
0xffff, 0xffff, 0xf8ff, 0xf0ff,
0xe0ff, 0xe0ff, 0xc1ff, 0xc1ff,
0x83ff, 0x83ff, 0x07ff, 0x07ff,
0x0fff, 0x1fff, 0x3fff, 0x7fff,
0x0000, 0x0000, 0x0000, 0x0600,
0x0600, 0x0000, 0x1800, 0x1800,
0x3800, 0x3000, 0x7000, 0x2000,
0x0000, 0x0000, 0x0000, 0x0000,
};

int DRAW[32]= {
0xfc7f, 0xfc7f, 0xfc7f, 0xfc7f,
0xfc7f, 0x8003, 0x8103, 0x8003,
0xfc7f, 0xfc7f, 0xfc7f, 0xfc7f,
0xfc7f, 0xffff, 0xffff, 0xffff,
0x0280, 0x0280, 0x0280, 0x0280,
0x0280, 0x7efc, 0x0100, 0x7efc,
0x0280, 0x0280, 0x0280, 0x0280,
0x0280, 0x0000, 0x0000, 0x0000,
};

int FILL[32]= {
0xffff, 0xff3f, 0xfe3f, 0xfd0f,
0xf807, 0xf003, 0xf001, 0xf000,
0xf800, 0xf801, 0xfc03, 0xfe07,
0xff0f, 0xff9f, 0xffff, 0xffff,
0x0000, 0x0000, 0x0080, 0x39c0,
0x73b0, 0xe7e0, 0xdfc0, 0xd592,
0xe306, 0xe20c, 0xe018, 0xe030,
0x6060, 0x6000, 0x2000, 0x0000,
};

int SELECT[32]= {
0x8fff, 0x3fff, 0x5fff, 0x6fff,
0xf7ff, 0xffff, 0xffff, 0xffff,
0xffff, 0xffff, 0xffff, 0xffff,
0xffff, 0xffff, 0xffff, 0xffff,
0x8000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000,
};
int SELECT_X=0,SELECT_Y=0;

int ERASER[32]= {
0xffff, 0xf8ff, 0xf8ff, 0xf8ff,
0xffff, 0xffff, 0xffff, 0xffff,
0xffff, 0xffff, 0xffff, 0xffff,
0xffff, 0xffff, 0xffff, 0xffff,
0x0f80, 0x0f80, 0x0f80, 0x0f80,
0x0f80, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000,
};
int ERASER_X=5,ERASER_Y=0;

int MODIFY[32] = {
0x3fff,0x1fff,0x0fff,0x07ff,
0x03ff,0x01ff,0x00ff,0x007f,
0x003f,0x001f,0x01ff,0x30ff,
0xf0ff,0xf87f,0xf87f,0xfcff,
0x0000,0x4000,0x6000,0x7000,
0x7800,0x7c00,0x7e00,0x7f00,
0x7f80,0x6c00,0x4c00,0x0600,
0x0600,0x0300,0x0300,0x0000,
};

void changecursor(int *shape,int x,int y)
{
    union REGS inreg, outreg;
    struct SREGS s;
    inreg.x.ax = 0x9;
    inreg.x.bx = x;
    inreg.x.cx = y;
    inreg.x.dx = (unsigned)shape;
    segread(&s);
    s.es = s.ds;
    int86x(0x33,&inreg,&outreg,&s);
}

void new_file() {   //clear screen and open new file
 del_files();
 ofstream fout("rect.txt", ios::out|ios::binary);
 rect_out(159, 40, getmaxx()-49, 250, WHITE, SOLID_LINE);
 fout.close();
 setfillstyle(SOLID_FILL, BLACK);
 bar(160, 41, getmaxx()-50, 249);
 b = 1;
 k = 0;
}

void exit_pgm() {      //exits the program
 union REGS i, o;
 k:
 i.x.ax=3;
 int86(51,&i,&o);
 z = o.x.bx;
 if(z == 1) goto k;
 del_files();
 exit(0);
}

void undo_file() {
 //for binary files of saved shapes:-
 rename("rect_redo.txt", "undo1.txt");
 rename("rect.txt", "rect_redo.txt");
 rename("rect_undo.txt", "rect.txt");
 rename("undo1.txt", "rect_undo.txt");
 rename("ell_redo.txt", "undo1.txt");
 rename("ell.txt", "ell_redo.txt");
 rename("ell_undo.txt", "ell.txt");
 rename("undo1.txt", "ell_undo.txt");
 rename("line_redo.txt", "undo1.txt");
 rename("line.txt", "line_redo.txt");
 rename("line_undo.txt", "line.txt");
 rename("undo1.txt", "line_undo.txt");

 ofstream fout("line_undo.txt", ios::out|ios::binary);
 fout.close();
 fout.open("ell_undo.txt", ios::out|ios::binary);
 fout.close();
 fout.open("rect_undo.txt", ios::out|ios::binary);
 fout.close();
 //for draw area:-
 rename("redo.dat", "undo1.dat");
 rename("current.dat", "redo.dat");
 rename("undo.dat", "current.dat");
 rename("undo1.dat", "undo.dat");
 bmp_to_dat("undo.dat", 0, 0, 0, 0);
 dat(0, 0, "current.dat");
 b = 1;
 l = 1;
}

void redo_file() {
 //for binary files of shapes:-
 rename("rect.txt", "undo1.txt");
 rename("rect_redo.txt", "rect.txt");
 rename("rect_undo.txt", "rect_redo.txt");
 rename("undo1.txt", "rect_undo.txt");
 rename("ell.txt", "undo1.txt");
 rename("ell_redo.txt", "ell.txt");
 rename("ell_undo.txt", "ell_redo.txt");
 rename("undo1.txt", "ell_undo.txt");
 rename("line.txt", "undo1.txt");
 rename("line_redo.txt", "line.txt");
 rename("line_undo.txt", "line_redo.txt");
 rename("undo1.txt", "line_undo.txt");
 //for draw area:-
 rename("current.dat", "undo1.dat");
 rename("redo.dat", "current.dat");
 rename("undo.dat", "redo.dat");
 rename("undo1.dat", "undo.dat");
 bmp_to_dat("redo.dat", 0, 0, 0, 0);
 dat(0, 0, "current.dat");
 b = 1;
}

void pattern1() {
     union REGS i, o;
     i.x.ax=2;
     int86(51,&i,&o);
     for(int j = 0; j < 165; j++) {
      setfillstyle(SOLID_FILL, WHITE);
      bar(60, 40, 140, 40+j);
      delay(5);

      }
      setcolor(BLACK);
      for(x1 = 15, y1 = 1; x1 <=165; x1+=15, y1++) {
       line(60, 40+x1, 140, 40+x1);
       setfillstyle(y1, WHITE);
       bar(60, 40+x1-15, 140, 40+x1);
      }
      setcolor(WHITE);
      for(x1 = 15; x1 <=165; x1+=15) {
       line(60, 40+x1, 140, 40+x1);
      }
      i.x.ax=1;
      int86(51,&i,&o);
      to:
      i.x.ax=3;
      int86(51,&i,&o);
      x = o.x.cx, y = o.x.dx, z = o.x.bx;
      if(z == 1) goto to;
      else if(z == 0) {

       t:
       i.x.ax=3;
       int86(51,&i,&o);
       x = o.x.cx, y = o.x.dx, z = o.x.bx;
       if(z == 1 && x > 60 && y > 28 && x < 140 && y < 40)
	{ i.x.ax=2;
	  int86(51,&i,&o);
	  for(int j = 0; j < 165; j++) {
	  setfillstyle(SOLID_FILL, BLACK);
	  bar(60, 205, 140, 205-j);
	  delay(5);  }
	 }
	else if(z == 1 && x > 60 && x < 140 && y > 40 && y < 205) {
	 y1 = y;
	 kgf = ((y1-40)/15)+1;
	 i.x.ax=2;
	 int86(51,&i,&o);
	 for(int j = 0; j < 165; j++) {
	 setfillstyle(SOLID_FILL, BLACK);
	 bar(60, 205, 140, 205-j);
	 delay(5);  }

	}
       else goto t;
       i.x.ax=1;
       int86(51,&i,&o);
     }
}

void pattern2() {
      union REGS i, o;
      i.x.ax=2;
      int86(51,&i,&o);
      for(int j = 0; j < 75; j++) {
       setfillstyle(SOLID_FILL, WHITE);
       bar(60, 40, 140, 40+j);
       delay(5);
      }
      setcolor(BLACK);
      for(x1 = 15, y1 = 0; x1 <=75; x1+=15, y1++) {
       setlinestyle(0, 3, 1);
       line(60, 40+x1, 140, 40+x1);
       setlinestyle(y1, 3, 1);
       line(61, 40+x1-7, 139, 40+x1-7);
      }
      i.x.ax=1;
      int86(51,&i,&o);
      too:
      i.x.ax=3;
      int86(51,&i,&o);
      x = o.x.cx, y = o.x.dx, z = o.x.bx;
      if(z == 1) goto too;
      else if(z == 0) {

       tooo:
       i.x.ax=3;
       int86(51,&i,&o);
       x = o.x.cx, y = o.x.dx, z = o.x.bx;
       if(z == 1 && x > 60 && y > 28 && x < 140 && y < 40)
	{ i.x.ax=2;
	  int86(51,&i,&o);
	  for(int j = 0; j < 73; j++) {
	  setfillstyle(SOLID_FILL, BLACK);
	  bar(60, 115, 140, 115-j);
	  delay(5);  }
	 }
	else if(z == 1 && x > 60 && x < 140 && y > 40 && y < 115) {
	 y1 = y;
	 kgf1 = ((y1-40)/15);
	 i.x.ax=2;
	 int86(51,&i,&o);
	 for(int j = 0; j < 73; j++) {
	 setfillstyle(SOLID_FILL, BLACK);
	 bar(60, 115, 140, 115-j);
	 delay(5);  }

	}
       else goto tooo;
       i.x.ax=1;
       int86(51,&i,&o);
    }
}

void fill_col(short unsigned u) {
   union REGS i, o;
   i.x.ax=3;
   int86(51,&i,&o);
   x = o.x.cx;
   y = o.x.dx;
   z = o.x.bx;
   i.x.ax=2;
   int86(51,&i,&o);
   rect_in(x, y, u);
   i.x.ax=1;
   int86(51,&i,&o);
}

void pen_draw(short unsigned u) {
   union REGS i, o;
   copy_file("line.txt", "line_undo.txt", 'a');
   setcolor(u);
   i.x.ax=3;
   int86(51,&i,&o);
   x1 = o.x.cx;
   y1 = o.x.dx;
   //z = o.x.bx;
   i.x.ax=2;
   int86(51,&i,&o);
   //delay(10);
   jh:
   i.x.ax=3;
   int86(51,&i,&o);
   x2 = o.x.cx;
   y2 = o.x.dx;
   z = o.x.bx;
   if(x2 > 159 && x2 < getmaxx()-49 && y2 > 40 && y2 < 250 && x1 > 159 && x1 < getmaxx()-49 && y1> 40 && y1 < 250)
   {
    line(x1, y1, x2, y2);
    line_out(x1, y1, x2, y2, u, kgf1);
   }
   if(z == 1) {
    x1 = x2;
    y1 = y2;
    goto jh;
   }
}

char* icon_name(int i) {
 switch(i) {
  case 1: return "Line";
  case 2: return "Square";
  case 3: return "Rectangle";
  case 4: return "Circle";
  case 5: return "Ellipse";
  case 6: return "Triangle";
  case 7: return "Right Triangle";
  case 8: return "Rhombus";
  case 9: return "Fill";
  case 10: return "Drawing";
  case 11: return "Undo";
  case 12: return "Redo";
  case 13: return "Clear";
  case 14: return "Exit";
  default: return "";
 }
}


void main()
{

   int gdriver = DETECT, gmode;
   short unsigned u = 15, htm = 0;
   /* initialize graphics and local variables */
   initgraph(&gdriver, &gmode, "C:\\TC\\bgi");
   /* read result of initialization */
   if (graphresult() != grOk)  /* an error occurred */
   {
      exit(1); /* terminate */
   }
   ///////////////////Saving draw area rectangle in file///////////
   ofstream fout("rect.txt", ios::app|ios::binary);
   uobj.obj.x1 = 159;
   uobj.obj.x2 = getmaxx()-49;
   uobj.obj.y1 = 40;
   uobj.obj.y2 = 250;
   uobj.obj.col = WHITE;
   fout.write((char*)&uobj.obj, sizeof(uobj.obj));
   fout.close();
   copy_file("rect.txt", "rect_undo.txt", 'r');
   ////////////////////////////////////////////////////////////////
   intro();                      //displaying 'SAS PAINT'
   //gdriver = DETECT;
   //initgraph(&gdriver, &gmode, "C:\\TC\\bgi");
   union REGS i,o;
   setcolor(WHITE);
   shapes();                     //shapes outside draw area
   n:
   disp_col();      //for displaying colours
  //union REGS i,o;
  i.x.ax=1;
  int86(51,&i,&o);
  i.x.ax=3;
  int86(51,&i,&o);
  x = o.x.cx;
  y = o.x.dx;
  z = o.x.bx;
  if (kbhit() != 0) goto l;
  if (z == 0) {
   if (x >= 38 && x <= 561 && y >= 326 && y <= 429) {
    changecursor(MODIFY, 0, 0);
      i.x.ax=1;
      int86(51,&i,&o);
    for (i1 = 40, j1 = 1; j1 < 9; j1++, i1+=70) {     //bottom
     if (x > i1 && x < i1+30 && y > 328 && y < 358) {
      changecursor(MODIFY, 0, 0);
      i.x.ax=2;
      int86(51,&i,&o);
      setcolor(WHITE);
      setlinestyle(SOLID_LINE, 1, 1);
      line(i1+15, 320, i1+15, 312);
      line(i1+15, 320, i1+18, 312);
      bar(i1-10, 292, i1+43, 312);
      floodfill(i1+16, 315, WHITE);
      setcolor(DARKGRAY);
      settextstyle(DEFAULT_FONT+2, HORIZ_DIR, 4);
      if(j1 == 7) {
       outtextxy(i1-8, 291, "Right");
       outtextxy(i1-8, 300, "Triangle");
      }
      else outtextxy(i1-8, 297, icon_name(j1));     //Printing names of icons
      for(x1 = 1; x1 <= 5; x1++) {
       rectangle(i1-x1, 328-x1, i1+30+x1, 358+x1);
       delay(10);
      }
      i.x.ax=1;
      int86(51,&i,&o);
      kgf:
      i.x.ax=3;
      int86(51,&i,&o);
      x = o.x.cx;
      y = o.x.dx;
      z = o.x.bx;
      if (x > i1 && x < i1+30 && y > 328 && y < 358) {
       if(z == 1) b = j1;
       goto kgf;
      }
      i.x.ax=2;
      int86(51,&i,&o);
      setcolor(BLACK);
      line(i1+15, 320, i1+15, 312);
      line(i1+15, 320, i1+18, 312);
      setfillstyle(SOLID_FILL, BLACK);
      bar(i1-10, 292, i1+43, 312);
      floodfill(i1+16, 315, BLACK);
      setcolor(WHITE);
      settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
      settextjustify(LEFT_TEXT, TOP_TEXT);
      outtextxy(235, 290, "SHAPES");
      rectangle(3, 280, getmaxx()-49, 365);             //bottom rectangle (top)
      line(3, 310, getmaxx()-49, 310);                  //line  bottom(top)
      setcolor(BLACK);
      for(x1 = 1; x1 <= 5; x1++)
       rectangle(i1-x1, 328-x1, i1+30+x1, 358+x1);
      i.x.ax=1;
      int86(51,&i,&o);
     }
    }
    for (i1 = 40, j1 = 9; j1 < 15; j1++, i1+=70) {     //bottom
     if (x > i1 && x < i1+30 && y > 408 && y < 438) {
      changecursor(MODIFY, 0, 0);
      i.x.ax=2;
      int86(51,&i,&o);
      setcolor(WHITE);
      setfillstyle(SOLID_FILL, WHITE);
      //i1, 408, i1+30, 398+40
      setlinestyle(SOLID_LINE, 1, 1);
      line(i1+15, 400, i1+15, 392);
      line(i1+15, 400, i1+18, 392);
      bar(i1-10, 372, i1+40, 392);
      floodfill(i1+16, 394, WHITE);
      setcolor(DARKGRAY);
      settextstyle(DEFAULT_FONT+2, HORIZ_DIR, 4);
      outtextxy(i1-8, 377, icon_name(j1));     //Printing names of icons
      for(x1 = 1; x1 <= 5; x1++) {
       rectangle(i1-x1, 408-x1, i1+30+x1, 438+x1);
       delay(10);
      }
      i.x.ax=1;
      int86(51,&i,&o);
      kf:
      i.x.ax=3;
      int86(51,&i,&o);
      x = o.x.cx;
      y = o.x.dx;
      z = o.x.bx;
      if (x > i1 && x < i1+30 && y > 408 && y < 438) {
       if(z == 1) b = j1;
       //////////////////////////new file/////////////////////////////////
       if(b == 13) {
	new_file();
       }
       //////////////////////////////////////////////////////////////////

       //////////////////////////exit////////////////////////////////////
       else if(b == 14) {
	exit_pgm();
       }
       //////////////////////////////////////////////////////////////////

       //////////////////////////undo////////////////////////////////////
       else if(b == 11 && z == 1 && k > 1) {
	undo_file();
       }
       //////////////////////////////////////////////////////////////////

       //////////////////////////redo////////////////////////////////////
       else if(b == 12 && z == 1 && l == 1) {
	redo_file();
       }
       //////////////////////////////////////////////////////////////////
       goto kf;
      }
      i.x.ax=2;
      int86(51,&i,&o);
      setcolor(BLACK);
      setfillstyle(SOLID_FILL, BLACK);
      line(i1+15, 400, i1+15, 392);
      line(i1+15, 400, i1+18, 392);
      bar(i1-10, 372, i1+40, 392);
      bar(i1+10, 392, i1+20, 396);
      //floodfill(i1+16, 394, WHITE);
      setcolor(WHITE);
      settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
      settextjustify(LEFT_TEXT, TOP_TEXT);
      outtextxy(185, 375, "TOOLS");
      rectangle(3, 370, getmaxx()-189, getmaxy()-35);   //bottom rectangle (bottom)
      line(3, 395, getmaxx()-189, 395);                 //line  bottom(bottom)
      setcolor(BLACK);
      for(x1 = 1; x1 <= 5; x1++)
       rectangle(i1-x1, 408-x1, i1+30+x1, 438+x1);
      i.x.ax=1;
      int86(51,&i,&o);
     }
    }
   }

   if ((x >= 15 && x <= 29) || (x >= 40 && x <= 54)) {
    changecursor(MODIFY, 0, 0);
    for (i1 = 0, j1 = 55; i1 < 8; i1++, j1+=20) {

    if (x > 17 && x < 27 && y > j1-10 && y < j1) {
     i.x.ax=3;
     int86(51,&i,&o);
     z = o.x.bx;
     b:
     for (i1 = 15, x = 29, y = j1-12, z = j1+2; i1 > 13; i1--, x++, y--, z++) {
      rectangle(i1, y, x, z);
     }

     i.x.ax=3;
     int86(51,&i,&o);
     x = o.x.cx;
     y = o.x.dx;
     z = o.x.bx;
     if (x > 17 && x < 27 && y > j1-10 && y < j1 && z == 0)
     goto b;
     if(x > 17 && x < 27 && y > j1-10 && y < j1 && z == 1)
     {
      i.x.ax=2;
      int86(51,&i,&o);
      u = getpixel(x, y);
      i.x.ax=1;
     int86(51,&i,&o);
      goto b;
     }
     setcolor(BLACK);

     i.x.ax=2;
     int86(51,&i,&o);
     for (i1 = 15, x = 29, y = j1-12, z = j1+2; i1 > 13; i1--, x++, y--, z++) {
      rectangle(i1, y, x, z);
     }
     i.x.ax=1;
     int86(51,&i,&o);
    }
    //rectangle(15, j1-12, 29, j1+2);
    }
   for (i1 = 9, j1 = 55; i1 < 16; i1++, j1+=20) {

    if (x > 42 && x < 52 && y > j1-10 && y < j1) {
    i.x.ax=3;
    int86(51,&i,&o);
    z = o.x.bx;
    c:
     for (i1 = 40, x = 54, y = j1-12, z = j1+2; i1 > 38; i1--, x++, y--, z++) {
      rectangle(i1, y, x, z);
     }
     i.x.ax=3;
     int86(51,&i,&o);
     x = o.x.cx;
     y = o.x.dx;
     z = o.x.bx;
     if (x > 42 && x < 52 && y > j1-10 && y < j1 & z == 0)
     goto c;
     if (x > 42 && x < 52 && y > j1-10 && y < j1 & z == 1)
     {
      i.x.ax=2;
      int86(51,&i,&o);
      u = getpixel(x, y);
      i.x.ax=1;
      int86(51,&i,&o);
      goto c;
     }
     setcolor(BLACK);
     delay(10);
     i.x.ax=2;
     int86(51,&i,&o);
     for (i1 = 40, x = 54, y = j1-12, z = j1+2; i1 > 38; i1--, x++, y--, z++) {
      rectangle(i1, y, x, z);
     }
     i.x.ax=1;
     int86(51,&i,&o);
     }

   }

    s:
   i.x.ax=3;
   int86(51,&i,&o);
   x = o.x.cx;
   y = o.x.dx;
   z = o.x.bx;


   setcolor(u);
    goto n;
  }
  else if (x >= 60 && x <= 140 && y >= 28 && y <= 40) {     //Pattern
    w:
    changecursor(MODIFY, 0, 0);
    setcolor(WHITE);
    for (short int i1 = 60, i2 = 140, j1 = 28, j2 = 40; i1 > 57; i1--, i2++, j1--, j2++) rectangle(i1, j1, i2, j2);
    i.x.ax=3;
    int86(51,&i,&o);
    x = o.x.cx, y = o.x.dx, z = o.x.bx;
    if(x > 60 && y > 28 && x < 140 && y < 40 && z == 1 && kl ==0) {   //pattern
     if(b == 9) {
      pattern1();
     }
     else {
      pattern2();
     }
    }   ////////////////////////////////////////////////////////////////
    i.x.ax=3;
     int86(51,&i,&o);
     x = o.x.cx, y = o.x.dx, z = o.x.bx;
     if(x < 60 && y < 28 && x > 140 && y > 40 && z == 1 && kl == 1) {
      for(j = 100; j >= 0; j--) {
       bar(60, 40, 140, 40-j);
       delay(5);
      }
      kl = 0;
      mn:
      i.x.ax=3;
     int86(51,&i,&o);
     x = o.x.cx, y = o.x.dx, z = o.x.bx;
     if(z == 1) goto mn;
     }
     else goto mn;
    if (x >= 60 && x <= 140 && y >= 28 && y <= 40) goto w;
    else {
    i.x.ax=2;
    int86(51,&i,&o);
     setcolor(BLACK);
     for (i1 = 60, i2 = 140, j1 = 28, j2 = 40; i1 > 57; i1--, i2++, j1--, j2++) rectangle(i1, j1, i2, j2);
     setcolor(WHITE);
     rectangle(60, 28, 140, 40);
     i.x.ax=1;
     int86(51,&i,&o);
    }
    goto n;
  }

  else if (x > 159 && x < getmaxx()-49 && y > 40 && y < 250) {
   if(b < 9) changecursor(DRAW, 8, 5);            //to change cursor shape
   if(b == 9) changecursor(FILL, 0, 8);
   if(b == 10) changecursor(PENCIL, 0, 0);
   i.x.ax=1;
   int86(51,&i,&o);
  }

  else {
   changecursor(MODIFY, 0, 0);
   goto n;
  }
  }

  else if (z == 1) {
  if(x > 159 && x < getmaxx()-49 && y > 40 && y < 250 && b < 9) { //draw area
   setcolor(u);
   i.x.ax=2;
   int86(51,&i,&o);
  ////////////////////////////////////////////
    size1 = imagesize(160, 41, 250, 249);
    size2 = imagesize(250, 41, 320, 249);
    size3 = imagesize(320, 41, 380, 249);
    size4 = imagesize(380, 41, 420, 249);
    size5 = imagesize(420, 41, 500, 249);

    buf1 = malloc(size1);
    buf2 = malloc(size2);
    buf3 = malloc(size3);
    buf4 = malloc(size4);
    buf5 = malloc(size5);


    if(buf1 == NULL ) {
     cout << "Memory fail1";
     getch();
     exit(0);
    }
    if(buf2 == NULL ) {
     cout << "Memory fail2";
     getch();
     exit(0);
    }
    if(buf3 == NULL ) {
     cout << "Memory fail3";
     getch();
     exit(0);
    }
    if(buf4 == NULL ) {
     cout << "Memory fail4";
     getch();
     exit(0);
    }
    if(buf5 == NULL ) {
     cout << "Memory fail5";
     getch();
     exit(0);
    }

    getimage(160, 41, 250, 249, buf1);
    getimage(250, 41, 320, 249, buf2);
    getimage(320, 41, 380, 249, buf3);
    getimage(380, 41, 420, 249, buf4);
    getimage(420, 41, 500, 249, buf5);
    bmp_to_dat("right.dat", 500, 41, getmaxx()-50, 249);
    delay(10);
    x1 = x;
    y1 = y;
    m:
    i.x.ax=3;
    int86(51,&i,&o);
    x = o.x.cx;
    y = o.x.dx;
    if(x >= 500) ip = 0;
    z = o.x.bx;
    if (z == 1 ) {
    /////////////line, right triangle, rectangle and rhombus///////
    if (x > 160 && x < getmaxx()-50 && y > 41 && y < 249 && (b == 1 || b == 3 || b == 7 || b == 8)) x2 = x, y2 = y;
    ///////////////////////////////////////////

    /////////////square////////////////////////
    else if (x > 160 && x < getmaxx()-50 && b == 2) {
     if (x >= x1 && y1+(x-x1) < 249) x2 = x, y2 = y;
     else if (x < x1 && y1-(x1-x) > 41) x2 = x, y2 = y;
    }
    ///////////////////////////////////////////

    /////////////circle////////////////////////
    else if (x > 160 && x < getmaxx()-50 && b == 4) {
     if (x >= x1 && y1+((x-x1)/2) < 249 && y1-((x-x1)/2) > 41) x2 = x, y2 = y;
     else if (x < x1 && y1+((x1-x)/2) < 249 && y1-((x1-x)/2) > 41) x2 = x, y2 = y;
    }
    ///////////////////////////////////////////

    /////////////ellipse and triangle//////////
    if (x > 160 && x < getmaxx()-50 && y > 41 && y < 249 && (b == 5||b == 6)) x2 = x, y2 = y;
    ///////////////////////////////////////////

    if(b != 10) {
     putimage(160, 41, buf1, COPY_PUT);
     putimage(250, 41, buf2, COPY_PUT);
     putimage(320, 41, buf3, COPY_PUT);
     putimage(380, 41, buf4, COPY_PUT);
     putimage(420, 41, buf5, COPY_PUT);
     if(x1 >= 500 || x2 >= 500)
      {
       dat(0, 0, "right.dat");
       fd = 0;
      }
     else if((x1 < 500 || x2 < 500) && fd == 0)
      {
       dat(0, 0, "right.dat");
       fd = 1;
      }
    }
    setcolor(u);
    setlinestyle(kgf1, 1, 1);
    ////////for line//////////////////////
    if(b == 1) line(x1, y1, x2, y2);
    //////////////////////////////////////

    ////////for rectangle/////////////////
    if(b == 3) rectangle(x1, y1, x2, y2);
    //////////////////////////////////////

    ////////for square////////////////////
    if(b == 2) {
     rectangle(x1, y1, x2, y1+(x2-x1));
     htm = 1;
    }
    //////////////////////////////////////

    ////////for circle////////////////////
    if(b == 4) {
     if(x2 >= x1) circle(x1+((x2-x1)/2), y1, ((x2-x1)/2));
     else if(x2 < x1) circle(x1-((x1-x2)/2), y1, ((x1-x2)/2));
     htm = 1;
    }
    //////////////////////////////////////

    ////////for ellipse///////////////////
    if(b == 5) {
     if(x2 >= x1 && y2 >= y1) ellipse(x1+((x2-x1)/2), y1+((y2-y1)/2), 0, 360, ((x2-x1)/2), ((y2-y1)/2));
     if(x2 >= x1 && y1 > y2)  ellipse(x1+((x2-x1)/2), y1-((y1-y2)/2), 0, 360, ((x2-x1)/2), ((y1-y2)/2));
     if(x1 > x2 && y2 >= y1)  ellipse(x1-((x1-x2)/2), y1+((y2-y1)/2), 0, 360, ((x1-x2)/2), ((y2-y1)/2));
     if(x1 > x2 && y1 >= y2)  ellipse(x1-((x1-x2)/2), y1-((y1-y2)/2), 0, 360, ((x1-x2)/2), ((y1-y2)/2));
    }
    //////////////////////////////////////

    ////////for triangle//////////////////
    if(b == 6) {
     line(x1, y2, x2, y2);
     if(x2 >= x1) {
      line(x1, y2, x1+((x2-x1)/2), y1);
      line(x2, y2, x1+((x2-x1)/2), y1);
     }
     else {
      line(x1, y2, x1-((x1-x2)/2), y1);
      line(x2, y2, x1-((x1-x2)/2), y1);
     }
    }
    //////////////////////////////////////

    ////////for rhombus///////////////////
    if(b == 8) {
     if(x2 >= x1 && y2 >= y1) {
      line(x1+((x2-x1)/2), y1, x2, y1+((y2-y1)/2));
      line(x2, y1+((y2-y1)/2), x1+((x2-x1)/2), y2);
      line(x1+((x2-x1)/2), y1, x1, y1+((y2-y1)/2));
      line(x1, y1+((y2-y1)/2), x1+((x2-x1)/2), y2);
     }
     if(x1 > x2 && y1 > y2) {
      line(x1, y1-((y1-y2)/2), x1-((x1-x2)/2), y1);
      line(x1-((x1-x2)/2), y1, x2, y1-((y1-y2)/2));
      line(x2, y1-((y1-y2)/2), x1-((x1-x2)/2), y2);
      line(x1-((x1-x2)/2), y2, x1, y1-((y1-y2)/2));
     }
     if(x1 > x2 && y2 >= y1) {
      line(x1-((x1-x2)/2), y1, x1, y1+((y2-y1)/2));
      line(x1, y1+((y2-y1)/2), x1-((x1-x2)/2), y2);
      line(x1-((x1-x2)/2), y2, x2, y1+((y2-y1)/2));
      line(x2, y1+((y2-y1)/2), x1-((x1-x2)/2), y1);
     }
     if(x2 >= x1 && y1 > y2) {
      line(x2-((x2-x1)/2), y2, x2, y1-((y1-y2)/2));
      line(x2, y1-((y1-y2)/2), x2-((x2-x1)/2), y1);
      line(x2-((x2-x1)/2), y1, x1, y1-((y1-y2)/2));
      line(x1, y1-((y1-y2)/2), x2-((x2-x1)/2), y2);
     }
    }
    //////////////////////////////////////

    ////////for right triangle////////////
    if(b == 7) {
     line(x1, y2, x2, y2);
     line(x1, y2, x1, y1);
     line(x2, y2, x1, y1);
    }
    //////////////////////////////////////
    //setcolor(BLACK);
    //rectangle(x1, y1, x2, y2);
    setcolor(u);
    goto m;
   }

   else if (z == 0) {
    if (x > 160 && x < getmaxx()-50 && y > 41 && y < 249 && (b == 1 || ((b == 2 || b == 4) && htm == 0) || b == 3 || b == 5)) {
     x2 = x;
     y2 = y;
    }
    if ((b == 2 || b == 4) && htm == 1) {
     htm = 0;
    }
   }
   setfillstyle(SOLID_FILL, WHITE);
   if(b != 10) {
     putimage(160, 41, buf1, COPY_PUT);
     putimage(250, 41, buf2, COPY_PUT);
     putimage(320, 41, buf3, COPY_PUT);
     putimage(380, 41, buf4, COPY_PUT);
     putimage(420, 41, buf5, COPY_PUT);
     //putimage(545, 41, buf6, COPY_PUT);
     dat(0, 0, "right.dat");
   }
   free(buf1);
   free(buf2);
   free(buf3);
   free(buf4);
   free(buf5);
   remove("right.dat");
   //free(buf6);
   //////////////for line//////////////////
   if(b == 1) line(x1, y1, x2, y2);
   ////////////////////////////////////////

   //////////////for rectangle/////////////
   if(b == 3) rectangle(x1, y1, x2, y2);
   ////////////////////////////////////////

   //////////////for square////////////////
   if(b == 2) {
    rectangle(x1, y1, x2, y1+(x2-x1));
    y2 = y1+(x2-x1);
   }
   ////////////////////////////////////////

   //////////////for circle////////////////
   if(b == 4) {
     if(x2 >= x1) {
      circle(x1+((x2-x1)/2), y1, ((x2-x1)/2));
      i1 = x1+((x2-x1)/2);
      j1 = (x2-x1)/2;
     }
     else if(x2 < x1) {
      circle(x1-((x1-x2)/2), y1, ((x1-x2)/2));
      i1 = x1-((x1-x2)/2);
      j1 = (x1-x2)/2;
     }
    }
   ////////////////////////////////////////

   //////////////for ellipse///////////////
   if(b == 5) {
    if(x2 >= x1 && y2 >= y1) {
     ellipse(x1+((x2-x1)/2), y1+((y2-y1)/2), 0, 360, ((x2-x1)/2), ((y2-y1)/2));
     i1 = x1+((x2-x1)/2);
     j1 = y1+((y2-y1)/2);
     x = ((x2-x1)/2);
     y = ((y2-y1)/2);
    }
    else if(x2 >= x1 && y1 > y2) {
     ellipse(x1+((x2-x1)/2), y1-((y1-y2)/2), 0, 360, ((x2-x1)/2), ((y1-y2)/2));
     i1 = x1+((x2-x1)/2);
     j1 = y1-((y1-y2)/2);
     x =  ((x2-x1)/2);
     y =  ((y1-y2)/2);
    }
    else if(x1 > x2 && y2 >= y1) {
     ellipse(x1-((x1-x2)/2), y1+((y2-y1)/2), 0, 360, ((x1-x2)/2), ((y2-y1)/2));
     i1 = x1-((x1-x2)/2);
     j1 = y1+((y2-y1)/2);
     x =  ((x1-x2)/2);
     y =  ((y2-y1)/2);
    }
    else if(x1 > x2 && y1 > y2) {
     ellipse(x1-((x1-x2)/2), y1-((y1-y2)/2), 0, 360, ((x1-x2)/2), ((y1-y2)/2));
     i1 = x1-((x1-x2)/2);
     j1 = y1-((y1-y2)/2);
     x =  ((x1-x2)/2);
     y =  ((y1-y2)/2);
    }
   }
   ////////////////////////////////////////

   //////////////for triangle//////////////
    if (b == 6) {
     line(x1, y2, x2, y2);
     if(x2 >= x1) {
      line(x1, y2, x1+((x2-x1)/2), y1);
      line(x2, y2, x1+((x2-x1)/2), y1);
     }
     else {
      line(x1, y2, x1-((x1-x2)/2), y1);
      line(x2, y2, x1-((x1-x2)/2), y1);
     }
    }
   ////////////////////////////////////////

   //////////////for rhombus///////////////
    if(b == 8) {
     if(x2 >= x1 && y2 >= y1) {
      line(x1+((x2-x1)/2), y1, x2, y1+((y2-y1)/2));
      line(x2, y1+((y2-y1)/2), x1+((x2-x1)/2), y2);
      line(x1+((x2-x1)/2), y1, x1, y1+((y2-y1)/2));
      line(x1, y1+((y2-y1)/2), x1+((x2-x1)/2), y2);
     }
     if(x1 > x2 && y1 > y2) {
      line(x1, y1-((y1-y2)/2), x1-((x1-x2)/2), y1);
      line(x1-((x1-x2)/2), y1, x2, y1-((y1-y2)/2));
      line(x2, y1-((y1-y2)/2), x1-((x1-x2)/2), y2);
      line(x1-((x1-x2)/2), y2, x1, y1-((y1-y2)/2));
     }
     if(x1 > x2 && y2 >= y1) {
      line(x1-((x1-x2)/2), y1, x1, y1+((y2-y1)/2));
      line(x1, y1+((y2-y1)/2), x1-((x1-x2)/2), y2);
      line(x1-((x1-x2)/2), y2, x2, y1+((y2-y1)/2));
      line(x2, y1+((y2-y1)/2), x1-((x1-x2)/2), y1);
     }
     if(x2 >= x1 && y1 > y2) {
      line(x2-((x2-x1)/2), y2, x2, y1-((y1-y2)/2));
      line(x2, y1-((y1-y2)/2), x2-((x2-x1)/2), y1);
      line(x2-((x2-x1)/2), y1, x1, y1-((y1-y2)/2));
      line(x1, y1-((y1-y2)/2), x2-((x2-x1)/2), y2);
     }
    }
   ////////////////////////////////////////

   //////////////for right triangle////////
   if(b == 7) {
     line(x1, y2, x2, y2);
     line(x1, y2, x1, y1);
     line(x2, y2, x1, y1);
    }
   ////////////////////////////////////////
   if(b == 1) {
    copy_file("line.txt", "line_undo.txt", 'a');
    line_out(x1, y1, x2, y2, u, kgf1);
   }
   if(b < 4 && b > 1) {
    copy_file("rect.txt", "rect_undo.txt", 'a');
    rect_out(x1, y1, x2, y2, u, kgf1);
   }
   if(b == 4) {
    copy_file("ell.txt", "ell_undo.txt", 'a');
    ell_out(i1, y1, j1, j1, u, kgf1);
   }
   if(b == 5) {
    copy_file("ell.txt", "ell_undo.txt", 'a');
    ell_out(i1, j1, x, y, u, kgf1);
   }
   if(b == 6) {
     copy_file("line.txt", "line_undo.txt", 'a');
     line_out(x1, y2, x2, y2, u, kgf1);
     if(x2 >= x1) {
      line_out(x1, y2, x1+((x2-x1)/2), y1, u, kgf1);
      line_out(x2, y2, x1+((x2-x1)/2), y1, u, kgf1);
     }
     else {
      line_out(x1, y2, x1-((x1-x2)/2), y1, u, kgf1);
      line_out(x2, y2, x1-((x1-x2)/2), y1, u, kgf1);
     }
   }
   if(b == 7) {
     copy_file("line.txt", "line_undo.txt", 'a');
     line_out(x1, y2, x2, y2, u, kgf1);
     line_out(x1, y2, x1, y1, u, kgf1);
     line_out(x2, y2, x1, y1, u, kgf1);
   }
   if(b == 8) {
     copy_file("line.txt", "line_undo.txt", 'a');
     if(x2 >= x1 && y2 >= y1) {
      line_out(x1+((x2-x1)/2), y1, x2, y1+((y2-y1)/2), u, kgf1);
      line_out(x2, y1+((y2-y1)/2), x1+((x2-x1)/2), y2, u, kgf1);
      line_out(x1+((x2-x1)/2), y1, x1, y1+((y2-y1)/2), u, kgf1);
      line_out(x1, y1+((y2-y1)/2), x1+((x2-x1)/2), y2, u, kgf1);
     }
     if(x1 > x2 && y1 > y2) {
      line_out(x1, y1-((y1-y2)/2), x1-((x1-x2)/2), y1, u, kgf1);
      line_out(x1-((x1-x2)/2), y1, x2, y1-((y1-y2)/2), u, kgf1);
      line_out(x2, y1-((y1-y2)/2), x1-((x1-x2)/2), y2, u, kgf1);
      line_out(x1-((x1-x2)/2), y2, x1, y1-((y1-y2)/2), u, kgf1);
     }
     if(x1 > x2 && y2 >= y1) {
      line_out(x1-((x1-x2)/2), y1, x1, y1+((y2-y1)/2), u, kgf1);
      line_out(x1, y1+((y2-y1)/2), x1-((x1-x2)/2), y2, u, kgf1);
      line_out(x1-((x1-x2)/2), y2, x2, y1+((y2-y1)/2), u, kgf1);
      line_out(x2, y1+((y2-y1)/2), x1-((x1-x2)/2), y1, u, kgf1);
     }
     if(x2 >= x1 && y1 > y2) {
      line_out(x2-((x2-x1)/2), y2, x2, y1-((y1-y2)/2), u, kgf1);
      line_out(x2, y1-((y1-y2)/2), x2-((x2-x1)/2), y1, u, kgf1);
      line_out(x2-((x2-x1)/2), y1, x1, y1-((y1-y2)/2), u, kgf1);
      line_out(x1, y1-((y1-y2)/2), x2-((x2-x1)/2), y2, u, kgf1);
     }
   }
   i.x.ax=1;
   int86(51,&i,&o);
  }
  else if (b == 9 && x > 159 && x < getmaxx()-49 && y > 40 && y < 250) {
   copy_file("rect.txt", "rect_undo.txt", 'a');
   copy_file("ell.txt", "ell_undo.txt", 'a');
   copy_file("line.txt", "line_undo.txt", 'a');
   fill_col(u);
  }
  else if (b == 10 && x > 159 && x < getmaxx()-49 && y > 40 && y < 250) {
   pen_draw(u);
  }
  k++;
  l = 0;
  if(b != 11) {
   rename("current.dat", "undo1.dat");
   rename("undo.dat", "current.dat");
   rename("undo1.dat", "undo.dat");
   i.x.ax=2;
   int86(51,&i,&o);
   bmp_to_dat("current.dat", 159, 40, getmaxx()-49, 250);
   i.x.ax=1;
   int86(51,&i,&o);
  }
  goto n;
  }
  goto n;
  l:
  del_files();      //to delete all binary files used
  closegraph();
}