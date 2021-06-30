#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include "graphics.h"
#include "genlib.h"
#include "conio.h"

#include <windows.h>
#include <olectl.h>
#include <stdio.h>
#include <mmsystem.h>
#include <wingdi.h>
#include <ole2.h>
#include <ocidl.h>
#include <winuser.h>

#define Max 100
#define Ratio 0.9
#define Extra 2
#define Bottom 1
#define WordWidth 0.2

int num=0, index_i=0, index_j=0, index_done=0, order=-1, algo=-1,selectNum=0,save=0;
int merge_len = 1;
double width, ratio_height;
double data[Max] = {-1};
char datac[Max][10];

void GetChar (){
	char datatype[10]; 
	FILE* fp; 
	if ((fp = fopen("data.txt","a+")) != NULL) {
		fscanf (fp,"%s",datatype);
		while (!feof(fp)){
			fscanf (fp,"%s",datac[num]);
			num++;
		}
	}
	fclose(fp);
}

void GetDouble (){
	int i=0;
	while (i<num) {
		data[i] = atof (datac[i]);
		i++;
	}
}

void GetBasicParameter (){
	double max_height = 0;
	int i=0;
	while (i<num) {
		if (data[i] > max_height) max_height = data[i];
		i++;
	}
	ratio_height = Ratio*(GetWindowHeight()-Bottom)/max_height;
	width = GetWindowWidth() / (num+Extra);
}

void DrawBox (double x, double y, double height){
    MovePen(x, y);
    DrawLine(0, height);
    DrawLine(width, 0);
    DrawLine(0, -height);
    DrawLine(-width, 0); 
}


void DrawBGraphics (int number){
	int i;
	SetPenColor("Black");
	for (i = 0; i<number; i++) {
		DrawBox (width*(i+1), Bottom, data[i]*ratio_height);
		MovePen (width*(i+1.5)-WordWidth, Bottom-WordWidth);
		DrawTextString (datac[i]); 
	}
}


void DrawRGraphicsSelect (int number) {
	int i;
	SetPenColor("Red");
	for (i = 0; i<number; i++) {
		DrawBox (width*(i+1), Bottom, data[i]*ratio_height);
		MovePen (width*(i+1.5)-WordWidth, Bottom-WordWidth);
		DrawTextString (datac[i]); 
	}
} 

void DrawBGraphicsSelect (int number){
	int i = num-number;
	SetPenColor("Black");
	for (i; i<num; i++){
		DrawBox (width*(i+1), Bottom, data[i]*ratio_height);
		MovePen (width*(i+1.5)-WordWidth, Bottom-WordWidth);
		DrawTextString (datac[i]); 
	}
}


void DrawRGraphics (int number) {
	int i = num-number;
	SetPenColor("Red");
	for (i; i<num; i++){
		DrawBox (width*(i+1), Bottom, data[i]*ratio_height);
		MovePen (width*(i+1.5)-WordWidth, Bottom-WordWidth);
		DrawTextString (datac[i]); 
	}
} 

void DrawWGraphics (int i) {
	SetPenColor("White");
	DrawBox (width*(i+1), Bottom, data[i]*ratio_height);
	MovePen (width*(i+1.5)-WordWidth, Bottom-WordWidth);
	DrawTextString (datac[i]); 
	DrawBox (width*(i+2), Bottom, data[i+1]*ratio_height);
	MovePen (width*(i+2.5)-WordWidth, Bottom-WordWidth);
	DrawTextString (datac[i+1]);
}

void DrawRTriangle (int i){
	SetPenColor("Red");
	MovePen(width*(i+1.5)-WordWidth/2, Bottom-2*WordWidth);
	DrawLine(WordWidth, 0);
    DrawLine(-WordWidth/2, WordWidth);
    DrawLine(-WordWidth/2, -WordWidth);
    MovePen(width*(i+2.5)-WordWidth/2, Bottom-2*WordWidth);
    DrawLine(WordWidth, 0);
    DrawLine(-WordWidth/2, WordWidth);
    DrawLine(-WordWidth/2, -WordWidth);
}
void DrawRTriangleSelect (int i,int j){
	SetPenColor("Red");
	MovePen(width*(i+1.5)-WordWidth/2, Bottom-2*WordWidth);
	DrawLine(WordWidth, 0);
    DrawLine(-WordWidth/2, WordWidth);
    DrawLine(-WordWidth/2, -WordWidth);
    MovePen(width*(j+1.5)-WordWidth/2, Bottom-2*WordWidth);
    DrawLine(WordWidth, 0);
    DrawLine(-WordWidth/2, WordWidth);
    DrawLine(-WordWidth/2, -WordWidth);
}


void DrawWTriangle (int i){
	SetPenColor("White");
	MovePen(width*(i+1.5)-WordWidth, Bottom-2*WordWidth);
	DrawLine(WordWidth*2, 0);
    DrawLine(-WordWidth, WordWidth);
    DrawLine(-WordWidth, -WordWidth);
}

void DrawWMergeGraphics (int i) {	
	SetPenColor("White");
	for (i = 0; i<num; i++) {
		DrawBox (width*(i+1), Bottom, data[i]*ratio_height);
		MovePen (width*(i+1.5)-WordWidth, Bottom-WordWidth);
		DrawTextString (datac[i]); 
	}
	//DrawTextString (datac[i]); 
}

void DrawBMergeGraphics (int i) {	
	SetPenColor("Black");
	for (i = 0; i<num; i++) {
		DrawBox (width*(i+1), Bottom, data[i]*ratio_height);
		MovePen (width*(i+1.5)-WordWidth, Bottom-WordWidth);
		DrawTextString (datac[i]); 
	}
	//DrawTextString (datac[i]);  
}

void DrawMergeGraphics (int len) {
	bool setColor = 0;
	int i=0, j=0, h=0;	
	SetPenColor("Black");
	for (h = 0; h<num/len; h++) {
		j=0;
		if(setColor == 0)SetPenColor("Black");
		else SetPenColor("Red");
		setColor = !setColor;
		for(j = 0; j<len; j++){
			i = h*len + j;
			DrawBox (width*(i+1), Bottom, data[i]*ratio_height);
			MovePen (width*(i+1.5)-WordWidth, Bottom-WordWidth);
			DrawTextString (datac[i]);
		}
	}
	i = i+1;
	if(setColor == 0)SetPenColor("Black");
	else SetPenColor("Red");
	for (; i<num; i++){
		DrawBox (width*(i+1), Bottom, data[i]*ratio_height);
		MovePen (width*(i+1.5)-WordWidth, Bottom-WordWidth);
		DrawTextString (datac[i]);
	}
}

void DrawAllTxt () {
	int i = 0;
	SetPenColor("Black");
	for (i = 0; i<num; i++){
		MovePen (width*(i+1.5)-WordWidth, Bottom-WordWidth);
		DrawTextString (datac[i]); 
	}
}

void BubbleSortSingle (int i){
	double temp;
	char tempc[10]; 
	temp = data[i];
	data[i] = data[i + 1];
	data[i + 1] = temp;
	strcpy (tempc, datac[i]);
	strcpy (datac[i], datac[i+1]);
	strcpy (datac[i+1], tempc);
}
//selection sort swap
void swap(char *xp, char *yp)
{
	char temp = *xp;
	*xp = *yp;
	*yp = temp;
}
//selection sort algo
void SelectionSort(){
	
	char arr[10];
	int i, j, min_idx, n = sizeof(arr);

	// One by one move boundary of unsorted subarray
	for (i = 0; i < n-1; i++)
	{
		// Find the minimum element in unsorted array
		min_idx = i;
		for (j = i+1; j < n; j++)
		if (arr[j] < arr[min_idx])
			min_idx = j;

		// Swap the found minimum element with the first element
		swap(&arr[min_idx], &arr[i]);
	}
}




static void mergeAsc(int lb,int mid,int ub) {
	int n1=mid-lb+1;
	int n2=ub-mid;
	double L[Max] = {0};
	double R[Max] = {0};
	char Lc[Max][10] = {0}, Rc[Max][10] = {0};
	int i=0;
	for(i=0;i<n1;i++) {
		L[i]=data[lb+i];
		strcpy (Lc[i], datac[lb+i]);
	}
	for(i=0;i<n2;i++) {
		R[i]=data[mid+1+i];
		strcpy (Rc[i], datac[mid+1+i]);
	}
	L[n1]=R[n2]=100000;
	i=0;
	int k=0,j=0;
	for(k=lb;k<=ub;k++) {
		if(L[i]<=R[j]) {
			data[k]=L[i];
			strcpy (datac[k], Lc[i]);
			i++;
		}else {
			data[k]=R[j];
			strcpy (datac[k], Rc[j]);
			j++;
		}
	}
}

static void mergeDes(int lb,int mid,int ub) {
	int n1=mid-lb+1;
	int n2=ub-mid;
	double L[100] = {0};
	double R[100] = {0};
	char Lc[Max][10] = {0}, Rc[Max][10] = {0};
	int i=0;
	for(i=0;i<n1;i++) {
		L[i]=data[lb+i];
		strcpy (Lc[i], datac[lb+i]);
	}
	for(i=0;i<n2;i++) {
		R[i]=data[mid+1+i];
		strcpy (Rc[i], datac[mid+1+i]);
	}
	L[n1]=R[n2]=-1;
	i=0;
	int k=0,j=0;
	for(k=lb;k<=ub;k++) {
		if(L[i]<=R[j]) {
			data[k]=R[j];
			strcpy (datac[k], Rc[j]);
			j++;
		}else {
			data[k]=L[i];
			strcpy (datac[k], Lc[i]);
			i++;
		}
	}
}

void KeyboardEventProcess(int key, int event){
	switch (event) {
		case KEY_DOWN:	break;
		case KEY_UP:{
			if (key == 97){
				order = 1;
			}
			else if (key == 96) {
				order = 0;
			}
			
			if (key == 100) algo = 4; 
			else if(key == 101) algo = 5;
			else if(key == 102) algo = 6;
			if(key == 103){
				FILE *fp;
    			int i;
    			fp=fopen("save.txt","wb");
    			if(fp==NULL) 
    			{
        			printf("File cannot open! " );
        			exit(0);
    			}
    			for(i=0; i<num; i++)
    			{
        			fprintf(fp,"%f\t", data[i]);
    			}
    			fclose(fp);
			}
			break;
		}
	}
}

void MouseEventProcess(int x, int y, int button, int event) {
	switch (event) {
		case MOUSEMOVE: break;
		case BUTTON_DOWN: break;
		case BUTTON_UP: 
			if (button == RIGHT_BUTTON && order == 1 && algo == 4) {
				int i, j;
				double temp;
				char tempc[10]; 
		    	InitGraphics();
		    	for (j = 0; j<num-1; j++) 
					for (i = 0; i<num-1-j; i++) 
						if (data[i] > data[i+1]) {
							temp = data[i];
							data[i] = data[i+1];
							data[i+1] = temp;
							strcpy (tempc, datac[i]);
							strcpy (datac[i], datac[i+1]);
							strcpy (datac[i+1], tempc);
						}
		    	DrawRGraphics(num);
		    	break;
			}
			else if (button == RIGHT_BUTTON && order == 0 && algo == 4) {
				int i, j;
				double temp;
				char tempc[10]; 
		    	InitGraphics();
		    	for (j = 0; j<num-1; j++) 
					for (i = 0; i<num-1-j; i++) 
						if (data[i] < data[i+1]) {
							temp = data[i];
							data[i] = data[i+1];
							data[i+1] = temp;
							strcpy (tempc, datac[i]);
							strcpy (datac[i], datac[i+1]);
							strcpy (datac[i+1], tempc);
						}
		    	DrawRGraphics(num);
		    	break;
			}
	     	else if (button == LEFT_BUTTON && order == 1 && algo == 4) {	
			    InitGraphics();
	     		DrawBGraphics(num-index_done);
	     		DrawRGraphics(index_done);
				DrawRTriangle(index_i);	     		
	     		if (data[index_i] > data[index_i + 1]) {
		    		DrawWGraphics (index_i);		    		
		    		BubbleSortSingle (index_i);
	    		}
	    		DrawBGraphics (num-index_done);
	    		DrawRGraphics (index_done);
	    		DrawAllTxt;
			}
			else if (button == LEFT_BUTTON && order == 0 && algo == 4) {
				InitGraphics();
	     		DrawBGraphics(num-index_done);
	     		DrawRGraphics(index_done);
				DrawRTriangle(index_i);	 
				if (data[index_i] < data[index_i + 1]) {
		    		DrawWGraphics (index_i);
		    		BubbleSortSingle (index_i);
	    		}
	    		DrawBGraphics (num-index_done);
	    		DrawRGraphics (index_done);
	    		DrawAllTxt;
			}
			else if (button == RIGHT_BUTTON && order == 1 && algo == 5) {
		    	InitGraphics();
		    	int len=1;
		    	int i=0;
				while(len<=num) {//while
					for(i=0;i+len<num;i+=len*2) {
						int lb=i,ub=i+len*2-1,mid=i+len-1;
							if(ub>num-1) {
								ub=num-1;
							}
						mergeAsc(lb,mid,ub);
					}
					len*=2;
				}
				
				
		    	DrawRGraphics(num);
		    	break;
			}
			else if (button == RIGHT_BUTTON && order == 0 && algo == 5) {
				InitGraphics();
		    	int len=1;
		    	int i=0;
				while(len<=num) {//while
					for(i=0;i+len<num;i+=len*2) {
						int lb=i,ub=i+len*2-1,mid=i+len-1;
							if(ub>num-1) {
								ub=num-1;//
							}
						mergeDes(lb,mid,ub);
					}
					len*=2;
				}
				
				
		    	DrawRGraphics(num);
		    	break;
			}
			else if (button == LEFT_BUTTON && order == 1 && algo == 5) {	
			    InitGraphics();
			    DrawWMergeGraphics(num);
			    int i=0;
			    if(merge_len <= num){
//			    	DrawMergeGraphics(merge_len);
			    	for(i=0;i+merge_len<num;i+=merge_len*2) {
						int lb=i,ub=i+merge_len*2-1,mid=i+merge_len-1;
							if(ub>num-1) {
								ub=num-1;
							}
						mergeAsc(lb,mid,ub);
					}
			    	merge_len *= 2;
			    	if(merge_len <= num)DrawMergeGraphics(merge_len);
			    	else DrawBMergeGraphics(num);
				}
	     		else DrawBMergeGraphics(num);
	    		DrawAllTxt;
			}
			else if (button == LEFT_BUTTON && order == 0 && algo == 5) {
				InitGraphics();
			    DrawWMergeGraphics(num);
			    int i=0;
			    if(merge_len <= num){
//			    	DrawMergeGraphics(merge_len);
			    	for(i=0;i+merge_len<num;i+=merge_len*2) {
						int lb=i,ub=i+merge_len*2-1,mid=i+merge_len-1;
							if(ub>num-1) {
								ub=num-1;
							}
						mergeDes(lb,mid,ub);
					}
			    	merge_len *= 2;
			    	if(merge_len <= num)DrawMergeGraphics(merge_len);
			    	else DrawBMergeGraphics(num);
				}
	     		else DrawBMergeGraphics(num);
	    		DrawAllTxt;
			}
			else if (button == RIGHT_BUTTON && order == 0 && algo == 6) {
				int i, j,flg;
				double temp;
				char tempc[10]; 
		    	InitGraphics();
		    	for (j = 0; j<num; j++) {
		    		temp=data[j];
		    		flg=j;
					for (i = j+1; i<num; i++) {
						if (data[i] > temp) {
							temp=data[i];
							flg=i;
						}
					}	
					data[flg]=data[j];
					data[j]=temp;
					strcpy (tempc, datac[flg]);
					strcpy (datac[flg], datac[j]);
					strcpy (datac[j], tempc);
				}	
		    	DrawRGraphics(num);
		    	break;
			}
			else if (button == RIGHT_BUTTON && order == 1 && algo == 6) {
				int i, j,flg;
				double temp;
				char tempc[10]; 
		    	InitGraphics();
		    	for (j = 0; j<num; j++) {
		    		temp=data[j];
		    		flg=j;
					for (i = j+1; i<num; i++) {
						if (data[i] < temp) {
							temp=data[i];
							flg=i;
						}
					}	
					data[flg]=data[j];
					data[j]=temp;
					strcpy (tempc, datac[flg]);
					strcpy (datac[flg], datac[j]);
					strcpy (datac[j], tempc);
				}	
		    	DrawRGraphics(num);
		    	break;
			}
			else if (button == LEFT_BUTTON && order == 1 && algo == 6) {	
				
				int i, j,flg;
				double temp;
				char tempc[10]; 
	     		if(selectNum==num){
	     			InitGraphics();
			    	DrawRGraphicsSelect(selectNum);
	     			DrawBGraphicsSelect(num-selectNum);
	     			break;
				 }
				temp=data[selectNum];
		    	flg=selectNum;
				for (i = selectNum+1; i<num; i++) {
					if (data[i] < temp) {
						temp=data[i];
						flg=i;
					}
				}	
				data[flg]=data[selectNum];
				data[selectNum]=temp;
				strcpy (tempc, datac[flg]);
				strcpy (datac[flg], datac[selectNum]);
				strcpy (datac[selectNum], tempc);
				InitGraphics();
				DrawRTriangleSelect(selectNum,flg);
				selectNum++;
				DrawRGraphicsSelect(selectNum);
				DrawBGraphicsSelect(num-selectNum);
	    		DrawAllTxt;
			}
			else if (button == LEFT_BUTTON && order == 0 && algo == 6) {	
				int i, j,flg;
				double temp;
				char tempc[10]; 
	     		if(selectNum==num){
	     			InitGraphics();
			    	DrawRGraphicsSelect(selectNum);
	     			DrawBGraphicsSelect(num-selectNum);
	     			break;
				 }
				temp=data[selectNum];
		    	flg=selectNum;
				for (i = selectNum+1; i<num; i++) {
					if (data[i] > temp) {
						temp=data[i];
						flg=i;
					}
				}	
				data[flg]=data[selectNum];
				data[selectNum]=temp;
				strcpy (tempc, datac[flg]);
				strcpy (datac[flg], datac[selectNum]);
				strcpy (datac[selectNum], tempc);
				InitGraphics();
				DrawRTriangleSelect(selectNum,flg);
				selectNum++;
				DrawRGraphicsSelect(selectNum);
				DrawBGraphicsSelect(num-selectNum);
	    		DrawAllTxt;
			}
			if (index_i < num-2-index_j) index_i++;
			else if (index_j < num-2) {
				index_i = 0;
				index_j++;
				index_done++;
			}
			else DrawRGraphics (num);
			break;
		case BUTTON_DOUBLECLICK: break;
	}
}

void Main() {
	InitGraphics(); 
	GetChar ();	
	GetDouble ();
    GetBasicParameter ();
    SetPenSize(2);
    DrawBGraphics(num);
    MovePen(1,GetWindowHeight()*0.95);
    DrawTextString ("ÅÅÐòÉèÖÃ£º¢ÙÉýÐòÇë°´1£¬½µÐòÇë°´0£»¢ÚÃ°ÅÝÅÅÐòÇë°´4£¬¹é²¢ÅÅÐòÇë°´5£¬Ñ¡ÔñÅÅÐòÇë°´6 ;±£´æÇë°´ 7");
    registerKeyboardEvent(KeyboardEventProcess);
	registerMouseEvent(MouseEventProcess);
} 
