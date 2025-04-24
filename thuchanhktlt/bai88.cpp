#include <stdio.h>
#include <string.h>

struct phanso {
	long tu, mau;
};

typedef struct phanso ps;
long ucln(long a, long b);
long bcnn(long a, long b);
void beautiful(ps *x);
void xuat(ps x);
void swap(ps x);
void rutgon(ps x);
void hopphan(ps x);
void ss(ps x, ps y, long bc);
void tong(ps x, ps y, long bc);
void hieu(ps x, ps y, long bc);
void tich(ps x, ps y);
void thuong(ps x, ps y);

int main(){
	char s[100];
	printf("nhap cac phan so (dang tu/mau) :  ");
	again:
	fgets(s,sizeof(s),stdin);
	 int len = strlen(s)-1;
	// printf("%d\n",len);
	long tu1 = 0, mau1 = 0, tu2=0 , mau2=0, d = 0;
		int index = 0,dau=1;
	for(int i=0; i<len; i++)
	{
		if(s[i]== '/')
		{
			d++;
			if(d==1)
			{
				if (s[index]=='-') 
				{
					dau=-1;
					index++;
				}
				for(int j=index; j<i; j++)
				{						 				
					tu1 = tu1*10 + dau*(s[j]-48);
				}
				index = i+1;
			}
			if(d == 2)
			{	
				if (s[index]=='-') 
				{
					dau=-1;
					index++;
				}
				else dau=1;
				for(int j=index; j<i; j++)
				{
				tu2 = tu2*10 + dau*(s[j]-48);
				}
				index = i+1;
				if (s[index]=='-') 
				{
					dau=-1;
					index++;
				}
				else dau=1;
				for(int k=index; k< len; k++)
				{
					mau2 = mau2*10 + dau*(s[k]-48);
				}
				i=len;
			}
		}
		
		if(i+1== len){
			if (s[index]=='-') 
				{
					dau=-1;
					index++;
				}
				else dau=1;
			for(int j=index; j<=i; j++){
				mau1 = mau1*10 + dau*(s[j]-48);
			}
		}
		if(s[i]==' '){
			if (s[index]=='-') 
				{
					dau=-1;
					index++;
				}
				else dau=1;
			for(int j=index; j<i; j++){
				mau1 = mau1*10 + dau*(s[j]-48);
			}
			index = i+1;
		}	
	}if(d==1 && mau1==0){
		printf("phan so khong hop le\nnhap lai: ");
		goto again;
	}
	if(d==2 && (mau1==0|| mau2==0)){
		printf("phan so khong hop le\nnhap lai: ");
		goto again;
	}
	if (d == 1){
		ps ps_1;
		ps_1.tu =tu1; ps_1.mau=mau1;
		beautiful(&ps_1);
		swap(ps_1);
		printf("Phan so rut gon la : ");
		rutgon(ps_1);
		printf("Hop phan cua phan so la : ");
		hopphan(ps_1);
	}
	else if (d == 2){

		ps ps_2[2];
		ps_2[0].tu=tu1;
		ps_2[0].mau=mau1;
		ps_2[1].tu=tu2;
		ps_2[1].mau=mau2;
		beautiful(&ps_2[0]);
		beautiful(&ps_2[1]);
		long bc = bcnn(ps_2[0].mau, ps_2[1].mau);
		ss(ps_2[0],ps_2[1], bc);
		printf("Boi so chung nho nhat cua 2 mau so la : %ld\n", bc);
		xuat(ps_2[0]); printf(" + "); xuat(ps_2[1]); printf(" = "); tong(ps_2[0], ps_2[1], bc);
		xuat(ps_2[0]); printf(" - "); xuat(ps_2[1]); printf(" = "); hieu(ps_2[0], ps_2[1], bc);
		xuat(ps_2[0]); printf(" * "); xuat(ps_2[1]); printf(" = "); tich(ps_2[0], ps_2[1]);
		xuat(ps_2[0]); printf(" : "); xuat(ps_2[1]); printf(" = "); thuong(ps_2[0], ps_2[1]);
	}
}

long ucln(long a, long b){
	long r;
	while(b){
		r = a % b;
		a = b;
		b = r;
	}
	return a;
}

long bcnn(long a, long b){
	return a*b/ucln(a,b);
}

void beautiful(ps *x){
	if ((x->mau <0)) {
		x->tu = -x->tu;
		x->mau = -x->mau;
	}
}

void xuat(ps x){
	printf("%ld/%ld",x.tu,x.mau);
}

void swap(ps x){
	int a;
	if( x.tu == 0){
		printf("Khong ton tai phan so nghich dao!\n");
		return;
	}
	a = x.tu;
	x.tu = x.mau;
	x.mau = a;
	printf("Phan so nghich dao la : ");
	xuat(x); printf("\n");
}

void rutgon(ps x){
	long a = ucln(x.tu,x.mau);
	if (x.tu % x.mau == 0){
		printf("%ld\n", x.tu / x.mau);
		return;
	}
	a = (a < 0? -a : a);
	x.tu = x.tu / a;
	x.mau = x.mau / a;
	xuat(x); printf("\n");
}

void hopphan(ps x){
	long a = ucln(x.tu,x.mau), b;
	if (x.tu % x.mau == 0){
		printf("%ld\n", x.tu / x.mau);
		return;
	}
	a = (a < 0? -a : a);
	x.tu = x.tu / a;
	x.mau = x.mau / a;
	b = x.tu / x.mau;
	x.tu = x.tu % x.mau;
	if (b > 0) printf("%ld + ", b);
	xuat(x); printf("\n");
}

void ss(ps x, ps y, long bc){
	if (x.tu * bc / x.mau > y.tu * bc / y.mau){
		xuat(x); printf(" > "); xuat(y); printf("\n");
	}
	if (x.tu * bc / x.mau == y.tu * bc / y.mau){
		xuat(x); printf(" = "); xuat(y); printf("\n");
	}
	if (x.tu * bc / x.mau < y.tu * bc / y.mau){
		xuat(x); printf(" < "); xuat(y); printf("\n");
	}
}

void tong(ps x, ps y, long bc){
	ps ps_tong;
	ps_tong.tu = x.tu * bc / x.mau + y.tu * bc / y.mau;
	ps_tong.mau = bc;
	rutgon(ps_tong);
}

void hieu(ps x, ps y, long bc){
	ps ps_hieu;
	long a = x.tu * bc / x.mau - y.tu * bc / y.mau;
	ps_hieu.tu = a;
	ps_hieu.mau = bc;
	rutgon(ps_hieu);
}

void tich(ps x, ps y){
	ps ps_tich;
	ps_tich.tu = x.tu * y.tu;
	ps_tich.mau = x.mau * y.mau;
	rutgon(ps_tich);
}

void thuong(ps x, ps y){
	ps ps_thuong;
	if (y.tu == 0) {
		printf("Khong hop le!");
		return ;
	}
	ps_thuong.tu = x.tu * y.mau;
	ps_thuong.mau = x.mau * y.tu;
	beautiful(&ps_thuong);
	rutgon(ps_thuong);
}
