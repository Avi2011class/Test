uses events, graphabc, crt, timers;
const N=20;
const Step=20;
const delay=50;
const walls=false;
type point=record; x:integer; y:integer; end;

type zm=record; loc:array[1..10000] of point; len:integer; vector:integer; end;

var z:zm; t:timer; eda:point; b:boolean; i:integer;
procedure pole; var i,j:integer; begin setwindowheight(step*(n+3)); setwindowwidth(step*(n+3)); for i:=1 to N do begin line(Step,i*step,Step*N,i*step); line(i*step,Step,i*step,Step*N); end; end;
procedure KeyPress(ch:char); begin if ch='w' then z.vector:=1; if ch='d' then z.vector:=2; if ch='s' then z.vector:=3; if ch='a' then z.vector:=4; end;
procedure DrawSqr(p:point); begin setbrushcolor(rgb(255,0,0)); fillrect(step*p.x+2,step*p.y+1,step*p.x+step-1,step*p.y+step-1); end;
procedure DeleteSqr(p:point); begin setbrushcolor(rgb(255,255,255)); fillrect(step*p.x+1,step*p.y+1,step*p.x+step-1,step*p.y+step-1); end;
procedure DrawEat(p:point); begin setbrushcolor(rgb(0,255,0)); fillrect(step*p.x+2,step*p.y+1,step*p.x+step-1,step*p.y+step-1); end;
function death(n:point):boolean; begin b:=false; for i:=1 to z.len do if (n.x=z.loc[i].x) and (n.y=z.loc[i].y) then b:=true; death:=b; end;

procedure tick;
var i:integer;
next:point;
b:boolean;
begin
  next:=z.loc[1];
 if z.vector=1 then next.y:=z.loc[1].y-1;
 if z.vector=2 then next.x:=z.loc[1].x+1;
 if z.vector=3 then next.y:=z.loc[1].y+1;
 if z.vector=4 then next.x:=z.loc[1].x-1;

 if (next.x=eda.x) and (next.y=eda.y) then
 begin
   for i:=z.len+1 downto 2 do z.loc[i]:=z.loc[i-1];
   z.loc[1]:=eda;
   z.len:=z.len+1;
   drawsqr(eda);
 repeat
  eda.x:=random(n-1)+1;
  eda.y:=random(n-1)+1;
  b:=true;
  for i:=1 to z.len do if (eda.x=z.loc[i].x) and (eda.y=z.loc[i].y) then b:=false;
 until b;
 draweat(eda);
 end

 else begin
 if ((walls) and ((next.x=0) or (next.y=0) or (next.x=n) or (next.y=n))) or(death(next)) then begin t.stop; writeln('Проиграл! Днина змейки равна ',z.len) end
 else begin
 deletesqr(z.loc[z.len]);
 for i:=z.len downto 2 do z.loc[i]:=z.loc[i-1];
 if next.x=0 then next.x:=n-1;
 if next.y=0 then next.y:=n-1;
 if next.x=n then next.x:=1;
 if next.y=n then next.y:=1;
 z.loc[1]:=next;
 drawsqr(z.loc[1]);
 end;
 end;
end;

begin
pole; z.loc[1].x:=2; z.loc[1].y:=2; z.vector:=3; z.len:=3;
 repeat
  eda.x:=random(n-1)+1; eda.y:=random(n-1)+1; b:=true;
  for i:=1 to z.len do if (eda.x=z.loc[i].x) and (eda.y=z.loc[i].y) then b:=false;
 until b;
 draweat(eda);

t:=Timer.Create(delay,tick);
OnKeyPress:=KeyPress;

end.