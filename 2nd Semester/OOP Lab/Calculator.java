import java.util.Scanner;
class test{
	double a, b;
	void initializer(double a, double b){
		this.a = a;
		this.b = b;
	}
	void sum(){
		double sum = a + b;
		System.out.println();
		System.out.println("   The summation of "+ a +" and "+ b + " is ("+ sum + ").");
		System.out.println();
	}
	void sub(){
		double sub = a - b;
		System.out.println();
		System.out.println("   The subtraction of "+ a +" and "+ b + " is ("+ sub + ").");
		System.out.println();
	}
	void mul(){
		double mul = a * b;
		System.out.println();
		System.out.println("   The multiplication of "+ a +" and "+ b + " is ("+ mul + ").");
		System.out.println();
	}
	void div(){
		double div = a / b;
		System.out.println();
        if(b == 0){
            System.out.println("   Error: Division by zero is not allowed.");
        }
        else{
            System.out.println("   The division of "+ a +" and "+ b + " is ("+ div + ").");
        }
		System.out.println();
	}

	public static void main(String args[]){
		Scanner scan = new Scanner(System.in);
		System.out.println("---Simple calculator for two numbers---");
		System.out.println();
		System.out.println();
		while(true){
			System.out.print("   Enter the first number - ");
					double num1 = scan.nextDouble();
					System.out.print("   Enter the second number - ");
					double num2 = scan.nextDouble();
					test c1 = new test();
					c1.initializer(num1, num2);
					System.out.println("   Enter a value 1 to 4..");
					System.out.println("   Where-");
					System.out.println("        1 for sum.");
					System.out.println("        2 for sub.");
					System.out.println("        3 for mul.");
					System.out.println("        4 for div.");
					System.out.print("   ");
					int num3;
					while(true){
						num3 = scan.nextInt();
						if(num3 < 1 || num3 > 4){
							System.out.print("   Invalid input re-enter the value - ");
						}
						else{
							break;
						}
					}
					if(num3 == 1){
						c1.sum();
					}
					else if(num3 == 2){
						c1.sub();
					}
					else if(num3 == 3){
						c1.mul();
					}
					else{
						c1.div();
					}
					System.out.println("   Enter 1 to start a new calculation... or Enter 2 to exit... - ");
					int num4;
					while(true){
						System.out.print("   ");
						num4 = scan.nextInt();
						if(num4 < 1 || num4 > 2){
							System.out.println("   Invalid Input!");
						}
						else{
							break;
						}
					}
					if(num4 == 2){
						break;
					}
		}
	}
}
