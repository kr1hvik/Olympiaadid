u := 1cm;

beginfig(0);
  drawarrow ((0,0)--(8,0)) scaled u;
  for x = 1 upto 7: draw ((x,0)--(x,-.1)) scaled u; endfor
  drawarrow ((0,0)--(0,6)) scaled u;
  for y = 1 upto 5: draw ((0,y)--(-.1,y)) scaled u; endfor
  draw ((1,2)--(2,1)--(3,3)--(4,2)--(5,4)--(6,5)--(7,3)) scaled u;
  draw ((2,1)--(3,1)) scaled u dashed evenly;
  drawdblarrow ((3,1)--(3,3)) scaled u dashed evenly;
  label.rt("2",.5[(3,1),(3,3)] scaled u);
  draw ((4,2)--(6,2)) scaled u dashed evenly;
  drawdblarrow ((6,2)--(6,5)) scaled u dashed evenly;
  label.rt("3",.5[(6,2),(6,5)] scaled u);
endfig;

end
