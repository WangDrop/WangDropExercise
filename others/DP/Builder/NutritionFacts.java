package com.wc.Builder;

public class NutritionFacts {
	private int servingSize;
	private int servings;
	private int calories;
	private int fat;
	private int sodium;
	private int carbonhydrate;

	public NutritionFacts(Builder builder) {
		servingSize = builder.servingSize;
		servings = builder.serving;
		this.calories = builder.calories;
		this.fat = builder.fat;
		this.sodium = builder.sodium;
		this.carbonhydrate = builder.carbonhydrate;
	}

	public static class Builder {
		private int servingSize;
		private int serving;
		private int calories;
		private int fat;
		private int sodium;
		private int carbonhydrate;

		public Builder(int servingSize, int serving) {
			this.serving = serving;
			this.servingSize = servingSize;
		}

		public Builder calories(int val) {
			this.calories = val;
			return this;
		}

		public Builder fat(int val) {
			this.fat = val;
			return this;
		}

		public Builder sodium(int val) {
			this.sodium = val;
			return this;
		}

		public Builder carbonhydrate(int val) {
			this.carbonhydrate = val;
			return this;
		}

		public NutritionFacts build() {
			return new NutritionFacts(this);
		}
	}

	@Override
	public String toString() {
		return "NutritionFacts [servingSize=" + servingSize + ", servings="
				+ servings + ", calories=" + calories + ", fat=" + fat
				+ ", sodium=" + sodium + ", carbonhydrate=" + carbonhydrate
				+ "]";
	}

	public static void main(String [] arg) {
		NutritionFacts nutritionFacts = new NutritionFacts.Builder(100, 100)
				.calories(100).carbonhydrate(10).fat(2).sodium(4).build();
		System.out.println(nutritionFacts);
	}
}
