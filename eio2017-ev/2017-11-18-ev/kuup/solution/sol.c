#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define PSIZE 12


char d[4] = {'N', 'E', 'S', 'W'};


int xx[10][7][3] = {

                  {{0,0,0}, {1,0,0}, {1,1,0}, {2,1,0}, {2,2,0}, {3,2,0}, {0,0,0}},

                  {{1,0,0}, {0,1,0}, {1,1,0}, {2,1,0}, {3,1,0}, {1,2,0}, {0,0,0}},
                  {{1,0,0}, {0,1,0}, {1,1,0}, {2,1,0}, {3,1,0}, {0,2,0}, {0,0,0}},
                  {{2,0,0}, {0,1,0}, {1,1,0}, {2,1,0}, {3,1,0}, {0,2,0}, {0,0,0}},
                  {{3,0,0}, {0,1,0}, {1,1,0}, {2,1,0}, {3,1,0}, {0,2,0}, {0,0,0}},

		  {{1,0,0}, {0,1,0}, {1,1,0}, {1,2,0}, {2,2,0}, {2,3,0}, {0,0,0}},
		  {{1,0,0}, {0,2,0}, {1,1,0}, {1,2,0}, {2,2,0}, {2,3,0}, {0,0,0}},
		  {{1,0,0}, {2,0,0}, {1,1,0}, {0,2,0}, {1,2,0}, {0,3,0}, {0,0,0}},

		  {{2,0,0}, {0,1,0}, {1,1,0}, {2,1,0}, {3,1,0}, {1,2,0}, {0,0,0}},
		  {{0,0,0}, {0,1,0}, {0,2,0}, {1,1,0}, {2,1,0}, {3,1,0}, {0,0,0}}
                  };




int ribad[10][7][3] = {
		{{0,0,0}, {0,0,2}, {0,0,3}, {1,0,1}, {1,0,2}, {2,1,1}, {1,1,0}},

		{{1,0,1}, {1,0,2}, {1,0,3}, {0,1,3}, {1,2,0}, {1,2,1}, {1,2,3}},
		{{1,0,1}, {1,0,2}, {1,0,3}, {0,1,3}, {0,2,0}, {0,2,1}, {0,2,3}},
		{{2,0,1}, {2,0,2}, {2,0,3}, {0,1,3}, {0,2,0}, {0,2,1}, {0,2,3}},
	        {{3,0,1}, {3,0,2}, {3,0,3}, {0,1,3}, {0,2,0}, {0,2,1}, {0,2,3}},

		{{0,1,0}, {0,1,2}, {0,1,3}, {1,0,1}, {1,0,2}, {1,1,1}, {1,2,0}},
		{{1,0,1}, {1,0,2}, {1,0,3}, {1,1,1}, {1,1,3}, {0,2,0}, {1,2,0}},
                {{1,0,3}, {1,0,2}, {2,0,0}, {2,0,1}, {2,0,2}, {1,1,3}, {1,2,0}},


		{{2,0,1}, {2,0,2}, {2,0,3}, {0,1,3}, {1,2,0}, {1,2,1}, {1,2,3}},
		{{0,2,0}, {0,2,1}, {0,2,3}, {0,1,3}, {0,0,1}, {0,0,2}, {0,0,3}}
};


// 
int comp(int a[7][3], int b[7][3]) {
	int b1[6] = {0,0,0,0,0,0};
	int b2[6] = {0,0,0,0,0,0};
	int j,i;	
	for (i=0;i<6;i++) 
		for (j=0;j<6;j++) 
			if ((a[i][0] == b[j][0]) && (a[i][1] == b[j][1])) {
				b1[i] = 1;
				b2[j] = 1;
			}
	for (j=0;j<6;j++)
		if ((b1[j] == 0) || (b2[j] == 0)) 
			return 0;
	return 1;
}

void rotate(int k[7][3]) {
	int w;
	for (w=0;w<7;w++) {
		int x,y;
		x = k[w][1];
		y = PSIZE - k[w][0] - 1;
		k[w][0] = x;
		k[w][1] = y;
		k[w][2] = (k[w][2] + 1)  % 4;
	}
}

void mirror(int k[7][3]) {
	int w;	
	int o;
	for (w=0;w<7;w++) {
		k[w][1] = PSIZE - k[w][1]  - 1;
		o = k[w][2];
		if (k[w][2] == 0) 
			o = 2;
		if (k[w][2] == 2)
			o = 0;
		k[w][2] = o;
	}
}

int minx(int k[7][3]) {
	int m;
	int w;
	m = k[0][0];
	for (w=1;w<6;w++) 
		if (m > k[w][0]) 
			m = k[w][0];
	return m;
}

int miny(int k[7][3]) {
	int m;
	int w;
	m = k[0][1];
	for (w=1;w<6;w++) 
		if (m > k[w][1]) 
			m = k[w][1];
	return m;
}

void shift(int x,int y,int k[7][3]) {
	int w;
	for (w=0;w<7;w++) {
		k[w][0]-=x;
		k[w][1]-=y;
	}
}


int sisend[7][3];
int var[7][3];


int main() {

	FILE *f, *fo;
	int w,i,m,r;
	int rot2;

	f =  fopen("kuupsis.txt","r");
	fo = fopen("kuupval.txt","w");
	for (w=0;w<6;w++) {
		fscanf(f,"%d %d\n",&sisend[w][0],&sisend[w][1]);
	}
	for (i=0;i<10;i++) { 		        // variandi nr
		for (m=0;m<2;m++)  {            // mirror yes/no
			for (r=0;r<4;r++) {     // poorete arv
				memcpy(var,sisend, 6 * 3 * sizeof(int));
				if (m==1) mirror(var);
				if (r>=3) rotate(var);
				if (r>=2) rotate(var);
				if (r>=1) rotate(var);
				int x = minx(var);
				int y = miny(var);
				shift(x,y,var);
				if (comp(var,xx[i])) {
					fprintf(fo,"JAH\n");
					shift(-x,-y,ribad[i]);		
					for (rot2=r; rot2 < 4; rot2++) {
						rotate(ribad[i]);
					}
					if (m==1) 
						mirror(ribad[i]);

					for (rot2=0;rot2<7;rot2++)  
						fprintf(fo,"%d %d %c\n", ribad[i][rot2][0], ribad[i][rot2][1], d[ribad[i][rot2][2]]);
					fclose(fo);
					exit(0);
				} 
				
			}
		}
	}
	fprintf(fo,"EI\n");
	fclose(fo);

}
