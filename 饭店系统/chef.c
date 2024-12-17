int a=10,b=10,c=10;

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
	}
}