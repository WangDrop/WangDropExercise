	double searchNumber(double x){
		if(x < 2.0) return 0.0;
		double lower = 0.0, higher = x/2;
		double mid = 0.0;
		double diff = 0.0;
		while(true){
			mid = (lower + higher)/2.0;
			diff = mid*mid - x;
			if(Math.abs(diff) < 0.01){
				return mid;
			}else if(diff > 0.01){
				higher = mid;
			}else if(diff < -0.01){
				lower = mid;
			}
			System.out.println(mid);
		}
	}