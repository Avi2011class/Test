uses crt, graphabc;
const T = 200; N = 10;
var i, j, i1, j1, mn:integer;
var alpha:real;
type ColorType=integer;
type Point = record; x,  y:integer; end;
type Point3D = record; x,  y:integer; end;

const Lx = -100; Ly = -100; Lz = -100;

procedure osi;
begin
    setpenwidth(3);
    line(400, 0, 400, 800);
    line(0, 400, 800, 400);
    line(800, 0, 0, 800);
end;

function to2DX(x, y, z:integer; phi:real):integer;
var x1,  y1,  z1: integer;
begin
    x1 := trunc( x * cos(phi) - y * sin(phi) );
    y1 := trunc( x * sin(phi) + y * cos(phi) );
    z1 := z;
    to2DX := 400 + y1 - trunc(0.3 * x1);
end;
 
function to2DY(x, y, z:integer; phi:real):integer;
var x1,  y1,  z1: integer;
begin
    x := trunc( x * cos(phi) - y * sin(phi) );
    y := trunc( x * sin(phi) + y * cos(phi) );
    z1 := z;
    to2DY := 400 - z + trunc(0.4 * x);
end;

procedure line3d(x, y, z, x1, y1, z1:integer; phi:real);
begin
 line(to2DX(x, y, z,  phi),  to2Dy(x, y, z,  phi),  to2DX(x1, y1, z1,  phi),  to2Dy(x1, y1, z1,  phi))
end;

procedure lineto3d(x1, y1, z1:integer; phi:real);
begin
 lineto(to2DX(x1, y1, z1,  phi), to2Dy(x1, y1, z1,  phi))
end;

procedure moveto3d(x1, y1, z1:integer; phi:real);
begin
 moveto(to2DX(x1, y1, z1,  phi), to2Dy(x1, y1, z1,  phi))
end;

procedure drawTriangle(x1,  y1,  z1,  x2,  y2,  z2,  x3,  y3,  z3 : integer; phi:real);
var Triangle : array[1..3] of Point;
var nx, ny,  nz : real;
var CS, S : real;
begin
     Triangle[1].x := to2dx(x1,  y1,  z1,  phi); Triangle[1].y := to2dy(x1,  y1,  z1,  phi);
     Triangle[2].x := to2dx(x2,  y2,  z2,  phi); Triangle[2].y := to2dy(x2,  y2,  z2,  phi);
     Triangle[3].x := to2dx(x3,  y3,  z3,  phi); Triangle[3].y := to2dy(x3,  y3,  z3,  phi);
     x1 := x3 - x1; y1 := y3 - y1; z3 := z3 - z1;
     x2 := x3 - x2; y2 := y3 - y2; z3 := z3 - z2;
     nx := y1 * z2 - y2 * z1;
     ny := z1 * x2 - z2 * x1;
     nz := x1 * y2 - x2 * y1;

     try
         CS := abs(      (nx * Lx + ny * Ly + nz * Lz) / sqrt(nx*nx + ny*ny + nz*nz) / sqrt(Lx*Lx + Ly*ly + Lz*Lz)      );
         setbrushcolor(rgb(trunc(100 * CS),  trunc(100 * CS),  trunc(100 * CS)));
         setpencolor(rgb(trunc(100 * CS),  trunc(100 * CS),  trunc(100 * CS)));
         Polygon(Triangle,  3);
     except
     end;
end;


procedure draw(f: function(x, y:real):real; color1:colortype; phi:real);
begin
    setpenwidth(1);
    setpencolor(color1);
    for j1:=-trunc(T/N) to trunc(T/N) do
    begin
        j:=j1*N;
        moveto3d(j, -T, trunc(f(j, -T)),  phi);
        for i1:=-trunc(T/N) to trunc(T/N) do
        begin
            i:=i1*N;
            lineto3d(j, i, trunc(f(j, i)),  phi);
        end;

        end;
        for i1:=-trunc(T/N) to trunc(T/N) do
        begin
            i:=i1*N;
            moveto3d(-T, i, trunc(f(-T, i)),  phi);
            for j1:=-trunc(T/N) to trunc(T/N) do
            begin
                j:=j1*N;
                lineto3d(j, i, trunc(f(j, i)),  phi);
            end;

    end;
end;


function p(x, y:real):real;
var a:integer;
begin
    try
     //p:=50*((sin(x/100)+sin(y/100)));   //сама функция двух аргументов
        p:=sqrt(90000 - x*x - y*y)/8 /((sin(x/100)+sin(y/100)))/30;
    except
        p:=1;
    end;
end;

function q(x, y:real):real;
var a:integer;
begin
    try
        q := sqrt(10000 - x * x - y * y) * sin((x - y) / 100); {сама функция двух аргументов}
    except
        q := 1;
    end;
end;

////////////////////////////////////////////////////////////////////////////////////////////////////
begin
    lockdrawing;
    setwindowheight(800);
    setwindowwidth(800);
    alpha := 0;
    while true do
    begin
        clearwindow();
        draw(p,  rgb(255,  0,  0),  alpha);
        //draw(q,  rgb(255,  0,  0),  -alpha);
        redraw;
        alpha := alpha - 0.04;
        delay(0);
    end;
end.


