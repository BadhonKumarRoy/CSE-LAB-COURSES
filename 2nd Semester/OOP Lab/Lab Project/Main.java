// Group Roll's: 04324205101006, 04324205101007 and 04324205101042.
// Updated version:
// Changed the assign or register course by id not by serial number.
import java.util.*;

class Person {
    protected int id;
    protected String name;
    protected int age;
}

class Course {
    String c_id;
    String c_title;
    float credit_hour;

    Scanner scanner = new Scanner(System.in);
    Course[] course = new Course[10];
    String display[] = {"Enter Course ID: ", "Enter Course Title: ", "Enter Credit Hour: "};
    int course0 = 0;

    Course(String c_id, String c_title, float credit_hour) {
        this.c_id = c_id;
        this.c_title = c_title;
        this.credit_hour = credit_hour;
    }

    void Display(int i) {
        System.out.print(display[i]);
    }

    boolean isDuplicateID(String id) {
        for (int i = 0; i < course0; i++) {
            if (course[i].c_id.equals(id)) return true;
        }
        return false;
    }

    void addCourse() {
        int x = 0;
        Display(x++);
        String a = scanner.nextLine();
        if (isDuplicateID(a)) {
            System.out.println("Course ID already exists.");
            return;
        }
        Display(x++);
        String b = scanner.nextLine();
        Display(x);
        float c = scanner.nextFloat();
        scanner.nextLine();

        course[course0] = new Course(a, b, c);
        course0++;
    }

    void addCourse(int i) {
        int x = 0;
        Display(x++);
        String a = scanner.nextLine();
        for (int j = 0; j < course0; j++) {
            if (j != i && course[j].c_id.equals(a)) {
                System.out.println("Course ID already exists.");
                return;
            }
        }
        Display(x++);
        String b = scanner.nextLine();
        Display(x);
        float c = scanner.nextFloat();
        scanner.nextLine();

        course[i] = new Course(a, b, c);
    }

    Course getCourseById(String id) {
        for (int i = 0; i < course0; i++) {
            if (course[i].c_id.equals(id)) return course[i];
        }
        return null;
    }

    void courseList() {
        System.out.println("\nCourses List:\n");
        for (int i = 0; i < course0; i++) {
            System.out.println("------------ " + (i + 1) + " ------------");
            System.out.println("Course ID: " + course[i].c_id);
            System.out.println("Title: " + course[i].c_title);
            System.out.println("Credit Hour: " + course[i].credit_hour);
            System.out.println();
        }
    }
}

class Teacher extends Person {
    String department;
    String designation;
    String courses;
    List<Course> assignedCourses = new ArrayList<>();

    Scanner scanner = new Scanner(System.in);
    static Teacher[] teacher = new Teacher[10];
    String display[] = {"Enter Name: ", "Enter Age: ", "Enter ID: ", "Enter Department: ", "Enter Designation: ", "Enter Courses (optional): "};
    int teacher0 = 0;

    Teacher(String name, int age, int id, String department, String designation) {
        this.name = name;
        this.age = age;
        this.id = id;
        this.department = department;
        this.designation = designation;
    }

    void assignCourse(Course c) {
        assignedCourses.add(c);
    }

    void Display(int i) {
        System.out.print(display[i]);
    }

    boolean isDuplicateID(int id) {
        for (int i = 0; i < teacher0; i++) {
            if (teacher[i].id == id) return true;
        }
        return false;
    }

    void addTeacher() {
        int x = 0;
        Display(x++);
        String a = scanner.nextLine();
        Display(x++);
        int b = scanner.nextInt();
        Display(x++);
        int c = scanner.nextInt();
        if (isDuplicateID(c)) {
            System.out.println("Teacher ID already exists.");
            scanner.nextLine();
            return;
        }
        Display(x++);
        scanner.nextLine();
        String d = scanner.nextLine();
        Display(x++);
        String e = scanner.nextLine();

        teacher[teacher0] = new Teacher(a, b, c, d, e);
        teacher0++;
    }

    void addTeacher(int i) {
        int x = 0;
        Display(x++);
        String a = scanner.nextLine();
        Display(x++);
        int b = scanner.nextInt();
        Display(x++);
        int c = scanner.nextInt();
        for (int j = 0; j < teacher0; j++) {
            if (j != i && teacher[j].id == c) {
                System.out.println("Teacher ID already exists.");
                scanner.nextLine();
                return;
            }
        }
        Display(x++);
        scanner.nextLine();
        String d = scanner.nextLine();
        Display(x++);
        String e = scanner.nextLine();

        teacher[i] = new Teacher(a, b, c, d, e);
    }

    Teacher getTeacherById(int id) {
        for (int i = 0; i < teacher0; i++) {
            if (teacher[i].id == id) return teacher[i];
        }
        return null;
    }

    int getTeacherIndexById(int id) {
        for (int i = 0; i < teacher0; i++) {
            if (teacher[i].id == id) return i;
        }
        return -1;
    }

    void teacherList() {
        System.out.println("\nTeachers List:\n");
        for (int i = 0; i < teacher0; i++) {
            System.out.println("------------ " + (i + 1) + " ------------");
            System.out.println("Name: " + teacher[i].name);
            System.out.println("ID: " + teacher[i].id);
            System.out.println("Department: " + teacher[i].department);
            System.out.println("Designation: " + teacher[i].designation);
            System.out.println("Assigned Courses:");
            for (Course c : teacher[i].assignedCourses) {
                System.out.println(" - " + c.c_title);
            }
            System.out.println();
        }
    }
}

class Student extends Person {
    String department;
    String semester;
    String batch;
    String grade;
    List<Course> registeredCourses = new ArrayList<>();

    Scanner scanner = new Scanner(System.in);
    static Student[] student = new Student[10];
    String display[] = {"Enter Name: ", "Enter Age: ", "Enter ID: ", "Enter Department: ", "Enter Batch: ", "Enter Semester: ", "Enter Grade: "};
    int student0 = 0;

    Student(String name, int age, int id, String department, String batch, String semester, String grade) {
        this.name = name;
        this.age = age;
        this.id = id;
        this.department = department;
        this.batch = batch;
        this.semester = semester;
        this.grade = grade;
    }

    void registerCourse(Course c) {
        registeredCourses.add(c);
    }

    void Display(int i) {
        System.out.print(display[i]);
    }

    boolean isDuplicateID(int id) {
        for (int i = 0; i < student0; i++) {
            if (student[i].id == id) return true;
        }
        return false;
    }

    void addStudent() {
        int x = 0;
        Display(x++);
        String a = scanner.nextLine();
        Display(x++);
        int b = scanner.nextInt();
        Display(x++);
        int c = scanner.nextInt();
        if (isDuplicateID(c)) {
            System.out.println("Student ID already exists.");
            scanner.nextLine();
            return;
        }
        Display(x++);
        scanner.nextLine();
        String d = scanner.nextLine();
        Display(x++);
        String e = scanner.nextLine();
        Display(x++);
        String f = scanner.nextLine();
        Display(x);
        String g = scanner.nextLine();

        student[student0] = new Student(a, b, c, d, e, f, g);
        student0++;
    }

    void addStudent(int i) {
        int x = 0;
        Display(x++);
        String a = scanner.nextLine();
        Display(x++);
        int b = scanner.nextInt();
        Display(x++);
        int c = scanner.nextInt();
        for (int j = 0; j < student0; j++) {
            if (j != i && student[j].id == c) {
                System.out.println("Student ID already exists.");
                scanner.nextLine();
                return;
            }
        }
        Display(x++);
        scanner.nextLine();
        String d = scanner.nextLine();
        Display(x++);
        String e = scanner.nextLine();
        Display(x++);
        String f = scanner.nextLine();
        Display(x);
        String g = scanner.nextLine();

        student[i] = new Student(a, b, c, d, e, f, g);
    }

    Student getStudentById(int id) {
        for (int i = 0; i < student0; i++) {
            if (student[i].id == id) return student[i];
        }
        return null;
    }

    int getStudentIndexById(int id) {
        for (int i = 0; i < student0; i++) {
            if (student[i].id == id) return i;
        }
        return -1;
    }

    void studentList() {
        System.out.println("\nStudents List:\n");
        for (int i = 0; i < student0; i++) {
            System.out.println("------------ " + (i + 1) + " ------------");
            System.out.println("Name: " + student[i].name);
            System.out.println("ID: " + student[i].id);
            System.out.println("Department: " + student[i].department);
            System.out.println("Batch: " + student[i].batch);
            System.out.println("Grade: " + student[i].grade);
            System.out.println("Semester: " + student[i].semester);
            System.out.println("Registered Courses:");
            for (Course c : student[i].registeredCourses) {
                System.out.println(" - " + c.c_title);
            }
            System.out.println();
        }
    }
}

class Menu {
    void displayTask() {
        System.out.println("\nMenu-\n");
        System.out.println("1. Add Teacher.");
        System.out.println("2. Edit Teacher Info.");
        System.out.println("3. View Teacher List.");
        System.out.println();
        System.out.println("4. Add Student.");
        System.out.println("5. Edit Student Info.");
        System.out.println("6. View Student List.");
        System.out.println();
        System.out.println("7. Add Course.");
        System.out.println("8. Edit Course Info.");
        System.out.println("9. View Course List.");
        System.out.println();
        System.out.println("10. Assign Course to Teacher");
        System.out.println("11. Register Course for Student");
        System.out.println("\n0. Exit");
        System.out.println();
    }
}

public class Main {
    public static void main(String[] args) {
        try (Scanner scanner = new Scanner(System.in)) {
            Menu menu = new Menu();
            Teacher te = new Teacher(null, 0, 0, null, null);
            Student st = new Student(null, 0, 0, null, null, null, null);
            Course co = new Course(null, null, 0);

            System.out.println("\n------WELCOME------");

            while (true) {
                try {
                    menu.displayTask();
                    System.out.print("Choose an option: ");
                    int input = Integer.parseInt(scanner.nextLine());

                    if (input == 1) {
                        te.addTeacher();
                    }

                    else if (input == 2) {
                        te.teacherList();
                        System.out.print("Enter Teacher ID: ");
                        int id = Integer.parseInt(scanner.nextLine());
                        int idx = te.getTeacherIndexById(id);
                        if (idx != -1) {
                            te.addTeacher(idx);
                        } else {
                            System.out.println("Teacher not found.");
                        }
                    }

                    else if (input == 3) {
                        te.teacherList();
                    }

                    else if (input == 4) {
                        st.addStudent();
                    }

                    else if (input == 5) {
                        st.studentList();
                        System.out.print("Enter Student ID: ");
                        int id = Integer.parseInt(scanner.nextLine());
                        int idx = st.getStudentIndexById(id);
                        if (idx != -1) {
                            st.addStudent(idx);
                        } else {
                            System.out.println("Student not found.");
                        }
                    }

                    else if (input == 6) {
                        st.studentList();
                    }

                    else if (input == 7) {
                        co.addCourse();
                    }

                    else if (input == 8) {
                        co.courseList();
                        System.out.print("Enter Course ID: ");
                        String cid = scanner.nextLine();
                        boolean found = false;
                        for (int i = 0; i < co.course0; i++) {
                            if (co.course[i].c_id.equals(cid)) {
                                co.addCourse(i);
                                found = true;
                                break;
                            }
                        }
                        if (!found) {
                            System.out.println("Course not found.");
                        }
                    }

                    else if (input == 9) {
                        co.courseList();
                    }

                    else if (input == 10) {
                        te.teacherList();
                        System.out.print("Enter Teacher ID: ");
                        int tid = Integer.parseInt(scanner.nextLine());
                        Teacher teacherObj = te.getTeacherById(tid);
                        if (teacherObj != null) {
                            co.courseList();
                            System.out.print("Enter Course ID: ");
                            String cid = scanner.nextLine();
                            Course courseObj = co.getCourseById(cid);
                            if (courseObj != null) {
                                teacherObj.assignCourse(courseObj);
                                System.out.println("Course assigned successfully.");
                            } else {
                                System.out.println("Course not found.");
                            }
                        } else {
                            System.out.println("Teacher not found.");
                        }
                    }

                    else if (input == 11) {
                        st.studentList();
                        System.out.print("Enter Student ID: ");
                        int sid = Integer.parseInt(scanner.nextLine());
                        Student studentObj = st.getStudentById(sid);
                        if (studentObj != null) {
                            co.courseList();
                            System.out.print("Enter Course ID: ");
                            String cid = scanner.nextLine();
                            Course courseObj = co.getCourseById(cid);
                            if (courseObj != null) {
                                studentObj.registerCourse(courseObj);
                                System.out.println("Course registered successfully.");
                            } else {
                                System.out.println("Course not found.");
                            }
                        } else {
                            System.out.println("Student not found.");
                        }
                    }

                    else if (input == 0) {
                        System.out.println(".........Exited.........");
                        break;
                    }

                    else {
                        System.out.println("Invalid option. Please choose from the menu.");
                    }
                } catch (NumberFormatException e) {
                    System.out.println("Invalid input! Please enter a number.");
                } catch (InputMismatchException e) {
                    System.out.println("Mismatched input type. Please try again.");
                    scanner.nextLine();
                } catch (Exception e) {
                    System.out.println("An unexpected error occurred: ");
                }
            }
        }
    }
}