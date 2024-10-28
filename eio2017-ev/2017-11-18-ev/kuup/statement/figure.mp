u := .75cm;

def square(expr x, y) =
  draw ((x,y)--(x+1,y)--(x+1,y+1)--(x,y+1)--cycle) scaled u;
  label(decimal(x)&","&decimal(y), (x+.5,y+.5) scaled u);
enddef;

def ribbon(expr x, y)(text d) =
  if d = "N": draw ((x+0.0,y+1.0)--(x+0.2,y+1.2)--(x+0.8,y+1.2)--(x+1.0,y+1.0)) scaled u; fi
  if d = "E": draw ((x+1.0,y+1.0)--(x+1.2,y+0.8)--(x+1.2,y+0.2)--(x+1.0,y+0.0)) scaled u; fi
  if d = "S": draw ((x+0.0,y+0.0)--(x+0.2,y-0.2)--(x+0.8,y-0.2)--(x+1.0,y+0.0)) scaled u; fi
  if d = "W": draw ((x+0.0,y+0.0)--(x-0.2,y+0.2)--(x-0.2,y+0.8)--(x+0.0,y+1.0)) scaled u; fi
enddef;

beginfig(0);
  square(3,1);
  square(3,2);
  square(4,2);
  square(2,3);
  square(3,3);
  square(2,4);
  ribbon(4,2,"N");
  ribbon(4,2,"S");
  ribbon(4,2,"E");
  ribbon(3,1,"W");
  ribbon(3,1,"S");
  ribbon(3,2,"W");
  ribbon(3,3,"N");
endfig;

beginfig(1);
  square(1,2);
  square(2,2);
  square(3,2);
  square(4,2);
  square(2,3);
  square(4,3);
endfig;

end
