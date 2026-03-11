class EmployeeSalary{
	double Basic_Salary, Bonus, Deductions;
	EmployeeSalary(double S){
		Basic_Salary = S;
		double Net_Salary = Basic_Salary + 2000;
		System.out.println("Employee 1 Net Salary (Basic + Allowance): " + Net_Salary);
	}
	EmployeeSalary(double S, double B){
		Basic_Salary = S;
		Bonus = B;
		double Deductions = 5000;
		double Net_Salary = Basic_Salary + Bonus;
		System.out.println("Employee 2 Net Salary (Basic + Bonus): " + Net_Salary);
	}
	EmployeeSalary(double S, double B, double D){
		Basic_Salary = S;
		Bonus = B;
		Deductions = D;
		double Net_Salary = Basic_Salary + Bonus - Deductions;
		System.out.println("Employee 3 Net Salary (Basic + Bonus - Deductions): " + Net_Salary);
	}
	public static void main(String args[]){
		EmployeeSalary E1 = new EmployeeSalary(30000);
		EmployeeSalary E2 = new EmployeeSalary(30000, 5000);
		EmployeeSalary E3 = new EmployeeSalary(30000, 5000, 1000);
	}
}