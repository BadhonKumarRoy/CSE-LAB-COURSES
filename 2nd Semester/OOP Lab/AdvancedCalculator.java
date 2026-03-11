class AdvancedCalculator{
	int num1, num2;
	double n1, n2;
	char operator;
	void operate(int a, int b, char c){
		num1 = a;
		num2 = b;
		operator = c;
		if(operator == '+')
		{
			int sum = num1 + num2;
				System.out.println("Integer Operation: " + num1 + " + " + num2 + " = " + sum);
		}
		else if(operator == '-'){
			int sub = num1 - num2;
				System.out.println("Integer Operation: " + num1 + " - " + num2 + " = " + sub);
		}
		else if(operator == '*'){
			int mul = num1 * num2;
				System.out.println("Integer Operation: " + num1 + " x " + num2 + " = " + mul);
		}
		else if(operator == '/'){
			if(num2 == 0){
				System.out.println("Error: Division by zero is not allowed.");
			}
			else{
				int div = num1 / num2;
				System.out.println("Integer Operation: " + num1 + " / " + num2 + " = " + div);
			}
		}
	}
	void operate(double a, double b, char c){
		n1 = a;
		n2 = b;
		operator = c;
		if(operator == '+')
		{
			double sum = num1 + num2;
				System.out.println("Decimal Operation: " + num1 + " + " + num2 + " = " + sum);
		}
		else if(operator == '-'){
			double sub = num1 - num2;
				System.out.println("Decimal Operation: " + num1 + " - " + num2 + " = " + sub);
		}
		else if(operator == '*'){
			double mul = num1 * num2;
				System.out.println("Decimal Operation: " + num1 + " x " + num2 + " = " + mul);
		}
		else if(operator == '/'){
			if(n2 == 0){
				System.out.println("Error: Division by zero is not allowed.");
			}
			else{
				double div = n1 / n2;
				System.out.println("Decimal Operation: " + n1 + " / " + n2 + " = " + div);
			}
		}
	}
	public static void main(String args[]){
		AdvancedCalculator a1 = new AdvancedCalculator();
		AdvancedCalculator a2 = new AdvancedCalculator();
		AdvancedCalculator a3 = new AdvancedCalculator();
		a1.operate(10, 5, '+');
		a2.operate(10.5, 2.5, '/');
		a3.operate(10.5, 0.0, '/');
	}
}