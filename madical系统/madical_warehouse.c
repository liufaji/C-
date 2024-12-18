int a=10,b=10,c=10,d=10,e=10;

int chef(int i){
	switch(i){
		case 1:
		a-=2;
		if(a>=0){
			return 1;
		}else return 0;
		break;
		case 2:
		b-=2;
		if(b>=0){
			return 1;
		}else return 0;
		break;
		case 3:
		c-=2;
		if(c>=0){
			return 1;
		}else return 0;
		break;
		case 4:
		d-=2;
		if(d>=0){
			return 1;
		}else return 0;
		break;
		case 5:
		e-=2;
		if(e>=0){
			return 1;
		}else return 0;
		break;
	}
}